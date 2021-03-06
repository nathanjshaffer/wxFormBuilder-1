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

#ifndef __WXMSW__
  #include "icons/wxwin16x16.xpm"
#endif //__WXMSW__

#include "mainframe.h"
#include "wx/splitter.h"
#include "wx/config.h"
#include "utils/debug.h"
#include "rad/title.h"
#include "rad/bitmaps.h"
#include "icons/system.xpm"
#include "icons/undo.xpm"
#include "icons/redo.xpm"
#include "icons/copy.xpm"
#include "icons/paste.xpm"
#include "icons/cruz.xpm"
#include "icons/tijeras.xpm"
#include "icons/ralign.xpm"
#include "icons/lalign.xpm"
#include "icons/chalign.xpm"
#include "icons/talign.xpm"
#include "icons/balign.xpm"
#include "icons/cvalign.xpm"
#include "icons/expand.xpm"
#include "icons/stretch.xpm"
#include "icons/top.xpm"
#include "icons/bottom.xpm"
#include "icons/left.xpm"
#include "icons/right.xpm"

#include "model/xrcfilter.h"
#include "rad/about.h"

#define ID_ABOUT         100
#define ID_QUIT          101
#define ID_SAVE_PRJ      102
#define ID_OPEN_PRJ      103
#define ID_NEW_PRJ       104
#define ID_GENERATE_CODE 105
#define ID_IMPORT_XRC    106
#define ID_UNDO          107
#define ID_REDO          108
#define ID_SAVE_AS_PRJ   109
#define ID_CUT           110
#define ID_DELETE        111
#define ID_COPY          112
#define ID_PASTE         113
#define ID_EXPAND        114
#define ID_STRETCH       115
#define ID_MOVE_UP       116
#define ID_MOVE_DOWN     117
#define ID_RECENT_0      118 // Tienen que tener ids consecutivos
#define ID_RECENT_1      119 // ID_RECENT_n+1 == ID_RECENT_n + 1
#define ID_RECENT_2      120 //
#define ID_RECENT_3      121 //
#define ID_RECENT_SEP    122

#define ID_ALIGN_LEFT     123
#define ID_ALIGN_CENTER_H 124
#define ID_ALIGN_RIGHT    125
#define ID_ALIGN_TOP      126
#define ID_ALIGN_CENTER_V 127
#define ID_ALIGN_BOTTOM   128

#define ID_BORDER_LEFT    129
#define ID_BORDER_RIGHT   130
#define ID_BORDER_TOP     131
#define ID_BORDER_BOTTOM  132

#define ID_MOVE_LEFT 133
#define ID_MOVE_RIGHT  134

BEGIN_EVENT_TABLE(MainFrame,wxFrame)
  EVT_MENU(ID_NEW_PRJ,MainFrame::OnNewProject)
  EVT_MENU(ID_SAVE_PRJ,MainFrame::OnSaveProject)
  EVT_MENU(ID_SAVE_AS_PRJ,MainFrame::OnSaveAsProject)
  EVT_MENU(ID_OPEN_PRJ,MainFrame::OnOpenProject)
  EVT_MENU(ID_ABOUT,MainFrame::OnAbout)
  EVT_MENU(ID_QUIT,MainFrame::OnExit)
  EVT_MENU(ID_IMPORT_XRC,MainFrame::OnImportXrc)
  EVT_MENU(ID_GENERATE_CODE,MainFrame::OnGenerateCode)
  EVT_MENU(ID_UNDO,MainFrame::OnUndo)
  EVT_MENU(ID_REDO,MainFrame::OnRedo)
  EVT_MENU(ID_DELETE,MainFrame::OnDelete)
  EVT_MENU(ID_CUT,MainFrame::OnCut)
  EVT_MENU(ID_COPY,MainFrame::OnCopy)
  EVT_MENU(ID_PASTE,MainFrame::OnPaste)
  EVT_MENU(ID_EXPAND,MainFrame::OnToggleExpand)
  EVT_MENU(ID_STRETCH,MainFrame::OnToggleStretch)
  EVT_MENU(ID_MOVE_UP,MainFrame::OnMoveUp)
  EVT_MENU(ID_MOVE_DOWN,MainFrame::OnMoveDown)
  EVT_MENU(ID_MOVE_LEFT,MainFrame::OnMoveLeft)
  EVT_MENU(ID_MOVE_RIGHT,MainFrame::OnMoveRight)
  EVT_MENU(ID_RECENT_0,MainFrame::OnOpenRecent)
  EVT_MENU(ID_RECENT_1,MainFrame::OnOpenRecent)
  EVT_MENU(ID_RECENT_2,MainFrame::OnOpenRecent)
  EVT_MENU(ID_RECENT_3,MainFrame::OnOpenRecent)
  EVT_MENU(ID_ALIGN_RIGHT,MainFrame::OnChangeAlignment)
  EVT_MENU(ID_ALIGN_LEFT,MainFrame::OnChangeAlignment)
  EVT_MENU(ID_ALIGN_CENTER_H,MainFrame::OnChangeAlignment)
  EVT_MENU(ID_ALIGN_TOP,MainFrame::OnChangeAlignment)
  EVT_MENU(ID_ALIGN_BOTTOM,MainFrame::OnChangeAlignment)
  EVT_MENU(ID_ALIGN_CENTER_V,MainFrame::OnChangeAlignment)
  EVT_MENU_RANGE(ID_BORDER_LEFT, ID_BORDER_BOTTOM, MainFrame::OnChangeBorder)
  EVT_CLOSE(MainFrame::OnClose)
