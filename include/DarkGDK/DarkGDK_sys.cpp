#include <DarkGDK_sys.h>

namespace irr{

//void dbDarkGDK(s32 argc, c8** argv)
//{
//	CDarkGDK& instance = CDarkGDK::GetInstance();
//}
//
//bool dbLoopGDK()
//{
//	CDarkGDK& instance = CDarkGDK::GetInstance();
//
//}




//		/// set default device parameters
//		SIrrlichtCreationParameters param;
//		param.DriverType = video::EDT_NULL;
//		param.WindowSize.set(1024,768);
//		param.Fullscreen = false;
//		param.LoggingLevel = ELL_INFORMATION;
//		param.HighPrecisionFPU = true;
//		param.Doublebuffer = true;
//
//		/// set more parameters using Null-Device
//		SIrrlichtCreationParameters nullParams;
//		nullParams.LoggingLevel = ELL_NONE;
//		nullParams.DriverType = video::EDT_NULL;
//		IrrlichtDevice* nullDev = createDeviceEx( nullParams );
//		if (nullDev)
//		{
//		    const core::dimension2du d_desktop = nullDev->getVideoModeList()->getDesktopResolution();
//			param.WindowSize = d_desktop;
//			param.WindowSize -= core::dimension2du(64,128);
//			s32 x = (s32)((d_desktop.Width - param.WindowSize.Width) >> 1);
//			s32 y = (s32)((d_desktop.Height - param.WindowSize.Height) >> 1);
//			param.Bits = nullDev->getVideoModeList()->getDesktopDepth();
//			param.WindowPosition = core::position2di(x,y);
//
//			if (nullDev->isDriverSupported(video::EDT_OPENGL))
//			{
//				param.DriverType = video::EDT_OPENGL;
//				param.AntiAlias = video::EAAM_QUALITY;
//				param.Vsync = true;
//				// param.ZBufferBits = 32;
//				// param.Stencilbuffer = true;
//				// param.WithAlphaChannel = false;
//			}
//			nullDev->drop();
//		}
//		else
//		{
//			fprintf( stdout, "ERROR: Could not create Null device\n");
//		}
//
//		/// create irrlicht-device
//		Device = createDeviceEx(param);
//		if (Device == 0)
//		{
//			// You can add your own exception handling on driver failure
//			exit(0);
//		}
//
//		/// set event-receiver
//		Device->setEventReceiver( this );
//
//		if (this != Device->getEventReceiver())
//		{
//			printf("MyEventReceiver() :: Could not set EventReceiver\n");
//		}
//
//		#ifdef _DEBUG
//		printf("EventReceiver attached to device\n");
//		#endif
//
//		/// set window-caption
//		Device->setWindowCaption( core::stringw( Title ).c_str() );
//
//		/// get pointer and stuff
//		gui::IGUIEnvironment* env = Device->getGUIEnvironment();
//		video::IVideoDriver* driver = Device->getVideoDriver();
//		scene::ISceneManager* smgr = Device->getSceneManager();
//		gui::ICursorControl* cursor = Device->getCursorControl();
//		ScreenSize = driver->getScreenSize();
//		io::IFileSystem* files = Device->getFileSystem();
//
//		/// skin & font
//		gui::IGUIElement* rootElement = env->getRootGUIElement();
//		gui::IGUISkin* skin = env->createSkin( gui::EGST_BURNING_SKIN );
//		db::setSkinColorsBlackStyle( skin );
//		gui::IGUIFont* font = env->getFont( "../../media/fontcourier.bmp");
//		gui::IGUIFont* fontWinCap = env->getFont( "../../media/lucida.png");
//		skin->setFont( font, gui::EGDF_DEFAULT );
//		skin->setFont( font, gui::EGDF_WINDOW );
//
//		env->setSkin( skin );
//
//		/// window stack rect ( bottom )
//		WindowMgrRect = core::recti( 0,11*ScreenSize.Height/12,
//									ScreenSize.Width-1, ScreenSize.Height-1);
//
//		/// window tiling
//		u32 w = ScreenSize.Width/3;
//		u32 h = ScreenSize.Height;
//		s32 x = 0;
//		s32 y = 0;
//
//
//		/// top left/center - XmlTreeViewWindow
//		db::createXmlTreeViewWindow( "../../source/Irrlicht/Irrlicht-gcc.cbp", files, env, rootElement,
//			core::recti( core::position2di(x,y), core::dimension2du(w,h) ) );
//
//		/// top right/center - XmlTreeViewWindow
//		db::createXmlTreeViewWindow( "./project.cbp", files, env, rootElement,
//			core::recti( core::position2di(x+w,y), core::dimension2du(w,h) ) );
//
//		/// top right
//		db::createHelpWindow( env, rootElement,	core::recti( core::position2di(x+2*w,y), core::dimension2du(w,h) ) );
//
//		/// set default image filename to load
//		io::path img_filename = "../../media/stones.jpg";
//		if (Argc>1)
//		{
//			img_filename = core::stringc( Argv[1] );
//		}
//
//		//	virtual IGUIImage* addImage(const core::rect<s32>& rectangle,
//		//		IGUIElement* parent=0, s32 id=-1, const wchar_t* text=0, bool useAlphaChannel=true) = 0;
//		gui::IGUIImage* guiImage = env->addImage(
//			driver->getTexture( img_filename ), core::position2di(0,0), true, rootElement, -1, L"Hello Text" );
//
//		/// set default object filename to load
//		io::path obj_filename = "../../media/ext/alien/alien.mdl";
////		if (Argc>1)
////		{
////			obj_filename = core::stringc( Argv[1] );
////		}
//
//		/// load object
//		scene::ISceneNode* node = db::loadObject( smgr, obj_filename, 0 );
//		if (!node)
//		{
//			printf("Could not load mesh %s\n", Argv[1]);
//		}
//		else
//		{
//			node->setScale( core::vector3df(100,100,100) );
//			node->setMaterialFlag( video::EMF_BACK_FACE_CULLING, true );
//			node->setMaterialFlag( video::EMF_FRONT_FACE_CULLING, false );
//			node->setMaterialFlag( video::EMF_ANTI_ALIASING, false );
//			node->setMaterialFlag( video::EMF_ANISOTROPIC_FILTER, true );
//			node->setMaterialFlag( video::EMF_BILINEAR_FILTER, true );
//			// node->setMaterialFlag( video::EMF_BLEND_OPERATION, false );
//			// node->setMaterialFlag( video::EMF_COLOR_MATERIAL, false );
//			// node->setMaterialFlag( video::EMF_COLOR_MASK, false );
//			node->setMaterialFlag( video::EMF_FOG_ENABLE, false );
//			// node->setMaterialFlag( video::EMF_GOURAUD_SHADING, false );
//			node->setMaterialFlag( video::EMF_LIGHTING, false );
//			// node->setMaterialFlag( video::EMF_NORMALIZE_NORMALS, false );
//			// node->setMaterialFlag( video::EMF_POINTCLOUD, false );
//			// node->setMaterialFlag( video::EMF_POLYGON_OFFSET, false );
//			node->setMaterialFlag( video::EMF_TRILINEAR_FILTER, true );
//			// node->setMaterialFlag( video::EMF_TEXTURE_WRAP, true );
//			// node->setMaterialFlag( video::EMF_USE_MIP_MAPS false );
//			node->setMaterialFlag( video::EMF_WIREFRAME, false );
//			// node->setMaterialFlag( video::EMF_ZBUFFER, true );
//			// node->setMaterialFlag( video::EMF_ZWRITE_ENABLE, true );
//		}
//


void dbDarkGDK(s32 argc, c8** argv)
{
	/// print CommandLine
	printf( "CommandLine ArgumentCount = %d\n", argc );
	for (s32 i=0; i<argc; i++)
		printf( "CommandLine Argv[%d] = %s\n", i, argv[i] );


	/// ask user for driver
//	printf("Please select the driver you want for this example:\n"
//		" (a) OpenGL 1.5\n (b) Direct3D 9.0c\n (c) Direct3D 8.1\n"
//		" (d) Burning's Software Renderer\n (e) Software Renderer\n"
//		" (f) NullDevice\n (otherKey) exit\n\n");
//
//	E_DRIVER_TYPE driverType;
//	char i;
//	std::cin >> i;
//	switch(i)
//	{
//		case 'a': driverType = EDT_OPENGL;   break;
//		case 'b': driverType = EDT_DIRECT3D9;break;
//		case 'c': driverType = EDT_DIRECT3D8;break;
//		case 'd': driverType = EDT_BURNINGSVIDEO;break;
//		case 'e': driverType = EDT_SOFTWARE; break;
//		case 'f': driverType = EDT_NULL;     break;
//		default: return 1;
//	}

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

	/// window tiling
//	u32 w = app.ScreenSize.Width/3;
//	u32 h = app.ScreenSize.Height;
//	s32 x = 0;
//	s32 y = 0;

//	/// top left/center - XmlTreeViewWindow
//	db::createXmlTreeViewWindow( "../../source/Irrlicht/Irrlicht-gcc.cbp", files, env, rootElement,
//		core::recti( core::position2di(x,y), core::dimension2du(w,h) ) );
//
//	/// top right/center - XmlTreeViewWindow
//	db::createXmlTreeViewWindow( "./project.cbp", files, env, rootElement,
//		core::recti( core::position2di(x+w,y), core::dimension2du(w,h) ) );
//
//	/// top right
//	db::createHelpWindow( env, rootElement,	core::recti( core::position2di(x+2*w,y), core::dimension2du(w,h) ) );
//
//	/// set default image filename to load
//	io::path img_filename = "../../media/stones.jpg";
//	if (Argc>1)
//	{
//		img_filename = core::stringc( Argv[1] );
//	}
//
//	//	IGUIImage* addImage(const core::rect<s32>& rectangle,
//	//		IGUIElement* parent=0, s32 id=-1, const wchar_t* text=0, bool useAlphaChannel=true) = 0;
//	gui::IGUIImage* guiImage = env->addImage(
//		driver->getTexture( img_filename ), core::position2di(0,0), true, rootElement, -1, L"Hello Text" );
//
//	/// set default object filename to load
//	io::path obj_filename = "../../media/ext/alien/alien.mdl";
////		if (Argc>1)
////		{
////			obj_filename = core::stringc( Argv[1] );
////		}
//
//	/// load object
//	scene::ISceneNode* node = db::loadObject( smgr, obj_filename, 0 );
//	if (!node)
//	{
//		printf("Could not load mesh %s\n", Argv[1]);
//	}
//	else
//	{
//		node->setScale( core::vector3df(100,100,100) );
//		node->setMaterialFlag( video::EMF_BACK_FACE_CULLING, true );
//		node->setMaterialFlag( video::EMF_FRONT_FACE_CULLING, false );
//		node->setMaterialFlag( video::EMF_ANTI_ALIASING, false );
//		node->setMaterialFlag( video::EMF_ANISOTROPIC_FILTER, true );
//		node->setMaterialFlag( video::EMF_BILINEAR_FILTER, true );
//		// node->setMaterialFlag( video::EMF_BLEND_OPERATION, false );
//		// node->setMaterialFlag( video::EMF_COLOR_MATERIAL, false );
//		// node->setMaterialFlag( video::EMF_COLOR_MASK, false );
//		node->setMaterialFlag( video::EMF_FOG_ENABLE, false );
//		// node->setMaterialFlag( video::EMF_GOURAUD_SHADING, false );
//		node->setMaterialFlag( video::EMF_LIGHTING, false );
//		// node->setMaterialFlag( video::EMF_NORMALIZE_NORMALS, false );
//		// node->setMaterialFlag( video::EMF_POINTCLOUD, false );
//		// node->setMaterialFlag( video::EMF_POLYGON_OFFSET, false );
//		node->setMaterialFlag( video::EMF_TRILINEAR_FILTER, true );
//		// node->setMaterialFlag( video::EMF_TEXTURE_WRAP, true );
//		// node->setMaterialFlag( video::EMF_USE_MIP_MAPS false );
//		node->setMaterialFlag( video::EMF_WIREFRAME, false );
//		// node->setMaterialFlag( video::EMF_ZBUFFER, true );
//		// node->setMaterialFlag( video::EMF_ZWRITE_ENABLE, true );
//	}
//
//	dbMakeCamera( 1 );
//	app.CurrentCamera = dbGetCameraPointer( 1 );
//	if (!app.CurrentCamera)
//	{
//		printf("Could not create FPS Camera !\n");
//	}
//	else
//	{
//		core::vector3df pos( 10,50,-100 );
//		core::vector3df eye( 0,0,0 );
//
////		if (node)
////		{
////			pos = node->getBoundingBox().getExtent();
////			pos *= 0.5f;
////			pos.Z *= -1.5f;
////		}
////
//		app.CurrentCamera->setPosition( pos );
//		app.CurrentCamera->setTarget( eye );
//	}

}

bool dbLoopGDK()
{
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


//	/// handle Timer
//	u32 dbTimer();
//	u32 dbScreenFPS();
//	u32 dbGetFrameCount();
//	u32 dbGetFrameCount();
//	u32 dbGetFrameCount();

u32 dbTimer()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return 0;

    return app.Device->getTimer()->getTime();
}

u32 dbPerfTimer()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return 0;

