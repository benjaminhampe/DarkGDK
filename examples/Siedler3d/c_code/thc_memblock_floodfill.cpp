// thc_memblock_fill_flood.cpp

#include "thc_memblock_floodfill.h"
#include "thc_memblock.h"
#include "thc_is.h"

namespace thc
{
//Flood-fill (node, target-color, replacement-color):
// 1. Set Q to the empty queue.
// 2. If the color of node is not equal to target-color, return.
// 3. Add node to Q.
// 4. For each element n of Q:
// 5.  If the color of n is equal to target-color:
// 6.   Set w and e equal to n.
// 7.   Move w to the west until the color of the node to the west of w 
//      no longer matches target-color.
// 8.   Move e to the east until the color of the node to the east of e
//      no longer matches target-color.
// 9.   Set the color of nodes between w and e to replacement-color.
//10.   For each node n between w and e:
//11.    If the color of the node to the north of n is target-color, add that node to Q.
//       If the color of the node to the south of n is target-color, add that node to Q.
//12. Continue looping until Q is exhausted.
//13. Return.

//******************************************************************************************
int MemblockFloodFill(int mem, int x, int y, DWORD newColor, DWORD oldColor)
//******************************************************************************************
{
	if (IsMemblock(mem)==0) return 0;
	
	DWORD *p=MemblockPointer(mem);
   	const int memX=MemblockX(mem);
   	const int memY=MemblockX(mem);

	if (MemblockReadDword(mem,memX,memY,x,y)==newColor) return 1;

	int lg, rg, px=x;
	while(MemblockReadDword(mem,memX,memY,x,y)==oldColor)
	{
		MemblockWriteDword(mem,memX,memY,x,y,newColor);
		x--;
	}

	lg=x+1;
	x=px+1;

	while(MemblockReadDword(mem,memX,memY,x,y)==oldColor)
	{
		MemblockWriteDword(mem,memX,memY,x,y,newColor);
		x++;
	}
	rg=x-1;
	
	for(x=rg; x>=lg; x--)
	{
		if((MemblockReadDword(mem,memX,memY,x,y-1)==oldColor) && (y-1>0))
			MemblockFloodFill(mem,x,y-1,newColor,oldColor);
		if((MemblockReadDword(mem,memX,memY,x,y+1)==oldColor) && (y<memY-1))
			MemblockFloodFill(mem,x,y+1,newColor,oldColor);
	}

	return 1;
}

} // END NAMESPACE

/*
fillRowByRow(int x, inty)
{
	int lg, int rg; int px=x;
	while(!getPixel(x,y))
	{
		setPixel(x,y);
		x--;
	}

	lg=x+1;
	x=px+1;

	while(!getPixel(x,y))
	{
		setPixel(x,y);
		x++;
	}
	rg=x-1;
	
	for(x=rg; x>=lg; x--)
	{
		if(!getPixel(x,y-1))
			fillRowByRow(x,y-1);
		if(!getPixel(x,y+1))
			fillRowByRow(x,y+1);
	}
}
*/
//********
//QUEUE ALGORITHM
//********
/*
void QueueFloodFill4(DWORD *pMB, int memX, int memY, int x, int y, DWORD newColor, DWORD oldColor)
{
		//don't go over the edge
     	if ((x < 0) || (x >= memX)) return;
     	if ((y < 0) || (y >= memY)) return;
  		
    		//calculate pointer offset
    		int* p=(int*) (scan0+(CoordsToIndex(x,y, stride)));
    		
    		//if the pixel is within the color tolerance, fill it and branch out
        	if (!(PixelsChecked[x,y]) && CheckPixel((byte*) p,startcolor)) 
        	{
				p[0]=m_fillcolor; 	 //fill with the color
				PixelsChecked[x,y]=true;
        		
				CheckQueue.Enqueue(new Point(x+1,y));
        		CheckQueue.Enqueue(new Point(x,y+1));
        		CheckQueue.Enqueue(new Point(x-1,y));
        		CheckQueue.Enqueue(new Point(x,y-1));
        	}
    	}   		
    		
*/


