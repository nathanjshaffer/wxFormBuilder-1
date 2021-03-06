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

#include <component.h>
#include <plugin.h>
#include <xrcconv.h>
#include <ticpp.h>

#include <wx/collpane.h>
#include <wx/splitter.h>
#include <wx/listctrl.h>

// Includes notebook, listbook, choicebook, treebook, toolbook, auibook
#include "bookutils.h"

///////////////////////////////////////////////////////////////////////////////

/**
Event handler for events generated by controls in this plugin
*/
class ComponentEvtHandler : public wxEvtHandler
{
private:
	wxWindow* m_window;
	IManager* m_manager;

public:
	ComponentEvtHandler( wxWindow* win, IManager* manager )
	:
	m_window( win ),
	m_manager( manager )
	{
	}

protected:
	void OnNotebookPageChanged( wxNotebookEvent& event );
	void OnListbookPageChanged( wxListbookEvent& event );
	void OnChoicebookPageChanged( wxChoicebookEvent& event );
	void OnTreebookPageChanged( wxTreebookEvent& event );
	void OnToolbookPageChanged( wxToolbookEvent& event );
	void OnAuiNotebookPageChanged( wxAuiNotebookEvent& event );
	void OnSplitterSashChanged( wxSplitterEvent& event );
	void OnCollapsiblePaneChanged( wxCollapsiblePaneEvent& event );

	template < class T >
		void OnBookPageChanged( int selPage, wxEvent* event )
	{
		// Only handle events from this book - prevents problems with nested books, because OnSelected is fired on an
		// object and all of its parents
		if ( m_window != event->GetEventObject() )
			return;

		if ( selPage < 0 )
			return;

		size_t count = m_manager->GetChildCount( m_window );
		for ( size_t i = 0; i < count; i++ )
		{
			wxObject* wxChild = m_manager->GetChild( m_window, i );
			IObject*  iChild = m_manager->GetIObject( wxChild );
			if ( iChild )
			{
				if ( (int)i == selPage && !iChild->GetPropertyAsInteger("selected") )
					m_manager->ModifyProperty( wxChild, "select", "1", false );
				else if ( (int)i != selPage && iChild->GetPropertyAsInteger("selected") )
					m_manager->ModifyProperty( wxChild, "select", "0", false );
			}
		}
		// Select the corresponding panel in the object tree
		T* book = wxDynamicCast( m_window, T );
		if ( NULL != book )
			m_manager->SelectObject( book->GetPage( selPage ) );
	}

	void OnAuiNotebookPageClosed( wxAuiNotebookEvent& event )
	{
		wxMessageBox( _("wxAuiNotebook pages can normally be closed.\nHowever, it is difficult to design a page that has been closed, so this action has been vetoed."),
						_("Page Close Vetoed!"), wxICON_INFORMATION, NULL );
		event.Veto();
	}

	void OnAuiNotebookAllowDND( wxAuiNotebookEvent& event )
	{
		wxMessageBox( _("wxAuiNotebook pages can be dragged to other wxAuiNotebooks if the wxEVT_COMMAND_AUINOTEBOOK_ALLOW_DND event is caught and allowed.\nHowever, it is difficult to design a page that has been moved, so this action was not allowed."),
						_("Page Move Not Allowed!"), wxICON_INFORMATION, NULL );
		event.Veto();
	}

	DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE( ComponentEvtHandler, wxEvtHandler )
	EVT_NOTEBOOK_PAGE_CHANGED( -1, ComponentEvtHandler::OnNotebookPageChanged )
	EVT_LISTBOOK_PAGE_CHANGED( -1, ComponentEvtHandler::OnListbookPageChanged )
	EVT_CHOICEBOOK_PAGE_CHANGED( -1, ComponentEvtHandler::OnChoicebookPageChanged )
	EVT_AUINOTEBOOK_PAGE_CHANGED( -1, ComponentEvtHandler::OnAuiNotebookPageChanged )
	EVT_AUINOTEBOOK_PAGE_CLOSE( -1, ComponentEvtHandler::OnAuiNotebookPageClosed )
	EVT_AUINOTEBOOK_ALLOW_DND( -1, ComponentEvtHandler::OnAuiNotebookAllowDND )
	EVT_SPLITTER_SASH_POS_CHANGED( -1, ComponentEvtHandler::OnSplitterSashChanged )
	EVT_COLLAPSIBLEPANE_CHANGED( -1, ComponentEvtHandler::OnCollapsiblePaneChanged )
END_EVENT_TABLE()

///////////////////////////////////////////////////////////////////////////////

class wxCustomSplitterWindow : public wxSplitterWindow
{
public:
	wxCustomSplitterWindow( wxWindow* parent, wxWindowID id,
							const wxPoint& point = wxDefaultPosition,
							const wxSize& size = wxDefaultSize,
							long style = wxSP_3D )
	:
	wxSplitterWindow( parent, id, point, size, style ),
	m_customSashPos( 0 ),
	m_customMinPaneSize( 0 )
	{
	}

	int m_customSashPos;
	int m_customMinPaneSize;
	int m_initialSashPos;

