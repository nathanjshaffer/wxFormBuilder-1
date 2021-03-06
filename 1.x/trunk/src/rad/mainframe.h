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

#ifndef __MAIN_FRAME__
#define __MAIN_FRAME__

#include "wx/wx.h"
#include "palette.h"
#include "inspector/objinspect.h"
#include "objecttree/objecttree.h"
//#include "designpanel.h"
#include "rad/designer/visualeditor.h"
//#include "codeeditor.h"
#include "rad/cpppanel/cpppanel.h"
#include "rad/xrcpanel/xrcpanel.h"
#include "rad/appobserver.h"

class MainFrame : public DataObserver, public wxFrame
{
 private:
  #ifdef __WXFB_DEBUG__
  wxLog * m_old_log;
  wxLogWindow * m_log;
  #endif //__WXFB_DEBUG__

  wxNotebook *m_notebook;
  wxFbPalette *m_palette;
  ObjectTree *m_objTree;
  ObjectInspector *m_objInsp;
  VisualEditor *m_visualEdit;
  CppPanel *m_cpp;
  XrcPanel *m_xrc;

  wxString m_currentDir;

  wxString m_recentProjects[4];

  void UpdateFrame();

  // Actualiza los projectos m�s recientes en el menu
  void UpdateRecentProjects();
  void OnOpenRecent(wxCommandEvent &event);
  void UpdateLayoutTools();

  bool SaveWarning();

  DECLARE_EVENT_TABLE()
 public:
  MainFrame(DataObservable *data,wxWindow *parent, int id = -1);
  ~MainFrame();
  void RestorePosition(const wxString &name);
  void SavePosition(const wxString &name);
  void OnSaveProject(wxCommandEvent &event);
  void OnSaveAsProject(wxCommandEvent &event);
  void OnOpenProject(wxCommandEvent &event);
  void OnNewProject(wxCommandEvent &event);
  void OnGenerateCode(wxCommandEvent &event);
  void OnAbout(wxCommandEvent &event);
  void OnExit(wxCommandEvent &event);
  void OnClose(wxCloseEvent &event);
  void OnImportXrc(wxCommandEvent &event);
  void OnUndo(wxCommandEvent &event);
  void OnRedo(wxCommandEvent &event);
  void OnCopy (wxCommandEvent &event);
  void OnPaste (wxCommandEvent &event);
  void OnCut (wxCommandEvent &event);
  void OnDelete (wxCommandEvent &event);
  void OnToggleExpand (wxCommandEvent &event);
  void OnToggleStretch (wxCommandEvent &event);
  void OnMoveUp (wxCommandEvent &event);
  void OnMoveDown (wxCommandEvent &event);
  void OnMoveLeft (wxCommandEvent &event);
  void OnMoveRight (wxCommandEvent &event);
  void OnChangeAlignment (wxCommandEvent &event);
  void OnChangeBorder(wxCommandEvent& e);

  void ProjectLoaded();
  void ProjectSaved();
  void ObjectSelected(PObjectBase obj);
  void ObjectCreated(PObjectBase obj);
  void ObjectRemoved(PObjectBase obj);
  void PropertyModified(PProperty prop);
  void CodeGeneration();
  void ProjectRefresh();

  void InsertRecentProject(const wxString &file);
};



#endif //__MAIN_FRAME__