END_EVENT_TABLE()

MainFrame::MainFrame(DataObservable *data,wxWindow *parent, int id)
  : wxFrame(parent,id,wxT("wxFormBuilder v.0.1"),wxDefaultPosition,wxSize(1000,800))
{
  #ifdef __WXMSW__
  SetIcon(wxICON(A));
  #else
  SetIcon(wxIcon(wxwin16x16_xpm));
  #endif

  wxString date(wxT(__DATE__));
  wxString time(wxT(__TIME__));
  SetTitle(wxT("wxFormBuilder (Build on ") + date +wxT(" - ")+ time + wxT(")"));

  SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));

  wxMenu *menuFile = new wxMenu;
  menuFile->Append(ID_NEW_PRJ, _T("&New"), _T("create an empty project"));
  menuFile->Append(ID_OPEN_PRJ, _T("&Open...\tF2"), _T("Open a project"));

  menuFile->Append(ID_SAVE_PRJ,          _T("&Save\tCTRL+S"), _T("Save current project"));
  menuFile->Append(ID_SAVE_AS_PRJ, _T("Save &As...\tF3"), _T("Save current project as..."));
  menuFile->AppendSeparator();
  menuFile->Append(ID_IMPORT_XRC, _T("&Import XRC..."), _T("Import XRC file"));
  menuFile->AppendSeparator();
  menuFile->Append(ID_GENERATE_CODE, _T("&Generate Code\tF8"), _T("Generate Code"));
  menuFile->AppendSeparator();
  menuFile->Append(ID_QUIT, _T("E&xit\tAlt-X"), _T("Quit wxFormBuilder"));
  menuFile->AppendSeparator();

  wxMenu *menuEdit = new wxMenu;
  menuEdit->Append(ID_UNDO, _T("&Undo \tCTRL+Z"), _T("Undo changes"));
  menuEdit->Append(ID_REDO, _T("&Redo \tCTRL+Y"), _T("Redo changes"));
  menuEdit->AppendSeparator();
  menuEdit->Append(ID_COPY, _T("&Copy \tCTRL+C"), _T("Copy selected object"));
  menuEdit->Append(ID_CUT, _T("&Cut \tCTRL+X"), _T("Cut selected object"));
  menuEdit->Append(ID_PASTE, _T("&Paste \tCTRL+V"), _T("Paste on selected object"));
  menuEdit->Append(ID_DELETE, _T("&Delete \tCTRL+D"), _T("Delete selected object"));
  menuEdit->AppendSeparator();
  menuEdit->Append(ID_EXPAND, _T("&Toggle Expand\tALT+W"), _T("Toggle wxEXPAND flag of sizeritem properties"));
  menuEdit->Append(ID_STRETCH, _T("&Toggle Stretch\tALT+S"), _T("Toggle option property of sizeritem properties"));
  menuEdit->Append(ID_MOVE_UP, _T("&Move Up\tALT+Up"), _T("Move Up selected object"));
  menuEdit->Append(ID_MOVE_DOWN, _T("&Move Down\tALT+Down"), _T("Move Down selected object"));
  menuEdit->Append(ID_MOVE_LEFT, _T("&Move Left\tALT+Left"), _T("Move Left selected object"));
  menuEdit->Append(ID_MOVE_RIGHT, _T("&Move Right\tALT+Right"), _T("Move Right selected object"));
  menuEdit->AppendSeparator();
  menuEdit->Append(ID_ALIGN_LEFT,     _T("&Align Left"),           _T("Align item to the left"));
  menuEdit->Append(ID_ALIGN_CENTER_H, _T("&Align Center Horizontal"), _T("Align item to the center horizontally"));
  menuEdit->Append(ID_ALIGN_RIGHT,    _T("&Align Right"),         _T("Align item to the right"));
  menuEdit->Append(ID_ALIGN_TOP,      _T("&Align Top"),              _T("Align item to the top"));
  menuEdit->Append(ID_ALIGN_CENTER_H, _T("&Align Center Vertical"),   _T("Align item to the center vertically"));
  menuEdit->Append(ID_ALIGN_BOTTOM,   _T("&Align Bottom"),         _T("Align item to the bottom"));

  wxMenu *menuHelp = new wxMenu;
  menuHelp->Append(ID_ABOUT, _T("&About...\tF1"), _T("Show about dialog"));


  // now append the freshly created menu to the menu bar...
  wxMenuBar *menuBar = new wxMenuBar();
  menuBar->Append(menuFile, _T("&File"));
  menuBar->Append(menuEdit, _T("&Edit"));
  menuBar->Append(menuHelp, _T("&Help"));

  // ... and attach this menu bar to the frame
  SetMenuBar(menuBar);
  wxBoxSizer *top_sizer = new wxBoxSizer(wxVERTICAL);

  ///////////////

  wxSplitterWindow *v_splitter = new wxSplitterWindow(this,-1,wxDefaultPosition,wxDefaultSize, wxSP_3DSASH | wxSP_LIVE_UPDATE);
  wxPanel *left = new wxPanel(v_splitter,-1);//,wxDefaultPosition, wxDefaultSize,wxSIMPLE_BORDER);
  wxBoxSizer *left_sizer = new wxBoxSizer(wxVERTICAL);

  wxPanel *right = new wxPanel(v_splitter,-1);
  v_splitter->SplitVertically(left,right,300);

  wxSplitterWindow *h_splitter = new wxSplitterWindow(left,-1,wxDefaultPosition,wxDefaultSize, wxSP_3D | wxSP_LIVE_UPDATE);//wxSP_BORDER);

  wxPanel *tree_panel = new wxPanel(h_splitter,-1);
  Title *tree_title = new Title(tree_panel,wxT("Object Tree"));

  m_objTree = new ObjectTree(tree_panel,-1);
  data->AddDataObserver(m_objTree);
  m_objTree->SetData(data);
  m_objTree->Create();

  wxBoxSizer *tree_sizer = new wxBoxSizer(wxVERTICAL);
  tree_sizer->Add(tree_title,0,wxEXPAND,0);
  tree_sizer->Add(m_objTree,1,wxEXPAND,0);

  tree_panel->SetSizer(tree_sizer);
  tree_panel->SetAutoLayout(true);

  wxPanel *obj_inspPanel = new wxPanel(h_splitter,-1);
  wxBoxSizer *obj_insp_sizer = new wxBoxSizer(wxVERTICAL);

  Title *obj_insp_title = new Title(obj_inspPanel,wxT("Object Properties"));

  m_objInsp = new ObjectInspector(obj_inspPanel,-1);
  data->AddDataObserver(m_objInsp);

  obj_insp_sizer->Add(obj_insp_title,0,wxEXPAND,0);

  obj_insp_sizer->Add(m_objInsp,1,wxEXPAND,0);

  h_splitter->SplitHorizontally(tree_panel,obj_inspPanel,400);
  obj_inspPanel->SetSizer(obj_insp_sizer);
  obj_inspPanel->SetAutoLayout(true);

  left_sizer->Add(h_splitter,1,wxEXPAND,0);

  left->SetSizer(left_sizer);
  left->SetAutoLayout(true);
  //////////////
  wxBoxSizer *right_sizer = new wxBoxSizer(wxVERTICAL);

  // la paleta de componentes, no es un observador propiamente dicho, ya
  // que no responde ante los eventos de la aplicaci�n
  m_palette = new wxFbPalette(right,-1);
  m_palette->SetData(data);
  m_palette->Create();

  m_notebook = new wxNotebook(right, -1, wxDefaultPosition, wxDefaultSize, wxNB_NOPAGETHEME);

  m_visualEdit = new VisualEditor(m_notebook);
  data->AddDataObserver(m_visualEdit);

  m_notebook->AddPage( m_visualEdit, wxT("Designer") );

  m_cpp = new CppPanel(m_notebook,-1);
  data->AddDataObserver(m_cpp);
  m_notebook->AddPage( m_cpp, wxT("C++") );

  m_xrc = new XrcPanel(m_notebook,-1);
  data->AddDataObserver(m_xrc);
  m_notebook->AddPage(m_xrc, wxT("XRC"));

  Title *ed_title = new Title(right,wxT("Editor"));

  right_sizer->Add(m_palette,0,wxEXPAND,0);
  right_sizer->Add(ed_title,0,wxEXPAND,0);
