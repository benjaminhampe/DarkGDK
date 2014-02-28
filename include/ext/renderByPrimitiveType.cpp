// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include <renderByPrimitiveType.h>

namespace irr
{
namespace video
{
	// this function is for 32bit indices
	void drawElements(
		IVideoDriver* driver,
		const core::array<video::S3DVertex>& vertices,
		const core::array<s32>& indices,
		scene::E_PRIMITIVE_TYPE primType)
	{
		if (!driver)
			return;

		u32 primCount = 0;

		const u32& indexCount = indices.size();

		switch (primType)
		{
			case scene::EPT_POINTS:
					primCount = indexCount;
					break;
			case scene::EPT_LINE_STRIP:
					primCount = indexCount-1;
					break;
			case scene::EPT_LINE_LOOP:
					primCount = indexCount-1;
					break;
			case scene::EPT_LINES:
					primCount = indexCount/2;
					break;
			case scene::EPT_TRIANGLE_STRIP:
					primCount = (indexCount-2)/3;
					break;
			case scene::EPT_TRIANGLE_FAN:
					primCount = (indexCount-2)/3;
					break;
			case scene::EPT_TRIANGLES:
					primCount = indexCount/3;
					break;
			case scene::EPT_QUAD_STRIP:
					primCount = (indexCount-2)/4;
					break;
			case scene::EPT_QUADS:
					primCount = indexCount/4;
					break;
			case scene::EPT_POLYGON:
					primCount = indexCount-1;
					break;
			case scene::EPT_POINT_SPRITES:
					primCount = indexCount;
					break;
			default:
					break;
		}

		driver->drawVertexPrimitiveList( vertices.const_pointer(),
				vertices.size(), indices.const_pointer(),
				primCount, video::EVT_STANDARD,
				primType, video::EIT_32BIT);
	}

	void drawMeshBufferEx( IVideoDriver* driver, scene::IMeshBuffer* buffer, scene::E_PRIMITIVE_TYPE primType, const core::vector3df& offset )
	{
		if (!driver)
			return;

		if (!buffer)
			return;

		u32 primCount = 0;

		const u32& indexCount = buffer->getIndexCount();
		const E_VERTEX_TYPE vertexType = buffer->getVertexType();
		const E_INDEX_TYPE indexType = buffer->getIndexType();

		switch (primType)
		{
			case scene::EPT_POINTS:
					primCount = indexCount;
					break;
			case scene::EPT_LINE_STRIP:
					primCount = indexCount-1;
					break;
			case scene::EPT_LINE_LOOP:
					primCount = indexCount-1;
					break;
			case scene::EPT_LINES:
					primCount = indexCount/2;
					break;
			case scene::EPT_TRIANGLE_STRIP:
					primCount = (indexCount-2)/3;
					break;
			case scene::EPT_TRIANGLE_FAN:
					primCount = (indexCount-2)/3;
					break;
			case scene::EPT_TRIANGLES:
					primCount = indexCount/3;
					break;
			case scene::EPT_QUAD_STRIP:
					primCount = (indexCount-2)/4;
					break;
			case scene::EPT_QUADS:
					primCount = indexCount/4;
					break;
			case scene::EPT_POLYGON:
					primCount = indexCount-1;
					break;
			case scene::EPT_POINT_SPRITES:
					primCount = indexCount;
					break;
			default:
					break;
		}

	//	driver->setMaterial(buffer->getMaterial());

		bool offset_vertices = ( !core::equals( offset.X, 0.0f ) || !core::equals( offset.Y, 0.0f ) || !core::equals( offset.Z, 0.0f ) );

		if ( offset_vertices )
		{

			const core::matrix4 world_matrix = driver->getTransform( ETS_WORLD );

			core::matrix4 my_matrix = core::IdentityMatrix;

			my_matrix.setTranslation( offset );

			driver->setTransform( video::ETS_WORLD, world_matrix * my_matrix );

			driver->drawVertexPrimitiveList(
					buffer->getVertices(), buffer->getVertexCount(),
					buffer->getIndices(), primCount,
					vertexType, primType, indexType);

			driver->setTransform( video::ETS_WORLD, world_matrix );
		}
		else
		{
			driver->drawVertexPrimitiveList(
					buffer->getVertices(), buffer->getVertexCount(),
					buffer->getIndices(), primCount,
					vertexType, primType, indexType);
		}



	}

	void drawMeshEx( IVideoDriver* driver, scene::IMesh* mesh, scene::E_PRIMITIVE_TYPE primType)
	{
		if (!driver)
			return;

		if (!mesh)
			return;

		u32 bufferCount = mesh->getMeshBufferCount();

		for (u32 i=0; i<bufferCount; i++)
		{
			scene::IMeshBuffer* buffer = mesh->getMeshBuffer( i );
			if ( buffer )
			{

				driver->setMaterial( buffer->getMaterial() );

				drawMeshBufferEx( driver, buffer, primType );
			}
		}
	}

