// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include <CAutoMeshSceneNode.h>

namespace irr
{
namespace scene
{

//! default constructor - value ctr ( by render-shape, shape-size, color-gradient, matrix-data, irr::ISceneNode-interface )
CAutoMeshSceneNode::CAutoMeshSceneNode(
	IMesh* mesh, ISceneManager* smgr, ISceneNode* parent, s32 id,
	E_PRIMITIVE_TYPE primType,
	const core::vector3df& position,
	const core::vector3df& rotation,
	const core::vector3df& scale )
: CMeshSceneNode( mesh, parent, smgr, id, position, rotation, scale)
, PrimitiveType( primType )
, LineStipple(0xffff)
{
	#ifdef _DEBUG
		os::Printer::log("CAutoMeshSceneNode()", ELL_INFORMATION);
	#endif // _DEBUG
}

//! default constructor - value ctr ( by render-shape, shape-size, color-gradient, matrix-data, irr::ISceneNode-interface )
CAutoMeshSceneNode::CAutoMeshSceneNode(
	IMeshBuffer* buffer, ISceneManager* smgr, ISceneNode* parent, s32 id,
	E_PRIMITIVE_TYPE primType,
	const core::vector3df& position,
	const core::vector3df& rotation,
	const core::vector3df& scale )
: CMeshSceneNode( new SMesh(), parent, smgr, id, position, rotation, scale)
, PrimitiveType( primType )
, LineStipple(0xffff)
{
	#ifdef _DEBUG
		os::Printer::log("CAutoMeshSceneNode()", ELL_INFORMATION);
	#endif // _DEBUG

	IMesh* mesh = Mesh;
	if (mesh)
	{
		((SMesh*)mesh)->addMeshBuffer( buffer );

		core::aabbox3df bbox = mesh->getBoundingBox();

		bbox.addInternalBox( buffer->getBoundingBox() );

		mesh->setBoundingBox( bbox );

		buffer->drop();

		mesh->drop();
	}
}
//! destructor
CAutoMeshSceneNode::~CAutoMeshSceneNode()
{

}

/// render
void CAutoMeshSceneNode::render()
{
	video::IVideoDriver* driver = SceneManager->getVideoDriver();

	if (!Mesh || !driver)
		return;

	bool isTransparentPass = (SceneManager->getSceneNodeRenderPass() == ESNRP_TRANSPARENT);

	++PassCount;

	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);

	Box = Mesh->getBoundingBox();

	if (Shadow && PassCount==1)
		Shadow->updateShadowVolumes();

	// for debug purposes only:

	bool renderMeshes = true;
	video::SMaterial mat;

    const u32 count = Mesh->getMeshBufferCount();

	if (DebugDataVisible && PassCount==1)
	{
		// overwrite half transparency
		if (DebugDataVisible & EDS_HALF_TRANSPARENCY)
		{
			for (u32 i=0; i < count; i++)
			{
				mat = Materials[i];
				mat.MaterialType = video::EMT_TRANSPARENT_ADD_COLOR;
				driver->setMaterial(mat);

				this->drawMeshBufferEx( Mesh->getMeshBuffer(i) );
			}
			renderMeshes = false;
		}
	}

	// render original meshes
	if (renderMeshes)
	{
		for (u32 i=0; i < count; i++)
		{
			IMeshBuffer* mb = Mesh->getMeshBuffer(i);
			if (mb)
			{
				const video::SMaterial& material = ReadOnlyMaterials ? mb->getMaterial() : Materials[i];

				video::IMaterialRenderer* rnd = driver->getMaterialRenderer(material.MaterialType);

				bool transparent = (rnd && rnd->isTransparent());

				// only render transparent buffer if this is the transparent render pass
				// and solid only in solid pass
				if (transparent == isTransparentPass)
				{
					driver->setMaterial(material);

					bool bEnableLineStipple = false;

					/// set state GL_LINE_STIPPLE
					if (LineStipple<0xffff)
					{
						if ( driver->getDriverType() == video::EDT_OPENGL )
						{
							glEnable( GL_LINE_STIPPLE );
							glLineStipple( 1, LineStipple );

							bEnableLineStipple = true;
						}
					}

					this->drawMeshBufferEx( mb );

					/// reset state GL_LINE_STIPPLE
					if (bEnableLineStipple)
					{
						glDisable( GL_LINE_STIPPLE );
					}
				}
			}
		}
	}

	driver->setTransform(video::ETS_WORLD, AbsoluteTransformation);

