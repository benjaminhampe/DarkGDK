/// Copyright (C) 2002-2013 Benjamin Hampe
/// This file is part of the "irrlicht-engine"
/// For conditions of distribution and use, see copyright notice in irrlicht.h

// Irrlicht Engine
#include <irrlicht.h>
#include <driverChoice.h>
#include <../source/Irrlicht/CColorConverter.cpp>
#include <../source/Irrlicht/CImage.cpp>
#include <../source/Irrlicht/os.cpp>

// Irrlicht extensions

#include <hampe.h>

// This Application
#include "MyEventReceiver.h"

#include "CGUIPlot.h"
#include "CGUIPlotManager.h"
#include "CGUIClassBuilder.h"

// Makro: FunctorType "f32 (f32)" this app uses
#if defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L
	#include <functional>
	#define Functor_f32_f32(x) std::function<f32 (const f32&)>((x))
#else
	#include <core/IFunction.h>
	#define Functor_f32_f32(x) (x)
#endif

using namespace irr;
using namespace scene::geometry;

s32 main( s32 argc, c8** argv)
{
	const c8* MY_TITLE = "CGUIPlot (c) 2013 by BenjaminHampe@gmx.de";

	video::E_DRIVER_TYPE DriverType = video::EDT_OPENGL;

	// we like to have some choice
	//DriverType = driverChoiceConsole(true);

	/// create NullDevice
	SIrrlichtCreationParameters params;
	params.DriverType = video::EDT_NULL;
	params.LoggingLevel = ELL_NONE;
	params.Fullscreen = false;

	IrrlichtDevice* nulldev = createDeviceEx( params );
    if (nulldev)
    {
		video::IVideoModeList* videoModes = nulldev->getVideoModeList();
        //params.WindowSize = videoModes->getDesktopResolution();
        //params.WindowSize -= core::dimension2du(100,100);
        params.WindowSize = core::dimension2du(800,600);
        params.Bits = videoModes->getDesktopDepth();

		nulldev->drop();
    }
    else
	{
		printf("Could not create Null device\n");
		exit(-1);
	}

	/// create Device

	params.LoggingLevel = ELL_INFORMATION;
	params.DriverType = DriverType;
	params.AntiAlias = video::EAAM_QUALITY;
	params.EventReceiver = 0;
	params.HighPrecisionFPU = true;
	params.Doublebuffer = true;
	params.Vsync = false;
	params.Fullscreen = false;
	// params.ZBufferBits = 32;
	// params.Stencilbuffer = true;
	// params.WithAlphaChannel = false;

	IrrlichtDevice* device = createDeviceEx( params );
	if (!device)
	{
		printf("Could not create device\n");
		exit(-2);
	}

	MyEventReceiver receiver( device );

	gui::IGUIEnvironment* env = device->getGUIEnvironment();
	video::IVideoDriver* driver = device->getVideoDriver();
	core::dimension2du screen = driver->getScreenSize();
	scene::ISceneManager* smgr = device->getSceneManager();
	ITimer* timer = device->getTimer();

    device->setResizable( true );
	device->setWindowCaption( core::stringw( MY_TITLE ).c_str() );

	//gui::IGUIFont* font = env->getBuiltInFont();

	/// create some functions of time f(t)

	CSineOscillator<f32> vco_0(1, 0, 3);
	CSineOscillator<f32> vco_1(2, 0, 2);
	CSineOscillator<f32> vco_2(3, 0, 1);

	CRectangleOscillator<f32> vco_3(1, 0.1f, 0.4f, 2, -1);

	CSawOscillator<f32> vco_4(1, 0, 0.5f, -0.5f);
	CSawOscillator<f32> vco_5(3, 0.5f, 3, 0);

	CADSREnvelope<f32> adsr(1,3,0.7,2, CADSREnvelope<f32>::EMTT_LINEAR);

	/// create IGUIWindow as container for CGUIPlot

	gui::IGUIWindow* plotWindow = env->addWindow(
		core::recti( 100,100,screen.Width-100, screen.Height-100 ),
		false, L"CGUIPlot Window", env->getRootGUIElement(), -1);

	/// create CGUIPlot

	gui::CGUIPlotManager* plotMgr = new gui::CGUIPlotManager( env, plotWindow, -1, plotWindow->getClientRect());

	gui::CGUIPlot* plot = plotMgr->addPlot( new gui::CGUIPlot( smgr, env, plotMgr, -1, plotMgr->getClientRect() ) );

	// left, bottom, right, top
	plot->setZoomRect( core::rectf( -1,-3,10,3) );

	plot->setDrawBackground( true );

	plot->setBackgroundColor( video::SColor(128,255,255,255) );



	scene::ISceneNode* smgrRoot = smgr->getRootSceneNode();

	/// PolyLine
	{
		scene::ISceneNode* node = createPolyLine<f32>( smgr, smgrRoot, Functor_f32_f32(vco_0), -1, 10, 2048, video::SColor(255,255,0,0), 0.75f, 0xfcfc );

		if (node) node->setDebugDataVisible( scene::EDS_BBOX );

		plot->addShape( "VCO_0", node );
	}

	/// PolyLine
	{
		scene::ISceneNode* node = createPolyLine<f32>( smgr, smgrRoot, Functor_f32_f32(vco_1), 0, 5, 2048, video::SColor(255,255,255,0), 1.5f, 0xdddd );

		if (node) node->setDebugDataVisible( scene::EDS_BBOX );

		plot->addShape( "VCO_1", node );
	}

	/// PolyLine
	{
		scene::ISceneNode* node = createPolyLine<f32>( smgr, smgrRoot, Functor_f32_f32(vco_2), 0, 5, 2048, video::SColor(255,0,0,255), .5f, 0xffff );

		if (node) node->setDebugDataVisible( scene::EDS_BBOX );

		plot->addShape( "VCO_2", node );
	}

	/// PolyLine
	{
		scene::ISceneNode* node = createPolyLine<f32>( smgr, smgrRoot, Functor_f32_f32(vco_3), 2, 8, 2048, video::SColor(255,255,0,255), 1.5f, 0xffff );

		if (node) node->setDebugDataVisible( scene::EDS_BBOX );

		plot->addShape( "VCO_3", node );
	}

	/// PolyLine
	{
		scene::ISceneNode* node = createPolyLine<f32>( smgr, smgrRoot, Functor_f32_f32(vco_4), 0, 8, 1024, video::SColor(255,0,192,0), .5f, 0xffff );

		if (node) node->setDebugDataVisible( scene::EDS_BBOX );

		plot->addShape( "VCO_4", node );
	}

	/// PolyLine [ADSR-curve]
	{
		scene::ISceneNode* node = createPolyLine<f32>( smgr, smgrRoot, Functor_f32_f32(adsr), 0, 8, 1024, video::SColor(255,192,0,192), .5f, 0xffff );

		// if (node) node->setDebugDataVisible( scene::EDS_BBOX );

		plot->addShape( "ADSR-Curve", node );
	}

	/// [main loop]

	u32 timeLastWindowTitleUpate(0);

	u32 timeWaitWindowTitleUpate(500);

    while (device->run())
    {
		/// Resize-Event

      	if (screen != driver->getScreenSize() )
		{
			screen = driver->getScreenSize();

			scene::ICameraSceneNode* camera = smgr->getActiveCamera();
			if (camera)
			{
				f32 aspect = (f32)screen.Width / (f32)screen.Height;
				camera->setAspectRatio( aspect );
			}
		}

		/// if window is active ( can be minimized but still active )
        if (device->isWindowActive())
        {

			/// if window is active ( can be minimized but still active )
			if (device->isWindowFocused())
			{

				/// render all

				driver->beginScene( true, true, video::SColor(255,225,225,225) );

				smgr->drawAll();

				env->drawAll();

				driver->endScene();


				/// window-title update

				if ( timer->getRealTime() - timeLastWindowTitleUpate > timeWaitWindowTitleUpate )
				{
					core::stringw txt = core::stringw( MY_TITLE );
					txt += L" | fps( ";
					txt += driver->getFPS();
					txt += L" ), poly( ";
					txt += driver->getPrimitiveCountDrawn(); txt += L" / ";
					txt += driver->getMaximalPrimitiveCount(); txt += L" ), ";

//					scene::ICameraSceneNode* cam = smgr->getActiveCamera();
//					if (cam)
//					{
//						const core::vector3df& pos = cam->getAbsolutePosition();
//						txt += L"cam( pos(";
//						txt += core::round32(pos.X); txt += L",";
//						txt += core::round32(pos.Y); txt += L",";
//						txt += core::round32(pos.Z); txt += L"), ";
//
//						const core::vector3df& eye = cam->getTarget();
//						txt += L"eye(";
//						txt += core::round32(eye.X); txt += L",";
//						txt += core::round32(eye.Y); txt += L",";
//						txt += core::round32(eye.Z); txt += L"), ";
//						txt += L"near(";
//						txt += cam->getNearValue();
//						txt += L"), far(";
//						txt += core::round32(cam->getFarValue() ); txt += L")";
//						txt += L" )";
//					}

					device->setWindowCaption( txt.c_str() );

					timeLastWindowTitleUpate = timer->getRealTime();
				}
			}
			else
			{
				device->yield();
			}
		}
        else
        {
            device->yield();
        }
    }

	if (device)
		device->drop();

	return 0;
}
