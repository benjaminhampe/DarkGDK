// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_GEOMETRY_SHAPES_H__
#define __IRR_EXT_GEOMETRY_SHAPES_H__

#include <irrlicht.h>
#include "CAutoMeshSceneNode.h"
#include "IFunction.h"
#include "sinCosTable.h"

#if defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L
	#include <functional>
#endif

/// geometry print macros
#if defined(_DEBUG) || defined(DEBUG)

	/// macro - geometry_log
	#define geometry_log( args...) \
	{ \
		printf( args ); \
	}

	/// macro - geometry_error
	#define geometry_error( args... ) \
	{ \
		printf( stderr, args ); \
		fprintf( stdout, args ); \
	}
#else
	/// macro - geometry_log
	#define geometry_log( args... ) {}

	/// macro - geometry_error
	#define geometry_error( args... ) \
	{ \
		fprintf( stderr, args ); \
	}
#endif

namespace irr
{

namespace scene
{


///@brief combine two buffer
bool addBuffer(
		SMeshBuffer* dst,
		SMeshBuffer* src,
		bool bDropBuffer = false,
		scene::E_PRIMITIVE_TYPE primType = EPT_TRIANGLES );

///@brief delete buffer
bool deleteBuffer( SMeshBuffer* buffer );

///@brief color buffer's vertices with one color
bool colorBuffer(
		SMeshBuffer* dst,
		const video::SColor& color = 0xffffffff );


///@brief get global vertex-count
u32 addVertex(
		scene::SMeshBuffer* dst,
		const video::S3DVertex& vertex );

///@brief get global vertex-count
u32 addLine(
		SMeshBuffer* dst,
		const video::S3DVertex& a,
		const video::S3DVertex& b );

///@brief get global vertex-count
u32 addTriangle(
		SMeshBuffer* dst,
		video::S3DVertex a,
		video::S3DVertex b,
		video::S3DVertex c );

///@brief get global vertex-count
u32 addQuad(
		SMeshBuffer* dst,
		const video::S3DVertex& a,
		const video::S3DVertex& b,
		const video::S3DVertex& c,
		const video::S3DVertex& d );

/////@brief get global vertex-count
//u32 addPlain(
//		SMeshBuffer* dst,
//		const core::dimension2df& sizeXY,
//		const video::SColor& color,
//		const core::vector3df& offset );
//
/////@brief get global vertex-count
//u32 addHexagon(
//		SMeshBuffer* dst,
//		const core::dimension2df& sizeXY,
//		const video::SColor& color,
//		const core::vector3df& offset );

/// Cone

//SMeshBuffer* createConeMeshBuffer(
//		f32 radius = 1.0f,
//		u32 tessXZ = 12,
//		u32 tessY = 12,
//		const video::SColor& color = 0xffffffff)
//{
//	return 0;
//}

/// Stanford Bunny

//SMeshBuffer* createBunnyMeshBuffer(
//		f32 radius = 1.0f,
//		u32 tessXZ = 12,
//		u32 tessY = 12,
//		const video::SColor& color = 0xffffffff)
//{
//	return 0;
//}

/// Teapot

//SMeshBuffer* createTeapotMeshBuffer(
//		f32 radius = 1.0f,
//		u32 tessXZ = 12,
//		u32 tessY = 12,
//		const video::SColor& color = 0xffffffff)
//{
//	return 0;
//}

/// [2d objects]

///@brief create Triangle meshbuffer
SMeshBuffer* createTriangleMeshBuffer(
		const core::vector3df& A,
		const core::vector3df& B,
		const core::vector3df& C,
		const video::SColor& colorA,
		const video::SColor& colorB,
		const video::SColor& colorC);

///@brief create Triangle meshbuffer
SMeshBuffer* createTriangleMeshBuffer(
		const core::vector3df& A,
		const core::vector3df& B,
		const core::vector3df& C,
		const video::SColor& color);

///@brief create Plain meshbuffer
SMeshBuffer* createPlainMeshBuffer(
		const core::dimension2df& size = core::dimension2df(10,10),
		const video::SColor& color = 0xffffffff,
		const core::vector3df& offset = core::vector3df(0,0,0) );

///@brief createRectangleMesh(
SMeshBuffer* createRectangleMeshBuffer(
		f32 width = 1.f,
		f32 height = 1.f,
		const video::SColor& bottomLeftColor = 0xffffffff,
		const video::SColor& topLeftColor = 0xffffffff,
		const video::SColor& topRightColor = 0xffffffff,
		const video::SColor& bottomRightColor = 0xffffffff);

///@brief create Box
SMeshBuffer* createBoxMeshBuffer(
		const core::vector3df& size,
		const video::SColor& color = 0xffffffff);

///@brief create Hexagon meshbuffer
SMeshBuffer* createHexagonMeshBuffer(
		const core::dimension2df& size = core::dimension2df(10,10),
		const video::SColor& color = 0xffffffff,
		bool XZPlane = false);

///@brief create Rainbow
SMeshBuffer* createRainbowMeshBuffer( // XY-plane, normale is -Z
		f32 outerRadius = 100.0f,
		f32 innerRadius = 50.0f,
		f32 zAngleStart = 0.0f,
		f32 zAngleEnd = 180.0f,
		u32 segments = 13,
		const core::vector3df& pos = core::vector3df(0,0,0));

///@brief create roundrect mesh
SMeshBuffer* createRoundRectMeshBuffer(
		f32 width = 1.0f,
		f32 height = 1.0f,
		f32 rx = .1f,
		f32 ry = .1f,
		u32 tesselation = 12,
		bool bFullyTextured = true,
		const video::SColor& outerColor = 0xffffffff,
		const video::SColor& innerColor = 0xffffffff);

///@brief create circle meshbuffer
SMeshBuffer* createCircleMeshBuffer(
		f32 radius = 0.5f,
		u32 tesselation = 12,
		bool filled = true,
		const video::SColor& outerColor = 0xffffffff,
		const video::SColor& innerColor = 0xffffffff);

SMeshBuffer* createEllipseMeshBuffer(
		f32 radiusX = 0.5f,
		f32 radiusY = 0.4f,
		u32 tesselation = 12,
		const video::SColor& outerColor = 0xffffffff,
		const video::SColor& innerColor = 0xffffffff);

SMeshBuffer* createRingMeshBuffer(
		f32 outerRadius = 0.5f,
		f32 innerRadius = 0.25f,
		u32 tesselation = 12,
		bool bRepeatTexture = false,
		const video::SColor& outerColor = 0xffffffff,
		const video::SColor& innerColor = 0xffffffff);

SMeshBuffer* createArcMeshBuffer(
		f32 outerRadius = .5f,
		f32 innerRadius = .25f,
		f32 angleStart = 0.0f,
		f32 angleEnd = 180.0f,
		u32 tesselation = 12,
		bool bRepeatTexture = true,
		const video::SColor& outerColor = 0xffffffff,
		const video::SColor& innerColor = 0xffffffff);

SMeshBuffer* createCylinderMeshBuffer(
		f32 radius,
		f32 height,
		u32 tessCircle = 12,
		u32 tessHull = 1,
		bool closeTop = true,
		bool closeBottom = true,
		bool bOneMaterial = false,
		const video::SColor& color = 0xffffffff,
		const video::SColor& topColor = 0xffffffff,
		const video::SColor& bottomColor = 0xffffffff);

SMeshBuffer* createUpperSphereHalfMeshBuffer(
		f32 radius = .5f,
		u32 tessCircle = 7,
		u32 tessRows = 7,
		const video::SColor& color = 0xffffffff,
		bool closeBottom = false);

SMeshBuffer* createLowerSphereHalfMeshBuffer(
		f32 radius = .5f,
		u32 tessCircle = 7,
		u32 tessRows = 7,
		const video::SColor& color = 0xffffffff,
		bool closeTop = false);

SMeshBuffer* createSphereMeshBuffer(
		f32 radius = 1.0f,
		u32 tessXZ = 12,
		u32 tessY = 12,
		const video::SColor& color = 0xffffffff);

SMeshBuffer* createEllipsoidMeshBuffer(
		f32 radiusX = 0.5f,
		f32 radiusY = 0.3f,
		f32 radiusZ = 0.4f,
		u32 tessX = 12,
		u32 tessY = 12,
		u32 tessZ = 12,
		const video::SColor& color = 0xffffffff);

SMeshBuffer* createCapsuleMeshBuffer(
		f32 radius = .5f,
		f32 height = 1.0f,
		u32 tessCircle = 7,
		u32 tessRows = 7,
		u32 tessHull = 1,
		const video::SColor& color = 0xffffffff,
		const video::SColor& topColor = 0xffffffff,
		const video::SColor& bottomColor = 0xffffffff);

SMeshBuffer* createTubeMeshBuffer(
		f32 outerRadius = .5f,
		f32 innerRadius = .4f,
		f32 height = 1.0f,
		u32 tessCircle = 12,
		u32 tessHull = 1,
		u32 bTextureMode = 0,
		const video::SColor& color = 0xffffffff);

SMeshBuffer* createTorusMeshBuffer(
		f32 outerRadius = .5f,
		f32 innerRadius = .1f,
		u32 tessOuterRadius = 12,
		u32 tessInnerRadius = 8,
		const video::SColor& color = 0xffffffff);

///@brief create line2d mesh
SMeshBuffer* createLine2dMeshBuffer(
		const core::array<core::vector2df>& points,	// all containing points get connected by min. one quad
		const core::array<video::SColor>& colors, // color-array
		f32 thickness = 1.0f,
		s32 lineJoin = 0, // 0 == rect-miter, 1==rect-bevel, >2 == circle-round segments
		video::ITexture* pTexture = 0,
		bool bRepeatTexture=true);

///@brief create PolyLine from array-of-2d-points

template<class T> SMeshBuffer* createPolyLineMeshBuffer(
	const core::array<core::vector2d<T> >& points,
	const video::SColor& lineColor = video::SColor(255,0,0,0),
	const f32& lineWidth = 1.0f,
	const u16& lineStipple = 0xffff,
	const core::vector3df& offset = core::vector3df(0,0,0) )
{
	#ifdef _DEBUG
	printf("createPolyLine\n");
	#endif // _DEBUG

	u32 point_count = core::min_<u32>( points.size(), 65536 );
	if (point_count < 2)
		return 0; /// ERROR

	SMeshBuffer* p = new SMeshBuffer();
	if (!p)
		return 0; /// ERROR

	p->Material.MaterialType = (lineColor.getAlpha()<255) ? video::EMT_TRANSPARENT_ALPHA_CHANNEL : video::EMT_SOLID;
	p->Vertices.reallocate( point_count );
	p->Vertices.set_used( 0 );
	p->Indices.reallocate( point_count );
	p->Indices.set_used( 0 );

	for (u32 i=0; i<point_count; i++)
	{
		p->Vertices.push_back( video::S3DVertex( offset.X+(f32)points[i].X, offset.Y+(f32)points[i].Y, offset.Z, 0.f, 0.f, -1.f, lineColor, 0.f, 0.f ) );
		p->Indices.push_back( i );
	}

	p->recalculateBoundingBox();
}

///@brief create PolyLine from function

template<class T> SMeshBuffer* createPolyLineMeshBuffer(
#if defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L
	const std::function<T (const T&)>& func,
#else
	const IFunction<T>* const func,
#endif
	const T& t_start,
	const T& t_end,
	const u32& point_count = 100,
	const video::SColor& lineColor = video::SColor(255,0,0,0),
	const f32& lineWidth = 1.0f,
	const core::vector3df& offset = core::vector3df(0,0,0))
{
	typedef core::vector2d<f32> Vector2f;
	typedef core::array<Vector2f> ArrayOfVector2f;

	if (point_count < 2)
		return 0;

	ArrayOfVector2f points;
	points.reallocate( point_count );
	points.set_used( 0 );

	const T t_delta = (t_end - t_start) / (T)point_count;

	T t_now = t_start;

	#ifdef _DEBUG
	printf("point_count = %d, time_delta = %f\n", point_count, t_delta );
	#endif // _DEBUG

	for (u32 i=0; i<point_count; i++)
	{
		points.push_back( Vector2f( (f32)t_now, (f32)func(t_now) ) );
		t_now += t_delta;

		#ifdef _DEBUG
		printf("points[%d] = { %f, %f }\n", i, points[i].X, points[i].Y );
		#endif // _DEBUG
	}

	return createPolyLineMeshBuffer<T>( points, lineColor, lineWidth, offset );
}

} // end namespace scene
} // end namespace irr

#endif // __IRR_EXT_GEOMETRY_HELPER_H__
