// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_GEOMETRY_HELPER_H__
#define __IRR_EXT_GEOMETRY_HELPER_H__

#include <irrlicht.h>

#include <geometry_meshbuffer.h>

#include <CAutoMeshSceneNode.h>

namespace irr
{
namespace scene
{

///@brief setVisible(false) to all SceneNodes
bool hideAll( ISceneManager* smgr );

///@brief setVisible(true) to all SceneNodes
bool showAll( ISceneManager* smgr );

///@brief create SceneNode
scene::CAutoMeshSceneNode* createNode(
		scene::ISceneManager* smgr,
		SMesh* mesh,
		bool bDropMesh = false,
		scene::ISceneNode* parent = 0,
		s32 id = -1,
		scene::E_PRIMITIVE_TYPE primType = EPT_TRIANGLES,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1,1,1) );

/// [meshes]

///@brief create mesh - from a meshbuffer
SMesh* createMesh(
		SMeshBuffer* buffer,
		bool bDropBuffer = false );

///@brief delete mesh
bool deleteMesh( IMesh* mesh );

///@brief get global vertex-count
u32 getMeshVertexCount( SMesh* mesh );

///@brief get global index-count
u32 getMeshIndexCount( SMesh* mesh );

///@brief clone mesh
SMesh* cloneMesh(
		SMesh* mesh,
		bool bDropMesh = false );

///@brief load mesh
IAnimatedMesh* loadMesh(
		scene::ISceneManager* smgr,
		const io::path& filename );

///@brief save mesh
bool saveMesh(
		scene::ISceneManager* smgr,
		const io::path& filename,
		SMesh* meshToSave );

///@brief color mesh's vertices with one color
bool colorMesh(
		SMesh* mesh,
		const video::SColor& color = 0xffffffff );

///@brief combine two meshes
bool combineMesh(
		SMesh* dst,
		SMesh* src,
		bool bDropMesh = false,
		scene::E_PRIMITIVE_TYPE primType = EPT_TRIANGLES );

///@brief create Triangle mesh
inline SMesh* createTriangleMesh(
		const core::vector3df& A,
		const core::vector3df& B,
		const core::vector3df& C,
		const video::SColor& colorA,
		const video::SColor& colorB,
		const video::SColor& colorC)
{
	geometry_log("createTriangleMesh()\n");
	return createMesh( createTriangleMeshBuffer(A,B,C,colorA,colorB,colorC), true );
}

///@brief create Triangle mesh
inline SMesh* createTriangleMesh(
		const core::vector3df& A,
		const core::vector3df& B,
		const core::vector3df& C,
		const video::SColor& color)
{
	geometry_log("createTriangleMesh()\n");
	return createMesh( createTriangleMeshBuffer(A,B,C,color), true );
}

///@brief create Plain mesh
inline SMesh* createPlainMesh(
		const core::dimension2df& size = core::dimension2df(10,10),
		const video::SColor& color = 0xffffffff,
		const core::vector3df& offset = core::vector3df(0,0,0) )
{
	return createMesh( createPlainMeshBuffer( size, color, offset ), true );
}

///@brief create Plain mesh
inline SMesh* createRectangleMesh(
		f32 width = 1.f,
		f32 height = 1.f,
		const video::SColor& bottomLeftColor = 0xffffffff,
		const video::SColor& topLeftColor = 0xffffffff,
		const video::SColor& topRightColor = 0xffffffff,
		const video::SColor& bottomRightColor = 0xffffffff)
{
	geometry_log("createRectangleMesh()\n");
	return createMesh(
		createRectangleMeshBuffer(
			width, height, bottomLeftColor, topLeftColor, topRightColor, bottomRightColor ), true );
}

///@brief create Box
inline SMesh* createBoxMesh(
		const core::vector3df& size,
		const video::SColor& color = 0xffffffff,
		u32 matCount = 6)
{
	geometry_log("createBoxMesh()\n");
	return createMesh(
		createBoxMeshBuffer(
			size, color ));
}

///@brief create Hexagon mesh
inline SMesh* createHexagonMesh(
		const core::dimension2df& size = core::dimension2df(10,10),
		const video::SColor& color = 0xffffffff,
		bool XZPlane = false)
{
	geometry_log("createHexagonMesh()\n");
	return createMesh(
		createHexagonMeshBuffer(
			size, color, XZPlane ), true );
}

///@brief create Rainbow
inline SMesh* createRainbowMesh( // XY-plane, normale is -Z
		f32 outerRadius = 100.0f,
		f32 innerRadius = 50.0f,
		f32 zAngleStart = 0.0f,
		f32 zAngleEnd = 180.0f,
		u32 segments = 13,
		const core::vector3df& pos = core::vector3df(0,0,0))
{
	geometry_log("createRainbowMesh()\n");
	return createMesh(
		createRainbowMeshBuffer(
			outerRadius, innerRadius, zAngleStart, zAngleEnd, segments, pos ), true );
}

///@brief create roundrect mesh
inline SMesh* createRoundRectMesh(
		f32 width = 1.0f,
		f32 height = 1.0f,
		f32 rx = .1f,
		f32 ry = .1f,
		u32 tesselation = 12,
		bool bFullyTextured = true,
		const video::SColor& outerColor = 0xffffffff,
		const video::SColor& innerColor = 0xffffffff)
{
	geometry_log("createRoundRectMesh()\n");
	return createMesh(
		createRoundRectMeshBuffer(
			width, height, rx,ry, tesselation, bFullyTextured, outerColor, innerColor ), true );
}

///@brief create circle mesh
inline SMesh* createCircleMesh(
		f32 radius = 0.5f,
		u32 tesselation = 12,
		bool filled = true,
		const video::SColor& outerColor = 0xffffffff,
		const video::SColor& innerColor = 0xffffffff)
{
	geometry_log("createCircleMesh()\n");
	return createMesh(
		createCircleMeshBuffer(
			radius, tesselation, filled, outerColor, innerColor ), true );
}

inline SMesh* createEllipseMesh(
		f32 radiusX = 0.5f,
		f32 radiusY = 0.4f,
		u32 tesselation = 12,
		const video::SColor& outerColor = 0xffffffff,
		const video::SColor& innerColor = 0xffffffff)
{
	geometry_log("createEllipseMesh()\n");
	return createMesh(
		createEllipseMeshBuffer(
			radiusX, radiusY, tesselation, outerColor, innerColor ), true );
}

inline SMesh* createRingMesh(
		f32 outerRadius = 0.5f,
		f32 innerRadius = 0.25f,
		u32 tesselation = 12,
		bool bRepeatTexture = false,
		const video::SColor& outerColor = 0xffffffff,
		const video::SColor& innerColor = 0xffffffff)
{
	geometry_log("createRingMesh()\n");
	return createMesh(
		createRingMeshBuffer(
			outerRadius, innerRadius, tesselation, bRepeatTexture, outerColor, innerColor ), true );
}

inline SMesh* createArcMesh(
		f32 outerRadius = .5f,
		f32 innerRadius = .25f,
		f32 angleStart = 0.0f,
		f32 angleEnd = 180.0f,
		u32 tesselation = 12,
		bool bRepeatTexture = true,
		const video::SColor& outerColor = 0xffffffff,
		const video::SColor& innerColor = 0xffffffff)
{
	geometry_log("createRingMesh()\n");
	return createMesh(
		createArcMeshBuffer(
			outerRadius, innerRadius, angleStart, angleEnd, tesselation, bRepeatTexture, outerColor, innerColor ), true );
}

inline SMesh* createCylinderMesh(
		f32 radius,
		f32 height,
		u32 tessCircle = 12,
		u32 tessHull = 1,
		bool closeTop = true,
		bool closeBottom = true,
		bool bOneMaterial = false,
		const video::SColor& color = 0xffffffff,
		const video::SColor& topColor = 0xffffffff,
		const video::SColor& bottomColor = 0xffffffff)
{
	geometry_log("createCylinderMesh()\n");
	return createMesh(
		createCylinderMeshBuffer(
			radius, height, tessCircle, tessHull, closeTop, closeBottom, bOneMaterial, color, topColor, bottomColor ), true );
}

inline SMesh* createUpperSphereHalfMesh(
		f32 radius = .5f,
		u32 tessCircle = 7,
		u32 tessRows = 7,
		const video::SColor& color = 0xffffffff,
		bool closeBottom = false)
{
	geometry_log("createUpperSphereHalfMesh()\n");
	return createMesh(
		createUpperSphereHalfMeshBuffer(
			radius, tessCircle, tessRows, color, closeBottom ), true );
}

inline SMesh* createLowerSphereHalfMesh(
		f32 radius = .5f,
		u32 tessCircle = 7,
		u32 tessRows = 7,
		const video::SColor& color = 0xffffffff,
		bool closeTop = false)
{
	geometry_log("createLowerSphereHalfMesh()\n");
	return createMesh(
		createLowerSphereHalfMeshBuffer(
			radius, tessCircle, tessRows, color, closeTop ), true );
}

inline SMesh* createSphereMesh(
		f32 radius = 1.0f,
		u32 tessXZ = 12,
		u32 tessY = 12,
		const video::SColor& color = 0xffffffff)
{
	geometry_log("createSphereMesh()\n");
	return createMesh(
		createSphereMeshBuffer(
			radius, tessXZ, tessY, color ), true );
}

inline SMesh* createEllipsoidMesh(
		f32 radiusX = 0.5f,
		f32 radiusY = 0.3f,
		f32 radiusZ = 0.4f,
		u32 tessX = 12,
		u32 tessY = 12,
		u32 tessZ = 12,
		const video::SColor& color = 0xffffffff)
{
	geometry_log("createEllipsoidMesh()\n");
	return createMesh(
		createEllipsoidMeshBuffer(
			radiusX, radiusY, radiusZ, tessX, tessY, tessY, color ), true );
}

inline SMesh* createCapsuleMesh(
		f32 radius = .5f,
		f32 height = 1.0f,
		u32 tessCircle = 7,
		u32 tessRows = 7,
		u32 tessHull = 1,
		bool bOneMaterial = true,
		const video::SColor& color = 0xffffffff,
		const video::SColor& topColor = 0xffffffff,
		const video::SColor& bottomColor = 0xffffffff)
{
	geometry_log("createCapsuleMesh()\n");
	return createMesh(
		createCapsuleMeshBuffer(
			radius, height, tessCircle, tessRows, tessHull, color, topColor, bottomColor ), true );
}

inline SMesh* createTubeMesh(
		f32 outerRadius = .5f,
		f32 innerRadius = .4f,
		f32 height = 1.0f,
		u32 tessCircle = 12,
		u32 tessHull = 1,
		u32 bTextureMode = 0,
		const video::SColor& color = 0xffffffff)
{
	geometry_log("createTubeMesh()\n");
	return createMesh(
		createTubeMeshBuffer(
			outerRadius, innerRadius, height, tessCircle, tessHull, bTextureMode ), true );
}

inline SMesh* createTorusMesh(
		f32 outerRadius = .5f,
		f32 innerRadius = .1f,
		u32 tessOuterRadius = 12,
		u32 tessInnerRadius = 8,
		const video::SColor& color = 0xffffffff)
{
	geometry_log("createTorusMesh()\n");
	return createMesh(
		createTorusMeshBuffer(
			outerRadius, innerRadius, tessOuterRadius, tessInnerRadius, color ), true );
}

///@brief create line2d mesh
inline SMesh* createLine2dMesh(
		const core::array<core::vector2df>& points,	// all containing points get connected by min. one quad
		const core::array<video::SColor>& colors, // color-array
		f32 thickness = 1.0f,
		s32 lineJoin = 0, // 0 == rect-miter, 1==rect-bevel, >2 == circle-round segments
		video::ITexture* pTexture = 0,
		bool bRepeatTexture=true)  // false = each segments has full tex, if true, planar uv mapping on boundingrect
{
	geometry_log("createLine2dMesh()\n");
	return createMesh(
		createLine2dMeshBuffer(
			points, colors, thickness, lineJoin, pTexture, bRepeatTexture ), true );
}

///@brief create PolyLine

template<class T>
CAutoMeshSceneNode*
createPolyLine(
	ISceneManager* smgr,
	ISceneNode* parent,
	const core::array<core::vector2d<T> >& points,
	const video::SColor& lineColor = video::SColor(255,0,0,0),
	const f32& lineWidth = 1.0f,
	const u16& lineStipple = 0xffff,
	const core::vector3df& position = core::vector3df(0,0,0),
	const core::vector3df& rotation = core::vector3df(0,0,0),
	const core::vector3df& scale = core::vector3df(1,1,1) )
{
	#ifdef _DEBUG
	printf("createPolyLine\n");
	#endif // _DEBUG

	u32 point_count = core::min_<u32>( points.size(), 65536 );
	if (point_count == 0)
		return 0; /// ERROR

	SMesh* mesh = new SMesh();
	if (!mesh)
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
		p->Vertices.push_back( video::S3DVertex( (f32)points[i].X, (f32)points[i].Y, 0.0f, 0.f, 0.f, -1.f, lineColor, 0.f, 0.f ) );
		p->Indices.push_back( i );
	}

