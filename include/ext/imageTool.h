// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_IMAGE_UTILS_H__
#define __IRR_EXT_IMAGE_UTILS_H__

#include <irrlicht.h>
#include <../../source/Irrlicht/os.h>
#include <../../source/Irrlicht/CColorConverter.h>
#include <../../source/Irrlicht/CImage.h>

/// maybe you need to include the following lines once to your main cpp file
//#include <../source/Irrlicht/os.cpp>
//#include <../source/Irrlicht/CColorConverter.cpp>
//#include <../source/Irrlicht/CImage.cpp>

/// IT_PRINT - variadic print macros
#if defined(_DEBUG) || defined(DEBUG)
	#define IT_PRINT( args...) \
	{ \
		printf( args ); \
	}
#else
	#define IT_PRINT( args... )
#endif

///  IT_ERROR - variadic print macros
#if defined(_DEBUG) || defined(DEBUG)
	#define IT_ERROR( args... ) \
	{ \
		printf( stderr, args ); \
		fprintf( stdout, args ); \
	}
#else
	#define IT_ERROR( args... ) \
	{ \
		fprintf( stderr, args ); \
	}
#endif

namespace irr
{

///@brief StringArray
typedef core::array<core::stringc> StringArray;

///@brief StringArrayW
//typedef core::array<core::Stringw> StringArrayW;

//! @brief video::PointList - Typedef list of 2d-points
typedef core::array<core::position2di> PointList;

//! @brief video::ImageList - Typedef list of 2d-points
typedef core::array<video::IImage*> ImageList;

/// colors included from DarkGDK_img
const static video::SColor transparent(0,0,0,0);
const static video::SColor white(255,255,255,255);
const static video::SColor black(255,0,0,0);
const static video::SColor grey32(255,32,32,32);
const static video::SColor grey64(255,64,64,64);
const static video::SColor grey96(255,96,96,96);
const static video::SColor grey128(255,128,128,128);
const static video::SColor grey160(255,160,160,160);
const static video::SColor grey192(255,192,192,192);
const static video::SColor grey224(255,224,224,224);
const static video::SColor red(255,255,0,0);
const static video::SColor green(255,0,255,0);
const static video::SColor blue(255,0,0,255);
const static video::SColor yellow(255,255,255,0);
const static video::SColor orange(255,255,127,0);
const static video::SColor violett(255,255,0,255);
const static video::SColor tuerkis(255,0,255,255);
const static video::SColor brown(255,255,255,127);
const static video::SColor light_red(255,255,200,200);
const static video::SColor light_green(255,200,255,200);
const static video::SColor light_blue(255,200,200,255);
const static video::SColor light_yellow(255,255,255,200);
const static video::SColor light_violett(255,255,200,255);
const static video::SColor light_tuerkis(255,200,255,255);
const static video::SColor light_brown(255,255,255,200);
const static video::SColor dark_red(255,127,0,0);
const static video::SColor dark_green(255,0,127,0);
const static video::SColor dark_blue(255,0,0,127);
const static video::SColor dark_yellow(255,127,127,0);
const static video::SColor dark_violett(255,127,0,127);
const static video::SColor dark_tuerkis(255,0,127,127);
const static video::SColor dark_brown(255,63,63,0);

namespace video
{

//! standard argb colors
//const SColor SC_Null(0,0,0,0);
//const SColor SC_Transparent = SC_Null;
//const SColor SC_Black(255,0,0,0);
//const SColor SC_White(255,255,255,255);
//const SColor SC_Opaque = SC_White;
//const SColor SC_HalfBlack(127,0,0,0);
//const SColor SC_HalfWhite(127,255,255,255);
//const SColor SC_GhostBlack(64,0,0,0);
//const SColor SC_GhostWhite(64,255,255,255);
//const SColor SC_LightRed(255,255,142,155);
//const SColor SC_DarkRed(255,155,50,50);
//const SColor SC_Red(255,255,0,0);
//const SColor SC_LightGreen(255,107,142,35);
//const SColor SC_DarkGreen(255,0,100,0);
//const SColor SC_Green(255,0,255,0);
//const SColor SC_LightBlue(255,120,173,209);
//const SColor SC_DarkBlue(255,70,130,180);
//const SColor SC_Blue(255,0,0,255);
//const SColor SC_Violett(255,255,0,255);
//const SColor SC_Marin(255,155,200,255);
//const SColor SC_Yellow(255,255,255,0);
//const SColor SC_Orange(255,255,127,30);
//const SColor SC_HL2(255,255,127,30);
//const SColor SC_Sky(255,255,127,30);
//const SColor SC_Sun(255,255,127,30);
//const SColor SC_Venus(255,255,127,30);
//const SColor SC_Moon(255,255,127,30);
//const SColor SC_Mars(255,255,127,30);
//const SColor SC_Saturn(255,255,127,30);


/// video::SFont
struct SFont
{
	core::stringc FileName;
	s32 Size;
	bool IsMonochrom;
	bool IsTransparent;
};

///@brief SText
struct SText
{
	gui::IGUIFont* Font;
	core::stringw Text;
	core::recti Position;
	video::SColor FGColor;
	video::SColor BGColor;
};

///@brief STexAtlas
struct STexAtlas
{
	video::IVideoDriver* Driver;
	video::IImage* Image;
	video::ITexture* Texture;
	core::dimension2du TileCount;
	core::dimension2du TileSize;

