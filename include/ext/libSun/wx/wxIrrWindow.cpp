#include "wxIrrWindow.h"

#include <gtk/gtk.h>
#include <gdk/gdkx.h>

wxIrrDevice::wxIrrDevice()
{
	Device = NULL;
}

wxIrrDevice::wxIrrDevice(HWND hwnd, IrrVideoDriverType type, bool bResizeable)
{
    Create(hwnd, type, bResizeable);
}

wxIrrDevice::~wxIrrDevice()
{
	if ( Device )
	{
		Device->closeDevice();
		Device->drop();
	}
}

IrrDevice *wxIrrDevice::Create( HWND hwnd, IrrVideoDriverType type, bool bResizeable)
{
	if (Device)
		return Device;

	IrrDeviceParams params;

//	ExposedData.OpenGLLinux.X11Context = glXGetCurrentContext();
//	ExposedData.OpenGLLinux.X11Display = glXGetCurrentDisplay();
//	ExposedData.OpenGLLinux.X11Window = (unsigned long)Params.WindowId;
//	Drawable = glXGetCurrentDrawable();
//	X11Display = (Display*)ExposedData.OpenGLLinux.X11Display;
//	extGlSwapInterval(Params.Vsync ? 1 : 0);

	GtkWidget *widget = hwnd;
    Window xid = gdk_x11_drawable_get_xid( gtk_widget_get_window(widget));

// It is C because Gtk+ is a C API, but it is also C++, so there should be no problem.

//And don't forget to !

	params.WindowId = reinterpret_cast<void *>( (unsigned long)xid );
	params.DriverType = type;
    params.Fullscreen = false;
    params.LoggingLevel = irr::ELL_INFORMATION;
    params.Doublebuffer = true;

	Device = irr::createDeviceEx(params);

	if (Device)
	{
		Device->setResizable( bResizeable );
	}

	return Device;
}

IrrCamera *wxIrrDevice::AddCamera( IrrNode *parent, const IrrVec3f &position, const IrrVec3f &lookat, s32 id)
{
	IrrSceneManager *smgr=GetSceneManager();

	if (smgr)
		return (IrrCamera*)smgr->addCameraSceneNode( parent, position, lookat );
	else
		return NULL;
}


////////////////////////////////////////////////////////////////////////////////

BEGIN_EVENT_TABLE(wxIrrWindow, wxWindow)
	EVT_PAINT(wxIrrWindow::OnPaint)
	EVT_SIZE(wxIrrWindow::OnSize)
	EVT_TIMER( wxID_ANY, wxIrrWindow::OnTimer)
	EVT_MOTION( wxIrrWindow::OnMouseMove)
	EVT_LEFT_DOWN(wxIrrWindow::OnMouseLeftDown)
	EVT_LEFT_UP(wxIrrWindow::OnMouseLeftUp)
END_EVENT_TABLE()

wxIrrWindow::wxIrrWindow(wxWindow *parent, wxWindowID id, long style, IrrVideoDriverType type, bool bResizeable)
:	wxWindow( parent, id, wxDefaultPosition, wxDefaultSize, style )
{
	Camera = NULL;
	Device = wxIrrDevice::Create( wxWindow::GetHandle(), type, bResizeable );
    m_timer.SetOwner(this, wxID_ANY);
	// font = Device->getGUIEnvironment()->getBuiltInFont();
	// m_viewportmanager.SetFont(font);
}

wxIrrWindow::~wxIrrWindow()
{
	if ( Camera )
         Camera->remove();
}

void wxIrrWindow::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc( this );
    doUpdate();
	event.Skip();
}
void wxIrrWindow::doUpdate()
{
	if ( Device )
	{
		IrrVideoDriver *driver = Device->getVideoDriver();
		IrrSceneManager *smgr = Device->getSceneManager();
        IrrGUIEnvironment* env = Device->getGUIEnvironment();
        IrrCamera* camera = smgr->getActiveCamera();

		if ( driver && smgr && camera && env)
		{
			driver->beginScene(true, true, IrrColor(255,0,0,0) );

			smgr->drawAll();

			env->drawAll();
//			m_viewportmanager.OnPaint(driver, scenemgr, Camera);
			driver->endScene();
		}
	}
}
void wxIrrWindow::OnSize(wxSizeEvent &event)
{
	// resize viewports
//	m_viewportmanager.OnSize(event);
	if ( Device )
	{
		IrrVideoDriver *driver=GetVideoDriver();

		if ( driver )
		{
			driver->OnResize( IrrDim2u(GetClientSize().GetWidth(), GetClientSize().GetHeight()) );
			if ( !m_timer.IsRunning() )
				Update();
		}
	}
	event.Skip();
}

void wxIrrWindow::OnTimer(wxTimerEvent &event)
{
	OnSceneUpdate();
	Refresh( false );
	event.Skip();
}

void wxIrrWindow::OnMouseMove(wxMouseEvent &event)
{
//	m_viewportmanager.OnMouseMove(event);
//	if ( m_viewportmanager.NeedRefresh() && (!m_timer.IsRunning()) )
//		Refresh(false);
	event.Skip();
}

void wxIrrWindow::OnMouseLeftDown(wxMouseEvent &event)
{
//	m_viewportmanager.OnMouseLeftDown(event);
//	if ( m_viewportmanager.NeedRefresh() && (!m_timer.IsRunning()) )
//		Refresh(false);
	event.Skip();
}

void wxIrrWindow::OnMouseLeftUp(wxMouseEvent &event)
{
//	m_viewportmanager.OnMouseLeftUp(event);
}

//
// Do the update of your scene here
//
void wxIrrWindow::OnSceneUpdate(void)
{
	IrrSceneManager *scene=GetSceneManager();

	if ( scene )
	{
		IrrNode *cube=scene->getSceneNodeFromId( 1 );

		if (cube)
		{
			IrrVec3f yaw=cube->getRotation();
            yaw.X += 1.0;
            yaw.Y += 0.5;
            yaw.Z += 0.25;
			cube->setRotation( yaw );
		}
	}
}

IrrCamera *wxIrrWindow::AddCamera(IrrNode *parent, const IrrVec3f &position, const IrrVec3f &lookat, s32 id, bool bsetcurrent)
{

	IrrCamera *newcamera=NULL;
    IrrVec3f pos = position;
    IrrVec3f look = lookat;
	if (Device)
	{
//		newcamera = wxIrrDevice::AddCamera(parent, position, lookat, id);
		newcamera = wxIrrDevice::AddCamera(parent, pos, look, id);
		if ( bsetcurrent )
			Camera = newcamera;
	}
	return newcamera;
}
