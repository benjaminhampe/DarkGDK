// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include <imageTool.h>


namespace irr
{

namespace video
{

IImage* Tool::repeatImage( IImage* src, f32 u, f32 v )
{
	if (!src)
		return 0;

//	const core::dimension2du& src_size = src->getDimension();
//
//	const u32 w = core::round32( u * src_size.Width );
//	const u32 h = core::round32( v * src_size.Height );
//
//	IImage* dst = new CImage( ECF_A8R8G8B8, core::dimension2du(w, h) );
	return 0;
}


////---------------------------------------------------------------------------
//int	MemblockRepeat( s32 mem, s32 SizeX, s32 SizeY, f32 newU, f32 newV, s32 quality)
////---------------------------------------------------------------------------
//{
//	// Abbruchbedingungen
//    if (IsMemblock(mem)==0) return 0;
//
//	// Memblock Size
//    s32 memX = MemblockX(mem);
//    s32 memY = MemblockY(mem);
//
//	// Neue Memblock Variable, falls memSource Scaliert werden muss
//	s32 nMB = mem;
//
//	// Standard UV Repeat
//	if (newU<=0.0f) newU=1.0f*SizeX/(1.0f*memX);
//    if (newV<=0.0f) newV=1.0f*SizeY/(1.0f*memY);
//
//	// Berechnet neue Textur Größe
//	s32 tileSizeX = SizeX/(s32)(newU);
//    s32 tileSizeY = SizeY/(s32)(newV);
//
//	// Berechnet Anzahl Wiederholungen der Textur
//	s32 factorX = SizeX/tileSizeX;
//	s32 factorY = SizeY/tileSizeY;
//
//	// Scaliere memSource, falls verschieden tileSize
//	if ((memX!=tileSizeX) || (memY!=tileSizeY))
//	{
//		nMB=MemblockScale(nMB,tileSizeX,tileSizeY,quality,0);
//        if (nMB==0) return 0;
//    }
//
//	// Create Memblock Memblock
//	s32 final = MemblockCreate(SizeX,SizeY,32);
//	if (final==0) return 0;
//
//	// Locals
//    u32 color;
//    s32 outX, outY, innX, innY, index;
//
//	// Loop for Anzahl Repeats = factor
//   	for (outY=0; outY<factorY; outY++) {
//	for (outX=0; outX<factorX; outX++) {
//
//	// Loop for Pixels pro Repeat
//   	for (innY=0; innY<tileSizeY; innY++) {
//   	for (innX=0; innX<tileSizeX; innX++) {
//
//		// Read Color
//		index=12+4*(innX+innY*tileSizeX);
//		color=MemblockReadDword(nMB,index);
//
//		// Write Color
//		index=12+4*(innX + innY*SizeX + outX*tileSizeX + outY*tileSizeY*SizeX);
//		MemblockWriteDword(final,index,color);
//
//	}}}}
//
//   if (nMB!=mem) MemblockDelete(nMB);
//   return final;
//}

// // ******************************************************************************************
//int	MemblockCountColors	(s32 mem)
// // ******************************************************************************************
//{
//	// Abbruchbedingung
//	if (IsMemblock(mem)==false) return 0;
//
//	// Source Information
//	s32 memX=MemblockX(mem);
//	s32 memY=MemblockY(mem);
//
//	// ARRAY
//	std::vector<u32> data;
//
//	// LOCALS
//	u32	color;
//	s32 x,y,index;
//	bool found_in_data;
//
//	// COUNT COLORS
//	for (y=0; y<memY; y++)
//	{	for (x=0; x<memX; x++)
//		{
//			// Read Color
//			index=12+4*(x+y*memX);
//			color=MemblockReadDword(mem,index);
//			found_in_data=false;
//
//			// Search Color in Container
//			for (vector<u32>::size_type i=0; i<data.size(); ++i)
//				if (color==data[i])
//					found_in_data=true;
//
//			// If not in Container, add to Container
//			if (found_in_data==false)
//				data.push_back(color);
//		}
//	}
//	return (s32)data.size();
//}
// // ******************************************************************************************
//int	MemblockCountAColors(s32 mem)
// // ******************************************************************************************
//{
//	// Abbruchbedingung
//	if (IsMemblock(mem)==false) return 0;
//
//	// Source Information
//	s32 memX=MemblockX(mem);
//	s32 memY=MemblockY(mem);
//
//	// ARRAY
//	std::vector<unsigned char> data;
//	std::vector<unsigned char>::size_type data_size;
//	unsigned char color;
//
//	// LOCALS
//	s32 x,y,index;
//	bool found_in_data;
//
//	// COUNT COLORS
//	for (y=0; y<memY; y++)
//	{	for (x=0; x<memX; x++)
//		{
//			data_size=data.size();
//			if (data_size==256) return 256;
//
//			// Read R-Color
//			index=12+4*(x+y*memX)+3;
//			color=(unsigned char)MemblockReadByte(mem,index);
//			found_in_data=false;
//
//			// Search Color in Container
//			for (vector<unsigned char>::size_type i=0; i<data_size; ++i)
//				if (color==data[i])
//					found_in_data=true;
//
//			// If not in Container, add to Container
//			if (found_in_data==false)
//				data.push_back(color);
//		}
//	}
//	return (s32)data.size();
//}
// // ******************************************************************************************
//int	MemblockCountRColors(s32 mem)
// // ******************************************************************************************
//{
//	// Abbruchbedingung
//	if (IsMemblock(mem)==false) return 0;
//
//	// Source Information
//	s32 memX=MemblockX(mem);
//	s32 memY=MemblockY(mem);
//
//	// ARRAY
//	std::vector<unsigned char> data;
//	std::vector<unsigned char>::size_type data_size;
//	unsigned char color;
//
//	// LOCALS
//	s32 x,y,index;
//	bool found_in_data;
//
//	// COUNT COLORS
//	for (y=0; y<memY; y++)
//	{	for (x=0; x<memX; x++)
//		{
//			data_size=data.size();
//			if (data_size==256) return 256;
//
//			// Read R-Color
//			index=12+4*(x+y*memX)+2;
//			color=(unsigned char)MemblockReadByte(mem,index);
//			found_in_data=false;
//
//			// Search Color in Container
//			for (vector<unsigned char>::size_type i=0; i<data_size; ++i)
//				if (color==data[i])
//					found_in_data=true;
//
//			// If not in Container, add to Container
//			if (found_in_data==false)
//				data.push_back(color);
//		}
//	}
//	return (s32)data.size();
//}
// // ******************************************************************************************
//int	MemblockCountGColors(s32 mem)
// // ******************************************************************************************
//{
//	// Abbruchbedingung
//	if (IsMemblock(mem)==false) return 0;
//
//	// Source Information
//	s32 memX=MemblockX(mem);
//	s32 memY=MemblockY(mem);
//
//	// ARRAY
//	std::vector<unsigned char> data;
//	std::vector<unsigned char>::size_type data_size;
//	unsigned char color;
//
//	// LOCALS
//	s32 x,y,index;
//	bool found_in_data;
//
//	// COUNT COLORS
//	for (y=0; y<memY; y++)
//	{	for (x=0; x<memX; x++)
//		{
//			data_size=data.size();
//			if (data_size==256) return 256;
//
//			// Read R-Color
//			index=12+4*(x+y*memX)+1;
//			color=(unsigned char)MemblockReadByte(mem,index);
//			found_in_data=false;
//
//			// Search Color in Container
//			for (vector<unsigned char>::size_type i=0; i<data_size; ++i)
//				if (color==data[i])
//					found_in_data=true;
//
//			// If not in Container, add to Container
//			if (found_in_data==false)
//				data.push_back(color);
//		}
//	}
//	return (s32)data.size();
//}
// // ******************************************************************************************
//int	MemblockCountBColors(s32 mem)
// // ******************************************************************************************
//{
//	// Abbruchbedingung
//	if (IsMemblock(mem)==false) return 0;
//
//	// Source Information
//	s32 memX=MemblockX(mem);
//	s32 memY=MemblockY(mem);
//
//	// ARRAY
//	std::vector<unsigned char> data;
//	std::vector<unsigned char>::size_type data_size;
//	unsigned char color;
//
//	// LOCALS
//	s32 x,y,index;
//	bool found_in_data;
//
//	// COUNT COLORS
//	for (y=0; y<memY; y++)
//	{	for (x=0; x<memX; x++)
//		{
//			data_size=data.size();
//			if (data_size==256) return 256;
//
//			// Read R-Color
//			index=12+4*(x+y*memX);
//			color=(unsigned char)MemblockReadByte(mem,index);
//			found_in_data=false;
//
//			// Search Color in Container
//			for (vector<unsigned char>::size_type i=0; i<data_size; ++i)
//				if (color==data[i])
//					found_in_data=true;
//
//			// If not in Container, add to Container
//			if (found_in_data==false)
//				data.push_back(color);
//		}
//	}
//	return (s32)data.size();
//}

// // ******************************************************************************************
//s32 MemblockFloodFill(s32 mem, s32 x, s32 y, u32 newColor, u32 oldColor)
// // ******************************************************************************************
//{
//	if (IsMemblock(mem)==0) return 0;
//
//   	const s32 memX=MemblockX(mem);
//   	const s32 memY=MemblockY(mem);
//	//u32 oldColor=MemblockReadDword(mem,memX,memY,x,y);
//
//	if (MemblockReadDword(mem,memX,memY,x,y)==newColor) return 1;
//
//	s32 lg, rg, px=x;
//	while(MemblockReadDword(mem,memX,memY,x,y)==oldColor)
//	{
//		MemblockWriteDword(mem,memX,memY,x,y,newColor);
//		x--;
//	}
//
//	lg=x+1;
//	x=px+1;
//
//	while(MemblockReadDword(mem,memX,memY,x,y)==oldColor)
//	{
//		MemblockWriteDword(mem,memX,memY,x,y,newColor);
//		x++;
//	}
//	rg=x-1;
//
//	for(x=rg; x>=lg; x--)
//	{
//		if((MemblockReadDword(mem,memX,memY,x,y-1)==oldColor) && (y-1>0))
//			MemblockFloodFill(mem,x,y-1,newColor,oldColor);
//		if((MemblockReadDword(mem,memX,memY,x,y+1)==oldColor) && (y<memY-1))
//			MemblockFloodFill(mem,x,y+1,newColor,oldColor);
//	}
//
//	return 1;
//}
//

} // end namespace video

} // end namespace irr



