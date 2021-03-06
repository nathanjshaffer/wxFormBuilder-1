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
// Written by
//   Jos� Antonio Hurtado - joseantonio.hurtado@gmail.com
//   Juan Antonio Ortega  - jortegalalmolda@gmail.com
//
///////////////////////////////////////////////////////////////////////////////

#include "appdata.h"
#include "utils/typeconv.h"
#include "utils/debug.h"
#include "codegen/codegen.h"
#include "rad/global.h"

using namespace TypeConv;


///////////////////////////////////////////////////////////////////////////////
// Comandos
///////////////////////////////////////////////////////////////////////////////

/**
 * Comando para insertar un objeto en el �rbol.
 */
class InsertObjectCmd : public Command
{
 private:
  ApplicationData *m_data;
  PObjectBase m_parent;
  PObjectBase m_object;
  int m_pos;
  PObjectBase m_oldSelected;


 protected:
  void DoExecute();
  void DoRestore();

 public:
   InsertObjectCmd(ApplicationData *data, PObjectBase object, PObjectBase parent, int pos = -1);
};

/**
 * Comando para borrar un objeto.
 */
class RemoveObjectCmd : public Command
{
private:
  ApplicationData *m_data;
  PObjectBase m_parent;
  PObjectBase m_object;
  int m_oldPos;
  PObjectBase m_oldSelected;

 protected:
  void DoExecute();
  void DoRestore();

 public:
   RemoveObjectCmd(ApplicationData *data,PObjectBase object);
};

/**
 * Comando para modificar una propiedad.
 */
class ModifyPropertyCmd : public Command
{
 private:
  PProperty m_property;
  string m_oldValue, m_newValue;

 protected:
  void DoExecute();
  void DoRestore();

 public:
  ModifyPropertyCmd(PProperty prop, string value);
};

/**
 * Comando para mover de posici�n un objeto.
 */
class ShiftChildCmd : public Command
{
 private:
  PObjectBase m_object;
  int m_oldPos, m_newPos;

 protected:
  void DoExecute();
  void DoRestore();

 public:
  ShiftChildCmd(PObjectBase object, int pos);

};

/**
 * CutObjectCmd ademas de eliminar el objeto del �rbol se asegura
 * de eliminar la referencia "clipboard" deshacer el cambio.
 */
class CutObjectCmd : public Command
{
 private:
  // necesario para consultar/modificar el objeto "clipboard"
  ApplicationData *m_data;
  //PObjectBase m_clipboard;
  PObjectBase m_parent;
  PObjectBase m_object;
  int m_oldPos;
  PObjectBase m_oldSelected;

 protected:
  void DoExecute();
  void DoRestore();

 public:
  CutObjectCmd(ApplicationData *data, PObjectBase object);
};

/**
 * Cambia el padre.
 */
class ReparentObjectCmd : public Command
{
 private:
	PObjectBase m_sizeritem;
	PObjectBase m_sizer;
	PObjectBase m_oldSizer;
 protected:
  void DoExecute();
  void DoRestore();

 public:
  ReparentObjectCmd (PObjectBase sizeritem, PObjectBase sizer);
};

///////////////////////////////////////////////////////////////////////////////
// Implementaci�n de los Comandos
///////////////////////////////////////////////////////////////////////////////

InsertObjectCmd::InsertObjectCmd(ApplicationData *data, PObjectBase object,
                                 PObjectBase parent, int pos)
  : m_data(data), m_parent(parent), m_object(object), m_pos(pos)
{
  m_oldSelected = data->GetSelectedObject();
}

void InsertObjectCmd::DoExecute()
{
  m_parent->AddChild(m_object);
  m_object->SetParent(m_parent);

  if (m_pos >= 0)
    m_parent->ChangeChildPosition(m_object,m_pos);
}

void InsertObjectCmd::DoRestore()
{
  m_parent->RemoveChild(m_object);
  m_object->SetParent(PObjectBase());
  m_data->SelectObject(m_oldSelected);
}

//-----------------------------------------------------------------------------

