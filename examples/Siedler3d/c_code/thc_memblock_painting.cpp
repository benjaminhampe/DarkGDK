// thc_memblock_painting.cpp

#include "thc_memblock_painting.h"
#include "thc_memblock.h"
#include "thc_is.h"
#include "thc_math.h"

namespace thc
{

///////////////////////////////////////////////////////////////////////
int MemblockDrawDot(int mem, int x, int y, DWORD color)
///////////////////////////////////////////////////////////////////////
{
   // User Identification
      if (IsMemblock(mem)==0) return 0;
        
	// Memblock Size
      int memX = MemblockX(mem);
      int memY = MemblockX(mem);  

   // Abbruchbedingung
      if ((x<0) || (y<0) || (x>=memX) || (y>=memY)) return 0;

   // Zeichnen
      MemblockWriteDword(mem,12+4*(x+y*memX),color);
   return 1;
}
///////////////////////////////////////////////////////////////////////
int MemblockDrawLineA(int mem, int x1, int y1, int x2, int y2, DWORD color)
///////////////////////////////////////////////////////////////////////
{
	// User Identification
    if (IsMemblock(mem)==0) return 0;
		  
	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem);  

	// Bresenham Algorithmus für Raster Linien (ohne Gleitkommas und Multiplikationen)
    int i, deltax, deltay, numpixels;
    int d, dinc1, dinc2;
	int x, xinc1, xinc2;
	int y, yinc1, yinc2;
	
	deltax = abs(x2 - x1);
	deltay = abs(y2 - y1);
	
	if (deltax >= deltay)
	{
		numpixels = deltax + 1;
	    d = (deltay<<1) - deltax;
	    dinc1 = deltay << 1;
	    dinc2 = (deltay - deltax) << 1;
	    xinc1 = 1;
	    xinc2 = 1;
	    yinc1 = 0;
	    yinc2 = 1;
	} 
	else 
	{
	   	numpixels = deltay + 1;
	    d = (2 * deltax) - deltay;
	    dinc1 = deltax << 1;
	    dinc2 = (deltax - deltay) << 1;
	    xinc1 = 0;
	    xinc2 = 1;
	    yinc1 = 1;
	    yinc2 = 1;
	}	
	if (x1 > x2)
	{
	    xinc1 = -xinc1;
	    xinc2 = -xinc2;
	}
	if (y1 > y2)
	{
	    yinc1 = -yinc1;
	    yinc2 = -yinc2;
	}
	
	x=x1;
	y=y1;
	
	for (i=0; i<numpixels; i++) 
	{
		MemblockWriteDword(mem,memX,memY,x,y,color);		
	    if (d < 0)
		{
			d = d + dinc1;
	        x = x + xinc1;
	        y = y + yinc1;
	    }
		else 
		{
	        d = d + dinc2;
	        x = x + xinc2;
	        y = y + yinc2;
	    }
	}
	return 1;
}
// *********************************************************************
int MemblockDrawLineB(int mem, int x1, int y1, int x2, int y2, DWORD color1, DWORD color2)
// *********************************************************************
{
	// User Identification
    if (IsMemblock(mem)==0) return 0;

	// Abbruchbedingung
    if (color1==color2) return MemblockDrawLineA(mem, x1, y1, x2, y2, color1);
    
	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem);  

	// COLOR DIFFERENCES
    const int
	ir1=RGBA_R(color1), ir2=RGBA_R(color2), dr=ir2-ir1,
    ig1=RGBA_G(color1), ig2=RGBA_G(color2), dg=ig2-ig1,
    ib1=RGBA_B(color1), ib2=RGBA_B(color2), db=ib2-ib1,
    ia1=RGBA_A(color1), ia2=RGBA_A(color2), da=ia2-ia1;   

    const float
	r1=(float)ir1,	r2=(float)ir2, fdr=r2-r1,
    g1=(float)ig1, g2=(float)ig2, fdg=g2-g1,
    b1=(float)ib1, b2=(float)ib2, fdb=b2-b1,
    a1=(float)ia1, a2=(float)ia2, fda=a2-a1;
	
	float f;
    int cR, cG, cB, cA;
    DWORD color;

	// Bresenham Algorithmus für Raster Linien (ohne Gleitkommas und Multiplikationen)
    int i, deltax, deltay, numpixels;
    int d, dinc1, dinc2;
	int x, xinc1, xinc2;
	int y, yinc1, yinc2;
	
	deltax = abs(x2 - x1);
	deltay = abs(y2 - y1);
	
	if (deltax >= deltay)
	{
		numpixels = deltax + 1;
	    d = (2 * deltay) - deltax;
	    dinc1 = deltay << 1;
	    dinc2 = (deltay - deltax) << 1;
	    xinc1 = 1;
	    xinc2 = 1;
	    yinc1 = 0;
	    yinc2 = 1;
	} 
	else 
	{
	   	numpixels = deltay + 1;
	    d = (2 * deltax) - deltay;
	    dinc1 = deltax << 1;
	    dinc2 = (deltax - deltay) << 1;
	    xinc1 = 0;
	    xinc2 = 1;
	    yinc1 = 1;
	    yinc2 = 1;
	}	
	if (x1 > x2)
	{
	    xinc1 = -xinc1;
	    xinc2 = -xinc2;
	}
	if (y1 > y2)
	{
	    yinc1 = -yinc1;
	    yinc2 = -yinc2;
	}
	x=x1;
	y=y1;
	
	for (i=0; i<numpixels; i++) 
	{
		f = (float)i/(float)numpixels;
        // R - COLOR
        if (dr==0) {   cR=ir1;  }
        else       {   cR=Round(r1+fdr*f); if (cR<0) cR=0; if (cR>255) cR=255; }
        
		// G - COLOR
        if (dg==0) {   cG=ig1;  }
        else       {   cG=Round(g1+fdg*f); if (cG<0) cG=0; if (cG>255) cG=255; }
         
		// B - COLOR
        if (db==0) {   cB=ib1;  }
        else       {   cB=Round(b1+fdb*f); if (cB<0) cB=0; if (cB>255) cB=255; }
        
		// A - COLOR
        if (da==0) {   cA=ia1;  }
        else       {   cA=Round(a1+fda*f); if (cA<0) cA=0; if (cA>255) cA=255; }
        
		// FINAL COLOR
        color=RGBA(cR,cG,cB,cA);        
		
		// WRITE COLOR DWORD
		MemblockWriteDword(mem,memX,memY,x,y,color);		
			  
	    if (d < 0)
		{
			d = d + dinc1;
	        x = x + xinc1;
	        y = y + yinc1;
	    }
		else 
		{
	        d = d + dinc2;
	        x = x + xinc2;
	        y = y + yinc2;
	    }
	}
	return 1;
}

