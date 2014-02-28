// thc_backbuffer.cpp

#include "thc_backbuffer.h"
#include "main.h"
#include "stdafx.h"
#include "DarkGDK.h"

namespace thc
{
/*
function get_color(x as integer, y as integer)

   ptr as dword : color as dword

   lock backbuffer
      ptr = get backbuffer ptr() + (y * get backbuffer pitch()) + (x * 4)
      color = *ptr
   unlock backbuffer

endfunction color
*/
	DWORD backbufferGetPixel(int x, int y)
	{
		if (x<0) return 0x00000000;
		if (y<0) return 0x00000000;
		if (x>=scr.x) return 0x00000000;
		if (y>=scr.y) return 0x00000000;
		DWORD *ptr;
		ptr=(DWORD*)(dbGetPixelsPointer()+(y * dbGetPixelsPitch()) + (x<<2));
		return *ptr;
	}
	void  backbufferSetPixel(int x, int y, DWORD color)
	{
		if (x<0) return;
		if (y<0) return;
		if (x>=scr.x) return;
		if (y>=scr.y) return;
		DWORD *ptr;
		ptr=(DWORD*)(dbGetPixelsPointer()+(y * dbGetPixelsPitch()) + (x<<2));
		*ptr=color;
	}
	void  backbufferLOCK()
	{
		dbLockPixels();
	}
	void backbufferUNLOCK()
	{
		dbUnlockPixels();
	}
	DWORD backbufferPointer()
	{
		return dbGetPixelsPointer();
	}
	DWORD backbufferPitch()
	{
		return dbGetPixelsPitch();
	}
	void  backbufferDrawLine(int x1, int y1, int x2, int y2, DWORD color)
	{
		// Memblock Size

		// Bresenham Algorithmus für Raster Linien (ohne Gleitkommas und Multiplikationen)
		int i, deltax, deltay, numpixels;
		int d, dinc1, dinc2;
		int x, xinc1, xinc2;
		int y, yinc1, yinc2;
		
		deltax = abs(x2 - x1);
		deltay = abs(y2 - y1);
		
		if (deltax >= deltay)
		{
			numpixels = deltax + 1;
			d = (deltay<<1) - deltax;
			dinc1 = deltay << 1;
			dinc2 = (deltay - deltax) << 1;
			xinc1 = 1;
			xinc2 = 1;
			yinc1 = 0;
			yinc2 = 1;
		} 
		else 
		{
	   		numpixels = deltay + 1;
			d = (2 * deltax) - deltay;
			dinc1 = deltax << 1;
			dinc2 = (deltax - deltay) << 1;
			xinc1 = 0;
			xinc2 = 1;
			yinc1 = 1;
			yinc2 = 1;
		}	
		if (x1 > x2)
		{
			xinc1 = -xinc1;
			xinc2 = -xinc2;
		}
		if (y1 > y2)
		{
			yinc1 = -yinc1;
			yinc2 = -yinc2;
		}
		
		x=x1;
		y=y1;
		
		for (i=0; i<numpixels; i++) 
		{
			backbufferSetPixel(x,y,color);		
			if (d < 0)
			{
				d = d + dinc1;
				x = x + xinc1;
				y = y + yinc1;
			}
			else 
			{
				d = d + dinc2;
				x = x + xinc2;
				y = y + yinc2;
			}
		}
	}
}