#include "tinyDarkGDK.h"

#ifdef _IRR_WINDOWS_ || _IRR_WINDOWS_API_
	#include <windows.h>
#endif // _IRR_WINDOWS_

namespace irr
{

///@brief print program's help text
void dbPrintHelp( )
{
	dbPRINT("cpp_parser -absf INPUT-FILE\n");
	dbPRINT("[OPTIONS] absf\n");
	dbPRINT("-absf\n");
	dbPRINT("-absf\n");
	dbPRINT("-absf\n");
	dbPRINT("-absf\n");
	dbPRINT("[OPTIONS] absf\n");
	dbPRINT("-absf\n");
	dbPRINT("-absf\n");
	dbPRINT("-absf\n");
	dbPRINT("-absf\n");
	dbPRINT("cpp_parser (c) 2008-2014 benjaminhampe@gmx.de\n");
}


///@brief print arguments given to program
void dbPrintCommandLine()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	dbPRINT( "CommandLine ArgumentCount = %d\n", app.Argc );
	for ( s32 i=0; i < app.Argc; i++)
		dbPRINT( "CommandLine Argv[%d] = %s\n", i, app.Argv[i] );
}

///@brief create window and irrlicht-device
void dbDarkGDK(s32 argc, c8** argv)
{
	dbPRINT("dbDarkGDK()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	app.Argc = argc;
	app.Argv = argv;
	app.SyncRate = 0;
	app.SyncWait = 0;
	app.ClearColor = video::SColor(255,0,0,255);
	app.TextForeColor = video::SColor(255,255,255,255);
	app.TextBackColor = video::SColor(255,0,0,0);
	app.DesktopSize = core::dimension2du( 640, 480 );
	app.NullParam.LoggingLevel = ELL_NONE;
	app.NullParam.DriverType = video::EDT_NULL;
	app.Param.LoggingLevel = ELL_INFORMATION;
	app.Param.Fullscreen = false;
	app.Param.WindowSize = app.DesktopSize;
	app.Param.WindowPosition = core::position2di( 0, 0 );
	app.Param.DriverType = video::EDT_BURNINGSVIDEO;
	app.Param.Doublebuffer = true;

	app.NullDevice = createDeviceEx( app.NullParam );
	if (!app.NullDevice)
	{
		printf("Error: Could not create NullDevice, something is broken!\n");
	}
	else
	{
		// get desktop size
		app.DesktopSize = app.NullDevice->getVideoModeList()->getDesktopResolution();

		// set window bits
		app.Param.Bits = app.NullDevice->getVideoModeList()->getDesktopDepth();

		// set window size
		app.Param.WindowSize = app.DesktopSize;
		app.Param.WindowSize -= core::dimension2du(64,128);

		// set window pos
		s32 x = (s32)((app.DesktopSize.Width - app.Param.WindowSize.Width) >> 1);
		s32 y = (s32)((app.DesktopSize.Height - app.Param.WindowSize.Height) >> 1);
		app.Param.WindowPosition = core::position2di(x,y);

		if (app.NullDevice->isDriverSupported(video::EDT_OPENGL))
		{
			app.Param.DriverType = video::EDT_OPENGL;
			app.Param.AntiAlias = video::EAAM_QUALITY;
			app.Param.Vsync = false;
			// param.ZBufferBits = 32;
			// param.Stencilbuffer = true;
			// param.WithAlphaChannel = false;
		}
	}

	/// [1] create OpenGL-Device
	app.Device = createDeviceEx( app.Param);
	if (!app.Device)
	{
		exit(0);
	}

	app.Device->setResizable( true );
	app.Time_Start = app.Device->getTimer()->getTime();
	app.Time_Now = app.Time_Start;
	app.Time_Last = app.Time_Start;
//	app.Time_Wait_Window_Title_Update = 200;
//	app.Time_Last_Window_Title_Update = app.Time_Start;

	/// set event-receiver
	app.Device->setEventReceiver( &app );
	app.Device->setWindowCaption( core::stringw( app.Title ).c_str() );

	printf("EventReceiver attached to device\n");


	/// get pointer and stuff
	gui::IGUIEnvironment* env = app.Device->getGUIEnvironment();
	video::IVideoDriver* driver = app.Device->getVideoDriver();
//	scene::ISceneManager* smgr = app.Device->getSceneManager();
//	gui::ICursorControl* cursor = app.Device->getCursorControl();
//	io::IFileSystem* files = app.Device->getFileSystem();

	/// skin & font
//	gui::IGUIElement* rootElement = env->getRootGUIElement();
	gui::IGUISkin* skin = env->createSkin( gui::EGST_BURNING_SKIN );
//	db::setSkinColorsBlackStyle( skin );

	gui::IGUIFont* font = 0; // env->getFont( "../../media/fontcourier.bmp");
	gui::IGUIFont* fontWinCap = 0; // env->getFont( "../../media/lucida.png");

	if (!font)
		font = env->getBuiltInFont();

	if (!fontWinCap)
		fontWinCap = env->getBuiltInFont();

	skin->setFont( font, gui::EGDF_DEFAULT );
	skin->setFont( fontWinCap, gui::EGDF_WINDOW );
	env->setSkin( skin );

	app.Font = skin->getFont( gui::EGDF_DEFAULT );

	app.ScreenSize = driver->getScreenSize();

	app.ScreenRect = core::recti( 0,11*app.ScreenSize.Height/12,
								app.ScreenSize.Width-1, app.ScreenSize.Height-1);

}

///@brief
bool dbLoopGDK()
{
	dbPRINT("dbLoopGDK()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	IrrlichtDevice* device = app.Device;

	if (!device) return false;

	/// empty irrlicht message loop
	if (!device->run()) return false;

	ITimer* timer = device->getTimer();

	/// get current time
	app.Time_Now = timer->getTime();

	if (app.Time_Now >= app.Time_Last + 1000 )
	{
		app.FPS_Now = app.FPS_Count;
		app.FPS_Count = 0;
		if (app.FPS_Min > app.FPS_Now)
			app.FPS_Min = app.FPS_Now;
		if (app.FPS_Max < app.FPS_Now)
			app.FPS_Max = app.FPS_Now;
		app.Time_Last = timer->getTime();
	}

	video::IVideoDriver* driver = device->getVideoDriver();

	/// check resize-event
	if ( app.ScreenSize != driver->getScreenSize() )
	{
		app.ScreenSize = driver->getScreenSize();

		app.ScreenRect = core::recti( 0, 0, app.ScreenSize.Width-1, app.ScreenSize.Height-1);

		driver->OnResize( app.ScreenSize );

		/// resize aspect ratio of current active camera

		scene::ISceneManager* smgr = device->getSceneManager();
		scene::ICameraSceneNode*  camera = smgr->getActiveCamera();
		if ( camera )
		{
			app.CurrentCamera = camera;

			camera->setAspectRatio( (f32)app.ScreenSize.Width / (f32)app.ScreenSize.Width );

		}
	}

	return true;
}

///@brief
u32 dbTimer()
{
	dbPRINT("dbTimer()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return 0;

    return app.Device->getTimer()->getTime();
}

///@brief
u32 dbPerfTimer()
{
	dbPRINT("dbPerfTimer()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return 0;

    return app.Device->getTimer()->getRealTime();
}

///@brief
u32 dbGetFrameCount()
{
	dbPRINT("dbGetFrameCount()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	return app.FrameCount;
}

///@brief
u32 dbGetFPS()
{
	dbPRINT("dbGetFPS()\n");
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	return app.FPS_Now;
}

///@brief
u32 dbGetFPSMin()
{
	dbPRINT("dbGetFPSMin()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	return app.FPS_Min;
}

///@brief
u32 dbGetFPSMax()
{
	dbPRINT("dbGetFPSMax()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	return app.FPS_Max;
}

///@brief
u32 dbGetFPSAverage()
{
	dbPRINT("dbGetFPSAverage()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	return app.FPS_Avg;
}

///@brief
u32 dbScreenFPS()
{
	dbPRINT("dbScreenFPS()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	IrrlichtDevice* device = (app.Device) ? app.Device : ( (app.NullDevice) ? app.NullDevice : 0 );
	if (!device)
		return 0;

    return (u32)device->getVideoDriver()->getFPS();
}

///@brief
u32 dbDesktopWidth()
{
	dbPRINT("dbDesktopWidth()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.NullDevice)
		return 0;

    return app.NullDevice->getVideoModeList()->getDesktopResolution().Width;
}

///@brief
u32 dbDesktopHeight()
{
	dbPRINT("dbDesktopHeight()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.NullDevice)
		return 0;

    return app.NullDevice->getVideoModeList()->getDesktopResolution().Height;
}

///@brief
u32 dbDesktopDepth()
{
	dbPRINT("dbDesktopDepth()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.NullDevice)
		return 0;

    return app.NullDevice->getVideoModeList()->getDesktopDepth();
}

///@brief dbScreenWidth() - Get Width of MainWindow
u32 dbScreenWidth()
{
	dbPRINT("dbScreenWidth()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return 0;

    return app.Device->getVideoDriver()->getScreenSize().Width;
}

///@brief dbScreenHeight() - Get Height of MainWindow
u32 dbScreenHeight()
{
	dbPRINT("dbScreenHeight()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return 0;

    return app.Device->getVideoDriver()->getScreenSize().Height;
}

///@brief dbScreenDepth() - Get BitsPerPixel from MainWindow ColorFormat
u32 dbScreenDepth()
{
	dbPRINT("dbScreenDepth()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return 0;

    return video::IImage::getBitsPerPixelFromFormat( app.Device->getVideoDriver()->getColorFormat() );
}

///@brief
bool dbSetDisplayMode( u32 w, u32 h, u32 bpp, bool fullscreen, bool vSync, bool antiAlias, bool anisotropFilter )
{
	dbPRINT("dbSetDisplayMode(dbSetDisplayMode( %d, %d, %d, %s, %s, %d, %,d)\n", w, h, bpp, (fullscreen)?"true":"false", (vSync)?"true":"false",antiAlias, anisotropFilter);

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
	{
		dbERROR("dbSetDisplayMode() - Invalid pointer IrrlichtDevice\n");
		return false;
	}

	video::IVideoDriver* driver = app.Device->getVideoDriver();
	core::dimension2du screenSize = driver->getScreenSize();
	driver->OnResize( core::dimension2du(w,h) );

	if (driver->getScreenSize() == screenSize)
	{
		dbERROR("dbSetDisplayMode() - No settings changed\n");
		return false;
	}

	return true;
}

///@brief
void dbSync()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	if (!app.Device)
		return;

	// ITimer* timer = app.Device->getTimer();

	if (app.Device->isWindowActive())
	{

		video::IVideoDriver* driver = app.Device->getVideoDriver();

		scene::ISceneManager* smgr = app.Device->getSceneManager();

		gui::IGUIEnvironment* env = app.Device->getGUIEnvironment();


	//	if (Device->isWindowFocused())
	//	{

		driver->beginScene(true, true, app.ClearColor);

		smgr->drawAll();

		env->drawAll();

		/// Draw Texts
		for (u32 i=0; i < app.Texts.size(); i++)
		{
			const DarkGDK_SText2d& txt = app.Texts[i];

			if (txt.BGColor.getAlpha() > 0)
				driver->draw2DRectangle( txt.BGColor, txt.Position );

			txt.Font->draw( txt.Text, txt.Position, txt.FGColor, false, false, 0 );

			/// if dbEnableDebugging( EMT_BOX )
			//driver->draw2DRectangleOutline( txt.Position, 0xffffffff );
		}

		driver->endScene();

	//	}

		app.FrameCount++;
		app.FPS_Count++;

	}
	else
	{
		app.Device->yield();
	}


	app.Texts.clear();
//	//enter main loop
//	while (Device && Device->run())
//	{
//
//	}
//

//    timeNow = device->getTimer()->getRealTime();
//    bool renderNow = false;
//
//    if (syncEnabled)
//    {
//        if (timeNow - timeLast > timeWait)
//        {
//            timeLast = timeNow;
//            if (device->isWindowActive())
//            {
//                renderNow = true;
//            }
//        }
//    }
//    else
//    {
//        renderNow = true;
//    }
//
//    if (renderNow)
//    {
//        driver->beginScene(true,true,video::SColor(255,0,0,0));
//        smgr->drawAll();
//        guienv->drawAll();
//        driver->endScene();
//    }
//    else
//    {
//        device->yield();
//    }
}

///@brief
void dbSyncOn()
{
	dbPRINT("dbSyncOn()\n");

    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

    app.SyncRate = 30;
    app.SyncWait = 33;
}

///@brief
void dbSyncOff()
{
	dbPRINT("dbSyncOff()\n");

    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

    app.SyncRate = 0;
    app.SyncWait = 0;
}

///@brief
void dbSyncRate(u32 rate)
{
	dbPRINT("dbSyncRate()\n");

    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

    app.SyncRate = rate;
    if (app.SyncRate > 0)
		app.SyncWait = 1000 / app.SyncRate;
    else
		app.SyncWait = 0;
}

///@brief
void dbYield()
{
	dbPRINT("dbYield()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	if ( !app.Device )
		return;

	app.Device->yield();
}

///@brief
void dbWait( u32 seconds )
{
	dbPRINT("dbWait()\n");

    clock_t endwait;
    endwait = clock () + seconds * CLOCKS_PER_SEC ;
    while (clock() < endwait)
    {
        /* do nothing == idle */
    }
}


/// SetWindowLong( hWnd, GWL_STYLE, LONG dwNewLong );
//GWL_EXSTYLE -20 Sets a new extended window style.
//GWL_HINSTANCE -6 Sets a new application instance handle.
//GWL_ID -12 Sets a new identifier of the child window. The window cannot be a top-level window.
//GWL_STYLE -16 Sets a new window style.
//GWL_USERDATA -21 Sets the user data associated with the window. This data is intended for use by the application that created the window. Its value is initially zero.
//GWL_WNDPROC -4 Sets a new address for the window procedure. You cannot change this attribute if the window does not belong to the same process as the calling thread.

///
//WS_BORDER 0x00800000L	The window has a thin-line border.
//WS_CAPTION 0x00C00000L The window has a title bar (includes the WS_BORDER style).
//WS_CHILD 0x40000000L The window is a child window. A window with this style cannot have a menu bar. This style cannot be used with the WS_POPUP style.
//WS_CHILDWINDOW 0x40000000L Same as the WS_CHILD style.
//WS_CLIPCHILDREN 0x02000000L	Excludes the area occupied by child windows when drawing occurs within the parent window. This style is used when creating the parent window.
//WS_CLIPSIBLINGS 0x04000000L	Clips child windows relative to each other; that is, when a particular child window receives a WM_PAINT message, the WS_CLIPSIBLINGS style clips all other overlapping child windows out of the region of the child window to be updated. If WS_CLIPSIBLINGS is not specified and child windows overlap, it is possible, when drawing within the client area of a child window, to draw within the client area of a neighboring child window.
//WS_DISABLED 0x08000000L The window is initially disabled. A disabled window cannot receive input from the user. To change this after a window has been created, use the EnableWindow function.
//WS_DLGFRAME 0x00400000L The window has a border of a style typically used with dialog boxes. A window with this style cannot have a title bar.
//WS_GROUP 0x00020000L The window is the first control of a group of controls. The group consists of this first control and all controls defined after it, up to the next control with the WS_GROUP style. The first control in each group usually has the WS_TABSTOP style so that the user can move from group to group. The user can subsequently change the keyboard focus from one control in the group to the next control in the group by using the direction keys.You can turn this style on and off to change dialog box navigation. To change this style after a window has been created, use the SetWindowLong function.
//WS_HSCROLL 0x00100000L The window has a horizontal scroll bar.
//WS_ICONIC 0x20000000L The window is initially minimized. Same as the WS_MINIMIZE style.
//WS_MAXIMIZE 0x01000000L The window is initially maximized.
//WS_MAXIMIZEBOX 0x00010000L The window has a maximize button. Cannot be combined with the WS_EX_CONTEXTHELP style. The WS_SYSMENU style must also be specified.
//WS_MINIMIZE 0x20000000L The window is initially minimized. Same as the WS_ICONIC style.
//WS_MINIMIZEBOX 0x00020000L The window has a minimize button. Cannot be combined with the WS_EX_CONTEXTHELP style. The WS_SYSMENU style must also be specified.
//WS_OVERLAPPED 0x00000000L The window is an overlapped window. An overlapped window has a title bar and a border. Same as the WS_TILED style.
//WS_OVERLAPPEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)	 The window is an overlapped window. Same as the WS_TILEDWINDOW style.
//WS_POPUP 0x80000000L The windows is a pop-up window. This style cannot be used with the WS_CHILD style.
//WS_POPUPWINDOW (WS_POPUP | WS_BORDER | WS_SYSMENU)	The window is a pop-up window. The WS_CAPTION and WS_POPUPWINDOW styles must be combined to make the window menu visible.
//WS_SIZEBOX 0x00040000L The window has a sizing border. Same as the WS_THICKFRAME style.
//WS_SYSMENU 0x00080000L The window has a window menu on its title bar. The WS_CAPTION style must also be specified.
//WS_TABSTOP 0x00010000L The window is a control that can receive the keyboard focus when the user presses the TAB key. Pressing the TAB key changes the keyboard focus to the next control with the WS_TABSTOP style.You can turn this style on and off to change dialog box navigation. To change this style after a window has been created, use the SetWindowLong function. For user-created windows and modeless dialogs to work with tab stops, alter the message loop to call the IsDialogMessage function.
//WS_THICKFRAME 0x00040000L The window has a sizing border. Same as the WS_SIZEBOX style.
//WS_TILED 0x00000000L The window is an overlapped window. An overlapped window has a title bar and a border. Same as the WS_OVERLAPPED style.
//WS_TILEDWINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)	The window is an overlapped window. Same as the WS_OVERLAPPEDWINDOW style.
//WS_VISIBLE 0x10000000L	The window is initially visible. This style can be turned on and off by using the ShowWindow or SetWindowPos function.
//WS_VSCROLL 0x00200000L The window has a vertical scroll bar.


///@brief set MainWindow on desktop
void dbPositionWindow( u32 id, s32 x, s32 y)
{
	dbPRINT("dbPositionWindow()\n");

    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Device)
	{
		dbERROR("dbPositionWindow() - Invalid pointer to IrrlichtDevice\n");
		return;
	}

	video::IVideoDriver* driver = app.Device->getVideoDriver();
	if (!driver)
	{
		dbERROR("dbPositionWindow() - Invalid pointer to IVideoDriver\n");
		return;
	}

	const core::recti winRect = dbWindowPosition(id);
	const HWND hWnd = reinterpret_cast<HWND>( driver->getExposedVideoData().OpenGLWin32.HWnd );
	const u32 hStyle = GetWindowLong( hWnd, GWL_EXSTYLE );

	const BOOL result = SetWindowPos( hWnd, HWND_TOP, x, y, winRect.getWidth(), winRect.getHeight(), hStyle );
	if (result == FALSE)
	{
		dbERROR("dbPositionWindow() - Error in WinApi\n");
	}
}

///@brief center MainWindow on desktop
bool dbCenterWindow()
{
    dbPRINT("dbCenterWindow()\n");

    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Device)
	{
		dbERROR("dbCenterWindow() - Invalid pointer to IrrlichtDevice\n");
		return false;
	}

	video::IVideoDriver* driver = app.Device->getVideoDriver();
	if (!driver)
	{
		dbERROR("dbCenterWindow() - Invalid pointer to IVideoDriver\n");
		return false;
	}

	const core::dimension2du desktopSize = app.Device->getVideoModeList()->getDesktopResolution();
	const core::dimension2du screenSize = driver->getScreenSize();
	const s32 winX = (s32)(desktopSize.Width - screenSize.Width)  / 2 ;
	const s32 winY = (s32)(desktopSize.Height - screenSize.Height)  / 2 ;

	dbPositionWindow( 0, winX, winY );
}

///@brief
core::recti dbWindowPosition( u32 id )
{
	core::recti pos(-1,-1,0,0);

    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Device)
	{
		dbERROR("dbWindowPosition(%d) - Invalid pointer to IrrlichtDevice\n", id);
		return pos;
	}

	video::IVideoDriver* driver = app.Device->getVideoDriver();
	if (!driver)
	{
		dbERROR("dbWindowPosition(%d) - Invalid pointer to IVideoDriver\n", id);
		return pos;
	}

	HWND hWnd = reinterpret_cast<HWND>( driver->getExposedVideoData().OpenGLWin32.HWnd );
	RECT hRect;
	BOOL result = GetWindowRect( hWnd, &hRect );

	pos.UpperLeftCorner.X = (s32)hRect.left;
	pos.UpperLeftCorner.Y = (s32)hRect.top;
	pos.LowerRightCorner.X = (s32)hRect.right;
	pos.LowerRightCorner.Y = (s32)hRect.bottom;

	if (result==FALSE)
	{
		dbERROR("dbWindowPosition(%d) - Error in WinApi\n", id);
	}

	return pos;
}

///@brief
s32 dbWindowPositionX( u32 id )
{
	return dbWindowPosition(id).UpperLeftCorner.X;
}

///@brief
s32 dbWindowPositionY( u32 id )
{
	return dbWindowPosition(id).UpperLeftCorner.Y;
}

///@brief
u32 dbWindowWidth( u32 id )
{
	return (u32)core::abs_<s32>(dbWindowPosition(id).getWidth());
}

///@brief
u32 dbWindowHeight( u32 id )
{
	return (u32)core::abs_<s32>(dbWindowPosition(id).getHeight());
}

void dbSetWindowTitle(const wchar_t* title)
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Device)
		return;

    app.Device->setWindowCaption( title );
}

void dbSetWindowOn()
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Device)
		return;
}

void dbSetWindowOff()
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Device)
		return;
}

void dbMaximizeWindow()
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Device)
		return;
	app.Device->maximizeWindow();
}

void dbMinimizeWindow()
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Device)
		return;
	app.Device->minimizeWindow();
}


/// DarkGDK


/// set polygon-count ( for current scenemanager )

u32 dbGetPolygonCount()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return 0;

	return app.Device->getVideoDriver()->getPrimitiveCountDrawn(0);
}

/// get current render-target size

u32 dbGetRTTWidth()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device || !app.Device->getVideoDriver() )
		return 0;

	return app.Device->getVideoDriver()->getCurrentRenderTargetSize().Width;
}