// *********************************************************************
int MemblockDrawBoxA(int mem, int x1, int y1, int x2, int y2, DWORD color)
// *********************************************************************
{
    //  c ---- c
    //  |  \   |
    //  |   \  |
    //  c ---- c

	// Abbruchbedingung
    if (IsMemblock(mem)==0) return 0;

	// Abbruchbedingung
	int alpha=RGBA_A(color);
	if (alpha==0) return 0;
             
	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem); 

	// Grenzen
    if (x1<0) x1=0;    if (y1<0) y1=0;
    if (x2<0) x2=0;    if (y2<0) y2=0;
    if (x1>memX) x1=memX;
    if (y1>memY) y1=memY;
    if (x2>memX) x2=memX;
    if (y2>memY) y2=memY;

	// Differences
    int dx=x2-x1;
    int dy=y2-y1;
      
    // Abbruchbedingung
    if ((dx==0) && (dy==0)){ return MemblockDrawDot(mem,x1,y1,color);											}

    // Index Variablen
    int istart, iende;
    int jstart, jende;

    // Fallunterscheidung
    if ((dx==0) && (dy>0)) { istart=x1; 	iende=x1+1; 	jstart=y1; 	jende=y2; 	if (iende>memX){return 0;}		}      
    if ((dx==0) && (dy<0)) { istart=x1; 	iende=x1+1; 	jstart=y2; 	jende=y1; 	if (iende>memX){return 0;}		}      
    if ((dx>0) && (dy>0))  { istart=x1; 	iende=x2;   	jstart=y1; 	jende=y2;							 		}
    if ((dx>0) && (dy==0)) { istart=x1; 	iende=x2;   	jstart=y1; 	jende=y1+1; if (jende>memY){return 0;}		}      
    if ((dx>0) && (dy<0))  { istart=x1; 	iende=x2;   	jstart=y2; 	jende=y1; 									}      
    if ((dx<0) && (dy>0))  { istart=x2; 	iende=x1;   	jstart=y1; 	jende=y2; 									}      
    if ((dx<0) && (dy==0)) { istart=x2; 	iende=x1;   	jstart=y1; 	jende=y1+1; if (jende>memY){return 0;}		}      
    if ((dx<0) && (dy<0))  { istart=x2; 	iende=x1;   	jstart=y2; 	jende=y1; 									}      
        
    int i,j,pos;

	// Zeichnen
	if (alpha==255)
	{
		for (j=jstart; j<jende; j++)
		{
			for (i=istart; i<iende; i++)
			{
				pos=12+4*(i+j*memX);
				MemblockWriteDword(mem,pos,color);
			}
		}
	}
	else
	{
		const float factor0=(float)alpha/255.0f;
		const float cr=(float)RGBA_R(color);
		const float cg=(float)RGBA_G(color);
		const float cb=(float)RGBA_B(color);
		const float factor1=1.0f-factor0;
		DWORD bgcolor;
		float r,g,b;

		for (j=jstart; j<jende; j++)
		{
			for (i=istart; i<iende; i++)
			{
				pos=12+4*(i+j*memX);
				bgcolor=MemblockReadDword(mem,pos);
				r=(float)RGBA_R(bgcolor)+cr;
				g=(float)RGBA_G(bgcolor)+cg;
				b=(float)RGBA_B(bgcolor)+cb;
				if (r<0.0f) r=0.0f;
				if (g<0.0f) g=0.0f;
				if (b<0.0f) b=0.0f;
				if (r>255.0f) r=255.0f;
				if (g>255.0f) g=255.0f;
				if (b>255.0f) b=255.0f;
				MemblockWriteDword(mem,pos,RGBA(Round(r),Round(g),Round(b),255));
			}
		}
	}

    return 1;
}
// *********************************************************************
int MemblockDrawBoxB(int mem, int x1, int y1, int x2, int y2, DWORD color, int borderwidth)
// *********************************************************************
{
	// Abbruchbedingung
    if (IsMemblock(mem)==0) return 0;

    //  c ---- c
    //  |  \   |
    //  |   \  |
    //  c ---- c
                                                                        
	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem);  
	  
	// Differences
    int dx=x2-x1;
    int dy=y2-y1;

	int abs_dx=abs(dx);
	int abs_dy=abs(dy);
	        
    if (2*borderwidth>=abs_dx) return MemblockDrawBoxA(mem,x1,y1,x2,y2,color);
    if (2*borderwidth>=abs_dy) return MemblockDrawBoxA(mem,x1,y1,x2,y2,color);
       
	// Fallunterscheidung
    if ((dx==0) && (dy==0)){ return MemblockDrawDot(mem,x1,y1,color);			}
    if ((dx==0) && (dy>0)) { return MemblockDrawLineA(mem,x1,y1,x2,y2,color);	}      
    if ((dx==0) && (dy<0)) { return MemblockDrawLineA(mem,x1,y1,x2,y2,color);	}      
    if ((dx>0) && (dy==0)) { return MemblockDrawLineA(mem,x1,y1,x2,y2,color);	}      
    if ((dx<0) && (dy==0)) { return MemblockDrawLineA(mem,x1,y1,x2,y2,color);	}      
	
	// Index Variablen
    int istart, iende;
    int jstart, jende;
	
	// Fallunterscheidung     
    if ((dx>0) && (dy>0))  { istart=x1; 	iende=x2;   	jstart=y1; 	jende=y2;	}
    if ((dx>0) && (dy<0))  { istart=x1; 	iende=x2;   	jstart=y2; 	jende=y1;  	}     
    if ((dx<0) && (dy>0))  { istart=x2; 	iende=x1;   	jstart=y1; 	jende=y2;  	}          
    if ((dx<0) && (dy<0))  { istart=x2; 	iende=x1;   	jstart=y2; 	jende=y1; 	}           
 	                                
	// Zeichnen
    int i,j,pos;
    const int m1=istart+borderwidth-1;
    const int m2=jstart+borderwidth-1;
    const int m3=iende-borderwidth+1;
    const int m4=jende-borderwidth+1;
    for (j=jstart; j<=jende; j++)
	{
		for (i=istart; i<=iende; i++)
		{
			if ((i>-1) && (j>-1) && (i<memX) && (j<memY))
	  		{
				if ((i>m1) && (i<m3) && (j>m2) && (j<m4))
				{
				}
				else
				{
					pos=12+4*(i+j*memX);
					MemblockWriteDword(mem,pos,color);
				}
			}
		}
	}
	return 1;
}
// *********************************************************************
int MemblockDrawBoxC(int mem, int x1, int y1, int x2, int y2, DWORD color1, DWORD color2, DWORD color3, DWORD color4)
// *********************************************************************
{
	// User Identification
    if (IsMemblock(mem)==0) return 0;

    // c1 ---- c2
    //  |  \ Q |		Q (fx>=fy) = c1 + fx/dx*(c2-c1) + fy/dy*(c4-c2)
    //  | P \  |        P (fx<fy) = c1 + fx/dx*(c4-c3) + fy/dy*(c3-c1)
    // c3 ---- c4
                                                                                    
	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem);  

	// Differences
    int dx=x2-x1;
    int dy=y2-y1;

	// Abbruchbedingung (Box == Dot or Line )           
    if ((dx==0) && (dy==0)){ return MemblockDrawDot(mem,x1,y1,color1);											}
    if ((dx==0) && (dy>0)) { return MemblockDrawLineB(mem,x1,y1,x2,y2,color1,color3);							}      
    if ((dx==0) && (dy<0)) { return MemblockDrawLineB(mem,x2,y2,x1,y1,color1,color3);							}      
    if ((dx>0) && (dy==0)) { return MemblockDrawLineB(mem,x1,y1,x2,y2,color1,color2);							}      
    if ((dx<0) && (dy==0)) { return MemblockDrawLineB(mem,x2,y2,x1,y1,color1,color2);							}      
	
	// Index Variablen
    int istart, iende;
    int jstart, jende;
	 
	// Fallunterscheidung	  	        
    if ((dx>0) && (dy>0))  { istart=x1; 	iende=x2;   	jstart=y1; 	jende=y2;							 		}
    if ((dx>0) && (dy<0))  { istart=x1; 	iende=x2;   	jstart=y2; 	jende=y1; 									}      
    if ((dx<0) && (dy>0))  { istart=x2; 	iende=x1;   	jstart=y1; 	jende=y2; 									}          
    if ((dx<0) && (dy<0))  { istart=x2; 	iende=x1;   	jstart=y2; 	jende=y1; 									}      
     
	// COLORS
    const float 
	r1=(float)RGBA_R(color1), r2=(float)RGBA_R(color2), r3=(float)RGBA_R(color3), r4=(float)RGBA_R(color4),
    g1=(float)RGBA_G(color1), g2=(float)RGBA_G(color2), g3=(float)RGBA_G(color3), g4=(float)RGBA_G(color4),
    b1=(float)RGBA_B(color1), b2=(float)RGBA_B(color2), b3=(float)RGBA_B(color3), b4=(float)RGBA_B(color4),
    a1=(float)RGBA_A(color1), a2=(float)RGBA_A(color2), a3=(float)RGBA_A(color3), a4=(float)RGBA_A(color4);
	 	  	  	                                
	float fx,fy,fr,fg,fb,fa,fdx=(float)abs(dx),fdy=(float)abs(dy);
	int ix,iy,ir,ig,ib,ia;	  
	DWORD color;
	 
	if (istart<0) istart=0;
	if (jstart<0) jstart=0;
	if (iende>memX) iende=memX;
	if (jende>memY) jende=memY;
	 
	// Zeichnen
    int i,j,pos;
    for (j=jstart; j<jende; j++)
	{
		for (i=istart; i<iende; i++)
		{ 	  
			ix=i-istart;
			iy=j-jstart;	  	  
			fx=(float)ix/fdx;
			fy=(float)iy/fdy;

			// Q = c1 + fx/dx*(c2-c1) + fy/dy*(c4-c2)
			if (fx>fy)
			{  
				fr=r1+fx*(r2-r1)+fy*(r4-r2);	
				fg=g1+fx*(g2-g1)+fy*(g4-g2);	
				fb=b1+fx*(b2-b1)+fy*(b4-b2);	
				fa=a1+fx*(a2-a1)+fy*(a4-a2);
			}
			// P = c1 + fx/dx*(c4-c3) + fy/dy*(c3-c1)						   	 		  
			else
			{
				fr=r1+fx*(r4-r3)+fy*(r3-r1);	
				fg=g1+fx*(g4-g3)+fy*(g3-g1);	
				fb=b1+fx*(b4-b3)+fy*(b3-b1);	
				fa=a1+fx*(a4-a3)+fy*(a3-a1);
			}											 
				 
			ir=(int)fr; if (ir<0) ir=0; if (ir>255) ir=255;
			ig=(int)fg; if (ig<0) ig=0; if (ig>255) ig=255;
			ib=(int)fb; if (ib<0) ib=0; if (ib>255) ib=255;
			ia=(int)fa; if (ia<0) ia=0; if (ia>255) ia=255;
				 
			color=RGBA(ir,ig,ib,ia);
			pos=12+4*(i+j*memX);
			MemblockWriteDword(mem,pos,color); 	     	  
		}
	}
    return 1;                                                                 
}
// *********************************************************************
int MemblockDrawBoxD(int mem, int x1, int y1, int x2, int y2, DWORD color1, DWORD color2, DWORD color3, DWORD color4, int borderwidth)
// *********************************************************************
{
	// Abbruchbedingung
    if (IsMemblock(mem)==0) return 0;

    // c1 ---- c2
    //  |  \ Q |		Q (fx>=fy) = c1 + fx/dx*(c2-c1) + fy/dy*(c4-c2)
    //  | P \  |        P (fx<fy) = c1 + fx/dx*(c4-c3) + fy/dy*(c3-c1)
    // c3 ---- c4
                                                                        
	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem);  

	// Differences
    int dx=x2-x1;
    int dy=y2-y1;

	int abs_dx=abs(dx);
	int abs_dy=abs(dy);
	        
	if (2*borderwidth>=abs_dx) return MemblockDrawBoxC(mem,x1,y1,x2,y2,color1,color2,color3,color4);
    if (2*borderwidth>=abs_dy) return MemblockDrawBoxC(mem,x1,y1,x2,y2,color1,color2,color3,color4);

	// Abbruchbedingung (Box == Dot or Line )           
    if ((dx==0) && (dy==0)){ return MemblockDrawDot(mem,x1,y1,color1);											}
    if ((dx==0) && (dy>0)) { return MemblockDrawLineB(mem,x1,y1,x2,y2,color1,color3);							}      
    if ((dx==0) && (dy<0)) { return MemblockDrawLineB(mem,x2,y2,x1,y1,color1,color3);							}      
    if ((dx>0) && (dy==0)) { return MemblockDrawLineB(mem,x1,y1,x2,y2,color1,color2);							}      
    if ((dx<0) && (dy==0)) { return MemblockDrawLineB(mem,x2,y2,x1,y1,color1,color2);							}      
	
	// Index Variablen
    int istart, iende;
    int jstart, jende;
 
	// Fallunterscheidung	  	        
    if ((dx>0) && (dy>0))  { istart=x1; 	iende=x2;   	jstart=y1; 	jende=y2;							 		}
    if ((dx>0) && (dy<0))  { istart=x1; 	iende=x2;   	jstart=y2; 	jende=y1; 									}      
    if ((dx<0) && (dy>0))  { istart=x2; 	iende=x1;   	jstart=y1; 	jende=y2; 									}          
    if ((dx<0) && (dy<0))  { istart=x2; 	iende=x1;   	jstart=y2; 	jende=y1; 									}      
    
	// COLORS
    const float 
	r1=(float)RGBA_R(color1), r2=(float)RGBA_R(color2), r3=(float)RGBA_R(color3), r4=(float)RGBA_R(color4),
    g1=(float)RGBA_G(color1), g2=(float)RGBA_G(color2), g3=(float)RGBA_G(color3), g4=(float)RGBA_G(color4),
    b1=(float)RGBA_B(color1), b2=(float)RGBA_B(color2), b3=(float)RGBA_B(color3), b4=(float)RGBA_B(color4),
    a1=(float)RGBA_A(color1), a2=(float)RGBA_A(color2), a3=(float)RGBA_A(color3), a4=(float)RGBA_A(color4);
	  	  	  	                                
	float fx,fy,fr,fg,fb,fa,fdx=(float)abs(dx),fdy=(float)abs(dy);
	DWORD color;
	int ix,iy,ir,ig,ib,ia;
	 	  	  
	// Zeichnen
    int i,j,pos;
    const int m1=istart+borderwidth-1;
    const int m2=jstart+borderwidth-1;
    const int m3=iende-borderwidth+1;
    const int m4=jende-borderwidth+1;

	for (j=jstart; j<=jende; j++)
	{
		for (i=istart; i<=iende; i++)
		{
			if ((i>-1) && (j>-1) && (i<memX) && (j<memY))
			{
				if ((i>m1) && (i<m3) && (j>m2) && (j<m4))
				{  
				}
				else
				{		   	  
	  				ix=i-istart;
	  				iy=j-jstart;	  	  
					fx=(float)ix/fdx;
					fy=(float)iy/fdy;

		  			// Q = c1 + fx/dx*(c2-c1) + fy/dy*(c4-c2)
		  			if (fx>fy)
		  			{  
			   			fr=r1+fx*(r2-r1)+fy*(r4-r2);	
			   			fg=g1+fx*(g2-g1)+fy*(g4-g2);	
			   			fb=b1+fx*(b2-b1)+fy*(b4-b2);	
			   			fa=a1+fx*(a2-a1)+fy*(a4-a2);
					}
			   		// P = c1 + fx/dx*(c4-c3) + fy/dy*(c3-c1)						   	 		  
					else
					{
			   			fr=r1+fx*(r4-r3)+fy*(r3-r1);	
			   			fg=g1+fx*(g4-g3)+fy*(g3-g1);	
			   			fb=b1+fx*(b4-b3)+fy*(b3-b1);	
			   			fa=a1+fx*(a4-a3)+fy*(a3-a1);
					}											 
					ir=(int)fr; if (ir<0) ir=0; if (ir>255) ir=255;
					ig=(int)fg; if (ig<0) ig=0; if (ig>255) ig=255;
					ib=(int)fb; if (ib<0) ib=0; if (ib>255) ib=255;
					ia=(int)fa; if (ia<0) ia=0; if (ia>255) ia=255;
				 
					color=RGBA(ir,ig,ib,ia);
					pos=12+4*(i+j*memX);
					MemblockWriteDword(mem,pos,color);
				}
			}
		}
	}
    return 1; 
}
// Zeichnet einen Kreisumfang -> Bresenham
// *********************************************************************
int MemblockDrawCircleA(int mem, int x, int y, int radius, DWORD color)
// *********************************************************************
{
	// Abbruchbedingung
    if (IsMemblock(mem)==0) return 0;
   	if (radius < 1) return 0;   

	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem);  
			
	// 'Bresenham' Algorithmus (Achtelkreis)
	// ohne Trigonometrische- und Wurzel-Funktionen
	// Verfahren : interpoliert 1/8 Kreis, der nur 2 Monotonieverläufe hat (Ost, Süd-Ost)
	// und Spiegelung auf Restliche 7/8
	int i,j,F;
	i = 0;
	j = radius;
	F = 1 - radius;
	
	while (i < j)
	{
		++i;
	    if (F < 0)
	    {
			F += (i<<1) - 1;
	    }
	    else
	    {
	      	F += ((i - j)<<1);
	       	--j;
	    }
	    // Verbesserungen by Neo Cortex
	    MemblockWriteDword(mem,memX,memY,x+i,y+j,color);
	    MemblockWriteDword(mem,memX,memY,x+j,y+i,color);
	    MemblockWriteDword(mem,memX,memY,x-i+1,y+j,color);
	    MemblockWriteDword(mem,memX,memY,x+j,y-i+1,color);
		MemblockWriteDword(mem,memX,memY,x+i,y-j+1,color);
	    MemblockWriteDword(mem,memX,memY,x-j+1,y+i,color);
	    MemblockWriteDword(mem,memX,memY,x-i+1,y-j+1,color);
	    MemblockWriteDword(mem,memX,memY,x-j+1,y-i+1,color);													      
	}
	return 1;
}

