///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wxSunPlotManager.h"

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/treectrl.h>
#include <wx/scrolwin.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/panel.h>

#include <wx/aui/aui.h>
#include <wx/aui/framemanager.h>
#include <wx/aui/dockart.h>
#include <wx/aui/floatpane.h>
#include <wx/aui/auibar.h>
#include <wx/aui/auibook.h>
#include <wx/aui/tabmdi.h>
///////////////////////////////////////////////////////////////////////////

wxSunPlotManager::wxSunPlotManager( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
    wxAuiNotebook* m_notebook = new wxAuiNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxAUI_NB_DEFAULT_STYLE );

	m_scrolled_window = new wxScrolledWindow( m_notebook, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );

    m_notebook->AddPage( m_scrolled_window, wxT("SunPlotManager"), true, wxNullBitmap );

//
////	wxFlexGridSizer* sizer_v;
////
////	sizer_v = new wxFlexGridSizer( 2, 1, 0, 0 );
////	sizer_v->AddGrowableCol( 1 );
////	sizer_v->AddGrowableRow( 1 );
////	sizer_v->SetFlexibleDirection( wxVERTICAL );
////	sizer_v->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
//
///// wxButtons
//
////	wxBoxSizer* h_sunplot_buttons;
////	h_sunplot_buttons = new wxBoxSizer( wxHORIZONTAL );
////
////	m_btn_new_scene = new wxButton( this, wxID_ANY, wxT("new"), wxDefaultPosition, wxDefaultSize, 0 );
////	m_btn_new_scene->SetMinSize( wxSize( 48,24 ) );
////	m_btn_load_scene = new wxButton( this, wxID_ANY, wxT("load"), wxDefaultPosition, wxDefaultSize, 0 );
////	m_btn_load_scene->SetMinSize( wxSize( 48,24 ) );
////	m_btn_save_scene = new wxButton( this, wxID_ANY, wxT("save"), wxDefaultPosition, wxDefaultSize, 0 );
////	m_btn_save_scene->SetMinSize( wxSize( 48,24 ) );
////	m_btn_add_shape = new wxButton( this, wxID_ANY, wxT("+"), wxDefaultPosition, wxDefaultSize, 0 );
////	m_btn_add_shape->SetMinSize( wxSize( 24,24 ) );
////	m_btn_shape_del = new wxButton( this, wxID_ANY, wxT("-"), wxDefaultPosition, wxDefaultSize, 0 );
////	m_btn_shape_del->SetMinSize( wxSize( 24,24 ) );
////	m_btn_shape_edit = new wxButton( this, wxID_ANY, wxT("edit"), wxDefaultPosition, wxDefaultSize, 0 );
////	m_btn_shape_edit->SetMinSize( wxSize( 48,24 ) );
////
////	h_sunplot_buttons->Add( m_btn_new_scene, 0, wxALIGN_CENTER_VERTICAL, 0 );
////	h_sunplot_buttons->Add( m_btn_load_scene, 0, wxALIGN_CENTER_VERTICAL, 0 );
////	h_sunplot_buttons->Add( m_btn_save_scene, 0, wxALIGN_CENTER_VERTICAL, 0 );
////	h_sunplot_buttons->Add( 0, 0, 1, wxALIGN_CENTER_VERTICAL|wxEXPAND, 0 );
////	h_sunplot_buttons->Add( m_btn_add_shape, 0, wxALIGN_CENTER_VERTICAL, 0 );
////	h_sunplot_buttons->Add( m_btn_shape_del, 0, wxALIGN_CENTER_VERTICAL, 0 );
////	h_sunplot_buttons->Add( m_btn_shape_edit, 0, wxALIGN_CENTER_VERTICAL, 0 );
////
////	sizer_v->Add( h_sunplot_buttons, 1, wxEXPAND, 5 );
//
///// wxTreeCtrl within wxScrolledWindow
//
//	m_scrolled_window->SetScrollRate( 5, 5 );
//
//	wxBoxSizer* sizer_h = new wxBoxSizer( wxVERTICAL );
//
//	m_treeview = new wxTreeCtrl( m_scrolled_window, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTR_DEFAULT_STYLE|wxTR_EXTENDED|wxTR_LINES_AT_ROOT|wxTR_MULTIPLE );
//
//    wxTreeItemData* rootData = NULL;
//    wxTreeItemData* itemData = NULL;
//    wxTreeItemId root = m_treeview->AddRoot( wxT("SunPlot: Dresden (13.2°, 51.2°)"), -1, -1, rootData );
//
//    wxTreeItemId item;
//    wxTreeItemId subitem;
//    item = m_treeview->AppendItem( root, wxT("Data"), -1, -1, itemData );
//    subitem = m_treeview->AppendItem( item, wxT("Location"), -1, -1, itemData );
//    subitem = m_treeview->AppendItem( item, wxT("Longitude"), -1, -1, itemData );
//    subitem = m_treeview->AppendItem( item, wxT("Latitude"), -1, -1, itemData );
//    subitem = m_treeview->AppendItem( item, wxT("JulianDay"), -1, -1, itemData );
//    subitem = m_treeview->AppendItem( item, wxT("Method"), -1, -1, itemData );
//    subitem = m_treeview->AppendItem( item, wxT("PointCount"), -1, -1, itemData );
//    subitem = m_treeview->AppendItem( item, wxT("CurveCount"), -1, -1, itemData );
//
//    item = m_treeview->AppendItem( root, wxT("LeftGrid : IMeshBuffer"), -1, -1, itemData );
//    item = m_treeview->AppendItem( root, wxT("RightGrid : IMeshBuffer"), -1, -1, itemData );
//    item = m_treeview->AppendItem( root, wxT("X-Axis : IMeshBuffer"), -1, -1, itemData );
//    item = m_treeview->AppendItem( root, wxT("Y-Axis : IMeshBuffer"), -1, -1, itemData );
//    item = m_treeview->AppendItem( root, wxT("Caption : IMeshBuffer"), -1, -1, itemData );
//    item = m_treeview->AppendItem( root, wxT("I"), -1, -1, itemData );
//
////    void AssignImageList(wxImageList* imageList)
////    bool Create(int width, int height, const bool mask = true, int initialCount = 1)
////    int Add(const wxBitmap& bitmap, const wxBitmap& mask = wxNullBitmap)
////    int Add(const wxBitmap& bitmap, const wxColour& maskColour)
////    int Add(const wxIcon& icon)
//
//	sizer_h->Add( m_treeview, 1, wxEXPAND, 2 );
////
//	m_scrolled_window->SetSizer( sizer_h );
//	m_scrolled_window->Layout();
//	sizer_h->Fit( m_scrolled_window );
////    sizer_v->Add( m_scrolled_window, 1, wxALL|wxEXPAND, 5 );
////
////    wxPanel* page_1 = new wxPanel( m_notebook, wxID_ANY );
////

//    m_notebook->AddPage( m_scrolled_window, wxT("SunPlotManager"), true, wxNullBitmap );
//    wxWindow* page = m_notebook->GetPage(0);
//    page->SetSizer( sizer_v );
    m_notebook->Layout();
//    sizer_v->Fit( page );
    m_notebook->Update();


}

wxSunPlotManager::~wxSunPlotManager()
{
}