//  right_sizer->Add(new wxNotebookSizer( m_notebook ),1,wxEXPAND|wxTOP,5);
  right_sizer->Add(m_notebook,1,wxEXPAND|wxTOP,5);
  right->SetSizer(right_sizer);

  top_sizer->Add(v_splitter,1,wxEXPAND,0);

  CreateStatusBar();
  wxToolBar* toolbar = CreateToolBar();
  toolbar->SetToolBitmapSize(wxSize(22, 22));
  toolbar->AddTool(ID_NEW_PRJ,wxT("New Project"),AppBitmaps::GetBitmap(wxT("new")));
  toolbar->AddTool(ID_OPEN_PRJ,wxT("Open Project"),AppBitmaps::GetBitmap(wxT("open")));
  toolbar->AddTool(ID_SAVE_PRJ,wxT("Save Project"),AppBitmaps::GetBitmap(wxT("save")));
  toolbar->AddSeparator();
  toolbar->AddTool(ID_UNDO, _T("Undo"), undo_xpm);
  toolbar->AddTool(ID_REDO, _T("Redo"), redo_xpm);
  toolbar->AddSeparator();
  toolbar->AddTool(ID_CUT, _T("Cut"), tijeras_xpm);
  toolbar->AddTool(ID_COPY, _T("Copy"), copy_xpm);
  toolbar->AddTool(ID_PASTE, _T("Paste"), paste_xpm);
  toolbar->AddTool(ID_DELETE, _T("Delete"), cruz_xpm);
  toolbar->AddSeparator();
  toolbar->AddTool(ID_GENERATE_CODE,wxT("Generate Code"),system_xpm);
  toolbar->AddSeparator();
  toolbar->AddTool(ID_ALIGN_LEFT,wxT(""),lalign_xpm,wxNullBitmap,wxITEM_CHECK);
  toolbar->AddTool(ID_ALIGN_CENTER_H,wxT(""),chalign_xpm,wxNullBitmap,wxITEM_CHECK);
  toolbar->AddTool(ID_ALIGN_RIGHT,wxT(""),ralign_xpm,wxNullBitmap,wxITEM_CHECK);
  toolbar->AddSeparator();
  toolbar->AddTool(ID_ALIGN_TOP,wxT(""),talign_xpm,wxNullBitmap,wxITEM_CHECK);
  toolbar->AddTool(ID_ALIGN_CENTER_V,wxT(""),cvalign_xpm,wxNullBitmap,wxITEM_CHECK);
  toolbar->AddTool(ID_ALIGN_BOTTOM,wxT(""),balign_xpm,wxNullBitmap,wxITEM_CHECK);
  toolbar->AddSeparator();
  toolbar->AddTool(ID_EXPAND,wxT(""),expand_xpm,wxNullBitmap,wxITEM_CHECK);
  toolbar->AddTool(ID_STRETCH,wxT(""),stretch_xpm,wxNullBitmap,wxITEM_CHECK);
  toolbar->AddSeparator();
  toolbar->AddTool(ID_BORDER_LEFT,wxT(""),left_xpm,wxNullBitmap,wxITEM_CHECK);
  toolbar->AddTool(ID_BORDER_RIGHT,wxT(""),right_xpm,wxNullBitmap,wxITEM_CHECK);
  toolbar->AddTool(ID_BORDER_TOP,wxT(""),top_xpm,wxNullBitmap,wxITEM_CHECK);
  toolbar->AddTool(ID_BORDER_BOTTOM,wxT(""),bottom_xpm,wxNullBitmap,wxITEM_CHECK);

  toolbar->Realize();

  SetSizer(top_sizer);
  top_sizer->SetSizeHints(this);
  SetAutoLayout(true);
  Layout();
  Fit();

  //SetSize(wxSize(1000,800));
  RestorePosition(_T("mainframe"));
  //Centre();
  Refresh();

  // a�adimos el manejador de las teclas r�pidas de la aplicaci�n
  // realmente este es el sitio donde hacerlo ?????
  //m_objTree->AddCustomKeysHandler(new CustomKeysEvtHandler(data));
  data->AddDataObserver(this);
};