	// for debug purposes only:
	if (DebugDataVisible && PassCount==1)
	{
		video::SMaterial m;
		m.Lighting = false;
		m.AntiAliasing=0;
		driver->setMaterial(m);

		if (DebugDataVisible & EDS_BBOX)
		{
			driver->draw3DBox(Box, video::SColor(255,255,255,255));
		}
		if (DebugDataVisible & EDS_BBOX_BUFFERS)
		{
			for (u32 i=0; i < count; i++)
			{
				driver->draw3DBox(
					Mesh->getMeshBuffer(i)->getBoundingBox(),
					video::SColor(255,190,128,128));
			}
		}

		if ((DebugDataVisible & EDS_NORMALS) && (PrimitiveType == EPT_TRIANGLES))
		{
			// draw normals
			const f32 debugNormalLength = SceneManager->getParameters()->getAttributeAsFloat(DEBUG_NORMAL_LENGTH);
			const video::SColor debugNormalColor = SceneManager->getParameters()->getAttributeAsColor(DEBUG_NORMAL_COLOR);

			for (u32 i=0; i < count; i++)
			{
				driver->drawMeshBufferNormals( Mesh->getMeshBuffer(i), debugNormalLength, debugNormalColor);
			}
		}

		// show mesh
		if (DebugDataVisible & EDS_MESH_WIRE_OVERLAY)
		{
			m.Wireframe = true;
			driver->setMaterial(m);

			for (u32 i=0; i < count; i++)
			{
				this->drawMeshBufferEx( Mesh->getMeshBuffer(i) );
			}
		}
	}
}

/// render single meshbuffer depending on PrimitiveType

void CAutoMeshSceneNode::drawMeshBufferEx( IMeshBuffer* buffer )
{
	if (!buffer)
		return;

	video::IVideoDriver* driver = SceneManager->getVideoDriver();
	if (!driver)
		return;

	u32 primCount = 0;

	const u32& indexCount = buffer->getIndexCount();
	const video::E_VERTEX_TYPE& vertexType = buffer->getVertexType();
	const video::E_INDEX_TYPE& indexType = buffer->getIndexType();

	switch (PrimitiveType)
	{
		case EPT_TRIANGLES:
				primCount = indexCount/3;
				break;
		case EPT_POLYGON:
				primCount = indexCount-1;
				break;
		case EPT_QUADS:
				primCount = indexCount/4;
				break;
		case EPT_LINES:
				primCount = indexCount/2;
				break;
		case EPT_LINE_STRIP:
				primCount = indexCount-1;
				break;
		case EPT_LINE_LOOP:
				primCount = indexCount-1;
				break;
		case EPT_POINTS:
				primCount = indexCount;
				break;
		case EPT_TRIANGLE_STRIP:
				primCount = (indexCount-2)/3;
				break;
		case EPT_TRIANGLE_FAN:
				primCount = (indexCount-2)/3;
				break;
		case EPT_QUAD_STRIP:
				primCount = (indexCount-2)/4;
				break;
		case EPT_POINT_SPRITES:
				primCount = indexCount;
				break;
		default:
				break;
	}

	driver->drawVertexPrimitiveList(
			buffer->getVertices(),
			buffer->getVertexCount(),
			buffer->getIndices(),
			primCount,
			vertexType,
			PrimitiveType,
			indexType);

}

} // end namespace scene

} // end namespace irr






// // this function is for 32bit indices
// void drawElements(
	// IVideoDriver* driver,
	// const core::array<video::S3DVertex>& vertices,
	// const core::array<s32>& indices,
	// E_PRIMITIVE_TYPE primType)
// {
	// if (!driver)
		// return;

	// u32 primCount = 0;

	// const u32& indexCount = indices.size();

	// switch (primType)
	// {
		// case EPT_POINTS:
				// primCount = indexCount;
				// break;
		// case EPT_LINE_STRIP:
				// primCount = indexCount-1;
				// break;
		// case EPT_LINE_LOOP:
				// primCount = indexCount-1;
				// break;
		// case EPT_LINES:
				// primCount = indexCount/2;
				// break;
		// case EPT_TRIANGLE_STRIP:
				// primCount = (indexCount-2)/3;
				// break;
		// case EPT_TRIANGLE_FAN:
				// primCount = (indexCount-2)/3;
				// break;
		// case EPT_TRIANGLES:
				// primCount = indexCount/3;
				// break;
		// case EPT_QUAD_STRIP:
				// primCount = (indexCount-2)/4;
				// break;
		// case EPT_QUADS:
				// primCount = indexCount/4;
				// break;
		// case EPT_POLYGON:
				// primCount = indexCount-1;
				// break;
		// case EPT_POINT_SPRITES:
				// primCount = indexCount;
				// break;
		// default:
				// break;
	// }

	// driver->drawVertexPrimitiveList( vertices.const_pointer(),
			// vertices.size(), indices.const_pointer(),
			// primCount, video::EVT_STANDARD,
			// primType, video::EIT_32BIT);
// }



// void drawMeshEx( IVideoDriver* driver, IMesh* mesh, E_PRIMITIVE_TYPE primType)
// {
	// if (!driver)
		// return;

	// if (!mesh)
		// return;

	// u32 bufferCount = mesh->getMeshBufferCount();

	// for (u32 i=0; i<bufferCount; i++)
	// {
		// IMeshBuffer* buffer = mesh->getMeshBuffer( i );
		// if ( buffer )
		// {

			// driver->setMaterial( buffer->getMaterial() );

			// drawMeshBufferEx( driver, buffer, primType );
		// }
	// }
// }

