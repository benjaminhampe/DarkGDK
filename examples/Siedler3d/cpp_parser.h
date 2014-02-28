/** sfml audio + midi options dialog for irrlicht-engine 1.9svn

*/



#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif


/*
	Main
*/

#include <windows.h>

namespace irr
{

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