MainFrame::~MainFrame()
{/*
  #ifdef __WXFB_DEBUG__
  wxLog::SetActiveTarget(m_old_log);
  m_log->GetFrame()->Destroy();
  #endif //__WXFB_DEBUG__
  */

  // Eliminamos los observadores, ya que si quedara alg�n evento por procesar
  // se producir�a un error de acceso no v�lido debido a que los observadores
  // ya estar�an destruidos
  m_objTree->GetData()->RemoveDataObserver(m_objTree);
  m_objInsp->GetData()->RemoveDataObserver(m_objInsp);
  m_visualEdit->GetData()->RemoveDataObserver(m_visualEdit);
}

void MainFrame::RestorePosition(const wxString &name)
{
    bool maximized;
    int x, y, w, h;

    m_currentDir = wxT("./projects");

    wxConfigBase *config = wxConfigBase::Get();
    config->SetPath(name);
    if (config->Read(_T("IsMaximized"), &maximized))
    {
        Maximize(maximized);
    	x = y = w = h = -1;
        config->Read(_T("PosX"), &x);
        config->Read(_T("PosY"), &y);
        config->Read(_T("SizeW"), &w);
        config->Read(_T("SizeH"), &h);
        SetSize(x, y, w, h);
        bool iconized = false;
        config->Read(_T("IsIconized"), &iconized);
        if (iconized) Iconize(iconized);
    }
    config->Read(_T("CurrentDirectory"), &m_currentDir);

    config->Read(_T("RecentFile0"),&m_recentProjects[0]);
    config->Read(_T("RecentFile1"),&m_recentProjects[1]);
    config->Read(_T("RecentFile2"),&m_recentProjects[2]);
    config->Read(_T("RecentFile3"),&m_recentProjects[3]);

    config->SetPath(_T(".."));
    UpdateRecentProjects();
}