    return app.Device->getTimer()->getRealTime();
}

u32 dbGetFrameCount()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	return app.FrameCount;
}

u32 dbGetFPS()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	return app.FPS_Now;
}

u32 dbGetFPSMin()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	return app.FPS_Min;
}

u32 dbGetFPSMax()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	return app.FPS_Max;
}

u32 dbGetFPSAverage()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	return app.FPS_Avg;
}

u32 dbScreenFPS()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	IrrlichtDevice* device = (app.Device) ? app.Device : ( (app.NullDevice) ? app.NullDevice : 0 );
	if (!device)
		return 0;

    return (u32)device->getVideoDriver()->getFPS();
}

//	/// handle Monitor Infos
//	u32 dbDesktopWidth();
//	u32 dbDesktopHeight();
//	u32 dbDesktopDepth();
//	u32 dbScreenWidth();
//	u32 dbScreenHeight();
//	u32 dbScreenDepth();

u32 dbDesktopWidth()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.NullDevice)
		return 0;

    return app.NullDevice->getVideoModeList()->getDesktopResolution().Width;
}

u32 dbDesktopHeight()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.NullDevice)
		return 0;

    return app.NullDevice->getVideoModeList()->getDesktopResolution().Height;
}

u32 dbDesktopDepth()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.NullDevice)
		return 0;

    return app.NullDevice->getVideoModeList()->getDesktopDepth();
}

