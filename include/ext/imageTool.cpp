// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include <imageTool.h>

#include <../../source/Irrlicht/CImage.h>
namespace irr
{

namespace video
{


//! @return analyzationResult image from input-image
IImage*	Tool::analyze( IImage* src)
{
	if (!src)
		return 0;

	core::dimension2du s = src->getDimension();
	s *= 2;

	CImage* dst = new CImage( video::ECF_A8R8G8B8, s );
	if (!dst)
		return 0;

	dst->fill( 0 );

	//! write Alpha Channel
	u32 x = 0;
	u32 y = 0;
	for (u32 py = 0; py<s.Height; py++)
	{
		for (u32 px = 0; px<s.Width; px++)
		{
			SColor color(255,0,0,0);
			const SColor& pixel = src->getPixel( px, py );
			color.set(255, pixel.getAlpha(), pixel.getAlpha(), pixel.getAlpha() );
			dst->setPixel( px+x, py+y, color );
		}
	}

	//! write Red Channel
	x = s.Width;
	y = 0;
	for (u32 py = 0; py<s.Height; py++)
	{
		for (u32 px = 0; px<s.Width; px++)
		{
			SColor color(255,0,0,0);
			const SColor& pixel = src->getPixel( px, py );
			color.set(255, pixel.getRed(), 0, 0 );
			dst->setPixel( px+x, py+y, color );
		}
	}

	//! write Green Channel
	x = 0;
	y = s.Height;
	for (u32 py = 0; py<s.Height; py++)
	{
		for (u32 px = 0; px<s.Width; px++)
		{
			SColor color(255,0,0,0);
			const SColor& pixel = src->getPixel( px, py );
			color.set(255, 0, pixel.getGreen(), 0 );
			dst->setPixel( px+x, py+y, color );
		}
	}

	//! write Blue Channel
	x = s.Width;
	y = s.Height;
	for (u32 py = 0; py<s.Height; py++)
	{
		for (u32 px = 0; px<s.Width; px++)
		{
			SColor color(255,0,0,0);
			const SColor& pixel = src->getPixel( px, py );
			color.set(255, 0, 0, pixel.getBlue() );
			dst->setPixel( px+x, py+y, color );
		}
	}

	return dst;
}

//=========================================================================
u32 Tool::getWidth( IImage* src )
//=========================================================================
{
	IT_PRINT("Tool::getWidth()\n");

	if (!src)
		return 0;

	return src->getDimension().Width;
}

//=========================================================================
u32 Tool::getHeight( IImage* src )
//=========================================================================
{
	IT_PRINT("ImageTool::getHeight()\n");

	if (!src)
	{
		IT_ERROR("invalid image pointer\n");
		return 0;
	}

	return src->getDimension().Height;
}

//=========================================================================
bool Tool::drop( IImage* src )
//=========================================================================
{
	IT_PRINT("ImageTool::drop()\n");

	if (!src)
	{
		IT_ERROR("invalid image pointer\n");
		return false;
	}

	src->drop();
	return true;
}


//=========================================================================
bool Tool::deleteImage( IImage* src )
//=========================================================================
{
	IT_PRINT("ImageTool::deleteImage()\n");

	if (!src)
	{
		IT_ERROR("invalid image pointer\n");
		return false;
	}

	src->drop();
	return true;
}



//=========================================================================
IImage* Tool::createImage( const core::dimension2du& size, const SColor& color, ECOLOR_FORMAT format )
//=========================================================================
{
	IT_PRINT("ImageTool::createImage( %d, %d, %d)\n", size.Width, size.Height, format );

	IImage* img = new CImage( format, size );
	if (!img)
	{
		IT_ERROR("could not create image\n" );
		return 0;
	}

	img->fill( color );

	return img;
}

//=========================================================================
IImage* Tool::createImage( u32 w, u32 h, const SColor& color, ECOLOR_FORMAT format )
//=========================================================================
{
	IT_PRINT("ImageTool::createImage( %d, %d, %d)\n", w, h, format );

	IImage* img = new CImage( format, core::dimension2du( w,h ) );
	if (!img)
	{
		printf( "could not create image\n" );
		return 0;
	}

	img->fill( color );

	return img;
}

//=========================================================================
IImage* Tool::createCircleBrush( f32 radius, const SColor& outerColor, const SColor& innerColor, ECOLOR_FORMAT format)
//=========================================================================
{
	IT_PRINT("ImageTool::createCircleBrush( %f )\n", radius );

	video::IImage* img = new CImage( format, core::dimension2du(2*radius, 2*radius));

	if (!img)
	{
		printf( "could not create image\n" );
		return 0;
	}

	img->fill( outerColor );

	drawCircle( img, core::position2di(radius,radius), radius, outerColor, 0, false);

	return (IImage*)img;

}

//=========================================================================
IImage* Tool::createImageFromTexture( IVideoDriver* driver, ITexture* src)
//=========================================================================
{
	IT_PRINT("ImageTool::createImageFromTexture()\n");

    if (!driver)
    {
		IT_ERROR("no valid pointer to video-driver\n");
        return 0;
    }

    if (!src)
    {
		IT_ERROR("no valid texture pointer\n");
        return 0;
    }

	//IImage* dst = new CImage( src->getColorFormat(), src->getSize() );

	IImage* dst = driver->createImage( src, core::position2di(0,0), src->getSize() );
    if (!dst)
    {
		IT_ERROR("could not create image from texture\n");
        return 0;
    }

	return dst;
}

//=========================================================================
ITexture* Tool::createTexture( IVideoDriver* driver, IImage* src)
//=========================================================================
{
	IT_PRINT("ImageTool::createTexture()\n");

	if (!driver)
    {
		IT_ERROR("no valid pointer to video-driver\n");
        return 0;
    }

	if (!src)
    {
		IT_ERROR("no valid image pointer\n");
        return 0;
    }

	ITexture* tex = 0;

	//! my RainbowTexture
	const core::dimension2du SourceSize = src->getDimension();

	core::stringw name(L"img_");
	name+= (s32)SourceSize.Width;
	name+= L"_";
	name+= (s32)SourceSize.Height;
	name+= L"_";
	name+= (s32)IImage::getBitsPerPixelFromFormat( src->getColorFormat() );
	name+= L"_";
	name+= (s32)src->getImageDataSizeInBytes();

	//! save states
	bool b0 = driver->getTextureCreationFlag(ETCF_ALLOW_NON_POWER_2);
	bool b1 = driver->getTextureCreationFlag(ETCF_ALWAYS_16_BIT);
	bool b2 = driver->getTextureCreationFlag(ETCF_ALWAYS_32_BIT);
	bool b3 = driver->getTextureCreationFlag(ETCF_CREATE_MIP_MAPS);
	bool b4 = driver->getTextureCreationFlag(ETCF_FORCE_32_BIT_DO_NOT_USE);
	bool b5 = driver->getTextureCreationFlag(ETCF_NO_ALPHA_CHANNEL);
	bool b6 = driver->getTextureCreationFlag(ETCF_OPTIMIZED_FOR_QUALITY);
	bool b7 = driver->getTextureCreationFlag(ETCF_OPTIMIZED_FOR_SPEED);

	//! my states
	driver->setTextureCreationFlag(ETCF_ALLOW_NON_POWER_2,true);
	driver->setTextureCreationFlag(ETCF_ALWAYS_16_BIT,false);
	driver->setTextureCreationFlag(ETCF_ALWAYS_32_BIT,true);
	driver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS,true);
	driver->setTextureCreationFlag(ETCF_FORCE_32_BIT_DO_NOT_USE,false);
	driver->setTextureCreationFlag(ETCF_NO_ALPHA_CHANNEL,false);
	driver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_QUALITY,true);
	driver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_SPEED,false);

	tex = driver->addTexture(name.c_str(), src, 0);

	//! restore states
	driver->setTextureCreationFlag(ETCF_ALLOW_NON_POWER_2,b0);
	driver->setTextureCreationFlag(ETCF_ALWAYS_16_BIT,b1);
	driver->setTextureCreationFlag(ETCF_ALWAYS_32_BIT,b2);
	driver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS,b3);
	driver->setTextureCreationFlag(ETCF_FORCE_32_BIT_DO_NOT_USE,b4);
	driver->setTextureCreationFlag(ETCF_NO_ALPHA_CHANNEL,b5);
	driver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_QUALITY,b6);
	driver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_SPEED,b7);

    if (!tex)
    {
		IT_ERROR("could not create texture\n");
        return 0;
    }

	return tex;
} // END FUNCTION

