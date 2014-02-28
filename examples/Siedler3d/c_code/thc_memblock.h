// thc_memblock.h

#ifndef __THC_MEMBLOCK_H_INCLUDED__
#define __THC_MEMBLOCK_H_INCLUDED__

#include <windows.h>
#include "DarkGDK.h"

namespace thc
{
	DWORD ALPHA_ON(DWORD color);
	DWORD ALPHA_OFF(DWORD color);
	DWORD SET_ALPHA(DWORD color, unsigned char value0_255);
	DWORD RGBA(int r, int g, int b, int a);
	int RGBA_R(DWORD color);
	int RGBA_G(DWORD color);
	int RGBA_B(DWORD color);
	int RGBA_A(DWORD color);
	int ImageFromMemblock( int mem );
	int MemblockFromImage( int img );
	int MemblockCreate(int size);
	int MemblockCreate(int dx,int dy, int dz);
	int MemblockHeader(int mem, int dx, int dy, int dz);

	int MemblockX( int mem );
	int MemblockY( int mem );
	int MemblockZ( int mem );
	int MemblockSetColorKey(int mem, DWORD color_key);
	int MemblockReplaceColor(int mem, DWORD color_old, DWORD color_new);
	int MemblockFromColor( int dx, int dy, DWORD color);
	int MemblockFromColorWithBorder( int dx, int dy, DWORD color, int border, DWORD bordercolor);
	int MemblockMultiplyWithColor(int mem, DWORD color, float factor);
	int MemblockCut(int mem, int x1, int y1, int x2, int y2);
	int MemblockCopy(int mem);
	DWORD ReadColor(const int& mem, int x, int y, const int& memX, const int& memY);
	DWORD _bilinear_pixel(int mem, float fx, float fy, int memX, int memY);
	int MemblockScale( int mem, int SizeX, int SizeY);

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//
//			INLINE - DEFINITIONEN
//
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////

	// Get Pointer
	inline DWORD* MemblockPointer(int mem)
	{
		return (DWORD*)dbGetMemblockPtr(mem);
	}
	
