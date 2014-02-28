// thc_memblock_rotation.cpp

#include "thc_memblock_rotation.h"
#include "thc_memblock.h"
#include "thc_is.h"
#include "thc_math.h"

namespace thc
{

// *********************************************************************
bool MemblockFlipH( int mem )
// *********************************************************************
{
	// Abbruchbedingung
 	if (IsMemblock(mem)==0) return 0;

 	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem);  
	int maxX = memX >> 1;
	int maxY = memY >> 1;
    
	DWORD color1, color2;
	int i,j,index1,index2;
		 
	for (j=0; j<memY; j++) 
	{
		for (i=0; i<maxX; i++) 
		{
			index1=12+4*(i+j*memX);
			index2=12+4*(memX-1-i+j*memX);
			color1=MemblockReadDword(mem,index1);
			color2=MemblockReadDword(mem,index2);
			MemblockWriteDword(mem,index2,color1);
			MemblockWriteDword(mem,index1,color2);
		}
	}
	return 1;	
}
// *********************************************************************
bool MemblockFlipV( int mem )
// *********************************************************************
{
	// Abbruchbedingung
 	if (IsMemblock(mem)==0) return 0;

 	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem);  
	int maxX = memX >> 1;
	int maxY = memY >> 1;

	DWORD color1, color2;
	int i,j,index1,index2;
	for (j=0; j<maxY; j++)
	{
		for (i=0; i<memX; i++)
		{
			index1=12+4*(i+j*memX);
			index2=12+4*(i+(memY-1-j)*memX);
			color1=MemblockReadDword(mem,index1);
			color2=MemblockReadDword(mem,index2);
			MemblockWriteDword(mem,index2,color1);
			MemblockWriteDword(mem,index1,color2);
		}
	}
	return 1;	
}