	// Used to ensure sash position is correct
	void OnIdle( wxIdleEvent& )
	{
		Disconnect( wxEVT_IDLE, wxIdleEventHandler( wxCustomSplitterWindow::OnIdle ) );

		// So the selection of the sizer at its initial position is cleared, then shown at the correct position
		Freeze();
		SetSashPosition( m_initialSashPos );
		Layout();
		Refresh();
		Update();
		Thaw();
	}

private:
	bool OnSashPositionChange( int newSashPosition )
	{
		m_customSashPos = newSashPosition;
		return wxSplitterWindow::OnSashPositionChange( newSashPosition );
	}

	void OnDoubleClickSash( int, int )
	{
		if ( 0 == m_customMinPaneSize )
		{
			wxMessageBox( 	_("Double-clicking a wxSplitterWindow sash with the minimum pane size set to 0 would normally unsplit it.\nHowever, it is difficult to design a pane that has been closed, so this action has been vetoed."),
							_("Unsplit Vetoed!"), wxICON_INFORMATION, NULL );
		}
	}

};

// Since wxGTK 2.8, wxNotebook has been sending page changed events in its destructor - this causes strange behavior
#if defined( __WXGTK__ )
	class wxCustomNotebook : public wxNotebook
	{
	public:
		wxCustomNotebook(wxWindow* parent, wxWindowID id,
						const wxPoint& point = wxDefaultPosition,
						const wxSize& size = wxDefaultSize, long style = 0 )
		:
		wxNotebook( parent, id, point, size, style )
		{
		}

		~wxCustomNotebook()
		{
			while ( GetEventHandler() != this )
			{
				// Remove and delete extra event handlers
				PopEventHandler( true );
			}
		}
	};
#else
	typedef wxNotebook wxCustomNotebook;
#endif

///////////////////////////////////////////////////////////////////////////////

class PanelComponent : public ComponentBase
{
public:

	wxObject* Create( IObject *obj, wxObject *parent )
	{
		wxPanel* panel = new wxPanel((wxWindow *)parent,-1,
									obj->GetPropertyAsPoint("pos"),
									obj->GetPropertyAsSize("size"),
									obj->GetPropertyAsInteger("style") |
									obj->GetPropertyAsInteger("window_style") );
		return panel;
	}

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "wxPanel", obj->GetPropertyAsString("name") );
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "wxPanel" );
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

class SplitterWindowComponent : public ComponentBase
{
	wxObject* Create( IObject *obj, wxObject *parent )
	{
		wxCustomSplitterWindow *splitter = new wxCustomSplitterWindow( (wxWindow *)parent,-1,
																		obj->GetPropertyAsPoint("pos"),
																		obj->GetPropertyAsSize("size"),
																		(obj->GetPropertyAsInteger("style") |
																		obj->GetPropertyAsInteger("window_style")) &
																		~wxSP_PERMIT_UNSPLIT );
		if ( !obj->IsNull("sashgravity") )
		{
			float gravity = obj->GetPropertyAsFloat("sashgravity");
			gravity = ( gravity < 0.0 ? 0.0 : gravity );
			gravity = ( gravity > 1.0 ? 1.0 : gravity );
			splitter->SetSashGravity( gravity );
		}

		if ( !obj->IsNull("sashsize") )
			splitter->SetSashSize( obj->GetPropertyAsInteger("sashsize") );

		if ( !obj->IsNull("min_pane_size") )
		{
			int minPaneSize = obj->GetPropertyAsInteger("min_pane_size");
			splitter->m_customMinPaneSize = minPaneSize;
			minPaneSize = ( minPaneSize < 1 ? 1 : minPaneSize );
			splitter->SetMinimumPaneSize( minPaneSize );
		}
		// Always have a child so it is drawn consistently
		splitter->Initialize( new wxPanel( splitter ) );

		// Used to ensure sash position is correct
		splitter->m_initialSashPos = obj->GetPropertyAsInteger("sashpos");
		splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( wxCustomSplitterWindow::OnIdle ) );
		return splitter;
	}

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "wxSplitterWindow", obj->GetPropertyAsString("name") );
		xrc.AddWindowProperties();
		xrc.AddProperty( "sashpos", "sashpos", XRC_TYPE_INTEGER );
		xrc.AddProperty( "sashgravity", "gravity", XRC_TYPE_FLOAT );
		xrc.AddProperty( "min_pane_size", "minsize", XRC_TYPE_INTEGER );

		if ( obj->GetPropertyAsString("splitmode") == "wxSPLIT_VERTICAL" )
			xrc.AddPropertyValue( "orientation", "vertical" );
		else
			xrc.AddPropertyValue( "orientation", "horizontal" );

		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "wxSplitterWindow" );
		filter.AddWindowProperties();
		filter.AddProperty( "sashpos", "sashpos", XRC_TYPE_INTEGER );
		filter.AddProperty( "gravity", "sashgravity", XRC_TYPE_FLOAT );
		filter.AddProperty( "minsize", "min_pane_size", XRC_TYPE_INTEGER );
		try
		{
			ticpp::Element *splitmode = xrcObj->FirstChildElement("orientation");
			std::string value = splitmode->GetText();
			if ( value == "vertical" )
				filter.AddPropertyValue( "splitmode", "wxSPLIT_VERTICAL" );
			else
				filter.AddPropertyValue( "splitmode", "wxSPLIT_HORIZONTAL" );

		}
		catch( ticpp::Exception& ) { }

		return filter.GetXfbObject();
	}

	void OnCreated( wxObject* wxobject, wxWindow* /*wxparent*/ )
	{
		wxCustomSplitterWindow* splitter = wxDynamicCast( wxobject, wxCustomSplitterWindow );
		if ( NULL == splitter )
		{
			wxLogError( _("This should be a wxSplitterWindow") );
			return;
		}

		// Remove default panel
		wxWindow* firstChild = splitter->GetWindow1();

		size_t childCount = GetManager()->GetChildCount( wxobject );
		switch ( childCount )
		{
			case 1:
			{
				// The child should be a splitteritem
				wxObject* splitterItem = GetManager()->GetChild( wxobject, 0 );

				// This one should be the actual wxWindow
				wxWindow* subwindow = wxDynamicCast( GetManager()->GetChild( splitterItem, 0 ), wxWindow );
				if ( NULL == subwindow )
				{
					wxLogError( _("A SplitterItem is abstract and must have a child!") );
					return;
				}
				if ( firstChild )
				{
					splitter->ReplaceWindow( firstChild, subwindow );
					firstChild->Destroy();
				}
				else
					splitter->Initialize( subwindow );

				splitter->PushEventHandler( new ComponentEvtHandler( splitter, GetManager() ) );
				break;
			}
			case 2:
			{
				// The child should be a splitteritem
				wxObject* splitterItem0 = GetManager()->GetChild( wxobject, 0 );
				wxObject* splitterItem1 = GetManager()->GetChild( wxobject, 1 );

				// This one should be the actual wxWindow
				wxWindow* subwindow0 = wxDynamicCast( GetManager()->GetChild( splitterItem0, 0 ), wxWindow );
				wxWindow* subwindow1 = wxDynamicCast( GetManager()->GetChild( splitterItem1, 0 ), wxWindow );

				if ( NULL == subwindow0 || NULL == subwindow1 )
				{
					wxLogError( _("A SplitterItem is abstract and must have a child!") );
					return;
				}

				// Get the split mode and sash position
				IObject* obj = GetManager()->GetIObject( wxobject );
				if ( obj == NULL )
					return;

				int sashPos = obj->GetPropertyAsInteger("sashpos");
				int splitmode = obj->GetPropertyAsInteger("splitmode");

				if ( firstChild )
				{
					splitter->ReplaceWindow( firstChild, subwindow0 );
					firstChild->Destroy();
				}

				if ( splitmode == wxSPLIT_VERTICAL )
					splitter->SplitVertically( subwindow0, subwindow1, sashPos );
				else
					splitter->SplitHorizontally( subwindow0, subwindow1, sashPos );

				splitter->PushEventHandler( new ComponentEvtHandler( splitter, GetManager() ) );
				break;
			}
			default:
				return;
		}
	}
};