u32 dbGetRTTHeight()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device || !app.Device->getVideoDriver() )
		return 0;

	return app.Device->getVideoDriver()->getCurrentRenderTargetSize().Height;
}

/// get maximum render-target size

u32 dbGetRTTWidthMax()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device || !app.Device->getVideoDriver() )
		return 0;

	return app.Device->getVideoDriver()->getMaxTextureSize().Width;
}

u32 dbGetRTTHeightMax()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device || !app.Device->getVideoDriver() )
		return 0;

	return app.Device->getVideoDriver()->getMaxTextureSize().Height;
}

/// get version

core::stringc dbGetVersion()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return core::stringc("");

	core::stringc txt = app.Device->getVersion();
	return txt;
}

/// get vendor

core::stringc dbGetVendor()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return core::stringc("");

	return app.Device->getVideoDriver()->getVendorInfo();
}



/// get driver-type as string

core::stringc dbGetDriverString()
{
	core::stringc txt("");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return txt;

	switch ( app.Device->getVideoDriver()->getDriverType() )
	{
		case video::EDT_OPENGL: txt = "OpenGL"; break;
		case video::EDT_BURNINGSVIDEO: txt = "Burnings"; break;
		case video::EDT_SOFTWARE: txt = "Software"; break;
		case video::EDT_NULL: txt = "Null"; break;
		case video::EDT_DIRECT3D8: txt = "Direct3d8"; break;
		case video::EDT_DIRECT3D9: txt = "Direct3d9"; break;
		case video::EDT_COUNT: txt = "unknown"; break;
		default: break;
	}

	return txt;
}

