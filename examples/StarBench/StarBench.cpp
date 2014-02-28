/// StarBench.cpp

///@author BenjaminHampe@gmx.de

//
// available ImageLoader: BMP,JPG,TGA,PSD,DDS,PCX,PNG,WAL,HalfLife,LMP,PPM,RGB
// available ImageWriter: BMP,JPG,TGA,PSD,PCX,PNG,PPM
//
// We need this include for the case of skinned mesh support without any such loader
// _IRR_COMPILE_WITH_SKINNED_MESH_SUPPORT_
//
// available ModelWriter: 	BSP,MD2,MDL,MS3D,3DS,X,OCT,CSM,LMTS,MY3D,COLLADA,
//							DMF,OGRE,OBJ,MD3,B3D,LWO,STL,PLY,SMF,IRR
// available ModelWriter: 	COLLADA,IRR,STL,OBJ,PLY
//


#include <DarkGDK.h>
#include <imageTool.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "DarkGDK.lib")
#endif

/// test 4x4 imageAtlas
void dbTestTexAtlas( IVideoDriver* driver )
{
	if (!driver)
		return;

	STexAtlas atlas( driver );
	Tool::createAtlas( atlas, core::dimension2du(4,4), core::dimension2du(128,128) );

    IImage* rainbowImage = Tool::createRainbowImage( 128, 128, 255, 1.01f );
	Tool::setAtlasTile( atlas, rainbowImage, 0,0);
	Tool::setAtlasTile( atlas, rainbowImage, 1,1);
	Tool::setAtlasTile( atlas, rainbowImage, 2,2);
	Tool::setAtlasTile( atlas, rainbowImage, 3,3);
	Tool::deleteImage( rainbowImage );

	IImage* tileWasser = video::Tool::loadImage( driver, "../../media/siedler3d/" );

	Tool::deleteImage( rainbowImage );


	Tool::updateAtlas( atlas );
	Tool::saveImage( driver, atlas.Image, "./save_texatlas.png" );
	Tool::saveImage( driver, atlas.Image, "./save_texatlas.jpg" );
}