/*
		///<summary>initializes the FloodFill operation</summary>
		public override void FloodFill(Bitmap bmp, Point pt)
		{
			int ctr=timeGetTime();
			
			//Debug.WriteLine("*******Flood Fill******");
			
			//get the color's int value, and convert it from RGBA to BGRA format (as GDI+ uses BGRA)
                        m_fillcolor=ColorTranslator.ToWin32(m_fillcolorcolor);
			m_fillcolor=BGRA(GetB(m_fillcolor),GetG(m_fillcolor),GetR(m_fillcolor),GetA(m_fillcolor));
			
			//get the bits
                        BitmapData bmpData=bmp.LockBits(new Rectangle(0,0,bmp.Width,bmp.Height),ImageLockMode.ReadWrite,PixelFormat.Format32bppArgb);
			System.IntPtr Scan0 = bmpData.Scan0;
		    
		    unsafe
		    {
		    	//resolve pointer
		        byte * scan0=(byte *)(void *)Scan0;
		    	//get the starting color
		    	//[loc += Y offset + X offset]
		    	int loc=CoordsToIndex(pt.X,pt.Y,bmpData.Stride);//((bmpData.Stride*(pt.Y-1))+(pt.X*4));
		    	int color= *((int*)(scan0+loc));
		    	
		    	//create the array of bools that indicates whether each pixel
                        //has been checked.  (Should be bitfield, but C# doesn't support bitfields.)
                        PixelsChecked=new bool[bmpData.Width+1,bmpData.Height+1];
		    	
		    	//do the first call to the loop
		    	switch(m_FillStyle)
		    	{
		    		case FloodFillStyle.Linear :
				    	if(m_FillDiagonal)
				    	{
				    		LinearFloodFill8(scan0,pt.X,pt.Y,new Size(bmpData.Width,bmpData.Height),bmpData.Stride,(byte*)&color);
				    	}else{
				    		LinearFloodFill4(scan0,pt.X,pt.Y,new Size(bmpData.Width,bmpData.Height),bmpData.Stride,(byte*)&color);
				    	}
				    	break;
		    		case FloodFillStyle.Queue :
		    			QueueFloodFill(scan0,pt.X,pt.Y,new Size(bmpData.Width,bmpData.Height),bmpData.Stride,(byte*)&color);
		    			break;
		    		case FloodFillStyle.Recursive :
				    	if(m_FillDiagonal)
				    	{
				    		RecursiveFloodFill8(scan0,pt.X,pt.Y,new Size(bmpData.Width,bmpData.Height),bmpData.Stride,(byte*)&color);
				    	}else{
				    		RecursiveFloodFill4(scan0,pt.X,pt.Y,new Size(bmpData.Width,bmpData.Height),bmpData.Stride,(byte*)&color);
				    	}
				    	break;
		        }
		    }
		    
		    bmp.UnlockBits(bmpData);
			
                    m_TimeBenchmark=timeGetTime()-ctr;
			
		}
		
		//*********
		//HELPER FUNCTIONS
		//*********
		
		///<summary>Sees if a pixel is within the color tolerance range.</summary>
		//px - a pointer to the pixel to check
		//startcolor - a pointer to the color of the pixel we started at
		unsafe bool CheckPixel(byte* px, byte* startcolor)
		{
                        bool ret=true;
			for(byte i=0;i<3;i++)
				ret&= (px[i]>= (startcolor[i]-m_Tolerance[i])) && px[i] <= (startcolor[i]+m_Tolerance[i]);		    
		    return ret;
		}
		
		///<summary>Given X and Y coordinates and the bitmap's stride, returns a pointer offset</summary>
		int CoordsToIndex(int x, int y, int stride)
		{
			return (stride*y)+(x*4);
		}

		//***********
		//LINEAR ALGORITHM
		//***********
		
		unsafe void LinearFloodFill4( byte* scan0, int x, int y,Size bmpsize, int stride, byte* startcolor)
		{
			
			//offset the pointer to the point passed in
			int* p=(int*) (scan0+(CoordsToIndex(x,y, stride)));
			
			
			//FIND LEFT EDGE OF COLOR AREA
			int LFillLoc=x; //the location to check/fill on the left
			int* ptr=p; //the pointer to the current location
			while(true)
			{
				ptr[0]=m_fillcolor; 	 //fill with the color
				PixelsChecked[LFillLoc,y]=true;
				LFillLoc--; 		 	 //de-increment counter
				ptr-=1;				 	 //de-increment pointer
				if(LFillLoc<=0 || !CheckPixel((byte*)ptr,startcolor) ||  (PixelsChecked[LFillLoc,y]))
					break;			 	 //exit loop if we're at edge of bitmap or color area
				
			}
			LFillLoc++;
			
			//FIND RIGHT EDGE OF COLOR AREA
			int RFillLoc=x; //the location to check/fill on the left
			ptr=p;
			while(true)
			{
				ptr[0]=m_fillcolor; //fill with the color
				PixelsChecked[RFillLoc,y]=true;
				RFillLoc++; 		 //increment counter
				ptr+=1;				 //increment pointer
				if(RFillLoc>=bmpsize.Width || !CheckPixel((byte*)ptr,startcolor) ||  (PixelsChecked[RFillLoc,y]))
					break;			 //exit loop if we're at edge of bitmap or color area
				
			}
			RFillLoc--;
			
			
			//START THE LOOP UPWARDS AND DOWNWARDS			
			ptr=(int*)(scan0+CoordsToIndex(LFillLoc,y,stride));
			for(int i=LFillLoc;i<=RFillLoc;i++)
			{
				//START LOOP UPWARDS
				//if we're not above the top of the bitmap and the pixel above this one is within the color tolerance
				if(y>0 && CheckPixel((byte*)(scan0+CoordsToIndex(i,y-1,stride)),startcolor) && (!(PixelsChecked[i,y-1])))
					LinearFloodFill4(scan0, i,y-1,bmpsize,stride,startcolor);
				//START LOOP DOWNWARDS
				if(y<(bmpsize.Height-1) && CheckPixel((byte*)(scan0+CoordsToIndex(i,y+1,stride)),startcolor) && (!(PixelsChecked[i,y+1])))
					LinearFloodFill4(scan0, i,y+1,bmpsize,stride,startcolor);
				ptr+=1;
			}
			
		}
				
		//********
		//QUEUE ALGORITHM
		//********
		public unsafe void QueueFloodFill(byte* scan0, int x, int y,Size bmpsize, int stride, byte* startcolor)
		{
			CheckQueue=new Queue();
			
			if(!m_FillDiagonal)
			{
				//start the loop
				QueueFloodFill4(scan0,x,y,bmpsize,stride,startcolor);
				//call next item on queue
				while(CheckQueue.Count>0)
				{
					Point pt=(Point)CheckQueue.Dequeue();
					QueueFloodFill4(scan0,pt.X,pt.Y,bmpsize,stride,startcolor);
				}
			}else{
				//start the loop
				QueueFloodFill8(scan0,x,y,bmpsize,stride,startcolor);
				//call next item on queue
				while(CheckQueue.Count>0)
				{
					Point pt=(Point)CheckQueue.Dequeue();
					QueueFloodFill8(scan0,pt.X,pt.Y,bmpsize,stride,startcolor);
				}
			}
		}
    	public unsafe void QueueFloodFill4(byte* scan0, int x, int y,Size bmpsize, int stride, byte* startcolor)
    	{
			//don't go over the edge
        	if ((x < 0) || (x >= bmpsize.Width)) return;
        	if ((y < 0) || (y >= bmpsize.Height)) return;
    		
    		//calculate pointer offset
    		int* p=(int*) (scan0+(CoordsToIndex(x,y, stride)));
    		
    		//if the pixel is within the color tolerance, fill it and branch out
        	if (!(PixelsChecked[x,y]) && CheckPixel((byte*) p,startcolor)) 
        	{
				p[0]=m_fillcolor; 	 //fill with the color
				PixelsChecked[x,y]=true;
        		
				CheckQueue.Enqueue(new Point(x+1,y));
        		CheckQueue.Enqueue(new Point(x,y+1));
        		CheckQueue.Enqueue(new Point(x-1,y));
        		CheckQueue.Enqueue(new Point(x,y-1));
        	}
    	}			
    	public unsafe void QueueFloodFill8(byte* scan0, int x, int y,Size bmpsize, int stride, byte* startcolor)
    	{
			//don't go over the edge
        	if ((x < 0) || (x >= bmpsize.Width)) return;
        	if ((y < 0) || (y >= bmpsize.Height)) return;
    		int* p=(int*) (scan0+(CoordsToIndex(x,y, stride)));
        	if (!(PixelsChecked[x,y]) && CheckPixel((byte*) p,startcolor)) 
        	{
				p[0]=m_fillcolor; 	 //fill with the color
				PixelsChecked[x,y]=true;
        		
                        CheckQueue.Enqueue(new Point(x+1,y));
        		CheckQueue.Enqueue(new Point(x,y+1));
        		CheckQueue.Enqueue(new Point(x-1,y));
        		CheckQueue.Enqueue(new Point(x,y-1));
				
                        CheckQueue.Enqueue(new Point(x+1,y+1));
        		CheckQueue.Enqueue(new Point(x-1,y-1));
        		CheckQueue.Enqueue(new Point(x-1,y+1));
        		CheckQueue.Enqueue(new Point(x+1,y-1));
        	}
    	}


unsafe void LinearFloodFill8( byte* scan0, int x, int y,Size bmpsize, int stride, byte* startcolor)
		{
			
			//offset the pointer to the point passed in
			int* p=(int*) (scan0+(CoordsToIndex(x,y, stride)));
			
			
			//FIND LEFT EDGE OF COLOR AREA
			int LFillLoc=x; //the location to check/fill on the left
			int* ptr=p; //the pointer to the current location
			while(true)
			{
				ptr[0]=m_fillcolor; 	 //fill with the color
				PixelsChecked[LFillLoc,y]=true;
				LFillLoc--; 		 	 //de-increment counter
				ptr-=1;				 	 //de-increment pointer
				if(LFillLoc<=0 || !CheckPixel((byte*)ptr,startcolor) ||  (PixelsChecked[LFillLoc,y]))
					break;			 	 //exit loop if we're at edge of bitmap or color area
				
			}
			LFillLoc++;
			
			//FIND RIGHT EDGE OF COLOR AREA
			int RFillLoc=x; //the location to check/fill on the left
			ptr=p;
			while(true)
			{
				ptr[0]=m_fillcolor; //fill with the color
				PixelsChecked[RFillLoc,y]=true;
				RFillLoc++; 		 //increment counter
				ptr+=1;				 //increment pointer
				if(RFillLoc>=bmpsize.Width || !CheckPixel((byte*)ptr,startcolor) ||  (PixelsChecked[RFillLoc,y]))
					break;			 //exit loop if we're at edge of bitmap or color area
				
			}
			RFillLoc--;
			
			
			//START THE LOOP UPWARDS AND DOWNWARDS			
			ptr=(int*)(scan0+CoordsToIndex(LFillLoc,y,stride));
			for(int i=LFillLoc;i<=RFillLoc;i++)
			{
				//START LOOP UPWARDS
				//if we're not above the top of the bitmap and the pixel above this one is within the color tolerance
				//START LOOP DOWNWARDS
				if(y>0)
				{
					//UP
					if(CheckPixel((byte*)(scan0+CoordsToIndex(i,y-1,stride)),startcolor) && (!(PixelsChecked[i,y-1])))
						LinearFloodFill8(scan0, i,y-1,bmpsize,stride,startcolor);
					//UP-LEFT
					if(x>0 && CheckPixel((byte*)(scan0+CoordsToIndex(i-1,y-1,stride)),startcolor) && (!(PixelsChecked[i-1,y-1])))
						LinearFloodFill8(scan0, i-1,y-1,bmpsize,stride,startcolor);
					//UP-RIGHT
					if(x<(bmpsize.Width-1) && CheckPixel((byte*)(scan0+CoordsToIndex(i+1,y-1,stride)),startcolor) && (!(PixelsChecked[i+1,y-1])))
						LinearFloodFill8(scan0, i+1,y-1,bmpsize,stride,startcolor);
				}
				
				if(y<(bmpsize.Height-1)) 
				{
					//DOWN
					if(CheckPixel((byte*)(scan0+CoordsToIndex(i,y+1,stride)),startcolor) && (!(PixelsChecked[i,y+1])))
						LinearFloodFill8(scan0, i,y+1,bmpsize,stride,startcolor);
					//DOWN-LEFT
					if(x>0 && CheckPixel((byte*)(scan0+CoordsToIndex(i-1,y+1,stride)),startcolor) && (!(PixelsChecked[i-1,y+1])))
						LinearFloodFill8(scan0, i-1,y+1,bmpsize,stride,startcolor);
					//UP-RIGHT
					if(x<(bmpsize.Width-1) && CheckPixel((byte*)(scan0+CoordsToIndex(i+1,y+1,stride)),startcolor) && (!(PixelsChecked[i+1,y+1])))
						LinearFloodFill8(scan0, i+1,y+1,bmpsize,stride,startcolor);
					
				}
				
				ptr+=1;
			}
			
		}
		
		//*********
		//RECURSIVE ALGORITHM
		//*********
		
    	public unsafe void RecursiveFloodFill8(byte* scan0, int x, int y,Size bmpsize, int stride, byte* startcolor)
    	{
			//don't go over the edge
        	if ((x < 0) || (x >= bmpsize.Width)) return;
        	if ((y < 0) || (y >= bmpsize.Height)) return;
    		int* p=(int*) (scan0+(CoordsToIndex(x,y, stride)));
        	if (!(PixelsChecked[x,y]) && CheckPixel((byte*) p,startcolor)) 
        	{
				p[0]=m_fillcolor; 	 //fill with the color
				PixelsChecked[x,y]=true;
        		
        		//branch in all 8 directions
            	RecursiveFloodFill8(scan0,x+1, y,bmpsize,stride, startcolor);
            	RecursiveFloodFill8(scan0,x, y+1,bmpsize,stride, startcolor);
            	RecursiveFloodFill8(scan0,x-1, y,bmpsize,stride, startcolor);
            	RecursiveFloodFill8(scan0,x, y-1,bmpsize,stride, startcolor);
            	RecursiveFloodFill8(scan0,x+1, y+1,bmpsize,stride, startcolor);
            	RecursiveFloodFill8(scan0,x-1, y+1,bmpsize,stride, startcolor);
            	RecursiveFloodFill8(scan0,x-1, y-1,bmpsize,stride, startcolor);
            	RecursiveFloodFill8(scan0,x+1, y-1,bmpsize,stride, startcolor);
        	}
    	}

    	public unsafe void RecursiveFloodFill4(byte* scan0, int x, int y,Size bmpsize, int stride, byte* startcolor)
    	{
			//don't go over the edge
        	if ((x < 0) || (x >= bmpsize.Width)) return;
        	if ((y < 0) || (y >= bmpsize.Height)) return;
    		
    		//calculate pointer offset
    		int* p=(int*) (scan0+(CoordsToIndex(x,y, stride)));
    		
    		//if the pixel is within the color tolerance, fill it and branch out
        	if (!(PixelsChecked[x,y]) && CheckPixel((byte*) p,startcolor)) 
        	{
				p[0]=m_fillcolor; 	 //fill with the color
				PixelsChecked[x,y]=true;
        		
            	RecursiveFloodFill4(scan0,x+1, y,bmpsize,stride, startcolor);
            	RecursiveFloodFill4(scan0,x, y+1,bmpsize,stride, startcolor);
            	RecursiveFloodFill4(scan0,x-1, y,bmpsize,stride, startcolor);
            	RecursiveFloodFill4(scan0,x, y-1,bmpsize,stride, startcolor);
        	}
    	}


		*/