	p->recalculateBoundingBox();

	mesh->addMeshBuffer( p );

	mesh->BoundingBox = p->getBoundingBox();

	p->drop();

	mesh->setHardwareMappingHint( EHM_STATIC);

	CAutoMeshSceneNode* node = new CAutoMeshSceneNode(
		mesh, smgr, parent, -1, EPT_LINE_STRIP, position, rotation, scale );

	mesh->drop();

	if (!node)
		return 0; /// ERROR

	node->setLineStipple( lineStipple );

	return node;
}

///@brief create PolyLine from function

template<class T>
CAutoMeshSceneNode*
createPolyLine(
	ISceneManager* smgr,
	ISceneNode* parent,
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
	const u16& lineStipple = 0xffff,
	const core::vector3df& position = core::vector3df(0,0,0),
	const core::vector3df& rotation = core::vector3df(0,0,0),
	const core::vector3df& scale = core::vector3df(1,1,1) )
{
	typedef core::vector2d<f32> Vector2f;
	typedef core::array<Vector2f> ArrayOfVector2f;

	if (point_count == 0)
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


	return createPolyLine<T>( smgr, parent, points, lineColor, lineWidth, lineStipple, position, rotation, scale );
}

} // end namespace scene
} // end namespace irr

#endif // __IRR_EXT_GEOMETRY_HELPER_H__