// *********************************************************************
int MemblockRotate90 ( int mem )
// *********************************************************************
{
	// Abbruchbedingung
 	if (IsMemblock(mem)==0) return 0;

 	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem);  

	// Neues Image
	int final=MemblockCreate(memY,memX,32);
	if (final==0) return 0;
        
	// LOCALS
	int i,j,pos;
	DWORD color;
	for (j=0; j<memY; j++)  
	{
		for (i=0; i<memX; i++)  
		{
			pos=12+4*(i+j*memX);
			color=MemblockReadDword(mem,pos);
			
			pos=12+4*(j+(memX-1-i)*memY);
			MemblockWriteDword(final,pos,color);
		}
	}
	return final;		
}
// *********************************************************************
int MemblockRotate180 ( int mem )
// *********************************************************************
{
	// Abbruchbedingung
 	if (IsMemblock(mem)==0) return 0;

 	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem); 

	// Neues Image
	int final=MemblockCreate(memX,memY,32);
	if (final==0) return 0;
	        
	// LOCALS
	int i,j,pos;
	DWORD color;
	for (j=0; j<memY; j++)  
	{
		for (i=0; i<memX; i++)  
		{
			pos=12+4*(i+j*memX);
			color=MemblockReadDword(mem,pos);
			 
			pos=12+4*(memX-1-i+(memY-1-j)*memX);
			MemblockWriteDword(final,pos,color);
		}
	}
	return final;		
}
// *********************************************************************
int MemblockRotate270 ( int mem )
// *********************************************************************
{
	// Abbruchbedingung
 	if (IsMemblock(mem)==0) return 0;

 	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem); 

	// Neues Image
	int final=MemblockCreate(memY,memX,32);
	if (final==0) return 0;
	        
	// LOCALS
	int i,j,pos;
	DWORD color;
	for (j=0; j<memY; j++)  
	{
		for (i=0; i<memX; i++)  
		{
		pos=12+4*(i+j*memX);
		color=MemblockReadDword(mem,pos);
			 
		pos=12+4*(memY-1-j+i*memY);
		MemblockWriteDword(final,pos,color);
		}
	}
	return final;		
}
// *********************************************************************
int MemblockRotateB ( int mem, float angle, DWORD bgcolor)
// *********************************************************************
{
	// Abbruchbedingung
 	if (IsMemblock(mem)==0) return 0;

 	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem); 

	// Winkel
    angle = WrapAngle(angle);

	// Abbruchbedingungen	    
	if (angle==0.0f)   return MemblockCopy(mem);
	if (angle==90.0f)  return MemblockRotate90 ( mem );
	if (angle==180.0f) return MemblockRotate180( mem );
	if (angle==270.0f) return MemblockRotate270( mem );

	// alpha 	 
	const float alpha=(360.0f-angle)*DEGTORAD;
	const float sin_alpha=(float)sin(alpha);
	const float cos_alpha=(float)cos(alpha);
	// gamma
	const float gamma=angle*DEGTORAD;
	const float sin_gamma=(float)sin(gamma);
	const float cos_gamma=(float)cos(gamma);
		  
	// BERECHNNUNG des Mittelpunktes von MEM
	const float mXh=0.5f*(float)memX;
	const float mYh=0.5f*(float)memY;

	// BERECHNNUNG der Eckpunkte
	const float Ax= mXh, 	Ay=-mYh;
	const float Bx=-mXh,	By=-mYh;
	const float Cx=-mXh, 	Cy= mYh;
	const float Dx= mXh, 	Dy= mYh;		

	// TRANSFORMATION der Eckpunkte
	float Anx=Ax*cos_alpha - Ay*sin_alpha;		 
	float Any=Ax*sin_alpha + Ay*cos_alpha;
	float Bnx=Bx*cos_alpha - By*sin_alpha;		 
	float Bny=Bx*sin_alpha + By*cos_alpha;
	float Cnx=Cx*cos_alpha - Cy*sin_alpha;		 
	float Cny=Cx*sin_alpha + Cy*cos_alpha;
	float Dnx=Dx*cos_alpha - Dy*sin_alpha;		 
	float Dny=Dx*sin_alpha + Dy*cos_alpha;
		 
	// BERECHNUNG der FINAL WIDTH and HEIGHT
	float minX=0.0f, maxX=0.0f;
	float minY=0.0f, maxY=0.0f;
	if (Anx<minX) minX=Anx;		 if (Any<minY) minY=Any;
	if (Anx>maxX) maxX=Anx;		 if (Any>maxY) maxY=Any;		 
	if (Bnx<minX) minX=Bnx;		 if (Bny<minY) minY=Bny;
	if (Bnx>maxX) maxX=Bnx;		 if (Bny>maxY) maxY=Bny;		 
	if (Cnx<minX) minX=Cnx;		 if (Cny<minY) minY=Cny;
	if (Cnx>maxX) maxX=Cnx;		 if (Cny>maxY) maxY=Cny;		 
	if (Dnx<minX) minX=Dnx;		 if (Dny<minY) minY=Dny;
	if (Dnx>maxX) maxX=Dnx;		 if (Dny>maxY) maxY=Dny;		 
	
	float fdx=maxX-minX;
	float fdy=maxY-minY;

	int   dx=Round(fdx);
	int   dy=Round(fdy);

	// BERECHNUNG des Mittelpunktes von FINAL
	float fdxh=0.5f*fdx;
	float fdyh=0.5f*fdy;
		 	 
	// FINAL MEMBLOCK
	int final=MemblockCreate(dx,dy,32);
    if (final==0) return 0;
	        
	// LET'S ROTATE
	int i,j,pos,x,y;
	DWORD color;
	float x0,y0,x1,y1;

	// Fuer alle Punkte im Zielbild den entsprechenden Punkt im Ausgangsbild  
	// suchen. Dadurch entstehen keine Luecken im Bild.                      

	for (j=0; j<dy; j++) 
	{
		for (i=0; i<dx; i++) 
		{
			x0=(float)i-fdxh; // relativ zu FinalMem Mittelpunkt
			y0=(float)j-fdyh; // relativ zu FinalMem Mittelpunkt
			x1=(cos_gamma*x0-sin_gamma*y0)+mXh; // relativ zu SourceMem Mittelpunkt
			y1=(sin_gamma*x0+cos_gamma*y0)+mYh; // relativ zu SourceMem Mittelpunkt
			x=Round(x1);
			y=Round(y1);
			
			// PIXEL von SourceMem
			if ((x>=0) && (y>=0) && (x<memX) && (y<memY))
			{	
	  			pos=12+4*(x+y*memX);
	  			color=MemblockReadDword(mem,pos);
   			}
   			else
   			{
				color=bgcolor;
			}
			// PIXEL in FinalMem
   			pos=12+4*(i+j*dx);
			MemblockWriteDword(final,pos,color);
		}
	}	
	return final;		
}

// *********************************************************************
int MemblockRotateA ( int mem, float angle)
// *********************************************************************
{
	return MemblockRotateB( mem, angle, RGBA(255,0,255,255));
}

// *********************************************************************
int MemblockSkewH ( int mem, float angle)
// *********************************************************************
{
	// Abbruchbedingung
 	if (IsMemblock(mem)==0) return 0;

 	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem); 
	return 1;	
}
// *********************************************************************
int MemblockSkewV ( int mem, float angle)
// *********************************************************************
{
	// Abbruchbedingung
 	if (IsMemblock(mem)==0) return 0;

 	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem); 

	return 1;	
}


} // END NAMESPACE