RemoveObjectCmd::RemoveObjectCmd(ApplicationData *data, PObjectBase object)
{
  m_data = data;
  m_object = object;
  m_parent = object->GetParent();
  m_oldPos = m_parent->GetChildPosition(object);
  m_oldSelected = data->GetSelectedObject();
}

void RemoveObjectCmd::DoExecute()
{
  m_parent->RemoveChild(m_object);
  m_object->SetParent(PObjectBase());
}

void RemoveObjectCmd::DoRestore()
{
  m_parent->AddChild(m_object);
  m_object->SetParent(m_parent);

  // restauramos la posici�n
  m_parent->ChangeChildPosition(m_object,m_oldPos);
  m_data->SelectObject(m_oldSelected);
}

//-----------------------------------------------------------------------------

ModifyPropertyCmd::ModifyPropertyCmd(PProperty prop, string value)
  : m_property(prop), m_newValue(value)
{
  m_oldValue = prop->GetValue();
}

void ModifyPropertyCmd::DoExecute()
{
  m_property->SetValue(m_newValue);
}

void ModifyPropertyCmd::DoRestore()
{
  m_property->SetValue(m_oldValue);
}

//-----------------------------------------------------------------------------

ShiftChildCmd::ShiftChildCmd(PObjectBase object, int pos)
{
  m_object = object;
  PObjectBase parent = object->GetParent();

  assert(parent);

  m_oldPos = parent->GetChildPosition(object);
  m_newPos = pos;
}

void ShiftChildCmd::DoExecute()
{
  if (m_oldPos != m_newPos)
  {
    PObjectBase parent (m_object->GetParent());
    parent->ChangeChildPosition(m_object,m_newPos);
  }
}

void ShiftChildCmd::DoRestore()
{
  if (m_oldPos != m_newPos)
  {
    PObjectBase parent (m_object->GetParent());
    parent->ChangeChildPosition(m_object,m_oldPos);
  }
}

//-----------------------------------------------------------------------------

CutObjectCmd::CutObjectCmd(ApplicationData *data, PObjectBase object)
{
  m_data = data;
  m_object = object;
  m_parent = object->GetParent();
  m_oldPos = m_parent->GetChildPosition(object);
  m_oldSelected = data->GetSelectedObject();
}

void CutObjectCmd::DoExecute()
{
  // guardamos el clipboard ???
  //m_clipboard = m_data->GetClipboardObject();

  m_data->SetClipboardObject(m_object);
  m_parent->RemoveChild(m_object);
  m_object->SetParent(PObjectBase());
}

void CutObjectCmd::DoRestore()
{
  // reubicamos el objeto donde estaba
  m_parent->AddChild(m_object);
  m_object->SetParent(m_parent);
  m_parent->ChangeChildPosition(m_object,m_oldPos);

  // restauramos el clipboard
  //m_data->SetClipboardObject(m_clipboard);
  m_data->SetClipboardObject(PObjectBase());
  m_data->SelectObject(m_oldSelected);
}

//-----------------------------------------------------------------------------

ReparentObjectCmd ::ReparentObjectCmd (PObjectBase sizeritem, PObjectBase sizer)
{
	m_sizeritem = sizeritem;
	m_sizer = sizer;
	m_oldSizer = m_sizeritem->GetParent();
}

void ReparentObjectCmd::DoExecute()
{
  m_oldSizer->RemoveChild(m_sizeritem);
  m_sizeritem->SetParent(m_sizer);
  m_sizer->AddChild(m_sizeritem);
}

void ReparentObjectCmd::DoRestore()
{
  m_sizer->RemoveChild(m_sizeritem);
  m_sizeritem->SetParent(m_oldSizer);
  m_oldSizer->AddChild(m_sizeritem);
}

///////////////////////////////////////////////////////////////////////////////
// ApplicationData
///////////////////////////////////////////////////////////////////////////////

