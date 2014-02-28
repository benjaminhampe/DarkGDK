// thc_memblock_fill_flood.h

#ifndef __IMAGE_DLL_MEMBLOCK_FILL_FLOOD_H_INCLUDED__
#define __IMAGE_DLL_MEMBLOCK_FILL_FLOOD_H_INCLUDED__

#include <windows.h>

namespace thc
{
	int MemblockFloodFill(int mem, int x, int y, DWORD newColor, DWORD oldColor);
}
#endif