///////////////////////////////////////////////////////////////////////////////
//
// wxFormBuilder - A Visual Dialog Editor for wxWidgets.
// Copyright (C) 2005 Jos� Antonio Hurtado
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//
// Written by Jos� Antonio Hurtado - joseantonio.hurtado@hispalinux.es
//
///////////////////////////////////////////////////////////////////////////////

#include "appdata.h"
#include "utils/typeconv.h"
#include "utils/debug.h"
#include "codegen/codegen.h"

using namespace TypeConv;

ApplicationData::ApplicationData()
{
  m_objDb = PObjectDatabase(new ObjectDatabase());
  m_objDb->SetXmlPath("./xml/");
  m_objDb->SetIconPath("./xpm/");
  m_objDb->LoadFile();
  /*
  PObjectInfo obj = m_objDb->GetObjectInfo("wxButton");
  PCodeInfo code_info = obj->GetCodeInfo("C++");
  
  Debug::Print((char *)(code_info->GetTemplate("construction").c_str()));
  Debug::Print((char *)(code_info->GetTemplate("declaration").c_str()));  
  
  {
    TemplateParser parser(PObjectBase(),code_info->GetTemplate("construction"));
    Debug::Print((char *)parser.ParseTemplate().c_str());
  }
  {
    TemplateParser parser(PObjectBase(),code_info->GetTemplate("declaration"));
    Debug::Print((char *)parser.ParseTemplate().c_str());
  }*/

  // creamos un arbol provisional
  
/*  PObjectBase project = m_objDb->CreateObject("Project");
  assert(project);
  PObjectBase form = m_objDb->CreateObject("Panel",project);
  PObjectBase os = m_objDb->CreateObject("wxBoxSizer",form);
  
  PObjectBase ob1 = m_objDb->CreateObject("wxButton",os);
  PObjectBase ob2 = m_objDb->CreateObject("wxButton",os);
  
  m_project = shared_dynamic_cast<ProjectObject>(project);*/
}  
  
PObjectBase ApplicationData::GetSelectedObject()
{
  return m_selObj;
}  

PObjectBase ApplicationData::GetSelectedForm()
{
  if (m_selObj->GetObjectType() == T_FORM)
    return m_selObj;
  else
    return m_selObj->FindNearAncestor(T_FORM);
}
  

PProjectObject ApplicationData::GetProjectData()
{
  return m_project;
}  


///////////////////////////////////////////////////////////////////////////////

void ApplicationData::SelectObject(PObjectBase obj)
{
  Debug::Print("Object Selected!");
  m_selObj = obj;
/*  
  if (obj->GetObjectType() != T_FORM)
  {
    m_selForm = shared_dynamic_cast<FormObject>(obj->FindNearAncestor(T_FORM));
  }
  else
    m_selForm = shared_dynamic_cast<FormObject>(obj);*/
    
  DataObservable::NotifyObjectSelected(obj);
}
  
void ApplicationData::CreateObject(wxString name)
{
  Debug::Print("ApplicationData::CreateObject] New %s",name.c_str());

  PObjectBase parent = GetSelectedObject();
  PObjectBase obj;
  if (parent)
  {
    obj = m_objDb->CreateObject(string(name.mb_str()),parent);
  }  
  
  DataObservable::NotifyObjectCreated(obj);
}
  
void ApplicationData::RemoveObject(PObjectBase obj)
{
  PObjectBase parent = obj->GetParent();
  if (parent && parent->GetObjectType() == T_SIZERITEM)
    obj = parent;

  SelectObject(obj->GetParent());

  obj->GetParent()->RemoveChild(obj);
  obj->SetParent(PObjectBase());
  
  DataObservable::NotifyObjectRemoved(obj);
}

void ApplicationData::CutObject(PObjectBase obj)
{
  m_clipboard = obj;
  RemoveObject(obj);
}

void ApplicationData::PasteObject(PObjectBase parent)
{
  if (m_clipboard)
  {
    // no me gusta este c�digo, es una copia de un trozo del m�todo
    // CreateObject de la clase ObjectDatabase. De momento
    // es solo un apa�o
    if (parent->GetObjectType() == T_SIZER && m_clipboard->GetObjectType() != T_SIZERITEM)
    {
      PObjectBase sizeritem(m_objDb->CreateObject("sizeritem"));
      sizeritem->AddChild(m_clipboard);
      m_clipboard->SetParent(sizeritem);

      parent->AddChild(sizeritem);
      sizeritem->SetParent(parent);
    }
    else
    {
      parent->AddChild(m_clipboard);
      m_clipboard->SetParent(parent);
    }
    
    m_clipboard.reset();
  }
  DataObservable::NotifyProjectRefresh();  
}
  
void ApplicationData::ModifyProperty(PProperty prop, wxString str)
{
  PObjectBase object = prop->GetObject();
  
  if (_STDSTR(str) != prop->GetValue())
  {
    prop->SetValue(string(str.mb_str()));
    DataObservable::NotifyPropertyModified(prop);
  }  
}
  

void ApplicationData::SaveProject(const wxString &filename)
{
  TiXmlDocument *doc = m_project->Serialize();
  doc->SaveFile(filename.mb_str());
  delete doc;
  
  DataObservable::NotifyProjectSaved();
}  

bool ApplicationData::LoadProject(const wxString &file)
{
  Debug::Print("LOADING");
  
  bool result = false;
  
  TiXmlDocument *doc = new TiXmlDocument();
  if (doc->LoadFile(file.mb_str()))
  {
    m_objDb->ResetObjectCounters();
    
    TiXmlElement *root = doc->RootElement();
    PObjectBase proj = m_objDb->CreateObject(root);
    if (proj && proj->GetObjectType()== T_PROJECT)
    {
      PObjectBase old_proj = m_project;
      m_project = shared_dynamic_cast<ProjectObject>(proj);
      m_selObj = m_project;
      result = true;
      DataObservable::NotifyProjectLoaded();
    }
  }
  delete doc;  
 
  return result;
}

void ApplicationData::NewProject()
{
  m_project = shared_dynamic_cast<ProjectObject>(m_objDb->CreateObject("Project"));
  m_selObj = m_project;
  DataObservable::NotifyProjectRefresh();  
}

void ApplicationData::GenerateCode()
{
  DataObservable::NotifyCodeGeneration();
}


void ApplicationData::MovePosition(PObjectBase obj, bool right, unsigned int num)
{
  PObjectBase parent = obj->GetParent();
  if (parent)
  {
    if (parent->GetObjectType() == T_SIZERITEM)
    {
      obj = parent;
      parent = parent->GetParent();
    }
      
    unsigned int pos = parent->GetChildPosition(obj);
    
    // nos aseguramos de que los l�mites son correctos
    
    unsigned int children_count = parent->GetChildCount();
    
    if ((right && num + pos < children_count) ||
        !right  && (num <= pos))
    {
      pos = (right ? pos+num : pos-num);
      
      parent->ChangeChildPosition(obj,pos);
      DataObservable::NotifyProjectRefresh();
    }
  }
}

