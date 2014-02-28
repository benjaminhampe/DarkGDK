#ifndef __WX_SUNPLOT_OPENGL_DRAW_PANEL_H__
#define __WX_SUNPLOT_OPENGL_DRAW_PANEL_H__

#include <wx/wx.h>

#include <wx/glcanvas.h>

#include <irrlicht.h>

#include "irrTypedef.h"

class wxSunPlotGLCanvas : public wxGLCanvas
{
public:
	wxSunPlotGLCanvas(wxFrame* parent, int* args);

	virtual ~wxSunPlotGLCanvas();

	void resized(wxSizeEvent& evt);

	int getWidth();
	int getHeight();

	void render(wxPaintEvent& evt);
	void prepare3DViewport(); // int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);
	void prepare2DViewport(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y);

	// events
	void mouseMoved(wxMouseEvent& event);
	void mouseDown(wxMouseEvent& event);
	void mouseWheelMoved(wxMouseEvent& event);
	void mouseReleased(wxMouseEvent& event);
	void rightClick(wxMouseEvent& event);
	void mouseLeftWindow(wxMouseEvent& event);
	void keyPressed(wxKeyEvent& event);
	void keyReleased(wxKeyEvent& event);

/// irrlicht - interface

    void setCameraProjectionMatrix( const IrrMatrix4& m );

    void setViewport( irr::f32 x, irr::f32 y, irr::f32 w, irr::f32 h );

    IrrRectf getViewport( ) const;

	DECLARE_EVENT_TABLE()

private:
    wxGLContext*	m_context;
    IrrRectf         m_viewport;
};

#endif // __WX_BASIC_OPENGL_PANEL_H__
