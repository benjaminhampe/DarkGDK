// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXTENSION_AUTOMATIC_MESH_SCENE_NODE_H__
#define __IRR_EXTENSION_AUTOMATIC_MESH_SCENE_NODE_H__

#include <irrlicht.h>

#ifdef _DEBUG
	#include <../../source/Irrlicht/os.h>
#endif // _DEBUG

#include <../../source/Irrlicht/CMeshSceneNode.h>
#include <../../source/Irrlicht/CShadowVolumeSceneNode.h>
#include <GL/gl.h>


namespace irr
{
namespace scene
{
	///@brief class that renders a SceneNode depending on PrimitiveType
	class CAutoMeshSceneNode : public CMeshSceneNode
	{
	public:
		/// @brief class constructor
		CAutoMeshSceneNode(
			IMesh* mesh,
			ISceneManager* smgr,
			ISceneNode* parent = 0,
			s32 id = -1,
			E_PRIMITIVE_TYPE primType = EPT_TRIANGLES,
			const core::vector3df& position = core::vector3df(0,0,0),
			const core::vector3df& rotation = core::vector3df(0,0,0),
			const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f) );

		/// @brief class constructor
		CAutoMeshSceneNode(
			IMeshBuffer* buffer,
			ISceneManager* smgr,
			ISceneNode* parent = 0,
			s32 id = -1,
			E_PRIMITIVE_TYPE primType = EPT_TRIANGLES,
			const core::vector3df& position = core::vector3df(0,0,0),
			const core::vector3df& rotation = core::vector3df(0,0,0),
			const core::vector3df& scale = core::vector3df(1.0f, 1.0f, 1.0f) );

		/// @brief class destructor
		virtual ~CAutoMeshSceneNode();

		/// @brief render SceneNode depending on PrimitiveType
		virtual void render() _IRR_OVERRIDE_;

		/// @brief getter
		virtual E_PRIMITIVE_TYPE getPrimitiveType( ) const
		{
			return PrimitiveType;
		}

		/// @brief setter
		virtual void setPrimitiveType( E_PRIMITIVE_TYPE primType )
		{
			PrimitiveType = primType;
		}

		/// @brief getter
		virtual u16 getLineStipple( ) const
		{
			return LineStipple;
		}

		/// @brief setter
		virtual void setLineStipple( const u16& lineStipple )
		{
			LineStipple = lineStipple;
		}

		/// @brief getter
		virtual u32 getMeshBufferCount() const  // inline
		{
			_IRR_DEBUG_BREAK_IF( !Mesh )
			return Mesh->getMeshBufferCount();
		}

	protected:

		/// @brief render a single meshbuffer depending on classes PrimitiveType
		void drawMeshBufferEx( IMeshBuffer* buffer );

	private:
		E_PRIMITIVE_TYPE PrimitiveType;
		u16 LineStipple;
		//s32 LineFactor;

	};

} // end namespace scene
} // end namespace irr


#endif // __IRR_C_DYNAMIC_EQ_SCENE_NODE_H__

