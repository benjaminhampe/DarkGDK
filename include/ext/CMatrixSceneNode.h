// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXTENSION_DYNAMIC_MATRIX_SCENE_NODE_H__
#define __IRR_EXTENSION_DYNAMIC_MATRIX_SCENE_NODE_H__

#include <irrlicht.h>
#include <ISceneNode.h>
// #include <EPrimitiveType.h>
#include <../../source/Irrlicht/os.h>
#include <../../source/Irrlicht/CImage.h>

#include <cmath>

// The matrix holds the actual heightdata
// it is stored as pointer, so the scenenode does not create copies and wastes space

#include "CMatrix.h"

// uses function drawMeshBufferEx() to render depending on E_PRIMITIVE_TYPE
#include "renderByPrimitiveType.h"

// uses IColorGradient for coloring the vertices
// depending on height and min/max-height, if needed
#include "IColorGradient.h"

namespace irr
{
namespace scene
{

// This SceneNode holds only vertices, primitivetype, materials etc.
// needed for rendering

class CMatrixSceneNode : public ISceneNode
{
/* Fields */
private:
	/// Matrix3D
	E_PRIMITIVE_TYPE PrimitiveType;
	core::vector3df Size3D;
	video::IColorGradient* ColorGradient;
	core::CMatrix<f32>* Data;

	/// ISceneNode
	core::aabbox3df BoundingBox;
	video::SMaterial Material; // TextureAtlas at maximum
	core::array<video::S3DVertex> Vertices;
	core::array<s32> Indices;

//
//	bool IsTextureAtlas;
//	core::dimension2du AtlasTileSize;
//	bool IsBillBoard; // needed to update rotation to camera space

/* constructor */
public:
	/**
	**/
	CMatrixSceneNode(
		E_PRIMITIVE_TYPE shapeType, /* = EPT_TRIANGLES */
		const core::vector3df& shapeSize,
		video::IColorGradient* colorGradient,
		core::CMatrix<f32>* matrixData,
		ISceneManager* smgr, ISceneNode* parent = 0, s32 id=-1,
		const core::vector3df& position = core::vector3df(0,0,0),
		const core::vector3df& rotation = core::vector3df(0,0,0),
		const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f) );

/* destructor */
	virtual ~CMatrixSceneNode();

/* fresh state */
	void clear();

/* create mesh depending on PrimitiveType */
	bool createMesh();
	bool createMeshAsLogarithmicTriangles();
	bool createMeshAsPointCloud();
	bool createMeshAsLines();
	bool createMeshAsLineStrips();
	bool createMeshAsTexturedBillboards( f32 billboard_width = core::PI );
	bool createMeshAsTriangles();
	bool createMeshAsTrianglesWithTextureAtlas( const core::dimension2du& tiles_size = core::dimension2du(64,64) );

/* ISceneNode Interface */
	virtual void render();

	virtual const core::aabbox3d<f32>& getBoundingBox() const	{ return BoundingBox; } // inline

	virtual u32 getMaterialCount() const { return 1; } // inline

	virtual video::SMaterial& getMaterial(u32 num) { return Material; } // inline

	virtual void OnRegisterSceneNode() // inline
	{
		if (IsVisible)
			SceneManager->registerNodeForRendering(this);
		ISceneNode::OnRegisterSceneNode();
	}

/* Matrix3D Interface */

	virtual E_PRIMITIVE_TYPE getPrimitiveType( ) const  // inline
	{
		return PrimitiveType;
	}

	virtual core::vector3df getMeshSize3D( ) const  // inline
	{
		return Size3D;
	}

	virtual video::IColorGradient* getColorGradient( ) const  // inline
	{
		return ColorGradient;
	}

	virtual core::CMatrix<f32>* getData()
	{
		return Data;
	}

	virtual u32 getRows() const  // inline
	{
		_IRR_DEBUG_BREAK_IF( !Data )
		return Data->getRows();
	}

	virtual u32 getCols() const  // inline
	{
		_IRR_DEBUG_BREAK_IF( !Data )
		return Data->getCols();
	}


	//! manipulate internal attributes:

//	virtual bool setColorGradient( video::IColorGradient* gradient ) // inline
//	{
//		if (ColorGradient)
//			ColorGradient->drop();
//
//		ColorGradient = gradient;
//
//		if (ColorGradient)
//			ColorGradient->grab();
//
//		return true;
//	}

//	virtual bool setPrimitiveType( E_PRIMITIVE_TYPE primType ) { PrimitiveType = primType; return true; } // inline


	virtual bool setData( core::CMatrix<f32>* mat )
	{
		if (Data)
			Data->drop();

		Data = mat;

		if ( !mat )
			return false;

		createMesh();

		return true;
	}

};

} // end namespace scene
} // end namespace irr


#endif // __IRR_C_DYNAMIC_EQ_SCENE_NODE_H__
