// thc_backbuffer.h

#ifndef __THC_BACKBUFFER_H_INCLUDED__
#define __THC_BACKBUFFER_H_INCLUDED__

#include "stdafx.h"

namespace thc
{
	DWORD	backbufferGetPixel(int x, int y);
	void	backbufferSetPixel(int x, int y, DWORD color);
	void	backbufferLOCK();
	void	backbufferUNLOCK();
	DWORD	backbufferPointer();
	DWORD	backbufferPitch();
	void	backbufferDrawLine(int x1, int y1, int x2, int y2, DWORD color);
}

#endif