void MainFrame::SavePosition(const wxString &name)
{
    wxConfigBase *config = wxConfigBase::Get();
    bool isIconized = IsIconized();
    bool isMaximized = IsMaximized();

    config->SetPath(name);
    if (!isMaximized)
    {
        config->Write(_T("PosX"), isIconized ? -1 : GetPosition().x);
        config->Write(_T("PosY"), isIconized ? -1 : GetPosition().y);
        config->Write(_T("SizeW"), isIconized ? -1 : GetSize().GetWidth());
        config->Write(_T("SizeH"), isIconized ? -1 : GetSize().GetHeight());
    }
    config->Write(_T("IsMaximized"), isMaximized);
    config->Write(_T("IsIconized"), isIconized);
    config->Write(_T("CurrentDirectory"), m_currentDir);

    config->Write(_T("RecentFile0"),m_recentProjects[0]);
    config->Write(_T("RecentFile1"),m_recentProjects[1]);
    config->Write(_T("RecentFile2"),m_recentProjects[2]);
    config->Write(_T("RecentFile3"),m_recentProjects[3]);

    config->SetPath(_T(".."));
}

void MainFrame::OnSaveProject(wxCommandEvent &event)
{
  wxString filename = _WXSTR(GetData()->GetProjectFileName());
  if (filename == wxT(""))
    OnSaveAsProject(event);
  else
  {
    GetData()->SaveProject(filename);
    InsertRecentProject(filename);
  }
}


void MainFrame::OnSaveAsProject(wxCommandEvent &event)
{
  wxFileDialog *dialog = new wxFileDialog(this,wxT("Open Project"),m_currentDir,
    wxT(""),wxT("wxFormBuilder Project File (*.fbp)|*.fbp|All files (*.*)|*.*"),wxSAVE);

  if (dialog->ShowModal() == wxID_OK)
  {
    m_currentDir = dialog->GetDirectory();
    wxString filename = dialog->GetPath();
    GetData()->SaveProject(filename); // FIXME: debe devolver bool.
    InsertRecentProject(filename);
  };

  dialog->Destroy();
}

void MainFrame::OnOpenProject(wxCommandEvent &event)
{
  if (!SaveWarning())
    return;

  wxFileDialog *dialog = new wxFileDialog(this,wxT("Open Project"),m_currentDir,
    wxT(""),wxT("wxFormBuilder Project File (*.fbp)|*.fbp|All files (*.*)|*.*"),wxOPEN | wxHIDE_READONLY);

  if (dialog->ShowModal() == wxID_OK)
  {
    m_currentDir = dialog->GetDirectory();
    wxString filename = dialog->GetPath();
    if (GetData()->LoadProject(filename))
      InsertRecentProject(filename);
  };

  dialog->Destroy();
}

void MainFrame::OnOpenRecent(wxCommandEvent &event)
{
  if (!SaveWarning())
    return;

  int i = event.GetId() - ID_RECENT_0;
  assert (i >= 0 && i < 4);

  wxString filename = m_recentProjects[i];
  if (GetData()->LoadProject(filename))
    InsertRecentProject(filename);
}