	// Read DWORD
	inline DWORD MemblockReadDword(int mem, int pos)
	{
		return dbMemblockDword(mem,pos);
	}
	// Read DWORD
	inline DWORD MemblockReadDword(int mem, const int& memX, const int& memY, int x, int y)
	{
		if (x<0)      x = 0;
		if (y<0)      y = 0;
		if (x>memX-1) x = memX-1;
		if (y>memY-1) y = memY-1;
		return MemblockReadDword(mem,12+4*(x+y*memX));
	}
	// Write DWORD
	inline void MemblockWriteDword(int mem, int pos, DWORD color)
	{
		dbWriteMemblockDword(mem,pos,color);
	}
	// Write DWORD
	inline void MemblockWriteDword(int mem, const int& memX, const int& memY, int x, int y, DWORD color)
	{
		if (x<0)      x = 0;
		if (y<0)      y = 0;
		if (x>memX-1) x = memX-1;
		if (y>memY-1) y = memY-1;
		MemblockWriteDword(mem, 12+4*(x+y*memX), color);
	}
	// Read BYTE
	inline int MemblockReadByte(int mem, int pos)
	{
		return dbMemblockByte(mem,pos);
	}
	// Write BYTE
	inline void MemblockWriteByte(int mem, int pos, int byte)
	{
		dbWriteMemblockByte(mem,pos,byte);
	}
	// Write BYTE
	inline void MemblockWriteByte(int mem, int pos, unsigned char byte)
	{
		dbWriteMemblockByte(mem,pos,byte);
	}
	// Read (R)
	inline int MemblockReadR(int mem, int pos)
	{
		return MemblockReadByte(mem,pos+2);
	}
	// Read (R)
	inline int MemblockReadR(int mem, const int& memX, const int& memY, int x, int y)
	{
		if (x<0)      x = 0;
		if (y<0)      y = 0;
		if (x>memX-1) x = memX-1;
		if (y>memY-1) y = memY-1;
		return MemblockReadByte(mem,12+4*(x+y*memX)+2);
	}
	// Read (G)
	inline int MemblockReadG(int mem, int pos)
	{
		return MemblockReadByte(mem,pos+1);
	}
	// Read (G)
	inline int MemblockReadG(int mem, const int& memX, const int& memY, int x, int y)
	{
		if (x<0)      x = 0;
		if (y<0)      y = 0;
		if (x>memX-1) x = memX-1;
		if (y>memY-1) y = memY-1;
		return MemblockReadByte(mem,12+4*(x+y*memX)+1);
	}
	// Read (B)
	inline int MemblockReadB(int mem, int pos)
	{
		return MemblockReadByte(mem,pos);
	}
	// Read (B)
	inline int MemblockReadB(int mem, const int& memX, const int& memY, int x, int y)
	{
		if (x<0)      x = 0;
		if (y<0)      y = 0;
		if (x>memX-1) x = memX-1;
		if (y>memY-1) y = memY-1;
		return MemblockReadByte(mem,12+4*(x+y*memX));
	}
	// Read (A)
	inline int MemblockReadA(int mem, int pos)
	{
		return MemblockReadByte(mem,pos+3);
	}
	// Read (A)
	inline int MemblockReadA(int mem, const int& memX, const int& memY, int x, int y)
	{
		if (x<0)      x = 0;
		if (y<0)      y = 0;
		if (x>memX-1) x = memX-1;
		if (y>memY-1) y = memY-1;
		return MemblockReadByte(mem,12+4*(x+y*memX)+3);
	}
	// Write (R)
	inline void MemblockWriteR(int mem, int pos, int R)
	{
		MemblockWriteByte(mem,pos+2,R);
	}
	// Write (R)
	inline void MemblockWriteR(int mem, int pos, unsigned char R)
	{
		MemblockWriteByte(mem,pos+2,R);
	}
	// Write (R)
	inline void MemblockWriteR(int mem, const int& memX, const int& memY, int x, int y, int R)
	{
		if (x<0)      x = 0;
		if (y<0)      y = 0;
		if (x>memX-1) x = memX-1;
		if (y>memY-1) y = memY-1;
		MemblockWriteByte(mem,12+4*(x+y*memX)+2,R);
	}
	// Write (R)
	inline void MemblockWriteR(int mem, const int& memX, const int& memY, int x, int y, unsigned char R)
	{
		if (x<0)      x = 0;
		if (y<0)      y = 0;
		if (x>memX-1) x = memX-1;
		if (y>memY-1) y = memY-1;
		MemblockWriteByte(mem,12+4*(x+y*memX)+2,R);
	}
	// Write (G)
	inline void MemblockWriteG(int mem, int pos, int G)
	{
		MemblockWriteByte(mem,pos+1,G);
	}
	// Write (G)
	inline void MemblockWriteG(int mem, int pos, unsigned char G)
	{
		MemblockWriteByte(mem,pos+1,G);
	}
	// Write (G)
	inline void MemblockWriteG(int mem, const int& memX, const int& memY, int x, int y, int G)
	{
		if (x<0)      x = 0;
		if (y<0)      y = 0;
		if (x>memX-1) x = memX-1;
		if (y>memY-1) y = memY-1;
		MemblockWriteByte(mem,12+4*(x+y*memX)+1,G);
	}
	// Write (G)
	inline void MemblockWriteG(int mem, const int& memX, const int& memY, int x, int y, unsigned char G)
	{
		if (x<0)      x = 0;
		if (y<0)      y = 0;
		if (x>memX-1) x = memX-1;
		if (y>memY-1) y = memY-1;
		MemblockWriteByte(mem,12+4*(x+y*memX)+1,G);
	}
	// Write (B)
	inline void MemblockWriteB(int mem, int pos, int B)
	{
		MemblockWriteByte(mem,pos,B);
	}
	// Write (B)
	inline void MemblockWriteB(int mem, int pos, unsigned char B)
	{
		MemblockWriteByte(mem,pos,B);
	}
	// Write (B)
	inline void MemblockWriteB(int mem, const int& memX, const int& memY, int x, int y, int B)
	{
		if (x<0)      x = 0;
		if (y<0)      y = 0;
		if (x>memX-1) x = memX-1;
		if (y>memY-1) y = memY-1;
		MemblockWriteByte(mem,12+4*(x+y*memX),B);
	}
	// Write (B)
	inline void MemblockWriteB(int mem, const int& memX, const int& memY, int x, int y, unsigned char B)
	{
		if (x<0)      x = 0;
		if (y<0)      y = 0;
		if (x>memX-1) x = memX-1;
		if (y>memY-1) y = memY-1;
		MemblockWriteByte(mem,12+4*(x+y*memX),B);
	}
	// Write (A)
	inline void MemblockWriteA(int mem, int pos, int A)
	{
		MemblockWriteByte(mem,pos+3,A);
	}
	// Write (A)
	inline void MemblockWriteA(int mem, int pos, unsigned char A)
	{
		MemblockWriteByte(mem,pos+3,A);
	}
	// Write (A)
	inline void MemblockWriteA(int mem, const int& memX, const int& memY, int x, int y, int A)
	{
		if (x<0)      x = 0;
		if (y<0)      y = 0;
		if (x>memX-1) x = memX-1;
		if (y>memY-1) y = memY-1;
		MemblockWriteByte(mem,12+4*(x+y*memX)+3,A);
	}
	// Write (A)
	inline void MemblockWriteA(const int& mem, const int& memX, const int& memY, int x, int y, unsigned char A)
	{
		if (x<0)      x = 0;
		if (y<0)      y = 0;
		if (x>memX-1) x = memX-1;
		if (y>memY-1) y = memY-1;
		MemblockWriteByte(mem,12+4*(x+y*memX)+3,A);
	}
}

#endif