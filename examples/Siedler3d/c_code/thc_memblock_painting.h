// thc_memblock_painting.h

#ifndef __IMAGE_DLL_MEMBLOCK_PAINTING_H_INCLUDED__
#define __IMAGE_DLL_MEMBLOCK_PAINTING_H_INCLUDED__

#include <windows.h>

namespace thc
{
	int MemblockDrawDot(int mem, int x, int y, DWORD color);
	int MemblockDrawLineA(int mem, int x1, int y1, int x2, int y2, DWORD color);
	int MemblockDrawLineB(int mem, int x1, int y1, int x2, int y2, DWORD color1, DWORD color2);
	int MemblockDrawBoxA(int mem, int x1, int y1, int x2, int y2, DWORD color);
	int MemblockDrawBoxB(int mem, int x1, int y1, int x2, int y2, DWORD color, int borderwidth);
	int MemblockDrawBoxC(int mem, int x1, int y1, int x2, int y2, DWORD color1, DWORD color2, DWORD color3, DWORD color4);
	int MemblockDrawBoxD(int mem, int x1, int y1, int x2, int y2, DWORD color1, DWORD color2, DWORD color3, DWORD color4, int borderwidth);
	int MemblockDrawCircleA(int mem, int x, int y, int radius, DWORD color);
	int MemblockDrawCircleB(int mem, int x, int y, int radius, DWORD colorI, DWORD colorO);
	int MemblockDrawCircleC(int mem, int x, int y, int radius, DWORD colorI, DWORD colorO, int borderwidth);
	int MemblockDrawEllipseA(int mem, int x, int y, int rx, int ry, DWORD color);
	int MemblockDrawEllipseB(int mem, int x, int y, int rx, int ry, DWORD colorI, DWORD colorO);
	int MemblockDrawEllipseC(int mem, int x, int y, int rx, int ry, DWORD colorI, DWORD colorO, int borderwidthX, int borderwidthY);
	int MemblockDrawTriangleA(int mem, int x1, int y1, int x2, int y2, int x3, int y3, DWORD color);
	int MemblockDrawTriangleB(int mem, int x1, int y1, int x2, int y2, int x3, int y3, DWORD color, int borderwidth);
	int MemblockDrawTriangleC(int mem, int x1, int y1, int x2, int y2, int x3, int y3, DWORD color1, DWORD color2, DWORD color3);
	int MemblockDrawTriangleD(int mem, int x1, int y1, int x2, int y2, int x3, int y3, DWORD color1, DWORD color2, DWORD color3, int borderwidth);
}

#endif