#ifndef __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_IMAGE_H__
#define __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_IMAGE_H__

#include <irrlicht.h>

#include <imageTool.h>

namespace irr
{
//	const static video::SColor transparent(0,0,0,0);
//	const static video::SColor white(255,255,255,255);
//	const static video::SColor black(255,0,0,0);
//	const static video::SColor grey32(255,32,32,32);
//	const static video::SColor grey64(255,64,64,64);
//	const static video::SColor grey96(255,96,96,96);
//	const static video::SColor grey128(255,128,128,128);
//	const static video::SColor grey160(255,160,160,160);
//	const static video::SColor grey192(255,192,192,192);
//	const static video::SColor grey224(255,224,224,224);
//	const static video::SColor red(255,255,0,0);
//	const static video::SColor green(255,0,255,0);
//	const static video::SColor blue(255,0,0,255);
//	const static video::SColor yellow(255,255,255,0);
//	const static video::SColor orange(255,255,127,0);
//	const static video::SColor violett(255,255,0,255);
//	const static video::SColor tuerkis(255,0,255,255);
//	const static video::SColor brown(255,255,255,127);
//	const static video::SColor light_red(255,255,200,200);
//	const static video::SColor light_green(255,200,255,200);
//	const static video::SColor light_blue(255,200,200,255);
//	const static video::SColor light_yellow(255,255,255,200);
//	const static video::SColor light_violett(255,255,200,255);
//	const static video::SColor light_tuerkis(255,200,255,255);
//	const static video::SColor light_brown(255,255,255,200);
//	const static video::SColor dark_red(255,127,0,0);
//	const static video::SColor dark_green(255,0,127,0);
//	const static video::SColor dark_blue(255,0,0,127);
//	const static video::SColor dark_yellow(255,127,127,0);
//	const static video::SColor dark_violett(255,127,0,127);
//	const static video::SColor dark_tuerkis(255,0,127,127);
//	const static video::SColor dark_brown(255,63,63,0);

	/// dbARGB
	u32 dbARGB(u8 a, u8 r, u8 g, u8 b);

	/// dbRGB
	u32 dbARGB(u8 r, u8 g, u8 b);

	/// dbARGB_setA
	u32 dbARGB_setA(u32 color, u8 a);

	/// dbARGB_setOpaque
	u32 dbARGB_setOpaque(u32 color);

	/// dbARGB_ghostOff
	u32 dbARGB_ghostOff(u32 color);

	/// dbARGB_ghostOn
	u32 dbARGB_ghostOn(u32 color);

	/// dbARGB_setTransparent
	u32 dbARGB_setTransparent(u32 color);

	/// dbARGB_setR
	u32 dbARGB_setR(u32 color, u8 r);

	/// dbARGB_setG
	u32 dbARGB_setG(u32 color, u8 g);

	/// dbARGB_setB
	u32 dbARGB_setB(u32 color, u8 b);

	/// dbARGB_setRGB
	u32 dbARGB_setRGB(u32 color, u32 rgb);

	/// dbARGB_A
	u8 dbARGB_A(u32 color);

	/// dbARGB_R
	u8 dbARGB_R(u32 color);

	/// dbARGB_G
	u8 dbARGB_G(u32 color);

	/// dbARGB_B
	u8 dbARGB_B(u32 color);

	/// dbGetFreeImageID
	u32 dbFreeImage( u32 imgID = 1 );

	/// dbImageExist
	bool dbImageExist( u32 imgID );

	/// dbDeleteImage
	bool dbDeleteImage( u32 imgID );

	/// dbAddImage
	u32 dbAddImage( u32 imgID, video::IImage* img );

	/// dbAddTexture
	u32 dbAddTexture( u32 imgID, video::ITexture* tex ); //, const io::path& fileName = _IRR_TEXT("") );

	/// dbGetImage
	video::IImage* dbGetImage( u32 imgID );

	/// dbGetTexture
	video::ITexture* dbGetTexture( u32 imgID );

	///@brief Return internal array-index for ObjectID
	u32 dbGetImageArrayIndex( u32 imgID );

	/// dbImageWidth
	u32 dbImageWidth( u32 imgID );

	/// dbImageHeight
	u32 dbImageHeight( u32 imgID );

	/// dbImageBits
	u32 dbImageBits( u32 imgID );

	/// dbImageFormat
	video::ECOLOR_FORMAT dbImageFormat( u32 imgID );

	/// dbImageFormatString
	core::stringc dbImageFormatString( u32 imgID );

	/// dbLoadImage
	bool dbLoadImage( u32 imgID, const io::path& fileName, u32 iFilter = 0 );

