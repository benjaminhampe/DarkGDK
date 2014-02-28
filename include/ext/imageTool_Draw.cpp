// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include <imageTool.h>

namespace irr
{

namespace video
{

//! @brief set pixel for signed integer coords only if inside (0,0,w,h)
void Tool::drawPixel( IImage* img, s32 x, s32 y, const SColor& color, bool blend )
{
	if (!img) return;
	if (x<0) return;
	if (y<0) return;
   img->setPixel( (u32)x, (u32)y, color, blend);
}

//! @brief set pixel for signed integer coords always - simple border align
void Tool::drawPixelAlways( IImage* img, s32 x, s32 y, const SColor& color, bool blend )
{
	if (!img) return;
	if (x<0) x=0;
	if (y<0) y=0;

	const core::dimension2du& Size = img->getDimension();

	if (x>=(s32)Size.Width) x=(s32)Size.Width-1;
	if (y>=(s32)Size.Height) y=(s32)Size.Height-1;
    img->setPixel( (u32)x, (u32)y, color, blend);
}

//! @brief get pixel from signed integer coords only if inside (0,0,w,h) else SColor(0,0,0,0)
SColor Tool::getPixel( IImage* img, s32 x, s32 y )
{
	if (!img) return SColor(0,0,0,0);
	if (x<0) return SColor(0,0,0,0);
	if (y<0) return SColor(0,0,0,0);
	const core::dimension2du& Size = img->getDimension();
	if (x>(s32)Size.Width-1) return SColor(0,0,0,0);
	if (y>(s32)Size.Height-1) return SColor(0,0,0,0);
	return img->getPixel((u32)x,(u32)y);
}

//! @brief get pixel from signed integer coords (always)
SColor Tool::getPixelAlways( IImage* img, s32 x, s32 y )
{
	if (!img) return SColor(0,0,0,0);
	if (x<0) x=0;
	if (y<0) y=0;
	const core::dimension2du& Size = img->getDimension();
	if (x>=(s32)Size.Width) x=(s32)Size.Width-1;
	if (y>=(s32)Size.Height) y=(s32)Size.Height-1;
	return img->getPixel( (u32)x, (u32)y);
}


/// Rainbow
SColor Tool::getLightWaveColor( f64 lambda, f64 gamma)
{
    // setze ? ? [380, 780]
    if (lambda < 380.0) lambda = 380.0;
    if (lambda > 780.0) lambda = 780.0;

    // Fallunterscheidung
    f64 r,g,b,f;

    if ((lambda >= 380.0) && (lambda < 440.0)) { r = (440.0-lambda)/(440.0-380.0); g = 0.0; b = 1.0; }
    else if ((lambda >= 440.0) && (lambda < 490.0)) { r = 0.0; g = (lambda-440.0)/(490.0-440.0); b = 1.0; }
    else if ((lambda >= 490.0) && (lambda < 510.0)) { r = 0.0; g = 1.0; b = (510.0-lambda)/(510.0-490.0); }
    else if ((lambda >= 510.0) && (lambda < 580.0)) { r = (lambda-510.0)/(580.0-510.0); g = 1.0; b = 0.0; }
    else if ((lambda >= 580.0) && (lambda < 645.0)) { r = 1.0; g = (645.0-lambda)/(645.0-580.0); b = 0.0; }
    else /* if ((lambda >= 645.0) && (lambda <= 780.0)) */ { r = 1.0; g = 0.0; b = 0.0; }

    // reduce intesity at the borders
    if ((lambda >= 380.0) && (lambda < 420.0)) { f = 0.3 + 0.7*(lambda-380.0)/(420.0-380.0); }
    else if ((lambda >= 420.0) && (lambda <= 700.0)) { f = 1.0; }
    else /* if ((lambda > 700.0) && (lambda <= 780.0)) */ { f = 0.3 + 0.7*(780.0-lambda)/(780.0-700.0); }

    // eigentliche Korrektur
    if (f!=1.0) { r *= f; g *= f; b *= f; }

    // Gamma Korrektur
    if (gamma!=1.0) { r = pow(r, gamma); g = pow(g, gamma); b = pow(b, gamma); }

    // Clamping to [0,255]
    r *= 255.0; g *= 255.0; b *= 255.0;

    // hoffentlicht optimiert der compiler dies mit mmx und sse befehlen
    if (r<0.0) r=0.0; if (g<0.0) g=0.0; if (b<0.0) b=0.0;

    if (r>255.0) r=255.0; if (g>255.0) g=255.0; if (b>255.0) b=255.0;

    // return ARGB 32bit color (Alpha = 'opaque' = 'nicht transparent' = '255')
    return SColor(255,(u32)r, (u32)g, (u32)b );
}

SColor Tool::getRainbowColor( u32 i, u32 count, f64 gamma)
{
    //! division by zero would lead to runtime error !!!
    if (count < 1)
		return SColor(255,255,255,255);

	//! just a simple wrapper function, that linear inperpolates
    return getLightWaveColor(380.0 + 400.0*(f64)i/(f64)count, gamma);
}

IImage* Tool::createRainbowImage( u32 w, u32 h, u8 transparency, f64 gamma)
{
	// create image
	core::dimension2du size(w,h);

	IImage* img = (IImage*)new CImage(ECF_A8R8G8B8, size);

	if (!img) return 0;

	size = img->getDimension();

	// loop pixels per col
	for (u32 y=0; y<size.Height; y++)
	{
		// calculate rainbow-color
		SColor c = getRainbowColor( y, size.Height, gamma);

		// set transparency
		c.setAlpha(transparency);

		// write one row with same color
		for (u32 x=0; x<size.Width; x++)
		{
			// write rainbow-color
			img->setPixel(x,y,c,false);
		}
	}

	return img;
}

ITexture* Tool::createRainbowTexture( IVideoDriver* driver, u32 w, u32 h, u8 transparency, f64 gamma)
{
	if (!driver)
	{
		return 0;
	}

	IImage* img = createRainbowImage(w,h,transparency, gamma);
	if (!img)
		return 0;

	ITexture* tex = 0;

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

	//! my RainbowTexture
	tex = driver->addTexture("rainbow", img, 0);

	//! restore states
	driver->setTextureCreationFlag(ETCF_ALLOW_NON_POWER_2,b0);
	driver->setTextureCreationFlag(ETCF_ALWAYS_16_BIT,b1);
	driver->setTextureCreationFlag(ETCF_ALWAYS_32_BIT,b2);
	driver->setTextureCreationFlag(ETCF_CREATE_MIP_MAPS,b3);
	driver->setTextureCreationFlag(ETCF_FORCE_32_BIT_DO_NOT_USE,b4);
	driver->setTextureCreationFlag(ETCF_NO_ALPHA_CHANNEL,b5);
	driver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_QUALITY,b6);
	driver->setTextureCreationFlag(ETCF_OPTIMIZED_FOR_SPEED,b7);