void ComponentEvtHandler::OnSplitterSashChanged( wxSplitterEvent& )
{
	wxCustomSplitterWindow* window = wxDynamicCast( m_window, wxCustomSplitterWindow );
	if ( window != NULL )
	{
		if ( window->m_customSashPos != 0 )
			m_manager->ModifyProperty( window, "sashpos", wxString::Format( "%i", window->GetSashPosition() ) );
	}
}

class SplitterItemComponent : public ComponentBase
{
	ticpp::Element* ExportToXrc( IObject *obj )
	{
		// A __dummyitem__ will be ignored...
		ObjectToXrcFilter xrc( obj, "__dummyitem__", "" );
		return xrc.GetXrcObject();
	}
};

class ScrolledWindowComponent : public ComponentBase
{
public:

    wxObject* Create( IObject *obj, wxObject *parent )
    {
        wxScrolledWindow *sw = new wxScrolledWindow((wxWindow *)parent, -1,
													obj->GetPropertyAsPoint("pos"),
													obj->GetPropertyAsSize("size"),
													obj->GetPropertyAsInteger("style") |
													obj->GetPropertyAsInteger("window_style") );

        sw->SetScrollRate( 	obj->GetPropertyAsInteger("scroll_rate_x"),
							obj->GetPropertyAsInteger("scroll_rate_y") );
        return sw;
    }

    ticpp::Element* ExportToXrc( IObject *obj )
    {
        ObjectToXrcFilter xrc( obj, "wxScrolledWindow", obj->GetPropertyAsString("name") );
        xrc.AddWindowProperties();
        return xrc.GetXrcObject();
    }

    ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
    {
        XrcToXfbFilter filter( xrcObj, "wxScrolledWindow" );
        filter.AddWindowProperties();
        return filter.GetXfbObject();
    }
};

class NotebookComponent : public ComponentBase
{
public:
	wxObject* Create( IObject *obj, wxObject *parent )
	{
		wxNotebook* book = new wxCustomNotebook((wxWindow *)parent, -1,
												obj->GetPropertyAsPoint("pos"),
												obj->GetPropertyAsSize("size"),
												obj->GetPropertyAsInteger("style") |
												obj->GetPropertyAsInteger("window_style") );
		BookUtils::AddImageList( obj, book );

		book->PushEventHandler( new ComponentEvtHandler( book, GetManager() ) );
		return book;
	}

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "wxNotebook", obj->GetPropertyAsString("name") );
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "wxNotebook" );
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