//
//
//
//
//
//IImage* Tool::createTexAtlas(
//	u32 tile_w, u32 tile_h, u32 cols, u32 rows, const core::array<IImage*>& data )
//{
//	printf("createTexAtlas( tw=%d, th=%d, cols=%d, rows=%d, n=%d )\n", tile_w, tile_h, cols, rows, data.size() );
//
//	if ( tile_w == 0 || tile_h == 0 || cols == 0 || rows == 0 )
//		return 0;
//
//	const u32 dst_w = cols * tile_w;
//	const u32 dst_h = rows * tile_h;
//	IImage* dst = new CImage( ECF_A8R8G8B8, core::dimension2du(dst_w, dst_h) );
//	if (!dst)
//	{
//		return 0;
//	}
//
//	dst->fill( SColor(255,0,0,255) );
//
//	IImage* tmp = new CImage( ECF_A8R8G8B8, core::dimension2du(tile_w, tile_h) );
//
//	if (tmp)
//	{
//		tmp->fill( SColor(0,0,0,0) );
//	}
//
//	for ( u32 y=0; y<rows; y++)
//	{
//	for ( u32 x=0; x<cols; x++)
//	{
//		u32 i = x + y * cols;
//		s32 px = x*tile_w;
//		s32 py = y*tile_h;
//
//		if (i<data.size())
//		{
//			core::dimension2du siz( tile_w, tile_h );
//			IImage* img = data[i];
//			if (dst && img && tmp)
//			{
//				img->copyToScaling( tmp );
//
//				const core::dimension2du& siz = tmp->getDimension();
//
//				tmp->copyTo( dst,
//					core::position2di(px,py),
//					core::recti( core::position2di(0,0), siz ) );
//
//				printf("TexAtlas[%d] x=%d, y=%d, w=%d, h=%d\n", i, x, y, siz.Width, siz.Height );
//			}
//			else
//			{
//				printf("TexAtlas[%d] x=%d, y=%d, nothing todo\n", i, x, y );
//			}
//		}
//
//	} // endfor tile_x
//	} // endfor tile_y
//
//
//}