	img->drop(); // delete rainbow-image

	return tex;
} // END FUNCTION




PointList Tool::traverseLine( const core::position2di& A, const core::position2di& B )
{
	PointList dst( irr::core::abs_<s32>(B.X-A.X)+irr::core::abs_<s32>(B.Y-A.Y) );
	return dst;
}

PointList Tool::traverseCircle( const core::position2di& center, s32 radius )
{
	PointList dst( radius+3 );
	dst.set_used(0);

	// Bresenham
	s32 i,j,F;
	i = 0;
	j = radius;
	F = 1 - radius;

	while (i < j)
	{
		++i;
		if (F < 0)
		{
			F += (i<<1) - 1;
		}
		else
		{
			F += ((i - j)<<1);
			--j;
		}
		// Verbesserungen by Benjamin Hampe (c) 2012
		dst.push_back( core::position2di( center.X+i,center.Y+j ) );
		dst.push_back( core::position2di( center.X+j,center.Y+i ) );
	}
	return dst;
}


PointList Tool::traverseEllipse( const core::position2di& center, s32 rx, s32 ry )
{
//	const s32 w = dest->getDimension().Width;
//	const s32 h = dest->getDimension().Height;

	if (rx==ry)
		return traverseCircle( center, rx );

	PointList dst;
	dst.reallocate(rx+ry);
	dst.set_used(0);

	// Abbruchbedingung
	if ( (rx==0) && (ry==0) )
		return dst;

	const s32 rx2=rx*rx; // Ellipsen Radien Quadrate
	const s32 ry2=ry*ry; // Ellipsen Radien Quadrate
	s32 x = center.X;
	s32 y = center.Y;
//	const s32 mx = center.X;	 // Ellipsen Mittelpunkt
//	const s32 my = center.Y; 	 // Ellipsen Mittelpunkt

	// Bresenham Anfangswerte
	// Trick: nur 1/4 Ellipse berechne und restliche 3/4 durch Spiegelung (gerade Ellipse!!!)
	s32 ddF_x=0;
	s32 ddF_y=((rx2*ry)<<1);
	x=0;
	y=ry;

	// Bresenham Alghorithmus
	s32 F=irr::core::round32((f32)(ry2-rx2*ry)+(f32)rx2*0.25f);
	while( ddF_x < ddF_y )
	{
		if (F >= 0)
		{
			y     -= 1;        // south
			ddF_y -= (rx2<<1);
			F     -= ddF_y;
		}
		x     += 1;          // east
		ddF_x += (ry2<<1);
		F     += ddF_x + ry2;

		dst.push_back( core::position2di( center.X+x, center.Y+y) );
	}

	// Bresenham Alghorithmus
	F = irr::core::round32((f32)ry2*((f32)x+0.5f)*((f32)x+0.5f) + (f32)(rx2*(y-1)*(y-1) - rx2*ry2));
	while( y > 0 )
	{
		if(F <= 0)
		{
			x     += 1;        // east
			ddF_x += (ry2<<1);
			F     += ddF_x;
		}
		y     -= 1;           // south
		ddF_y -= (rx2<<1);
		F     += rx2 - ddF_y;

		dst.push_back( core::position2di( center.X+x, center.Y+y) );
	}
	return dst;
}



void Tool::drawImage(
	IImage* src,
	IImage* dst,
	const core::position2di& pos,
	const core::dimension2du& size,
	bool bTransparent,
	bool blend)
{
	if (!src)
		return;

	const u32 x_max = irr::core::min_<u32>( dst->getDimension().Width, src->getDimension().Width );
	const u32 y_max = irr::core::min_<u32>( dst->getDimension().Height, src->getDimension().Height );

	for (u32 y=0; y<y_max; y++)
	{
		for (u32 x=0; x<x_max; x++)
		{
			const SColor& color = src->getPixel(x,y);

			drawPixel( dst, (s32)x+pos.X, (s32)y+pos.Y, color, blend);
		}
	}
}

//! draw a line with 1 color(s) to image ( Bresenham, no AA )
bool Tool::drawLine(
	video::IImage* dst,
	s32 x0,
	s32 y0,
	s32 x1,
	s32 y1,
	const video::SColor& color,
	bool blend )
{
	if (!dst) return false;

	const core::dimension2du img_size = dst->getDimension();

	if ((img_size.Width==0) || (img_size.Height==0)) return false;

	const s32 dx = core::abs_<s32>( x1 - x0 );
	const s32 dy = core::abs_<s32>( y1 - y0 );

	if ((dx==0) && (dy==0)) return false;

	s32 sx=1; // sign
	s32 sy=1; // sign

	if (x0>x1) sx = -1;
	if (y0>y1) sy = -1;

	s32 err = dx-dy;
	s32 e2 = 0;
	s32 x = x0;
	s32 y = y0;

	while(1)
	{
		drawPixel( dst,x,y,color, blend);

		if ((x==x1) && (y==y1)) break;

		e2 = err << 1;

		if (e2 > -dy) { err -= dy;	x += sx; }
		if (e2 < dx) { y += sy; err += dx; }
	}

	return true;
}

//! draw a line with 2 color(s) to image ( Bresenham, no AA )
bool Tool::drawLine(
	video::IImage* dst,
	s32 x0,
	s32 y0,
	s32 x1,
	s32 y1,
	const video::SColor& color_a,
	const video::SColor& color_b,
	bool blend )
{
	if (!dst) return false;

	const core::dimension2du img_size = dst->getDimension();

	if ((img_size.Width == 0) || (img_size.Height == 0))
		return false;

	const s32 dx = core::abs_<s32>( x1 - x0 );
	const s32 dy = core::abs_<s32>( y1 - y0 );

	if ((dx==0) && (dy==0)) return false;

	s32 sx = 1; // sign
	s32 sy = 1; // sign

	if (x0 > x1) sx = -1;
	if (y0 > y1) sy = -1;

	s32 err = dx-dy;
	s32 e2 = 0;
	s32 x = x0;
	s32 y = y0;

	s32 numpixels = 0;

	// count pixels
	while (1)
	{
		numpixels++;

		if ((x==x1) && (y==y1)) break;

		e2 = err << 1;
		if (e2 > -dy) { err -= dy;	x += sx; }
		if (e2 < dx) { err += dx; y += sy; }
	}

	// reset vars;
	err = dx-dy;
	e2 = 0;
	x = x0;
	y = y0;

	// values for linear color interpolation
	const f32 A1=(f32)color_a.getAlpha();
	const f32 R1=(f32)color_a.getRed();
	const f32 G1=(f32)color_a.getGreen();
	const f32 B1=(f32)color_a.getBlue();
	const f32 dA=(f32)color_b.getAlpha()-A1;
	const f32 dR=(f32)color_b.getRed()-R1;
	const f32 dG=(f32)color_b.getGreen()-G1;
	const f32 dB=(f32)color_b.getBlue()-B1;

	// actual drawing
	f32 f=0.f;
	s32 k=0;
	u32 cR=0, cG=0, cB=0, cA=0;
	while (1)
	{
		f = (f32)k/(f32)numpixels;
		k++;

		cA=A1;
		cR=R1;
		cG=G1;
		cB=B1;

		// maybe faster under the assumption that colors have most likely same alpha value
		if (dA>0) cA = (u32)core::clamp( core::round32(A1+dA*f), 0, 255);
		if (dR>0) cR = (u32)core::clamp( core::round32(R1+dR*f), 0, 255);
		if (dG>0) cG = (u32)core::clamp( core::round32(G1+dG*f), 0, 255);
		if (dB>0) cB = (u32)core::clamp( core::round32(B1+dB*f), 0, 255);

		drawPixel( dst, x, y, video::SColor( cA, cR, cG, cB), blend );

		if (x == x1 && y == y1) break;

		e2 = err << 1;
		if (e2 > -dy)	{	err -= dy;	x += sx; }
		if (e2 < dx)	{	err += dx;	y += sy; }
	}

	return true;
}

//! draw a line with 2 color(s) to image ( Bresenham, no AA )
bool Tool::drawLine(
	video::IImage* dst,
	const core::rectf& pos,
	const video::SColor& color,
	bool blend )
{
	const s32 x0 = core::floor32( pos.UpperLeftCorner.X );
	const s32 y0 = core::floor32( pos.UpperLeftCorner.Y );
	const s32 x1 = core::floor32( pos.LowerRightCorner.X );
	const s32 y1 = core::floor32( pos.LowerRightCorner.Y );

	return drawLine( dst, x0, y0, x1, y1, color, blend);
}

//! draw a line with 2 color(s) to image ( Bresenham, no AA )

bool Tool::drawLine(
	video::IImage* dst,
	const core::rectf& pos,
	const video::SColor& color_a,
	const video::SColor& color_b,
	bool blend )
{
	if (!dst)
		return false;

	const core::dimension2du img_size = dst->getDimension();

	if ( ( img_size.Width == 0 ) || ( img_size.Height == 0 ) )
		return false;

	const s32 x0 = core::floor32( pos.UpperLeftCorner.X );
	const s32 y0 = core::floor32( pos.UpperLeftCorner.Y );
	const s32 x1 = core::floor32( pos.LowerRightCorner.X );
	const s32 y1 = core::floor32( pos.LowerRightCorner.Y );

	return drawLine( dst, x0, y0, x1, y1, color_a, color_b, blend );
}


//! draw a bresenham rect with 1 color
//! if ( border <= 0 ) solid/filled else (border>0) outlined/border
void Tool::drawRect(
	IImage* dst,
	const core::recti& pos,
	const SColor& color,
	s32 border,
	bool blend )
{
	s32 x1 = pos.UpperLeftCorner.X;
	s32 y1 = pos.UpperLeftCorner.Y;
	s32 x2 = pos.LowerRightCorner.X;
	s32 y2 = pos.LowerRightCorner.Y;

	if (border==0)
	{
		for (s32 y=y1; y<=y2; y++)
		{
			for (s32 x=x1; x<=x2; x++)
			{
				if (color.getAlpha()<255)
				{
					SColor pixel = getPixelAlways( dst, x,y );
					s32 r = (s32)irr::core::clamp<f32>((f32)color.getAlpha()*(f32)color.getRed()/255.0f, 0,255.f);
					s32 g = (s32)irr::core::clamp<f32>((f32)color.getAlpha()*(f32)color.getGreen()/255.0f, 0,255.f);
					s32 b = (s32)irr::core::clamp<f32>((f32)color.getAlpha()*(f32)color.getBlue()/255.0f, 0,255.f);
					pixel.set( pixel.getAlpha(),
						(u32)irr::core::s32_clamp(pixel.getRed() + r,0,255),
						(u32)irr::core::s32_clamp(pixel.getGreen() + g,0,255),
						(u32)irr::core::s32_clamp(pixel.getBlue() + b,0,255) );
					drawPixel( dst, x, y, pixel, blend);

				}
				else
				{
					drawPixel( dst, x, y, color, blend);
				}
			}
		}
	}
	else if ( border >= 1)
	{
		for (s32 b=0; b<border; b++)
		{
			drawLine( dst, x1+b,y1+b, x2-b,y1+b, color, blend);
			drawLine( dst, x1+b,y1+b, x1+b,y2-b, color, blend);
			drawLine( dst, x2-b,y1+b, x2-b,y2-b, color, blend);
			drawLine( dst, x1+b,y2-b, x2-b,y2-b, color, blend);
		}
	}
}

//! draw a bresenham rect with 4 linear interpolated colors
//! if ( border <= 0 ) solid/filled else (border>0) outlined/border
void Tool::drawRect(
	IImage* dst,
	const core::recti& pos,
	const SColor& bottomLeft,
	const SColor& topLeft,
	const SColor& topRight,
	const SColor& bottomRight,
	s32 border,
	bool blend )
{
	if (border==0)
	{
		const s32& x1 = pos.UpperLeftCorner.X;
		const s32& x2 = pos.LowerRightCorner.X;
		const s32& y1 = pos.UpperLeftCorner.Y-1;
		const s32& y2 = pos.LowerRightCorner.Y-1;

		// common factor for all colors ( 1 / (dx * dy) )
		const f32 n_inv = irr::core::reciprocal( (f32)(x2 - x1) * (f32)(y2 - y1) );

		for (s32 y=y1; y<=y2; y++)
		{
			for (s32 x=x1; x<=x2; x++)
			{
				const f32 f11 = (f32)(x2 - x) * (f32)(y2 - y) * n_inv; // bottomRight
				const f32 f21 = (f32)(x - x1) * (f32)(y2 - y) * n_inv; // bottomLeft
				const f32 f12 = (f32)(x2 - x) * (f32)(y - y1) * n_inv; // topRight
				const f32 f22 = (f32)(x - x1) * (f32)(y - y1) * n_inv; // topLeft

				const f32 fA = 	(f32)topLeft.getAlpha() * f11 +
								(f32)topRight.getAlpha() * f21 +
								(f32)bottomRight.getAlpha() * f22 +
								(f32)bottomLeft.getAlpha() * f12;

				const f32 fR = 	(f32)topLeft.getRed() * f11 +
								(f32)topRight.getRed() * f21 +
								(f32)bottomRight.getRed() * f22 +
								(f32)bottomLeft.getRed() * f12;

				const f32 fG = 	(f32)topLeft.getGreen() * f11 +
								(f32)topRight.getGreen() * f21 +
								(f32)bottomRight.getGreen() * f22 +
								(f32)bottomLeft.getGreen() * f12;

				const f32 fB = 	(f32)topLeft.getBlue() * f11 +
								(f32)topRight.getBlue() * f21 +
								(f32)bottomRight.getBlue() * f22 +
								(f32)bottomLeft.getBlue() * f12;

				SColor color(
					(u32)irr::core::clamp( irr::core::round32(fA), 0, 255),
					(u32)irr::core::clamp( irr::core::round32(fR), 0, 255),
					(u32)irr::core::clamp( irr::core::round32(fG), 0, 255),
					(u32)irr::core::clamp( irr::core::round32(fB), 0, 255) );

				drawPixel( dst, x, y, color, blend);
			}
		}
	}
	else if ( border == 1)
	{
//		drawLine( pos.UpperLeftCorner, core::position2di(pos.LowerRightCorner.X, pos.UpperLeftCorner.Y), color, blend);
//		drawLine( pos.UpperLeftCorner, core::position2di(pos.UpperLeftCorner.X, pos.LowerRightCorner.Y), color, blend);
//		drawLine( core::position2di(pos.LowerRightCorner.X, pos.UpperLeftCorner.Y), pos.LowerRightCorner, color, blend);
//		drawLine( core::position2di(pos.UpperLeftCorner.X, pos.LowerRightCorner.Y), pos.LowerRightCorner, color, blend);
//
		const s32 x = pos.LowerRightCorner.X-1;
		const s32 y = pos.LowerRightCorner.Y-1;
		drawLine( dst, pos.UpperLeftCorner.X, pos.UpperLeftCorner.Y, x, pos.UpperLeftCorner.Y, topLeft, topRight, blend);
		drawLine( dst, pos.UpperLeftCorner.X, pos.UpperLeftCorner.Y, pos.UpperLeftCorner.X, y, topLeft, bottomLeft, blend);
		drawLine( dst, x, pos.UpperLeftCorner.Y, x,y, topRight, bottomRight, blend);
		drawLine( dst, pos.UpperLeftCorner.X, y, x,y, bottomLeft, bottomRight, blend);
	}
	else if ( border > 1)
	{
		IImage* tmp = new CImage( dst->getColorFormat(), core::dimension2du( (u32)pos.getWidth(), (u32)pos.getHeight() ) );
		if (!tmp)
			return;

		const SColor black(  0,  0,  0,  0);
		const SColor white(255,255,255,255);

		tmp->fill( black );
		drawRect( tmp, core::recti( core::position2di(0,0), tmp->getDimension()), white, border, blend);

		// common factor for all colors ( 1 / (w * h) )
		const u32 w = tmp->getDimension().Width;
		const u32 h = tmp->getDimension().Height;
		const f32 n_inv = irr::core::reciprocal( (f32)w * (f32)h );

		for (u32 y = 0; y < h; y++)
		{
			u32 x = 0;
			while (x < w)
			{
				const SColor& colorNow = tmp->getPixel(x,y);

				if (colorNow == white)
				{
					const f32 f11 = (f32)(w-1-x) * (f32)(h-1-y) * n_inv; // topLeft
					const f32 f21 = (f32)(x) * (f32)(h-1-y) * n_inv; // topRight
					const f32 f12 = (f32)(w-1-x) * (f32)(y) * n_inv; // bottomLeft
					const f32 f22 = (f32)(x) * (f32)(y) * n_inv; // bottomRight

					const f32 fA = (f32)topLeft.getAlpha() * f11 +
									(f32)topRight.getAlpha() * f21 +
									(f32)bottomRight.getAlpha() * f12 +
									(f32)bottomLeft.getAlpha() * f22;

					const f32 fR = 	(f32)topLeft.getRed() * f11 +
									(f32)topRight.getRed() * f21 +
									(f32)bottomRight.getRed() * f12 +
									(f32)bottomLeft.getRed() * f22;

					const f32 fG = 	(f32)topLeft.getGreen() * f11 +
									(f32)topRight.getGreen() * f21 +
									(f32)bottomRight.getGreen() * f12 +
									(f32)bottomLeft.getGreen() * f22;

					const f32 fB = 	(f32)topLeft.getBlue() * f11 +
									(f32)topRight.getBlue() * f21 +
									(f32)bottomRight.getBlue() * f12 +
									(f32)bottomLeft.getBlue() * f22;

					SColor color(
						(u32)irr::core::clamp( irr::core::round32(fA), 0, 255),
						(u32)irr::core::clamp( irr::core::round32(fR), 0, 255),
						(u32)irr::core::clamp( irr::core::round32(fG), 0, 255),
						(u32)irr::core::clamp( irr::core::round32(fB), 0, 255) );

					drawPixel( dst, x, y, color, blend);
				}
//				else
//				{
//					x += ( w - (border<<1)) - 2; // skip pixels to increase speed
//				}
				x++;
			}
		}

		drawImage( tmp, dst, pos.UpperLeftCorner, tmp->getDimension(), true, false);
		tmp->drop();
	}
}

//! draw a Bresenham-round-rect, 1 colors, filled (border=0) or outlined with border, option to blend
void Tool::drawRoundRect( IImage* dst, const core::recti& pos, s32 rx, s32 ry, const SColor& color, s32 border, bool blend)
{
	// abort
	if (!dst)
		return;

	// abort
	if (rx < 1 && ry < 1)
		return;

	// set equal, if one radius is zero --> circle
	if (rx==0) rx = ry;
	if (ry==0) ry = rx;

	s32 w = pos.getWidth();
	s32 h = pos.getHeight();

//	core::position2di m = pos.getCenter();
//	core::position2di dA( (w-1)>>1, ry);
//	core::position2di lowerRight(w-1-rx, ry);
//	core::position2di upperLeft(rx, h-1-ry);
//	core::position2di upperRight(w-1-rx, h-1-ry);

	core::position2di lowerLeft = core::position2di(rx, ry) + pos.UpperLeftCorner;
	core::position2di lowerRight = core::position2di(w-1-rx, ry) + pos.UpperLeftCorner;
	core::position2di upperLeft = core::position2di(rx, h-1-ry) + pos.UpperLeftCorner;
	core::position2di upperRight = core::position2di(w-1-rx, h-1-ry) + pos.UpperLeftCorner;

	// draw a filled round-rect
	if (border == 0)
	{
		// Ellipsen-Code
		const s32 rx2=rx*rx; // Ellipsen Radien Quadrate
		const s32 ry2=ry*ry; // Ellipsen Radien Quadrate
		s32 x = 0;
		s32 y = 0;

		// Bresenham Ellipse Anfangswerte
		s32 ddF_x=0;
		s32 ddF_y=((rx2*ry)<<1);
		x=0;
		y=ry;

		// Bresenham Alghorithmus
		s32 F=irr::core::round32((f32)(ry2-rx2*ry)+(f32)rx2*0.25f);
		while( ddF_x < ddF_y )
		{
			if (F >= 0)
			{
				y     -= 1;        // south
				ddF_y -= (rx2<<1);
				F     -= ddF_y;
			}
			x     += 1;          // east
			ddF_x += (ry2<<1);
			F     += ddF_x + ry2;
			drawLine( dst, upperLeft.X-x, upperLeft.Y+y, upperRight.X+x, upperRight.Y+y, color, blend);
			drawLine( dst, lowerLeft.X-x, lowerLeft.Y-y, lowerRight.X+x, lowerRight.Y-y, color, blend);
		}

		// Bresenham Alghorithmus
		F = irr::core::round32((f32)ry2*((f32)x+0.5f)*((f32)x+0.5f) + (f32)(rx2*(y-1)*(y-1) - rx2*ry2));
		while( y > 0 )
		{
			if(F <= 0)
			{
				x     += 1;        // east
				ddF_x += (ry2<<1);
				F     += ddF_x;
			}
			y     -= 1;           // south
			ddF_y -= (rx2<<1);
			F     += rx2 - ddF_y;

			drawLine( dst, upperLeft.X-x, upperLeft.Y+y, upperRight.X+x, upperRight.Y+y, color, blend);
			drawLine( dst, lowerLeft.X-x, lowerLeft.Y-y, lowerRight.X+x, lowerRight.Y-y, color, blend);
		}

		s32 y1 = pos.UpperLeftCorner.Y + ry;
		s32 y2 = pos.UpperLeftCorner.Y + pos.getHeight() - ry;
		y = y1;
		while( y < y2 )
		{
			drawLine( dst, pos.UpperLeftCorner.X , y, pos.LowerRightCorner.X, y, color, blend);
			y++;
		}

	}
	// draw a bordered round-rect
	else
	{
		if (border == 1)
		{
			PointList points = traverseEllipse( core::position2di(0,0), rx,ry);

			for (u32 i=0; i<points.size(); i++)
			{
				dst->setPixel(upperRight.X + points[i].X, upperRight.Y + points[i].Y, color);
				dst->setPixel(lowerRight.X + points[i].X, lowerRight.Y - points[i].Y, color);
				dst->setPixel(upperLeft.X - points[i].X, upperLeft.Y + points[i].Y, color);
				dst->setPixel(lowerLeft.X - points[i].X, lowerLeft.Y - points[i].Y, color);
			}

			//! core::recti has flaws, i.e. it does not guarantee that UpperLeftCorner is more upper and left than LowerRightCorner !!!
			const s32 x1 = irr::core::s32_min( pos.UpperLeftCorner.X, pos.LowerRightCorner.X);
			const s32 y1 = irr::core::s32_min( pos.UpperLeftCorner.Y, pos.LowerRightCorner.Y);
			const s32 x2 = irr::core::s32_max( pos.UpperLeftCorner.X, pos.LowerRightCorner.X);
			const s32 y2 = irr::core::s32_max( pos.UpperLeftCorner.Y, pos.LowerRightCorner.Y);

			drawLine( dst, x1+rx, y1, x2-1-rx, y1, color, blend);
			drawLine( dst, x1+rx, y2-1, x2-1-rx, y2-1, color, blend);
			drawLine( dst, x1, y1+ry, x1, y2-1-ry, color, blend);
			drawLine( dst, x2-1, y1+ry, x2-1, y2-1-ry, color, blend);
		}
		else
		{
			IImage* tmp = new CImage( dst->getColorFormat(), core::dimension2du(w+1,h+1));
			if (!tmp)
				return;

			tmp->fill(0);
			drawRoundRect( tmp, core::recti(0,0,(s32)w, (s32)h), rx,ry, color, 0, false);
			drawRoundRect( tmp, core::recti(border, border, (s32)w-border, (s32)h-border), rx,ry, 0, 0, false);

			drawImage( tmp, dst, pos.UpperLeftCorner, tmp->getDimension(), true, false);
			tmp->drop();

//			floodFill(x1)
		}
	}
}

void Tool::drawRoundRect( IImage* dst, const core::recti& pos, s32 rx, s32 ry, const SColor& topLeft, const SColor& topRight, const SColor& bottomRight, const SColor& bottomLeft, s32 border, bool blend)
{
	// abort
	if (!dst)
		return;

	//! guarantee that UpperLeftCorner is more upperleft than LowerRightCorner
	const s32 x1 = irr::core::s32_min( pos.UpperLeftCorner.X, pos.LowerRightCorner.X);
	const s32 y1 = irr::core::s32_min( pos.UpperLeftCorner.Y, pos.LowerRightCorner.Y);
	const s32 x2 = irr::core::s32_max( pos.UpperLeftCorner.X, pos.LowerRightCorner.X);
	const s32 y2 = irr::core::s32_max( pos.UpperLeftCorner.Y, pos.LowerRightCorner.Y);

	core::dimension2du size( (u32)(x2-x1)+1, (u32)(y2-y1)+1 );

	// abort
	if ((size.Width == 0) || (size.Height == 0))
		return;

	// create temporary canvas-image
	IImage* tmp = new CImage( dst->getColorFormat(), size);

	// abort
	if (!tmp)
		return;

	const SColor black(0,0,0,0);
	const SColor white(255,255,255,255);

	tmp->fill( black );

	drawRoundRect( tmp, core::recti( core::position2di(0,0), size), rx,ry, white, border, false);

	// interpolate colors
	// common factor for all colors ( 1 / (dx * dy) )
	const f32 n_inv = irr::core::reciprocal( (f32)(x2 - x1) * (f32)(y2 - y1) );

	for (u32 y=0; y<size.Height; y++)
	{
		for (u32 x=0; x<size.Width; x++)
		{
			if (getPixel( tmp,x,y ) == white)
			{
				const f32 f11 = (f32)(size.Width-1-x) * (f32)(size.Height-1 - y) * n_inv; // topLeft
				const f32 f21 = (f32)(x) * (f32)(size.Height-1 - y) * n_inv; // topRight
				const f32 f12 = (f32)(size.Width-1 - x) * (f32)(y) * n_inv; // bottomLeft
				const f32 f22 = (f32)(x) * (f32)(y) * n_inv; // bottomRight

				const f32 fA = 	(f32)topLeft.getAlpha() * f11 +
								(f32)topRight.getAlpha() * f21 +
								(f32)bottomRight.getAlpha() * f12 +
								(f32)bottomLeft.getAlpha() * f22;

				const f32 fR = 	(f32)topLeft.getRed() * f11 +
								(f32)topRight.getRed() * f21 +
								(f32)bottomRight.getRed() * f12 +
								(f32)bottomLeft.getRed() * f22;

				const f32 fG = 	(f32)topLeft.getGreen() * f11 +
								(f32)topRight.getGreen() * f21 +
								(f32)bottomRight.getGreen() * f12 +
								(f32)bottomLeft.getGreen() * f22;

				const f32 fB = 	(f32)topLeft.getBlue() * f11 +
								(f32)topRight.getBlue() * f21 +
								(f32)bottomRight.getBlue() * f12 +
								(f32)bottomLeft.getBlue() * f22;

				SColor color(
					(u32)irr::core::clamp( irr::core::round32(fA), 0, 255),
					(u32)irr::core::clamp( irr::core::round32(fR), 0, 255),
					(u32)irr::core::clamp( irr::core::round32(fG), 0, 255),
					(u32)irr::core::clamp( irr::core::round32(fB), 0, 255) );

				drawPixel( tmp, x, y, color, blend);
			}
		}
	}

	// drawing finished and copy dst to srcImage
	drawImage( dst, tmp, core::position2di(x1,y1), size, true, false);
	tmp->drop();
}


//! Bresenham circle with 1 color(s), if border <= 0 then filled/solid shape
void Tool::drawCircle( IImage* dst, const core::position2di& center,
	s32 radius,	const SColor& color, s32 border, bool blend)
{
	if ( !dst ) return;
	if ( radius < 0 ) return;

	else if ( radius == 0 )
	{
		drawPixel( dst, center.X, center.Y, color, blend);
	}
	else if ( radius == 1)
	{
		if ( border == 0 )
		{
			drawPixel( dst, center.X,center.Y,color,blend);
		}
		drawPixel( dst, center.X-1,center.Y,color,blend);
		drawPixel( dst, center.X,center.Y-1,color,blend);
		drawPixel( dst, center.X,center.Y+1,color,blend);
		drawPixel( dst, center.X+1,center.Y,color,blend);
	}
	else if ( radius == 2 )
	{
		if ( border == 0 )
		{
			drawPixel( dst, center.X-1,center.Y+1,color,blend);
			drawPixel( dst, center.X-1,center.Y,color,blend);
			drawPixel( dst, center.X,center.Y+1,color,blend);
			drawPixel( dst, center.X,center.Y,color,blend);
		}

		drawPixel( dst, center.X-2,center.Y+1,color,blend);
		drawPixel( dst, center.X-2,center.Y,  color,blend);
		drawPixel( dst, center.X-1,center.Y+2,color,blend);
		drawPixel( dst, center.X-1,center.Y-1,color,blend);
		drawPixel( dst, center.X,  center.Y+2,color,blend);
		drawPixel( dst, center.X,  center.Y-1,color,blend);
		drawPixel( dst, center.X+1,center.Y+1,color,blend);
		drawPixel( dst, center.X+1,center.Y,  color,blend);
	}
	else
	{
		// 'Bresenham' Algorithmus (Achtelkreis Symmetrie)
		// ohne Trigonometrische- und Wurzel-Funktionen
		// und Spiegelung auf Restliche 7/8

		if ( border == 0 ) // filled
		{
			s32 i,j,F;
			i = 0;
			j = radius;
			F = 1 - radius;

			while (i < j)
			{
				++i;
				if (F < 0)
				{
					F += (i<<1) - 1;
				}
				else
				{
					F += ((i - j)<<1);
					--j;
				}

				// Verbesserungen by Benjamin Hampe (c) 2012
				drawLine( dst, center.X-i, center.Y+j-1, center.X+i-1,center.Y+j-1, color, blend );
				drawLine( dst, center.X-j, center.Y+i-1, center.X+j-1,center.Y+i-1, color, blend );
				drawLine( dst, center.X-j, center.Y-i, center.X+j-1, center.Y-i, color, blend );
				drawLine( dst, center.X-i, center.Y-j, center.X+i-1, center.Y-j, color, blend );
			}
		}

		// 'Bresenham' Algorithmus (Achtelkreis Symmetrie)
		// ohne Trigonometrische- und Wurzel-Funktionen
		// und Spiegelung auf Restliche 7/8

		else if (border == 1)
		{
			s32 i,j,F;
			i = 0;
			j = radius;
			F = 1 - radius;

			while (i < j)
			{
				++i;
				if (F < 0)
				{
					F += (i<<1) - 1;
				}
				else
				{
					F += ((i - j)<<1);
					--j;
				}
				// Verbesserungen by Benjamin Hampe (c) 2012
				drawPixel( dst, center.X+i-1,center.Y-j,color, blend); // 1st quadrant
				drawPixel( dst, center.X+j-1,center.Y-i,color, blend); // 1st quadrant
				drawPixel( dst, center.X+i-1,center.Y+j-1,color, blend); // 2nd quadrant
				drawPixel( dst, center.X+j-1,center.Y+i-1,color, blend); // 2nd quadrant
				drawPixel( dst, center.X-i,center.Y+j-1,color, blend); // 3rd quadrant
				drawPixel( dst, center.X-j,center.Y+i-1,color, blend); // 3rd quadrant
				drawPixel( dst, center.X-i,center.Y-j,color, blend); // 4th quadrant
				drawPixel( dst, center.X-j,center.Y-i,color, blend); // 4th quadrant
			}
		}

		// by Benjamin Hampe
		// create circle from undistorted temporary image

		else if (border > 1)
		{
			if (radius - border > 1)
			{
				IImage* tmp = new CImage( dst->getColorFormat(), core::dimension2du( radius<<1, radius<<1) );
				if (!tmp)
					return;

//				tmp->enableColorKey();
				tmp->fill( 0 );
				drawCircle( tmp, core::position2di(radius,radius), radius, color, 0, blend);
				drawCircle( tmp, core::position2di(radius,radius), radius - border, 0, 0, blend);
				drawImage( tmp, dst, center - core::position2di(radius,radius), tmp->getDimension(), true, false);
				tmp->drop();
			}
		}
	}
}

//! Bresenham circle with 2 interpolated color(s) from center to outline
//! if (border <= 0) then filled/solid shape
//void ImageTool::drawCircle( IImage* dst, const core::position2di& center, s32 radius, const SColor& c1, const SColor& c2, s32 border, bool blend)
//{
//	// abort
//	if (!dst) return;
//
//	// abort
//	if (radius < 0)
//	{
//		return;
//	}
//	else if (radius == 0)
//	{
//		drawPixel( dst,center.X,center.Y,c2,blend);
//		return;
//	}
//	else if (radius == 1)
//	{
//		drawPixel( dst,center.X,center.Y,c2,blend);
//		drawPixel( dst,center.X,center.Y-1,c1,blend);
//		drawPixel( dst,center.X,center.Y+1,c1,blend);
//		drawPixel( dst,center.X+1,center.Y,c1,blend);
//		drawPixel( dst,center.X-1,center.Y,c1,blend);
//		return;
//	}
//	else
//	{
//		if (border==0) // filled
//		{
//			IImage* tmp = new CImage( dst->getColorFormat(), core::dimension2du( radius<<1, radius<<1) );
//			if (!tmp)
//				return;
//			tmp->fill( 0 );
//			drawCircle( tmp, core::position2di(radius,radius), radius, SColor(255,255,255,255), 0, blend);
//
//			const f32 fA = (f32)c1.getAlpha(), fdA = (f32)c2.getAlpha() - fA;
//			const f32 fR = (f32)c1.getRed(), fdR = (f32)c2.getRed() - fR;
//			const f32 fG = (f32)c1.getGreen(), fdG = (f32)c2.getGreen() - fG;
//			const f32 fB = (f32)c1.getBlue(), fdB = (f32)c2.getBlue() - fB;
//			const SColor white(255,255,255,255);
//			const f32 fw = 0.5f*(f32)tmp->getDimension().Width;
//			const f32 fh = 0.5f*(f32)tmp->getDimension().Height;
//			const f32 invRadius = irr::core::reciprocal( (f32)radius );
//
//			const core::dimension2du& Size = tmp->getDimension();
//			for (u32 y = 0; y < Size.Height; y++)
//			{
//				for (u32 x = 0; x < Size.Width; x++)
//				{
//					const SColor& colorNow = tmp->getPixel(x,y);
//					if (colorNow == white)
//					{
//						const f32 dx = (f32)x - fw;
//						const f32 dy = (f32)y - fh;
//						f32 f = squareroot( dx*dx + dy*dy ) * invRadius;
//						u32 uA = (u32)irr::core::s32_clamp( irr::core::round32( fA + f*fdA ), 0, 255);
//						u32 uR = (u32)irr::core::s32_clamp( irr::core::round32( fR + f*fdR ), 0, 255);
//						u32 uG = (u32)irr::core::s32_clamp( irr::core::round32( fG + f*fdG ), 0, 255);
//						u32 uB = (u32)irr::core::s32_clamp( irr::core::round32( fB + f*fdB ), 0, 255);
//						tmp->setPixel( x, y, SColor(uA,uR,uG,uB), blend );
//					}
//				}
//			}
//
//			drawImage( tmp, dst, center - core::position2di(radius,radius), tmp->getDimension(), true, false);
//			tmp->drop();
//			return;
//		}
//		else if (border == 1) // outline with color c1
//		{
//			drawCircle( dst, center, radius, c1, 1, blend);
//		}
//		else if (border > 1)
//		{
//			if (radius - border > 0)
//			{
//				IImage* tmp = new CImage( dst->getColorFormat(), core::dimension2du( radius<<1, radius<<1) );
//				if (!tmp)
//					return;
//
//				const SColor black(  0,  0,  0,  0);
//				const SColor white(255,255,255,255);
//
//				tmp->fill( black );
//				drawCircle( tmp, core::position2di(radius,radius), radius, white, 0, blend);
//				drawCircle( tmp, core::position2di(radius,radius), radius-border, black, 0, blend);
//
//				const f32 fA = (f32)c1.getAlpha(), fdA = (f32)c2.getAlpha() - fA;
//				const f32 fR = (f32)c1.getRed(), fdR = (f32)c2.getRed() - fR;
//				const f32 fG = (f32)c1.getGreen(), fdG = (f32)c2.getGreen() - fG;
//				const f32 fB = (f32)c1.getBlue(), fdB = (f32)c2.getBlue() - fB;
//
//				const core::dimension2du& Size = tmp->getDimension();
//
//				const f32 fw = 0.5f*(f32)Size.Width;
//				const f32 fh = 0.5f*(f32)Size.Height;
//				const f32 invRadius = irr::core::reciprocal( (f32)border );
//				const s32 innerCircle = radius-border;
//
//				for (u32 y = 0; y < Size.Height; y++)
//				{
//					for (u32 x = 0; x < Size.Width; x++)
//					{
//						const SColor& colorNow = tmp->getPixel(x,y);
//						if (colorNow == white)
//						{
//							const f32 dx = (f32)x - fw;
//							const f32 dy = (f32)y - fh;
//
//							f32 f = (squareroot( dx*dx + dy*dy ) - (f32)innerCircle ) * invRadius;
//							u32 uA = (u32)irr::core::s32_clamp( irr::core::round32( fA + f*fdA ), 0, 255);
//							u32 uR = (u32)irr::core::s32_clamp( irr::core::round32( fR + f*fdR ), 0, 255);
//							u32 uG = (u32)irr::core::s32_clamp( irr::core::round32( fG + f*fdG ), 0, 255);
//							u32 uB = (u32)irr::core::s32_clamp( irr::core::round32( fB + f*fdB ), 0, 255);
//							tmp->setPixel( x, y, SColor(uA,uR,uG,uB), blend );
//						}
//					}
//				}
//
//				drawImage( tmp, dst, center - core::position2di(radius,radius), tmp->getDimension(), true, false);
//				tmp->drop();
//			}
//		}
//	}
//}


//! draw a Bresenham-ellipse, 1 color, filled or outlined, option to blend
void Tool::drawEllipse( IImage* dst, const core::position2di& center, s32 rx, s32 ry, const SColor& color, s32 border, bool blend)

{
	if (!dst) return; // abort
//			const s32 w = dest->getDimension().Width;
//			const s32 h = dest->getDimension().Height;

	// Abbruchbedingung
	if (rx < 1 && ry < 1) return;
	if (rx==0) rx = ry;
	if (ry==0) ry = rx;

	if (rx==ry)
		drawCircle( dst, center, rx, color, border, blend);

	//if (rw==1 && rh==1) dest->setPixel(x,y,color);

	const s32 rx2=rx*rx; // Ellipsen Radien Quadrate
	const s32 ry2=ry*ry; // Ellipsen Radien Quadrate
	s32 x = center.X;
	s32 y = center.Y;
//	const s32 mx = center.X;	 // Ellipsen Mittelpunkt
//	const s32 my = center.Y; 	 // Ellipsen Mittelpunkt

	// Bresenham Anfangswerte
	// Trick: nur 1/4 Ellipse berechne und restliche 3/4 durch Spiegelung (gerade Ellipse!!!)
	s32 ddF_x=0;
	s32 ddF_y=((rx2*ry)<<1);
	x=0;
	y=ry;

	// Bresenham Alghorithmus
	s32 F=irr::core::round32((f32)(ry2-rx2*ry)+(f32)rx2*0.25f);
	while( ddF_x < ddF_y )
	{
		if (F >= 0)
		{
			y     -= 1;        // south
			ddF_y -= (rx2<<1);
			F     -= ddF_y;
		}
		x     += 1;          // east
		ddF_x += (ry2<<1);
		F     += ddF_x + ry2;

		if (border==0)
		{
			drawLine( dst, center.X-x, center.Y+y, center.X+x, center.Y+y, color, blend);
			drawLine( dst, center.X-x, center.Y-y, center.X+x, center.Y-y, color, blend);
		}
		else
		{
			drawPixel( dst, x+center.X, y+center.Y, color, blend);
			drawPixel( dst, -x+center.X, y+center.Y, color, blend);
			drawPixel( dst, x+center.X, -y+center.Y, color, blend);
			drawPixel( dst, -x+center.X, -y+center.Y, color, blend);

			// Spiegelung mit meinen Anpassungen
			// drawPixel( dst, x+mx, y+my, color, blend);
			// drawPixel( dst, -x+mx+1, y+my, color, blend);
			// drawPixel( dst, x+mx, -y+my+1, color, blend);
			// drawPixel( dst, -x+mx+1, -y+my+1, color, blend);
		}
	}

	// Bresenham Alghorithmus
	F = irr::core::round32((f32)ry2*((f32)x+0.5f)*((f32)x+0.5f) + (f32)(rx2*(y-1)*(y-1) - rx2*ry2));
	while( y > 0 )
	{
		if(F <= 0)
		{
			x     += 1;        // east
			ddF_x += (ry2<<1);
			F     += ddF_x;
		}
		y     -= 1;           // south
		ddF_y -= (rx2<<1);
		F     += rx2 - ddF_y;

		if (border==0)
		{
			drawLine( dst, center.X-x, center.Y+y, center.X+x, center.Y+y, color, blend);
			drawLine( dst, center.X-x, center.Y-y, center.X+x, center.Y-y, color, blend);
		}
		else
		{
			drawPixel( dst, x+center.X, y+center.Y, color, blend);
			drawPixel( dst, -x+center.X, y+center.Y, color, blend);
			drawPixel( dst, x+center.X, -y+center.Y, color, blend);
			drawPixel( dst, -x+center.X, -y+center.Y, color, blend);

			// Spiegelung mit meinen Anpassungen
//			drawPixel( dst, x+mx, y+my, color, blend);
//			drawPixel( dst, -x+mx+1, y+my, color, blend);
//			drawPixel( dst, x+mx, -y+my+1, color, blend);
//			drawPixel( dst, -x+mx+1, -y+my+1, color, blend);
		}
	}
}

//! Bresenham ellipse
void Tool::drawEllipse( IImage* dst, const core::position2di& center, s32 rx, s32 ry, const SColor& c1, const SColor& c2, s32 border, bool blend)
{
	if (!dst) return; // abort
//			const s32 w = dest->getDimension().Width;
//			const s32 h = dest->getDimension().Height;

	// Abbruchbedingung
	if (rx < 1 && ry < 1) return;
	if (rx==0) rx = ry;
	if (ry==0) ry = rx;

	if (rx==ry)
		drawCircle( dst, center, rx, c1, border, blend);

	//if (rw==1 && rh==1) dest->setPixel(x,y,color);

	const s32 rx2=rx*rx; // Ellipsen Radien Quadrate
	const s32 ry2=ry*ry; // Ellipsen Radien Quadrate
	s32 x = center.X;
	s32 y = center.Y;
//	const s32 mx = center.X;	 // Ellipsen Mittelpunkt
//	const s32 my = center.Y; 	 // Ellipsen Mittelpunkt

	// Bresenham Anfangswerte
	// Trick: nur 1/4 Ellipse berechne und restliche 3/4 durch Spiegelung (gerade Ellipse!!!)
	s32 ddF_x=0;
	s32 ddF_y=((rx2*ry)<<1);
	x=0;
	y=ry;

	// Bresenham Alghorithmus
	s32 F=irr::core::round32((f32)(ry2-rx2*ry)+(f32)rx2*0.25f);
	while( ddF_x < ddF_y )
	{
		if (F >= 0)
		{
			y     -= 1;        // south
			ddF_y -= (rx2<<1);
			F     -= ddF_y;
		}
		x     += 1;          // east
		ddF_x += (ry2<<1);
		F     += ddF_x + ry2;

		if (border==0)
		{
			drawLine( dst, center.X-x, center.Y+y, center.X+x, center.Y+y, c1, blend);
			drawLine( dst, center.X-x, center.Y-y, center.X+x, center.Y-y, c1, blend);
		}
		else
		{
			drawPixel( dst, x+center.X, y+center.Y, c1, blend);
			drawPixel( dst, -x+center.X, y+center.Y, c1, blend);
			drawPixel( dst, x+center.X, -y+center.Y, c1, blend);
			drawPixel( dst, -x+center.X, -y+center.Y, c1, blend);
		}
	}

	// Bresenham Alghorithmus
	F = irr::core::round32((f32)ry2*((f32)x+0.5f)*((f32)x+0.5f) + (f32)(rx2*(y-1)*(y-1) - rx2*ry2));
	while( y > 0 )
	{
		if(F <= 0)
		{
			x     += 1;        // east
			ddF_x += (ry2<<1);
			F     += ddF_x;
		}
		y     -= 1;           // south
		ddF_y -= (rx2<<1);
		F     += rx2 - ddF_y;

		if (border==0)
		{
			drawLine( dst, center.X-x, center.Y+y, center.X+x, center.Y+y, c1, blend);
			drawLine( dst, center.X-x, center.Y-y, center.X+x, center.Y-y, c1, blend);
		}
		else
		{
			drawPixel( dst, x+center.X, y+center.Y, c1, blend);
			drawPixel( dst, -x+center.X, y+center.Y, c1, blend);
			drawPixel( dst, x+center.X, -y+center.Y, c1, blend);
			drawPixel( dst, -x+center.X, -y+center.Y, c1, blend);
		}
	}
}

} // end namespace video

} // end namespace irr
