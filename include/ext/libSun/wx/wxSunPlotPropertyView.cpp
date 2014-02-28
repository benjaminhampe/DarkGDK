#include "wxSunPlotPropertyView.h"


/// PropertyGrid

//EVT_PG_SELECTED (id, func)	Property is selected.
//EVT_PG_CHANGED (id, func)	Property value is modified.
//EVT_PG_CHANGING (id, func)	Property value is about to be changed. Use wxPropertyGridEvent::GetValue() to take a peek at the pending value, and wxPropertyGridEvent::Veto() to prevent change from taking place, if necessary.
//EVT_PG_HIGHLIGHTED (id, func)	Mouse moves over property. Event's property is NULL if hovered on area that is not a property.
//EVT_PG_RIGHT_CLICK (id, func)	Mouse right-clicked on a property.
//EVT_PG_DOUBLE_CLICK (id, func)	Mouse double-clicked on a property.
//EVT_PG_ITEM_COLLAPSED (id, func)	User collapses a property or category.
//EVT_PG_ITEM_EXPANDED (id, func)	User expands a property or category.
//EVT_PG_LABEL_EDIT_BEGIN (id, func)	User is about to begin editing a property label. You can veto this event to prevent the action.
//EVT_PG_LABEL_EDIT_ENDING (id, func)
//User is about to end editing of a property label. You can veto this event to prevent the action.
//
//EVT_BUTTON (id, func)	Button in a property editor was clicked. Only occurs if the property doesn't handle button clicks itself.
//EVT_TEXT (id, func)	wxTextCtrl based editor was updated (but property value was not yet modified)

BEGIN_EVENT_TABLE(wxSunPlotPropertyView, wxPanel)

END_EVENT_TABLE()

// irr::astro::CSunCurve* curve,

wxSunPlotPropertyView::wxSunPlotPropertyView( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
: wxPanel( parent, id, pos, size, style )
, m_curve( 0 )
{
    //ctor
	m_pmgr = new wxPropertyGridManager( this, id, wxDefaultPosition, wxDefaultSize, wxPGMAN_DEFAULT_STYLE|wxPG_SPLITTER_AUTO_CENTER|wxPG_TOOLBAR);
	m_pmgr->SetExtraStyle( wxPG_EX_MODE_BUTTONS );
	m_pmgr->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DDKSHADOW ) );
	m_pmgr->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

    wxPropertyGridPage* page = m_pmgr->AddPage(wxT("Page0"), wxPG_NULL_BITMAP );

/// build Object Properties

    wxPGProperty* p = 0;
    p = new wxBoolProperty("IsVisible", wxPG_LABEL, false ); page->Append( p );
    p = new wxBoolProperty("IsBackfaceCulling", wxPG_LABEL, false ); page->Append( p );
    p = new wxBoolProperty("IsTransparent", wxPG_LABEL, false ); page->Append( p );
    p = new wxBoolProperty("IsWireframe", wxPG_LABEL, false ); page->Append( p );
    p = new wxBoolProperty("IsLighting", wxPG_LABEL, false ); page->Append( p );
    p = new wxBoolProperty("IsFogEnable", wxPG_LABEL, false ); page->Append( p );
    p = new wxBoolProperty("IsAmbient", wxPG_LABEL, false ); page->Append( p );

{
    wxPropertyGridPage* page = m_pmgr->AddPage(wxT("Page2"), wxPG_NULL_BITMAP );
    p = new wxBoolProperty("IsVisible", wxPG_LABEL, false ); page->Append( p );
    p = new wxBoolProperty("IsBackfaceCulling", wxPG_LABEL, false ); page->Append( p );
    p = new wxBoolProperty("IsTransparent", wxPG_LABEL, false ); page->Append( p );
}

	wxBoxSizer* sizerV = new wxBoxSizer( wxVERTICAL );
	sizerV->Add( m_pmgr, 1, wxEXPAND | wxALL, 5 );
	this->SetSizer( sizerV );
	this->Layout();
}

wxSunPlotPropertyView::~wxSunPlotPropertyView()
{
    //dtor
}
