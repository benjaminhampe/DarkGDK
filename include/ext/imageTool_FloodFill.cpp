// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include <imageTool.h>


namespace irr
{

namespace video
{

void Tool::fill( IImage* dst, const SColor& color, E_COLOR_PLANE planes, bool blend)
{
	if (!dst) return; 														// abort

	SColor c;
	const core::dimension2du& my_size = dst->getDimension();
	for (u32 y=0; y<my_size.Height; y++)													// loop y
	{	for (u32 x=0; x<my_size.Width; x++)												// loop x
		{
			c = color;
			const SColor& old = dst->getPixel(x,y);							// read pixel
			if (!(planes&irr::video::ECP_ALPHA)) c.setAlpha(old.getAlpha());		// set alpha channel to old pixel, if channel not used
			if (!(planes&irr::video::ECP_RED)) c.setRed(old.getRed());				// set red channel to old pixel, if channel not used
			if (!(planes&irr::video::ECP_GREEN)) c.setGreen(old.getGreen());		// set green channel to old pixel, if channel not used
			if (!(planes&irr::video::ECP_RED)) c.setBlue(old.getBlue());			// set blue channel to old pixel, if channel not used
			dst->setPixel(x,y,c,blend);									// write pixel
		}
	}
}

//! MS Paint Style
bool Tool::floodFill( IImage* img, s32 x, s32 y, const SColor& fillcolor, const SColor& old)
{
	if (!img)
		return false;

	SColor oldcolor(old);
	if (old.color==0)
		oldcolor=getPixel(img,x,y);

	if (getPixel(img,x,y)==fillcolor)
       return false;

	s32 lg, rg, px=x;
	while(x>=0 && getPixel(img,x,y)==oldcolor)
	{
		drawPixel(img,x,y,fillcolor);
		x--;
	}

	lg=x+1;
	x=px+1;

	const core::dimension2du& Size = img->getDimension();

	while(x<(s32)Size.Width && getPixel(img,x,y)==oldcolor)
	{
		drawPixel(img,x,y,fillcolor);
		x++;
	}
	rg=x-1;

	for(x=rg; x>=lg; x--)
	{
		//! alle Zeilen oberhalb
		if((getPixel(img,x,y-1)==oldcolor) && (y-1>0))
			floodFill( img,x, y-1, fillcolor, oldcolor);
		//! alle Zeilen unterhalb
		if((getPixel(img,x,y+1)==oldcolor) && (y<(s32)Size.Height-1))
			floodFill( img,x,y+1,fillcolor,oldcolor);
	}

	return true;
}


} // end namespace video

} // end namespace irr
