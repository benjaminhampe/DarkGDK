#ifndef __WX_SUNGUI_CREATOR_H__
#define __WX_SUNGUI_CREATOR_H__

#include <wx/wx.h>
#include <wx/datetime.h>
#include <wx/grid.h>
#include <wx/treectrl.h>
#include <wx/spinctrl.h>
#include <wx/artprov.h>
#include <wx/image.h>
#include <wx/colordlg.h>
#include <wx/clipbrd.h>
#include <wx/xrc/xmlres.h>

#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/manager.h>
#include <wx/propgrid/advprops.h>

#include <irrlicht.h>

#include "../../CDateTime.h"
#include "../CSonnenstand.h"
#include "../CSunData.h"
#include "../CSunCurve.h"


class wxSunPlotPropertyView : public wxPanel
{
public:
    wxSunPlotPropertyView( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL );

    ~wxSunPlotPropertyView();

public:
    void clear();

//    irr::u32 getPropertyCount();
//    irr::core::stringc getStringUTF8( const wxString& id );
//    irr::video::SColor getColor( const wxString& id );
//    irr::core::dimension2du getDimension2u( const wxString& id );
//    irr::core::dimension2df getDimension2f( const wxString& id );
//    irr::core::vector2d<irr::s32> getVector2i( const wxString& id );
//    irr::core::vector2d<irr::f32> getVector2f( const wxString& id );
//    irr::core::vector3d<irr::f32> getVector3f( const wxString& id );
//    irr::core::recti getRecti( const wxString& id );
//    irr::core::rectf getRectf( const wxString& id );
//    wxDateTime getDateTime( const wxString& id );
//
//    void addCircleProperty( const wxString& id );
//    void addStringProperty( const wxString& id, const wxString& init = wxT("0") );
//    void addColorProperty( const wxString& id, const irr::video::SColor& init = irr::video::SColor(255,255,255,255) );
//    void addVectorProperty( const wxString& id, const irr::core::vector3df& init = irr::core::vector3df(0,0,0) );
//    void addDateProperty( const wxString& id, const irr::ITimer::RealTimeDate& rTimeDate );
//    void addTimeProperty( const wxString& id );
//    void addBoolProperty( const wxString& id );
//    void addIntProperty( const wxString& id );
//    void addUIntProperty( const wxString& id );



protected:
    wxPropertyGridManager* m_pmgr;
    irr::astro::CSunCurve* m_curve;

private:

public:
    DECLARE_EVENT_TABLE();
};

#endif // WXPROPGRIDCREATORTOOLS_H