void ComponentEvtHandler::OnNotebookPageChanged( wxNotebookEvent& event )
{
	OnBookPageChanged< wxNotebook >( event.GetSelection(), &event );
	event.Skip();
}

class NotebookPageComponent : public ComponentBase
{
public:
	void OnCreated( wxObject* wxobject, wxWindow* wxparent )
	{
		BookUtils::OnCreated< wxNotebook >( wxobject, wxparent, GetManager(), "NotebookPageComponent" );
	}

	void OnSelected( wxObject* wxobject )
	{
		BookUtils::OnSelected< wxNotebook >( wxobject, GetManager() );
	}

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "notebookpage" );
		xrc.AddProperty( "label", "label", XRC_TYPE_TEXT );
        if ( !obj->IsNull("bitmap") )
		{
			xrc.AddProperty( "bitmap", "bitmap", XRC_TYPE_BITMAP );
//			xrc.AddProperty( "image", "image", XRC_TYPE_INTEGER );
		}
		xrc.AddProperty( "select", "selected", XRC_TYPE_BOOL );
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
    XrcToXfbFilter filter( xrcObj, "notebookpage" );
		filter.AddWindowProperties();
		filter.AddProperty( "selected", "select", XRC_TYPE_BOOL );
		filter.AddProperty( "bitmap", "bitmap", XRC_TYPE_BITMAP );
//		filter.AddProperty( "image", "image", XRC_TYPE_INTEGER );
		filter.AddProperty( "label", "label", XRC_TYPE_TEXT );
		return filter.GetXfbObject();
	}
};

class ListbookComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxListbook* book = new wxListbook( (wxWindow *)parent, -1,
											obj->GetPropertyAsPoint("pos"),
											obj->GetPropertyAsSize("size"),
											obj->GetPropertyAsInteger("style") |
											obj->GetPropertyAsInteger("window_style"));
		BookUtils::AddImageList( obj, book );

		book->PushEventHandler( new ComponentEvtHandler( book, GetManager() ) );
		return book;
	}

// Small icon style not supported by GTK
#ifndef  __WXGTK__
	void OnCreated( wxObject* wxobject, wxWindow* wxparent )
	{
		wxListbook* book = wxDynamicCast( wxparent, wxListbook );
		if ( book )
		{
			// Small icon style if bitmapsize is not set
			IObject* obj = GetManager()->GetIObject( wxobject );
			if ( obj->GetPropertyAsString("bitmapsize").empty() )
			{
				wxListView* tmpListView = book->GetListView();
				long flags = tmpListView->GetWindowStyleFlag();
				flags = ( flags & ~wxLC_ICON ) | wxLC_SMALL_ICON; // TODO: Check this
				tmpListView->SetWindowStyleFlag( flags );
			}
		}
	}
#endif

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "wxListbook", obj->GetPropertyAsString("name") );
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "wxListbook" );
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

void ComponentEvtHandler::OnListbookPageChanged( wxListbookEvent& event )
{
	OnBookPageChanged< wxListbook >( event.GetSelection(), &event );
	event.Skip();
}

class ListbookPageComponent : public ComponentBase
{
public:
	void OnCreated( wxObject* wxobject, wxWindow* wxparent )
	{
		BookUtils::OnCreated< wxListbook >( wxobject, wxparent, GetManager(), "ListbookPageComponent" );
	}

	void OnSelected( wxObject* wxobject )
    {
		BookUtils::OnSelected< wxListbook >( wxobject, GetManager() );
    }

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "listbookpage" );
		xrc.AddProperty( "label", "label", XRC_TYPE_TEXT );
        if ( !obj->IsNull("bitmap") )
		{
			xrc.AddProperty( "bitmap", "bitmap", XRC_TYPE_BITMAP );
//			xrc.AddProperty( "image", "image", XRC_TYPE_INTEGER );
		}
		xrc.AddProperty( "select", "selected", XRC_TYPE_BOOL );
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "listbookpage" );
		filter.AddWindowProperties();
		filter.AddProperty( "selected", "select", XRC_TYPE_BOOL );
		filter.AddProperty( "bitmap", "bitmap", XRC_TYPE_BITMAP );
//		filter.AddProperty( "image", "image", XRC_TYPE_INTEGER );
		filter.AddProperty( "label", "label", XRC_TYPE_TEXT );
		return filter.GetXfbObject();
	}
};

class ChoicebookComponent : public ComponentBase
{
public:
	wxObject* Create( IObject *obj, wxObject *parent )
	{
		wxChoicebook* book = new wxChoicebook( (wxWindow *)parent, -1,
												obj->GetPropertyAsPoint("pos"),
												obj->GetPropertyAsSize("size"),
												obj->GetPropertyAsInteger("style") |
												obj->GetPropertyAsInteger("window_style") );

		book->PushEventHandler( new ComponentEvtHandler( book, GetManager() ) );
		return book;
	}

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "wxChoicebook", obj->GetPropertyAsString("name") );
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "wxChoicebook" );
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

void ComponentEvtHandler::OnChoicebookPageChanged( wxChoicebookEvent& event )
{
	OnBookPageChanged< wxChoicebook >( event.GetSelection(), &event );
	event.Skip();
}