	STexAtlas( video::IVideoDriver* driver )
		: Driver(driver), Image(0), Texture(0), TileCount(0,0), TileSize(0,0)
	{}
};

enum E_IMAGE_FILTER
{	EIF_SHARPEN=0, EIF_SMOOTHEN, EIF_BLUR, EIF_MEAN_REMOVAL,
	EIF_EMBOSS, EIF_EMBOSS_ALL, EIF_EMBOSS_LOSSY, EIF_EMBOSS_H, EIF_EMBOSS_V,
    EIF_EDGE_DETECT, EIF_SEPIA, EIF_INVERT, EIF_BLACKWHITE, EIF_GREYSCALES,
	EIF_AVERAGE, EIF_HDR, EIF_SATURATE, EIF_COUNT
};

const char* const E_IMAGE_FILTER_STRINGS[] =
{
    "EIF_SHARPEN", "EIF_SMOOTHEN", "EIF_BLUR", "EIF_MEAN_REMOVAL", "EIF_EMBOSS",
    "EIF_EMBOSS_ALL", "EIF_EMBOSS_LOSSY", "EIF_EMBOSS_H", "EIF_EMBOSS_V",
    "EIF_EDGE_DETECT", "EIF_SEPIA","EIF_INVERT", "EIF_BLACKWHITE", "EIF_GREYSCALES",
    "EIF_AVERAGE", "EIF_HDR", "EIF_SATURATE", "EIF_COUNT"
};

enum E_IMAGE_SCALE_QUALITY
{	EISQ_BILINEAR_FAST=0, EISQ_NEAREST, EISQ_BILINEAR,  EISQ_BICUBIQ, EISQ_COUNT
};

/// @class CImageFilter<T>

template <class T>
class CImageFilter : public IReferenceCounted
{
public:
	explicit CImageFilter(
		T e00=T(0), T e01=T(0), T e02=T(0),
		T e10=T(0), T e11=T(1), T e12=T(0),
		T e20=T(0), T e21=T(0), T e22=T(0),
		T factor=T(1),
		T offset=T(0)) // default constructor
	{
		this->pixels[0][0]=e00;
		this->pixels[0][1]=e01;
		this->pixels[0][2]=e02;
		this->pixels[1][0]=e10;
		this->pixels[1][1]=e11;
		this->pixels[1][2]=e12;
		this->pixels[2][0]=e20;
		this->pixels[2][1]=e21;
		this->pixels[2][2]=e22;
		if (factor==T(0))
			factor=T(1);
		this->factor=factor;
		this->offset=offset;
	}

	T get(s32 index)
	{
		index = index%9;
		s32 col = index%3;
		s32 row = (index-col)/3;
		return (pixels[row][col]/factor) + offset;
	}