ApplicationData::ApplicationData(const string &rootdir)
{
  m_rootDir = rootdir;
  m_objDb = PObjectDatabase(new ObjectDatabase());
  m_objDb->SetXmlPath(m_rootDir + "/xml/");
  m_objDb->SetIconPath(m_rootDir + "/xpm/");
  m_objDb->LoadObjectTypes();
  m_objDb->LoadFile();
}

PObjectBase ApplicationData::GetSelectedObject()
{
  return m_selObj;
}

PObjectBase ApplicationData::GetSelectedForm()
{
  if (m_selObj->GetObjectTypeName() == "form")
    return m_selObj;
  else
    return m_selObj->FindNearAncestor("form");
}


PObjectBase ApplicationData::GetProjectData()
{
  return m_project;
}

void ApplicationData::BuildNameSet(PObjectBase obj, PObjectBase top, set<string> &name_set)
{
  if (obj != top)
  {
    PProperty nameProp = top->GetProperty("name");
    if (nameProp)
      name_set.insert(nameProp->GetValue());
  }

  for (unsigned int i=0; i< top->GetChildCount(); i++)
    BuildNameSet(obj, top->GetChild(i), name_set);
}

void ApplicationData::ResolveNameConflict(PObjectBase obj)
{
  while (obj && obj->GetObjectInfo()->GetObjectType()->IsItem())
  {
    if (obj->GetChildCount() > 0)
      obj = obj->GetChild(0);
    else
      return;
  }

  PProperty nameProp = obj->GetProperty("name");
  if (!nameProp)
    return;

  string name = nameProp->GetValue();

  // el nombre no puede estar repetido dentro del mismo form
  PObjectBase top = obj->FindNearAncestor("form");
  if (!top)
    top = m_project; // el objeto es un form.

  // construimos el conjunto de nombres
  set<string> name_set;
  BuildNameSet(obj, top, name_set);

  // comprobamos si hay conflicto
  set<string>::iterator it = name_set.find(name);
  while (it != name_set.end())
  {
    name = name + "_";
    it = name_set.find(name);
  }

  nameProp->SetValue(name);
}

void ApplicationData::ResolveSubtreeNameConflicts(PObjectBase obj, PObjectBase topObj)
{
  if (!topObj)
  {
    topObj = obj->FindNearAncestor("form");
    if (!topObj)
      topObj = m_project; // object is the project
  }

  // Ignore item objects
  while (obj && obj->GetObjectInfo()->GetObjectType()->IsItem())
  {
    if (obj->GetChildCount() > 0)
      obj = obj->GetChild(0);
    else
      return; // error
  }

  // Resolve a possible name conflict
  ResolveNameConflict(obj);

  // Recurse through all children
  for (unsigned int i=0 ; i < obj->GetChildCount() ; i++)
    ResolveSubtreeNameConflicts(obj->GetChild(i), topObj);
}

int ApplicationData::CalcPositionOfInsertion(PObjectBase selected,PObjectBase parent)
{
  int pos = -1;

  if (parent && selected)
  {
    PObjectBase parentSelected = selected->GetParent();
    while (parentSelected && parentSelected != parent)
    {
      selected = parentSelected;
      parentSelected = selected->GetParent();
    }

    if (parentSelected && parentSelected == parent)
      pos = parent->GetChildPosition(selected) + 1;
  }

  return pos;
}

void ApplicationData::RemoveEmptyItems(PObjectBase obj)
{
  if (!obj->GetObjectInfo()->GetObjectType()->IsItem())
  {
    bool emptyItem = true;

    // esto es un algoritmo ineficiente pero "seguro" con los �ndices
    while (emptyItem)
    {
      emptyItem = false;
      for (unsigned int i=0; !emptyItem && i<obj->GetChildCount(); i++)
      {
        PObjectBase child = obj->GetChild(i);
        if (child->GetObjectInfo()->GetObjectType()->IsItem() &&
            child->GetChildCount() == 0)
        {
          obj->RemoveChild(child); // borramos el item
          child->SetParent(PObjectBase());

          emptyItem = true;        // volvemos a recorrer
          wxString msg;
          msg.Printf(wxT("Empty item removed under %s"),obj->GetPropertyAsString(wxT("name")).c_str());
          wxLogWarning(msg);
        }
      }
    }
  }

  for (unsigned int i=0; i<obj->GetChildCount() ; i++)
    RemoveEmptyItems(obj->GetChild(i));
}