/// set clear-color ( for current renderTarget )

void dbCls( const video::SColor& color )
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	app.ClearColor = color;
}

/// set text-color ( for current font )

void dbInk( const video::SColor& fgcolor, const video::SColor& bgcolor )
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	app.TextForeColor = fgcolor;
	app.TextBackColor = bgcolor;
}

/// Get Text Count

u32 dbGetTextCount()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	return app.Texts.size();
}

/// Get Text Dimension ( from current font )

//core::dimension2du dbGetTextDimension( const core::stringc& txt )
//{
//
//    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
//    if (!app.Font)
//		return core::dimension2du(0,0);
//
//	return app.Font->getDimension( core::stringw( txt ).c_str() );
//}

core::dimension2du dbGetTextDimension( const core::stringw& txt )
{

    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Font)
		return core::dimension2du(0,0);

	return app.Font->getDimension( txt.c_str() );
}

/// Get Text Width ( from current font )

//u32 dbGetTextWidth( const core::stringc& txt )
//{
//	return dbGetTextDimension( core::stringw(txt) ).Width;
//}

u32 dbGetTextWidth( const core::stringw& txt )
{
	return dbGetTextDimension( txt ).Width;
}

/// Get Text Height ( from current font )

//u32 dbGetTextHeight( const core::stringc& txt )
//{
//	return dbGetTextDimension( core::stringw(txt) ).Height;
//}

