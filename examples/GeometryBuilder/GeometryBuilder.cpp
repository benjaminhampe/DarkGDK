/// FPS-Cube.cpp

///@author BenjaminHampe@gmx.de

#include <DarkGDK.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "DarkGDK.lib")
#endif

/// DarkGDK example

s32 main( s32 argc, c8** argv )
{
	const core::stringw AppTitle = L"FPS-Cube (c) 2013 by benjaminhampe@gmx.de";

	dbDarkGDK			( argc, argv );
	dbSetWindowTitle	( AppTitle.c_str() );
	dbSetDisplayMode	( 1024, 786, 32, false, false );
	// dbSetDisplayMode	( dbDesktopWidth()-200, dbDesktopHeight()-200, dbDesktopDepth(), false, false );
	dbPositionWindow	( 0, 100, 100);

	/// create camera ( create first because of possible need as rendertarget )
	dbMakeCamera		( 1 );
	dbPositionCamera	( 1, 0, 100, -100 );
	dbPointCamera		( 1, 0,0,0 );

	/// create skybox
	u32 skybox = dbGetFreeObjectID();
	dbMakeObjectBox ( skybox, 10000,10000,10000 );
	dbSetObjectBackCull( skybox, false );

	u32 texmon = dbGetFreeImageID();
	dbLoadImage( texmon, "../../media/sysmon.png");
	dbTextureObject( skybox, texmon, 0 );

	//u32 textroll = dbGetFreeImageID();
	//dbLoadImage( textroll, "../../media/trollface.png");
	//dbTextureObject( skybox, texmon, 1 );

	//dbSetObjectLight ( skybox, false );
	//dbPositionObject( skybox, 100,0,0 );

	/// create floor
	u32 ground = dbGetFreeObjectID();
	dbMakeObjectPlain	( ground, 100.0f, 100.0f, SColor(255,50,168,60) );
	dbPositionObject	( ground, 0,0,0);
	//	dbLoadObject        ( ground, "../../media/player/alien/alien.mdl" );
	dbSetObjectLight    ( ground, false );

	/// create sun
//	u32 sun = dbGetFreeObjectID();
//	dbLoadObject        ( sun, "../../media/player/alien/alien.mdl" );
//	dbSetObjectLight    ( sun, false );
//	dbPositionObject	( sun, 100,0,0 );

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

		t = "get-dir = "; t += dbGetDir(); dbPrint( t );

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
