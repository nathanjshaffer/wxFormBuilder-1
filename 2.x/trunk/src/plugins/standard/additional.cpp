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
#include "icons/unknown.xpm"

#include <wx/calctrl.h>
#include <wx/html/htmlwin.h>
#include <wx/treectrl.h>
#include <wx/spinbutt.h>
#include <wx/spinctrl.h>
#include <wx/tglbtn.h>
#include <wx/scrolbar.h>
#include <wx/splitter.h>
#include <wx/checklst.h>
#include <wx/datectrl.h>
#include <wx/listbook.h>
#include <wx/choicebk.h>
#include <wx/listctrl.h>
#include <wx/image.h>
#include <wx/notebook.h>

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
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxCalendarCtrl"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxCalendarCtrl"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		return filter.GetXfbObject();
	}
};

class DatePickerCtrlComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		return new wxDatePickerCtrl((wxWindow *)parent,-1,
			wxDefaultDateTime,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxDatePickerCtrl"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxDatePickerCtrl"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		return filter.GetXfbObject();
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
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

		wxString dummy_page(
			wxT("<b>wxHtmlWindow</b><br />")
			wxT("This is a dummy page.</body></html>"));

		hw->SetPage(dummy_page);

		return hw;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxHtmlWindow"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxHtmlWindow"));
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

class RadioButtonComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxRadioButton *rb = new wxRadioButton((wxWindow *)parent,-1,
			obj->GetPropertyAsString(_("label")),
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

		rb->SetValue( ( obj->GetPropertyAsInteger(_("value")) != 0 ) );
		return rb;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxRadioButton"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		xrc.AddProperty(_("label"),_("label"), XRC_TYPE_TEXT);
		xrc.AddProperty(_("value"),_("value"), XRC_TYPE_BOOL);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxRadioButton"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		filter.AddProperty(_("label"),_("label"), XRC_TYPE_TEXT);
		filter.AddProperty(_("value"),_("value"), XRC_TYPE_BOOL);
		return filter.GetXfbObject();
	}
};

class ToggleButtonComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxToggleButton* tb = new wxToggleButton((wxWindow *)parent,-1,
			obj->GetPropertyAsString(_("label")),
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("window_style")));

		tb->SetValue( ( obj->GetPropertyAsInteger(_("value")) != 0 ) );
		return tb;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxToggleButton"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		xrc.AddProperty(_("label"),_("label"), XRC_TYPE_TEXT);
		xrc.AddProperty(_("value"),_("checked"), XRC_TYPE_BOOL);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxToggleButton"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		filter.AddProperty(_("label"),_("label"), XRC_TYPE_TEXT);
		filter.AddProperty(_("checked"),_("value"), XRC_TYPE_BOOL);
		return filter.GetXfbObject();
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
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

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

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxTreeCtrl"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxTreeCtrl"));
		filter.AddWindowProperties();
		return filter.GetXfbObject();
	}
};

class ScrollBarComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxScrollBar *sb = new wxScrollBar((wxWindow *)parent,-1,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

        sb->SetScrollbar(obj->GetPropertyAsInteger(_T("value")),
            obj->GetPropertyAsInteger(_T("thumbsize")),
            obj->GetPropertyAsInteger(_T("range")),
            obj->GetPropertyAsInteger(_T("pagesize")));
        return sb;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxScrollBar"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		xrc.AddProperty(_("value"), _("value"), XRC_TYPE_INTEGER);
		xrc.AddProperty(_("thumbsize"), _("thumbsize"), XRC_TYPE_INTEGER);
		xrc.AddProperty(_("range"), _("range"), XRC_TYPE_INTEGER);
		xrc.AddProperty(_("pagesize"), _("pagesize"), XRC_TYPE_INTEGER);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxScrollBar"));
		filter.AddWindowProperties();
		filter.AddProperty(_("value"), _("value"), XRC_TYPE_INTEGER);
		filter.AddProperty(_("thumbsize"), _("thumbsize"), XRC_TYPE_INTEGER);
		filter.AddProperty(_("range"), _("range"), XRC_TYPE_INTEGER);
		filter.AddProperty(_("pagesize"), _("pagesize"), XRC_TYPE_INTEGER);
		return filter.GetXfbObject();
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
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")),
			obj->GetPropertyAsInteger(_("min")),
			obj->GetPropertyAsInteger(_("max")),
			obj->GetPropertyAsInteger(_("initial")));
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxSpinCtrl"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		xrc.AddProperty(_("initial"),_("value"), XRC_TYPE_TEXT);
		xrc.AddProperty(_("min"),_("min"), XRC_TYPE_INTEGER);
		xrc.AddProperty(_("max"),_("max"), XRC_TYPE_INTEGER);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxSpinCtrl"));
		filter.AddWindowProperties();
		filter.AddProperty(_("value"),_("value"), XRC_TYPE_TEXT);
		filter.AddProperty(_("value"),_("initial"), XRC_TYPE_TEXT);
		filter.AddProperty(_("min"),_("min"), XRC_TYPE_INTEGER);
		filter.AddProperty(_("max"),_("max"), XRC_TYPE_INTEGER);

		return filter.GetXfbObject();
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
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxSpinButton"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxSpinButton"));
		filter.AddWindowProperties();
		return filter.GetXfbObject();
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
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

		splitter->CreateSplit(obj->GetPropertyAsInteger(_("splitmode")),
			obj->GetPropertyAsInteger(_("sashpos")));

		splitter->SetSashGravity( obj->GetPropertyAsFloat(_("sashgravity")) );

		return splitter;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxSplitterWindow"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		xrc.AddProperty(_("sashpos"),_("sashpos"),XRC_TYPE_INTEGER);
		//xrc.AddProperty(_("minsize"),_("minsize"),...
		if (obj->GetPropertyAsString(_("splitmode")) == wxT("wxSPLIT_VERTICAL"))
			xrc.AddPropertyValue(_("orientation"),wxT("vertical"));
		else
			xrc.AddPropertyValue(_("orientation"),wxT("horizontal"));

		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxSplitterWindow"));
		filter.AddWindowProperties();
		filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		filter.AddProperty(_("sashpos"),_("sashpos"),XRC_TYPE_INTEGER);

		TiXmlElement *splitmode = xrcObj->FirstChildElement("orientation");
		if (splitmode)
		{
			TiXmlText *xmlValue = splitmode->FirstChild()->ToText();
			if (xmlValue)
			{
				string value = xmlValue->Value();
				if (value == "vertical")
					filter.AddPropertyValue(wxT("splitmode"),wxT("wxSPLIT_VERTICAL"));
				else
					filter.AddPropertyValue(wxT("splitmode"),wxT("wxSPLIT_HORIZONTAL"));
			}
		}

		return filter.GetXfbObject();
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

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		// A __dummyitem__ will be ignored...
		ObjectToXrcFilter xrc(obj, _("__dummyitem__"),wxT(""));
		return xrc.GetXrcObject();
	}
};

class CheckListBoxComponent : public ComponentBase
{
public:

	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxArrayString choices (obj->GetPropertyAsArrayString(_("choices")));
		wxCheckListBox *cl =
			new wxCheckListBox((wxWindow *)parent,-1,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			choices,
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

		return cl;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxCheckList"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		xrc.AddProperty(_("choices"), _("choices"), XRC_TYPE_STRINGLIST);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxCheckList"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"), XRC_TYPE_BITLIST);
		filter.AddProperty(_("choices"), _("choices"), XRC_TYPE_STRINGLIST);
		return filter.GetXfbObject();
	}
};

class ScrolledWindowComponent : public ComponentBase
{
public:

    wxObject* Create(IObject *obj, wxObject *parent)
    {
        wxScrolledWindow *sw = new wxScrolledWindow((wxWindow *)parent, -1,
            obj->GetPropertyAsPoint(_("pos")),
            obj->GetPropertyAsSize(_("size")),
            obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

        sw->SetScrollRate(
            obj->GetPropertyAsInteger(_("scroll_rate_x")),
            obj->GetPropertyAsInteger(_("scroll_rate_y")));
        return sw;
    }

    TiXmlElement* ExportToXrc(IObject *obj)
    {
        ObjectToXrcFilter xrc(obj, _("wxScrolledWindow"), obj->GetPropertyAsString(_("name")));
        xrc.AddWindowProperties();
        return xrc.GetXrcObject();
    }

    TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
    {
        XrcToXfbFilter filter(xrcObj, _("wxScrolledWindow"));
        filter.AddWindowProperties();
        return filter.GetXfbObject();
    }
};


class NotebookComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxNotebook* book = new wxNotebook((wxWindow *)parent,-1,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

		if ( !obj->GetPropertyAsString( _("bitmapsize") ).empty() )
		{
			wxSize imageSize = obj->GetPropertyAsSize(_("bitmapsize"));
			wxImageList* images = new wxImageList( imageSize.GetWidth(), imageSize.GetHeight() );
			wxImage image = wxBitmap( unknown_xpm ).ConvertToImage();
			images->Add( image.Scale( imageSize.GetWidth(), imageSize.GetHeight() ) );
			book->AssignImageList( images );
		}

		return book;
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxNotebook"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxNotebook"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		return filter.GetXfbObject();
	}

	bool KeepEvtHandler() { return true; }
};

class NotebookPageComponent : public ComponentBase
{
public:
	void OnCreated(IObjectView *objview, wxWindow *wxparent, IObjectView *parent,
		IObjectView *first_child)
	{
		IObject *obj = objview->Object();
		wxNotebook *nb = (wxNotebook *)parent->Window();
		wxWindow *page = first_child->Window();

		wxEvtHandler* visObjEvtHandler = nb->PopEventHandler();

		// Save selection
		int selection = nb->GetSelection();
		nb->AddPage( page, obj->GetPropertyAsString( _("label") ) );

		// Apply image to page
		IObject* parentObj = parent->Object();
		if ( !parentObj->GetPropertyAsString( _("bitmapsize") ).empty() )
		{
			if ( !obj->GetPropertyAsString( _("bitmap") ).empty() )
			{
				wxSize imageSize = parentObj->GetPropertyAsSize(_("bitmapsize"));
				int width = imageSize.GetWidth();
				int height = imageSize.GetHeight();
				if ( width > 0 && height > 0 )
				{
					wxImageList* imageList = nb->GetImageList();
					wxImage image = obj->GetPropertyAsBitmap( _("bitmap") ).ConvertToImage();
					imageList->Add( image.Scale( width, height ) );
					nb->SetPageImage( nb->GetPageCount() - 1, imageList->GetImageCount() - 1 );
				}
			}
		}

		if (obj->GetPropertyAsString(_("select"))==wxT("0") && selection >= 0)
			nb->SetSelection(selection);
		else
			nb->SetSelection(nb->GetPageCount()-1);

		nb->PushEventHandler( visObjEvtHandler );
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
    ObjectToXrcFilter xrc(obj, _("notebookpage"));
		xrc.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
		xrc.AddProperty(_("selected"),_("selected"),XRC_TYPE_BOOL);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
    XrcToXfbFilter filter(xrcObj, _("notebookpage"));
		filter.AddWindowProperties();
		filter.AddProperty(_("selected"),_("selected"),XRC_TYPE_BOOL);
		filter.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
		return filter.GetXfbObject();
	}
};

class ListbookComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		wxListbook* book = new wxListbook((wxWindow *)parent,-1,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));

		if ( !obj->GetPropertyAsString( _("bitmapsize") ).empty() )
		{
			wxSize imageSize = obj->GetPropertyAsSize(_("bitmapsize"));
			wxImageList* images = new wxImageList( imageSize.GetWidth(), imageSize.GetHeight() );
			wxImage image = wxBitmap( unknown_xpm ).ConvertToImage();
			images->Add( image.Scale( imageSize.GetWidth(), imageSize.GetHeight() ) );
			book->AssignImageList( images );
		}

		return book;
	}

// Small icon style not supported by GTK
#ifndef  __WXGTK__
	void OnCreated(IObjectView *objview, wxWindow *wxparent, IObjectView *parent,
		IObjectView *first_child)
	{
		wxListbook *lb = (wxListbook*) objview->Window();
		wxASSERT(lb->IsKindOf(CLASSINFO(wxListbook)));

		// Small icon style if bitmapsize is not set
		IObject* obj = objview->Object();
		if ( obj->GetPropertyAsString( _("bitmapsize") ).empty() )
		{
			wxListView* tmpListView = lb->GetListView();
			long flags = tmpListView->GetWindowStyleFlag();
			flags = (flags & ~wxLC_ICON) | wxLC_SMALL_ICON;
			tmpListView->SetWindowStyleFlag( flags );
		}
	}