PObjectBase ApplicationData::SearchSizerInto(PObjectBase obj)
{
  PObjectBase theSizer;

  if (obj->GetObjectTypeName() == "sizer")
    theSizer = obj;
  else
  {
    for (unsigned int i = 0; !theSizer && i < obj->GetChildCount(); i++)
      theSizer = SearchSizerInto(obj->GetChild(i));
  }

  return theSizer;
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
    bool created = false;

    // Para que sea m�s pr�ctico, si el objeto no se puede crear debajo
    // del objeto seleccionado vamos a intentarlo en el padre del seleccionado
    // y seguiremos subiendo hasta que ya no podamos crear el objeto.
    while (parent && !created)
    {
      // adem�s, el objeto se insertar� a continuaci�n del objeto seleccionado
      obj = m_objDb->CreateObject(string(name.mb_str()),parent);

      if (obj)
      {
        int pos = CalcPositionOfInsertion(GetSelectedObject(),parent);

        PCommand command(new InsertObjectCmd(this,obj,parent,pos));
        Execute(command); //m_cmdProc.Execute(command);
        created = true;
        ResolveNameConflict(obj);
      }
      else
      {
        // lo vamos a seguir intentando con el padre, pero cuidado, el padre
        // no puede ser un item!
        parent = parent->GetParent();
        while (parent && parent->GetObjectInfo()->GetObjectType()->IsItem())
          parent = parent->GetParent();
      }
    }
  }

  DataObservable::NotifyObjectCreated(obj);

  // Seleccionamos el objeto, si este es un item entonces se selecciona
  // el objeto contenido. �Tiene sentido tener un item debajo de un item?
  while (obj && obj->GetObjectInfo()->GetObjectType()->IsItem())
    obj = ( obj->GetChildCount() > 0 ? obj->GetChild(0) : PObjectBase());

  if (obj)
    SelectObject(obj);
}

void ApplicationData::RemoveObject(PObjectBase obj)
{
  DoRemoveObject(obj,false);
}

void ApplicationData::CutObject(PObjectBase obj)
{
  DoRemoveObject(obj,true);
}

void ApplicationData::DoRemoveObject(PObjectBase obj, bool cutObject)
{
  // Nota:
  //  cuando se va a eliminar un objeto es importante que no se dejen
  //  nodos ficticios ("items") en las hojas del �rbol.
  PObjectBase parent = obj->GetParent();
  if (parent)
  {
    while (parent && parent->GetObjectInfo()->GetObjectType()->IsItem())
    {
      obj = parent;
      parent = obj->GetParent();
    }

    if (cutObject)
    {
      m_copyOnPaste = false;
      PCommand command(new CutObjectCmd(this, obj));
      Execute(command); //m_cmdProc.Execute(command);
    }
    else
    {
      PCommand command(new RemoveObjectCmd(this,obj));
      Execute(command); //m_cmdProc.Execute(command);
    }

    DataObservable::NotifyObjectRemoved(obj);

    // "parent" ser� el nuevo objeto seleccionado tras eliminar obj.
    SelectObject(parent);
  }
  else
  {
    if (obj->GetObjectTypeName()!="project")
      assert(false);
  }

  CheckProjectTree(m_project);
}

void ApplicationData::CopyObject(PObjectBase obj)
{
  m_copyOnPaste = true;

  // Hacemos una primera copia del objeto, ya que si despues de copiar
  // el objeto se modificasen las propiedades, dichas modificaciones se verian
  // reflejadas en la copia.
  m_clipboard = m_objDb->CopyObject(obj);

  CheckProjectTree(m_project);
}

