#include "wxSunPlotDrawPanel.h"

#include <wx/wx.h>


BEGIN_EVENT_TABLE(wxSunPlotDrawPanel, wxPanel)
// some useful events
/*
 EVT_MOTION(wxSunPlotDrawPanel::mouseMoved)
 EVT_LEFT_DOWN(wxSunPlotDrawPanel::mouseDown)
 EVT_LEFT_UP(wxSunPlotDrawPanel::mouseReleased)
 EVT_RIGHT_DOWN(wxSunPlotDrawPanel::rightClick)
 EVT_LEAVE_WINDOW(wxSunPlotDrawPanel::mouseLeftWindow)
 EVT_KEY_DOWN(wxSunPlotDrawPanel::keyPressed)
 EVT_KEY_UP(wxSunPlotDrawPanel::keyReleased)
 EVT_MOUSEWHEEL(wxSunPlotDrawPanel::mouseWheelMoved)
 */

// catch paint events
EVT_PAINT(wxSunPlotDrawPanel::paintEvent)

END_EVENT_TABLE()

// some useful events
/*
 void wxSunPlotDrawPanel::mouseMoved(wxMouseEvent& event) {}
 void wxSunPlotDrawPanel::mouseDown(wxMouseEvent& event) {}
 void wxSunPlotDrawPanel::mouseWheelMoved(wxMouseEvent& event) {}
 void wxSunPlotDrawPanel::mouseReleased(wxMouseEvent& event) {}
 void wxSunPlotDrawPanel::rightClick(wxMouseEvent& event) {}
 void wxSunPlotDrawPanel::mouseLeftWindow(wxMouseEvent& event) {}
 void wxSunPlotDrawPanel::keyPressed(wxKeyEvent& event) {}
 void wxSunPlotDrawPanel::keyReleased(wxKeyEvent& event) {}
 */


/*
 * Here we do the actual rendering. I put it in a separate
 * method so that it can work no matter what type of DC
 * (e.g. wxPaintDC or wxClientDC) is used.
 */

void wxSunPlotDrawPanel::createViewFromData( irr::CSunData* doc )
{
    if (!doc)
        return;

    irr::u32 curveCount = doc->getCurveCount();
}

void wxSunPlotDrawPanel::render( wxDC& dc )
{
    long int w = dc.GetSize().GetWidth();
    long int h = dc.GetSize().GetHeight();

    // dc.SetPen(*wxYELLOW_BRUSH); // blue filling
    dc.SetBrush(*wxWHITE_BRUSH); // blue filling
    dc.DrawRectangle( wxPoint(0,0), wxSize(w,h) );

    // draw a circle RGBA
    wxBrush* brush = new wxBrush( wxColour(255,255,255,255), wxBRUSHSTYLE_TRANSPARENT );
    dc.SetBrush( *brush ); // green filling

    dc.SetPen( wxPen( wxColor(0,0,0), 1 ) ); // 5-pixels-thick red outline
    dc.DrawRectangle( wxPoint(0,0), wxSize(w,h) );

    dc.SetPen( wxPen( wxColor(255,0,0), 1 ) ); // 1-pixels-thick red outline
    dc.DrawRoundedRectangle( wxPoint(0,0), wxSize(w,h), 10.0);

    // draw some text
    dc.SetPen( wxPen( wxColor(0,0,0), 1 ) ); // 1-pixels-thick red outline
    dc.DrawText(wxT("Testing"), 0, 0);

    dc.DrawCircle( wxPoint(w/2,h/2), std::min<int>(w/2,h/2) );

    // Look at the wxDC docs to learn how to draw other stuff
}

wxSunPlotDrawPanel::wxSunPlotDrawPanel(wxFrame* parent) :
wxPanel(parent)
{
}

/*
 * Called by the system of by wxWidgets when the panel needs
 * to be redrawn. You can also trigger this call by
 * calling Refresh()/Update().
 */

void wxSunPlotDrawPanel::paintEvent(wxPaintEvent & evt)
{
    wxPaintDC dc(this);
    render(dc);
}

/*
 * Alternatively, you can use a clientDC to paint on the panel
 * at any time. Using this generally does not free you from
 * catching paint events, since it is possible that e.g. the window
 * manager throws away your drawing when the window comes to the
 * background, and expects you will redraw it when the window comes
 * back (by sending a paint event).
 *
 * In most cases, this will not be needed at all; simply handling
 * paint events and calling Refresh() when a refresh is needed
 * will do the job.
 */
void wxSunPlotDrawPanel::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}
