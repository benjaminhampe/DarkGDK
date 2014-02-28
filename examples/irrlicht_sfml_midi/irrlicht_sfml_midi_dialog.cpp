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

using namespace irr;

s32 main( s32 argc, c8** argv )
{
	const c8* app_title = "SFML-Audio and RtMidi Settings Dialog for Irrlicht-Engine";

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
	// ERROR_NULL_POINTER(device, "Could not create Device\n");

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
	// myNode->drop();
	// myNode = 0; // As I shouldn't refer to it again, ensure that I can't

	/*
	Now draw everything and finish.
	*/
	u32 frames=0;
	while( device && device->run() )
	{
		driver->beginScene(true, true, video::SColor(0,100,100,100));

		smgr->drawAll();

		env->drawAll();

		driver->endScene();

		if (++frames==100)
		{
			core::stringw str = L"Irrlicht Engine [";
			str += driver->getName();
			str += L"] FPS: ";
			str += (s32)driver->getFPS();

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