///@brief dbScreenWidth() - Get Width of MainWindow
u32 dbScreenWidth()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return 0;

    return app.Device->getVideoDriver()->getScreenSize().Width;
}

///@brief dbScreenHeight() - Get Height of MainWindow
u32 dbScreenHeight()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return 0;

    return app.Device->getVideoDriver()->getScreenSize().Height;
}

///@brief dbScreenDepth() - Get BitsPerPixel from MainWindow ColorFormat
u32 dbScreenDepth()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return 0;

    return video::IImage::getBitsPerPixelFromFormat( app.Device->getVideoDriver()->getColorFormat() );
}


//bool
//DarkGL_run()
//{
//    if (!SDK) return false;
//    if (!SDK->getDevice()) return false;
//    if (!SDK->getDevice()->run()) return false;
//
//    core::dimension2du screen = SDK->getDevice()->getVideoDriver()->getScreenSize();
//
//    if (screen != SDK->)
//
//        if ((ScreenSize.Width != oldScreenSize.Width) || (ScreenSize.Height != oldScreenSize.Height))
//        {
//            OnResizeEvent(ScreenSize.Width, ScreenSize.Height);
//        }
//
//    return true;
//}
//
//void
//DarkGL_resize(u32 w, u32 h)
//{
//    scene::ICameraSceneNode* cam = g_pGlob->smgr->getActiveCamera();
//    if (cam)
//    {
//        if (h==0) h=1;
//        if (w==0) w=1;
//        f32 aspect = f32)w / (f32)h;
//        cam->setAspectRatio((f32)w / (f32)h);
//        g_pGlob->logger->log( $("OnResizeEvent %d x %d with Aspect Ratio = %f",w,h,aspect), ELL_INFORMATION);
//        oldScreenSize.Width = w;
//        oldScreenSize.Height = h;
//    }
//}
//