void MainFrame::OnImportXrc(wxCommandEvent &event)
{
  wxFileDialog *dialog = new wxFileDialog(this,wxT("Import XRC file"),m_currentDir,
  wxT("example.xrc"),wxT("*.xrc"),wxOPEN | wxHIDE_READONLY);

  if (dialog->ShowModal() == wxID_OK)
  {
    m_currentDir = dialog->GetDirectory();
    TiXmlDocument doc(_STDSTR(dialog->GetPath()));
    if (doc.LoadFile())
    {
      XrcLoader xrc;
      xrc.SetObjectDatabase(GetData()->GetObjectDatabase());
      PObjectBase project = xrc.GetProject(&doc);
      if (project)
      {
        GetData()->MergeProject(project);
      }
      else
        wxLogMessage(wxT("Error al importar XRC"));
    }
    else
      wxLogMessage(wxT("Error al cargar archivo XRC"));
  }

  dialog->Destroy();
}


void MainFrame::OnNewProject(wxCommandEvent &event)
{
  if (!SaveWarning())
    return;

  GetData()->NewProject();
}

void MainFrame::OnGenerateCode(wxCommandEvent &event)
{
  GetData()->GenerateCode();
}

void MainFrame::OnAbout(wxCommandEvent &event)
{
  AboutDialog *dlg = new AboutDialog(this);
  dlg->ShowModal();
  dlg->Destroy();

  /*
  wxMessageBox(
    wxT("wxFormBuilder v.0.1\n"
        "wxFormBuilder is a visual dialog editor with\n"
        "code generation for wxWidgets Framework\n"
        "(C) 2005 - Jos� Antonio Hurtado"),
    wxT("About of wxFormBuilder..."),wxOK);*/
}

void MainFrame::OnExit(wxCommandEvent &event)
{
  if (!SaveWarning())
    return;

  Close();
}

void MainFrame::OnClose(wxCloseEvent &event)
{
  if (!SaveWarning())
    return;

  SavePosition(_T("mainframe"));
  event.Skip();
}

void MainFrame::ProjectLoaded()
{
  GetStatusBar()->SetStatusText(wxT("Project Loaded!"));
  UpdateFrame();
}
void MainFrame::ProjectSaved()
{
  GetStatusBar()->SetStatusText(wxT("Project Saved!"));
  UpdateFrame();
}
void MainFrame::ObjectSelected(PObjectBase obj)
{
  wxString name;
  PProperty prop(obj->GetProperty("name"));

  if (prop)
    name = prop->GetValueAsString();
  else

    name = wxT("\"Unknown\"");

  GetStatusBar()->SetStatusText(wxT("Object ") + name + wxT(" Selected!"));
  UpdateFrame();
}

void MainFrame::ObjectCreated(PObjectBase obj)
{
  GetStatusBar()->SetStatusText(wxT("Object Created!"));
  UpdateFrame();
}

void MainFrame::ObjectRemoved(PObjectBase obj)
{
  GetStatusBar()->SetStatusText(wxT("Object Removed!"));
  UpdateFrame();
}

void MainFrame::PropertyModified(PProperty prop)
{
  GetStatusBar()->SetStatusText(wxT("Property Modified!"));
  UpdateFrame();
}

void MainFrame::CodeGeneration()
{
  GetStatusBar()->SetStatusText(wxT("Code Generated!"));
}

void MainFrame::OnUndo(wxCommandEvent &event)
{
  GetData()->Undo();
}
void MainFrame::OnRedo(wxCommandEvent &event)
{
  GetData()->Redo();
}

void MainFrame::ProjectRefresh()
{
  UpdateFrame();
}

