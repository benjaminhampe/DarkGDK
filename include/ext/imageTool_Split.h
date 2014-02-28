// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_SPLIT_IMAGES_H__
#define __IRR_EXT_SPLIT_IMAGES_H__

#include <irrlicht.h>
#include <../source/Irrlicht/CImage.h>

namespace irr{
// namespace video{

inline video::IImage* loadImage( video::IVideoDriver* driver, const io::path& filename, ILogger* logger = 0 )
{
	#ifdef _DEBUG
	if (logger)
	{
		core::stringc txt = "loadImage(";
		txt += filename;
		txt += ") = ";
		logger->log( txt.c_str(), ELL_INFORMATION );
	}
	#endif // _DEBUG

	if (!driver)
	{
		if (logger)
		{
			logger->log( "no valid videodriver pointer", ELL_ERROR );
		}
		return 0;
	}

	bool bMipMaps = driver->getTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS );
	driver->setTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS, false );
	video::IImage* img = driver->createImageFromFile( filename );
	driver->setTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS, bMipMaps );
	return img;
}


inline video::ITexture* loadTexture( video::IVideoDriver* driver, const io::path& filename, ILogger* logger = 0 )
{
	#ifdef _DEBUG
	if (logger)
	{
		core::stringc txt = "loadTexture(";
		txt += filename;
		txt += ") = ";
		logger->log( txt.c_str(), ELL_INFORMATION );
	}
	#endif // _DEBUG

	if (!driver)
	{
		if (logger)
		{
			logger->log( "no valid videodriver pointer", ELL_ERROR );
		}
		return 0;
	}

	bool bMipMaps = driver->getTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS );
	driver->setTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS, false );
	video::ITexture* tex = driver->getTexture( filename );
	driver->setTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS, bMipMaps );
	return tex;
}

inline bool splitImage( video::IImage* src, core::array<video::IImage*>& container, u32 nRows = 10, u32 nCols = 10, ILogger* logger = 0 )
{
	#ifdef _DEBUG
	if (logger)
	{
		core::stringc txt = "splitImage(";
		txt += nRows;
		txt += ",";
		txt += nCols;
		txt += ")...BEGIN";
		logger->log( txt.c_str(), ELL_INFORMATION );
	}
	#endif // _DEBUG

	if (!src)
	{
		if (logger)
		{
			logger->log( "no valid image pointer", ELL_ERROR );
		}
		return false;
	}

	if (nRows<1)
	{
		if (logger)
		{
			logger->log( "no valid row count", ELL_ERROR );
		}
		return false;
	}

	if (nCols<1)
	{
		if (logger)
		{
			logger->log( "no valid column count", ELL_ERROR );
		}
		return false;
	}

	const u32 w = src->getDimension().Width;
	const u32 h = src->getDimension().Height;
	const u32 step_x = w / nCols;
	const u32 step_y = h / nRows;

	if (step_x==0 || step_y==0)
	{
		if (logger)
		{
			logger->log( "cant create image with zero size", ELL_ERROR );
		}
		return false;
	}

	container.reallocate( nCols * nRows );
	container.set_used(0);

	for (u32 r=0; r<nRows; r++)
	{
		u32 y = r*step_y;
		for (u32 c=0; c<nCols; c++)
		{
			u32 x = c*step_x;
			video::IImage* img = (video::IImage*)new video::CImage( src->getColorFormat(), core::dimension2du(step_x, step_y) );
			if (!img)
			{
				if (logger)
				{
					logger->log( "no valid column count", ELL_ERROR );
				}
			}
			else
			{
				for (u32 iy=0; iy<step_y; iy++)
				{
					for (u32 ix=0; ix<step_x; ix++)
					{
						img->setPixel( ix,iy, src->getPixel( core::min_<u32>(x+ix,w-1), core::min_<u32>(y+iy, h-1)) );
					}
				}

				container.push_back( img );
			}
		}
	}

	return true;
}

} // end namespace irr

#endif
