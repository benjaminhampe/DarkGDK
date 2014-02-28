// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include <imageTool.h>

namespace irr
{

namespace video
{

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
bool Tool::drawText(
	IImage* dst, gui::IGUIEnvironment* env, gui::IGUIFont* font,
	const core::stringw& txt,
	s32 x, s32 y, s32 hAlign, s32 vAlign,
	const SColor& txt_color,
	const SColor& background_color,
	core::recti* clipRect, bool blend)

{
	#ifdef _DEBUG
	printf( "video::Tool::drawText()\n" );
	#endif // _DEBUG

	if (!dst)
	{
		#ifdef _DEBUG
		printf(  "video::Tool::drawText() - Invalid pointer to IImage\n" );
		#endif // _DEBUG
		return false;
	}

	if (!env)
	{
		#ifdef _DEBUG
		printf(  "video::Tool::drawText() - Invalid pointer to IGUIEnvironment\n" );
		#endif // _DEBUG
		return false;
	}

	const core::dimension2du& dst_size = dst->getDimension();

	if (x>=(s32)dst_size.Width)
	{
		#ifdef _DEBUG
		printf(  "video::Tool::drawText() - Cant draw outside destination Image ( x coord too big )\n");
		#endif // _DEBUG
		return false;
	}

	if (y>=(s32)dst_size.Height)
	{
		#ifdef _DEBUG
		printf(  "video::Tool::drawText() - Cant draw outside destination Image ( y coord too big )\n");
		#endif // _DEBUG
		return false;
	}

	IImage* img = createImageFromText( env, font, txt, txt_color, background_color );
	if (!img)
	{
		#ifdef _DEBUG
		printf(  "video::Tool::drawText() - Could not create image\n" );
		#endif // _DEBUG
		return false;
	}

	const core::dimension2du& txt_size = img->getDimension();

	IVideoDriver* driver = env->getVideoDriver();

	if (!driver)
	{
		#ifdef _DEBUG
		printf(  "video::Tool::drawText() - Invalid pointer to IVideoDriver\n" );
		#endif // _DEBUG
		return false;
	}

	/// h alignment
	if (hAlign == 0)
	{
		x -= (s32)(txt_size.Width>>1);
	}
	else if (hAlign > 0 )
	{
		x -= (s32)(txt_size.Width);
	}

	/// v alignment
	if (vAlign == 0)
	{
		y -= (s32)(txt_size.Height>>1);
	}
	else if (vAlign > 0 )
	{
		y -= (s32)(txt_size.Height);
	}

	/// actual text-drawing
	// loop all pixels of text-image, skip operation when outside dst-bound
	// or skip when txt-pixel is 0 == SColor(0,0,0,0)
	for (u32 j=0; j<txt_size.Height; j++)
	{
		for (u32 i=0; i<txt_size.Width; i++)
		{
			const SColor& pixel = img->getPixel(i,j);
			if (pixel.color != 0)
			{
				s32 dx = x+(s32)i;
				s32 dy = y+(s32)j;
				drawPixel( dst, dx,dy, pixel, true );
			}
		}
	}

	/// debug-drawing
	#ifdef _DEBUG
	drawRect( dst,
		core::recti( x-1, y-1, x+txt_size.Width+1, y+txt_size.Height+1 ),
		SColor(255,255,0,0),
		1,
		false);
	#endif // _DEBUG

	return true;
}

//! irrlicht API conform
//! uses Environment->getVideoDriver() to create a renderTarget
//! + filtering when possible )
//! uses IGUIEnvironment and its IVideoDriver
//! create image from text ( always centered ) with minimal size for text
//! can be used in combination with IGUITTFont to load truetype-fonts of any size

IImage*	Tool::createImageFromText(
	gui::IGUIEnvironment* env, gui::IGUIFont* font,
	const core::stringw& txt, const SColor& txt_color,
	const SColor& background_color )
{
	if (!env)
	{
		#ifdef _DEBUG
		printf(  "createImageFromText() - Invalid pointer to IVideoDriver\n" );
		#endif // _DEBUG
		return 0;
	}

	if (!font)
	{
		#ifdef _DEBUG
		printf(  "createImageFromText() - Invalid pointer to IGUIFont, 1. fallback\n" );
		#endif // _DEBUG
		gui::IGUISkin* skin  = env->getSkin();
		if (skin)
			font = skin->getFont( gui::EGDF_DEFAULT );
	}

	if (!font)
	{
		#ifdef _DEBUG
		printf(  "createImageFromText() - Invalid pointer to IGUIFont, 2. fallback\n" );
		#endif // _DEBUG
		font = env->getBuiltInFont();
	}

	if (!font)
	{
		#ifdef _DEBUG
		printf(  "createImageFromText() - Invalid pointer to IGUIFont, abort\n" );
		#endif // _DEBUG
		return 0;
	}

	IVideoDriver* driver = env->getVideoDriver();

	if (!driver)
	{
		#ifdef _DEBUG
		printf(  "createImageFromText() - Invalid pointer to IVideoDriver, abort\n" );
		#endif // _DEBUG
		return 0;
	}

	core::dimension2du txt_size = font->getDimension( txt.c_str() );

	if ( (txt_size.Width == 0) || (txt_size.Height == 0) )
	{
		#ifdef _DEBUG
		printf(  "createImageFromText() - Invalid image size\n" );
		#endif // _DEBUG
		return 0;
	}

	core::dimension2du tex_size = txt_size;

	u32 max_tex_size = core::min_<u32>( driver->getMaxTextureSize().Width, driver->getMaxTextureSize().Height );

	tex_size.getOptimalSize(
		!driver->queryFeature( EVDF_TEXTURE_NPOT ),
		!driver->queryFeature( EVDF_TEXTURE_NSQUARE ),
		true, max_tex_size );

	IImage* raw = 0;

	if ( driver->queryFeature( EVDF_RENDER_TO_TARGET ) )
	{
		ITexture* rtt = driver->addRenderTargetTexture( tex_size, "textRTT", ECF_A8R8G8B8 );
		if (rtt)
		{
			if (driver->setRenderTarget( rtt, true, true, background_color ))
			{
				font->draw( txt, core::recti(core::position2di(0,0), txt_size), txt_color, false, false, 0);

				driver->setRenderTarget( 0 );

				raw = driver->createImage(rtt, core::position2di(0,0), txt_size );

				if (!raw)
				{
					#ifdef _DEBUG
					printf(  "createImageFromText() - Could not create Image from RenderTexture\n" );
					#endif // _DEBUG
					return 0;
				}

				driver->removeTexture( rtt );
			}
			else
			{
				#ifdef _DEBUG
				printf(  "createImageFromText() - Could not set RenderTargetTexture\n" );
				#endif // _DEBUG
			}
		}
		else
		{
			#ifdef _DEBUG
			printf(  "createImageFromText() - Could not create RenderTargetTexture\n" );
			printf(  "createImageFromText() - Warning, VideoDriver does not support RenderTarget textures, screen may flicker\n" );
			#endif // _DEBUG

			driver->beginScene(true, true, background_color );

			font->draw( txt, core::recti(core::position2di(0,0), txt_size), txt_color, false, false, 0);

			driver->endScene();

			raw = driver->createScreenShot( ECF_A8R8G8B8, ERT_FRAME_BUFFER);
		}
	}

	IImage* img = 0;

	if (raw)
	{
		/// cut out text-area inside "raw" image

		if (raw->getDimension() != txt_size)
		{
			/// create final image
			img = (IImage*)(new CImage( raw->getColorFormat(), txt_size ));
			if (!img)
			{
				printf( "createImageFromText() - Could not create image of txt_size\n" );
				return raw;
			}

			/// copy
			const u32 max_width = core::min_<u32>( txt_size.Width, raw->getDimension().Width );

			const u32 max_height = core::min_<u32>( txt_size.Height, raw->getDimension().Height );

			for (u32 y=0; y<max_height; y++)
			{
				for (u32 x=0; x<max_width; x++)
				{
					img->setPixel( x,y, raw->getPixel(x,y));
				}
			}

			raw->drop();
		}
		else
		{
			img = raw;
		}
	}

	return img;
}


#ifdef _IRR_COMPILE_WITH_FREETYPE2_