class ChoicebookPageComponent : public ComponentBase
{
public:
	void OnCreated( wxObject* wxobject, wxWindow* wxparent )
	{
		BookUtils::OnCreated< wxChoicebook >( wxobject, wxparent, GetManager(), "ChoicebookPageComponent" );
	}

	void OnSelected( wxObject* wxobject )
	{
		BookUtils::OnSelected< wxChoicebook >( wxobject, GetManager() );
	}

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "choicebookpage" );
		xrc.AddProperty( "label", "label", XRC_TYPE_TEXT );
		xrc.AddProperty( "select", "selected", XRC_TYPE_BOOL );
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "choicebookpage" );
		filter.AddWindowProperties();
		filter.AddProperty( "selected", "select", XRC_TYPE_BOOL );
		filter.AddProperty( "label", "label", XRC_TYPE_TEXT );
		return filter.GetXfbObject();
	}
};

class TreebookComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxTreebook* book = new wxTreebook((wxWindow *)parent,-1,
										obj->GetPropertyAsPoint("pos"),
                                        obj->GetPropertyAsSize("size"),
                                        obj->GetPropertyAsInteger("style") |
										obj->GetPropertyAsInteger("window_style") );

		BookUtils::AddImageList( obj, book );

		book->PushEventHandler( new ComponentEvtHandler( book, GetManager() ) );
		return book;
	}

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "wxTreebook" ); //, obj->GetPropertyAsString("name")
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "wxTreebook" );
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

void ComponentEvtHandler::OnTreebookPageChanged( wxTreebookEvent& event )
{
	OnBookPageChanged< wxTreebook >( event.GetSelection(), &event );
	event.Skip();
}

class TreebookPageComponent : public ComponentBase
{
public:
	void OnCreated( wxObject* wxobject, wxWindow* wxparent )
	{
		// Easy read-only property access
		IObject* obj = GetManager()->GetIObject( wxobject );
		wxTreebook* book = wxDynamicCast( wxparent, wxTreebook );
		wxWindow* page = wxDynamicCast( GetManager()->GetChild( wxobject, 0 ), wxWindow );

		// Error checking
		if ( !( obj && book && page ) )
		{
			wxLogError( _("TreebookPageComponent is missing its wxFormBuilder object(%i), its parent(%i), or its child(%i)"), obj, book, page );
			return;
		}

        // TODO : size_t depth = GetLong( "depth" ); GetPropertyAsLong needed?
        size_t depth = obj->GetPropertyAsInteger("depth");

        if( depth > book->GetPageCount() )
		{
			wxLogError( _("TreebookPageComponent has an invalid depth."), obj, book, page );
			// TODO : Change depth property to 0
			// GetManager()->ModifyProperty( wxobject, "depth", "0" );
			return;
		}

		// Prevent events during construction - two event handlers have been pushed onto the stack
		// VObjEvtHandler and Component Event handler
		wxEvtHandler* vobjEvtHandler = book->PopEventHandler();
		wxEvtHandler* bookEvtHandler = book->PopEventHandler();

		int selection = book->GetSelection();
        int imageIndex = 0;

		// Apply image to page
		IObject* parentObj = GetManager()->GetIObject( wxparent );
		if ( !parentObj->GetPropertyAsString("bitmapsize").empty() )
		{
			if ( !obj->GetPropertyAsString("bitmap").empty() )
			{
				wxSize imageSize = parentObj->GetPropertyAsSize("bitmapsize");
				int width = imageSize.GetWidth();
				int height = imageSize.GetHeight();
				if ( width > 0 && height > 0 )
				{
					wxImageList* imageList = book->GetImageList();
					if ( imageList != NULL )
					{
						wxImage image = obj->GetPropertyAsBitmap("bitmap").ConvertToImage();
						imageIndex = imageList->Add( image.Scale( width, height ) );
                        book->SetPageImage( book->GetPageCount(), imageIndex );
					}
				}
			}
		}

		if ( depth == 0 )
		{
		    book->AddPage( page, obj->GetPropertyAsString("label"), false, imageIndex );
		}
        else
        {
            // TODO : Set a different value in cpp/pythoncode than $depth - 1
            book->InsertSubPage( depth - 1, page, obj->GetPropertyAsString("label"), false, imageIndex );
        }

		if ( obj->GetPropertyAsString("select") == "0" && selection >= 0 )
		{
			book->SetSelection( selection );
		}
		else
		{
			book->SetSelection( book->GetPageCount() - 1 );
		}
		// Restore event handling
		book->PushEventHandler( bookEvtHandler );
		book->PushEventHandler( vobjEvtHandler );
	}

	void OnSelected( wxObject* wxobject )
	{
		BookUtils::OnSelected< wxTreebook >( wxobject, GetManager() );
	}

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "treebookpage" );
		xrc.AddProperty( "depth", "depth", XRC_TYPE_INTEGER );
		xrc.AddProperty( "label", "label", XRC_TYPE_TEXT );
		xrc.AddProperty( "bitmap", "bitmap", XRC_TYPE_BITMAP );
