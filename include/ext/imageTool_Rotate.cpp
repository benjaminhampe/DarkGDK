// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include <imageTool.h>


namespace irr
{

namespace video
{


IImage* Tool::rotateLeft( IImage* src )
{
	if (!src)
		return 0;

	const core::dimension2du& Size = src->getDimension();

	IImage* dst = new CImage( src->getColorFormat(), Size );
	if (!dst)
		return 0;

	for (u32 y=0; y<Size.Height; y++)
	{
		for (u32 x=0; x<Size.Width; x++)
		{
			SColor color = src->getPixel(x,y);
			dst->setPixel(y, Size.Width-1-x, color);
		}
	}

	return dst;
}


IImage*	Tool::rotateRight( IImage* src )
{
	if (!src)
		return 0;

	const core::dimension2du& Size = src->getDimension();

	IImage* dst = new CImage( src->getColorFormat(), Size );
	if (!dst)
		return 0;

	for (u32 y=0; y<Size.Height; y++)
	{
		for (u32 x=0; x<Size.Width; x++)
		{
			SColor color = src->getPixel(x,y);
			dst->setPixel(Size.Height-1-y, x, color);
		}
	}

	return dst;
}

bool Tool::flipH( IImage* dst )
{
	if (!dst) return false;
	const core::dimension2du& Size = dst->getDimension();
	u32 HalfWidth = Size.Width >> 1;
	SColor color1, color2;

	for (u32 y=0; y<Size.Height; y++)
	{
		for (u32 x=0; x<HalfWidth; x++)
		{
			color1 = dst->getPixel(x,y);
			color2 = dst->getPixel(Size.Width-1-x,y);
			dst->setPixel(x,y,color2);
			dst->setPixel(Size.Width-1-x,y,color1);
		}
	}
	return true;
}

bool Tool::flipV( IImage* dst )
{
	if (!dst) return false;
	const core::dimension2du& Size = dst->getDimension();

	u32 HalfHeight = Size.Height >> 1;
	SColor color1, color2;

	for (u32 y=0; y<HalfHeight; y++)
	{
		for (u32 x=0; x<Size.Width; x++)
		{
			color1 = dst->getPixel(x,y);
			color2 = dst->getPixel(x,Size.Height-1-y);
			dst->setPixel(x,y,color2);
			dst->setPixel(x,Size.Height-1-y,color1);
		}
	}
	return true;
}

bool Tool::rotate180( IImage* dst )
{
	if (!dst) return false;
	const core::dimension2du& Size = dst->getDimension();

	u32 m = Size.Height >> 1;
	SColor color1, color2;

	for (u32 y=0; y<m; y++)
	{
		for (u32 x=0; x<Size.Width; x++)
		{
			color1 = dst->getPixel(x,y);
			color2 = dst->getPixel(x,Size.Height-1-y);
			dst->setPixel(x,y,color2);
			dst->setPixel(x,Size.Height-1-y,color1);
		}
	}
	return true;
}

IImage*	Tool::rotate( IImage* src, f32 angleDegreesCCW, SColor* colorKey )
{
	if (!src)
		return 0;

	const core::dimension2du& Size = src->getDimension();

	// Winkel
	while (angleDegreesCCW<0.0f)	{	angleDegreesCCW+=360.0f;	}
	while (angleDegreesCCW>=360.0f)	{	angleDegreesCCW-=360.0f;	}

	//
	if (core::equals(angleDegreesCCW,0.0f))
	{
		return cloneImage(src);
	}
	else if (core::equals(angleDegreesCCW,90.0f))
	{
		return rotateLeft(src);
	}
	else if (core::equals(angleDegreesCCW,270.0f))
	{
		return rotateRight(src);
	}
	else if (core::equals(angleDegreesCCW,180.0f))
    {
        IImage* tmp = cloneImage(src);
		rotate180(tmp);
        return tmp;
    }
    else
    {
        // alpha
        const f32 a=(360.0f-angleDegreesCCW)*core::DEGTORAD;
        const f32 sa=sinf(a);
        const f32 ca=cosf(a);

        // gamma
        const f32 g=angleDegreesCCW*core::DEGTORAD;
        const f32 sg=sinf(g);
        const f32 cg=cosf(g);

        // BERECHNNUNG des Mittelpunktes von MEM
        const f32 mXh=0.5f*(f32)Size.Width;
        const f32 mYh=0.5f*(f32)Size.Height;

        // BERECHNNUNG der Eckpunkte
        const f32 Ax= mXh, 	Ay=-mYh;
        const f32 Bx=-mXh,	By=-mYh;
        const f32 Cx=-mXh, 	Cy= mYh;
        const f32 Dx= mXh, 	Dy= mYh;

        // TRANSFORMATION der Eckpunkte
        f32 Anx=Ax*ca - Ay*sa;
        f32 Any=Ax*sa + Ay*ca;
        f32 Bnx=Bx*ca - By*sa;
        f32 Bny=Bx*sa + By*ca;
        f32 Cnx=Cx*ca - Cy*sa;
        f32 Cny=Cx*sa + Cy*ca;
        f32 Dnx=Dx*ca - Dy*sa;
        f32 Dny=Dx*sa + Dy*ca;

        // BERECHNUNG der FINAL WIDTH and HEIGHT
        f32 minX=0.0f, maxX=0.0f;
        f32 minY=0.0f, maxY=0.0f;
        if (Anx<minX) minX=Anx;		 if (Any<minY) minY=Any;
        if (Anx>maxX) maxX=Anx;		 if (Any>maxY) maxY=Any;
        if (Bnx<minX) minX=Bnx;		 if (Bny<minY) minY=Bny;
        if (Bnx>maxX) maxX=Bnx;		 if (Bny>maxY) maxY=Bny;
        if (Cnx<minX) minX=Cnx;		 if (Cny<minY) minY=Cny;
        if (Cnx>maxX) maxX=Cnx;		 if (Cny>maxY) maxY=Cny;
        if (Dnx<minX) minX=Dnx;		 if (Dny<minY) minY=Dny;
        if (Dnx>maxX) maxX=Dnx;		 if (Dny>maxY) maxY=Dny;

        f32 fdx=maxX-minX;
        f32 fdy=maxY-minY;

        u32 dx=(u32)core::abs_<s32>( core::round32(fdx) );
        u32 dy=(u32)core::abs_<s32>( core::round32(fdy) );

		core::stringc txt = "New Image with size (";
		txt += dx;
		txt += ", ";
		txt += dy;
		txt += ")";
		IT_PRINT(txt.c_str(), ELL_INFORMATION);

        // FINAL MEMBLOCK
        IImage* dst = new CImage( src->getColorFormat(), core::dimension2du(dx,dy));
        if (!dst)
            return 0;

		const core::dimension2du& Size2 = dst->getDimension();

        // BERECHNUNG des Mittelpunktes von FINAL
        f32 fdxh=0.5f*fdx;
        f32 fdyh=0.5f*fdy;

        // LET'S ROTATE
        s32 x,y;
        SColor color;
        f32 x0,y0,x1,y1;

		IT_PRINT("OK\n");
        // Fuer alle Punkte im Zielbild den entsprechenden Punkt im Ausgangsbild
        // suchen. Dadurch entstehen keine Luecken im Bild.
        for (u32 j=0; j<dy; j++)
        {
            for (u32 i=0; i<dx; i++)
            {
                if ( (i<Size2.Width) && (j<Size2.Height) )
                {
					x0=(f32)i-fdxh; // relativ zu FinalMem Mittelpunkt
					y0=(f32)j-fdyh; // relativ zu FinalMem Mittelpunkt
					x1=(cg*x0-sg*y0)+mXh; // relativ zu SourceMem Mittelpunkt
					y1=(cg*y0+sg*x0)+mYh; // relativ zu SourceMem Mittelpunkt
					x=core::round32(x1);
					y=core::round32(y1);

					// PIXEL von SourceMem
					if ((x>=0) && (y>=0) && ((u32)x<Size.Width) && ((u32)y<Size.Height))
					{
						color=src->getPixel((u32)x, (u32)y);
					}
					else
					{
						if (colorKey)
							color=*colorKey;
						else
							color.color = 0;
					}

					dst->setPixel( i,j,color );
                }
            }
        }
        return dst;
    }
    return 0;
}

} // end namespace video

} // end namespace irr
