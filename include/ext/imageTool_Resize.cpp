// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include <imageTool.h>


namespace irr
{

namespace video
{

SColor Tool::getNearestPixel( IImage* src, f32 fx, f32 fy )
{
	const s32 i=core::round32(fx);
	const s32 j=core::round32(fy);
	return getPixelAlways(src,i,j);
}

SColor Tool::getBilinearPixelFast( IImage* src, f32 fx, f32 fy )
{
	const s32 i=(s32)fx;
	const s32 j=(s32)fy;
	const f32 x=fx-(f32)i;
	const f32 y=fy-(f32)j;
	const core::dimension2du& Size = src->getDimension();
	const s32 ii = (i+1>=(s32)Size.Width) ? i : i+1;
	const s32 jj = (j+1>=(s32)Size.Height) ? j : j+1;
	const SColor& cA=getPixelAlways(src,i,j);
	const SColor& cB=getPixelAlways(src,ii,j);
	const SColor& cC=getPixelAlways(src,ii,jj);
	const SColor& cD=getPixelAlways(src,i,jj);
	const f32 rA=(f32)cA.getRed();
	const f32 rB=(f32)cB.getRed();
	const f32 rC=(f32)cC.getRed();
	const f32 rD=(f32)cD.getRed();
	const f32 gA=(f32)cA.getGreen();
	const f32 gB=(f32)cB.getGreen();
	const f32 gC=(f32)cC.getGreen();
	const f32 gD=(f32)cD.getGreen();
	const f32 bA=(f32)cA.getBlue();
	const f32 bB=(f32)cB.getBlue();
	const f32 bC=(f32)cC.getBlue();
	const f32 bD=(f32)cD.getBlue();
	const f32 e=(1.0f-x);
	const f32 f=(1.0f-y);
	const f32 fr = rA*e*f+rB*x*f+rC*x*y+rD*e*y;
	const f32 fg = gA*e*f+gB*x*f+gC*x*y+gD*e*y;
	const f32 fb = bA*e*f+bB*x*f+bC*x*y+bD*e*y;
	return SColor(255,(u32)fr,(u32)fg,(u32)fb);
}

SColor Tool::getBilinearPixel( IImage* src, f32 fx, f32 fy, E_COLOR_PLANE planes, SColor* colorKey)
{
	const s32 i=(s32)fx;     // dirty round (fast)
	const s32 j=(s32)fy;     // dirty round (fast)
	const f32 x=fx-(f32)i;   // dirty difference from pixel (fast)
	const f32 y=fy-(f32)j;   // dirty difference from pixel (fast)
	const f32 e=(1.0f-x);    // A+AB*t = B+AB*(1-t) = B-AB*t = B+BA*t
	const f32 f=(1.0f-y);    // A+AB*t = B+AB*(1-t) = B-AB*t = B+BA*t
	const SColor& A=getPixelAlways(src, i,   j); // read pixel, even if out of bounds (gets most nearest pixel)
	const SColor& B=getPixelAlways(src, i+1, j); // read pixel, even if out of bounds (gets most nearest pixel)
	const SColor& C=getPixelAlways(src, i+1, j+1); // read pixel, even if out of bounds (gets most nearest pixel)
	const SColor& D=getPixelAlways(src, i,   j+1); // read pixel, even if out of bounds (gets most nearest pixel)

    if (colorKey && ((A==*colorKey) || (B==*colorKey) || (C==*colorKey) || (D==*colorKey)))
        return *colorKey;

    u32 a(0),r(0),g(0),b(0);

    if (planes & ECP_ALPHA)
    {   f32 fa = A.getAlpha()*e*f+B.getAlpha()*x*f+C.getAlpha()*x*y+D.getAlpha()*e*y;
        a = (u32)core::s32_clamp( (s32)core::round32(fa), 0, 255);
    }
    if (planes & ECP_RED)
    {   f32 fr = A.getRed()*e*f+B.getRed()*x*f+C.getRed()*x*y+D.getRed()*e*y;
        r = (u32)core::s32_clamp( (s32)core::round32(fr), 0, 255);
    }
    if (planes & ECP_GREEN)
    {   f32 fg = A.getGreen()*e*f+B.getGreen()*x*f+C.getGreen()*x*y+D.getGreen()*e*y;
        g = (u32)core::s32_clamp( (s32)core::round32(fg), 0, 255);
    }
    if (planes & ECP_BLUE)
    {   f32 fb = A.getBlue()*e*f+B.getBlue()*x*f+C.getBlue()*x*y+D.getBlue()*e*y;
        b = (u32)core::s32_clamp( (s32)core::round32(fb), 0, 255);
    }
    return SColor(a,r,g,b);
}

f32 Tool::getBicubicFactor(const f32& arg)
{
	const f32 f1 = arg>0.0f?arg:0.0f; const f32 f2 = arg-1.0f; const f32 f3 = arg+1.0f; const f32 f4 = arg+2.0f;
	const f32 n1 = f2>0.0f?f2:0.0f;	const f32 n2 = f3>0.0f?f3:0.0f;	const f32 n3 = f4>0.0f?f4:0.0f;
	return (f32)((n3*n3*n3 - 4.0f*n2*n2*n2 + 6.0f*f1*f1*f1 - 4.0f*n1*n1*n1)/6.0f);
}

SColor Tool::getBicubicPixel( IImage* src, f32 fx, f32 fy, E_COLOR_PLANE planes, SColor* colorKey)
{
	// abort, if nothing todo
	if (planes == ECP_NONE)
		return ((colorKey) ? (*colorKey) : SColor(0,0,0,0));

	// calculate 4x4 indices
	const s32 x1=(s32)fx-(fx>=0?0:1);	const s32 x2=x1-1;	const s32 x3=x1+1;	const s32 x4=x3+1;
	const s32 y1=(s32)fy-(fy>=0?0:1);	const s32 y2=y1-1;  const s32 y3=y1+1;	const s32 y4=y3+1;
	const f32 dx=fx-x1;	const f32 dy=fy-y1;

	// 4x4 Pixels for bicubic Interpolation
	const SColor& C0 = getPixelAlways(src, x2,y2);	const SColor& C1 = getPixelAlways(src, x1,y2);
	const SColor& C2 = getPixelAlways(src, x3,y2);	const SColor& C3 = getPixelAlways(src, x4,y2);
	const SColor& C4 = getPixelAlways(src, x2,y1);	const SColor& C5 = getPixelAlways(src, x1,y1);
	const SColor& C6 = getPixelAlways(src, x3,y1);	const SColor& C7 = getPixelAlways(src, x4,y1);
	const SColor& C8 = getPixelAlways(src, x2,y3);	const SColor& C9 = getPixelAlways(src, x1,y3);
	const SColor& CA = getPixelAlways(src, x3,y3);	const SColor& CB = getPixelAlways(src, x4,y3);
	const SColor& CC = getPixelAlways(src, x2,y4);	const SColor& CD = getPixelAlways(src, x1,y4);
	const SColor& CE = getPixelAlways(src, x3,y4);	const SColor& CF = getPixelAlways(src, x4,y4);

	// abort, if nothing todo
	// --> return ColorKey as dst, if min 1 out of 16 pixel equals ColorKey --> sharp edges, but some pixel are lost
	if (colorKey && ((C0==*colorKey) || (C1==*colorKey) || (C2==*colorKey) || (C3==*colorKey) ||
					(C4==*colorKey) || (C5==*colorKey) || (C6==*colorKey) || (C7==*colorKey) ||
                    (C8==*colorKey) || (C9==*colorKey) || (CA==*colorKey) || (CB==*colorKey) ||
                    (CC==*colorKey) || (CD==*colorKey) || (CE==*colorKey) || (CF==*colorKey))) return *colorKey;

	// calculate factors
	const f32 Fx1 = getBicubicFactor(-1.0f-dx );	const f32 Fx2 = getBicubicFactor( 0.0f+dx );
	const f32 Fx3 = getBicubicFactor( 1.0f-dx );	const f32 Fx4 = getBicubicFactor( 2.0f-dx );
	const f32 Fy1 = getBicubicFactor( dy+1.0f );	const f32 Fy2 = getBicubicFactor( dy+0.0f );
	const f32 Fy3 = getBicubicFactor( dy-1.0f );	const f32 Fy4 = getBicubicFactor( dy-2.0f );

	// calculate final color, default SColor(0,0,0,0)
	u32 uA(0), uR(0), uG(0), uB(0);
	if (planes & ECP_ALPHA)
	{
		f32 fa = Fx1*Fy1*C0.getAlpha() + Fx2*Fy1*C1.getAlpha() + Fx3*Fy1*C2.getAlpha() + Fx4*Fy1*C3.getAlpha() +
		Fx1*Fy2*C4.getAlpha() + Fx2*Fy2*C5.getAlpha() + Fx3*Fy2*C6.getAlpha() + Fx4*Fy2*C7.getAlpha() +
        Fx1*Fy3*C8.getAlpha() + Fx2*Fy3*C9.getAlpha() + Fx3*Fy3*CA.getAlpha() + Fx4*Fy3*CB.getAlpha() +
        Fx1*Fy4*CC.getAlpha() + Fx2*Fy4*CD.getAlpha() + Fx3*Fy4*CE.getAlpha() + Fx4*Fy4*CF.getAlpha();
        uA = (u32)core::clamp( core::round32(fa), 0, 255);
	}

	if (planes & ECP_RED)
	{
		f32 fr = Fx1*Fy1*C0.getRed() + Fx2*Fy1*C1.getRed() + Fx3*Fy1*C2.getRed() + Fx4*Fy1*C3.getRed() +
		Fx1*Fy2*C4.getRed() + Fx2*Fy2*C5.getRed() + Fx3*Fy2*C6.getRed() + Fx4*Fy2*C7.getRed() +
		Fx1*Fy3*C8.getRed() + Fx2*Fy3*C9.getRed() + Fx3*Fy3*CA.getRed() + Fx4*Fy3*CB.getRed() +
		Fx1*Fy4*CC.getRed() + Fx2*Fy4*CD.getRed() + Fx3*Fy4*CE.getRed() + Fx4*Fy4*CF.getRed();
		uR = (u32)core::clamp( core::round32(fr), 0, 255);
	}

	if (planes & ECP_GREEN)
	{
		f32 fg = Fx1*Fy1*C0.getGreen() + Fx2*Fy1*C1.getGreen() + Fx3*Fy1*C2.getGreen() + Fx4*Fy1*C3.getGreen() +
		Fx1*Fy2*C4.getGreen() + Fx2*Fy2*C5.getGreen() + Fx3*Fy2*C6.getGreen() + Fx4*Fy2*C7.getGreen() +
		Fx1*Fy3*C8.getGreen() + Fx2*Fy3*C9.getGreen() + Fx3*Fy3*CA.getGreen() + Fx4*Fy3*CB.getGreen() +
		Fx1*Fy4*CC.getGreen() + Fx2*Fy4*CD.getGreen() + Fx3*Fy4*CE.getGreen() + Fx4*Fy4*CF.getGreen();
        uG = (u32)core::clamp( core::round32(fg), 0, 255);
	}

	if (planes & ECP_BLUE)
	{
        f32 fb = Fx1*Fy1*C0.getBlue() + Fx2*Fy1*C1.getBlue() + Fx3*Fy1*C2.getBlue() + Fx4*Fy1*C3.getBlue() +
        Fx1*Fy2*C4.getBlue() + Fx2*Fy2*C5.getBlue() + Fx3*Fy2*C6.getBlue() + Fx4*Fy2*C7.getBlue() +
        Fx1*Fy3*C8.getBlue() + Fx2*Fy3*C9.getBlue() + Fx3*Fy3*CA.getBlue() + Fx4*Fy3*CB.getBlue() +
        Fx1*Fy4*CC.getBlue() + Fx2*Fy4*CD.getBlue() + Fx3*Fy4*CE.getBlue() + Fx4*Fy4*CF.getBlue();
        uB = (u32)core::clamp( core::round32(fb), 0, 255);
	}

	// return final color
    return SColor(uA,uR,uG,uB);
}

IImage* Tool::resize( IImage* src, const core::dimension2du& newSize, s32 scaleOp, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen)
{
	if (!src)
		return 0;

    switch((E_IMAGE_SCALE_OPERATION)scaleOp)
    {
        case EISO_FAST: return resizeFast(src,newSize,planes,bPreserveAspect,bSharpen); break;
        case EISO_NEAREST: return resizeNearest(src,newSize,planes,bPreserveAspect,bSharpen); break;
        case EISO_BILINEAR: return resizeBilinear(src,newSize,planes,bPreserveAspect,bSharpen); break;
        case EISO_BICUBIC: return resizeBicubic(src,newSize,planes,bPreserveAspect,bSharpen); break;
        default: break;
    }
    return 0;
}

IImage* Tool::resizeNearest( IImage* src, const core::dimension2du& newSize, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen)
{
	/// error
	if (!src)
		return 0;

	/// error
	if (newSize == core::dimension2du(0,0) )
	{
		return 0;
	}

	/// get size from source image
	const core::dimension2du& Size = src->getDimension();

	/// just clone it when same size requested -> likely faster
	if (newSize == Size)
	{
		return cloneImage(src);
	}

	/// calculate size of final image
    core::dimension2du nSize = newSize;

	// calculate width from aspect-ratio
	if (nSize.Width == 0)
		nSize.Width = (u32)( (f32)nSize.Height * (f32)Size.Width * core::reciprocal( (f32)Size.Height ) );

	// calculate height from aspect-ratio
	if (nSize.Height == 0)
		nSize.Height = (u32)( (f32)nSize.Width * (f32)Size.Height * core::reciprocal( (f32)Size.Width ) );

    /// create final image
	IImage* dst = (IImage*)new CImage(src->getColorFormat(), nSize);

	/// error, could not create final image
	if (!dst)
        return 0;

	/// loop pixel
	const f32 zoomXinv = (f32)Size.Width/(f32)nSize.Width;
	const f32 zoomYinv = (f32)Size.Height/(f32)nSize.Height;

	for (u32 y=0; y<nSize.Height; y++)
	{
		for (u32 x=0; x<nSize.Width; x++)
		{
			u32 u=(u32)core::round32( (f32)x * zoomXinv); // interpolate pos of current pixel in img to nearest of src
			u32 v=(u32)core::round32( (f32)y * zoomYinv); // interpolate pos of current pixel in img to nearest of src
			SColor color = getPixelAlways(src,u,v);

			if ( planes == ECP_ALL )
			{
				// change nothing on color
			}
			else if( planes==ECP_RGB )
			{
				color.setAlpha(255);
			}
			else
			{
				if ( ! (planes & ECP_ALPHA) )
				{
					color.setAlpha(255);
				}
				if ( ! (planes & ECP_RED) )
				{
					color.setRed(0);
				}
				if ( ! (planes & ECP_GREEN) )
				{
					color.setGreen(0);
				}
				if ( ! (planes & ECP_BLUE) )
				{
					color.setBlue(0);
				}
			}

			// write color to image
			dst->setPixel(x,y,color,false);
        }
	}

	/// old, most likely inefficient code
//
//    const f32 zoomX = ((f32)nSize.Width)/((f32)Size.Width);
//	const f32 zoomY = ((f32)nSize.Height)/((f32)Size.Height);
//
//	if (planes==ECP_RGB)
//	{
//		for (u32 y=0; y<nSize.Height; y++)
//        {
//            for (u32 x=0; x<nSize.Width; x++)
//            {
//                u32 u=(u32)((f32)x/zoomX); // interpolate pos of current pixel in img to nearest of src
//                u32 v=(u32)((f32)y/zoomY); // interpolate pos of current pixel in img to nearest of src
//                SColor color = getPixelAlways(src,u,v);
//                color.setAlpha(255);
//                dst->setPixel(x,y,color,false);
//            }
//        }
//	}
//    else
//	{
//		for (u32 y=0; y<nSize.Height; y++)
//        {
//            for (u32 x=0; x<nSize.Width; x++)
//            {
//                u32 u=(u32)((f32)x/zoomX); // interpolate pos of current pixel in img to nearest of src
//                u32 v=(u32)((f32)y/zoomY); // interpolate pos of current pixel in img to nearest of src
//                SColor color = getPixelAlways(src,u,v);
//                dst->setPixel(x,y,color,false);
//            }
//        }
//	}


	return dst;
}

IImage* Tool::resizeFast( IImage* src, const core::dimension2du& newSize, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen )
{
	/// error
	if (!src)
		return 0;

	/// error
	if (newSize == core::dimension2du(0,0) )
	{
		return 0;
	}

	/// get size from source image
	const core::dimension2du& Size = src->getDimension();

	/// just clone it when same size requested -> likely faster
	if (newSize == Size)
	{
		return cloneImage(src);
	}

	/// calculate size of final image
    core::dimension2du nSize = newSize;

	// calculate width from aspect-ratio
	if (nSize.Width == 0)
		nSize.Width = (u32)( (f32)nSize.Height * (f32)Size.Width * core::reciprocal( (f32)Size.Height ) );

	// calculate height from aspect-ratio
	if (nSize.Height == 0)
		nSize.Height = (u32)( (f32)nSize.Width * (f32)Size.Height * core::reciprocal( (f32)Size.Width ) );

    /// create final image
	IImage* dst = (IImage*)new CImage(src->getColorFormat(), nSize);

	/// error, could not create final image
	if (!dst)
        return 0;

	/// loop pixel
	const f32 zoomXinv = (f32)Size.Width/(f32)nSize.Width;
	const f32 zoomYinv = (f32)Size.Height/(f32)nSize.Height;

    for (u32 y=0; y<nSize.Height; y++)
    {
        for (u32 x=0; x<nSize.Width; x++)
        {
            u32 u=(u32)core::round32( (f32)x * zoomXinv ); // interpolate pos of current pixel in img LINEAR to src
            u32 v=(u32)core::round32( (f32)y * zoomYinv ); // interpolate pos of current pixel in img LINEAR to src
            SColor color = getBilinearPixelFast(src,u,v);

			if ( planes == ECP_ALL )
			{
				// change nothing on color
			}
			else if( planes==ECP_RGB )
			{
				color.setAlpha(255);
			}
			else
			{
				if ( ! (planes & ECP_ALPHA) )
				{
					color.setAlpha(255);
				}
				if ( ! (planes & ECP_RED) )
				{
					color.setRed(0);
				}
				if ( ! (planes & ECP_GREEN) )
				{
					color.setGreen(0);
				}
				if ( ! (planes & ECP_BLUE) )
				{
					color.setBlue(0);
				}
			}

			// write color to image
			dst->setPixel(x,y,color,false);
        }
	}

	return dst;
}

IImage* Tool::resizeBilinear( IImage* src, const core::dimension2du& newSize, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen)
{
	/// error
	if (!src)
		return 0;

	/// error
	if (newSize == core::dimension2du(0,0) )
	{
		return 0;
	}

	/// get size from source image
	const core::dimension2du& Size = src->getDimension();

	/// just clone it when same size requested -> likely faster
	if (newSize == Size)
	{
		return cloneImage(src);
	}

	/// calculate size of final image
    core::dimension2du nSize = newSize;

	// calculate width from aspect-ratio
	if (nSize.Width == 0)
		nSize.Width = (u32)( (f32)nSize.Height * (f32)Size.Width * core::reciprocal( (f32)Size.Height ) );

	// calculate height from aspect-ratio
	if (nSize.Height == 0)
		nSize.Height = (u32)( (f32)nSize.Width * (f32)Size.Height * core::reciprocal( (f32)Size.Width ) );

    /// create final image
	IImage* dst = (IImage*)new CImage(src->getColorFormat(), nSize);

	/// error, could not create final image
	if (!dst)
        return 0;

	/// loop pixel
	const f32 zoomXinv = (f32)Size.Width/(f32)nSize.Width;
	const f32 zoomYinv = (f32)Size.Height/(f32)nSize.Height;

    for (u32 y=0; y<nSize.Height; y++)
    {
        for (u32 x=0; x<nSize.Width; x++)
        {
            u32 u=(u32)core::round32( (f32)x * zoomXinv ); // interpolate pos of current pixel in img LINEAR to src
            u32 v=(u32)core::round32( (f32)y * zoomYinv ); // interpolate pos of current pixel in img LINEAR to src
            SColor color = getBilinearPixel(src,u,v,planes,0);

 			if ( planes == ECP_ALL )
			{
				// change nothing on color
			}
			else if( planes==ECP_RGB )
			{
				color.setAlpha(255);
			}
			else
			{
				if ( ! (planes & ECP_ALPHA) )
				{
					color.setAlpha(255);
				}
				if ( ! (planes & ECP_RED) )
				{
					color.setRed(0);
				}
				if ( ! (planes & ECP_GREEN) )
				{
					color.setGreen(0);
				}
				if ( ! (planes & ECP_BLUE) )
				{
					color.setBlue(0);
				}
			}

			// write color to image
			dst->setPixel(x,y,color,false);
        }
	}

	return dst;
}

IImage* Tool::resizeBicubic( IImage* src, const core::dimension2du& newSize, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen)
{
	/// error
	if (!src)
		return 0;

	/// error
	if (newSize == core::dimension2du(0,0) )
	{
		return 0;
	}

	/// get size from source image
	const core::dimension2du& Size = src->getDimension();

	/// just clone it when same size requested -> likely faster
	if (newSize == Size)
	{
		return cloneImage(src);
	}

	/// calculate size of final image
    core::dimension2du nSize = newSize;

	// calculate width from aspect-ratio
	if (nSize.Width == 0)
		nSize.Width = (u32)( (f32)nSize.Height * (f32)Size.Width * core::reciprocal( (f32)Size.Height ) );

	// calculate height from aspect-ratio
	if (nSize.Height == 0)
		nSize.Height = (u32)( (f32)nSize.Width * (f32)Size.Height * core::reciprocal( (f32)Size.Width ) );

    /// create final image
	IImage* dst = (IImage*)new CImage(src->getColorFormat(), nSize);

	/// error, could not create final image
	if (!dst)
        return 0;

	/// loop pixel
	const f32 zoomXinv = (f32)Size.Width/(f32)nSize.Width;
	const f32 zoomYinv = (f32)Size.Height/(f32)nSize.Height;

    for (u32 y=0; y<nSize.Height; y++)
    {
        for (u32 x=0; x<nSize.Width; x++)
        {
            u32 u=(u32)core::round32( (f32)x * zoomXinv );
            u32 v=(u32)core::round32( (f32)y * zoomYinv );
            SColor color = getBicubicPixel(src,u,v,planes,0);

 			if ( planes == ECP_ALL )
			{
				// change nothing on color
			}
			else if( planes==ECP_RGB )
			{
				color.setAlpha(255);
			}
			else
			{
				if ( ! (planes & ECP_ALPHA) )
				{
					color.setAlpha(255);
				}
				if ( ! (planes & ECP_RED) )
				{
					color.setRed(0);
				}
				if ( ! (planes & ECP_GREEN) )
				{
					color.setGreen(0);
				}
				if ( ! (planes & ECP_BLUE) )
				{
					color.setBlue(0);
				}
			}

			// write color to image
			dst->setPixel(x,y,color,false);
        }
	}

	return dst;
}

IImage* Tool::scale( IImage* src, const core::vector2df& scaleXY, s32 scaleOp, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen)
{
	if (!src)
		return 0;

 	const u32 pixelX = (u32)core::round32( scaleXY.X*src->getDimension().Width );
 	const u32 pixelY = (u32)core::round32( scaleXY.Y*src->getDimension().Height );
    return resize( src, core::dimension2du(pixelX,pixelY), scaleOp, planes, bPreserveAspect, bSharpen );
}

IImage* Tool::scaleNearest( IImage* src, const core::vector2df& scaleXY, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen)
{
	if (!src)
		return 0;

 	u32 pixelX = (u32)core::round32( scaleXY.X*src->getDimension().Width );
 	u32 pixelY = (u32)core::round32( scaleXY.Y*src->getDimension().Height );
    return resizeNearest( src, core::dimension2du(pixelX,pixelY), planes, bPreserveAspect, bSharpen );
}

IImage* Tool::scaleFast( IImage* src, const core::vector2df& scaleXY, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen)
{
	if (!src)
		return 0;

 	const u32 pixelX = (u32)core::round32( scaleXY.X*src->getDimension().Width );
 	const u32 pixelY = (u32)core::round32( scaleXY.Y*src->getDimension().Height );
    return resizeFast( src, core::dimension2du(pixelX,pixelY), planes, bPreserveAspect, bSharpen );
}

IImage* Tool::scaleBilinear( IImage* src, const core::vector2df& scaleXY, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen)
{
	if (!src)
		return 0;

 	const u32 pixelX = (u32)core::round32( scaleXY.X*src->getDimension().Width );
 	const u32 pixelY = (u32)core::round32( scaleXY.Y*src->getDimension().Height );
    return resizeBilinear( src, core::dimension2du(pixelX,pixelY), planes, bPreserveAspect, bSharpen );
}

IImage* Tool::scaleBicubic( IImage* src, const core::vector2df& scaleXY, E_COLOR_PLANE planes, bool bPreserveAspect, bool bSharpen)
{
	if (!src)
		return 0;

 	const u32 pixelX = (u32)core::round32( scaleXY.X*src->getDimension().Width );
 	const u32 pixelY = (u32)core::round32( scaleXY.Y*src->getDimension().Height );
    return resizeBicubic( src, core::dimension2du(pixelX,pixelY), planes, bPreserveAspect, bSharpen );
}

} // end namespace video

} // end namespace irr