#endif

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxListbook"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxListbook"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		return filter.GetXfbObject();
	}

	bool KeepEvtHandler() { return true; }
};

class ListbookPageComponent : public ComponentBase
{
public:
	void OnCreated(IObjectView *objview, wxWindow *wxparent, IObjectView *parent,
		IObjectView *first_child)
	{
		IObject *obj = objview->Object();
		wxListbook *lb = (wxListbook *)parent->Window();
		wxWindow *page = first_child->Window();

		wxEvtHandler* visObjEvtHandler = lb->PopEventHandler();

		// save selection
		int selection = lb->GetSelection();
		wxString selectProperty = obj->GetPropertyAsString(_("select"));
		lb->AddPage( page, obj->GetPropertyAsString( _("label") ) );

		// Apply image to page
		IObject* parentObj = parent->Object();
		if ( !parentObj->GetPropertyAsString( _("bitmapsize") ).empty() )
		{
			if ( !obj->GetPropertyAsString( _("bitmap") ).empty() )
			{
				wxSize imageSize = parentObj->GetPropertyAsSize(_("bitmapsize"));
				int width = imageSize.GetWidth();
				int height = imageSize.GetHeight();
				if ( width > 0 && height > 0 )
				{
					wxImageList* imageList = lb->GetImageList();
					wxImage image = obj->GetPropertyAsBitmap( _("bitmap") ).ConvertToImage();
					imageList->Add( image.Scale( width, height ) );
					lb->SetPageImage( lb->GetPageCount() - 1, imageList->GetImageCount() - 1 );
				}
			}
		}

		if (selectProperty==wxT("0") && selection >= 0)
			lb->SetSelection(selection);
		else
			lb->SetSelection(lb->GetPageCount()-1);

		lb->PushEventHandler( visObjEvtHandler );
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("listbookpage"));
		xrc.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
		xrc.AddProperty(_("selected"),_("selected"),XRC_TYPE_BOOL);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("listbookpage"));
		filter.AddWindowProperties();
		filter.AddProperty(_("selected"),_("selected"),XRC_TYPE_BOOL);
		filter.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
		return filter.GetXfbObject();
	}
};
class ChoicebookComponent : public ComponentBase
{
public:
	wxObject* Create(IObject *obj, wxObject *parent)
	{
		return new wxChoicebook((wxWindow *)parent,-1,
			obj->GetPropertyAsPoint(_("pos")),
			obj->GetPropertyAsSize(_("size")),
			obj->GetPropertyAsInteger(_("style")) | obj->GetPropertyAsInteger(_("window_style")));
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("wxChoicebook"), obj->GetPropertyAsString(_("name")));
		xrc.AddWindowProperties();
		//xrc.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("wxChoicebook"));
		filter.AddWindowProperties();
		//filter.AddProperty(_("style"),_("style"),XRC_TYPE_BITLIST);
		return filter.GetXfbObject();
	}

	bool KeepEvtHandler() { return true; }
};

class ChoicebookPageComponent : public ComponentBase
{
public:
	void OnCreated(IObjectView *objview, wxWindow *wxparent, IObjectView *parent,
		IObjectView *first_child)
	{
		IObject *obj = objview->Object();
		wxChoicebook *cb = (wxChoicebook*)parent->Window();
		wxWindow *page = first_child->Window();

		wxEvtHandler* visObjEvtHandler = cb->PopEventHandler();

		int selection = cb->GetSelection();
		cb->AddPage(page,obj->GetPropertyAsString(_("label")));

		if (obj->GetPropertyAsString(_("select"))==wxT("0") && selection >= 0)
			cb->SetSelection(selection);
		else
			cb->SetSelection(cb->GetPageCount()-1);

		cb->PushEventHandler( visObjEvtHandler );
	}