//=========================================================================
IImage* Tool::copyImage( IImage* src, const core::recti& area, E_COLOR_PLANE planes )
//=========================================================================
{
	IT_PRINT("ImageTool::copyImage()\n");

    IImage* dst = new CImage( src->getColorFormat(), core::dimension2du( (u32)area.getWidth(), (u32)area.getHeight()) );

    if (!dst)
	{
		IT_ERROR("could not create image\n");
        return 0;
	}

	//!Blit
    s32 x = area.UpperLeftCorner.X;
    s32 y = area.UpperLeftCorner.Y;
//    u32 bytesPerRow = Pitch * Size.Width * BytesPerPixel;
    u8* ptrSrc = (u8*)src->lock() + ((y*src->getPitch()+x) * src->getBytesPerPixel());
    u8* ptrDst = (u8*)dst->lock() + ((y*dst->getPitch()+x) * dst->getBytesPerPixel());
    for (s32 j = 0; j < (s32)dst->getDimension().Height; j++)
    {
        memcpy( (void*)ptrDst, (void*)ptrSrc, dst->getDimension().Width * dst->getBytesPerPixel());
        ptrSrc += src->getPitch() * src->getDimension().Width;
        ptrDst += dst->getPitch() * dst->getDimension().Width;
    }

	return dst;
}