void MainFrame::UpdateLayoutTools()
{
  int option, border, flag;
  if (GetData()->GetLayoutSettings(GetData()->GetSelectedObject(),&flag,&option,&border))
  {
    // Activamos todas las herramientas de layout
    GetToolBar()->EnableTool(ID_EXPAND,true);
    GetToolBar()->EnableTool(ID_STRETCH,true);
    GetToolBar()->EnableTool(ID_ALIGN_LEFT,true);
    GetToolBar()->EnableTool(ID_ALIGN_CENTER_H,true);
    GetToolBar()->EnableTool(ID_ALIGN_RIGHT,true);
    GetToolBar()->EnableTool(ID_ALIGN_TOP,true);
    GetToolBar()->EnableTool(ID_ALIGN_CENTER_V,true);
    GetToolBar()->EnableTool(ID_ALIGN_BOTTOM,true);

    GetToolBar()->EnableTool(ID_BORDER_TOP, true);
    GetToolBar()->EnableTool(ID_BORDER_RIGHT, true);
    GetToolBar()->EnableTool(ID_BORDER_LEFT, true);
    GetToolBar()->EnableTool(ID_BORDER_BOTTOM, true);

    // Colocamos la posici�n de los botones
    GetToolBar()->ToggleTool(ID_EXPAND,         flag & wxEXPAND);
    GetToolBar()->ToggleTool(ID_STRETCH,        option > 0);
    GetToolBar()->ToggleTool(ID_ALIGN_LEFT,     !(flag & (wxALIGN_RIGHT | wxALIGN_CENTER_HORIZONTAL)));
    GetToolBar()->ToggleTool(ID_ALIGN_CENTER_H, flag & wxALIGN_CENTER_HORIZONTAL);
    GetToolBar()->ToggleTool(ID_ALIGN_RIGHT,    flag & wxALIGN_RIGHT);
    GetToolBar()->ToggleTool(ID_ALIGN_TOP,      !(flag & (wxALIGN_BOTTOM | wxALIGN_CENTER_VERTICAL)));
    GetToolBar()->ToggleTool(ID_ALIGN_CENTER_V, flag & wxALIGN_CENTER_VERTICAL);
    GetToolBar()->ToggleTool(ID_ALIGN_BOTTOM,   flag & wxALIGN_BOTTOM);

    GetToolBar()->ToggleTool(ID_BORDER_TOP,      flag & wxTOP);
    GetToolBar()->ToggleTool(ID_BORDER_RIGHT,    flag & wxRIGHT);
    GetToolBar()->ToggleTool(ID_BORDER_LEFT,     flag & wxLEFT);
    GetToolBar()->ToggleTool(ID_BORDER_BOTTOM,   flag & wxBOTTOM);
  }
  else
  {
    // Desactivamos todas las herramientas de layout
    GetToolBar()->EnableTool(ID_EXPAND,false);
    GetToolBar()->EnableTool(ID_STRETCH,false);
    GetToolBar()->EnableTool(ID_ALIGN_LEFT,false);
    GetToolBar()->EnableTool(ID_ALIGN_CENTER_H,false);
    GetToolBar()->EnableTool(ID_ALIGN_RIGHT,false);
    GetToolBar()->EnableTool(ID_ALIGN_TOP,false);
    GetToolBar()->EnableTool(ID_ALIGN_CENTER_V,false);
    GetToolBar()->EnableTool(ID_ALIGN_BOTTOM,false);

    GetToolBar()->EnableTool(ID_BORDER_TOP, false);
    GetToolBar()->EnableTool(ID_BORDER_RIGHT, false);
    GetToolBar()->EnableTool(ID_BORDER_LEFT, false);
    GetToolBar()->EnableTool(ID_BORDER_BOTTOM, false);
  }
}

void MainFrame::UpdateFrame()
{
  // Actualizamos el t�tulo
  wxString date(wxT(__DATE__));
  wxString time(wxT(__TIME__));
  wxString title(wxT("wxFormBuilder (Build on ") + date +wxT(" - ")+ time + wxT(") - "));

  if (GetData()->IsModified())
    title = title + wxChar('*');

   wxString filename = _WXSTR(GetData()->GetProjectFileName());

   title = title + ( filename.IsEmpty() ?
                      wxT("[untitled]") :
                      wxT("[") + filename + wxT("]"));

  SetTitle(title);

  // Actualizamos los menus
  wxMenu *menuEdit = GetMenuBar()->GetMenu(GetMenuBar()->FindMenu(_("Edit")));

  menuEdit->Enable(ID_REDO,GetData()->CanRedo());
  menuEdit->Enable(ID_UNDO,GetData()->CanUndo());

  // Actualizamos la barra de herramientas
  GetToolBar()->EnableTool(ID_REDO,GetData()->CanRedo());
  GetToolBar()->EnableTool(ID_UNDO,GetData()->CanUndo());
  GetToolBar()->EnableTool(ID_COPY,GetData()->CanCopyObject());
  GetToolBar()->EnableTool(ID_CUT,GetData()->CanCopyObject());
  GetToolBar()->EnableTool(ID_DELETE,GetData()->CanCopyObject());
  GetToolBar()->EnableTool(ID_PASTE,GetData()->CanPasteObject());

  UpdateLayoutTools();


  // Actualizamos la barra de estado
  // TO-DO: definir un campo...
}

void MainFrame::UpdateRecentProjects()
{
  int i;
  wxMenu *menuFile = GetMenuBar()->GetMenu(GetMenuBar()->FindMenu(_("File")));

  // borramos los items del menu de los projectos recientes
  for (i = 0 ; i < 4 ; i++)
  {
    if (menuFile->FindItem(ID_RECENT_0 + i))
      menuFile->Destroy(ID_RECENT_0 + i);
  }

  // creamos los nuevos ficheros recientes
  for (unsigned int i = 0 ; i < 4 && !m_recentProjects[i].IsEmpty() ; i++)
    menuFile->Append(ID_RECENT_0+i, m_recentProjects[i], wxT(""));
}