u32 dbGetTextHeight( const core::stringw& txt )
{
	return dbGetTextDimension( txt ).Height;
}

/// draw text on screen ( with current font )

void dbText( const core::stringw& txt, s32 x, s32 y, s32 hAlign = -1, s32 vAlign = -1 )
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Font)
		return;

	const core::dimension2du txt_size = app.Font->getDimension( txt.c_str() );

	// calculate final 2d-position for text ( top/left)
	core::position2di txt_pos(x,y);

	// horizontal align
	if (hAlign == 0)
	{
		txt_pos.X -= (s32)txt_size.Width / 2;
	}
	else if (hAlign == 1)
	{
		txt_pos.X -= (s32)txt_size.Width;
	}

	// vertical align
	if (vAlign == 0)
	{
		txt_pos.Y -= (s32)txt_size.Height / 2;
	}
	else if (vAlign == 1)
	{
		txt_pos.Y -= (s32)txt_size.Height;
	}

	DarkGDK_SText2d tmp;
	tmp.Font = app.Font;
	tmp.Text = txt;
	tmp.Position = core::recti( txt_pos, txt_size);
	tmp.FGColor = app.TextForeColor;
	tmp.BGColor = app.TextBackColor;

	app.Texts.push_back( tmp );
}

void dbCenterText( const core::stringw& txt, s32 x, s32 y )
{
	dbText( txt, x, y, 0, -1 );
}