	/// dbSaveImage
	bool dbSaveImage( u32 imgID, const io::path& filename, u32 iFilter = 0);


	/// dbLockImage
	u8* dbLockImage( u32 imgID );

	/// dbUnlockImage
	void dbUnlockImage( u32 imgID );


	/// dbMakeImage
	bool dbMakeImage( u32 imgID, u32 w, u32 h, const video::SColor& fillColor = 0x00000000 );

	/// dbMakeMemblockFromImage
	bool dbMakeMemblockFromImage( u32 memID, u32 imgID );

	/// dbMakeImageFromMemblock
	bool dbMakeMemblockFromImage( u32 imgID, u32 memID );


	/// dbFill
	void dbFill( u32 imgID, const video::SColor& color);

	/// dbFill
	//void dbFill( u32 imgID, const video::SColor& color, video::E_COLOR_PLANE planes = video::ECP_ALL, core::recti* clipRect = 0);

	/// dbFloodfill
	bool dbFloodfill( u32 imgID, s32 x, s32 y, const video::SColor& fillcolor, const video::SColor& old);


	/// dbDrawPixel
	void dbDrawPixel( u32 imgID, s32 x, s32 y, const video::SColor& color, bool blend);

	/// dbDrawPixelAlways
	void dbDrawPixelAlways( u32 imgID, s32 x, s32 y, const video::SColor& color, bool blend);

	/// dbGetPixel
	video::SColor dbGetPixel( u32 imgID, s32 x, s32 y);

	/// dbGetPixelAlways
	video::SColor dbGetPixelAlways( u32 imgID, s32 x, s32 y);


	/// dbCopyImage
	u32 dbCopyImage( u32 imgID );

	/// dbCutImage
	u32 dbCutImage( u32 imgID, s32 x, s32 y, s32 w, s32 h, bool blend);

	/// dbPasteImage
	bool dbPasteImage( u32 dstID, u32 srcID, s32 x, s32 y, bool blend);


	/// dbExtractColorChannel
	u32 dbExtractImageColorChannel( u32 imgID, video::E_COLOR_PLANE planes = video::ECP_ALL);


	/// dbDrawLine
	void dbDrawLine( u32 imgID, s32 x1, s32 y1, s32 x2, s32 y2, const video::SColor& color, bool blend);

	/// dbDrawLine
	void dbDrawLine( u32 imgID, s32 x1, s32 y1, s32 x2, s32 y2, const video::SColor& A, const video::SColor& B, bool blend);

	/// dbDrawRect
	void dbDrawRect( u32 imgID, s32 x1, s32 y1, s32 x2, s32 y2, const video::SColor& color, bool blend);

	/// dbDrawRect
	void dbDrawRect( u32 imgID, s32 x1, s32 y1, s32 x2, s32 y2, const video::SColor& A, const video::SColor& B, const video::SColor& C, const video::SColor& D, bool blend);

	/// dbDrawRect
	void dbDrawRect( u32 imgID, s32 x1, s32 y1, s32 x2, s32 y2, const video::SColor& color, s32 border, bool blend);

	/// dbDrawRect
	void dbDrawRect( u32 imgID, s32 x1, s32 y1, s32 x2, s32 y2, const video::SColor& A, const video::SColor& B, const video::SColor& C, const video::SColor& D, s32 border, bool blend);

	/// dbDrawBox
	void dbDrawBox( u32 imgID, s32 x1, s32 y1, s32 x2, s32 y2, const video::SColor& A, bool blend);

	/// dbDrawBox
	void dbDrawBox( u32 imgID, s32 x1, s32 y1, s32 x2, s32 y2, const video::SColor& A, const video::SColor& B, const video::SColor& C, const video::SColor& D, bool blend);

	/// dbDrawCircle
	void dbDrawCircle( u32 imgID, s32 x, s32 y, s32 radius, const video::SColor& color, bool blend);

	/// dbDrawCircle
	void dbDrawCircle( u32 imgID, s32 x, s32 y, s32 radius, const video::SColor& O, const video::SColor& I, bool blend);

	/// dbDrawEllipse
	void dbDrawEllipse( u32 imgID, s32 x, s32 y, s32 rx, s32 ry, const video::SColor& color);

	/// dbFlipImageH
	void dbFlipImageH( u32 imgID );

	/// dbFlipImageV
	void dbFlipImageV( u32 imgID );


	/// dbRotateImage180
	void dbRotateImage180( u32 imgID );

	/// dbRotateImage90cw
	u32 dbRotateImage90cw( u32 imgID );

	/// dbRotateImage90ccw
	u32 dbRotateImage90ccw( u32 imgID );