/*
//The scanline floodfill algorithm using our own stack routines, faster
void floodFillScanlineStack(int x, int y, int newColor, int oldColor)
{
    if(oldColor == newColor) return;
    emptyStack();
    
    int y1; 
    bool spanLeft, spanRight;
    
    if(!push(x, y)) return;
    
    while(pop(x, y))
    {    
        y1 = y;
        while(y1 >= 0 && screenBuffer[x][y1] == oldColor) y1--;
        y1++;
        spanLeft = spanRight = 0;
        while(y1 < h && screenBuffer[x][y1] == oldColor )
        {
            screenBuffer[x][y1] = newColor;
            if(!spanLeft && x > 0 && screenBuffer[x - 1][y1] == oldColor) 
            {
                if(!push(x - 1, y1)) return;
                spanLeft = 1;
            }
            else if(spanLeft && x > 0 && screenBuffer[x - 1][y1] != oldColor)
            {
                spanLeft = 0;
            }
            if(!spanRight && x < w - 1 && screenBuffer[x + 1][y1] == oldColor) 
            {
                if(!push(x + 1, y1)) return;
                spanRight = 1;
            }
            else if(spanRight && x < w - 1 && screenBuffer[x + 1][y1] != oldColor)
            {
                spanRight = 0;
            } 
            y1++;
        }
    }
}



*/