void ApplicationData::PasteObject(PObjectBase parent)
{
  if (m_clipboard)
  {
    // Vamos a hacer un peque�o truco, intentaremos crear un objeto nuevo
    // del mismo tipo que el guardado en m_clipboard debajo de parent.
    // El objeto devuelto quiz� no sea de la misma clase que m_clipboard debido
    // a que est� incluido dentro de un "item".
    // Por tanto, si el objeto devuelto es no-nulo, entonces vamos a descender
    // en el arbol hasta que el objeto sea de la misma clase que m_clipboard,
    // momento en que cambiaremos dicho objeto por m_clipboard.
    //
    // Ejemplo:
    //
    //  m_clipboard :: wxButton
    //  parent      :: wxBoxSizer
    //
    //  obj = CreateObject(m_clipboard->GetObjectInfo()->GetClassName(), parent)
    //
    //  obj :: sizeritem
    //              /
    //           wxButton   <- Cambiamos este por m_clipboard
    PObjectBase old_parent = parent;

    PObjectBase obj =
      m_objDb->CreateObject(m_clipboard->GetObjectInfo()->GetClassName(), parent);

    int pos = -1;

    if (!obj)
    {
      // si no se ha podido crear el objeto vamos a intentar crearlo colgado
      // del padre de "parent" y adem�s vamos a insertarlo en la posici�n
      // siguiente a "parent"
      PObjectBase selected = parent;
      parent = selected->GetParent();
      while (parent && parent->GetObjectInfo()->GetObjectType()->IsItem())
      {
        selected = parent;
        parent = selected->GetParent();
      }

      if (parent)
      {
        obj = m_objDb->CreateObject(m_clipboard->GetObjectInfo()->GetClassName(), parent);

        if (obj)
          pos = CalcPositionOfInsertion(selected,parent);
      }
    }

    if (obj)
    {
      PObjectBase clipboard(m_clipboard);
      if (m_copyOnPaste)
        clipboard = m_objDb->CopyObject(m_clipboard);

      PObjectBase aux = obj;
      while (aux && aux->GetObjectInfo() != clipboard->GetObjectInfo())
        aux = ( aux->GetChildCount() > 0 ? aux->GetChild(0) : PObjectBase());

      if (aux && aux != obj)
      {
        // sustituimos aux por clipboard
        PObjectBase auxParent = aux->GetParent();
        auxParent->RemoveChild(aux);
        aux->SetParent(PObjectBase());

        auxParent->AddChild(clipboard);
        clipboard->SetParent(auxParent);
      }
      else
        obj = clipboard;

      // y finalmente insertamos en el arbol
      PCommand command(new InsertObjectCmd(this,obj,parent,pos));
      Execute(command); //m_cmdProc.Execute(command);

      if (!m_copyOnPaste)
        m_clipboard.reset();

      ResolveSubtreeNameConflicts(obj);

      DataObservable::NotifyProjectRefresh();

      // vamos a mantener seleccionado el nuevo objeto creado
      // pero hay que tener en cuenta que es muy probable que el objeto creado
      // sea un "item"
      while (obj && obj->GetObjectInfo()->GetObjectType()->IsItem())
      {
        assert(obj->GetChildCount() > 0);
        obj = obj->GetChild(0);
      }

      SelectObject(obj);
    }
  }

  CheckProjectTree(m_project);
}

void ApplicationData::InsertObject(PObjectBase obj, PObjectBase parent)
{
  // FIXME! comprobar obj se puede colgar de parent
//  if (parent->GetObjectInfo()->GetObjectType()->FindChildType(
//    obj->GetObjectInfo()->GetObjectType()))
//  {
    PCommand command(new InsertObjectCmd(this,obj,parent));
    Execute(command); //m_cmdProc.Execute(command);
    DataObservable::NotifyProjectRefresh();
//  }
}

void ApplicationData::MergeProject(PObjectBase project)
{
  // FIXME! comprobar obj se puede colgar de parent
  for (unsigned int i=0; i<project->GetChildCount(); i++)
  {
    //m_project->AddChild(project->GetChild(i));
    //project->GetChild(i)->SetParent(m_project);

    PObjectBase child = project->GetChild(i);
    RemoveEmptyItems(child);

    InsertObject(child,m_project);
  }
  DataObservable::NotifyProjectRefresh();
}

