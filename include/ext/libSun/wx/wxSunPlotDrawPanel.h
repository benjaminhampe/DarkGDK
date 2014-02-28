#ifndef __WX_SUNPLOT_DRAW_PANEL_WX_H__
#define __WX_SUNPLOT_DRAW_PANEL_WX_H__

#include <wx/wx.h>

#include <irrlicht.h>

#include "../../CDateTime.h"
#include "../CSonnenstand.h"
#include "../CSunCurve.h"
#include "../CSunData.h"

class wxSunPlotDrawPanel : public wxPanel
{

public:
    wxSunPlotDrawPanel(wxFrame* parent);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();

    void render(wxDC& dc);

    void createViewFromData( irr::CSunData* doc = 0 );

    // some useful events
    /*
     void mouseMoved(wxMouseEvent& event);
     void mouseDown(wxMouseEvent& event);
     void mouseWheelMoved(wxMouseEvent& event);
     void mouseReleased(wxMouseEvent& event);
     void rightClick(wxMouseEvent& event);
     void mouseLeftWindow(wxMouseEvent& event);
     void keyPressed(wxKeyEvent& event);
     void keyReleased(wxKeyEvent& event);
     */

    DECLARE_EVENT_TABLE()

private:
    bool IsReady;

};


#endif
