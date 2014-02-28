#ifndef WXPROPGRIDCREATORTOOLS_H
#define WXPROPGRIDCREATORTOOLS_H

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
//#include <irrTypes.h>
//#include <irrString.h>
//#include <irrArray.h>
//#include <vector2d.h>
//#include <vector3d.h>
//#include <matrix4.h>
//#include <CMeshBuffer.h>
//#include <SMeshBuffer.h>
//#include <SMeshBufferLightMap.h>
//#include <SMeshBufferTangents.h>
//#include <SMesh.h>
//#include <ISceneNode.h>
//#include <IMeshSceneNode.h>
//#include <IAnimatedMeshSceneNode.h>


// -- property grid manager --

class wxPGTool : public wxPanel
{
private:

protected:
    wxPropertyGridManager* m_pmgr;

public:

    wxPGTool( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL );
    ~wxPGTool();

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



    DECLARE_EVENT_TABLE();
};

#endif // WXPROPGRIDCREATORTOOLS_H