/// draw text on screen ( with current font )

void dbText( const StringArray& lines, s32 x, s32 y, s32 hAlign, s32 vAlign )
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Font)
		return;

	const u32 lineCount = lines.size();

	const u32 lineHeight = app.Font->getDimension( L"HQLuiaWq" ).Height;

	for (u32 i=0; i<lineCount; i++)
	{

		dbText( lines[i], x, y, hAlign, vAlign );
		y += lineHeight;
	}
}

/// handle cursor
//	void dbPositionCursor(s32 x, s32 y);
//	void dbCursorPositionX();
//	void dbCursorPositionY();

void dbPositionCursor(s32 x, s32 y, s32 hAlign, s32 vAlign )
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	app.CursorPos = core::position2di(x,y);
	app.CursorAlign = core::position2di(hAlign,vAlign);
}

void dbSetTextFont(const io::path& file)
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Device)
		return;

	gui::IGUIEnvironment* env = app.Device->getGUIEnvironment();

	gui::IGUIFont* font = env->getFont( file );

	if ( font )
		env->getSkin()->setFont( font );
	else
		env->getSkin()->setFont( env->getBuiltInFont() );

	app.Font = font;
}


///@brief print container of strings at cursor pos
//
//void dbPrint( const io::path& line_txt )
//{
//    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
//	const u32 lineHeight = dbGetTextHeight( L"LHQWui" );
//	const s32 x = app.CursorPos.X;
//	const s32 y = app.CursorPos.Y;
//	dbText( core::stringw( line_txt ), x, y, -1, -1 );
//	app.CursorPos.Y += lineHeight;
//}

