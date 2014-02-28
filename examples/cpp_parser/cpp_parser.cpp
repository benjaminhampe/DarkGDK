/** sfml audio + midi options dialog for irrlicht-engine 1.9svn

*/

#include <cstdlib>
#include <cstdio>
#include <cstdarg>
#include <cmath>
#include <ctime>

#include <SFML/Audio.hpp>

#include <irrlicht.h>
#include "driverChoice.h"

#if defined(DEBUG) || defined(_DEBUG)
	#define PRINT(args...) fprintf( stdout, args );

	#define ERROR_ON_NULL_POINTER(x,args...) if (!(x)) { \
		fprintf( stdout, args ); \
		fprintf( stderr, args ); \
		return -1; \
		}
#else
	#define swap(a, b) { \
        a ^= b; \
        b ^= a; \
        a ^= b; \
    }
	// #define PRINT(args...)
	#define PRINT(args...) { fprintf( stdout, args ); }
	#define ERROR_NULL_POINTER(x, args... ) { if ( !(x) ) \
	{ \
		fprintf( stdout, args ); \
		fprintf( stderr, args ); \
		return -1; \
		} \
	}
#endif


#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif


/*
	Main
*/

#include <windows.h>

namespace irr
{
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

	bool printHelp( )
	{
		PRINT("cpp_parser -absf INPUT-FILE\n");
		PRINT("[OPTIONS] absf\n");
		PRINT("-absf\n");
		PRINT("-absf\n");
		PRINT("-absf\n");
		PRINT("-absf\n");
		PRINT("[OPTIONS] absf\n");
		PRINT("-absf\n");
		PRINT("-absf\n");
		PRINT("-absf\n");
		PRINT("-absf\n");
		PRINT("cpp_parser (c) 2008-2014 benjaminhampe@gmx.de\n");
	}

	/// getWindowPosition
	core::recti getWindowPosition( IrrlichtDevice* device )
	{
		core::recti pos(-1,-1,0,0);

		if (!device)
		{
			PRINT("getWindowPosition() - Invalid pointer to IrrlichtDevice\n");
			return pos;
		}

		video::IVideoDriver* driver = device->getVideoDriver();
		if (!driver)
		{
			PRINT("getWindowPosition() - Invalid pointer to IVideoDriver\n");
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
			PRINT("getWindowPosition() - Error in WinApi\n");
		}

		return pos;
	}

	/// setWindowPosition
	bool setWindowPosition( IrrlichtDevice* device, s32 x, s32 y )
	{
		if (!device)
		{
			PRINT("setWindowPosition() - Invalid pointer to IrrlichtDevice\n");
			return false;
		}

		video::IVideoDriver* driver = device->getVideoDriver();
		if (!driver)
		{
			PRINT("setWindowPosition() - Invalid pointer to IVideoDriver\n");
			return false;
		}

		const core::recti winRect = getWindowPosition( device );
		const HWND hWnd = reinterpret_cast<HWND>( driver->getExposedVideoData().OpenGLWin32.HWnd );
		const u32 hStyle = GetWindowLong( hWnd, GWL_EXSTYLE );

		const BOOL result = SetWindowPos( hWnd, HWND_TOP, x, y, winRect.getWidth(), winRect.getHeight(), hStyle );
		if (result == FALSE)
		{
			PRINT("setWindowPosition() - Error in WinApi\n");
		}

		return true;
	}

	/// center Window
	bool centerWindow( IrrlichtDevice* device )
	{
		if (!device)
		{
			PRINT("centerWindow() - Invalid pointer to IrrlichtDevice\n");
			return false;
		}

		video::IVideoDriver* driver = device->getVideoDriver();
		if (!driver)
		{
			PRINT("centerWindow() - Invalid pointer to IVideoDriver\n");
			return false;
		}

		const core::dimension2du desktopSize = device->getVideoModeList()->getDesktopResolution();
		const core::dimension2du screenSize = driver->getScreenSize();
		const s32 winX = (s32)(desktopSize.Width - screenSize.Width)  / 2 ;
		const s32 winY = (s32)(desktopSize.Height - screenSize.Height)  / 2 ;

		return setWindowPosition( device, winX, winY );
	}

} // end namespace irr


/*
	Main Application Window
*/

using namespace irr;

