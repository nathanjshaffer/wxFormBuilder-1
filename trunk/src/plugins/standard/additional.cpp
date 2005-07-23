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

#include "plugins/component.h"
#include "plugins/plugin.h"
#include "utils/xrcconv.h"
//#include "icons/unknown.xpm"

#include <wx/calctrl.h>
#include <wx/html/htmlwin.h>
#include <wx/treectrl.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/tglbtn.h>
#include <wx/scrolbar.h>
#include <wx/splitter.h>


///////////////////////////////////////////////////////////////////////////////

class wxCustomSplitterWindow : public wxSplitterWindow
{
 private:
  int m_swCount;
  int m_splitMode;
  int m_sashPos;
  wxWindow * m_subWindows[2];
  
  void Rebuild();
 public:
  wxCustomSplitterWindow(wxWindow* parent, wxWindowID id, const wxPoint& point,
    const wxSize& size, long style);
    
  void CreateSplit(int splitMode, int sashPos);
  
  void AddSubwindow(wxWindow *subw);
};

wxCustomSplitterWindow::wxCustomSplitterWindow (wxWindow* parent, wxWindowID id,
  const wxPoint& point,  const wxSize& size, long style)
  : wxSplitterWindow(parent,id,point,size,style)
{
  m_swCount = 0;
  m_sashPos = 0;
  m_subWindows[0] = new wxPanel(this,-1);
  m_subWindows[1] = new wxPanel(this,-1);
  SetAutoLayout(true);
}

void wxCustomSplitterWindow::CreateSplit(int splitMode, int sashPos)
{
  m_splitMode = splitMode;
  m_sashPos = sashPos;
  Rebuild();
}

void wxCustomSplitterWindow::AddSubwindow(wxWindow *subw)
{ 
  if (m_swCount < 2)
  {
    Unsplit();
    m_subWindows[m_swCount]->Destroy();
    m_subWindows[m_swCount] = subw;
    Rebuild();
    m_swCount++;
  }
}

void wxCustomSplitterWindow::Rebuild()
{
  if (IsSplit())
    Unsplit();
    
  if (m_splitMode == wxSPLIT_VERTICAL)
    SplitVertically(m_subWindows[0],m_subWindows[1],m_sashPos);
  else
    SplitHorizontally(m_subWindows[0],m_subWindows[1],m_sashPos);
}

///////////////////////////////////////////////////////////////////////////////

class CalendarCtrlComponent : public ComponentBase
{
public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxCalendarCtrl((wxWindow *)parent,-1,
      wxDefaultDateTime,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }
};

class HtmlWindowComponent : public ComponentBase
{
public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    wxHtmlWindow *hw = new wxHtmlWindow((wxWindow *)parent,-1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
    
    wxString dummy_page(
      wxT("<b>wxHtmlWindow</b><br />")
      wxT("This is a dummy page.</body></html>"));
      
    hw->SetPage(dummy_page);
    
    return hw;
  }
};

class RadioButtonComponent : public ComponentBase
{
public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxRadioButton((wxWindow *)parent,-1,
      obj->GetPropertyAsString(_("label")),
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }
};

class ToggleButtonComponent : public ComponentBase
{
public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxToggleButton((wxWindow *)parent,-1,
      obj->GetPropertyAsString(_("label")),
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }
};

class TreeCtrlComponent : public ComponentBase
{
public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    wxTreeCtrl *tc = new wxTreeCtrl((wxWindow *)parent,-1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
      
    // dummy nodes
    wxTreeItemId root = tc->AddRoot(wxT("root node"));
    wxTreeItemId node1 = tc->AppendItem(root,wxT("node1"));
    wxTreeItemId node2 = tc->AppendItem(root,wxT("node2"));
    wxTreeItemId node3 = tc->AppendItem(node2,wxT("node3"));
    tc->Expand(root);
    tc->Expand(node1);
    tc->Expand(node2);
    tc->Expand(node3);
    
    return tc;
  }
};

class ScrollBarComponent : public ComponentBase
{
public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxScrollBar((wxWindow *)parent,-1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));    
  }
};

class SpinCtrlComponent : public ComponentBase
{
public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxSpinCtrl((wxWindow *)parent,-1,
      obj->GetPropertyAsString(_("value")),
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")),
      obj->GetPropertyAsInteger(_("min")),
      obj->GetPropertyAsInteger(_("max")),
      obj->GetPropertyAsInteger(_("initial")));
  }
};

class SpinButtonComponent : public ComponentBase
{
public:
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    return new wxSpinButton((wxWindow *)parent,-1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
  }
};