	void drawCoordSystem( f32 size, const core::vector3df& pos )
	{
		glMatrixMode( GL_MODELVIEW_MATRIX );
		glPushMatrix( );
		glTranslatef( pos.X,pos.Y,pos.Z );
		glRotatef( 0,1,0,0 );
		glRotatef( 0,0,1,0 );
		glRotatef( 0,0,0,1 );
		glBegin( GL_LINES );
		glColor4ub( 255,0,0,255 ); 	// red
		glVertex3f( pos.X,pos.Y,pos.Z );		// origin
		glVertex3f( pos.X+size,pos.Y,pos.Z );  	// x-axis
		glColor4ub( 0,255,0,255 ); 	// green
		glVertex3f( pos.X,pos.Y,pos.Z );		// origin
		glVertex3f( pos.X,pos.Y+size, pos.Z );  	// y-axis
		glColor4ub( 0,0,255,255 ); 	// blue
		glVertex3f( pos.X,pos.Y,pos.Z );		// origin
		glVertex3f( pos.X,pos.Y,pos.Z+size );  	// z-axis
		glEnd( );
		glPopMatrix();
	}

	void drawXMeter( const core::vector3df& pos, s32 x_min, s32 x_max )
	{
		GLboolean IsLightEnabled = 0;
		glGetBooleanv(GL_LIGHTING, &IsLightEnabled);
		glDisable(GL_LIGHTING);
		glMatrixMode( GL_MODELVIEW_MATRIX );
		glPushMatrix( );
		//glLoadIdentity();
		glTranslatef( 0,0,0 );
		glBegin( GL_LINES );
		glColor4ub( 255,255,255,255 ); 	// red
		glVertex3f( pos.X + (f32)x_min, pos.Y,pos.Z );
		glVertex3f( pos.X + (f32)x_max, pos.Y,pos.Z );
		for ( s32 x = x_min; x<=x_max; x++)
		{
			f32 fx = pos.X + (f32)x;

			glVertex3f( fx, pos.Y, pos.Z );		// origin
			if (x%100==0)
			{
				glVertex3f( fx, pos.Y, pos.Z-25.0f );  	// -z direction
			}
			else if (x%10==0)
			{
				glVertex3f( fx, pos.Y,pos.Z-10.0f );  	// -z direction
			}
			else
			{
				glVertex3f( fx,pos.Y,pos.Z-5.0f );  	// -z direction
			}
		}
		glEnd( );
		glPopMatrix();

		if (IsLightEnabled)
			glEnable(GL_LIGHTING);
	}

	void drawYMeter( const core::vector3df& pos, s32 y_min, s32 y_max )
	{
		GLboolean IsLightEnabled = 0;
		glGetBooleanv(GL_LIGHTING, &IsLightEnabled);
		glDisable(GL_LIGHTING);

		glMatrixMode( GL_MODELVIEW_MATRIX );
		glPushMatrix( );
		//glLoadIdentity();
		glTranslatef( 0,0,0 );
		glBegin( GL_LINES );
		glColor4ub( 255,255,255,255 ); 	// red
		glVertex3f( pos.X, pos.Y+(f32)y_min,pos.Z );
		glVertex3f( pos.X, pos.Y+(f32)y_max,pos.Z );
		for ( s32 y=y_min; y<=y_max; y++)
		{
			f32 fy = pos.Y + (f32)y;

			glVertex3f( pos.X, fy, pos.Z );		// origin
			if (y%100==0)
			{
				glVertex3f( pos.X-25.0f, fy, pos.Z );  	// -x direction
			}
			else if (y%10==0)
			{
				glVertex3f( pos.X-10.0f, fy, pos.Z );  	// -x direction
			}
			else
			{
				glVertex3f( pos.X-5.0f, fy, pos.Z );  	// -x direction
			}
		}
		glEnd( );
		glPopMatrix();

		if (IsLightEnabled)
			glEnable(GL_LIGHTING);
	}

	void drawZMeter( const core::vector3df& pos, s32 z_min, s32 z_max )
	{
		GLboolean IsLightEnabled = 0;
		glGetBooleanv(GL_LIGHTING, &IsLightEnabled);
		glDisable(GL_LIGHTING);

		glMatrixMode( GL_MODELVIEW_MATRIX );
		glPushMatrix( );
		// glLoadIdentity();
		glTranslatef( 0,0,0 );
		glBegin( GL_LINES );
		glColor4ub( 255,255,255,255 ); 	// red
		glVertex3f( pos.X, pos.Y,pos.Z + (f32)z_min );
		glVertex3f( pos.X, pos.Y,pos.Z + (f32)z_max );

		for ( s32 z = z_min; z<=z_max; z++)
		{
			f32 fz = pos.Z + (f32)z;

			glVertex3f( pos.X, pos.Y, fz );		// origin
			if (z%100==0)
			{
				glVertex3f( pos.X-25.0f, pos.Y, fz );  	// -x direction
			}
			else if (z%10==0)
			{
				glVertex3f( pos.X-10.0f, pos.Y, fz );  	// -x direction
			}
			else
			{
				glVertex3f( pos.X-5.0f, pos.Y, fz ); // -x direction
			}
		}

		glEnd( );
		glPopMatrix();

		if (IsLightEnabled)
			glEnable(GL_LIGHTING);
	}

} // end namespace video
} // end namespace irr