// Zeichnet einen gefüllten Kreis mit 2 Farben, wenn color1==color2, dann zeichne nur mit einer Farbe
// *********************************************************************
int MemblockDrawCircleB(int mem, int x, int y, int radius, DWORD colorI, DWORD colorO)
// *********************************************************************
{
	// User Identification
    if (IsMemblock(mem)==0) return 0;
   	if (radius < 1) return 0;   
   	
	// Modi
	bool only_one_color=false;
	if (colorI==colorO) only_one_color=true;

	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem);  

	// Kreis Mittelpunkt
	const float mx=(float)x+0.5f;
	const float my=(float)y+0.5f;
	   
	// Kreis Radius
	const float r=(float)radius;
	const float q=r*r;

	// Kreis Grenzen
	const int x1=Round(mx-r)-1;
	const int x2=Round(mx+r)+1;
	const int y1=Round(my-r)-1;
	const int y2=Round(my+r)+1;

	// Zeichne mit einer Farbe
	if (only_one_color==true)
	{
		int i,j,pos;
		float fx,fy,fd;
		for (j=y1; j<y2; j++)
		{  
			for (i=x1; i<x2; i++)
			{	
				// Check, if Point within Memblock
				if ((i>-1) && (j>-1) && (i<memX) && (j<memY))
		  	  	{
					// Get Point relative to Circle
		      		fx=(float)i-mx;
					fy=(float)j-my;
					fd=fx*fx+fy*fy;
					// Check, if Point Within Circle
					if (fd<q)
					{			
				  		pos=12+4*(i+j*memX);
				  		MemblockWriteDword(mem,pos,colorO);
					}
				}
			}
		}
	}
	// Zeichne mit 2 Farben
	else
	{
		// Colors
   		const float 
		r1=(float)RGBA_R(colorI), r2=(float)RGBA_R(colorO),
   		g1=(float)RGBA_G(colorI), g2=(float)RGBA_G(colorO),
   		b1=(float)RGBA_B(colorI), b2=(float)RGBA_B(colorO),
   		a1=(float)RGBA_A(colorI), a2=(float)RGBA_A(colorO);

		// LOCALS   	     	  
		int i,j,pos,ir,ig,ib,ia;
   		float fx,fy,fd,fc,fr,fg,fb,fa;
   		DWORD color;

		// Zeichnen
		for (j=y1; j<y2; j++)
		{  
			for (i=x1; i<x2; i++)
			{
				// Check, if Point within Memblock
				if ((i>-1) && (j>-1) && (i<memX) && (j<memY))
	  	  		{
					// Get Point relative to Circle
	      			fx=(float)i-mx;
					fy=(float)j-my;
					fd=fx*fx+fy*fy;
					
					// Check, if Point Within Circle
					if (fd<q)
					{	
						if (fd<1.0f)
						{	
							fc=0.0f;			
						}
						else
						{  
							fc=(float)sqrt(fd)/r;	
						}
						
						fr=r1+fc*(r2-r1);	   
						fg=g1+fc*(g2-g1);
						fb=b1+fc*(b2-b1);
						fa=a1+fc*(a2-a1);
						ir=(int)fr; if (ir<0) ir=0; if (ir>255) ir=255;
						ig=(int)fg; if (ig<0) ig=0; if (ig>255) ig=255;
						ib=(int)fb; if (ib<0) ib=0; if (ib>255) ib=255;
						ia=(int)fa; if (ia<0) ia=0; if (ia>255) ia=255;
						color=RGBA(ir,ig,ib,ia);	
				  		pos=12+4*(i+j*memX);
				  		MemblockWriteDword(mem,pos,color);
					}
				}
			}
		}
	}
	return 1;
}
// Zeichnet einen Kreis mit 2 Farben,
// wenn borderwidth==0 -> dann DrawCircleB
// wenn borderwidth==1 -> dann DrawCircleA mit color=colorO
// wenn borderwidth>=2 -> dann DrawCircleC(Ring), wenn colorI==colorO dann zeichne mit nur einer Farbe
// *********************************************************************
int MemblockDrawCircleC(int mem, int x, int y, int radius, DWORD colorI, DWORD colorO, int borderwidth)
// *********************************************************************
{
	// Abbruchbedingung
    if (IsMemblock(mem)==0) return 0;
   	if (radius < 1) return 0;   
	if (radius-borderwidth < 1) return 0;

	if (borderwidth <= 0) return MemblockDrawCircleB(mem,x,y,radius,colorI,colorO);
   	if (borderwidth == 1) return MemblockDrawCircleA(mem,x,y,radius,colorO);

	// Modus
	bool only_one_color=false;
	if (colorI==colorO) only_one_color=true;

	// Memblock Size
    int memX = MemblockX(mem);
    int memY = MemblockY(mem);  

	// Kreis Mittelpunkt
	const float mx=(float)x+0.5f;
	const float my=(float)y+0.5f;
	   
	// Kreis RadiusO
	const float rO=(float)radius;
	const float qO=rO*rO;

	// Kreis RadiusI
	const float rI=(float)radius-(float)borderwidth;
	const float qI=rI*rI;

	// Kreis Grenzen
	const int x1=Round(mx-rO)-1;
	const int x2=Round(mx+rO)+1;
	const int y1=Round(my-rO)-1;
	const int y2=Round(my+rO)+1;

	// Zeichne 1 Farbe colorO
	if (only_one_color==true)
	{
		// LOCALS   	     	  
		int i,j,pos;
   		float fx,fy,fd;

		// Zeichnen
		for (j=y1; j<y2; j++)
		{	for (i=x1; i<x2; i++)
			{	
				// Check, if Point within Memblock
				if ((i>-1) && (j>-1) && (i<memX) && (j<memY))
		  	  	{
					// Get Point relative to Circle
		      		fx=(float)i-mx;
					fy=(float)j-my;
					fd=fx*fx+fy*fy;

					// Check, if Point Within Circle
					if ((fd<qO) && (fd>qI))
					{		
				  		pos=12+4*(i+j*memX);
				  		MemblockWriteDword(mem,pos,colorO);
					}
				}
			}
		}
	}
	// 2 Farben
	else
	{
		// Kreis Radius Differenz
		const float dr=rO-rI;

		// COLORS
   		const float 
		r1=(float)RGBA_R(colorI), r2=(float)RGBA_R(colorO),
   		g1=(float)RGBA_G(colorI), g2=(float)RGBA_G(colorO),
   		b1=(float)RGBA_B(colorI), b2=(float)RGBA_B(colorO),
   		a1=(float)RGBA_A(colorI), a2=(float)RGBA_A(colorO);

		// LOCALS   	     	  
		int i,j,pos,ir,ig,ib,ia;
   		float fx,fy,fd,fw,fr,fg,fb,fa,fc;
   		DWORD color;

		// Zeichnen
		for (j=y1; j<y2; j++)
		{	for (i=x1; i<x2; i++)
			{	
				// Check, if Point within Memblock
				if ((i>-1) && (j>-1) && (i<memX) && (j<memY))
		  	  	{
					// Get Point relative to Circle
		      		fx=(float)i-mx;
					fy=(float)j-my;
					fd=fx*fx+fy*fy;
					
					// Check, if Point Within Circle
					if ((fd<qO) && (fd>qI))
					{		
						fw=(float)sqrt(fd);
						fc=(fw-rI)/dr;
						fr=r1+fc*(r2-r1);	   
						fg=g1+fc*(g2-g1);
						fb=b1+fc*(b2-b1);
						fa=a1+fc*(a2-a1);
						ir=(int)fr; if (ir<0) ir=0; if (ir>255) ir=255;
						ig=(int)fg; if (ig<0) ig=0; if (ig>255) ig=255;
						ib=(int)fb; if (ib<0) ib=0; if (ib>255) ib=255;
						ia=(int)fa; if (ia<0) ia=0; if (ia>255) ia=255;
						color=RGBA(ir,ig,ib,ia);	
				  		pos=12+4*(i+j*memX);
				  		MemblockWriteDword(mem,pos,color);
					}
				}
			}
		}
	}
	return 1;
}

