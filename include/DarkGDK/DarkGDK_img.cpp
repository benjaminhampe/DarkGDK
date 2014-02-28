#include "DarkGDK_img.h"

#include "DarkGDK_struct.h"

namespace irr
{

//! dbARGB
u32 dbARGB(u8 a, u8 r, u8 g, u8 b)
{
	return ((a<<24) | (r<<16) | (g<<8) | b);
}

//! RGB
u32 dbARGB(u8 r, u8 g, u8 b)
{
	return (0xFF000000 | (r<<16) | (g<<8) | b);
}

//! lösche A und setze A neu
u32 dbARGB_setA(u32 color, u8 a)
{
	return ( (color&0x00FFFFFF) | (a<<24) );
}

//! lösche A und setze A=255
u32 dbARGB_setOpaque(u32 color)
{
	return color|0xFF000000;
}

//! lösche A und setze A=255
u32 dbARGB_ghostOff(u32 color)
{
	return color|0xFF000000;
}

//! lösche A und setze A=128
u32 dbARGB_ghostOn(u32 color)
{
	return  color|0x8000000;
}

//! lösche A und setze A=0
u32 dbARGB_setTransparent(u32 color)
{
	return color&0x00FFFFFF;
}

//! lösche R und setze R neu
u32 dbARGB_setR(u32 color, u8 r)
{
	return ((color&0xFF00FFFF) | (r<<16) );
}

//! lösche G und setze G neu
u32 dbARGB_setG(u32 color, u8 g)
{
	return ((color&0xFFFF00FF) | (g<<8) );
}

//! lösche B und setze B neu
u32 dbARGB_setB(u32 color, u8 b)
{
	return ((color&0xFFFFFF00) | b);
}

//! lösche RGB und setze RGB neu
u32 dbARGB_setRGB(u32 color, u32 rgb)
{
	return ((color&0xFF000000)|(rgb&0x00FFFFFF));
}

//! extract A component
u8 dbARGB_A(u32 color)
{
	return (u8)(color>>24);
}

//! extract A component
u8 dbARGB_R(u32 color)
{
	return (u8)(color>>16);
}

//! extract A component
u8 dbARGB_G(u32 color)
{
	return (u8)(color>>8);
}

//! extract A component
u8 dbARGB_B(u32 color)
{
	return (u8)color;
}




// -----------------------------------------------------------------------------------------------------------
// dbImageExist
// -----------------------------------------------------------------------------------------------------------
bool dbImageExist( u32 imgID ) // i von 1..n, i=0 invalid
{
	dbPRINT("dbImageExist(%d)\n", imgID);

	if ( dbGetImage( imgID ) )
	{
		return true;
	}
	else
	{
		dbERROR( "image does not exist\n");
		return false;
	}
}

// -----------------------------------------------------------------------------------------------------------
// dbFreeImage
// -----------------------------------------------------------------------------------------------------------

u32 dbFreeImage(u32 start)
{
	dbPRINT("dbFreeImage()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	u32 id = app.Images.size()+1;

	dbPRINT("return free id %d\n", id);
	return id;
}

// -----------------------------------------------------------------------------------------------------------
// dbDeleteImage
// -----------------------------------------------------------------------------------------------------------

bool dbDeleteImage( u32 imgID )
{
	dbPRINT("dbDeleteImage(%d) = ", imgID);

	if (!dbImageExist(imgID))
	{
		dbERROR("image does not exist\n");
		return false;
	}

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	const u32 count = app.Images.size();
	const u32 index = dbGetImageArrayIndex(imgID);

	/// get pointer and call its remove() function
	video::IImage* img = app.Images[index].Image;
	if (img)
	{
		img->drop();
		img = 0;
	}

	video::ITexture* tex = app.Images[index].Texture;
	if (tex)
	{
		if (app.Device)
		{
			app.Device->getVideoDriver()->removeTexture( tex );
		}
		tex = 0;
	}

	/// return status
	if (count != app.Images.size())
		return true;
	else
		return false;
}

/// dbAddImage
u32 dbAddImage( u32 imgID, video::IImage* img )
{
	dbPRINT( "dbAddImage()\n");

	if (!img)
		return 0;

	if (imgID > 0)
	{
		dbDeleteImage( imgID );
	}

	DarkGDK_SImage sImage;
	sImage.Image = img;
	sImage.Texture = 0;
	sImage.ID = dbFreeImage();

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	app.Images.push_back( sImage );

	return sImage.ID;
}

/// dbAddTexture
u32 dbAddTexture( u32 imgID, video::ITexture* tex )
{
	dbPRINT( "dbAddTexture()\n");

	if (!tex)
		return 0;

	if (imgID > 0)
	{
		dbDeleteImage( imgID );
	}

	DarkGDK_SImage sImage;
	sImage.Image = 0;
	sImage.Texture = tex;
	sImage.ID = dbFreeImage();

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	app.Images.push_back( sImage );

	return sImage.ID;
}


/// dbGetTexture
video::ITexture* dbGetTexture( u32 imgID )
{
	dbPRINT( "dbGetTexture(%d)", imgID );

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	if (imgID == 0)
		return 0;

	const u32 imgCount = app.Images.size();

	u32 i = 0;
	bool found = false;

	while (!found && i<imgCount)
	{
		if (app.Images[i].ID == imgID)
			found = true;
		else
			i++;
	}

	if (found)
	{
		video::ITexture* tex = app.Images[i].Texture;
		if (tex)
		{
			return tex;
		}
		else
		{
			video::IImage* img = app.Images[i].Image;
			if (img)
			{
				if (app.Device)
				{
					return app.Device->getVideoDriver()->addTexture( "", img, 0);
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
	}

	return 0;
}

/// dbGetImage
video::IImage* dbGetImage( u32 imgID )
{
	dbPRINT( "dbGetImage(%d)", imgID );

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	if (imgID == 0)
	{
		dbERROR("Invalid image-id\n");
		return 0;
	}

	const u32 imgCount = app.Images.size();

	u32 i = 0;
	bool found = false;

	while (!found && i<imgCount)
	{
		if (app.Images[i].ID == imgID)
			found = true;
		else
			i++;
	}

	if (found)
	{
		video::IImage* img = app.Images[i].Image;
		if (img)
		{
			dbPRINT("image found\n");
			return img;
		}
		else
		{
			video::ITexture* tex = app.Images[i].Texture;
			if (tex)
			{
				if (app.Device)
				{
					img = app.Device->getVideoDriver()->createImage( tex, core::position2di(0,0), tex->getSize() );
					if (img)
					{
						dbPRINT("created image from texture\n");
					}
					else
					{
						dbERROR("could not create image from texture\n");
					}

					return img;
				}
				else
				{
					dbERROR("no device available to create image from texture\n");
					return 0;
				}
			}
			else
			{
				dbERROR("no image and no texture available\n");
				return 0;
			}
		}
	}
	return 0;
}

///@brief Return internal array-index for ObjectID
u32 dbGetImageArrayIndex(u32 imgID)
{
	dbPRINT("dbGetImageArrayIndex()\n");

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	const u32 count = app.Images.size();

	if (imgID == 0)
	{
		dbERROR("no valid image-id\n");
		return count;
	}

	bool found = false;
	u32 i = 0;
	while (!found && i<count)
	{
		if (app.Images[i].ID == imgID)
			found = true;
		else
			i++;
	};

	if (found)
	{
		dbPRINT("found image at array-index %d\n", i);
		return i;
	}
	else
	{
		dbERROR("no image found, return array-size %d\n", count);
		return count;
	}
}

// dbImageWidth
u32 dbImageWidth( u32 imgID )
{
	video::IImage* img = dbGetImage( imgID );
	if (!img) return 0;
	return img->getDimension().Width;
}

// dbImageHeight
u32 dbImageHeight( u32 imgID )
{
	video::IImage* img = dbGetImage( imgID );
	if (!img) return 0;
	return img->getDimension().Height;
}

// dbImageBits
u32 dbImageBits( u32 imgID )
{
	video::IImage* img = dbGetImage( imgID );
	if (!img) return 0;
	return img->getBitsPerPixel();
}

// dbImageFormat
video::ECOLOR_FORMAT dbImageFormat( u32 imgID )
{
	video::IImage* img = dbGetImage( imgID );
	if (!img) return video::ECF_UNKNOWN;
	return img->getColorFormat();
}

// dbImageFormatString
core::stringc dbImageFormatString( u32 imgID )
{
	core::stringc s;
//	video::IImage* img = dbGetImage( imgID );
//	if (!img) return s;
//	s+=video::ECOLOR_FORMAT_STRINGS[(u32)img->getColorFormat()];
	return s;
}

// dbLoadImage
bool dbLoadImage( u32 imgID, const io::path& fileName, u32 iFilter)
{
	if (imgID == 0)
		return false;

	dbDeleteImage( imgID );



	return true;
}

// -----------------------------------------------------------------------------------------------------------
// dbSaveImage
// -----------------------------------------------------------------------------------------------------------
bool dbSaveImage( u32 imgID,  const io::path& fileName, u32 iFilter)
{
	video::IImage* img = dbGetImage( imgID );
	if (!img) return false;

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
u8* dbLockImage(u32 id)
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
//		if (id==0) return NULL;
//		dbWarning("dbLockImage(): Not implemented yet :-)");
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void dbUnlockImage(u32 id)
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
//		if (id==0) return;
//		dbWarning("dbUnlockImage(): Not implemented yet :-)");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool dbMakeImage( u32 id, u32 w, u32 h, const video::SColor& fillColor, video::ECOLOR_FORMAT format)
{
	video::IImage* img = video::Tool::createImage( core::dimension2du(w,h), fillColor, format );
	return dbAddImage( id, img );
}

// -----------------------------------------------------------------------------------------------------------
// dbFill
// -----------------------------------------------------------------------------------------------------------
void dbFill( u32 imgID, const video::SColor& color )
{
	video::IImage* img=dbGetImage(imgID);
	if (!img) return;

	video::Tool::fill( img, color, video::ECP_ALL, false);
}

//// -----------------------------------------------------------------------------------------------------------
//// dbFill
//// -----------------------------------------------------------------------------------------------------------
//void dbFill( u32 imgID, const video::SColor& color, const core::recti& target, bool blend)
//{
//	video::IImage* img=dbGetImage(imgID);
//	if (!img) return;
//
//	video::Tool::fill( img, color, video::ECP_ALL, blend);
//}
//
//// -----------------------------------------------------------------------------------------------------------
//// dbFill
//// -----------------------------------------------------------------------------------------------------------
//void dbFill( u32 imgID, const video::SColor& color, video::E_COLOR_PLANE planes, bool blend)
//{
//	video::IImage* src=dbGetImage(imgID);//
//	if (!src) return; 														// abort
//}
//
//// -----------------------------------------------------------------------------------------------------------
//// dbFill
//// -----------------------------------------------------------------------------------------------------------
//void dbFill( u32 imgID, const video::SColor& color, video::E_COLOR_PLANE planes, const core::recti& target, bool blend)
//{
//	video::IImage* src=dbGetImage(imgID);
//	if (!src) return; 														// abort
//
//}

// -----------------------------------------------------------------------------------------------------------
// dbFloodfill
// -----------------------------------------------------------------------------------------------------------
bool dbFloodfill( u32 imgID, s32 x, s32 y, const video::SColor& fillColor, const video::SColor& old)
{
	video::IImage* img=dbGetImage(imgID);
	video::Tool::floodFill( img, x, y, fillColor, old );
	return true;
}

// -----------------------------------------------------------------------------------------------------------
// dbImageSetPixel
// -----------------------------------------------------------------------------------------------------------
void dbDrawPixel( u32 imgID, s32 x, s32 y, const video::SColor& color, bool blend)
{
	video::IImage* img=dbGetImage(imgID);
	video::Tool::drawPixel( img, x, y, color, blend);
}

// -----------------------------------------------------------------------------------------------------------
// dbSetPixel
// -----------------------------------------------------------------------------------------------------------
void dbSetPixel( u32 imgID, s32 x, s32 y,	const video::SColor& color, bool blend)
{
	dbDrawPixel( imgID, x, y, color, blend);
}

// -----------------------------------------------------------------------------------------------------------
// dbImageSetPixelAlways
// -----------------------------------------------------------------------------------------------------------
void dbDrawPixelAlways( u32 imgID, s32 x, s32 y, const video::SColor& color, bool blend)
{
	video::IImage* img=dbGetImage(imgID);
	video::Tool::drawPixelAlways( img, x, y, color, blend);
}

// -----------------------------------------------------------------------------------------------------------
// dbGetPixel
// -----------------------------------------------------------------------------------------------------------
video::SColor dbGetPixel( u32 imgID, s32 x, s32 y)
{
	video::IImage* img=dbGetImage(imgID);
	return video::Tool::getPixel( img, x, y );
}

// -----------------------------------------------------------------------------------------------------------
// dbGetPixelAlways
// -----------------------------------------------------------------------------------------------------------
video::SColor dbGetPixelAlways( u32 imgID, s32 x, s32 y)
{
	video::IImage* img=dbGetImage(imgID);
	return video::Tool::getPixelAlways( img, x, y );
}

// -----------------------------------------------------------------------------------------------------------
// dbCopy
// -----------------------------------------------------------------------------------------------------------
u32 dbCopyImage( u32 imgID )
{
	video::IImage* src = dbGetImage(imgID);
	video::IImage* dst = video::Tool::copyImage( src, core::recti( core::position2di(0,0), src->getDimension() ), video::ECP_ALL );
	return dbAddImage( 0, dst );
}

// -----------------------------------------------------------------------------------------------------------
// dbCut
// -----------------------------------------------------------------------------------------------------------
u32 dbCutImage( u32 imgID, s32 x, s32 y, s32 w, s32 h, bool blend)
{
	video::IImage* src=dbGetImage(imgID);
	if (!src)
		return 0;

	return 0;
}

// -----------------------------------------------------------------------------------------------------------
// dbPaste
// -----------------------------------------------------------------------------------------------------------
bool dbPasteImage( u32 dstID, u32 srcID, s32 x, s32 y, bool blend)
{
	video::IImage* src=dbGetImage(srcID);
	if (!src)
		return false;

	return true;
}

// -----------------------------------------------------------------------------------------------------------
// dbExtractColorChannel
// -----------------------------------------------------------------------------------------------------------
u32 dbExtractImageColorChannel( u32 imgID, video::E_COLOR_PLANE planes)
{
	return 0;
}

// -----------------------------------------------------------------------------------------------------------
// dbLine
// -----------------------------------------------------------------------------------------------------------
void dbDrawLine( u32 imgID, s32 x1, s32 y1, s32 x2, s32 y2, const video::SColor& color, bool blend)
{

}

// -----------------------------------------------------------------------------------------------------------
// dbLine
// -----------------------------------------------------------------------------------------------------------

void dbDrawLine( u32 imgID, s32 x1, s32 y1, s32 x2, s32 y2, const video::SColor& A, const video::SColor& B, bool blend)
{
}

// -----------------------------------------------------------------------------------------------------------
// dbRect
// -----------------------------------------------------------------------------------------------------------

void dbDrawRect( u32 imgID, s32 x1, s32 y1, s32 x2, s32 y2, const video::SColor& color, bool blend)
{
}

// -----------------------------------------------------------------------------------------------------------
// dbRect
// -----------------------------------------------------------------------------------------------------------

void dbDrawRect( u32 imgID, s32 x1, s32 y1, s32 x2, s32 y2, const video::SColor& A, const video::SColor& B, const video::SColor& C, const video::SColor& D, bool blend)
{
}

// -----------------------------------------------------------------------------------------------------------
// dbRect
// -----------------------------------------------------------------------------------------------------------

void dbDrawRect( u32 imgID, s32 x1, s32 y1, s32 x2, s32 y2, const video::SColor& color, s32 border, bool blend)
{
}

// -----------------------------------------------------------------------------------------------------------
// dbRect
// -----------------------------------------------------------------------------------------------------------

void dbDrawRect( u32 imgID, s32 x1, s32 y1, s32 x2, s32 y2, const video::SColor& A, const video::SColor& B, const video::SColor& C, const video::SColor& D, s32 border, bool blend)
{
}

// -----------------------------------------------------------------------------------------------------------
// dbBox
// -----------------------------------------------------------------------------------------------------------

void dbDrawBox( u32 imgID, s32 x1, s32 y1, s32 x2, s32 y2, const video::SColor& A, bool blend)
{

}

// -----------------------------------------------------------------------------------------------------------
// dbBox
// -----------------------------------------------------------------------------------------------------------

void dbBox( u32 imgID, s32 x1, s32 y1,	s32 x2, s32 y2,
	const video::SColor& A, const video::SColor& B, const video::SColor& C, const video::SColor& D,	bool blend)
{

}

// -----------------------------------------------------------------------------------------------------------
// dbCircle
// -----------------------------------------------------------------------------------------------------------

void dbCircle( u32 imgID, s32 x, s32 y, s32 radius, const video::SColor& color,	bool blend)
{

}

// -----------------------------------------------------------------------------------------------------------
// dbCircle
// -----------------------------------------------------------------------------------------------------------

void dbCircle( u32 imgID, s32 x, s32 y, s32 radius, const video::SColor& O, const video::SColor& I, bool blend)
{

}

// -----------------------------------------------------------------------------------------------------------
// dbEllipse
// -----------------------------------------------------------------------------------------------------------

void dbEllipse( u32 imgID, s32 x, s32 y, s32 rx, s32 ry, const video::SColor& color)
{

}

// -----------------------------------------------------------------------------------------------------------
// dbFlipH
// -----------------------------------------------------------------------------------------------------------

void dbFlipH( u32 imgID )
{

}

// -----------------------------------------------------------------------------------------------------------
// dbFlipV
// -----------------------------------------------------------------------------------------------------------

void dbFlipV( u32 imgID )
{
}

// -----------------------------------------------------------------------------------------------------------
// dbRotate180
// -----------------------------------------------------------------------------------------------------------

void dbRotate180( u32 imgID )
{
}


// -----------------------------------------------------------------------------------------------------------
// dbRotate90cw
// -----------------------------------------------------------------------------------------------------------

u32 dbRotate90cw( u32 imgID )
{
	return 0;
}

// -----------------------------------------------------------------------------------------------------------
// dbRotate90ccw
// -----------------------------------------------------------------------------------------------------------

u32 dbRotate90ccw( u32 imgID )
{
	return 0;
}

// -----------------------------------------------------------------------------------------------------------
// dbRotate90right
// -----------------------------------------------------------------------------------------------------------

u32 dbRotate90right( u32 imgID )
{
	return 0;
}

// -----------------------------------------------------------------------------------------------------------
// dbRotate90left
// -----------------------------------------------------------------------------------------------------------

u32 dbRotate90left( u32 imgID )
{
	return 0;
}

// -----------------------------------------------------------------------------------------------------------
// dbRotate
// -----------------------------------------------------------------------------------------------------------

u32 dbRotate( u32 imgID, f32 angle_ccw, const video::SColor& colorKey, bool sharpenOutline, s32 filter)
{
	return 0;
}

// -----------------------------------------------------------------------------------------------------------
// dbSkewH
// -----------------------------------------------------------------------------------------------------------

u32 dbSkewH( u32 imgID, f32 angle)
{
	return 0;
}

u32 dbSkewV( u32 imgID, f32 angle)
{
	return 0;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!
//!		IMAGE FILTER (c) 2008-2011 by BenjaminHampe@gmx.de
//!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
//	void dbImageFilter(video::IImage* src, video::E_COLOR_PLANE planes, video::E_IMAGE_FILTER choice)
//	{

//	}

//	void dbImageFilterSepia(video::IImage* src, video::E_COLOR_PLANE planes)
//	{
//	}
//
//	void dbImageFilterInvert(video::IImage* src, video::E_COLOR_PLANE planes)
//	{
//	}
//
//	void dbImageFilterBlackwhite(video::IImage* src, video::E_COLOR_PLANE planes)
//	{
//	}
//
//	void dbImageFilterAverage(video::IImage* src, video::E_COLOR_PLANE planes)
//	{
//	}
//
//	void dbImageFilterHDR(video::IImage* src, video::E_COLOR_PLANE planes)
//	{
//	}
//
//	void dbImageCorrectColors(video::IImage* src, video::E_COLOR_PLANE planes)
//	{
//	}

// -----------------------------------------------------------------------------------------------------------
// dbRepeat
// -----------------------------------------------------------------------------------------------------------

u32 dbRepeat( u32 imgID, u32 w, u32 h, f32 uRepeat, f32 vRepeat)
{
	return 0;
}

// -----------------------------------------------------------------------------------------------------------
// dbScale
// -----------------------------------------------------------------------------------------------------------

u32 dbScale( u32 imgID, u32 w, u32 h, u32 quality, video::E_COLOR_PLANE planes, bool sharpen, bool useColorKey, const video::SColor& colorkey)
{
	return 0;
}

//	// -----------------------------------------------------------------------------------------------------------
//	// dbScaleBicubic
//	// -----------------------------------------------------------------------------------------------------------
//
//	video::IImage* dbScaleBicubic( video::IImage* src, u32 w, u32 h, video::E_COLOR_PLANE planes,	bool sharpen, bool useColorKey, const video::SColor& colorkey = 0x00000000 )
//	{
//		video::IImage* img = 0;
//			if (!src) return img; // abort
//
//			// correct input, if nessecary
//		if (w<1) w=1;
//		if (h<1) h=1;
//
//			// get dst size
//			const u32 oldWidth = src->getDimension().Width;
//			const u32 oldHeight = src->getDimension().Height;
//
//			// compare sizes, abort if new and old size are equal with copy()
//			if ((oldWidth==w) && (oldHeight==h))
//					return dbCopy(src);
//
//			// create new dst 32bit ARGB, fill with zero
//		img = dbMakeImage(core::dimension2du(w, h), video::ECF_A8R8G8B8, SCOLOR_NULL);
//
//		// abort, if something went wrong
//		if (!img)
//					return img;
//
//			/// Zoom Faktoren, (zx = x'/x = w'/w), (zy = y'/y = h'/h)
//			const f32 zoomX = ((f32)w)/((f32)oldWidth);
//		const f32 zoomY = ((f32)h)/((f32)oldHeight);
//
//			for (u32 y=0; y<h; y++)
//			{
//					for (u32 x=0; x<w; x++)
//					{
//							f32 u=(f32)x/zoomX; // interpolate pos of current pixel in img to nearest of src
//							f32 v=(f32)y/zoomY; // interpolate pos of current pixel in img to nearest of src
//							video::SColor color = _bicubic_pixel(src,u,v,planes,useColorKey,colorkey);
//							dbSetPixel(img,x,y,color);
//					}
//			}
//		return img;
//	}
//


} // end namespace irr
