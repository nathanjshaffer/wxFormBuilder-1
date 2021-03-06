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

#include "visualobj.h"
#include "visualeditor.h"

#include "utils/typeconv.h"
#include "utils/debug.h"
#include "rad/genericpanel.h"

using namespace TypeConv;

PVisualObject VisualObject::CreateVisualObject
  (PObjectBase obj, wxWindow *wx_parent)
{
  PVisualObject vobj;
  
  PObjectInfo obj_info = obj->GetObjectInfo();
  string type = obj->GetObjectTypeName();

  // TO-DO: arreglar esto! 
  //
  // El tipo de objeto se deber� indicar en el plugin
  // quiz� sea conveniente dividir la macro COMPONENT("name",component)
  // estas tres:
  //   WINDOW_COMPONENT
  //   SIZER_COMPONENT
  //   ABSTRACT_COMPONENT
  // y que se pueda consultar el tipo.
  
  IComponent *comp = obj->GetObjectInfo()->GetComponent(); 
  
  if (comp)
  {
    int compType = comp->GetComponentType();
    
    switch (compType)
    {
      case COMPONENT_TYPE_WINDOW:
        vobj = PVisualObject(new VisualWindow(obj,wx_parent));
        break;
    
      case COMPONENT_TYPE_SIZER:
        vobj = PVisualObject(new VisualSizer(obj,wx_parent));
        break;
    
      default: // items y forms
        vobj = PVisualObject(new VisualObject(obj));
        break;
    }
  }
  else
  {
    vobj = PVisualObject(new VisualObject(obj));
    wxLogError(_("Component for ") + _WXSTR(obj->GetClassName()) + _("%s not found!"));
  }

  return vobj;
}   

VisualObject::VisualObject(PObjectBase obj) : m_object(obj) {}  

VisualObject::~VisualObject() {}
  
///////////////////////////////////////////////////////////////////////////////
VisualSizer::VisualSizer(PObjectBase obj,wxWindow *parent)
  : VisualObject(obj)
{
  IComponent *comp = obj->GetObjectInfo()->GetComponent();  
  if (comp)
    SetSizer((wxSizer *)(comp->Create(obj.get(),parent)));

  else
    // para que no pete ponemos un sizer por defecto, aunque deber� mostrar algun
    // mensaje de advertencia
    SetSizer(new wxBoxSizer(wxVERTICAL));
}  



///////////////////////////////////////////////////////////////////////////////

VisualWindow::VisualWindow(PObjectBase obj, wxWindow *parent)
  : VisualObject(obj)
{
  IComponent *comp = obj->GetObjectInfo()->GetComponent();
  
  if (comp)
    SetWindow((wxWindow *)(comp->Create(obj.get(),parent)));

  else
    SetWindow(new GenericWindow(parent));
 
  SetupWindow();
}

//void VisualWindow::AddToSizer(wxSizer *sizer, PObjectBase obj)
//{
//  wxWindow *window_obj = GetWindow();
//  sizer->Add(window_obj,
//    obj->GetProperty("option")->GetValueAsInteger(),
//    obj->GetProperty("flag")->GetValueAsInteger(),
//    obj->GetProperty("border")->GetValueAsInteger());
//    
//  Debug::Print("Add window to sizer");
//}


void VisualWindow::SetupWindow()
{
  PObjectBase obj = GetObject();
  
  // todas las propiedades del objeto wxWindow se aplicaran en este
  // procedimiento
  PProperty ppos   = obj->GetProperty("pos");
  PProperty psize  = obj->GetProperty("size");
  PProperty pfont  = obj->GetProperty("font");
  PProperty pfg_colour  = obj->GetProperty("fg");
  PProperty pbg_colour  = obj->GetProperty("bg");
  PProperty penabled = obj->GetProperty("enabled");
  PProperty phidden  = obj->GetProperty("hidden");
  PProperty ptooltip = obj->GetProperty("tooltip");
    
  wxPoint pos;
  wxSize size;
  wxFont font;
  wxColour fg_colour;
  wxColour bg_colour;
  
  if (ppos)
    pos = StringToPoint(_WXSTR(ppos->GetValue()));

  if (psize)
    size = StringToSize(_WXSTR(psize->GetValue()));

  if (pfont)
    font = StringToFont(_WXSTR(pfont->GetValue()));
    
  if (pfg_colour)
    fg_colour = StringToColour(_WXSTR(pfg_colour->GetValue()));

  if (pbg_colour)
    bg_colour = StringToColour(_WXSTR(pbg_colour->GetValue()));


  if (GetWindow())
  {
    GetWindow()->SetSize(pos.x,pos.y,size.GetWidth(), size.GetHeight());

    if (pfont && pfont->GetValue() != "")
      GetWindow()->SetFont(font);
    
    if (pfg_colour && pfg_colour->GetValue() != "")
      GetWindow()->SetForegroundColour(fg_colour);

    if (pbg_colour && pbg_colour->GetValue() != "")
      GetWindow()->SetBackgroundColour(bg_colour);
      
    if (penabled)
      GetWindow()->Enable(penabled->GetValueAsInteger());
      
    if (phidden)
      GetWindow()->Show(!phidden->GetValueAsInteger());
      
    if (ptooltip)
      GetWindow()->SetToolTip(ptooltip->GetValueAsString());
  }
}