s32 main( s32 argc, c8** argv )
{
	/*
		Console
	*/
	const c8* app_title = "C/C++ Parser for IDE";

	/*
		Console - CommandLine Arguments
	*/
	PRINT( "Hello World!\n" );
	PRINT( "argc = %d\n", argc );
	for (s32 i = 0; i < argc; i++)
	{
		PRINT( "argv = %s\n", argv[i] );
	}

	// ask user for driver
	//	PRINT( "User Driver Choice Console Dialog!\n" );
	//	video::E_DRIVER_TYPE driverType=driverChoiceConsole();
	//	if (driverType==video::EDT_COUNT)
	//		return 1;

	// create device
	IrrlichtDevice* device = createDevice( video::EDT_OPENGL, core::dimension2d<u32>(800, 600), 32, false);
	device->setResizable( true );
	device->setWindowCaption( core::stringw( core::stringc( app_title ) ).c_str() );

	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();
	gui::IGUIEnvironment* env = device->getGUIEnvironment();

	// ERROR_NULL_POINTER(driver, "Invalid Pointer\n");
	// ERROR_NULL_POINTER(smgr, "Invalid Pointer\n");
	// ERROR_NULL_POINTER(env, "Invalid Pointer\n");
	smgr->addCameraSceneNode(0, core::vector3df(0,-40,0), core::vector3df(0,0,0));
	scene::ISceneNode* myNode = smgr->addCubeSceneNode( 10.0f, smgr->getRootSceneNode(), -1 );

	// ERROR_NULL_POINTER(myNode, "Invalid Pointer\n");
	scene::ISceneNodeAnimator* anim = smgr->createRotationAnimator(core::vector3df(0.8f, 0, 0.8f));

	// ERROR_NULL_POINTER(anim, "Invalid Pointer\n");
	myNode->addAnimator(anim);
	anim->drop();
	anim = 0; // As I shouldn't refer to it again, ensure that I can't

	/*
		Now draw everything and finish.
	*/
	u32 frames=0;

	core::dimension2du DesktopSize = device->getVideoModeList()->getDesktopResolution();
	core::recti WinRect = getWindowPosition( device );
	core::dimension2du ScreenSize = driver->getScreenSize();

	centerWindow( device );

	ITimer* timer = device->getTimer();
	u32 timeNow = timer->getTime();
//	u32 timeWaitWindowMove = 1000;
//	u32 timeLastWindowMove = time;

//	core::array<core::position2di> Positions;
//	Positions.push_back( core::position2di(0,0) );
//	Positions.push_back( core::position2di(ScreenSize.Width/2,0) );
//	Positions.push_back( core::position2di(ScreenSize.Width,0) );
//	Positions.push_back( core::position2di(0,0) );
//	Positions.push_back( core::position2di(ScreenSize.Width/2, ScreenSize.Height/2) );
//	Positions.push_back( core::position2di(ScreenSize.Width, ScreenSize.Height/2) );
//	Positions.push_back( core::position2di(0, ScreenSize.Height/2) );
//	Positions.push_back( core::position2di(ScreenSize.Width/2,0) );
//	Positions.push_back( core::position2di(ScreenSize.Width,0) );
//	u32 index_pos = 0;

	while( device && device->run() )
	{
		timeNow = timer->getTime();

		core::recti winRect = getWindowPosition( device );
		core::dimension2du screenSize = driver->getScreenSize();

		// Window Move Event
		if ( WinRect != winRect )
		{
			WinRect = winRect;
			PRINT( "OnWindowMove(%d,%d,%d,%d)\n",  WinRect.UpperLeftCorner.X, WinRect.UpperLeftCorner.Y, WinRect.LowerRightCorner.X, WinRect.LowerRightCorner.Y );
		}

		// Window Resize Event
		if ( ScreenSize != screenSize )
		{
			ScreenSize = screenSize;
			PRINT( "OnResize(%d,%d)\n", ScreenSize.Width, ScreenSize.Height );

			scene::ICameraSceneNode* cam = smgr->getActiveCamera();
			if (cam)
			{
				cam->setAspectRatio( (f32)ScreenSize.Width / (f32)ScreenSize.Height );
				PRINT( "OnSetCameraAspect(%f)\n", cam->getAspectRatio() );
			}
		}

//		if (time > timeLastWindowMove + timeWaitWindowMove )
//		{
//			timeLastWindowMove = timer->getTime();
//
//			if (index_pos >= Positions.size())
//				index_pos = 0;
//
//			setWindowPosition( device, Positions[index_pos].X, Positions[index_pos].Y);
//
//			index_pos++;
//		}


		driver->beginScene(true, true, video::SColor(255,255,255,255));

		smgr->drawAll();

		env->drawAll();

		driver->endScene();

		if (++frames==100)
		{
			core::stringw str ( app_title );
			str += L" | Driver ";
			str += driver->getName();
			str += L" | FPS  ";
			str += (s32)driver->getFPS();
			str += L" | Triangles ";
			str += (s32)driver->getPrimitiveCountDrawn();
			str += L" | ScreenSize(";
			str += ScreenSize.Width;
			str += L",";
			str += ScreenSize.Height;
			str += L") | WinRect(";
			str += WinRect.UpperLeftCorner.X;
			str += L",";
			str += WinRect.UpperLeftCorner.Y;
			str += L",";
			str += WinRect.LowerRightCorner.X;
			str += L",";
			str += WinRect.LowerRightCorner.Y;
			str += L")";
			device->setWindowCaption(str.c_str());
			frames=0;
		}
	}

	device->drop();

	return 0;
}

/*
That's it. Compile and play around with the program.
**/
