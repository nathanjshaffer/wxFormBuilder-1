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

#ifndef __OBJ_INSPECT__
#define __OBJ_INSPECT__

#include "wx/wx.h"
#include "wx/grid.h"
#include <wx/notebook.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/propdev.h>
#include <wx/propgrid/advprops.h>
#include <wx/propgrid/manager.h>

//#include "propeditor.h"
#include "rad/appobserver.h"

// -----------------------------------------------------------------------

WX_PG_DECLARE_VALUE_TYPE_VOIDP(wxPoint)

WX_PG_DECLARE_PROPERTY(wxPointProperty,const wxPoint&,wxPoint(0,0))

// -----------------------------------------------------------------------

WX_PG_DECLARE_VALUE_TYPE_VOIDP(wxSize)

WX_PG_DECLARE_PROPERTY(wxSizeProperty,const wxSize&,wxSize(0,0))

// -----------------------------------------------------------------------

WX_PG_DECLARE_CUSTOM_COLOUR_PROPERTY_USES_WXCOLOUR(fbColourProperty)

// -----------------------------------------------------------------------

WX_PG_DECLARE_PROPERTY_WITH_DECL(wxMyImageFileProperty,const wxString&,wxEmptyString,WXDLLIMPEXP_PG)

// -----------------------------------------------------------------------


class ObjectInspector : public DataObserver, public wxPanel
{
 private:
  typedef map<wxPGProperty*,PProperty> ObjInspectorMap;
  ObjInspectorMap m_propmap;

  PObjectBase m_currentSel;
  wxPropertyGrid *m_pg;
  
  int StringToBits(const wxString& strVal, wxPGConstants& constants);
  void CreateCategory(const wxString& name, PObjectBase obj,
                      PObjectInfo obj_info, PropertyMap &map);
  wxPGProperty* GetProperty(PProperty prop);
  
  void Create(bool force = false);
  
  void OnPropertyGridChange(wxPropertyGridEvent& event);
  
 protected:
   
 public:
  ObjectInspector(wxWindow *parent, int id);

  void ProjectLoaded();
  void ProjectSaved();
  void ObjectSelected(PObjectBase obj);
  void ObjectCreated(PObjectBase obj);
  void ObjectRemoved(PObjectBase obj);
  void ProjectRefresh();
  void PropertyModified(PProperty prop);
  
  DECLARE_EVENT_TABLE()
};

#endif //__OBJ_INSPECT__