class SplitterWindowComponent : public ComponentBase
{
  wxObject* Create(IObject *obj, wxObject *parent)
  {
    wxCustomSplitterWindow *splitter =
      new wxCustomSplitterWindow((wxWindow *)parent,-1,
      obj->GetPropertyAsPoint(_("pos")),
      obj->GetPropertyAsSize(_("size")),
      obj->GetPropertyAsInteger(_("style")));
    
    splitter->CreateSplit(obj->GetPropertyAsInteger(_("splitmode")),
      obj->GetPropertyAsInteger(_("sashpos")));
      
    return splitter;
  }
};

class SplitterItemComponent : public ComponentBase
{
 public:
  void OnCreated(IObjectView *objview, wxWindow *wxparent, IObjectView *parent,
                 IObjectView *first_child)
  {
    wxCustomSplitterWindow *splitter = (wxCustomSplitterWindow *)parent->Window();
    wxWindow *subwindow = first_child->Window();
    splitter->AddSubwindow(subwindow);
  }
};


///////////////////////////////////////////////////////////////////////////////

BEGIN_LIBRARY()
    
  WINDOW_COMPONENT("wxCalendarCtrl",CalendarCtrlComponent)
  WINDOW_COMPONENT("wxHtmlWindow",HtmlWindowComponent)
  WINDOW_COMPONENT("wxRadioButton",RadioButtonComponent)
  WINDOW_COMPONENT("wxToggleButton",ToggleButtonComponent)
  WINDOW_COMPONENT("wxTreeCtrl",TreeCtrlComponent)
  WINDOW_COMPONENT("wxScrollBar",ScrollBarComponent)
  WINDOW_COMPONENT("wxSpinCtrl",SpinCtrlComponent)
  WINDOW_COMPONENT("wxSpinButton",SpinButtonComponent)
  WINDOW_COMPONENT("wxSplitterWindow",SplitterWindowComponent)
  ABSTRACT_COMPONENT("splitteritem",SplitterItemComponent)

  // wxCalendarCtrl
  MACRO(wxCAL_SUNDAY_FIRST)
  MACRO(wxCAL_MONDAY_FIRST)
  MACRO(wxCAL_SHOW_HOLIDAYS)
  MACRO(wxCAL_NO_YEAR_CHANGE)
  MACRO(wxCAL_NO_MONTH_CHANGE)
  MACRO(wxCAL_SHOW_SURROUNDING_WEEKS)
  MACRO(wxCAL_SEQUENTIAL_MONTH_SELECTION)

  // wxHtmlWindow
  MACRO(wxHW_SCROLLBAR_NEVER)
  MACRO(wxHW_SCROLLBAR_AUTO)
  MACRO(wxHW_NO_SELECTION)
  
  // wxTreeCtrl
  MACRO(wxTR_EDIT_LABELS)
  MACRO(wxTR_NO_BUTTONS)
  MACRO(wxTR_HAS_BUTTONS)
  MACRO(wxTR_TWIST_BUTTONS)
  MACRO(wxTR_NO_LINES)
  MACRO(wxTR_FULL_ROW_HIGHLIGHT)
  MACRO(wxTR_LINES_AT_ROOT)
  MACRO(wxTR_HIDE_ROOT)
  MACRO(wxTR_ROW_LINES)
  MACRO(wxTR_HAS_VARIABLE_ROW_HEIGHT)
  MACRO(wxTR_SINGLE)
  MACRO(wxTR_MULTIPLE)
  MACRO(wxTR_EXTENDED)
  MACRO(wxTR_DEFAULT_STYLE)
  
  // wxRadioButton
  MACRO(wxRB_GROUP)
  MACRO(wxRB_SINGLE)
  MACRO(wxRB_USE_CHECKBOX)

  // wxScrollBar
  MACRO(wxSB_HORIZONTAL)
  MACRO(wxSB_VERTICAL)

  // wxSpinCtrl y wxSpinButton 
  MACRO(wxSP_ARROW_KEYS)
  MACRO(wxSP_WRAP)
  MACRO(wxSP_HORIZONTAL)
  MACRO(wxSP_VERTICAL)
  
  // wxSplitterWindow
  MACRO(wxSP_3D)
  MACRO(wxSP_3DSASH)
  MACRO(wxSP_3DBORDER)
  MACRO(wxSP_BORDER)
  MACRO(wxSP_NOBORDER)
  MACRO(wxSP_NO_XP_THEME)
  MACRO(wxSP_PERMIT_UNSPLIT)
  MACRO(wxSP_LIVE_UPDATE)

  MACRO(wxSPLIT_VERTICAL)
  MACRO(wxSPLIT_HORIZONTAL)
  
END_LIBRARY()