///////////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(VObjEvtHandler,wxEvtHandler)
  EVT_LEFT_DOWN(VObjEvtHandler::OnLeftClick)
  EVT_PAINT(VObjEvtHandler::OnPaint)
  EVT_SET_CURSOR(VObjEvtHandler::OnSetCursor)
  EVT_NOTEBOOK_PAGE_CHANGED(-1,VObjEvtHandler::OnNotebookPageChanged)
END_EVENT_TABLE()

VObjEvtHandler::VObjEvtHandler(wxWindow *win, PObjectBase obj, DataObservable *data)
{
  m_window = win;
  m_object = obj;
  m_data = data;
};

void VObjEvtHandler::OnLeftClick(wxMouseEvent &event)
{
  PObjectBase obj = m_object.lock();
    
  if (obj)
  {
    if (m_data->GetSelectedObject() != obj)
      m_data->SelectObject(obj); 
    else
      event.Skip();
  }

   
  //event.Skip();
  m_window->ClientToScreen(&event.m_x, &event.m_y);
  m_window->GetParent()->ScreenToClient(&event.m_x, &event.m_y);
  ::wxPostEvent(m_window->GetParent(), event);
}  


void VObjEvtHandler::OnPaint(wxPaintEvent &event)
{
  PObjectBase wo = shared_dynamic_cast<ObjectBase>(m_object.lock());
  if (wo->IsContainer())
  {
    wxWindow *aux = m_window;
    while (!aux->IsKindOf(CLASSINFO(GridPanel))) aux = aux->GetParent();
    GridPanel *gp = (GridPanel*) aux;
    if (gp->GetActivePanel() == m_window)
    {
      wxPaintDC dc(m_window);
      gp->HighlightSelection(dc);
    }
  }
  event.Skip();  
}

void VObjEvtHandler::OnSetCursor(wxSetCursorEvent &event)
{
  wxCoord x = event.GetX(), y = event.GetY();
  m_window->ClientToScreen(&x, &y);
  m_window->GetParent()->ScreenToClient(&x, &y);
  wxSetCursorEvent sce(x, y);
  ::wxPostEvent(m_window->GetParent(), sce);
}

//////////////////////////////////////
// Object Tree for notebook objects:
//
//  notebook
//      |
//    notebookpage (item)
//          |
//       container
//////////////////////////////////////

void VObjEvtHandler::OnNotebookPageChanged(wxNotebookEvent &event)
{
	PObjectBase obj = m_data->GetSelectedObject();
  if (obj->GetObjectTypeName() == "notebook")
  {
    int selPage = event.GetSelection();
    if (selPage >= 0)
    {
    	for (unsigned int i=0; i<obj->GetChildCount(); i++)
    	{
  	  	PObjectBase child = obj->GetChild(i);
    		PProperty propSelect = child->GetProperty("select");
    		if (propSelect)
  	  	{
  	  		// we can't use DataObservable::ModifyProperty because
  	  		// it will regenerate de gui, so these modifications won't be
  	  		// undoable
  			  if ((int)i == selPage && !propSelect->GetValueAsInteger())
  			    propSelect->SetValue(string("1"));
          else if ((int)i != selPage && propSelect->GetValueAsInteger())
            propSelect->SetValue(string("0"));
  		  }
  	  }
    }
  }
  event.Skip();
}