//		xrc.AddProperty( "image", "image", XRC_TYPE_INTEGER );
		xrc.AddProperty( "select", "selected", XRC_TYPE_BOOL );
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "treebookpage" );
		filter.AddWindowProperties();
		filter.AddProperty( "depth", "depth", XRC_TYPE_INTEGER );
		filter.AddProperty( "label", "label", XRC_TYPE_TEXT );
		filter.AddProperty( "bitmap", "bitmap", XRC_TYPE_BITMAP );
//		filter.AddProperty( "image", "image", XRC_TYPE_INTEGER );
		filter.AddProperty( "selected", "select", XRC_TYPE_BOOL );
		return filter.GetXfbObject();
	}
};

class ToolbookComponent : public ComponentBase
{
public:
	wxObject* Create( IObject *obj, wxObject *parent )
	{
		wxToolbook* book = new wxToolbook( (wxWindow *)parent, -1,
											obj->GetPropertyAsPoint("pos"),
											obj->GetPropertyAsSize("size"),
											obj->GetPropertyAsInteger("style") |
											obj->GetPropertyAsInteger("window_style") );

		BookUtils::AddImageList( obj, book );

		book->PushEventHandler( new ComponentEvtHandler( book, GetManager() ) );
		return book;
	}

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "wxToolbook" ); //, obj->GetPropertyAsString("name")
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "wxToolbook" );
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

void ComponentEvtHandler::OnToolbookPageChanged( wxToolbookEvent& event )
{
	OnBookPageChanged< wxToolbook >( event.GetSelection(), &event );
	event.Skip();
}

class ToolbookPageComponent : public ComponentBase
{
public:
	void OnCreated( wxObject* wxobject, wxWindow* wxparent )
	{
		// Easy read-only property access
		IObject* obj = GetManager()->GetIObject( wxobject );
		wxToolbook* book = wxDynamicCast( wxparent, wxToolbook );
		wxWindow* page = wxDynamicCast( GetManager()->GetChild( wxobject, 0 ), wxWindow );

		// Error checking
		if ( !( obj && book && page ) )
		{
			wxLogError( _("ToolbookPageComponent is missing its wxFormBuilder object(%i), its parent(%i), or its child(%i)"), obj, book, page );
			return;
		}

		// Prevent events during construction - two event handlers have been pushed onto the stack
		// VObjEvtHandler and Component Event handler
		wxEvtHandler* vobjEvtHandler = book->PopEventHandler();
		wxEvtHandler* bookEvtHandler = book->PopEventHandler();

		int selection = book->GetSelection();
        int imageIndex = 0;

		// Apply image to page
		IObject* parentObj = GetManager()->GetIObject( wxparent );
		if ( !parentObj->GetPropertyAsString("bitmapsize").empty() )
		{
			if ( !obj->GetPropertyAsString("bitmap").empty() )
			{
				wxSize imageSize = parentObj->GetPropertyAsSize("bitmapsize");
				int width = imageSize.GetWidth();
				int height = imageSize.GetHeight();
				if ( width > 0 && height > 0 )
				{
					wxImageList* imageList = book->GetImageList();
					if ( imageList != NULL )
					{
						wxImage image = obj->GetPropertyAsBitmap("bitmap").ConvertToImage();
						imageIndex = imageList->Add( image.Scale( width, height ) );
                        book->SetPageImage( book->GetPageCount(), imageIndex );
					}
				}
			}
		}
        book->AddPage( page, obj->GetPropertyAsString("label"), false, imageIndex );

		if ( obj->GetPropertyAsString("select") == "0" && selection >= 0 )
		{
			book->SetSelection(selection);
		}
		else
		{
			book->SetSelection( book->GetPageCount() - 1 );
		}

		// Restore event handling
		book->PushEventHandler( bookEvtHandler );
		book->PushEventHandler( vobjEvtHandler );
    }

	void OnSelected( wxObject* wxobject )
	{
		BookUtils::OnSelected< wxToolbook >( wxobject, GetManager() );
	}

	ticpp::Element* ExportToXrc( IObject *obj )
	{
        ObjectToXrcFilter xrc( obj, "toolbookpage" );
		xrc.AddProperty( "label", "label", XRC_TYPE_TEXT );
        if ( !obj->IsNull("bitmap") )
		{
			xrc.AddProperty( "bitmap", "bitmap", XRC_TYPE_BITMAP );
//			xrc.AddProperty( "image", "image", XRC_TYPE_INTEGER );
		}
		xrc.AddProperty( "select", "selected", XRC_TYPE_BOOL );
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
        XrcToXfbFilter filter( xrcObj, "toolbookpage" );
		filter.AddWindowProperties();
		filter.AddProperty( "label", "label", XRC_TYPE_TEXT );
		filter.AddProperty( "bitmap", "bitmap", XRC_TYPE_BITMAP );
//		filter.AddProperty( "image", "image", XRC_TYPE_INTEGER );
		filter.AddProperty( "selected", "select", XRC_TYPE_BOOL );
		return filter.GetXfbObject();
	}
};

