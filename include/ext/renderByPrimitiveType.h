// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_RENDER_MESHBUFFER_AND_VERTEX_ARRAYA_UTILS_H__
#define __IRR_EXT_RENDER_MESHBUFFER_AND_VERTEX_ARRAYA_UTILS_H__

#include <irrlicht.h>

#include <GL/gl.h>
#include <GL/glu.h>

namespace irr
{
	namespace video
	{
		// this function is for 32bit indices
		void drawElements( IVideoDriver* driver,
							const core::array<video::S3DVertex>& vertices,
							const core::array<s32>& indices,
							scene::E_PRIMITIVE_TYPE primType = scene::EPT_TRIANGLES);

		void drawMeshBufferEx( IVideoDriver* driver, scene::IMeshBuffer* buffer, scene::E_PRIMITIVE_TYPE primType = scene::EPT_TRIANGLES, const core::vector3df& offset = core::vector3df(0,0,0));

		void drawMeshEx( IVideoDriver* driver, scene::IMesh* mesh, scene::E_PRIMITIVE_TYPE primType = scene::EPT_TRIANGLES);

		void drawCoordSystem( f32 size = 100.0f, const core::vector3df& pos = core::vector3df(0,0,0) );

		void drawXMeter( const core::vector3df& pos = core::vector3df(0,0,-1), s32 x_min = 0, s32 x_max = 1000 );

		void drawYMeter( const core::vector3df& pos = core::vector3df(0,0,-10), s32 y_min = 0, s32 y_max = 500 );

		void drawZMeter( const core::vector3df& pos = core::vector3df(-1,0,0), s32 z_min = 0, s32 z_max = 500 );
	} // end namespace video

} // end namespace irr

#endif // __IRR_EXT_RENDER_MESHBUFFER_AND_VERTEX_ARRAYA_UTILS_H__