void ApplicationData::ModifyProperty(PProperty prop, wxString str)
{
  PObjectBase object = prop->GetObject();

  if (_STDSTR(str) != prop->GetValue())
  {
    PCommand command(new ModifyPropertyCmd(prop,_STDSTR(str)));
    Execute(command); //m_cmdProc.Execute(command);

    DataObservable::NotifyPropertyModified(prop);
  }
}

void ApplicationData::SaveProject(const wxString &filename)
{
  TiXmlDocument *doc = m_project->Serialize();
  m_modFlag = false;
  doc->SaveFile(filename.mb_str());
  m_projectFile = _STDSTR(filename);
  GlobalData()->SetProjectPath(::wxPathOnly(filename));
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
    if (proj && proj->GetObjectTypeName()== "project")
    {
      PObjectBase old_proj = m_project;
      //m_project = shared_dynamic_cast<ProjectObject>(proj);
      m_project = proj;
      m_selObj = m_project;
      result = true;
      m_modFlag = false;
      m_cmdProc.Reset();
      m_projectFile = _STDSTR(file);
      GlobalData()->SetProjectPath(::wxPathOnly(file));
      DataObservable::NotifyProjectLoaded();
      DataObservable::NotifyProjectRefresh();
    }
  }
  delete doc;

  return result;
}

void ApplicationData::NewProject()
{
  m_project = m_objDb->CreateObject("Project");
  m_selObj = m_project;
  m_modFlag = false;
  m_cmdProc.Reset();
  m_projectFile = "";
  GlobalData()->SetProjectPath(wxT(""));
  DataObservable::NotifyProjectRefresh();
}

void ApplicationData::GenerateCode()
{
  DataObservable::NotifyCodeGeneration();
}

void ApplicationData::MovePosition(PObjectBase obj, bool right, unsigned int num)
{
  PObjectBase noItemObj = obj;

  PObjectBase parent = obj->GetParent();
  if (parent)
  {
    // Si el objeto est� incluido dentro de un item hay que desplazar
    // el item
    while (parent && parent->GetObjectInfo()->GetObjectType()->IsItem())
    {
      obj = parent;
      parent = obj->GetParent();
    }

    unsigned int pos = parent->GetChildPosition(obj);

    // nos aseguramos de que los l�mites son correctos

    unsigned int children_count = parent->GetChildCount();

    if ((right && num + pos < children_count) ||
        !right  && (num <= pos))
    {
      pos = (right ? pos+num : pos-num);

      PCommand command(new ShiftChildCmd(obj,pos));
      Execute(command); //m_cmdProc.Execute(command);
      DataObservable::NotifyProjectRefresh();
      SelectObject(noItemObj);

    }
  }
}

void ApplicationData::MoveHierarchy(PObjectBase obj, bool up)
{
  PObjectBase sizeritem = obj->GetParent();

  // object must be inside a sizer
  if (sizeritem && sizeritem->GetObjectTypeName() == "sizeritem")
  {
    PObjectBase nextSizer = sizeritem->GetParent(); // points to the object's sizer
    if (nextSizer)
    {
      if (up)
      {
        do
          nextSizer = nextSizer->GetParent();
        while (nextSizer && nextSizer->GetObjectTypeName() != "sizer");

        if (nextSizer && nextSizer->GetObjectTypeName() == "sizer")
        {
          PCommand cmdReparent(new ReparentObjectCmd(sizeritem,nextSizer));
			    Execute(cmdReparent);
			    DataObservable::NotifyProjectRefresh();
			    SelectObject(obj);
        }
      }
      else
      {
        // object will be move to the top sizer of the next sibling object
        // subtree.
        unsigned int pos = nextSizer->GetChildPosition(sizeritem) + 1;

        if (pos < nextSizer->GetChildCount())
        {
          nextSizer = SearchSizerInto(nextSizer->GetChild(pos));
          if (nextSizer)
          {
            PCommand cmdReparent(new ReparentObjectCmd(sizeritem,nextSizer));
	  		    Execute(cmdReparent);
  			    DataObservable::NotifyProjectRefresh();
  			    SelectObject(obj);
          }
        }
      }
    }
  }
}