// Zeichnet einen Ellipsenumfang -> Bresenham
// *********************************************************************
int MemblockDrawEllipseA(int mem, int x, int y, int rx, int ry, DWORD color)
// *********************************************************************
{
	// Abbruchbedingung
    if (IsMemblock(mem)==0) return 0;

	// Memblock Size
	int memX = MemblockX(mem);
	int memY = MemblockY(mem);

	// Ellipsen Radien Quadrate
	const int rx2=rx*rx;
	const int ry2=ry*ry;

	// Ellipsen Mittelpunkt
	const int mx = x;
	const int my = y;

	// Bresenham Anfangswerte
	int F=Round((float)(ry2-rx2*ry)+(float)rx2*0.25f);
	int ddF_x=0;
	int ddF_y=((rx2*ry)<<1);
	x=0;
	y=ry;
	
	// Bresenham Alghorithmus für eine 4tel Ellipse, restliche 3Viertel durch Spiegelung
	// Ellipse nicht rotiert.
	while( ddF_x < ddF_y ) 
	{
		if (F >= 0)
		{
			y     -= 1;        // south
	      ddF_y -= (rx2<<1);
			F     -= ddF_y;
		}
		x     += 1;          // east
		ddF_x += (ry2<<1);
		F     += ddF_x + ry2;
		// Spiegelung mit meinen Anpassungen
		MemblockWriteDword(mem, memX, memY, x+mx, y+my, color);
		MemblockWriteDword(mem, memX, memY, -x+mx+1, y+my, color);
		MemblockWriteDword(mem, memX, memY, x+mx, -y+my+1, color);
		MemblockWriteDword(mem, memX, memY, -x+mx+1, -y+my+1, color);
	}
	F = Round((float)ry2*((float)x+0.5f)*((float)x+0.5f) + (float)(rx2*(y-1)*(y-1) - rx2*ry2));
			
	while( y > 0 ) 
	{
		if(F <= 0) 
		{
			x     += 1;        // east
			ddF_x += (ry2<<1);
			F     += ddF_x;
		}
		y     -=1;           // south
		ddF_y -= (rx2<<1);
		F     += rx2 - ddF_y;
	
		// Spiegelung mit meinen Anpassungen
		MemblockWriteDword(mem, memX, memY, x+mx, y+my, color);
		MemblockWriteDword(mem, memX, memY, -x+mx+1, y+my, color);
		MemblockWriteDword(mem, memX, memY, x+mx, -y+my+1, color);
		MemblockWriteDword(mem, memX, memY, -x+mx+1, -y+my+1, color);
	}		  
	return 1;
}
// Zeichnet eine gefüllte Ellipse mit 2 Farben, wenn colorI==colorO, dann zeichne nur mit einer Farbe
// *********************************************************************
int MemblockDrawEllipseB(int mem, int x, int y, int rx, int ry, DWORD colorI, DWORD colorO)
// *********************************************************************
{
	// Abbruchbedingung
	if (IsMemblock(mem)==0) return 0;

	// Memblock Size
	int memX = MemblockX(mem);
	int memY = MemblockY(mem);
	
	return 1;
}
// Zeichnet eine Ellipse mit 2 Farben
// wenn borderwidthXY==0 -> dann DrawEllipseB
// wenn borderwidthXY==1 -> dann DrawEllipseA mit color=colorO
// wenn borderwidthXY>=2 -> dann DrawEllipseC(Ring), wenn colorI==colorO dann zeichne mit nur einer Farbe
// *********************************************************************
int MemblockDrawEllipseC(int mem, int x, int y, int rx, int ry, DWORD colorI, DWORD colorO, int borderwidthX, int borderwidthY)
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
int MemblockDrawTriangleA(int mem, int x1, int y1, int x2, int y2, int x3, int y3, DWORD color)
// *********************************************************************
{
	// Abbruchbedingung
	if (IsMemblock(mem)==0) return 0;
	MemblockDrawLineA(mem,x1,y1,x2,y2,color);
	MemblockDrawLineA(mem,x1,y1,x3,y3,color);
	MemblockDrawLineA(mem,x2,y2,x3,y3,color);
	return 1;
}
// *********************************************************************
int MemblockDrawTriangleB(int mem, int x1, int y1, int x2, int y2, int x3, int y3, DWORD color, int borderwidth)
// *********************************************************************
{
	// Abbruchbedingung
	if (borderwidth==1) return MemblockDrawTriangleA(mem,x1,y1,x2,y2,x3,y3,color);
	if (IsMemblock(mem)==0) return 0;

	MemblockDrawLineA(mem,x1,y1,x2,y2,color);
	MemblockDrawLineA(mem,x1,y1,x3,y3,color);
	MemblockDrawLineA(mem,x2,y2,x3,y3,color);

	return 1;
}
// *********************************************************************
int MemblockDrawTriangleC(int mem, int x1, int y1, int x2, int y2, int x3, int y3, DWORD color1, DWORD color2, DWORD color3)
// *********************************************************************
{
	// Abbruchbedingung
	if (IsMemblock(mem)==0) return 0;

	MemblockDrawLineB(mem,x1,y1,x2,y2,color1,color2);
	MemblockDrawLineB(mem,x1,y1,x3,y3,color1,color3);
	MemblockDrawLineB(mem,x2,y2,x3,y3,color2,color3);

	return 1;
}
// *********************************************************************
int MemblockDrawTriangleD(int mem, int x1, int y1, int x2, int y2, int x3, int y3, DWORD color1, DWORD color2, DWORD color3, int borderwidth)
// *********************************************************************
{
	// Abbruchbedingung
	if (borderwidth==1) return MemblockDrawTriangleA(mem,x1,y1,x2,y2,x3,y3,color1);
	if (IsMemblock(mem)==0) return 0;

	MemblockDrawLineB(mem,x1,y1,x2,y2,color1,color2);
	MemblockDrawLineB(mem,x1,y1,x3,y3,color1,color3);
	MemblockDrawLineB(mem,x2,y2,x3,y3,color2,color3);

	return 1;
}

} // END NAMESPACE
/*
void DrawEllipseQuadrant(
  int x0, int y0,
  int rx, int ry,
  int color
) {
  const int rx2(rx*rx);
  const int ry2(ry*ry);
  int F(Round(ry2-rx2*ry+0.25*rx2));
  int ddF_x(0);
  int ddF_y(2*rx2*ry);
  int x(0);
  int y(ry);

  SetPixel(x+x0, y+y0, color);
    // while ( 2*ry2*x < 2*rx2*y ) {  we can use ddF_x and ddF_y
  while( ddF_x < ddF_y ) {
    if(F >= 0) {
      y     -= 1;        // south
      ddF_y -= 2*rx2;
      F     -= ddF_y;
    }
    x     += 1;          // east
    ddF_x += 2*ry2;
    F     += ddF_x + ry2;
    SetPixel(x+x0, y+y0, color);
  }
  F = Round(ry2*(x+0.5)*(x+0.5) + rx2*(y-1)*(y-1) - rx2*ry2);
  while( y > 0 ) {
    if(F <= 0) {
      x     += 1;        // east
      ddF_x += 2*ry2;
      F     += ddF_x;
    }
    y     -=1;           // south
    ddF_y -= 2*rx2;
    F     += rx2 - ddF_y;
    SetPixel(x+x0, y+y0, color);
  }
}
*/

/*
	// *********************************			
	// * Input: 
	// * xP: x-value of the startpoint
	// * yP: y-value of the startpoint
	// * xQ: x-value of the endpoint
	// * yQ: y-value of the endpoint
	// ********************************
	function drawLine(xP, yP, xQ, yQ) {
		x = xP;
		y = yP;
		D = 0;
		HX = xQ - xP;
		HY = yQ - yP;
		xInc = 1;
		yInc = 1;
		
		if(HX < 0) {
			xInc = -1; HX = -HX;
		}
		if(HY < 0) {
			yInc = -1; HY = -HY;
		}
		if(HY <= HX) {
			c = 2 * HX; M = 2 * HY;
			while(true) {
				putPixel(x, y, g);
				if(x == xQ) {
					break;
				}
				x += xInc;
				D += M;
				if(D > HX) {
					y += yInc; D -=c;
				}
			}
		}
		else {
			c = 2 * HY; M = 2 * HX;
			while(true) {
				putPixel(x, y, g);
				if(y == yQ) {
					break;
				}
				y += yInc;
				D += M;
				if(D > HY) {
					x += xInc; D -=c;
				}
			} 
			
		}
	}
	*/
