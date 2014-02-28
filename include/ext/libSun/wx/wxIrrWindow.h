#ifndef WX_IRRLICHT_DEVICE
#define WX_IRRLICHT_DEVICE

class wxIrrDevice;
class wxIrrWindow;

#include "irrTypedef.h"

#include <wx/wx.h>
#include <wx/window.h>
#include <irrlicht.h>

//typedef void* HWND;

// using wxWidgets 2.9.3

typedef GtkWidget* HWND;

class wxIrrDevice
{
	public:
		wxIrrDevice();
		wxIrrDevice( HWND hwnd, IrrVideoDriverType type=irr::video::EDT_OPENGL, bool bResizeable=true);
		~wxIrrDevice();

		IrrDevice *Create( HWND hwnd, IrrVideoDriverType type=irr::video::EDT_OPENGL, bool bResizeable=true);

		inline IrrDevice *GetHandle(void)
		{
            return Device;
        }
		inline irr::scene::ISceneManager *GetSceneManager(void)
		{
            return Device ? Device->getSceneManager() : NULL;
        }

		inline irr::video::IVideoDriver *GetVideoDriver(void)
		{
            return Device ? Device->getVideoDriver() : NULL;
        }

		virtual IrrCamera *AddCamera(
            IrrNode *parent=0,
            const IrrVec3f &position=IrrVec3f(0.0f,0.0f,0.0f), const IrrVec3f &lookat=IrrVec3f(0.0f,0.0f,1.0f), irr::s32 id=1);

	protected:
		IrrDevice *Device;
};

class wxIrrWindow : public wxWindow, public wxIrrDevice
{
	public:
		wxIrrWindow(wxWindow *parent, wxWindowID id = wxID_ANY, long style=wxTAB_TRAVERSAL, IrrVideoDriverType type=irr::video::EDT_OPENGL, bool bResizeable=true);
		~wxIrrWindow();

		void OnPaint(wxPaintEvent &event);
		void doUpdate();
		void OnSize(wxSizeEvent &event);
		void OnTimer(wxTimerEvent &event);
		void OnMouseMove(wxMouseEvent &event);
		void OnMouseLeftDown(wxMouseEvent &event);
		void OnMouseLeftUp(wxMouseEvent &event);

		virtual void OnSceneUpdate(void);

		inline void StartUpdate(int millisecs) { if (!m_timer.IsRunning()) m_timer.Start(millisecs); }
//		inline void StopUpdate(void) { m_timer.IsRunning() ? m_timer.Stop() : NULL; }
		inline void StopUpdate(void) { if ( m_timer.IsRunning() ) { m_timer.Stop();} }

		IrrCamera *AddCamera(IrrNode *parent=0, const IrrVec3f &position=IrrVec3f(0.0f,0.0f,0.0f), const IrrVec3f &lookat=IrrVec3f(0.0f,0.0f,1.0f), irr::s32 id=1, bool bsetcurrent=true);
//		IrrCamera *AddCamera(IrrNode *parent, IrrVec3f &position, IrrVec3f &lookat, irr::s32 id, bool bsetcurrent);

	DECLARE_EVENT_TABLE()

	protected:
		IrrCamera* Camera;

	private:
		wxTimer m_timer;
		IrrFont *font;
};

#endif