//	void dbSetDisplayMode(u32 w, u32 h, u32 bpp, bool fullscreen, bool vSync);
//	void dbSyncOn();
//	void dbSyncOff();
//	void dbSyncRate(u32 rate);
//	void dbSync();
//  void dbYield();
//  void dbWait( u32 seconds );


bool dbSetDisplayMode( u32 w, u32 h, u32 bpp, bool fullscreen, bool vSync, bool antiAlias, bool anisotropFilter )
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	if (!app.Device)
		return false;

	video::IVideoDriver* driver = app.Device->getVideoDriver();

	core::dimension2du screenSize = driver->getScreenSize();

	driver->OnResize( core::dimension2du(w,h) );

	if (driver->getScreenSize() == screenSize)
		return false;
	else
		return true;
}


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

void dbSyncOn()
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

    app.SyncRate = 30;
    app.SyncWait = 33;
}

void dbSyncOff()
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

    app.SyncRate = 0;
    app.SyncWait = 0;
}

void dbSyncRate(u32 rate)
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

    app.SyncRate = rate;
    if (app.SyncRate > 0)
		app.SyncWait = 1000 / app.SyncRate;
    else
		app.SyncWait = 0;
}

void dbYield()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	if ( !app.Device )
		return;

	app.Device->yield();
}

