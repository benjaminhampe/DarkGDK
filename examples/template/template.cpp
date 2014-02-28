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


#include <DarkGDK/DarkGDK.h>

using namespace irr;
//using namespace core;
//using namespace scene;
//using namespace video;
//using namespace io;
//using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif



s32 main( s32 argc, c8** argv )
{
	const core::stringw AppTitle = L"StarBench (c) 2013 by benjaminhampe@gmx.de";

	// print CommandLine
	fprintf( stdout, "CommandLine ArgumentCount = %d\n", argc );
	for (u32 i=0; i<argc; i++)
		fprintf( stdout, "CommandLine Argv[%d] = %s\n", i, argv[i] );

	dbDarkGDK			( argc, argv );
	dbSetWindowTitle	( AppTitle.c_str() );
	dbSetDisplayMode	( dbDesktopWidth()-200, dbDesktopHeight()-200, dbDesktopDepth(), false, false );
	dbPositionWindow	( 0, 100, 100);

//	dbMakeObjectCube	( 1, 10.0f );
//	dbPositionObject	( 1, 100,0,0);

	dbMakeCamera		( 1 );
	dbPositionCamera	( 1, 434, 42, -517 );
	dbPointCamera		( 1, 0,0,0 );

	dbLoadObject        ( 2, "../../media/player/alien/alien.mdl" );
	dbSetObjectLight    ( 2, false );
	//dbSetObjectTexture  ( 2, 3, 2 );
	//dbScaleObject       ( 2, 5000, 5000, 5000 );


	// camera variables
	f32 fCameraAngleX = 0.0f;
	f32 fCameraAngleY = 0.0f;

	#ifdef _DEBUG
	SGlobalStruct& app = SGlobalStruct::getInstance();
	printf("Font used = %ld\n", app.Font);
	#endif // _DEBUG

	dbSetTextFont( "../../media/fonts/courier10.png" );

	u32 TimeLastWindowTitleUpdate = dbTimer();
	u32 TimeWaitWindowTitleUpdate = 200;

	while (dbLoopGDK())
	{
		dbInk( white, black );
		for (u32 i=0; i<20; i++)
			dbText( core::stringw(L"Hello World!"), 5,5+i*20);

		dbInk( white );
		dbCenterText( core::stringw(L"Hello World!"),
					dbScreenWidth()/2, dbScreenHeight()-32 );

        // move the camera using the arrow keys
        dbControlCameraUsingArrowKeys ( 1 );

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
			core::stringw txt = AppTitle;
			txt += L" | frames ";
			txt += dbGetFrameCount();
			txt += L", fps ";
			txt += dbGetFPS();
			txt += L", fps_min ";
			txt += dbGetFPSMin();
			txt += L", fps_max ";
			txt += dbGetFPSMax();
			dbSetWindowTitle( txt.c_str() );

			TimeLastWindowTitleUpdate = dbTimer();
		}


	}

	return 0;
}

/*
**/