void dbPrint( const core::stringc& line_txt )
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	const u32 lineHeight = dbGetTextHeight( "LHQWui" );
	const s32 x = app.CursorPos.X;
	const s32 y = app.CursorPos.Y;
	dbText( line_txt, x, y, app.CursorAlign.X, app.CursorAlign.Y );
	app.CursorPos.Y += lineHeight;
}

void dbPrint( const core::stringw& line_txt )
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	const u32 lineHeight = dbGetTextHeight( L"HQWui" );
	const s32 x = app.CursorPos.X;
	const s32 y = app.CursorPos.Y;
	dbText( line_txt, x, y, app.CursorAlign.X, app.CursorAlign.Y );
	app.CursorPos.Y += lineHeight;
}

///@brief print container of strings at cursor pos

void dbPrint( const StringArray& container )
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	const u32 lineCount = container.size();

	const u32 lineHeight = dbGetTextHeight( L"LHQWui" );

	const s32 x = app.CursorPos.X;

	s32 y = app.CursorPos.Y;

	for (u32 i=0; i<lineCount; i++)
	{
		dbText( core::stringw( container[i] ), x, y, app.CursorAlign.X, app.CursorAlign.Y );
		y += lineHeight;
		app.CursorPos.Y = y;
	}
}

//	void dbOnResize(u32 w, u32 h);
//	void dbOnDisplay(void);
//	void dbOnKey(unsigned char key, int x, int y);
//	void dbOnIdle(void);
//
//	/// handle Fonts
//	void dbSetTextFont(const io::path& file);
//	void dbSetTextSize(u32 height);
//	void dbGetTextSize();
//
//	/// handle Colors
//	void dbCls(u32 color)
//	void dbInk(u32 fgcolor, u32 bgcolor)


	/// handle Keyboard