	TiXmlElement* ExportToXrc(IObject *obj)
	{
		ObjectToXrcFilter xrc(obj, _("choicebookpage"));
		xrc.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
		xrc.AddProperty(_("selected"),_("selected"),XRC_TYPE_BOOL);
		return xrc.GetXrcObject();
	}

	TiXmlElement* ImportFromXrc(TiXmlElement *xrcObj)
	{
		XrcToXfbFilter filter(xrcObj, _("choicebookpage"));
		filter.AddWindowProperties();
		filter.AddProperty(_("selected"),_("selected"),XRC_TYPE_BOOL);
		filter.AddProperty(_("label"),_("label"),XRC_TYPE_TEXT);
		return filter.GetXfbObject();
	}
};
///////////////////////////////////////////////////////////////////////////////

BEGIN_LIBRARY()

WINDOW_COMPONENT("wxCalendarCtrl",CalendarCtrlComponent)
WINDOW_COMPONENT("wxDatePickerCtrl", DatePickerCtrlComponent )
WINDOW_COMPONENT("wxHtmlWindow",HtmlWindowComponent)
WINDOW_COMPONENT("wxRadioButton",RadioButtonComponent)
WINDOW_COMPONENT("wxToggleButton",ToggleButtonComponent)
WINDOW_COMPONENT("wxTreeCtrl",TreeCtrlComponent)
WINDOW_COMPONENT("wxScrollBar",ScrollBarComponent)
WINDOW_COMPONENT("wxSpinCtrl",SpinCtrlComponent)
WINDOW_COMPONENT("wxSpinButton",SpinButtonComponent)
WINDOW_COMPONENT("wxSplitterWindow",SplitterWindowComponent)
ABSTRACT_COMPONENT("splitteritem",SplitterItemComponent)
WINDOW_COMPONENT("wxScrolledWindow",ScrolledWindowComponent)
WINDOW_COMPONENT("wxNotebook", NotebookComponent)
ABSTRACT_COMPONENT("notebookpage",NotebookPageComponent)
WINDOW_COMPONENT("wxListbook", ListbookComponent)
ABSTRACT_COMPONENT("listbookpage", ListbookPageComponent)

WINDOW_COMPONENT("wxChoicebook", ChoicebookComponent)
ABSTRACT_COMPONENT("choicebookpage", ChoicebookPageComponent)

// wxCheckListBox
WINDOW_COMPONENT("wxCheckListBox",CheckListBoxComponent)

// wxCalendarCtrl
MACRO(wxCAL_SUNDAY_FIRST)
MACRO(wxCAL_MONDAY_FIRST)
MACRO(wxCAL_SHOW_HOLIDAYS)
MACRO(wxCAL_NO_YEAR_CHANGE)
MACRO(wxCAL_NO_MONTH_CHANGE)
MACRO(wxCAL_SHOW_SURROUNDING_WEEKS)
MACRO(wxCAL_SEQUENTIAL_MONTH_SELECTION)

// wxDatePickerCtrl
MACRO(wxDP_SPIN)
MACRO(wxDP_DROPDOWN)
MACRO(wxDP_SHOWCENTURY)
MACRO(wxDP_ALLOWNONE)
MACRO(wxDP_DEFAULT)

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

// wxScrolledWindow
MACRO(wxHSCROLL);
MACRO(wxVSCROLL);

// wxNotebook
MACRO(wxNB_TOP)
MACRO(wxNB_LEFT)
MACRO(wxNB_RIGHT)
MACRO(wxNB_BOTTOM)
MACRO(wxNB_FIXEDWIDTH)
MACRO(wxNB_MULTILINE)
MACRO(wxNB_NOPAGETHEME)
MACRO(wxNB_FLAT)

// wxListbook
MACRO(wxLB_TOP)
MACRO(wxLB_LEFT)
MACRO(wxLB_RIGHT)
MACRO(wxLB_BOTTOM)
MACRO(wxLB_DEFAULT)

// wxChoicebook
MACRO(wxCHB_TOP)
MACRO(wxCHB_LEFT)
MACRO(wxCHB_RIGHT)
MACRO(wxCHB_BOTTOM)
MACRO(wxCHB_DEFAULT)

END_LIBRARY()