//=========================================================================
IImage* Tool::cloneImage( IImage* src )
//=========================================================================
{
	IT_PRINT("ImageTool::cloneImage()\n");

    if (!src)
	{
		IT_ERROR("no valid image-pointer\n");
        return 0;
	}

    IImage* dst = new CImage( src->getColorFormat(), src->getDimension() );
    if (!dst)
	{
		IT_ERROR("could not create image\n");
        return 0;
	}

	void* srcPtr = src->lock();
	void* dstPtr = dst->lock();
    memcpy( dstPtr, srcPtr, src->getPitch() * src->getDimension().Height );
	dst->unlock();
//	dst->setColorKeyEnabled( IsColorKeyEnabled );
//	dst->setColorKey( ColorKey );
//	dst->setMemoryOwner( true );
	return dst;
}


//=========================================================================
IImage* Tool::loadImage( IVideoDriver* driver, const io::path& filename )
//=========================================================================
{
	IT_PRINT("ImageTool::loadImage()\n");

	if (!driver)
	{
		printf( "Invalid pointer to IVideoDriver\n");
		return 0;
	}

	IImage* img = driver->createImageFromFile( filename );
	if (!img)
	{
		printf( "Could not load image %s\n", core::stringc( filename ).c_str() );
		return 0;
	}

	return img;
}

//=========================================================================
bool Tool::saveImage( IVideoDriver* driver, IImage* src, const io::path& filename )
//=========================================================================
{
	IT_PRINT("ImageTool::saveImage()\n");

	if (!driver)
    {
		IT_ERROR("no valid pointer to video-driver\n");
        return false;
    }

	if (!src)
	{
		IT_ERROR("Invalid pointer to IImage\n");
		return false;
	}

	return driver->writeImageToFile( src, filename );
}