//	void dbInitKeyboard();
//	void dbCloseKeyboard();
//
//	s32 dbKbHit();
//	s32 dbKbGet();

//	core::stringw dbInkey();
//	s32 dbKeyState(EKEY_CODE key);


// This is the one method that we have to implement
bool OnKeyEvent(const SEvent::SKeyInput& key_event )
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return false;

	// Remember whether each key is down or up
	app.KeyIsDown[key_event.Key] = key_event.PressedDown;

	app.KeyBuffer.push_back( key_event.Key );

	return false;
}

bool dbKbHit()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	if ( app.KeyBuffer.size() > 0 )
		return true;
	else
		return false;
}

EKEY_CODE dbKbKey()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	u32 c = app.KeyBuffer.size();
	if (c==0)
		return KEY_KEY_CODES_COUNT;

	EKEY_CODE key = app.KeyBuffer[c-1];
	app.KeyBuffer.erase(c-1,1);
	return key;
}

// This is used to check whether a key is being held down
bool isPressed(EKEY_CODE keyCode)
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	return app.KeyIsDown[keyCode];
}

//	u8 dbUpKey();
//	u8 dbDownKey();
//	u8 dbLeftKey();
//	u8 dbRightKey();
//	u8 dbEscapeKey();
//	u8 dbReturnKey();
//	u8 dbShiftKey();
//	u8 dbControlKey();


core::stringw dbInkey()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
//	dbPrint("dbInKey()");
//	if (!SDK) return 0;
//	if (!SDK->getDevice()->getEventReceiver()) return 0;
//	return reinterpret_cast<CMasterEventReceiver*>(SDK->getDevice()->getEventReceiver())->getKey();
	return core::stringw(L"");
}

s32 dbKeyState(EKEY_CODE key)
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
//	dbPrint("dbKeyState()");
//	if (!SDK) return 0;
//	if (!SDK->getDevice()->getEventReceiver()) return 0;
//	return reinterpret_cast<CMasterEventReceiver*>(SDK->getDevice()->getEventReceiver())->getKeyState(key);
	return 0;
}

u8 dbUpKey(){ return dbKeyState(KEY_UP); }
u8 dbDownKey(){ return dbKeyState(KEY_DOWN);}
u8 dbLeftKey(){ return dbKeyState(KEY_LEFT);}
u8 dbRightKey(){ return dbKeyState(KEY_RIGHT);}
u8 dbEscapeKey(){ return dbKeyState(KEY_ESCAPE);}
u8 dbReturnKey(){ return dbKeyState(KEY_RETURN);}
u8 dbShiftKey(){ return dbKeyState(KEY_SHIFT);}
u8 dbControlKey(){ return dbKeyState(KEY_CONTROL);}