void ApplicationData::Undo()
{
  m_cmdProc.Undo();
  DataObservable::NotifyProjectRefresh();
  CheckProjectTree(m_project);
  DataObservable::NotifyObjectSelected(GetSelectedObject());
}

void ApplicationData::Redo()
{
  m_cmdProc.Redo();
  DataObservable::NotifyProjectRefresh();
  CheckProjectTree(m_project);
  DataObservable::NotifyObjectSelected(GetSelectedObject());
}


void ApplicationData::ToggleExpandLayout(PObjectBase obj)
{
  if (obj)
  {
    PObjectBase parent = obj->GetParent();
    if (parent && parent->GetObjectTypeName() == "sizeritem")
    {
      PProperty propFlag = parent->GetProperty("flag");
      assert(propFlag);

      wxString value;
      wxString currentValue = propFlag->GetValueAsString();

      value =
        (TypeConv::FlagSet(wxT("wxEXPAND"),currentValue) ?
         TypeConv::ClearFlag(wxT("wxEXPAND"),currentValue) :
         TypeConv::SetFlag(wxT("wxEXPAND"),currentValue));

      ModifyProperty(propFlag,value);
    }
  }
}

void ApplicationData::ToggleStretchLayout(PObjectBase obj)
{
  if (obj)
  {
    PObjectBase parent = obj->GetParent();
    if (parent && parent->GetObjectTypeName() == "sizeritem")
    {
      PProperty propOption = parent->GetProperty("option");
      assert(propOption);

      string value = ( propOption->GetValue() == "1" ? "0" : "1");

      ModifyProperty(propOption, _WXSTR(value));
    }
  }
}

void ApplicationData::CheckProjectTree(PObjectBase obj)
{
  assert(obj);
  for (unsigned int i=0; i< obj->GetChildCount(); i++)
  {
    PObjectBase child = obj->GetChild(i);
    if (child->GetParent() != obj)
      wxLogError(wxString::Format(wxT("Parent of object \'%s\' is wrong!"),child->GetPropertyAsString(wxT("name")).c_str()));

    CheckProjectTree(child);
  }
}

bool ApplicationData::GetLayoutSettings(PObjectBase obj, int *flag, int *option,int *border)
{
  if (obj)
  {
    PObjectBase parent = obj->GetParent();
    if (parent && parent->GetObjectTypeName() == "sizeritem")
    {
      PProperty propOption = parent->GetProperty("option");
      PProperty propFlag   = parent->GetProperty("flag");
      PProperty propBorder = parent->GetProperty("border");
      assert(propOption && propFlag && propBorder);

      *option = propOption->GetValueAsInteger();
      *flag   = propFlag->GetValueAsInteger();
      *border = propBorder->GetValueAsInteger();

      return true;
    }
  }
  return false;
}

void ApplicationData::ChangeAlignment (PObjectBase obj, int align, bool vertical)
{
  if (obj)
  {
    PObjectBase parent = obj->GetParent();
    if (parent && parent->GetObjectTypeName() == "sizeritem")
    {
      PProperty propFlag = parent->GetProperty("flag");
      assert(propFlag);

      wxString value = propFlag->GetValueAsString();

      // Primero borramos los flags de la configuraci�n previa, para as�
      // evitar conflictos de alineaciones.
      if (vertical)
      {
        value = TypeConv::ClearFlag(wxT("wxALIGN_TOP"), value);
        value = TypeConv::ClearFlag(wxT("wxALIGN_BOTTOM"), value);
        value = TypeConv::ClearFlag(wxT("wxALIGN_CENTER_VERTICAL"), value);
      }
      else
      {
        value = TypeConv::ClearFlag(wxT("wxALIGN_LEFT"), value);
        value = TypeConv::ClearFlag(wxT("wxALIGN_RIGHT"), value);
        value = TypeConv::ClearFlag(wxT("wxALIGN_CENTER_HORIZONTAL"), value);
      }

      wxString alignStr;
      switch (align)
      {
        case wxALIGN_RIGHT:
          alignStr = wxT("wxALIGN_RIGHT");
          break;
        case wxALIGN_CENTER_HORIZONTAL:
          alignStr = wxT("wxALIGN_CENTER_HORIZONTAL");
          break;
        case wxALIGN_BOTTOM:
          alignStr = wxT("wxALIGN_BOTTOM");
          break;
        case wxALIGN_CENTER_VERTICAL:
          alignStr = wxT("wxALIGN_CENTER_VERTICAL");
          break;
      }

      value = TypeConv::SetFlag(alignStr, value);
      ModifyProperty(propFlag,value);
    }
  }
}

