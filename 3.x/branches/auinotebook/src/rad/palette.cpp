///////////////////////////////////////////////////////////////////////////////
//
// wxFormBuilder - A Visual Dialog Editor for wxWidgets.
// Copyright (C) 2005 José Antonio Hurtado
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
//   José Antonio Hurtado - joseantonio.hurtado@gmail.com
//   Juan Antonio Ortega  - jortegalalmolda@gmail.com
//
///////////////////////////////////////////////////////////////////////////////

#include "palette.h"
#include "model/objectbase.h"
#include "bitmaps.h"
#include "utils/debug.h"
#include "utils/typeconv.h"
#include "rad/title.h"
#include "wx/config.h"
#include "rad/appdata.h"
#include "rad/fbaui/wxfbauinotebook.h"

#define ID_PALETTE_BUTTON 999

#ifdef __WXGTK__
	#if wxCHECK_VERSION( 2, 8, 0 )
		#define DRAG_OPTION 0
	#else
		#define DRAG_OPTION wxFNB_NODRAG
	#endif
#else
	#define DRAG_OPTION 0
#endif

wxWindowID wxFbPalette::nextId = wxID_HIGHEST + 1000;

BEGIN_EVENT_TABLE(wxFbPalette, wxPanel)
    EVT_TOOL(-1, wxFbPalette::OnButtonClick)
    EVT_SPIN_UP(-1, wxFbPalette::OnSpinUp)
    EVT_SPIN_DOWN(-1, wxFbPalette::OnSpinDown)
END_EVENT_TABLE()

wxFbPalette::wxFbPalette(wxWindow *parent,int id)
  : wxPanel(parent,id), m_notebook(NULL)
{
}

void wxFbPalette::PopulateToolbar(PObjectPackage pkg, wxToolBar *toolbar)
{
  unsigned int j = 0;
  while (j < pkg->GetObjectCount())
  {
  	PObjectInfo info = pkg->GetObjectInfo(j);
    if ( info->IsStartOfGroup() )
    {
    	toolbar->AddSeparator();
    }
    if ( NULL == info->GetComponent() )
    {
    	Debug::Print( _("Missing Component for Class \"%s\" of Package \"%s\"."), info->GetClassName().c_str(), pkg->GetPackageName().c_str() );
    }
    else
    {
		wxString widget( info->GetClassName() );

		wxBitmap icon = info->GetIconFile();
		toolbar->AddTool(nextId++, widget, icon, widget);

		toolbar->Realize();
    }
    j++;
  }
}

void wxFbPalette::Create()
{
  wxBoxSizer *top_sizer = new wxBoxSizer(wxVERTICAL);

  m_notebook = new wxFBAuiNotebook( this, -1, wxDefaultPosition, wxDefaultSize, wxAUI_NB_TAB_MOVE | wxAUI_NB_WINDOWLIST_BUTTON );

  unsigned int pkg_count = AppData()->GetPackageCount();

  Debug::Print( wxT("[Palette] Pages %d"),pkg_count);
  int pageHeight = 36;
  for (unsigned int i = 0; i < pkg_count;i++)
  {
    PObjectPackage pkg = AppData()->GetPackage(i);
    wxString pkg_name = pkg->GetPackageName();

    wxPanel *panel = new wxPanel(m_notebook,-1);
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    wxToolBar *toolbar = new wxToolBar(panel, -1, wxDefaultPosition, wxDefaultSize, wxTB_NODIVIDER | wxTB_FLAT);
    toolbar->SetToolBitmapSize(wxSize(22, 22));
    PopulateToolbar(pkg, toolbar);
    m_tv.push_back(toolbar);

    sizer->Add(toolbar, 1, 0 );

    wxSpinButton *sb = new wxSpinButton(panel, -1, wxDefaultPosition, wxDefaultSize, wxSP_HORIZONTAL);
    sb->SetRange(0, (int)pkg->GetObjectCount() - 1);
    sb->SetValue(0);
    m_posVector.push_back(0);
    sizer->Add(sb, 0, wxEXPAND);

    panel->SetSizer(sizer);
    sizer->Fit(panel);
    sizer->SetSizeHints(panel);
	pageHeight = panel->GetSize().GetHeight();

    m_notebook->AddPage(panel, pkg_name, false, pkg->GetPackageIcon());
  }

  m_notebook->SetMinSize( wxSize( -1, m_notebook->GetHeightForPageHeight( pageHeight ) ) );
  top_sizer->Add(m_notebook,0,wxEXPAND,0);

  SetSizer(top_sizer);
  top_sizer->Fit(this);
  top_sizer->SetSizeHints(this);
}

void wxFbPalette::OnSpinUp(wxSpinEvent& )
{
  int page = m_notebook->GetSelection();
  PObjectPackage pkg = AppData()->GetPackage(page);

  if ((int)pkg->GetObjectCount() - m_posVector[page] - 1 <= 0) return;

  m_posVector[page]++;
  wxToolBar *toolbar = m_tv[page];
  toolbar->DeleteToolByPos(0);
  toolbar->Realize();
}

void wxFbPalette::OnSpinDown(wxSpinEvent& )
{
  int page = m_notebook->GetSelection();
  if (m_posVector[page] <= 0) return;

  m_posVector[page]--;
  wxToolBar *toolbar = m_tv[page];
  PObjectPackage pkg = AppData()->GetPackage(page);
  wxString widget( pkg->GetObjectInfo( m_posVector[page] )->GetClassName() );
  wxBitmap icon = pkg->GetObjectInfo(m_posVector[page])->GetIconFile();
  toolbar->InsertTool(0, nextId++, icon, wxNullBitmap, false, NULL, widget, widget);
  toolbar->Realize();
}

void wxFbPalette::OnButtonClick(wxCommandEvent &event)
{
  for (unsigned int i = 0; i < m_tv.size(); i++)
  {
    if (m_tv[i]->FindById(event.GetId()))
    {
      wxString name = m_tv[i]->GetToolShortHelp(event.GetId());
      AppData()->CreateObject(name);
      return;
    }
  }
}

wxFbPalette::~wxFbPalette()
{
	wxConfigBase* config = wxConfigBase::Get();
	config->Write( wxT("/palette/pageOrder"), m_notebook->GetPageOrder() );
}
