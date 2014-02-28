/// Siedler3d.cpp

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

#include <irrlicht.h>

#include <tinyDarkGDK.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

s32 main( s32 argc, c8** argv )
{
	/// print CommandLine ArgumentCount
	fprintf( stdout, "CommandLine ArgumentCount = %d\n", argc );

	/// print CommandLine
	for (u32 i=0; i<argc; i++)
		fprintf( stdout, "CommandLine Argv[%d] = %s\n", i, argv[i] );


	//create new application context
//	DarkGDK_App app( argc, argv, "ImageViewer (c) 2013 by benjaminhampe@gmx.de | ");
	dbDarkGDK( argc, argv );
	dbSetDisplayMode( dbDesktopWidth()-200, dbDesktopHeight()-200, dbDesktopDepth(), false, false );
	dbPositionWindow( 0, 100, 100);

//	dbMakeCamera( 1, 100.f, 1.5f );
//	dbPositionCamera( 1, 0,100,-100);
//	dbPointCamera( 1, 0,0,0 );

	// dbCls( 0xffffffff );
	// dbInk( black, yellow );

	dbMakeObjectCube( 1, 10.0f );
	dbPositionObject( 1, 100,0,0);

	while (dbLoopGDK())
	{
		dbInk( red );
		dbText( core::stringw(L"Hello World!"), 0,0);

		dbInk( blue );
		dbCenterText( core::stringw(L"Hello World!"), dbScreenWidth()/2, dbScreenHeight()-32 );

		dbSync();

	}

// dbLoadObject        ( "skybox2.x", 2 );
// dbSetObjectLight    ( 2, 0 );
// dbSetObjectTexture    ( 2, 3, 2 );
//    dbScaleObject        ( 2, 5000, 5000, 5000 );
//
//    // position the camera
//    dbPositionCamera    ( 434, 42, -517 );
//
//    // camera variables
//    float fCameraAngleX = 0.0f;
//    float fCameraAngleY = 0.0f;
//
//    // our main loop
//    while ( LoopGDK ( ) )
//    {
//        // move the camera using the arrow keys
//        dbControlCameraUsingArrowKeys ( 0, 5.0f, 0.3f );
//
//        // create a rotation axis based on mouse movement
//        fCameraAngleX = dbWrapValue ( fCameraAngleX + dbMouseMoveY ( ) * 0.4f );
//        fCameraAngleY = dbWrapValue ( fCameraAngleY + dbMouseMoveX ( ) * 0.4f );
//
//        // rotate camera
//        dbXRotateCamera ( fCameraAngleX );
//        dbYRotateCamera ( fCameraAngleY );
//
//        // update the screen
//        dbSync ( );
//    }
//

	return 0;
}