class AuiNotebookComponent : public ComponentBase
{
public:
	wxObject* Create( IObject *obj, wxObject *parent )
	{
		wxAuiNotebook* book = new wxAuiNotebook((wxWindow *)parent, -1,
												obj->GetPropertyAsPoint("pos"),
												obj->GetPropertyAsSize("size"),
												obj->GetPropertyAsInteger("style") |
												obj->GetPropertyAsInteger("window_style") );

		book->SetTabCtrlHeight( obj->GetPropertyAsInteger("tab_ctrl_height") );
		book->SetUniformBitmapSize( obj->GetPropertyAsSize("uniform_bitmap_size") );

		book->PushEventHandler( new ComponentEvtHandler( book, GetManager() ) );
		return book;
	}
/*
	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "wxAuiNotebook", obj->GetPropertyAsString("name") );
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "wxAuiNotebook" );
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
*/
};

void ComponentEvtHandler::OnAuiNotebookPageChanged( wxAuiNotebookEvent& event )
{
	OnBookPageChanged< wxAuiNotebook >( event.GetSelection(), &event );
	event.Skip();
}

class AuiNotebookPageComponent : public ComponentBase
{
public:
	void OnCreated( wxObject* wxobject, wxWindow* wxparent )
	{
		// Easy read-only property access
		IObject* obj = GetManager()->GetIObject( wxobject );

		wxAuiNotebook* book = wxDynamicCast( wxparent, wxAuiNotebook );

		//This wouldn't compile in MinGW - strange
		///wxWindow* page = wxDynamicCast( manager->GetChild( wxobject, 0 ), wxWindow );

		// Do this instead
		wxObject* child = GetManager()->GetChild( wxobject, 0 );
		wxWindow* page = NULL;
		if ( child->IsKindOf(CLASSINFO(wxWindow)))
		{
			page = (wxWindow*)child;
		}

		// Error checking
		if ( !( obj && book && page ) )
		{
			wxLogError( _("AuiNotebookPageComponent is missing its wxFormBuilder object(%i), its parent(%i), or its child(%i)"), obj, book, page );
			return;
		}

		// Prevent event handling by wxFB - these aren't user generated events
		SuppressEventHandlers suppress( book );

		// Save selection
		int selection = book->GetSelection();
		const wxBitmap& bitmap = obj->IsNull("bitmap") ? wxNullBitmap : obj->GetPropertyAsBitmap("bitmap");
		book->AddPage( page, obj->GetPropertyAsString("label"), false, bitmap );

		if ( obj->GetPropertyAsString("select") == "0" && selection >= 0 )
		{
			book->SetSelection(selection);
		}
		else
		{
			book->SetSelection( book->GetPageCount() - 1 );
		}
	}

	void OnSelected( wxObject* wxobject )
	{
		BookUtils::OnSelected< wxAuiNotebook >( wxobject, GetManager() );
	}
/*
	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "auinotebookpage" );
		xrc.AddProperty( "label", "label", XRC_TYPE_TEXT );
        if ( !obj->IsNull("bitmap") )
		{
			xrc.AddProperty( "bitmap", "bitmap", XRC_TYPE_BITMAP );
//			xrc.AddProperty( "image", "image", XRC_TYPE_INTEGER );
		}
		xrc.AddProperty( "select", "selected", XRC_TYPE_BOOL );
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element* xrcObj )
	{
		XrcToXfbFilter filter(xrcObj, "auinotebookpage");
		filter.AddWindowProperties();
		filter.AddProperty( "selected", "select", XRC_TYPE_BOOL );
		filter.AddProperty( "bitmap", "bitmap", XRC_TYPE_BITMAP );
		filter.AddProperty( "label", "label", XRC_TYPE_TEXT );
		return filter.GetXfbObject();
	}
*/
};

class CollapsiblePaneComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxCollapsiblePane* collapsiblePane = new wxCollapsiblePane((wxWindow *)parent,-1,
																	obj->GetPropertyAsString("label"),
																	obj->GetPropertyAsPoint("pos"),
																	obj->GetPropertyAsSize("size"),
																	obj->GetPropertyAsInteger("window_style") );
/*
        ComponentEvtHandler* eventHandler = new ComponentEvtHandler( collapsiblePane, GetManager() );
        collapsiblePane->PushEventHandler( eventHandler );
        collapsiblePane->Collapse( false );

	    bool collapsed = ( obj->GetPropertyAsInteger(_T("collapsed")) != 0 ? true : false );
        wxCollapsiblePaneEvent event( collapsiblePane, -1, collapsed );
        eventHandler->AddPendingEvent( event );
*/
		SuppressEventHandlers suppress( collapsiblePane );

        collapsiblePane->Collapse( ( obj->GetPropertyAsInteger("collapsed") != 0 ? true : false ) );
        collapsiblePane->PushEventHandler( new ComponentEvtHandler( collapsiblePane, GetManager() ) );

		return collapsiblePane;
	}

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "wxCollapsiblePane", obj->GetPropertyAsString("name") );
		xrc.AddWindowProperties();
		xrc.AddProperty( "label", "label", XRC_TYPE_TEXT );
		xrc.AddProperty( "collapsed", "collapsed", XRC_TYPE_BOOL );
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element *xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "wxCollapsiblePane" );
		filter.AddWindowProperties();
		filter.AddProperty( "label", "label", XRC_TYPE_TEXT );
		filter.AddProperty( "collapsed", "collapsed", XRC_TYPE_BOOL );
		return filter.GetXfbObject();
	}
};