	T get(s32 row, s32 col)
	{
		if (row<0) row=0; if (row>2) row=2;
		if (col<0) col=0; if (col>2) col=2;
		return (T)(((f32)pixels[row][col]/(f32)factor) + (f32)offset);
	}
public:
	// (matrix / factor) + offset
	T pixels[3][3]; // pixels weight matrix3x3
	T factor;		  // factor
	T offset;		  // offset
};

template <class T> class CImageFilterSharpen : public CImageFilter<T>{public:CImageFilterSharpen():CImageFilter<T>(0,-2,0,-2,11,-2,0,-2,0,3,0){}};
template <class T> class CImageFilterSmoothing : public CImageFilter<T>{public:CImageFilterSmoothing():CImageFilter<T>(1,1,1,1,1,1,1,1,1,9,0){}};
template <class T> class CImageFilterGaussianBlur : public CImageFilter<T>{public:CImageFilterGaussianBlur():CImageFilter<T>(1,2,1,2,4,2,1,2,1,16,0){}};
template <class T> class CImageFilterMeanRemoval : public CImageFilter<T>{public:CImageFilterMeanRemoval():CImageFilter<T>(-1,-1,-1,-1,9,-1,-1,-1,-1,1,0){}};
template <class T> class CImageFilterEmboss : public CImageFilter<T>{public:CImageFilterEmboss():CImageFilter<T>(-1,0,-1,0,4,0,-1,0,-1,1,0){}};
template <class T> class CImageFilterEmbossAll : public CImageFilter<T>{public:CImageFilterEmbossAll():CImageFilter<T>(-1,-1,-1,-1,8,-1,-1,-1,-1,1,0){}};
template <class T> class CImageFilterEmbossLossy : public CImageFilter<T>{public:CImageFilterEmbossLossy():CImageFilter<T>(1,-2,1,-2,4,-2,-2,1,-2,1,127){}};
template <class T> class CImageFilterEmbossH : public CImageFilter<T>{public:CImageFilterEmbossH():CImageFilter<T>(0,0,0,-1,2,-1,0,0,0,1,127){}};
template <class T> class CImageFilterEmbossV : public CImageFilter<T>{public:CImageFilterEmbossV():CImageFilter<T>(0,-1,0,0,0,0,0,1,0,1,127){}};
template <class T> class CImageFilterEdgeDetect : public CImageFilter<T>{public:CImageFilterEdgeDetect():CImageFilter<T>(1,1,1,0,0,0,-1,-1,-1,1,0){}};

typedef CImageFilterSharpen<f32> CImageFilterSharpenf;
typedef CImageFilterSmoothing<f32> CImageFilterSmoothingf;
typedef CImageFilterGaussianBlur<f32> CImageFilterGaussianBlurf;
typedef CImageFilterMeanRemoval<f32> CImageFilterMeanRemovalf;
typedef CImageFilterEmboss<f32> CImageFilterEmbossf;
typedef CImageFilterEmbossAll<f32> CImageFilterEmbossAllf;
typedef CImageFilterEmbossLossy<f32> CImageFilterEmbossLossyf;
typedef CImageFilterEmbossH<f32> CImageFilterEmbossHf;
typedef CImageFilterEmbossV<f32> CImageFilterEmbossVf;
typedef CImageFilterEdgeDetect<f32> CImageFilterEdgeDetectf;

/// video::Tool - irrlicht image extensions

class Tool
{
public:

/// +++ analyze +++

//! @return analyzationResult image from input-image
static IImage* analyze( IImage* src);

/// +++ get size +++

static u32 getWidth( IImage* src );
static u32 getHeight( IImage* src );

/// +++ delete +++

static bool deleteImage( IImage* src );
static bool drop( IImage* src );

/// +++ create +++

static IImage* createImage( const core::dimension2du& size, const SColor& color = 0xffffffff, ECOLOR_FORMAT format = ECF_A8R8G8B8 );
static IImage* createImage( u32 w, u32 h, const SColor& color = 0xffffffff, ECOLOR_FORMAT format = ECF_A8R8G8B8 );
static IImage* createImage( const core::dimension2du& size, ECOLOR_FORMAT format);
static IImage* createCircleBrush( f32 radius, const SColor& outerColor, const SColor& innerColor, ECOLOR_FORMAT format);
static IImage* createImageFromTexture( IVideoDriver* driver, ITexture* src);

static ITexture* createTexture( IVideoDriver* driver, IImage* src );

/// +++ copy +++

static IImage* copyImage( IImage* src, const core::recti& area, E_COLOR_PLANE planes );

/// +++ clone +++

static IImage* cloneImage( IImage* src );

/// +++ load and save +++

static IImage* loadImage( IVideoDriver* driver, const io::path& filename );
static bool saveImage( IVideoDriver* driver, IImage* src, const io::path& filename );
static IImage* load( IVideoDriver* driver, const io::path& filename );
static bool save( IVideoDriver* driver, IImage* src, const io::path& filename, u32 compressValue );

/// +++ unique colors +++

static u32 getUniqueColorCount( IImage* src, E_COLOR_PLANE planes);
static core::array< SColor > getUniqueColorArray( IImage* src, E_COLOR_PLANE planes);

/// +++ extract color planes +++

static IImage* extract( IImage* src, E_COLOR_PLANE srcPlanes, E_COLOR_PLANE dstPlanes );
//
//	//! ARGB
//	inline u32 dbARGB(u8 a, u8 r, u8 g, u8 b)	{ return ((a<<24) | (r<<16) | (g<<8) | b);	}
//	//! RGB
//	inline u32 dbARGB(u8 r, u8 g, u8 b){ return (0xFF000000 | (r<<16) | (g<<8) | b); }
//	//! lösche A und setze A neu
//	inline u32 dbARGB_setA(u32 color, u8 a){ return ( (color&0x00FFFFFF) | (a<<24) ); }
//	//! lösche A und setze A=255
//	inline u32 dbARGB_setOpaque(u32 color){ return color|0xFF000000; }
//	//! lösche A und setze A=255
//	inline u32 dbARGB_ghostOff(u32 color){ return color|0xFF000000; }
//	//! lösche A und setze A=128
//	inline u32 dbARGB_ghostOn(u32 color){ return  color|0x8000000; }
//	//! lösche A und setze A=0
//	inline u32 dbARGB_setTransparent(u32 color){ return color&0x00FFFFFF; }
//	//! lösche R und setze R neu
//	inline u32 dbARGB_setR(u32 color, u8 r){ return ((color&0xFF00FFFF) | (r<<16) ); }
//	//! lösche G und setze G neu
//	inline u32 dbARGB_setG(u32 color, u8 g){ return ((color&0xFFFF00FF) | (g<<8) ); }
//	//! lösche B und setze B neu
//	inline u32 dbARGB_setB(u32 color, u8 b) {	return ((color&0xFFFFFF00) | b); }
//	//! lösche RGB und setze RGB neu
//	inline u32 dbARGB_setRGB(u32 color, u32 rgb) { return ((color&0xFF000000)|(rgb&0x00FFFFFF)); }
//	//! extract A component
//	inline u8 dbARGB_A(u32 color) { return (u8)(color>>24); }
//	//! extract A component
//	inline u8 dbARGB_R(u32 color) { return (u8)(color>>16);	}
//	//! extract A component
//	inline u8 dbARGB_G(u32 color) { return (u8)(color>>8); }
//	//! extract A component
//	inline u8 dbARGB_B(u32 color) { return (u8)color; }
///// manage texture-atlas

///@brief Create texture-atlas
static bool createAtlas( STexAtlas& atlas,
	const core::dimension2du& tileCount = core::dimension2du( 5, 5),
	const core::dimension2du& tileSize = core::dimension2du( 128, 128 ) );

///@brief Set tile of texture-atlas at 2d coords (ix,iy)
static bool setAtlasTile( STexAtlas& atlas, IImage* src, u32 index_x, u32 index_y );

///@brief Update texture-atlas
static bool updateAtlas( STexAtlas& atlas );

///@brief Delete texture-atlas
static bool deleteAtlas( STexAtlas& atlas );

/// manage ImageList

/////@brief load ImageList from text-file
//static ImageList loadImageList( IVideoDriver* driver, const io::path& fileName, io::IFileList* inputList = 0 );
//
/////@brief save ImageList to text-file
//static StringArray getFileList( const ImageList& imageList );
//
/////@brief save ImageList to text-file
//static ImageList getImageList( IVideoDriver* driver, const StringArray& fileList );
//
/////@brief load ImageList from text-file
//static ImageList getImageList( IVideoDriver* driver, io::IFileList* fileList = 0 );
//
/////@brief save ImageList to text-file
//static bool saveImageList( IVideoDriver* driver, const io::path& fileName, const ImageList& imageList );
//
/////@brief delete ImageList
//static bool deleteImageList( ImageList& imageList );

// static IImage* createTexAtlas( u32 tile_w, u32 tile_h, u32 cols, u32 rows, const core::array<IImage*>& data );



/// +++ fill +++




//! @author BenjaminHampe@gmx.de
//! @brief fill user defined color-planes with color-planes from another image or blend together
//! @param image to copy color-planes (all pixels involed) from
//! @param image to copy color-planes (all pixels involed) from
//! @param signed 32bit y-coord
static void fill( IImage* dst, const SColor& color, E_COLOR_PLANE planes, bool blend);

//! @brief MS Paint Style floodFill-Can
static bool floodFill( IImage* img, s32 x, s32 y, const SColor& fillcolor, const SColor& old);

/// +++ Rainbow +++

//! Wavelength in nanometer to SColor ( valid range λ ∈ [380, 780] nm )
//! which are the visible colors for human eyes (blue to red)
//! uses algorithm from Bruton ( linear approx of CIE color system )
static SColor getLightWaveColor( f64 lambda = 380.0f /* upper blue end*/, f64 gamma = 1.0);

//! Wavelength in nanometer to SColor ( valid range λ ∈ [380, 780] nm )
//! which are the visible colors for human eyes (blue to red)
//! uses algorithm from Bruton ( linear approx of CIE color system )
static SColor getRainbowColor( u32 i = 0, u32 count = 64, f64 gamma = 1.0);

//! does not need the driver, but the path to class CImage!!!
//! the height actually contains all different values, w cols are just copies
//! but driver may only support spare textures
static IImage* createRainbowImage( u32 w = 4, u32 h = 64, u8 transparency = 127, f64 gamma = 1.0);

//! if driver 0, it uses the null device
static ITexture* createRainbowTexture( IVideoDriver* driver = 0, u32 w = 64, u32 h = 64, u8 transparency = 127, f64 gamma = 1.0);



/// +++ Drawing stuff +++



/// create precalculated point-collections for faster drawing
//! @brief Create list/array of 2d points
static PointList traverseLine( const core::position2di& A, const core::position2di& B );

//! @brief Create list/array of 2d points
static PointList traverseCircle( const core::position2di& center, s32 radius );

//! @brief Create list/array of 2d points
static PointList traverseEllipse( const core::position2di& center, s32 rx, s32 ry );

//! @brief set pixel for signed integer coords only if inside (0,0,w,h)
static void drawPixel( IImage* img, s32 x, s32 y, const SColor& color, bool blend = false );

//! @brief set pixel for signed integer coords always - simple border align
static void drawPixelAlways( IImage* img, s32 x, s32 y, const SColor& color, bool blend = false );

//! @brief get pixel from signed integer coords only if inside (0,0,w,h) else SColor(0,0,0,0)
static SColor getPixel( IImage* img, s32 x, s32 y );

//! @brief get pixel from signed integer coords (always)
static SColor getPixelAlways( IImage* img, s32 x, s32 y );

//! @brief blit/fast software-image drawing
static void drawImage( IImage* src, IImage* dst, const core::position2di& pos, const core::dimension2du& size, bool bTransparent = false, bool blend = false);



/// +++  Shape Drawing +++


//! @brief draw fast bresenham-line with 1 color to software-image
//! @return true if success
static bool drawLine( IImage* dst, s32 x0, s32 y0, s32 x1, s32 y1, const SColor& color, bool blend = false);
static bool drawLine( IImage* dst, s32 x0, s32 y0, s32 x1, s32 y1, const SColor& color_a, const SColor& color_b, bool blend = false);
static bool drawLine( IImage* dst, const core::rectf& pos, const SColor& color, bool blend = false);
static bool drawLine( IImage* dst, const core::rectf& pos, const SColor& color_a, const SColor& color_b, bool blend = false);

//! @brief draw fast bresenham-rect with 1 color to software-image
//! @return true if success
//! @details if ( border <= 0 ) solid/filled else (border>0) outlined/border
static void drawRect( IImage* dst, const core::recti& pos, const SColor& color, s32 border = 0, bool blend = false);
static void drawRect( IImage* dst, const core::recti& pos, const SColor& bottomLeft, const SColor& topLeft, const SColor& topRight, const SColor& bottomRight, s32 border = 0, bool blend = false);

//! draw a Bresenham-round-rect, 1 color(s), filled (border=0) or outlined with border, option to blend
static void drawRoundRect( IImage* dst, const core::recti& pos, s32 rx, s32 ry, const SColor& color, s32 border = 0, bool blend = false);
static void drawRoundRect( IImage* dst, const core::recti& pos, s32 rx, s32 ry, const SColor& topLeft, const SColor& topRight, const SColor& bottomRight, const SColor& bottomLeft, s32 border = 0, bool blend = false);

//! Bresenham circle, 1 color(s), filled or outlined, option to blend
static void drawCircle( IImage* dst, const core::position2di& center, s32 radius, const SColor& color, s32 border = 0, bool blend = false);
//void drawCircle( IImage* dst, const core::position2di& center, s32 radius, const SColor& c1, const SColor& c2, s32 border, bool blend);

//! Bresenham ellipse, 1 color(s), filled or outlined, option to blend
static void drawEllipse( IImage* dst, const core::position2di& center, s32 rx, s32 ry, const SColor& color, s32 border = 0, bool blend = false);
static void drawEllipse( IImage* dst, const core::position2di& center, s32 rx, s32 ry, const SColor& c1, const SColor& c2, s32 border = 0, bool blend = false);



/// +++ Text Drawing +++


//! irrlicht API conform
//! uses Environment->getVideoDriver() to create a renderTarget
//! + filtering when possible )
//! uses IGUIEnvironment and its IVideoDriver
//! create image from text ( always centered ) with minimal size for text
//! can be used in combination with IGUITTFont to load truetype-fonts of any size
static IImage* createImageFromText( gui::IGUIEnvironment* env, gui::IGUIFont* font, const core::stringw& txt, const SColor& fg_color = 0xffffffff, const SColor& bg_color = SColor(0,0,0,0) );

//! irrlicht API conform
//! draw text to image ( must already exist )
//! create temporary image with text and draw it into given image
//! with 2d-coords and 2d-alignment ( -1=left/top, 0=center/middle, 1=right/bottom )
//! can be used in combination with IGUITTFont to load truetype-fonts of any size
//! if (!dst) return false; -> no valid image surface to draw to
//! if (!env) return false; -> no irrlicht-factories available
//! if (!font) fallback to Environment->getSkin()->getFont( EGDF_DEFAULT );
//! if still (!font) fallback to Environment->getBuildInFont();
//! if still (!font) return false;
static bool drawText( IImage* dst, gui::IGUIEnvironment* env, gui::IGUIFont* font, const core::stringw& txt, s32 x, s32 y, s32 hAlign = -1, s32 vAlign = -1, const SColor& txt_color = 0xffffffff, const SColor& background_color = SColor(0,0,0,0), core::recti* clipRect = 0, bool blend = true);

#ifdef _IRR_COMPILE_WITH_FREETYPE2_

//! draw Glyph to image
static void drawBitmapFT(	IImage* dst,	FT_Bitmap* bitmap,	s32 x, s32 y, const video::SColor& txt_color = 0xffffffff );

//! create image from text ( always centered ) with minimal size for text
//! using freetype2 library and no irrlicht-device
static IImage* createImageFromText( SFont* font, const core::stringw& txt, const SColor& txt_color = 0xffffffff, const SColor& background_color = 0x00000000 );

//! draw text to existing software image
//! using freetype2 library and no irrlicht-device
//! text is aligned at borders ( -1=left/top, 0=center/middle, 1=right/bottom )
static bool drawText( SFont* font, IImage* dst, const core::stringw& txt, s32 x, s32 y, s32 hAlign = -1, s32 vAlign = -1,
	const SColor& txt_color = 0xffffffff, const SColor& background_color = SColor(0,0,0,0), core::recti* clipRect = 0, bool blend = true );

#endif // _IRR_COMPILE_WITH_FREETYPE2_



/// +++ Filter +++

static IImage* filter( IImage* dst, video::E_IMAGE_FILTER myFilter, u32 param);
static IImage* filter( IImage* src, video::CImageFilter<f32>* filter, bool deleteFilter );
static IImage* sepia( IImage* src );
static IImage* invert( IImage* src, E_COLOR_PLANE planes );
static IImage* blackwhite( IImage* src, u32 threshold );
static IImage* greyscales( IImage* src );
static IImage* average( IImage* src );
static IImage* hdr( IImage* src, u32 threshold );
static IImage* saturate( IImage* src );
static IImage* sharpen( IImage* src, f32 value );

/// +++ Repeat +++

//! @author BenjaminHampe@gmx.de
//! @brief repeatImage
//! @param image to copy color-planes (all pixels involed) from
//! @param image to copy color-planes (all pixels involed) from
//! @param signed 32bit y-coord
static IImage* repeatImage( IImage* src, f32 u, f32 v );


/// +++ Rotate +++

static bool flipH( IImage* dst );
static bool flipV( IImage* dst );
static bool rotate180( IImage* dst );
static IImage* rotateLeft( IImage* src );
static IImage* rotateRight( IImage* src );
static IImage* rotate( IImage* src, f32 angleDegreesCCW, SColor* colorKey = 0);

/// +++ Resize and Scaling +++

enum E_IMAGE_SCALE_OPERATION
{
	EISO_FAST=0,
	EISO_NEAREST,
	EISO_BILINEAR,
	EISO_BICUBIC,
	EISO_COUNT,
	EISO_UNKNOWN
};

static SColor getNearestPixel( IImage* src, f32 fx, f32 fy );
static SColor getBilinearPixelFast( IImage* src, f32 fx, f32 fy );
static SColor getBilinearPixel( IImage* src, f32 fx, f32 fy, E_COLOR_PLANE planes, SColor* colorKey);
static f32 getBicubicFactor(const f32& arg);
static SColor getBicubicPixel( IImage* src, f32 fx, f32 fy, E_COLOR_PLANE planes, SColor* colorKey);
static IImage* resize( IImage* src, const core::dimension2du& newSize, s32 scaleOp, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen);
static IImage* resizeNearest( IImage* src, const core::dimension2du& newSize, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen);
static IImage* resizeFast( IImage* src, const core::dimension2du& newSize, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen );
static IImage* resizeBilinear( IImage* src, const core::dimension2du& newSize, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen);
static IImage* resizeBicubic( IImage* src, const core::dimension2du& newSize, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen);
static IImage* scale( IImage* src, const core::vector2df& scaleXY, s32 scaleOp, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen);
static IImage* scaleNearest( IImage* src, const core::vector2df& scaleXY, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen);
static IImage* scaleFast( IImage* src, const core::vector2df& scaleXY, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen);
static IImage* scaleBilinear( IImage* src, const core::vector2df& scaleXY, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen);
static IImage* scaleBicubic( IImage* src, const core::vector2df& scaleXY, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen);

}; // end class Tool

} // end namespace video

} // end namespace irr




#endif // __IRR_EXT_DRAW_BRESENHAM_LINE_TO_SOFTWARE_IMAGE_H__
