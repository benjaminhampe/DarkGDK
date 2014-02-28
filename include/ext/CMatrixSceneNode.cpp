// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include <CMatrixSceneNode.h>

namespace irr
{
namespace scene
{

//! default constructor - value ctr ( by render-shape, shape-size, color-gradient, matrix-data, irr::scene::ISceneNode-interface )
CMatrixSceneNode::CMatrixSceneNode(
	scene::E_PRIMITIVE_TYPE shapeType,
	const core::vector3df& shapeSize,
	video::IColorGradient* colorGradient,
	core::CMatrix<f32>* matrixData,
	ISceneManager* smgr, ISceneNode* parent, s32 id, const core::vector3df& position,
	const core::vector3df& rotation, const core::vector3df& scale )

: ISceneNode( parent, smgr, id, position, rotation, scale)

, PrimitiveType( shapeType )

, ColorGradient( colorGradient )

, Data( matrixData )

, BoundingBox( core::aabbox3df( core::vector3df(0,0,0), shapeSize ))

//, IsTextureAtlas(false), AtlasTileSize(0,0), IsBillBoard(false)

{
	#ifdef _DEBUG
		os::Printer::log("CMatrixSceneNode()", ELL_INFORMATION);
	#endif // _DEBUG

	if (Data)
		Data->grab();

	if (ColorGradient)
		ColorGradient->grab();

	createMesh();
}

//! destructor
CMatrixSceneNode::~CMatrixSceneNode()
{
	clear();
}


//! create mesh by PrimtitiveType
bool CMatrixSceneNode::createMesh()
{
	bool result = false;
	switch (PrimitiveType)
	{
		case EPT_POINTS: result = createMeshAsPointCloud(); break;
		case EPT_POINT_SPRITES: result = createMeshAsTexturedBillboards(); break;
		case EPT_LINES: result = createMeshAsLines(); break;
		case EPT_LINE_STRIP: result = createMeshAsLineStrips(); break;
		case EPT_LINE_LOOP: result = createMeshAsLineStrips(); break;
		//case EPT_TRIANGLES: result = createMeshAsTriangles(); break;
		case EPT_TRIANGLES: result = createMeshAsLogarithmicTriangles(); break;
		case EPT_TRIANGLE_FAN: result = createMeshAsTriangles(); break;
		case EPT_POLYGON: result = createMeshAsTriangles(); break;
		case EPT_QUADS:	result = createMeshAsTrianglesWithTextureAtlas(); break;
		case EPT_QUAD_STRIP: result = createMeshAsTexturedBillboards(); break;
		default: break;
	}
	return result;
}

void CMatrixSceneNode::clear()
{
	Vertices.clear();
	Indices.clear();

	if (Data)
	{
		Data->drop();
		Data = 0;
	}

	if (ColorGradient)
	{
		ColorGradient->drop();
		ColorGradient = 0;
	}

}

/// render

void CMatrixSceneNode::render()
{
	if (!IsVisible)
		return;

	video::IVideoDriver* driver = SceneManager->getVideoDriver();

    core::matrix4 oldWorldMatrix = driver->getTransform(video::ETS_WORLD);

    driver->setTransform(video::ETS_WORLD, getAbsoluteTransformation());

	driver->setMaterial( Material );

	video::drawElements( driver, Vertices, Indices, PrimitiveType );


	if (DebugDataVisible & EDS_BBOX)
	{
		video::SMaterial debugMaterial;
		debugMaterial.MaterialType = video::EMT_SOLID;
		debugMaterial.Lighting = false;
		debugMaterial.FogEnable = false;
		debugMaterial.Wireframe = false;

		driver->draw3DBox( BoundingBox );
	}

	driver->setTransform(video::ETS_WORLD, oldWorldMatrix);
}

//! create Logarithmic Triangles Mesh

bool CMatrixSceneNode :: createMeshAsLogarithmicTriangles()

{
	if (!Data)	return false;

	const u32 r = Data->getRows();

	const u32 c = Data->getCols();

	if ((r==0) || (c==0))	return false;

	Vertices.reallocate( 4*(r-1)*(c-1) );
	Vertices.set_used( 0 );

	Indices.reallocate( 6*(r-1)*(c-1) );
	Indices.set_used( 0 );

	Material.MaterialType = (ColorGradient)?ColorGradient->getMaterialType():video::EMT_SOLID;
	Material.Lighting = false;
	Material.Wireframe = false;
	Material.FogEnable = false;

	const core::vector3df& mesh_size_ = BoundingBox.getExtent();

	const core::vector2df data_min_max_(0,160); // = Data->getMinMax(); // = Data->getMinMax();

	const f32 data_range_inv_ = core::reciprocal( data_min_max_.Y-data_min_max_.X /* in dB */ );

	const f32 step_x = mesh_size_.X / (f32)(c-1);
	const f32 step_y = mesh_size_.Y * data_range_inv_;
	const f32 step_z = mesh_size_.Z / (f32)(r-1);

	f32 y1, y2, y3, y4;
	f32 t1, t2, t3, t4;
	video::SColor c1, c2, c3, c4;
	c1 = video::SColor(255,100,100,255);
	c2 = c1;
	c3 = c1;
	c4 = c1;

	/// loop rows ( y-direction )
	for (u32 y=0; y<r-1; y++)
	{
		/// loop columns ( x-direction )
		for (u32 x=0; x<c-1; x++)
		{
			y1 = Data->getElement(y,x); // normalized y-height to range 0..1, needed for color-gradient
			y2 = Data->getElement(y+1,x);	// normalized y-height to range 0..1, needed for color-gradient
			y3 = Data->getElement(y+1,x+1);	// normalized y-height to range 0..1, needed for color-gradient
			y4 = Data->getElement(y,x+1);	// normalized y-height to range 0..1, needed for color-gradient

			if (ColorGradient)
			{
				t1 = (y1-data_min_max_.X)*data_range_inv_; // normalized y-height to range 0..1, needed for color-gradient
				t2 = (y2-data_min_max_.X)*data_range_inv_;	// normalized y-height to range 0..1, needed for color-gradient
				t3 = (y3-data_min_max_.X)*data_range_inv_;	// normalized y-height to range 0..1, needed for color-gradient
				t4 = (y4-data_min_max_.X)*data_range_inv_;	// normalized y-height to range 0..1, needed for color-gradient

				c1 = ColorGradient->getColor(t1);
				c2 = ColorGradient->getColor(t2);
				c3 = ColorGradient->getColor(t3);
				c4 = ColorGradient->getColor(t4);
			}

			f32 x1 = core::clamp<f32>(1.0f-(f32)(x+1)/(f32)c, 0.0f, 1.0f );
			f32 x2 = core::clamp<f32>(1.0f-(f32)(x+2)/(f32)c, 0.0f, 1.0f );

			u32 k = Vertices.size();

			Vertices.push_back( video::S3DVertex( (f32)x1*mesh_size_.X,y1*step_y,(f32)y*step_z, 0,0,-1, c1, 0,0) );
			Vertices.push_back( video::S3DVertex( (f32)x1*mesh_size_.X,y2*step_y,(f32)(y+1)*step_z, 0,0,-1, c2, 0,0) );
			Vertices.push_back( video::S3DVertex( (f32)x2*mesh_size_.X,y3*step_y,(f32)(y+1)*step_z, 0,0,-1, c3, 0,0) );
			Vertices.push_back( video::S3DVertex( (f32)x2*mesh_size_.X,y4*step_y,(f32)y*step_z, 0,0,-1, c4, 0,0) );

			Indices.push_back( k );
			Indices.push_back( k+1 );
			Indices.push_back( k+2 );
			Indices.push_back( k );
			Indices.push_back( k+2 );
			Indices.push_back( k+3 );
		}
	}
	return true;
}


//! create Triangles Mesh

bool CMatrixSceneNode :: createMeshAsTriangles()
{
	if (!Data)	return false;

	const u32 r = Data->getRows();

	const u32 c = Data->getCols();

	if ((r==0) || (c==0))	return false;

	Vertices.reallocate( 4*(r-1)*(c-1) );
	Vertices.set_used( 0 );

	Indices.reallocate( 6*(r-1)*(c-1) );
	Indices.set_used( 0 );

	Material.MaterialType = (ColorGradient)?ColorGradient->getMaterialType():video::EMT_SOLID;
	Material.Lighting = false;
	Material.Wireframe = false;
	Material.FogEnable = false;

	const core::vector3df& mesh_size_ = BoundingBox.getExtent();

	const core::vector2df data_min_max_(0,160); // = Data->getMinMax(); // = Data->getMinMax();

	const f32 data_range_inv_ = core::reciprocal( data_min_max_.Y-data_min_max_.X /* in dB */ );

	const f32 step_x = mesh_size_.X / (f32)(c-1);
	const f32 step_y = mesh_size_.Y * data_range_inv_;
	const f32 step_z = mesh_size_.Z / (f32)(r-1);

	f32 y1, y2, y3, y4;
	f32 t1, t2, t3, t4;
	video::SColor c1, c2, c3, c4;
	c1 = video::SColor(255,100,100,255);
	c2 = c1;
	c3 = c1;
	c4 = c1;

	/// loop rows ( y-direction )
	for (u32 y=0; y<r-1; y++)
	{
		/// loop columns ( x-direction )
		for (u32 x=0; x<c-1; x++)
		{
			y1 = Data->getElement(y,x); // normalized y-height to range 0..1, needed for color-gradient
			y2 = Data->getElement(y+1,x);	// normalized y-height to range 0..1, needed for color-gradient
			y3 = Data->getElement(y+1,x+1);	// normalized y-height to range 0..1, needed for color-gradient
			y4 = Data->getElement(y,x+1);	// normalized y-height to range 0..1, needed for color-gradient

			if (ColorGradient)
			{
				t1 = (y1-data_min_max_.X)*data_range_inv_; // normalized y-height to range 0..1, needed for color-gradient
				t2 = (y2-data_min_max_.X)*data_range_inv_;	// normalized y-height to range 0..1, needed for color-gradient
				t3 = (y3-data_min_max_.X)*data_range_inv_;	// normalized y-height to range 0..1, needed for color-gradient
				t4 = (y4-data_min_max_.X)*data_range_inv_;	// normalized y-height to range 0..1, needed for color-gradient

				c1 = ColorGradient->getColor(t1);
				c2 = ColorGradient->getColor(t2);
				c3 = ColorGradient->getColor(t3);
				c4 = ColorGradient->getColor(t4);
			}

//			t1 = (y1-data_min_max_.X)*data_range_inv_; // normalized y-height to range 0..1, needed for color-gradient
//			t2 = (y2-data_min_max_.X)*data_range_inv_;	// normalized y-height to range 0..1, needed for color-gradient
//			t3 = (y3-data_min_max_.X)*data_range_inv_;	// normalized y-height to range 0..1, needed for color-gradient
//			t4 = (y4-data_min_max_.X)*data_range_inv_;	// normalized y-height to range 0..1, needed for color-gradient
//
//			u32 cf = core::s32_clamp( (s32)(t1*255.0f), 0, 255);
//			c1 = video::SColor( 255, 0,0,cf ); // video::SColor( 255, cf,cf,255 );
//			cf = core::s32_clamp( (s32)(t2*255.0f), 0, 255);
//			c2 = video::SColor( 255, 0,0,cf ); // video::SColor( 255, cf,cf,255 );
//			cf = core::s32_clamp( (s32)(t3*255.0f), 0, 255);
//			c3 = video::SColor( 255, 0,0,cf ); // video::SColor( 255, cf,cf,255 );
//			cf = core::s32_clamp( (s32)(t4*255.0f), 0, 255);
//			c4 = video::SColor( 255, 0,0,cf ); // video::SColor( 255, cf,cf,255 );

			u32 k = Vertices.size();

			Vertices.push_back( video::S3DVertex( (f32)x*step_x,y1*step_y,(f32)y*step_z, 0,0,-1, c1, 0,0) );
			Vertices.push_back( video::S3DVertex( (f32)x*step_x,y2*step_y,(f32)(y+1)*step_z, 0,0,-1, c2, 0,0) );
			Vertices.push_back( video::S3DVertex( (f32)(x+1)*step_x,y3*step_y,(f32)(y+1)*step_z, 0,0,-1, c3, 0,0) );
			Vertices.push_back( video::S3DVertex( (f32)(x+1)*step_x,y4*step_y,(f32)y*step_z, 0,0,-1, c4, 0,0) );

			Indices.push_back( k );
			Indices.push_back( k+1 );
			Indices.push_back( k+2 );
			Indices.push_back( k );
			Indices.push_back( k+2 );
			Indices.push_back( k+3 );
		}
	}
	return true;
}


//! create Lines Mesh
bool CMatrixSceneNode::createMeshAsLineStrips()
{
	#ifdef _DEBUG
	printf("createMeshAsLineStrips()\n");
	#endif // _DEBUG

	if (!Data)
		return false;

	const u32& rows = Data->getRows();
	const u32& cols = Data->getCols();

	if ((rows==0) || (cols==0))
		return false;

	Vertices.reallocate( rows*cols*4 );
	Vertices.set_used( 0 );
	Indices.reallocate( rows*cols*6 );
	Indices.set_used( 0 );


	Material.MaterialType = video::EMT_SOLID;
	Material.PointCloud = true;
	//PrimitiveType = EPT_POINTS;
	//Material.MaterialType = video::EMT_SOLID;
	//video::EMT_TRANSPARENT_VERTEX_ALPHA;
	//(ColorGradient)?ColorGradient->getMaterialType():video::EMT_SOLID;
	//Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
	Material.Thickness = 3.55f;
	Material.Lighting = false;
	Material.Wireframe = false;
	Material.FogEnable = false;

	const core::vector3df& mesh_size_ = BoundingBox.getExtent();
	const core::vector2df data_min_max_(0,160); // = Data->getMinMax(); // = Data->getMinMax();
	const f32 data_range_ = data_min_max_.Y-data_min_max_.X /* in dB */;
	const f32 data_range_inv_ = core::reciprocal( data_range_ );

	const f32 step_x = mesh_size_.X / (f32)(cols-1);
	const f32 step_y = mesh_size_.Y * data_range_inv_;
	const f32 step_z = mesh_size_.Z / (f32)(rows-1);

//	#ifdef _DEBUG
//	printf( "DataMinMax = ( %f, %f )\n", data_min_max_.X, data_min_max_.Y );
//	printf( "DataRange = ( %f, %f )\n", data_range_, data_range_inv_ );
//	printf( "MeshExtent = ( %f, %f, %f )\n", MeshExtent.X, MeshExtent.Y, MeshExtent.Z );
//	printf( "StepSizes = ( %f, %f, %f )\n", step_x, step_y, step_z);
//	#endif // _DEBUG

	/// loop rows ( y-direction )
//	for (u32 y=0; y<rows; y++)
//	{
//		for (u32 x=0; x<cols-1; x++)
//		{
//			const f32 y0 = Data->getElement(y,x);
//			const f32 y1 = Data->getElement(y,x+1);
//			const f32 t0 = (y0 - data_min_max_.X) * DataRangeInv;
//			const f32 t1 = (y1 - data_min_max_.X) * DataRangeInv;
//			const video::SColor c0 = (ColorGradient)?ColorGradient->getColor( t0 ):0xffffffff;
//			const video::SColor c1 = (ColorGradient)?ColorGradient->getColor( t1 ):0xffffffff;
//
//			const u32 k = Vertices.size();
//
//			Vertices.push_back( video::S3DVertex( (f32)x*step_x, y0*step_y, (f32)y*step_z, 0,0,-1, c0, 0,0) );
//			Vertices.push_back( video::S3DVertex( (f32)(x+1)*step_x, y1*step_y, (f32)y*step_z, 0,0,-1, c1, 0,0) );
//			Indices.push_back( k );
//			Indices.push_back( k+1 );
//		}
//	}

	/// loop columns ( x-direction )
	for (u32 x=0; x<cols; x++)
	{
		for (u32 y=0; y<rows-1; y++)
		{
			const f32 y0 = Data->getElement(y,x);
			//const f32 y1 = Data->getElement(y+1,x);
			const f32 t0 = (y0 - data_min_max_.X) * data_range_inv_;
			//const f32 t1 = (y1 - data_min_max_.X) * DataRangeInv;
			const video::SColor c0 = (ColorGradient)?ColorGradient->getColor( t0 ):0xffffffff;
			//const video::SColor c1 = (ColorGradient)?ColorGradient->getColor( t1 ):0xffffffff;
			//c0.setAlpha( 128 );
			const u32 k = Vertices.size();

			Vertices.push_back( video::S3DVertex( (f32)x*step_x, y0*step_y, (f32)y*step_z, 0,0,-1, c0, 0,0) );
			//Vertices.push_back( video::S3DVertex( (f32)x*step_x, y1*step_y, (f32)(y+1)*step_z, 0,0,-1, c1, 0,0) );
			Indices.push_back( k );
			//Indices.push_back( k+1 );
		}
	}

	return true;
}

//! create Lines Mesh
bool CMatrixSceneNode::createMeshAsLines()
{
	#ifdef _DEBUG
	printf("createMeshAsLineStrips()\n");
	#endif // _DEBUG

	if (!Data)
		return false;

	const u32& rows = Data->getRows();
	const u32& cols = Data->getCols();

	#ifdef _DEBUG
	printf( "rows=%d, cols=%d\n", rows, cols);
	#endif // _DEBUG

	if ((rows==0) || (cols==0))
		return false;

	Vertices.reallocate( rows*cols*4 );
	Vertices.set_used( 0 );
	Indices.reallocate( rows*cols*6 );
	Indices.set_used( 0 );

	Material.MaterialType = video::EMT_SOLID;
	// Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
	// Material.MaterialType = (ColorGradient)?ColorGradient->getMaterialType():video::EMT_SOLID;
	Material.Thickness = 1.5f;
	Material.Lighting = false;
	Material.Wireframe = false;
	Material.FogEnable = false;

	const core::vector2df DataMinMax(0,160); // = Data->getMinMax();
//	const f32 DataRange = DataMinMax.Y-DataMinMax.X;
	const f32 DataRangeInv = core::reciprocal( 160.0f /* in dB */ );
	const core::vector3df& MeshExtent = BoundingBox.getExtent();
	const f32 step_x = MeshExtent.X / (f32)cols;
	const f32 step_y = 1.0f;//MeshExtent.Y / DataRange;
	const f32 step_z = MeshExtent.Z / (f32)rows;

	#ifdef _DEBUG
	printf( "DataMinMax = ( %f, %f )\n", DataMinMax.X, DataMinMax.Y );
	printf( "DataRangeInv = ( %f )\n", DataRangeInv );
	printf( "MeshExtent = ( %f, %f, %f )\n", MeshExtent.X, MeshExtent.Y, MeshExtent.Z );
	printf( "StepSizes = ( %f, %f, %f )\n", step_x, step_y, step_z);
	#endif // _DEBUG

	/// loop rows ( y-direction )
//	for (u32 y=0; y<rows; y++)
//	{
//		for (u32 x=0; x<cols-1; x++)
//		{
//			const f32 y0 = Data->getElement(y,x);
//			const f32 y1 = Data->getElement(y,x+1);
//			const f32 t0 = (y0 - DataMinMax.X) * DataRangeInv;
//			const f32 t1 = (y1 - DataMinMax.X) * DataRangeInv;
//			const video::SColor c0 = (ColorGradient)?ColorGradient->getColor( t0 ):0xffffffff;
//			const video::SColor c1 = (ColorGradient)?ColorGradient->getColor( t1 ):0xffffffff;
//
//			const u32 k = Vertices.size();
//
//			Vertices.push_back( video::S3DVertex( (f32)x*step_x, y0*step_y, (f32)y*step_z, 0,0,-1, c0, 0,0) );
//			Vertices.push_back( video::S3DVertex( (f32)(x+1)*step_x, y1*step_y, (f32)y*step_z, 0,0,-1, c1, 0,0) );
//			Indices.push_back( k );
//			Indices.push_back( k+1 );
//		}
//	}

	video::SColor c1, c2;

	/// loop columns ( x-direction )
	for (u32 x=0; x<cols; x++)
	{
		for (u32 y=0; y<rows-1; y++)
		{
			const f32 y1 = Data->getElement(y,x);
			const f32 y2 = Data->getElement(y+1,x);
//			const f32 t0 = (y0 - DataMinMax.X) * DataRangeInv;
//			const f32 t1 = (y1 - DataMinMax.X) * DataRangeInv;
//			const video::SColor c0 = (ColorGradient)?ColorGradient->getColor( t0 ):0xffffffff;
//			const video::SColor c1 = (ColorGradient)?ColorGradient->getColor( t1 ):0xffffffff;

			const f32 t1 = (y1-DataMinMax.X)*DataRangeInv; // normalized y-height to range 0..1, needed for color-gradient
			const f32 t2 = (y2-DataMinMax.X)*DataRangeInv;	// normalized y-height to range 0..1, needed for color-gradient

			u32 cf = core::s32_clamp( (s32)(t1*255.0f), 0, 255);
			c1 = video::SColor( 255, cf,cf,255 );
			cf = core::s32_clamp( (s32)(t2*255.0f), 0, 255);
			c2 = video::SColor( 255, cf,cf,255 );
//			cf = core::s32_clamp( (s32)(t3*255.0f), 0, 255);
//			c3 = video::SColor( 255, cf,cf,255 );
//			cf = core::s32_clamp( (s32)(t4*255.0f), 0, 255);
//			c4 = video::SColor( 255, cf,cf,255 );

			const u32 k = Vertices.size();

			Vertices.push_back( video::S3DVertex( (f32)x*step_x, y1*step_y, (f32)y*step_z, 0,0,-1, c1, 0,0) );
			Vertices.push_back( video::S3DVertex( (f32)x*step_x, y2*step_y, (f32)(y+1)*step_z, 0,0,-1, c2, 0,0) );
			Indices.push_back( k );
			Indices.push_back( k+1 );
		}
	}

	return true;
}

bool CMatrixSceneNode::createMeshAsPointCloud()
{
	return false;
}


/* random texturing tiles from tex-atlas for now */
bool CMatrixSceneNode::createMeshAsTrianglesWithTextureAtlas( const core::dimension2du& tiles_size )
{
	return false;
}

/// EPT_POINT_SPRITE
bool CMatrixSceneNode::createMeshAsTexturedBillboards( f32 billboard_width )
{
	return false;
}


////! create Lines Mesh from PointData
//IMesh* CMatrixSceneNode::createClosedPathMesh( const core::vector3df& Size, const core::array<f32>& Points, u32 pointsPerRow, video::CLinearColorGradient* gradient, ILogger* logger) const
//{
//	#ifdef _DEBUG
//	printf("createClosedPathMesh( )\n");
//	#endif // _DEBUG
//
//	//! Mesh
//	SMesh* mesh = new SMesh();
//	if (!mesh)
//	{
//		os::Printer::log( "Could not allocate mesh", ELL_ERROR );
//		return 0;
//	}
//    mesh->BoundingBox = core::aabbox3df( 0,0,0,1,1,1 );
//
//
//	const u32 pointCount = Points.size();
//	const u32 rowCount = pointCount/pointsPerRow + 1;
//
//	#ifdef _DEBUG
//	printf( "pointCount = %d\n",pointCount );
//	printf( "rowCount = %d\n",rowCount );
//	#endif // _DEBUG
//
//
//	/**
//		Minimum and Maximum values of Point-Array
//	*/
//
//	f32 min_y = FLT_MAX;
//	f32 max_y = FLT_MIN;
//
//	for (u32 i=0; i<pointCount; i++)
//	{
//		// minimum
//		if (min_y > Points[ i ])
//			min_y = Points[ i ];
//
//		// maximum
//		if (max_y < Points[ i ])
//			max_y = Points[ i ];
//	}
//
//	#ifdef _DEBUG
//	printf("min_y = %f\n", min_y);
//	printf("max_y = %f\n", max_y);
//	printf("delta_y = %f\n", max_y-min_y);
//	printf("delta_y_abs = %f\n", core::abs_<f32>( max_y - min_y ));
//	#endif // _DEBUG
//
//	/**
//		Step values
//	*/
//
//	f32 step_x = core::reciprocal( (f32)pointsPerRow );
//	f32 step_y = core::reciprocal( core::abs_<f32>( max_y - min_y ) );
//	f32 step_z = core::reciprocal( (f32)rowCount );
//
//	#ifdef _DEBUG
//	printf("step_x = %f\n", step_x);
//	printf("step_y = %f\n", step_y);
//	printf("step_z = %f\n", step_z);
//	#endif // _DEBUG
//
//	/**
//		create MeshBuffer
//	*/
//	u32 k=0;
//	u32 row = 0;
//
//	const video::E_MATERIAL_TYPE matType = (gradient)?gradient->getMaterialType():video::EMT_SOLID;
//	const video::SColor bgcolor = (gradient)?gradient->getColor(0.0f):video::SColor(255,0,0,0);
//
//	while( k<pointCount && row<rowCount )
//	{
//		SMeshBuffer* buffer = new SMeshBuffer();
//		if (buffer)
//		{
//			buffer->Vertices.reallocate( pointsPerRow );
//			buffer->Vertices.set_used( 0 );
//			buffer->Indices.reallocate( 2*pointsPerRow );
//			buffer->Indices.set_used( 0 );
//			buffer->Material.Lighting = false;
//			buffer->Material.Wireframe = false;
//			buffer->Material.FogEnable = false;
//			buffer->Material.MaterialType = matType;
//
//			for (u32 i=0; i<pointsPerRow-1; i++)
//			{
//				f32 y = 0;
//				f32 y2 = 0;
//				if (k+i<pointCount)
//					y = (f32)((Points[k+i]-min_y)*step_y);
//				if (k+i+1<pointCount)
//					y2 = (f32)((Points[k+i+1]-min_y)*step_y);
//
//				video::SColor color = 0xFFFFFFFF;
//				video::SColor color2 = 0xFFFFFFFF;
//
//				if (gradient)
//				{
//					color = gradient->getColor( y );
//					color2 = gradient->getColor( y2 );
//				}
//
//				video::S3DVertex A,B,C,D;
//				A.Pos = core::vector3df((f32)i*step_x,0.0f,(f32)row*step_z);
//				A.Normal = core::vector3df( 0,0,-1);
//				A.Color = bgcolor;
//				A.TCoords = core::vector2df(0,0);
//				B.Pos = core::vector3df((f32)i*step_x,y,(f32)row*step_z);
//				B.Normal = core::vector3df(0,0,-1);
//				B.Color = color;
//				B.TCoords = core::vector2df(0,0);
//				C.Pos = core::vector3df((f32)(i+1)*step_x,y2,(f32)row*step_z);
//				C.Normal = core::vector3df(0,0,-1);
//				C.Color = color2;
//				C.TCoords = core::vector2df(0,0);
//				D.Pos = core::vector3df((f32)(i+1)*step_x,0.0f,(f32)row*step_z);
//				D.Normal = core::vector3df(0,0,-1);
//				D.Color = bgcolor;
//				D.TCoords = core::vector2df(0,0);
//
//				u32 vCount = buffer->Vertices.size();
//				buffer->Vertices.push_back(	A );
//				buffer->Vertices.push_back( B );
//				buffer->Vertices.push_back( C );
//				buffer->Vertices.push_back( D );
//
//				buffer->Indices.push_back( vCount );
//				buffer->Indices.push_back( vCount+1 );
//				buffer->Indices.push_back( vCount+2 );
//				buffer->Indices.push_back( vCount );
//				buffer->Indices.push_back( vCount+2 );
//				buffer->Indices.push_back( vCount+3 );
//
//			}
//
//			buffer->recalculateBoundingBox();
//			mesh->addMeshBuffer( buffer );
//			mesh->BoundingBox.addInternalBox( buffer->getBoundingBox() );
//			buffer->drop();
//			buffer = 0;
//		}
//
//		k += pointsPerRow;
//		row++;
//	}
//
//	return mesh;
//}



} // end namespace scene
} // end namespace irr
