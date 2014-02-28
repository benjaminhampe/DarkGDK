// thc_image.h

#ifndef __THC_IMAGE_H_INCLUDED__
#define __THC_IMAGE_H_INCLUDED__

#include "stdafx.h"

namespace thc
{
	int ImageLoad(const char * pFile, int flag);
	int MemblockLoad(const char* pLoad , int iFlag);
	bool ImageSave(const char* pSave , int img);
	bool MemblockSave(const char* pSave , int mem);
	int ImageMultiplyWithColor(int img, DWORD color, float factor);
	int ImageReplaceColor(int img, DWORD color_old, DWORD color_new);
	int ImageWorkAroundForMipmapUse(int img);
	int ImageFromColor( int dx, int dy, DWORD color);
	int ImageFromColorWithBorder( int dx, int dy, DWORD color, int border, DWORD bordercolor);
}
#endif