//=========================================================================
///@brief createImageAtlas
//=========================================================================
bool Tool::createAtlas( STexAtlas& atlas, const core::dimension2du& tileCount, const core::dimension2du& tileSize )
//=========================================================================
{
	IT_PRINT("ImageTool::createAtlas( tileCount( %d, %d ), tileSize( %d, %d ) )\n", tileCount.Width, tileCount.Height, tileSize.Width, tileSize.Height );

	if (!atlas.Driver)
    {
		IT_ERROR("no valid pointer to video-driver\n");
        return false;
    }

	/// Delete old image
	if (atlas.Image)
	{
		IT_PRINT("delete old image\n" );
		atlas.Image->drop();
		atlas.Image = 0;
	}

	/// Create new image
	const u32 w = tileCount.Width * tileSize.Width;
	const u32 h = tileCount.Height * tileSize.Height;
	atlas.Image = new CImage( ECF_A8R8G8B8, core::dimension2du( w, h ) );

	if (!atlas.Image)
	{
		IT_ERROR("could not create atlas-image ( %d, %d )\n", w, h );
		return false;
	}

	atlas.TileCount = tileCount;
	atlas.TileSize = tileSize;
	atlas.Image->fill( 0x00000000 );

	IT_PRINT( "created atlas-image ( %d, %d )\n", w, h );
	return true;
}

//=========================================================================
bool Tool::setAtlasTile( STexAtlas& atlas, IImage* src, u32 index_x, u32 index_y )
//=========================================================================
{
	IT_PRINT("ImageTool::setAtlasTile( %d, %d )\n", index_x, index_y );
	if (!atlas.Image)
	{
		printf( "Invalid image pointer\n" );
		return false;
	}

	/// source and target size ( for scaling to tile-size, if needed )
	const u32 index = index_x + index_y * atlas.TileCount.Width;
	const u32 src_w = src->getDimension().Width;
	const u32 src_h = src->getDimension().Height;
	const u32 tile_w = atlas.TileSize.Width;
	const u32 tile_h = atlas.TileSize.Height;
	printf("AtlasImage[%d] = src ( %d, %d ) => dst ( %d, %d )\n",
		index, src_w, src_h, tile_w, tile_h );

	/// abort
	if ( src_w == 0 || src_h == 0 || tile_w == 0 || tile_h == 0 )
		return 0;

	/// target position
	const u32 x = index_x * tile_w;
	const u32 y = index_y * tile_h;
	printf("final pos[]( %d, %d )\n", x, y );

	/// scale image, if needed
	bool needScaling = false;
	if ( (src_w != tile_w) || (src_h != tile_h) )
	{
		needScaling = true;

		/// Create temporary image
		IImage* tmp = new CImage( ECF_A8R8G8B8, atlas.TileSize );
		if (!tmp)
		{
			printf("Could not create temporary image for scaling ( %d, %d )\n", tile_w, tile_h );
		}
		else
		{
			printf("Created temporary image for scaling ( %d, %d )\n", tile_w, tile_h );
			src->copyToScaling( tmp );
			src = tmp;
		}
	}

	/// Copy to final image
	if (src)
	{
		src->copyTo( atlas.Image,
			core::position2di(x,y),
			core::recti( core::position2di(0,0), src->getDimension() ) );
	}
	else
	{
		printf("Could not copy to final image\n" );
	}

	/// CleanUp
	if (needScaling)
	{
		printf("CleanUp\n" );
		src->drop();
		src = 0;
	}

	/// quit
	return true;
}

//=========================================================================
bool Tool::updateAtlas( STexAtlas& atlas )
//=========================================================================
{
	IT_PRINT("ImageTool::updateAtlasImage()\n" );

	/// Abort, if update-source invalid
	if (!atlas.Image)
	{
		printf( "Cannot update from empty image\n" );
		return false;
	}

	/// Delete, if exist
	if (atlas.Texture)
	{
		atlas.Texture->drop();
		atlas.Texture = 0;
	}

	/// Create new texture from image-source
	atlas.Texture = atlas.Driver->addTexture( "", atlas.Image, 0);
	if (!atlas.Texture)
	{
		printf( "Could not add texture to driver\n" );
		return false;
	}

	/// quit
	printf( "Added texture %s to driver\n", core::stringc( atlas.Texture->getName().getPath() ).c_str() );
	return true;
}