///@brief dbMakeObjectSiedlerBoard()
/**
*
*	@param objID Unique object-id
*	@param a X-width Dimension
*	@param b Y-height Dimension
*	@param c Z-depth Dimension
*
*/
//inline void dbMakeObjectSiedlerBoard( u32 objID, const core::vector3df& size )
//{
//	/// check id
//	if (dbObjectExist(objID))
//	{
//		printf("dbMakeObjectHexagon() :: Could not make object because id %d already exist.\n", objID );
//		return;
//	}
//
//	/// get instance
//	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
//	if (!app.Device)
//		return;
//
//	/// create mesh
//	scene::SMesh* mesh = new scene::SMesh();
//	if (!mesh)
//		return;
//
////	/// s32 texAtlas4x4
////    video::IImage* tmp = video::Tool::createRainbowImage( 128, 128, 255, 1.01f );
////
////	video::STexAtlas atlas( app.Device->getVideoDriver() );
////	video::Tool::createAtlas( atlas, core::dimension2du(4,4), core::dimension2du(128,128) );
////
////	video::IImage* tmp = video::Tool::createRainbowImage( 128, 128, 255, 1.01f );
////	video::Tool::setAtlasTile( atlas, tmp, 0,0);
////	video::Tool::setAtlasTile( atlas, tmp, 1,1);
////	video::Tool::setAtlasTile( atlas, tmp, 2,2);
////	video::Tool::setAtlasTile( atlas, tmp, 3,3);
////	video::Tool::updateAtlas( atlas );
//
//
//	/// create meshbuffer
//	scene::SMeshBuffer* buffer = new scene::SMeshBuffer();
//	if (buffer)
//	{
//		// bbox
//		if (XZPlane)
//			buffer->setBoundingBox( core::aabbox3df( -.5f*d, 0.f, -.5f*d, .5f*d, 0.f, .5f*d ) );
//		else
//			buffer->setBoundingBox( core::aabbox3df( -.5f*d,-.5f*d, 0.f, .5f*d, .5f*d, 0.f ) );
//
//		// material
//		if (color.getAlpha()<255)
//			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
//		else
//			buffer->Material.MaterialType = video::EMT_SOLID;
//
//		// vertices
//		buffer->Vertices.reallocate(6);
//		buffer->Vertices.set_used(0);
//		if (XZPlane)
//		{
//		buffer->Vertices.push_back( video::S3DVertex( -0.5f*d, 0, -0.25f*d, 0,0,-1, color, 0,   0.75f) );
//		buffer->Vertices.push_back( video::S3DVertex( -0.5f*d, 0,  0.25f*d, 0,0,-1, color, 0,   0.25f) );
//		buffer->Vertices.push_back( video::S3DVertex(  0, 0, 0.5f *d, 0,0,-1, color, 0.5f,0    ) );
//		buffer->Vertices.push_back( video::S3DVertex(  0.5f*d, 0,  0.25f*d, 0,0,-1, color, 1.0f,0.25f) );
//		buffer->Vertices.push_back( video::S3DVertex(  0.5f*d, 0, -0.25f*d, 0,0,-1, color, 1.0f,0.75f) );
//		buffer->Vertices.push_back( video::S3DVertex(  0, 0, -0.5f *d, 0,0,-1, color, 0.5f,1    ) );
//		}
//		else
//		{
//		buffer->Vertices.push_back( video::S3DVertex( -0.5f*d, -0.25f*d, 0, 0,0,-1, color, 0,   0.75f) );
//		buffer->Vertices.push_back( video::S3DVertex( -0.5f*d,  0.25f*d, 0, 0,0,-1, color, 0,   0.25f) );
//		buffer->Vertices.push_back( video::S3DVertex(  0, 0.5f *d, 0, 0,0,-1, color, 0.5f,0    ) );
//		buffer->Vertices.push_back( video::S3DVertex(  0.5f*d,  0.25f*d, 0, 0,0,-1, color, 1.0f,0.25f) );
//		buffer->Vertices.push_back( video::S3DVertex(  0.5f*d, -0.25f*d, 0, 0,0,-1, color, 1.0f,0.75f) );
//		buffer->Vertices.push_back( video::S3DVertex(  0, -0.5f *d, 0, 0,0,-1, color, 0.5f,1    ) );
//		}
//		// indices
//		buffer->Indices.reallocate(12);
//		buffer->Indices.set_used(0);
//		buffer->Indices.push_back( 0 );
//		buffer->Indices.push_back( 1 );
//		buffer->Indices.push_back( 3 ); // ABD
//		buffer->Indices.push_back( 0 );
//		buffer->Indices.push_back( 3 );
//		buffer->Indices.push_back( 4 ); // ADE
//		buffer->Indices.push_back( 1 );
//		buffer->Indices.push_back( 2 );
//		buffer->Indices.push_back( 3 ); // BCD
//		buffer->Indices.push_back( 0 );
//		buffer->Indices.push_back( 4 );
//		buffer->Indices.push_back( 5 ); // AEF
//
//		// add to mesh
//		mesh->addMeshBuffer(buffer);
//		mesh->BoundingBox = buffer->getBoundingBox();
//		buffer->drop();
//	}
//
//	mesh->setHardwareMappingHint( scene::EHM_STATIC);
//
//	/// add mesh to internal manager
//	dbMakeObjectFromMesh( objID, mesh);
//}
//