s32 main( s32 argc, c8** argv )
{
	const core::stringw AppTitle = L"StarBench (c) 2013 by benjaminhampe@gmx.de";

	/// print CommandLine
	printf( "CommandLine ArgumentCount = %d\n", argc );
	for (s32 i=0; i<argc; i++)
		printf( "CommandLine Argv[%d] = %s\n", i, argv[i] );


	/// ask user for driver
	printf("Please select the driver you want for this example:\n"\
		" (a) OpenGL 1.5\n (b) Direct3D 9.0c\n (c) Direct3D 8.1\n"\
		" (d) Burning's Software Renderer\n (e) Software Renderer\n"\
		" (f) NullDevice\n (otherKey) exit\n\n");

	E_DRIVER_TYPE driverType;
	char i;
	std::cin >> i;
	switch(i)
	{
		case 'a': driverType = EDT_OPENGL;   break;
		case 'b': driverType = EDT_DIRECT3D9;break;
		case 'c': driverType = EDT_DIRECT3D8;break;
		case 'd': driverType = EDT_BURNINGSVIDEO;break;
		case 'e': driverType = EDT_SOFTWARE; break;
		case 'f': driverType = EDT_NULL;     break;
		default: return 1;
	}

	/// DarkGDK

	dbDarkGDK			( argc, argv );
	dbSetWindowTitle	( AppTitle.c_str() );
	dbSetDisplayMode	( 1024, 786, dbDesktopDepth(), false, false );
	// dbSetDisplayMode	( dbDesktopWidth()-200, dbDesktopHeight()-200, dbDesktopDepth(), false, false );
	dbPositionWindow	( 0, 100, 100);

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	dbTestTexAtlas( app.Device->getVideoDriver() );

	/// save old directory
	io::path old_dir = dbGetDir();

	/// set new directory
	dbSetDir( "../../media" );

	/// list files in directory
	const StringArray files = dbGetFiles();

	/// list files in archive
	const StringArray files_in_zip = dbGetFilesFromArchive( "maps/crp_de_dust.pk3" );

	/// create camera ( create first because of possible need as rendertarget )
	dbMakeCamera		( 1 );
	dbPositionCamera	( 1, 0, 100, -100 );
	dbPointCamera		( 1, 0,0,0 );

	/// create first object
	// dbMakeObjectCube	( 1, 10.0f );
	// dbPositionObject	( 1, 100,0,0);

	/// create skybox
	u32 skybox = dbGetFreeObjectID();
	dbMakeObjectBox ( skybox, 1000,1000,1000 );

//	dbSetObjectLight    ( skybox, false );
//	dbPositionObject	( skybox, 100,0,0 );

	/// create floor
	u32 ground = dbGetFreeObjectID();
	dbMakeObjectPlain	( ground, 10.0f, 10.0f, SColor(255,50,168,60) );
	dbPositionObject	( ground, 0,-1000,0);
//	dbLoadObject        ( ground, "../../media/player/alien/alien.mdl" );
	dbSetObjectLight    ( ground, false );

	/// create sun
//	u32 sun = dbGetFreeObjectID();
//	dbLoadObject        ( sun, "../../media/player/alien/alien.mdl" );
//	dbSetObjectLight    ( sun, false );
//	dbPositionObject	( sun, 100,0,0 );

//	u32 map1 = dbGetFreeObjectID();
//	dbLoadObjectPK3     ( map1, "crp_de_dust.pk3", "de_dust.bsp" );
//	dbSetObjectLight    ( map1, false );
//	dbPositionObject	( map1, 100,0,0 );

	/// create player
	dbLoadObject        ( 1, "player/guerilla/guerilla.mdl" );
	dbSetObjectLight    ( 1, false );
	dbPositionObject	( 1, 0,0,0 );

	dbLoadObject        ( 2, "player/alien/alien.mdl" );
	dbSetObjectLight    ( 2, false );
	dbPositionObject	( 2, 100,0,0 );
	//dbSetObjectTexture  ( 2, 3, 2 );
	dbScaleObject       ( 2, 1, 1, 1 );


	/// create world
	u32 map2 = dbGetFreeObjectID();

	dbLoadObjectPK3     ( map2, "maps/stargate.pk3", "STARGATE.bsp" );
	// dbLoadObjectPK3     ( map2, "stargate_atlantis.pk3", "stargate_atlantis.bsp" );
	// dbLoadObjectPK3     ( map2, "sylars_spacewalk.pk3", "spacewalk.bsp" );
	dbSetObjectLight    ( map2, false );
	dbSetObjectFog	    ( map2, false );
	dbSetObjectFrontCull( map2, false );
	dbSetObjectBackCull ( map2, true );

	dbPositionObject	( map2, 0,-500,0 );
//
//	u32 map3 = dbGetFreeObjectID();
//	dbLoadObjectPK3        ( map3, "stargate_atlantis.pk3" );
//	dbSetObjectLight    ( map3, false );
//	dbPositionObject	( map3, 100,0,0 );

	// camera variables
	f32 fCameraAngleX = 0.0f;
	f32 fCameraAngleY = 0.0f;

	dbSetTextFont( "fonts/courier10.png" );

	u32 TimeLastWindowTitleUpdate = dbTimer();
	u32 TimeWaitWindowTitleUpdate = 200;

	s32 x,y;

	core::stringc t;

	while (dbLoopGDK())
	{
       // move the camera using the arrow keys
        dbControlCameraUsingArrowKeys ( 1 );

		/// Hello World! ( top center )
		dbInk( white );
		dbCenterText( core::stringw(L"Hello World!"), dbScreenWidth()/2, 5 );

		/// info-box ( left bottom )
		dbInk( yellow, black );
		x = 5;
		y = dbScreenHeight() - 5;
		dbPositionCursor( x, y, -1, 1 );
		t = "version = "; t += dbGetVersion(); dbPrint( t );
		t = "vendor = "; t += dbGetVendor(); dbPrint( t );
		t = "driver = "; t += dbGetDriverString(); dbPrint( t );
		t = "fps = "; t += dbScreenFPS(); dbPrint( t );
		t = "tris = "; t += dbGetPolygonCount(); dbPrint( t );

		t = "desktop ("; t += dbDesktopWidth();
		t = ","; t += dbDesktopHeight();
		t = ","; t += dbDesktopDepth();
		t = ")"; dbPrint( t );

		t = "screen ("; t += dbScreenWidth();
		t = ","; t += dbScreenHeight();
		t = ","; t += dbScreenDepth();
		t = ")"; dbPrint( t );

		t = "rtt_w = "; t += dbDesktopWidth(); dbPrint( t );
		t = "rtt_h = "; t += dbDesktopHeight(); dbPrint( t );
		t = "rtt_bpp = "; t += dbDesktopDepth(); dbPrint( t );

		t = "old-dir = "; t += old_dir; dbPrint( t );
		t = "get-dir = "; t += dbGetDir(); dbPrint( t );


		/// print files in current directory
		dbInk( white, SColor(123,0,0,0 ) );
		dbText( files, dbScreenWidth()-6, 5, 1, -1);

		//dbPositionCursor( dbScreenWidth()/2,dbScreenHeight()-400 );
		//dbPrint( files_in_zip );


		/// print number of object-list-item
		x = dbScreenWidth()-600;
		y = dbScreenHeight()-200;
		dbPositionCursor( x,y );
        const u32 obj_count = dbGetObjectCount();
		t = "obj_count = "; t += obj_count; dbPrint( t );

		/// print object-list
		for (u32 i = 1; i <= obj_count; i++)
		{
			core::vector3df s = dbGetObjectSize( i );
			t =  "obj[" ;
			t += i;
			t += "] - size(";
			t += s.X;
			t += ", ";
			t += s.Y;
			t += ", ";
			t += s.Z;
			t += ")";
			dbPrint( t );
		}

        // create a rotation axis based on mouse movement
//        fCameraAngleX = dbWrapValue ( fCameraAngleX + dbMouseMoveY ( ) * 0.4f );
//        fCameraAngleY = dbWrapValue ( fCameraAngleY + dbMouseMoveX ( ) * 0.4f );
//
//        // rotate camera
//        dbXRotateCamera ( 1, fCameraAngleX );
//        dbYRotateCamera ( 1, fCameraAngleY );

        // update the screen
		dbSync();

		if ( dbTimer() > TimeLastWindowTitleUpdate + TimeWaitWindowTitleUpdate)
		{
			core::stringw t = AppTitle;
			t += L" | frames ";
			t += dbGetFrameCount();
			t += L", polys ";
			t += dbGetPolygonCount();
			t += L", fps ";
			t += dbGetFPS();
			t += L", fps_min ";
			t += dbGetFPSMin();
			t += L", fps_max ";
			t += dbGetFPSMax();
			dbSetWindowTitle( t.c_str() );

			TimeLastWindowTitleUpdate = dbTimer();
		}


	}

	return 0;
}

/*
**/
