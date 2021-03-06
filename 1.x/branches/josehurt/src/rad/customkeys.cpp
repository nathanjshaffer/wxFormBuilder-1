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

#include "customkeys.h"
#include "utils/debug.h"
#include "codegen/cppcg.h"


BEGIN_EVENT_TABLE(CustomKeysEvtHandler,wxEvtHandler)
  EVT_CHAR(CustomKeysEvtHandler::OnKeyPress)
END_EVENT_TABLE()

void CustomKeysEvtHandler::OnKeyPress(wxKeyEvent &event)
{
  Debug::Print("%d",event.GetKeyCode());
  
  if (event.GetKeyCode() == WXK_DELETE)
    m_data->RemoveObject(m_data->GetSelectedObject());
  else if (event.GetKeyCode() == 'P')
  {
    /////
    // prueba del parser
    /////
    
    Debug::Print("#### Prueba del parser ####");
    
    PObjectBase obj = m_data->GetSelectedObject();
    PCodeInfo code_info = obj->GetObjectInfo()->GetCodeInfo("C++");
  
    Debug::Print("#### Plantillas ####");
    Debug::Print((char *)(code_info->GetTemplate("construction").c_str()));
    Debug::Print((char *)(code_info->GetTemplate("declaration").c_str()));  
  
    Debug::Print("#### C�digo ####");
    {
      CppTemplateParser parser(obj,code_info->GetTemplate("construction"));
      Debug::Print((char *)parser.ParseTemplate().c_str());
    }
    {
      CppTemplateParser parser(obj,code_info->GetTemplate("declaration"));
      Debug::Print((char *)parser.ParseTemplate().c_str());
    }    
  }
  else if (event.GetKeyCode() == 'C')
  {
    m_data->GenerateCode();
  }
  else
    event.Skip();
}

