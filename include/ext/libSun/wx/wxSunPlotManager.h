///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __WXSUNPLOTEDITOR_H__
#define __WXSUNPLOTEDITOR_H__

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

///////////////////////////////////////////////////////////////////////////////
/// Class wxSunPlotManager
///////////////////////////////////////////////////////////////////////////////
class wxSunPlotManager : public wxPanel
{
	private:

	protected:
		wxButton* m_btn_new_scene;
		wxButton* m_btn_load_scene;
		wxButton* m_btn_save_scene;
		wxButton* m_btn_add_shape;
		wxButton* m_btn_shape_del;
		wxButton* m_btn_shape_edit;

		wxScrolledWindow* m_scrolled_window;
		wxTreeCtrl* m_treeview;

//		wxStaticText* m_static000011;
//		wxTextCtrl* m_edt_plot_name;
//		wxStaticText* m_static0000111;
//		wxTextCtrl* m_edt_plot_root;
//		wxStaticText* m_static00001;
//		wxTextCtrl* m_textCtrl37;
//		wxStaticText* m_edt_buffer_count;
//		wxTextCtrl* m_textCtrl38;
//		wxStaticText* m_edt_buffer_count1;
//		wxTextCtrl* m_textCtrl381;
//		wxStaticText* m_static004;
//		wxTextCtrl* m_edt_index_count;

	public:

		wxSunPlotManager( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxTAB_TRAVERSAL );
		~wxSunPlotManager();

};

#endif //__WXSUNPLOTEDITOR_H__
