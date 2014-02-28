// thc_memblock.cpp

#include "thc_memblock.h"
#include "DarkGDK.h"
#include "thc_free.h"
#include "thc_is.h"
#include "thc_delete.h"
#include "thc_math.h"


namespace thc
{
//---------------------------------------------------------------------------
	DWORD ALPHA_ON(DWORD color)
	{
		color = color & 0x00FFFFFF;
		return color;
	}
//---------------------------------------------------------------------------
	DWORD ALPHA_OFF(DWORD color)
	{
		color = color | 0xFF000000;
		return color;
	}
//---------------------------------------------------------------------------
	DWORD SET_ALPHA(DWORD color, unsigned char value0_255)
	{
		color = color | ((DWORD)value0_255)<<24; 
		return color;
	}
//---------------------------------------------------------------------------
	DWORD RGBA(int r, int g, int b, int a)
	{                                                                        
		DWORD cR=(DWORD)r;   DWORD cG=(DWORD)g;   DWORD cB=(DWORD)b;   DWORD cA=(DWORD)a;
		DWORD color = (cA << 24) + (cR << 16) + (cG << 8) + cB;         
		return color;
	}
//---------------------------------------------------------------------------
	int RGBA_R(DWORD color)
	{
		DWORD cR = (color & 0x00FF0000) >> 16;		return (int)cR;
	}
//---------------------------------------------------------------------------
	int RGBA_G(DWORD color)
	{
		DWORD cG = (color & 0x0000FF00) >> 8;	   return (int)cG;
	}
//---------------------------------------------------------------------------
	int RGBA_B(DWORD color)
	{
		DWORD cB = (color & 0x000000FF);			   return (int)cB;
	}
//---------------------------------------------------------------------------
	int RGBA_A(DWORD color)
	{
		DWORD cA = (color & 0xFF000000) >> 24;		return (int)cA;
	}
//---------------------------------------------------------------------------
	int ImageFromMemblock( int mem )
	{
		if (IsMemblock(mem)==0) return 0;
		int img=FreeImage();
		dbMakeImageFromMemblock(img,mem);
		if (IsImage(img)==0) return 0;            
		return img; 
	}
//---------------------------------------------------------------------------
	int MemblockFromImage( int img )
	{
		if (IsImage(img)==0) return 0;
		int mem=FreeMemblock();
		dbMakeMemblockFromImage(mem,img);
		if (IsMemblock( mem )==0) return 0;            
		return mem; 
	}
//---------------------------------------------------------------------------
	int MemblockCreate(int size)
	{
		int mem=FreeMemblock();
		dbMakeMemblock(mem,size);
		if (IsMemblock(mem)==0) return 0;
		return mem;
	}
//---------------------------------------------------------------------------
	int MemblockCreate(int dx,int dy, int dz)
	{
		int mem=FreeMemblock();
		dbMakeMemblock(mem,12+dx*dy*(dz>>3));
		if (MemblockHeader(mem,dx,dy,dz)==0) return 0;
		return mem;
	}
//---------------------------------------------------------------------------
	int MemblockHeader(int mem, int dx, int dy, int dz)
	{
		if (IsMemblock(mem)==0) return 0;
		MemblockWriteDword(mem,0,(DWORD)dx);
		MemblockWriteDword(mem,4,(DWORD)dy);
		MemblockWriteDword(mem,8,(DWORD)dz);
		return 1;
	}
//---------------------------------------------------------------------------
	int MemblockX( int mem )
	{
		if (IsMemblock(mem)==0) return 0;
		return (int)MemblockReadDword(mem,0); 
	}
//---------------------------------------------------------------------------
	int MemblockY( int mem )
	{
		if (IsMemblock(mem)==0) return 0;
		return (int)MemblockReadDword(mem,4); 
	}
//---------------------------------------------------------------------------
	int MemblockZ( int mem )
	{
		if (IsMemblock(mem)==0) return 0;
		return (int)MemblockReadDword(mem,8); 
	}
//---------------------------------------------------------------------------
	int MemblockSetColorKey(int mem, DWORD color_key)
	{
		// erzeugt einen neuen memblock
		if (IsMemblock(mem)==0) return 0;
		int memX=MemblockX(mem);
		int memY=MemblockY(mem);

		int final=MemblockCreate(memX,memY,32);
		if (final==0) return 0;

		int x,y,index;
		DWORD color;
		for (y=0; y<memY; y++)
		{
			for (x=0; x<memX; x++)
			{
				index=12+4*(x+y*memX);
				color=MemblockReadDword(mem,index);
				if (color==color_key)
				{
					MemblockWriteDword(final,index,ALPHA_ON(color_key));
				}
				else
				{
					MemblockWriteDword(final,index,ALPHA_OFF(color));
				}
			}
		}
		return final;	
	}
//---------------------------------------------------------------------------
	int MemblockReplaceColor(int mem, DWORD color_old, DWORD color_new)
	{
		if (IsMemblock(mem)==0) return 0;
		int memX=MemblockX(mem);
		int memY=MemblockX(mem);

		// erzeugt einen neuen memblock

		int final=MemblockCreate(memX,memY,32);
		if (final==0) return 0;

		int x,y,index;
		DWORD color;
		for (y=0; y<memY; y++)
		{
			for (x=0; x<memX; x++)
			{
				index=12+4*(x+y*memX);
				color=MemblockReadDword(mem,index);
				if (color==color_old)
				{
					MemblockWriteDword(final,index,color_new);
				}
				else
				{
					MemblockWriteDword(final,index,color);
				}
			}
		}
		return final;	
	}
//---------------------------------------------------------------------------	
	int MemblockFromColor( int dx, int dy, DWORD color)
	{
		  // Create Memblock
     		  int mem=MemblockCreate(dx,dy,32);
			  if (mem==0) return 0;   

			// Write Memblock Colors
				int i,j,pos;
				for (j=0; j<dy; j++)        
				{
					for (i=0; i<dx; i++)        
					{ 
						pos=12+4*(i+j*dx);
						MemblockWriteDword(mem,pos,color);   
					}
				}

			return mem;
	}
//---------------------------------------------------------------------------	
	int MemblockFromColorWithBorder( int dx, int dy, DWORD color, int border, DWORD bordercolor)
	{
		// Create Memblock
   			int mem=MemblockCreate(dx,dy,32);
			if (mem==0) return 0;   
		        
		// Write Memblock Colors
			int i,j,pos;
			for (j=0; j<dy; j++){
			for (i=0; i<dx; i++){ 
				pos=12+4*(i+j*dx);
				MemblockWriteDword(mem,pos,color);   
			}}
		         
		// Write Memblock Border
			for (j=0; j<dy; j++){
			for (i=0; i<dx; i++){
				if ((i<border) || (j<border) || (i>dx-1-border) || (j>dy-1-border))
				{
					pos = 12+4*(i+j*dx);             
					MemblockWriteDword(mem,pos,bordercolor);   
				}
			}}   
		return mem;
	}
//---------------------------------------------------------------------------
	int MemblockMultiplyWithColor(int mem, DWORD color, float factor)
	{
		// erzeugt neuen memblock
		if (IsMemblock(mem)==0) return 0;
		int memX=MemblockX(mem);
		int memY=MemblockY(mem);

		int memfinal=MemblockCreate(memX,memY,32);
		if (memfinal==0) return 0;

		if (factor<0.0f) factor=0.5f;
		if (factor>1.0f) factor=0.5f;
		float cr=(float)RGBA_R(color);
		float cg=(float)RGBA_G(color);
		float cb=(float)RGBA_B(color);
		float fr,fg,fb;
		int i,j,index;
		float divisor = 1.0f-factor;
		DWORD final;

		for (j=0; j<memY; j++)
		{		
			for (i=0; i<memX; i++)
			{
				index=12+4*(i+j*memX);
				fr=(float)MemblockReadByte(mem,index+0)*divisor+cr*factor;
				fg=(float)MemblockReadByte(mem,index+1)*divisor+cg*factor;
				fb=(float)MemblockReadByte(mem,index+2)*divisor+cb*factor;
				if (fr<0.0f)	fr=0.0f;			
				if (fg<0.0f)	fg=0.0f;			
				if (fb<0.0f)	fb=0.0f;			
				if (fr>255.0f) fr=255.0f;
				if (fg>255.0f) fg=255.0f;
				if (fb>255.0f) fb=255.0f;
				final=RGBA(Round(fr),Round(fg),Round(fb),255);
				MemblockWriteDword(memfinal,index,final);
			}
		}
		return memfinal;	
	}
//---------------------------------------------------------------------------	
	int MemblockCut(int mem, int x1, int y1, int x2, int y2)
	{
		//erzeugt einen neuen memblock
		if (IsMemblock(mem)==0) return 0;
		int memX = MemblockX(mem);
		int memY = MemblockY(mem);  

		// Tauschen      
		if (x2<x1) {int tmpX=x1;	x1=x2;   x2=tmpX;	}
		if (y2<y1) {int tmpY=y1;	y1=y2;   y2=tmpY;	}

		int dx=x2-x1; if (dx==0) return 0;
		int dy=y2-y1; if (dy==0) return 0;

		if (x1<0) x1=0;			if (y1<0) y1=0;
		if (x2<0) x2=0;			if (y2<0) y2=0;
		if (x1>memX) x1=memX;   if (y1>memY) y1=memY;
		if (x2>memX) x2=memX;   if (y2>memY) y2=memY;
      
		// Create Memblock
		int cut=MemblockCreate(dx,dy,32);
		if (cut==0) return 0;   
      
		// Cut
		DWORD color;
		int i,j,pos;
		for (j=y1; j<y2; j++){             
		for (i=x1; i<x2; i++){
				pos=12+4*(i+j*memX);
				color=ALPHA_OFF(MemblockReadDword(mem,pos));
				pos=12+4*(i-x1+(j-y1)*dx);
				MemblockWriteDword(cut,pos,color);
			}}
		return cut;
	}
//---------------------------------------------------------------------------	
	int MemblockCopy(int mem)
	{
		if (IsMemblock(mem)==0) return 0;
		const int memX = MemblockX(mem);
		const int memY = MemblockY(mem);       
		int final = MemblockCreate(memX,memY,32);
		if (final==0) return 0;
		
		int i,j,index;	DWORD color;
		for (j=0; j<memY; j++){
			for (i=0; i<memX; i++){
				index=12+4*(i+j*memX);
				color=MemblockReadDword(mem,index);
				MemblockWriteDword(final,index,color);
			}
		}
		return final;
	}

