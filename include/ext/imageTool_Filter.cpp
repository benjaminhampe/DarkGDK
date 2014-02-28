// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include <imageTool.h>

namespace irr
{

namespace video
{

IImage* Tool::filter( IImage* dst, video::E_IMAGE_FILTER myFilter, u32 param)
{
	switch (myFilter)
	{
		case video::EIF_SHARPEN: return filter( dst, new video::CImageFilterSharpenf, true ); break;
		case video::EIF_SMOOTHEN: return filter( dst, new video::CImageFilterSmoothingf, true ); break;
		case video::EIF_BLUR: return filter( dst, new video::CImageFilterGaussianBlurf, true ); break;
		case video::EIF_MEAN_REMOVAL: return filter( dst, new video::CImageFilterMeanRemovalf, true ); break;
		case video::EIF_EMBOSS: return filter( dst, new video::CImageFilterEmbossf, true ); break;
		case video::EIF_EMBOSS_ALL: return filter( dst, new video::CImageFilterEmbossAllf, true ); break;
		case video::EIF_EMBOSS_LOSSY: return filter( dst, new video::CImageFilterEmbossLossyf, true ); break;
		case video::EIF_EMBOSS_H: return filter( dst, new video::CImageFilterEmbossHf, true ); break;
		case video::EIF_EMBOSS_V: return filter( dst, new video::CImageFilterEmbossVf, true ); break;
		case video::EIF_EDGE_DETECT: return filter( dst, new video::CImageFilterEdgeDetectf, true ); break;
		case video::EIF_SEPIA: return sepia(dst); break;
		case video::EIF_INVERT: return invert(dst, ECP_ALL); break;
		case video::EIF_BLACKWHITE: return blackwhite(dst, param); break;
		case video::EIF_GREYSCALES: return greyscales(dst); break;
		case video::EIF_AVERAGE: return average(dst); break;
		case video::EIF_HDR: return hdr(dst, param); break;
		case video::EIF_SATURATE: return saturate(dst); break;
		default: break;
	}
	return 0;
}

IImage* Tool::filter( IImage* src, video::CImageFilter<f32>* filter, bool deleteFilter )
{
    if (!src) return 0;
    if (!filter) return 0;
	const core::dimension2du& Size = src->getDimension();

    IImage* dst = new CImage( src->getColorFormat(), Size );

    for (s32 y=0; y<(s32)Size.Height; ++y)
    {
        for (s32 x=0; x<(s32)Size.Width; ++x)
        {
            // use my function getPixel()! to be save at bounds, returns pixel at nearest pos
            SColor c00 = getPixel(src, x-1,y-1);
            SColor c01 = getPixel(src, x  ,y-1);
            SColor c02 = getPixel(src, x+1,y-1);
            SColor c10 = getPixel(src, x-1,y  );
            SColor c11 = getPixel(src, x  ,y  ); // current pixel (x,y)
            SColor c12 = getPixel(src, x+1,y  );
            SColor c20 = getPixel(src, x-1,y+1);
            SColor c21 = getPixel(src, x  ,y+1);
            SColor c22 = getPixel(src, x+1,y+1);

            f32 r =	(f32)c00.getRed()*filter->get(0,0)+
                    (f32)c01.getRed()*filter->get(0,1)+
                    (f32)c02.getRed()*filter->get(0,2)+
                    (f32)c10.getRed()*filter->get(1,0)+
                    (f32)c11.getRed()*filter->get(1,1)+
                    (f32)c12.getRed()*filter->get(1,2)+
                    (f32)c20.getRed()*filter->get(2,0)+
                    (f32)c21.getRed()*filter->get(2,1)+
                    (f32)c22.getRed()*filter->get(2,2);

            f32 g = (f32)c00.getGreen()*filter->get(0,0)+
                    (f32)c01.getGreen()*filter->get(0,1)+
                    (f32)c02.getGreen()*filter->get(0,2)+
                    (f32)c10.getGreen()*filter->get(1,0)+
                    (f32)c11.getGreen()*filter->get(1,1)+
                    (f32)c12.getGreen()*filter->get(1,2)+
                    (f32)c20.getGreen()*filter->get(2,0)+
                    (f32)c21.getGreen()*filter->get(2,1)+
                    (f32)c22.getGreen()*filter->get(2,2);

            f32 b = (f32)c00.getBlue()*filter->get(0,0)+
                    (f32)c01.getBlue()*filter->get(0,1)+
                    (f32)c02.getBlue()*filter->get(0,2)+
                    (f32)c10.getBlue()*filter->get(1,0)+
                    (f32)c11.getBlue()*filter->get(1,1)+
                    (f32)c12.getBlue()*filter->get(1,2)+
                    (f32)c20.getBlue()*filter->get(2,0)+
                    (f32)c21.getBlue()*filter->get(2,1)+
                    (f32)c22.getBlue()*filter->get(2,2);

            drawPixel(dst, x, y, SColor(c11.getAlpha(),
				(u32)core::s32_clamp( core::round32(r), 0, 255),
				(u32)core::s32_clamp( core::round32(g), 0, 255),
				(u32)core::s32_clamp( core::round32(b), 0, 255)));
        }
    }

	if (deleteFilter)
		delete filter;

    return dst;
}


IImage* Tool::sepia( IImage* src )
{
	return 0;
}

IImage* Tool::invert( IImage* src, E_COLOR_PLANE planes )
{
	return 0;
}

IImage* Tool::blackwhite( IImage* src, u32 threshold )
{
	if (!src)
		return 0;

	IImage* dst = new CImage( src->getColorFormat(), src->getDimension() );
	if (!dst)
		return 0;

	if (threshold<1)
	{
		dst->fill( SColor(255,0,0,0) );
		return dst;
	}
	else if (threshold>=255)
	{
		dst->fill( SColor(255,255,255,255) );
		return dst;
	}
	else
	{
		const core::dimension2du& Size = src->getDimension();
		for (u32 y=0; y<Size.Height; y++)
		{
			for (u32 x=0; x<Size.Width; x++)
			{
				SColor color = src->getPixel(x,y);
				if (((color.getRed() + color.getGreen() + color.getBlue()) / 3) >= threshold)
					color.set(color.getAlpha(),255,255,255);
				else
					color.set(color.getAlpha(),0,0,0);
				dst->setPixel(x,y,color,false);
			}
		}
	}
	return dst;
}


IImage* Tool::greyscales( IImage* src )
{
	return 0;
}


IImage* Tool::average( IImage* src )
{
	if (!src)
		return 0;

	core::dimension2du Size = src->getDimension();
	ECOLOR_FORMAT Format = src->getColorFormat();

	IImage* dst = new CImage( Format, Size );
	if (dst)
	{
		dst->fill( SColor(0,0,0,0) );
		for (u32 y=0; y<Size.Height; y++)
		{
			for (u32 x=0; x<Size.Width; x++)
			{
				SColor color = src->getPixel(x,y);
				const u32 average = color.getAverage();
				color.set( color.getAlpha(), average, average, average);
				dst->setPixel(x,y,color,false);
			}
		}

	}
	return dst;
}


IImage* Tool::hdr( IImage* src, u32 threshold )
{
	return 0;
}

//! returns a saturated image
IImage* Tool::saturate( IImage* src )
{
	if (!src)
		return 0;

	IImage* dst = new CImage( src->getColorFormat(), src->getDimension() );
	if (!dst)
		return 0;

	u8 max_A(0);
	u8 max_R(0);
	u8 max_G(0);
	u8 max_B(0);
	u8 min_A(255);
	u8 min_R(255);
	u8 min_G(255);
	u8 min_B(255);

	const core::dimension2du& Size = src->getDimension();
	for (u32 y=0; y<Size.Height; y++)
	{
		for (u32 x=0; x<Size.Width; x++)
		{
			const SColor& color = src->getPixel(x,y);

			if ( min_A > color.getAlpha()) min_A = color.getAlpha();
			if ( min_R > color.getRed()) min_R = color.getRed();
			if ( min_G > color.getGreen()) min_G = color.getGreen();
			if ( min_B > color.getBlue()) min_B = color.getBlue();

			if ( max_A < color.getAlpha()) max_A = color.getAlpha();
			if ( max_R < color.getRed()) max_R = color.getRed();
			if ( max_G < color.getGreen()) max_G = color.getGreen();
			if ( max_B < color.getBlue()) max_B = color.getBlue();
		}
	}

	const u32 A_diff = max_A-min_A;
	const u32 R_diff = max_R-min_R;
	const u32 G_diff = max_G-min_G;
	const u32 B_diff = max_B-min_B;

	for (u32 y=0; y<Size.Height; y++)
	{
		for (u32 x=0; x<Size.Width; x++)
		{
			SColor color = src->getPixel(x,y);
			u32 A = (u32)core::clamp( core::round32( 255.0f*color.getAlpha()/(f32)A_diff ), 0, 255);
			u32 R = (u32)core::clamp( core::round32( 255.0f*color.getRed()/(f32)R_diff ), 0, 255);
			u32 G = (u32)core::clamp( core::round32( 255.0f*color.getGreen()/(f32)G_diff ), 0, 255);
			u32 B = (u32)core::clamp( core::round32( 255.0f*color.getBlue()/(f32)B_diff ), 0, 255);
			dst->setPixel( x,y, SColor(A,R,G,B), false);
		}
	}

	return dst;
}

//! returns a sharpened image
IImage* Tool::sharpen( IImage* src, f32 value )
{
	IImage* dst = new CImage( src->getColorFormat(), src->getDimension(), 0, false, true);
	if (!dst)
	{
		return 0;
	}
	filter(dst, new video::CImageFilterSharpenf(), true);
    return dst;
}


} // end namespace video

} // end namespace irr
