// thc_memblock_rotation.h

#ifndef __IMAGE_DLL_MEMBLOCK_ROTATE_H_INCLUDED__
#define __IMAGE_DLL_MEMBLOCK_ROTATE_H_INCLUDED__

#include <windows.h>

namespace thc
{
	bool MemblockFlipH( int mem );
	bool MemblockFlipV( int mem );
	int	MemblockRotate90 ( int mem );
	int MemblockRotate180 ( int mem );
	int MemblockRotate270 ( int mem );
	float WrapAngle(float winkel);
	float RotateX_2D(const float& x, const float& y, const float& winkel);
	float RotateY_2D(const float& x, const float& y, const float& winkel);
	int MemblockRotateB ( int mem, float angle, DWORD bgcolor);
	int MemblockRotateA ( int mem, float angle);
	int MemblockSkewH ( int mem, float angle);
	int MemblockSkewV ( int mem, float angle);
}

#endif