void ApplicationData::ToggleBorderFlag(PObjectBase obj, int border)
{
  if (obj)
  {
    PObjectBase parent = obj->GetParent();
    if (parent && parent->GetObjectTypeName() == "sizeritem")
    {
      PProperty propFlag = parent->GetProperty("flag");
      assert(propFlag);

      wxString value = propFlag->GetValueAsString();

      value = TypeConv::ClearFlag(wxT("wxALL"), value);
      value = TypeConv::ClearFlag(wxT("wxTOP"), value);
      value = TypeConv::ClearFlag(wxT("wxBOTTOM"), value);
      value = TypeConv::ClearFlag(wxT("wxRIGHT"), value);
      value = TypeConv::ClearFlag(wxT("wxLEFT"), value);

      int intVal = propFlag->GetValueAsInteger();
      intVal ^= border;

      if ((intVal & wxALL) == wxALL)
        value = TypeConv::SetFlag(wxT("wxALL"), value);
      else
      {
        if ((intVal & wxTOP) != 0) value = TypeConv::SetFlag(wxT("wxTOP"), value);
        if ((intVal & wxBOTTOM) != 0) value = TypeConv::SetFlag(wxT("wxBOTTOM"), value);
        if ((intVal & wxRIGHT) != 0) value = TypeConv::SetFlag(wxT("wxRIGHT"), value);
        if ((intVal & wxLEFT) != 0) value = TypeConv::SetFlag(wxT("wxLEFT"), value);
      }

      ModifyProperty(propFlag, value);
    }
  }
}

void ApplicationData::CreateBoxSizerWithObject(PObjectBase obj)
{
	PObjectBase sizer, sizeritem;

	sizeritem = obj->GetParent();
	if (sizeritem && sizeritem->GetObjectTypeName()=="sizeritem")
	{
		sizer = sizeritem->GetParent();
		unsigned int childPos = sizer->GetChildPosition(sizeritem);

		// creamos un wxBoxSizer
		PObjectBase newSizer = m_objDb->CreateObject("wxBoxSizer",sizer);
		if (newSizer)
		{
			PCommand cmd(new InsertObjectCmd(this,newSizer,sizer,childPos));
			Execute(cmd);

      if (newSizer->GetObjectTypeName() == "sizeritem")
			  newSizer = newSizer->GetChild(0);

			PCommand cmdReparent(new ReparentObjectCmd(sizeritem,newSizer));
			Execute(cmdReparent);
			DataObservable::NotifyProjectRefresh();
		}
	}
}

bool ApplicationData::CanPasteObject()
{
  PObjectBase obj = GetSelectedObject();
  if (obj && obj->GetObjectTypeName() != "project")
    return (m_clipboard != NULL);

  return false;
}

bool ApplicationData::CanCopyObject()
{
  PObjectBase obj = GetSelectedObject();
  if (obj && obj->GetObjectTypeName() != "project")
    return true;

  return false;
}

bool ApplicationData::IsModified()
{
  return m_modFlag;
}

void ApplicationData::Execute(PCommand cmd)
{
  m_modFlag = true;
  m_cmdProc.Execute(cmd);
}

//////////////////////////////////////////////////////////////////////////////