	DWORD _bilinear_pixel(int mem, float fx, float fy, int memX, int memY)
	{
	    
		const int i=(int)fx;
		const int j=(int)fy;
		const float x=fx-(float)i;
		const float y=fy-(float)j;
		const DWORD cA=MemblockReadDword(mem, i,   j,   memX, memY);
		const DWORD cB=MemblockReadDword(mem, i+1, j,   memX, memY);
		const DWORD cC=MemblockReadDword(mem, i+1, j+1, memX, memY);
		const DWORD cD=MemblockReadDword(mem, i,   j+1, memX, memY);

		const float rA=(float)RGBA_R(cA);
		const float rB=(float)RGBA_R(cB);
		const float rC=(float)RGBA_R(cC);
		const float rD=(float)RGBA_R(cD);

		const float gA=(float)RGBA_G(cA);
		const float gB=(float)RGBA_G(cB);
		const float gC=(float)RGBA_G(cC);
		const float gD=(float)RGBA_G(cD);
	   
		const float bA=(float)RGBA_B(cA);
		const float bB=(float)RGBA_B(cB);
		const float bC=(float)RGBA_B(cC);
		const float bD=(float)RGBA_B(cD);
	     
		const float e=(1.0f-x);
		const float f=(1.0f-y);
		const float fr = rA*e*f+rB*x*f+rC*x*y+rD*e*y;   
		const float fg = gA*e*f+gB*x*f+gC*x*y+gD*e*y;   
		const float fb = bA*e*f+bB*x*f+bC*x*y+bD*e*y;   

		return RGBA((int)fr,(int)fg,(int)fb,255);
	}
	int MemblockScale( int mem, int SizeX, int SizeY)
	{
   	 if (IsMemblock(mem)==0) return 0;
                  
		 // Memblock Size
		const int memX = MemblockX(mem);
		const int memY = MemblockY(mem);       

		if ((memX==SizeX) && (memY==SizeY)) return MemblockCopy(mem);

		// Zoom Faktoren
		const float zoomX = ((float)SizeX)/((float)memX);
		const float zoomY = ((float)SizeY)/((float)memY);

		 // Create Memblock
		int final = MemblockCreate(SizeX,SizeY,32);
		if (final==0) return 0;

		// Locals
	    int x, y, index;
	    float fx, fy;
		DWORD color;
       
		// Bicubische Interpolation
		for (y=0; y<SizeY; y++) {
		for (x=0; x<SizeX; x++) {
			fx=((float)x)/zoomX;
      		fy=((float)y)/zoomY;
            index=12+4*(x+y*SizeX);
		    color=_bilinear_pixel(mem,fx,fy,memX,memY);         
            MemblockWriteDword(final,index,color);		       
        }}
		return final;
	}
}