	void Tool::drawBitmapFT(

		IImage* dst,

		FT_Bitmap* bitmap,

		s32 x,

		s32 y,

		const SColor& txt_color )

	{

		if (!dst)
			return;

		if (!bitmap)
			return;

		const core::dimension2du img_size = dst->getDimension();

		const s32  x_max = x + (s32)bitmap->width;

		const s32  y_max = y + (s32)bitmap->rows;

		const s32 w = (s32)img_size.Width;

		const s32 h = (s32)img_size.Height;

		s32 i, j;

		u32 p, q;

		for ( j = y, q = 0; j < y_max; j++, q++ )
		{
			for ( i = x, p = 0; i < x_max; i++, p++ )
			{
				if ( i < 0 || j < 0 || i >= w || j >= h )
				{
					// skip to next loop, if any
					continue;
				}

				u32 a = bitmap->buffer[q * bitmap->width + p];

				dst->setPixel( i,j,
					SColor ( a,
						txt_color.getRed(),
						txt_color.getGreen(),
						txt_color.getBlue() ) );
			}
		}
	}


	//! create image from text ( always centered ) with minimal size for text

	//! uses IGUIEnvironment and its IVideoDriver

	//! can be used in combination with IGUITTFont to load truetype-fonts of any size

	IImage*