void dbWait( u32 seconds )
{
    clock_t endwait;
    endwait = clock () + seconds * CLOCKS_PER_SEC ;
    while (clock() < endwait)
    {
        /* do nothing == idle */
    }
}


/// handle Window

void dbPositionWindow( u32 id, s32 x, s32 y)
{
    // DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    //app.Device->restoreWindow()
}

s32 dbWindowPositionX( u32 id )
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Device)
		return 0;
	return app.Device->getWindowPosition().X;
}

s32 dbWindowPositionY( u32 id )
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Device)
		return 0;
	return app.Device->getWindowPosition().Y;
}

u32 dbWindowWidth( u32 id )
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Device)
		return 0;
	return (u32)app.Device->getGUIEnvironment()->getRootGUIElement()->getAbsolutePosition().getWidth();
}

u32 dbWindowHeight( u32 id )
{
    DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
    if (!app.Device)
		return 0;
	return (u32)app.Device->getGUIEnvironment()->getRootGUIElement()->getAbsolutePosition().getHeight();
}

//	void dbSetWindowTitle(const wchar_t* title);
//	void dbSetWindowOn();
//	void dbSetWindowOff();
//	void dbMaximizeWindow();
//	void dbMinimizeWindow();
//	void dbPositionWindow( s32 x,s32 y);

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
