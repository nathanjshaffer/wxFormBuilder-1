#ifndef NOTEBOOKCHOOSER
#define NOTEBOOKCHOOSER

#ifndef USE_WXNOTEBOOK

#include <wx/wxFlatNotebook/wxFlatNotebook.h>
typedef wxFlatNotebook wxNotebookChooser;
typedef wxFlatNotebookImageList wxNotebookChooserImageList;
typedef wxFlatNotebookEvent wxNotebookChooserEvent;

#ifdef __WXGTK__
#define NOTEBOOK_STYLE wxFNB_NO_X_BUTTON | wxFNB_NO_NAV_BUTTONS | wxFNB_NODRAG
#else
#define NOTEBOOK_STYLE wxFNB_NO_X_BUTTON | wxFNB_NO_NAV_BUTTONS
#endif

#define ChooseNotebook( parent, id ) wxFlatNotebook( parent, id, wxDefaultPosition, wxDefaultSize, NOTEBOOK_STYLE );
#define EVT_NOTEBOOKCHOOSER_PAGE_CHANGED EVT_FLATNOTEBOOK_PAGE_CHANGED

#else

#include <wx/notebook.h>
typedef wxNotebook wxNotebookChooser;
typedef wxImageList wxNotebookChooserImageList;
typedef wxNotebookEvent wxNotebookChooserEvent;
#define ChooseNotebook( parent, id ) wxNotebook( parent, id );
#define EVT_NOTEBOOKCHOOSER_PAGE_CHANGED EVT_NOTEBOOK_PAGE_CHANGED

#endif

#endif //NOTEBOOKCHOOSER