        createImageFromText(

			SFont* font,

			const core::stringw& txt,

			const SColor& txt_color,

			const SColor& background_color )

	{
		#ifdef _DEBUG
		os::Printer::log("createImageFromTextFT()", ELL_INFORMATION);
		#endif // _DEBUG

		if (!font)
		{
			os::Printer::log( "Invalid pointer to SFont", ELL_ERROR );
			return 0;
		}

		FT_Library    library;
		FT_Face       face;
		FT_GlyphSlot  slot;
		FT_Vector     pen;                    /* untransformed origin  */
		FT_Error      error;
		const s32 num_chars = (s32)txt.size();
		s32 n;

		/// init freetype2

		error = FT_Init_FreeType( &library ); /* initialize library */
		//error handling omitted

		error = FT_New_Face( library, font->FileName.c_str(), 0, &face );/* create face object */
		//error handling omitted

		// use 100dpi
		error = FT_Set_Char_Size( face, font->Size * 64, 0, 100, 0 ); /* set character size */
		//error handling omitted

		slot = face->glyph;

		/// calculate text-size

		pen.x = 0;
		pen.y = 0;


		for ( n = 0; n < num_chars; n++ )
		{
			// set transformation
			// FT_Set_Transform( face, &matrix, &pen );

			// load glyph image into the slot (erase previous one)
			error = FT_Load_Char( face, (s32)txt[n], FT_LOAD_RENDER );
			if ( error )
				continue;                 /* ignore errors */

			// now, draw to our target surface (convert position)
			//drawBitmapFT( dst, &slot->bitmap, slot->bitmap_left, h - slot->bitmap_top );

			// increment pen position
			pen.x += slot->advance.x;
			pen.y += slot->advance.y;
		}

		/// create image from text-size

		const core::dimension2du img_size( (u32)pen.x, (u32)pen.y);

		IImage* img = new CImage( ECF_A8R8G8B8, img_size );

		if (!img)
		{
			os::Printer::log( "Could not create image of txt_size", ELL_ERROR);
			return 0;
		}

		img->fill( background_color );

		const s32 w = (s32)img_size.Width;

		const s32 h = (s32)img_size.Height;

		/// draw text to image
		//set up matrix
		//matrix.xx = (FT_Fixed)( cos( angle ) * 0x10000L );
		//matrix.xy = (FT_Fixed)(-sin( angle ) * 0x10000L );
		//matrix.yx = (FT_Fixed)( sin( angle ) * 0x10000L );
		//matrix.yy = (FT_Fixed)( cos( angle ) * 0x10000L );

		//the pen position in 26.6 cartesian space coordinates;
		//start at (300,200) relative to the upper left corner
		pen.x = 0;
		pen.y = 0;

		for ( n = 0; n < num_chars; n++ )
		{
			// set transformation
			// FT_Set_Transform( face, &matrix, &pen );

			// load glyph image into the slot (erase previous one)
			error = FT_Load_Char( face, (s32)txt[n], FT_LOAD_RENDER );
			if ( error )
				continue;                 /* ignore errors */

			// now, draw to our target surface (convert position)
			drawBitmapFT( img, &slot->bitmap, pen.x, h - pen.y );
			// drawBitmapFT( img, &slot->bitmap, slot->bitmap_left, h - slot->bitmap_top );

			// increment pen position
			pen.x += slot->advance.x;
			pen.y += slot->advance.y;
		}


		/// drop freetype2

		FT_Done_Face    ( face );
		FT_Done_FreeType( library );

//
//		const core::dimension2du& txt_size = img->getDimension();
//
//		core::position2di offset(0,0);
//		if (hAlign == 0)
//		{
//			offset.X = -(s32)(txt_size.Width>>1);
//		}
//		else if (hAlign > 0 )
//		{
//			offset.X = -(s32)(txt_size.Width);
//		}
//
//		if (vAlign == 0)
//		{
//			offset.Y = -(s32)(txt_size.Height>>1);
//		}
//		else if (vAlign > 0 )
//		{
//			offset.Y = -(s32)(txt_size.Height);
//		}
//
//		x+=offset.X;
//		y+=offset.Y;
//
//		/// debug-drawing
//		#ifdef _DEBUG
//		drawRect( dst, core::recti( core::position2di(x,y), txt_size ), SColor(255,255,0,0), 1, false);
//		#endif // _DEBUG
//
//		/// actual text-drawing
//		// loop all pixels of text-image, skip operation when outside dst-bound
//		// or skip when txt-pixel is 0 == SColor(0,0,0,0)
//		for (u32 j=0; j<txt_size.Height; j++)
//		{
//			for (u32 i=0; i<txt_size.Width; i++)
//			{
//				const SColor& pixel = img->getPixel(i,j);
//				if (pixel.color != 0)
//				{
//					s32 dx = x+(s32)i;
//					s32 dy = y+(s32)j;
//					if (dx>=0 && dy>=0 && dx<(s32)img_size.Width && dy<(s32)img_size.Height)
//					{
//						dst->setPixel( dx,dy, pixel, blend );
//					}
//				}
//			}
//		}

		return img;
	}

//! draw text to existing software image

//! using only software freetype2 library and no irrlicht-device

//! text is aligned at borders ( -1=left/top, 0=center/middle, 1=right/bottom )

bool
	drawText(
			SFont* font,
			IImage* dst,
			const core::stringw& txt,
			s32 x,
			s32 y,
			s32 hAlign,
			s32 vAlign,
			const SColor& txt_color,
			const SColor& background_color,
			core::recti* clipRect,
			bool blend)