/// handle Mouse
//  void dbPositionMouse(s32 x, s32 y)
//	s32 dbMouseClick();
//	s32 dbMouseX();
//	s32 dbMouseY();
//	f32 dbMouseZ();
//	s32 dbMouseMoveX();
//	s32 dbMouseMoveY();
//	f32 dbMouseMoveZ();
//	bool dbMouseOver(s32 x1, s32 y1, s32 x2, s32 y2);
//	bool dbMouseOver(const core::rect<s32>& box);

void dbPositionMouse(s32 x, s32 y)
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return;

	app.CursorPos = core::position2di(x,y);

	app.Device->getCursorControl()->setPosition(x,y);
}


s32 dbMouseClick()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	return app.MouseClick;
}

s32 dbMouseX()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	return app.MousePosX;
}

s32 dbMouseY()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	return app.MousePosY;
}

f32 dbMouseZ()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	return app.MousePosZ;
}

s32 dbMouseMoveX()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	return app.MouseMoveX;
}

s32 dbMouseMoveY()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	return app.MouseMoveY;
}

f32 dbMouseMoveZ()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	return app.MouseMoveZ;
}

bool dbMouseOver(s32 x1, s32 y1, s32 x2, s32 y2)
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	if ((app.MousePosX >= x1) ||
		(app.MousePosY >= y1) ||
		(app.MousePosX <= x2) ||
		(app.MousePosY <= y2))
	{
		return true;
	}

	return false;
}

bool dbMouseOver(const core::rect<s32>& box)
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	if ((app.MousePosX >= box.UpperLeftCorner.X) ||
		(app.MousePosY >= box.UpperLeftCorner.Y) ||
		(app.MousePosX <= box.LowerRightCorner.X) ||
		(app.MousePosY <= box.LowerRightCorner.Y))
	{
		return true;
	}

	return false;
}


io::path dbGetDir()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return io::path( _IRR_TEXT("") );

	return app.Device->getFileSystem()->getWorkingDirectory();
}

void dbSetDir( const io::path& newDir )
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return;

	io::IFileSystem* fs = app.Device->getFileSystem();
	if (!fs)
		return;

	fs->changeWorkingDirectoryTo( newDir );

	core::stringc txt("");

	if ( fs->getWorkingDirectory() == fs->getAbsolutePath( newDir ) )
	{
		txt = "SetDir(";
		txt += newDir;
		txt += ")";
		printf( "%s\n", txt.c_str() );
	}
	else
	{
		txt = "Could not SetDir(";
		txt += newDir;
		txt += ")";
		printf( "%s\n", txt.c_str() );
	}
}

StringArray dbGetFiles()
{
	StringArray container;

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return container;

	io::IFileSystem* fileSys = app.Device->getFileSystem();
	if (!fileSys)
		return container;

	io::IFileList* fileList = fileSys->createFileList();
	if (!fileList)
		return container;

	u32 fileCount = fileList->getFileCount();

	for (u32 i=0; i<fileCount; i++)
	{
		core::stringc txt("");
		txt += fileList->getFullFileName( i );
		txt += "\t";
		txt += fileList->getFileSize( i );
		container.push_back( txt );
	}
	return container;
}


StringArray dbGetFilesFromArchive( const io::path& filename )
{
	StringArray container;

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return container;

	io::IFileSystem* fileSys = app.Device->getFileSystem();
	if (!fileSys)
		return container;


//	addFileArchive(const path& filename, bool ignoreCase=true,
//		bool ignorePaths=true,
//		E_FILE_ARCHIVE_TYPE archiveType=EFAT_UNKNOWN,
//		const core::stringc& password="",
//		IFileArchive** retArchive=0) =0;

	io::IFileArchive* fileArc = 0;
	// io::IFileArchive* zip
	// bool result = fileSys->addFileArchive( filename );
	// bool result = fileSys->addFileArchive( filename, false, false );
	bool result = fileSys->addFileArchive( filename, true, true, io::EFAT_UNKNOWN, "", &fileArc);
	if (!result)
	{
		printf( "Could not add FileArchive.\n" );
		return container;
	}
	if (!fileArc)
	{
		printf( "Returned FileArchive-pointer is invalid.\n" );
		return container;
	}

//	io::IFileList* fileList = fileSys->createFileList();
//	if (!fileList)
//		return container;
//
//	u32 fileCount = fileList->getFileCount();
//
//	for (u32 i=0; i<fileCount; i++)
//	{
//		core::stringc txt("");
//		txt += fileList->getFullFileName( i );
//		txt += "\t";
//		txt += fileList->getFileSize( i );
//		container.push_back( txt );
//	}
	return container;
}



} // end namespace irr
