#include "wxSunPlotGLCanvas.h"

#include <wx/wx.h>
#include <wx/sizer.h>
#include <wx/glcanvas.h>

// include OpenGL
#ifdef __WXMAC__
#include "OpenGL/glu.h"
#include "OpenGL/gl.h"
#else
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include "irrGL.h"

BEGIN_EVENT_TABLE(wxSunPlotGLCanvas, wxGLCanvas)
    EVT_MOTION(wxSunPlotGLCanvas::mouseMoved)
    EVT_LEFT_DOWN(wxSunPlotGLCanvas::mouseDown)
    EVT_LEFT_UP(wxSunPlotGLCanvas::mouseReleased)
    EVT_RIGHT_DOWN(wxSunPlotGLCanvas::rightClick)
    EVT_LEAVE_WINDOW(wxSunPlotGLCanvas::mouseLeftWindow)
    EVT_SIZE(wxSunPlotGLCanvas::resized)
    EVT_KEY_DOWN(wxSunPlotGLCanvas::keyPressed)
    EVT_KEY_UP(wxSunPlotGLCanvas::keyReleased)
    EVT_MOUSEWHEEL(wxSunPlotGLCanvas::mouseWheelMoved)
    EVT_PAINT(wxSunPlotGLCanvas::render)
END_EVENT_TABLE()


// some useful events to use
void wxSunPlotGLCanvas::mouseMoved(wxMouseEvent& event)
{

}

void wxSunPlotGLCanvas::mouseDown(wxMouseEvent& event)
{

}
void wxSunPlotGLCanvas::mouseWheelMoved(wxMouseEvent& event)
{

}
void wxSunPlotGLCanvas::mouseReleased(wxMouseEvent& event)
{

}
void wxSunPlotGLCanvas::rightClick(wxMouseEvent& event)
{

}
void wxSunPlotGLCanvas::mouseLeftWindow(wxMouseEvent& event)
{

}
void wxSunPlotGLCanvas::keyPressed(wxKeyEvent& event)
{

}
void wxSunPlotGLCanvas::keyReleased(wxKeyEvent& event)
{

}

// Vertices and faces of a simple cube to demonstrate 3D render
// source: http://www.opengl.org/resources/code/samples/glut_examples/examples/cube.c
GLfloat v[8][3];
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
    {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
    {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };



wxSunPlotGLCanvas::wxSunPlotGLCanvas(wxFrame* parent, int* args) :
    wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
	m_context = new wxGLContext(this);
    // prepare a simple cube to demonstrate 3D render
    // source: http://www.opengl.org/resources/code/samples/glut_examples/examples/cube.c
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -1;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = 1;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -1;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = 1;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = 1;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = -1;

    // To avoid flashing on MSW
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

wxSunPlotGLCanvas::~wxSunPlotGLCanvas()
{
	delete m_context;
}

void wxSunPlotGLCanvas::resized(wxSizeEvent& evt)
{
	wxGLCanvas::OnSize(evt);

    prepare3DViewport();

    Refresh();

}


void wxSunPlotGLCanvas::setCameraProjectionMatrix( const IrrMatrix4& m ) //int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y)
{

}



int wxSunPlotGLCanvas::getWidth()
{
    return GetSize().x;
}

int wxSunPlotGLCanvas::getHeight()
{
    return GetSize().y;
}




void wxSunPlotGLCanvas::render( wxPaintEvent& evt )
{
    if(!IsShown()) return;

    wxGLCanvas::SetCurrent(*m_context);
    wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


//    // ------------- draw some 2D ----------------
//    prepare2DViewport(0,0,getWidth()/2, getHeight());
//    glLoadIdentity();
//
//    // white background
//    glColor4f(1, 1, 1, 1);
//    glBegin(GL_QUADS);
//    glVertex3f(0,0,0);
//    glVertex3f(getWidth(),0,0);
//    glVertex3f(getWidth(),getHeight(),0);
//    glVertex3f(0,getHeight(),0);
//    glEnd();
//
//    // red square
//    glColor4f(1, 0, 0, 1);
//    glBegin(GL_QUADS);
//    glVertex3f(getWidth()/8, getHeight()/3, 0);
//    glVertex3f(getWidth()*3/8, getHeight()/3, 0);
//    glVertex3f(getWidth()*3/8, getHeight()*2/3, 0);
//    glVertex3f(getWidth()/8, getHeight()*2/3, 0);
//    glEnd();

    // ------------- settings ----------------
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black Background
    glClearDepth(1.0f);	// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST); // Enables Depth Testing
    glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glEnable(GL_COLOR_MATERIAL);

    // ------------- draw some 3D ----------------

    prepare3DViewport();

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
// glRotatef(orbitDegrees, 0.f, 1.f, 0.f);/* orbit the Y axis
// ...where orbitDegrees is derived from mouse motion

//    glColor4f(0, 0, 0, 0);  // N
//    glColor4f(1, 1, 1, 1);  // W
//    glColor4f(0, 0, 0, 1);  // S
//    glColor4f(1, 0, 0, 1);  // R
//    glColor4f(0, 1, 0, 1);  // G
//    glColor4f(0, 0, 1, 1);  // B
//    glColor4f(1, 1, 0, 1);  // Y

    glLoadIdentity();
    glTranslatef(0,-10,0);

    irr::GL irrGL;
    irrGL.drawGridXZ( IrrColor(255,255,255,255) );

    glPopMatrix();

/// render red cube
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0,0,10);
    glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
    glColor4f(1, 0, 0, 1); // R
    for (int i = 0; i < 6; i++)
    {
        glBegin(GL_LINE_STRIP);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glEnd();
    }
    glPopMatrix();

/// draw RGB 3d-coord-system
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0,0,0);
    glBegin(GL_LINES);
        glVertex3f(0,0,0);
        glVertex3f(1,0,0);
        glColor4f(0, 1, 0, 1);  // G
        glVertex3f(0,0,0);
        glVertex3f(0,1,0);
        glColor4f(0, 0, 1, 1);  // B
        glVertex3f(0,0,0);
        glVertex3f(0,0,1);
    glEnd();
    glPopMatrix();

/// draw yellow cube
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0,0,2);
    glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
    glColor4f(1,1,0,1); // yellow
    for (int i = 0; i < 6; i++)
    {
        glBegin(GL_LINE_STRIP);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glEnd();
    }
    glPopMatrix();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0,0,10);

    irrGL.drawRect(
        IrrRectf(0,0,200,50),
        IrrColor(255,255,255,255), IrrColor(255,255,0,0),
        IrrColor(255,0,255,0), IrrColor(255,0,0,255),
        5.0f, 0xffff, 1);

    glPopMatrix();
    glFlush();
    SwapBuffers();
}


void wxSunPlotGLCanvas::setViewport( irr::f32 x, irr::f32 y, irr::f32 w, irr::f32 h )
{
    m_viewport = IrrRectf( irr::core::position2df(x,y), IrrDim2f(w,h) );
}

IrrRectf wxSunPlotGLCanvas::getViewport( ) const
{
    return m_viewport;
}