	/// dbRotateImage90right
	u32 dbRotateImage90right( u32 imgID );

	/// dbRotateImage90left
	u32 dbRotateImage90left( u32 imgID );

	/// dbRotateImage
	u32 dbRotateImage( u32 imgID, f32 angle_ccw, const video::SColor& colorKey, bool sharpenOutline, u32 iFilter);

	/// dbBlendImage
	bool dbBlendImage( u32 srcID, u32 dstID, video::E_BLEND_FACTOR srcFactor, const core::recti& srcRect, video::E_BLEND_FACTOR dstFactor, const core::recti& dstRect, video::E_BLEND_OPERATION blendOperation, video::E_COLOR_PLANE planes = video::ECP_ALL );

	/// dbSkewImageH
	u32 dbSkewImageH( u32 imgID, f32 angle);

	/// dbSkewImageV
	u32 dbSkewImageV( u32 imgID, f32 angle);

	/// dbFilterImage
	bool dbFilterImage( u32 imgID, video::CImageFilter<f32>* filterMatrix);

//	void dbImageFilter(video::IImage* src, video::E_COLOR_PLANE planes, video::E_IMAGE_FILTER choice)
//
//	void dbImageFilter( video::IImage* src, CImageFilter<f32>* filterMatrix, video::E_COLOR_PLANE planes, bool deleteFilter)
//
//	void dbImageFilterSepia(video::IImage* src, video::E_COLOR_PLANE planes)
//
//	void dbImageFilterInvert(video::IImage* src, video::E_COLOR_PLANE planes)
//
//	void dbImageFilterBlackwhite(video::IImage* src, video::E_COLOR_PLANE planes)
//
//	void dbImageFilterAverage(video::IImage* src, video::E_COLOR_PLANE planes)
//
//	void dbImageFilterHDR(video::IImage* src, video::E_COLOR_PLANE planes)
//
//	void dbImageCorrectColors(video::IImage* src, video::E_COLOR_PLANE planes)

	// dbRepeatImage
	u32 dbRepeat( u32 imgID, u32 w, u32 h, f32 uRepeat, f32 vRepeat);

	/// dbScaleImage
	u32 dbScale( u32 imgID, u32 w, u32 h, u32 quality, video::E_COLOR_PLANE planes, bool sharpen, bool useColorKey, const video::SColor& colorkey);

	/// dbScaleImageNearest
	//u32 dbScaleNearest( u32 imgID, u32 w, u32 h, video::E_COLOR_PLANE planes, bool sharpen,	bool useColorKey, const video::SColor& colorkey);

	/// dbScaleImageFast
	//u32 dbScaleFast( u32 imgID, u32 w, u32 h, video::E_COLOR_PLANE planes, bool sharpen, bool useColorKey, const video::SColor& colorkey);

	/// dbScaleImageBilinear
	//u32 dbScaleBilinear( u32 imgID, u32 w, u32 h, video::E_COLOR_PLANE planes, bool sharpen, bool useColorKey, const video::SColor& colorkey);

	/// dbScaleImageBicubic
	//u32 dbScaleBicubic( u32 imgID, u32 w, u32 h, video::E_COLOR_PLANE planes,	bool sharpen, bool useColorKey, const video::SColor& colorkey = 0x00000000 );

	//bool MemblockReset(s32 mem, u32 color)
	//bool MemblockResetA(s32 mem, s32 a)
	//bool MemblockResetR(s32 mem, s32 r)
	//bool MemblockResetG(s32 mem, s32 g)
	//bool MemblockResetB(s32 mem, s32 b)

	//int MemblockCountColors(s32 mem)
	//int MemblockCountAColors(s32 mem)
	//int MemblockCountRColors(s32 mem)
	//int MemblockCountGColors(s32 mem)
	//int MemblockCountBColors(s32 mem)

	//bool MemblockInvert(s32 mem)
	//bool MemblockInvertR(s32 mem)
	//bool MemblockInvertG(s32 mem)
	//bool MemblockInvertB(s32 mem)
	//bool MemblockInvertA(s32 mem)

	//s32 MemblockGetAMin(s32 mem)
	//s32 MemblockGetAMax(s32 mem)
	//s32 MemblockGetRMin(s32 mem)
	//s32 MemblockGetRMax(s32 mem)
	//s32 MemblockGetGMin(s32 mem)
	//s32 MemblockGetGMax(s32 mem)
	//s32 MemblockGetBMin(s32 mem)
	//s32 MemblockGetBMax(s32 mem)


} // end namespace irr

#endif // __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_IMAGE_H__