//=========================================================================
bool Tool::deleteAtlas( STexAtlas& atlas )
//=========================================================================
{
	IT_PRINT("ImageTool::deleteAtlas()\n" );

	/// Delete, if exist
	if (atlas.Image)
	{
		atlas.Image->drop();
		atlas.Image = 0;
	}

	/// Delete, if exist
	if (atlas.Texture)
	{
		atlas.Texture->drop();
		atlas.Texture = 0;
	}

	return true;
}

//! @author extension 2012 by BenjaminHampe@gmx.de
//! @brief count ARGB colors in the image, but better use getUniqueColorArray().size()
//! @param color-planes that will be taken into account during the unique-count-count
//! @return amount of unique ARGB colors in the image
u32 Tool::getUniqueColorCount( IImage* src, E_COLOR_PLANE planes)
{
	IT_PRINT("ImageTool::getUniqueColorCount()\n");

	return getUniqueColorArray( src, planes ).size();
}

//! @author extension 2012 by BenjaminHampe@gmx.de
//! @brief array of all unique ARGB colors of the image
//! @param color-planes that will be taken into account during the unique-count-count
//! @return array of all unique ARGB colors of the image
core::array< SColor > Tool::getUniqueColorArray( IImage* src, E_COLOR_PLANE planes)
{
	IT_PRINT("ImageTool::getUniqueColorArray()\n");

    core::array< SColor > container;

	if (!src)
		return container;

    if (src->getDimension() == core::dimension2du(0,0))
        return container;

    container.reallocate( src->getDimension().Width * src->getDimension().Height );
    container.set_used(0);

    for (u32 y=0; y<src->getDimension().Height; y++)
    {
        for (u32 x=0; x<src->getDimension().Width; x++)
        {
            SColor color = src->getPixel(x,y);

            if (!(planes & ECP_ALPHA))
				color.setAlpha(0);
            if (!(planes & ECP_RED))
				color.setRed(0);
            if (!(planes & ECP_GREEN))
				color.setGreen(0);
            if (!(planes & ECP_BLUE))
				color.setBlue(0);

            bool found = false;
            for (u32 i=0; i<container.size(); i++)
            {
                if (container[i] == color)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                container.push_back(color);
            }
        }
    }

    return container;
}


//! returns a new image from user-defined color-planes and writes them to user-defined planes only
//! if ECP_ALPHA not set, then ALPHA = 0

IImage* Tool::extract( IImage* src, E_COLOR_PLANE srcPlanes, E_COLOR_PLANE dstPlanes )
{
	IT_PRINT("ImageTool::extract()\n");

	if (!src)
		return 0;

	IImage* img = (IImage*)new CImage( src->getColorFormat(), src->getDimension() );
	if (!img)
		return 0;

	if (srcPlanes == ECP_NONE)
	{
		src->fill(0);
		return img;
	}

	const core::dimension2du Size = src->getDimension();

	for (u32 y=0; y<Size.Height; ++y)
	{
		for (u32 x=0; x<Size.Width; ++x)
		{
			SColor c(0);
			SColor d = src->getPixel(x,y);

			if (srcPlanes^ECP_ALPHA)
			{
				c.setAlpha(d.getAlpha());
			}
			else if (srcPlanes^ECP_RED)
			{
				c.setRed(d.getRed());
			}
			else if (srcPlanes^ECP_GREEN)
			{
				c.setGreen(d.getGreen());
			}
			else if (srcPlanes^ECP_BLUE)
			{
				c.setBlue(d.getBlue());
			}

			img->setPixel(x,y,c);
		}
	}
	return img;
}


} // end namespace video

} // end namespace irr