	{
		#ifdef _DEBUG
		os::Printer::log("drawTextFT()", ELL_INFORMATION);
		#endif // _DEBUG

		if (!dst)
		{
			os::Printer::log( "drawText() - Invalid pointer to IImage", ELL_ERROR );
			return false;
		}

		if (!font)
		{
			os::Printer::log( "drawText() - Invalid pointer to IGUIFont", ELL_ERROR );
			return false;
		}

		const core::dimension2du& dst_size = dst->getDimension();

		if (x>=(s32)dst_size.Width)
		{
			os::Printer::log( "drawText() - Cant draw outside destination Image ( x coord too big )", ELL_ERROR );
			return false;
		}

		if (y>=(s32)dst_size.Height)
		{
			os::Printer::log( "drawText() - Cant draw outside destination Image ( y coord too big )", ELL_ERROR );
			return false;
		}

		IImage* img = createImageFromText(font, txt, txt_color, background_color);

		if (!img)
		{
			os::Printer::log( "drawText() - Could not create image from text", ELL_ERROR );
			return false;
		}

		const core::dimension2du& img_size = img->getDimension();

		core::position2di offset(0,0);
		if (hAlign == 0)
		{
			offset.X = -(s32)(img_size.Width>>1);
		}
		else if (hAlign > 0 )
		{
			offset.X = -(s32)img_size.Width;
		}

		if (vAlign == 0)
		{
			offset.Y = -(s32)(img_size.Height>>1);
		}
		else if (vAlign > 0 )
		{
			offset.Y = -(s32)img_size.Height;
		}

		x+=offset.X;
		y+=offset.Y;

		/// debug-drawing
		#ifdef _DEBUG
		//drawRect( dst, core::recti( core::position2di(x,y), txt_size ), SColor(255,255,0,0), 1, false);
		#endif // _DEBUG

		/// actual text-drawing
		// loop all pixels of text-image, skip operation when outside dst-bound
		// or skip when txt-pixel is 0 == SColor(0,0,0,0)
		for (u32 j=0; j<img_size.Height; j++)
		{
			for (u32 i=0; i<img_size.Width; i++)
			{
				const SColor& pixel = img->getPixel(i,j);
				if (pixel.color != 0)
				{
					s32 dx = x+(s32)i;
					s32 dy = y+(s32)j;
					if (dx>=0 && dy>=0 && dx<(s32)dst_size.Width && dy<(s32)dst_size.Height)
					{
						dst->setPixel( dx,dy, pixel, blend );
					}
				}
			}
		}

		if (img)
			img->drop();

		return true;
	}

#endif // _IRR_COMPILE_WITH_FREETYPE2_

} // end namespace video

} // end namespace irr