void MainFrame::InsertRecentProject(const wxString &file)
{
  bool found;
  int i;

  for (i = 0; i < 4 && !found; i++)
    found = (file == m_recentProjects[i]);

  if (found) // en i-1 est� la posici�n encontrada (0 < i < 4)
  {
    // desplazamos desde 0 hasta i-1 una posici�n a la derecha
    for (i = i - 1; i > 0; i--)
      m_recentProjects[i] = m_recentProjects[i-1];
  }
  else if (!found)
  {
    for (i = 3; i > 0; i--)
      m_recentProjects[i] = m_recentProjects[i-1];
  }
  m_recentProjects[0] = file;

  UpdateRecentProjects();
}

void MainFrame::OnCopy(wxCommandEvent &event)
{
  GetData()->CopyObject(GetData()->GetSelectedObject());
  UpdateFrame();
}

void MainFrame::OnCut (wxCommandEvent &event)
{
  GetData()->CutObject(GetData()->GetSelectedObject());
  UpdateFrame();
}

void MainFrame::OnDelete (wxCommandEvent &event)
{
  GetData()->RemoveObject(GetData()->GetSelectedObject());
  UpdateFrame();
}

void MainFrame::OnPaste (wxCommandEvent &event)
{
  GetData()->PasteObject(GetData()->GetSelectedObject());
  UpdateFrame();
}

void MainFrame::OnToggleExpand (wxCommandEvent &event)
{
  GetData()->ToggleExpandLayout(GetData()->GetSelectedObject());
}

void MainFrame::OnToggleStretch (wxCommandEvent &event)
{
  GetData()->ToggleStretchLayout(GetData()->GetSelectedObject());
}

void MainFrame::OnMoveUp (wxCommandEvent &event)
{
  GetData()->MovePosition(GetData()->GetSelectedObject(),false,1);
}

void MainFrame::OnMoveDown (wxCommandEvent &event)
{
  GetData()->MovePosition(GetData()->GetSelectedObject(),true,1);
}

void MainFrame::OnMoveLeft (wxCommandEvent &event)
{
  GetData()->MoveHierarchy(GetData()->GetSelectedObject(),true);
}

void MainFrame::OnMoveRight (wxCommandEvent &event)
{
  GetData()->MoveHierarchy(GetData()->GetSelectedObject(),false);
}

void MainFrame::OnChangeAlignment (wxCommandEvent &event)
{
  int align = 0;
  bool vertical = (event.GetId() == ID_ALIGN_TOP ||
                   event.GetId() == ID_ALIGN_BOTTOM ||
                   event.GetId() == ID_ALIGN_CENTER_V);

  switch (event.GetId())
  {
    case ID_ALIGN_RIGHT:
      align = wxALIGN_RIGHT;
      break;
    case ID_ALIGN_CENTER_H:
      align = wxALIGN_CENTER_HORIZONTAL;
      break;
    case ID_ALIGN_BOTTOM:
      align = wxALIGN_BOTTOM;
      break;
    case ID_ALIGN_CENTER_V:
      align = wxALIGN_CENTER_VERTICAL;
      break;
  }

  GetData()->ChangeAlignment(GetData()->GetSelectedObject(),align,vertical);
  UpdateLayoutTools();
}

void MainFrame::OnChangeBorder(wxCommandEvent& e)
{
  int border;

  switch (e.GetId())
  {
    case ID_BORDER_LEFT:
      border = wxLEFT;
      break;
    case ID_BORDER_RIGHT:
      border = wxRIGHT;
      break;
    case ID_BORDER_TOP:
      border = wxTOP;
      break;
    case ID_BORDER_BOTTOM:
      border = wxBOTTOM;
      break;
  }

  GetData()->ToggleBorderFlag(GetData()->GetSelectedObject(), border);
  UpdateLayoutTools();
}

bool MainFrame::SaveWarning()
{
  int result = wxYES;

  if (GetData()->IsModified())
  {
    result = ::wxMessageBox(wxT("Current project file has been modified...\n")
                            wxT("Do you want to save the changes?"),
                            wxT("Save project"),
                            wxYES | wxNO | wxCANCEL,
                            this);

    if (result == wxYES)
    {
      wxCommandEvent dummy;
      OnSaveProject(dummy);
    }
  }

  return (result != wxCANCEL);
}

