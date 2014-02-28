// thc_image.cpp

#include "thc_image.h"
#include "DarkGDK.h"
#include "thc_free.h"
#include "thc_is.h"
#include "thc_delete.h"
#include "thc_memblock.h"

namespace thc
{
//---------------------------------------------------------------------------
	int ImageLoad(const char * pFile, int flag)
	{
		if (IsImageFile(pFile)==false) return 0;
		int img=FreeImage();
		dbLoadImage((char*)pFile,img,flag);
		if (IsImage(img)==false) return 0;
		return img;
	}
//---------------------------------------------------------------------------
	bool ImageSave(const char* pSave , int img)
	{
			if (!pSave) return false;							// String Pointer == NULL
			if (IsImage(img)==0) return false;		// Image existiert nicht
			FileDelete(pSave);					// Delete File if Exist == true
			dbSaveImage((char*)pSave,img);
			return true;
	}
//---------------------------------------------------------------------------
	int MemblockLoad(const char* pLoad , int iFlag)
	{
        int img = ImageLoad(pLoad,iFlag);
        if (img==0) return 0;
        int mem = MemblockFromImage(img);
		  ImageDelete(img);
        return mem; 
	}
//---------------------------------------------------------------------------
	bool MemblockSave(const char* pSave , int mem)
	{
        if (!pSave) return false;
        if (IsMemblock(mem)==0) return false;      
        int img=ImageFromMemblock(mem);
        if (img==0) return false;
        ImageSave(pSave,img);
        ImageDelete(img);
        return true;
}
//---------------------------------------------------------------------------
	int ImageMultiplyWithColor(int img, DWORD color, float factor)
	{
		if (IsImage(img)==0) return 0;
		int mem=MemblockFromImage(img);
		if (mem==0) return 0;
		int memfinal=MemblockMultiplyWithColor(mem,color,factor);
		MemblockDelete(mem);
		if (memfinal==0) return 0;
		int imgfinal=ImageFromMemblock(memfinal);
		MemblockDelete(memfinal);
		return imgfinal;
	}
//---------------------------------------------------------------------------
	int ImageReplaceColor(int img, DWORD color_old, DWORD color_new)
	{
		if (IsImage(img)==0) return 0;
		int mem=MemblockFromImage(img);
		if (mem==0) return 0;
		int finalmem=MemblockReplaceColor(mem,color_old,color_new);
		MemblockDelete(mem);
		int final=ImageFromMemblock(finalmem);
		MemblockDelete(finalmem);
		return final;	
	}
//---------------------------------------------------------------------------
	int ImageWorkAroundForMipmapUse(int img)
	{
		if (IsImage(img)==0) return 0;
		char *pFile="temp.bmp";
		if (dbFileExist(pFile)==1) dbDeleteFile(pFile);
		dbSaveImage(pFile,img);
		int use=FreeImage();
		dbLoadImage(pFile,use,0);
		if (dbFileExist(pFile)==1) dbDeleteFile(pFile);
		if (IsImage(use)==0) return 0;
	   return use;
	}
//---------------------------------------------------------------------------	
	int ImageFromColor( int dx, int dy, DWORD color)
	{
     		int mem=MemblockFromColor(dx,dy,color);
			if (mem==0) return 0;   
			int img=ImageFromMemblock(mem);
			MemblockDelete(mem);
			return img;
	}
//---------------------------------------------------------------------------	
	int ImageFromColorWithBorder( int dx, int dy, DWORD color, int border, DWORD bordercolor)
	{
     		int mem=MemblockFromColorWithBorder(dx,dy,color,border,bordercolor);
			if (mem==0) return 0;   
			int img=ImageFromMemblock(mem);
			MemblockDelete(mem);
			return img;
	}
}