void ComponentEvtHandler::OnCollapsiblePaneChanged( wxCollapsiblePaneEvent& event )
{
    if ( m_window != event.GetEventObject() )
        return;

	// Modify the "collapsed" property
	wxCollapsiblePane* collapsiblePane = wxDynamicCast( m_window, wxCollapsiblePane );
	if ( collapsiblePane != NULL )
	{
		SuppressEventHandlers suppress( collapsiblePane );

		bool collapsed = event.GetCollapsed();

		m_manager->ModifyProperty( collapsiblePane, "collapsed", "collapsed" ? "1" : "0" );

        collapsiblePane->Collapse( collapsed );

        // Select the corresponding collPane in the object tree
        m_manager->SelectObject( collapsiblePane );
	}
}

class CollapsiblePaneWindowComponent : public ComponentBase
{
public:
	wxObject* Create( IObject *obj, wxObject *parent )
	{
		wxCollapsiblePane* collapsiblePane = wxDynamicCast( parent, wxCollapsiblePane );

        if ( collapsiblePane == NULL )
        {
            wxLogError( _("panewindow must be added to a wxCollapsiblePane!") );
            return NULL;
        }

		wxWindow* window = collapsiblePane->GetPane();
		return window;
	}

	ticpp::Element* ExportToXrc( IObject *obj )
	{
		ObjectToXrcFilter xrc( obj, "panewindow" );//, obj->GetPropertyAsString("pane_name") );
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	ticpp::Element* ImportFromXrc( ticpp::Element *xrcObj )
	{
		XrcToXfbFilter filter( xrcObj, "panewindow" );
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

BEGIN_LIBRARY()

	WINDOW_COMPONENT("wxPanel",PanelComponent)

	WINDOW_COMPONENT( 	"wxCollapsiblePane", 	CollapsiblePaneComponent)
	ABSTRACT_COMPONENT( "panewindow", 		CollapsiblePaneWindowComponent)

	WINDOW_COMPONENT("wxScrolledWindow",ScrolledWindowComponent)
	MACRO(wxHSCROLL);
	MACRO(wxVSCROLL);

	WINDOW_COMPONENT("wxSplitterWindow",SplitterWindowComponent)
	ABSTRACT_COMPONENT("splitteritem",SplitterItemComponent)
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

	WINDOW_COMPONENT("wxChoicebook", ChoicebookComponent)
	ABSTRACT_COMPONENT("choicebookpage", ChoicebookPageComponent)
	MACRO(wxCHB_TOP)
	MACRO(wxCHB_LEFT)
	MACRO(wxCHB_RIGHT)
	MACRO(wxCHB_BOTTOM)
	MACRO(wxCHB_DEFAULT)

	WINDOW_COMPONENT("wxListbook", ListbookComponent)
	ABSTRACT_COMPONENT("listbookpage", ListbookPageComponent)
	MACRO(wxLB_TOP)
	MACRO(wxLB_LEFT)
	MACRO(wxLB_RIGHT)
	MACRO(wxLB_BOTTOM)
	MACRO(wxLB_DEFAULT)

	WINDOW_COMPONENT("wxNotebook", NotebookComponent)
	ABSTRACT_COMPONENT("notebookpage",NotebookPageComponent)
	MACRO(wxNB_TOP)
	MACRO(wxNB_LEFT)
	MACRO(wxNB_RIGHT)
	MACRO(wxNB_BOTTOM)
	MACRO(wxNB_FIXEDWIDTH)
	MACRO(wxNB_MULTILINE)
	MACRO(wxNB_NOPAGETHEME)
	MACRO(wxNB_FLAT)

	WINDOW_COMPONENT("wxTreebook", TreebookComponent)
	ABSTRACT_COMPONENT("treebookpage", TreebookPageComponent)

	WINDOW_COMPONENT("wxToolbook", ToolbookComponent)
	ABSTRACT_COMPONENT("toolbookpage", ToolbookPageComponent)

	// wxBookCtrl flags (common for wxNotebook, wxListbook, wxChoicebook, wxTreebook)
	MACRO(wxBK_DEFAULT)
	MACRO(wxBK_TOP)
	MACRO(wxBK_BOTTOM)
	MACRO(wxBK_LEFT)
	MACRO(wxBK_RIGHT)

	WINDOW_COMPONENT("wxAuiNotebook", AuiNotebookComponent)
	ABSTRACT_COMPONENT("auinotebookpage", AuiNotebookPageComponent)
	MACRO(wxAUI_NB_DEFAULT_STYLE)
	MACRO(wxAUI_NB_TAB_SPLIT)
	MACRO(wxAUI_NB_TAB_MOVE)
	MACRO(wxAUI_NB_TAB_EXTERNAL_MOVE)
	MACRO(wxAUI_NB_TAB_FIXED_WIDTH)
	MACRO(wxAUI_NB_SCROLL_BUTTONS)
	MACRO(wxAUI_NB_WINDOWLIST_BUTTON)
	MACRO(wxAUI_NB_CLOSE_BUTTON)
	MACRO(wxAUI_NB_CLOSE_ON_ACTIVE_TAB)
	MACRO(wxAUI_NB_CLOSE_ON_ALL_TABS)

END_LIBRARY()
