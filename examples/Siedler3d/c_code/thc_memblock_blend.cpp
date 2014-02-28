// thc_memblock_blend.cpp

#include "DarkGDK.h"
#include "thc_memblock_blend.h"
#include "thc_memblock.h"
#include "thc_math.h"
#include "thc_is.h"

namespace thc
{
// ################################################
int MemblockBlend( int mem1, int mem2)
// ################################################
{
	// Abbruchbedingung
	if (IsMemblock(mem1)==0) return 0;
	if (IsMemblock(mem2)==0) return 0;

	// Memblock Size
	int mem1X = MemblockX(mem1);
	int mem1Y = MemblockY(mem1);  
	int mem2X = MemblockX(mem2);
	int mem2Y = MemblockY(mem2);  

	// Abbruchbedingung
	if ((mem1X!=mem2X) || (mem1Y!=mem2Y)) return 0;

	// Final Memblock
	int final=MemblockCreate(mem1X,mem1Y,32);
	if (final==0) return 0;
	
	// LOCALS
	float c1_r, c1_g, c1_b, c1_fact;
	float c2_r, c2_g, c2_b, c2_fact;
	float blend_fact,fr,fg,fb;
	int ir,ig,ib, x,y,index;

	// LOOP
	for (y=0; y<mem1Y; y++)
	{
	for (x=0; x<mem1X; x++)
	{
		//Memblock Index
		index=12+4*(x+y*mem1X);

		//Calculate Color From Fader
		blend_fact=(float)MemblockReadByte(mem2,index+3);

		//Calculate Color (1)
		c1_fact=(255.0f-blend_fact)/255.0f;
		c1_r=(float)MemblockReadByte(mem1,index+0);
		c1_g=(float)MemblockReadByte(mem1,index+1);
		c1_b=(float)MemblockReadByte(mem1,index+2);

		//Calculate Color (2)
		c2_fact=blend_fact/255.0f;
		c2_r=(float)MemblockReadByte(mem2,index+0);
		c2_g=(float)MemblockReadByte(mem2,index+1);
		c2_b=(float)MemblockReadByte(mem2,index+2);

		//Final Color :: Calculate
		fr = c1_fact*c1_r + c2_fact*c2_r;
		fg = c1_fact*c1_g + c2_fact*c2_g;
		fb = c1_fact*c1_b + c2_fact*c2_b;

		//Final Color :: Round
		ir=Round(fr);
		ig=Round(fg);
		ib=Round(fb);

		//Final Color :: Check
		if (ir<0) 	ir=0;
		if (ig<0) 	ig=0;
		if (ib<0) 	ib=0;
		if (ir>255) ir=255;
		if (ig>255) ig=255;
		if (ib>255) ib=255;

		//Final Color :: Save
		MemblockWriteDword(final,index,RGBA(ir,ig,ib,255));
	}
	}
	return final;
}
// ################################################
int MemblockBlend( int mem1, int mem2, int memAlpha)
// ################################################
{
	// Abbruchbedingung
    if (IsMemblock(mem1)==0) return 0;
    if (IsMemblock(mem2)==0) return 0;
    if (IsMemblock(memAlpha)==0) return 0;      
		               
	// Memblock Size
    int mem1X = MemblockX(mem1);
    int mem1Y = MemblockY(mem1);  
    int mem2X = MemblockX(mem2);
    int mem2Y = MemblockY(mem2);  
    int mem3X = MemblockX(memAlpha);
    int mem3Y = MemblockY(memAlpha);  
      
	// Abbruchbedingung
	if ((mem1X!=mem2X) || (mem1Y!=mem2Y)) return 0;
	if ((mem1X!=mem3X) || (mem1Y!=mem3Y)) return 0;
    
	// Final Memblock
	int final=MemblockCreate(mem1X,mem1Y,32);
	if (final==0) return 0;
	
	// LOCALS
	float c1_r, c1_g, c1_b, c1_fact;
	float c2_r, c2_g, c2_b, c2_fact;
	float c3_r, c3_g, c3_b;
	float blend_fact,fr,fg,fb;
	int ir,ig,ib, x,y,index;

	// LOOP
	for (y=0; y<mem1Y; y++)
	{
	for (x=0; x<mem1X; x++)
	{
		//Memblock Index
		index=12+4*(x+y*mem1X);

		//Calculate Color From Fader
		c3_r=(float)MemblockReadByte(memAlpha,index+0);
		c3_g=(float)MemblockReadByte(memAlpha,index+1);
		c3_b=(float)MemblockReadByte(memAlpha,index+2);      
		blend_fact=(c3_r+c3_g+c3_b)/3.0f;

		//Calculate Color (1)
		c1_fact=(255.0f-blend_fact)/255.0f;
		c1_r=(float)MemblockReadByte(mem1,index+0);
		c1_g=(float)MemblockReadByte(mem1,index+1);
		c1_b=(float)MemblockReadByte(mem1,index+2);

		//Calculate Color (2)
		c2_fact=blend_fact/255.0f;
		c2_r=(float)MemblockReadByte(mem2,index+0);
		c2_g=(float)MemblockReadByte(mem2,index+1);
		c2_b=(float)MemblockReadByte(mem2,index+2);

		//Final Color :: Calculate
		fr = c1_fact*c1_r + c2_fact*c2_r;
		fg = c1_fact*c1_g + c2_fact*c2_g;
		fb = c1_fact*c1_b + c2_fact*c2_b;

		//Final Color :: Round
		ir=Round(fr);
		ig=Round(fg);
		ib=Round(fb);

		//Final Color :: Check
		if (ir<0) 	ir=0;
		if (ig<0) 	ig=0;
		if (ib<0) 	ib=0;
		if (ir>255) ir=255;
		if (ig>255) ig=255;
		if (ib>255) ib=255;

		//Final Color :: Save
		MemblockWriteDword(final,index,RGBA(ir,ig,ib,255));
	}
	}
	return final;
}

} // END NAMESPACE