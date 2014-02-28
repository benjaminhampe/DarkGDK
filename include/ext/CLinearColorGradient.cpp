// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include <CLinearColorGradient.h>

#ifdef _DEBUG
#include <../../source/Irrlicht/os.h>
#endif // _DEBUG

#include <../../source/Irrlicht/CImage.h>

namespace irr
{

namespace video
{

/// /// /// /// /// /// /// /// /// /// /// ///

/// class CLinearColorGradient selfprint

/// /// /// /// /// /// /// /// /// /// /// ///


core::stringc CLinearColorGradient::toString( ) const
{
	core::stringc s("CLinearColorGradient[");

	// print number of colors used
	u32 c = getColorCount();
	s += (s32)c;

	// print name
	if (Name.size()>0)
	{
		s += Name;
		s += ", ";
	}

	// print
	s += "] = {\n";

	// print colors
	for (u32 i=0; i<c; i++)
	{
		s += "\t{ ";
		s += video::toString( Colors[i].Color.toSColor() );
		s += ", ";
		s += Colors[i].Position;
		s += " }";
		if (i<c)
		{
			s += ",";
		}
		s += "\n";
	}

	// print
	s += "};\n";
	return s;
}

/// /// /// /// /// /// /// /// /// /// /// ///

/// class CLinearColorGradient

/// /// /// /// /// /// /// /// /// /// /// ///

CLinearColorGradient::CLinearColorGradient( u32 color_count ) // const SColor& startColor, const SColor& endColor)
: IColorGradient( "CLinearColorGradient", color_count )
{
}

CLinearColorGradient::~CLinearColorGradient()
{
	clear();
}

void CLinearColorGradient::clear()
{
	Colors.clear();
}


SColor CLinearColorGradient::getColor( f32 t ) const
{
	return getColorf(t).toSColor();
}

SColorf CLinearColorGradient::getColorf( f32 t ) const
{
//	#if _DEBUG
//		os::Printer::log( "CLinearColorGradient::getColor()", ELL_INFORMATION );
//	#endif // _DEBUG

	const u32 color_count = getColorCount();
	if (color_count==0)
	{
		return SColorf(0,0,0,0);
	}

	if (color_count==1)
	{
		return Colors[0].Color;
	}

	t = core::clamp<f32>( t, 0.0f, 1.0f);

	// find maximum and minimum neighbors
	bool found_greater_t = false;
	u32 greater_t_index = 0;

	for (u32 i=0; i<color_count; i++)
	{
		if ( core::equals(t, Colors[i].Position) )
		{
			return Colors[i].Color;
		}
		else if (Colors[i].Position > t)
		{
			found_greater_t = true;
			greater_t_index = i;
			break;
		}
	}

	if (!found_greater_t)
	{
		return Colors[color_count-1].Color;
	}

	// interpolate between prev and next neighbor color
	const SColorf& A = Colors[greater_t_index-1].Color;
	const SColorf& B = Colors[greater_t_index].Color;
	const f32 min_t = Colors[greater_t_index-1].Position;
	const f32 max_t = Colors[greater_t_index].Position;
	const f32 dx = core::abs_<f32>( (t - min_t) / (max_t - min_t) );
	const f32 fa = A.getAlpha() + dx*( B.getAlpha() - A.getAlpha() );
	const f32 fr = A.getRed() + dx*( B.getRed() - A.getRed() );
	const f32 fg = A.getGreen() + dx*( B.getGreen() - A.getGreen() );
	const f32 fb = A.getBlue() + dx*( B.getBlue() - A.getBlue() );

	return SColorf( fr,fg,fb,fa );
}

//
//bool CLinearColorGradient::addColor( const SColor& stopColor, f32 t )
//{
//	return addColor( SColorf(stopColor), t);
//}
//
//bool CLinearColorGradient::addColor( const SColorf& stopColor, f32 t )
//{
//	#if _DEBUG
//		os::Printer::log( "CLinearColorGradient::addColor()", ELL_INFORMATION );
//	#endif // _DEBUG
//
//	MyColorStruct entry;
//	entry.Color = stopColor;
//	entry.Position = core::clamp<f32>( t, 0.0f, 1.0f );
//
//	/// new 12.04.2013: this version just pushes the new stop-color to the end of array
//	/// 				now the user has to sort the list afterwards
//
////	const u32 c = getColorCount();
////
////	if (c==0)
////	{
//		Colors.push_back( entry );
////	}
////	else // if (c>0)
////	{
////		bool found_greater_t = false;
////		u32 greater_t_index = 0;
////
////		for (u32 i=0; i<c; i++)
////		{
////			if ( core::equals(t, Colors[i].Position) )
////			{
////				return *this;	// dont insert if any t does equal one of array-elements
////			}
////			else if ( Colors[i].Position > t )
////			{
////				found_greater_t = true;
////				greater_t_index = i+1;
////				break;
////			}
////		}
////
////		if (found_greater_t)
////			Colors.insert( entry, greater_t_index);
////		else
////			Colors.push_back( entry );
////	}
//	return true;
//}
//
//bool CLinearColorGradient::setColor( u32 index, const SColor& stopColor, f32 t )
//{
//	const u32 size0 = getColorCount();
//	if (index >= size0)
//		return false;
//
//	Colors[index].Color = SColorf(stopColor);
//	Colors[index].Position = core::clamp<f32>( t, 0.0f, 1.0f );
//	return true;
//}
//
//bool CLinearColorGradient::setColor( u32 index, const SColorf& stopColor, f32 t )
//{
//	const u32 size0 = getColorCount();
//	if (index >= size0)
//		return false;
//
//	Colors[index].Color = stopColor;
//	Colors[index].Position = core::clamp<f32>( t, 0.0f, 1.0f );
//	return true;
//}


// swap two colors based on their indices in array
bool
CLinearColorGradient::swapColor ( u32 i1, u32 i2 )
{
	if (i1==i2)
	{
		return false;
	}

	u32 c = Colors.size();

	if (i1>=c || i2>=c)
	{
		return false;
	}

	MyColorStruct tmp = Colors[i1];
	Colors[i1] = Colors[i2];
	Colors[i2] = tmp;
	return true;
}

CLinearColorGradient&
CLinearColorGradient::sort( bool bReverse )
{
	sortBubble( bReverse );
	return *this;
}

CLinearColorGradient&
CLinearColorGradient::sortQuick( bool bReverse )
{
	return *this;
}

CLinearColorGradient&
CLinearColorGradient::sortBubble( bool bReverse )
{
	#if _DEBUG
	os::Printer::log( "CLinearColorGradient::sortBubble()", ELL_INFORMATION );
	#endif // _DEBUG

	u32 n = Colors.size();
	u32 newn;
	u32 i;
	do
	{
		newn = 1;
		for (i=0; i<n-1; i++)
		{
			if (Colors[i] > Colors[i+1])
			{
				swapColor( i, i+1 );
				newn = i+1;
			} // ende if
		} // ende for
		n = newn;
	}
	while (n > 1);

	return *this;
}

CLinearColorGradient&
CLinearColorGradient::randomize ( ITimer* timer )
{
	if (!timer)
		return *this;

	u32 c = Colors.size();

	if (c<2)
		return *this;

	srand( ((timer->getRealTime()>>2)-1) );

	for (u32 i=0; i<c; i++)
	{
		Colors[i].Position = 1.0f/(f32)(1+rand()%((s32)c));
	}
	return *this;
}

//
//
//// new
//IImage*
//CLinearColorGradient::createImage( u32 w, u32 h, bool bVertical ) const
//{
//	#if _DEBUG
//	os::Printer::log( "CLinearColorGradient::createImage()", ELL_INFORMATION );
//	#endif // _DEBUG
//
//	if (w==0 || h==0)
//	{
//		#if _DEBUG
//		os::Printer::log( "Can't create Image of size zero.", ELL_ERROR );
//		#endif // _DEBUG
//		return 0;
//	}
//
//	IImage* tmp = (IImage*)new CImage( this->getColorFormat(), core::dimension2du(w,h) );
//	if (!tmp)
//	{
//		#if _DEBUG
//		os::Printer::log( "Could not create CImage", ELL_ERROR );
//		#endif // _DEBUG
//		return 0;
//	}
//
//	const core::dimension2du& ImageSize = tmp->getDimension();
//
//	// vertical filling
//	if ( bVertical )
//	{
//		const f32 fy = 1.0f / (f32)h;
//
//		for (u32 y=0; y<ImageSize.Height; y++)
//		{
//			SColor color = getColor( fy*y );
//
//			for (u32 x=0; x<ImageSize.Width; x++)
//			{
//				tmp->setPixel( x,y,color );
//			}
//		}
//
//	}
//	// horizontal filling
//	else
//	{
//		const f32 fx = 1.0f / (f32)w ;
//
//		for (u32 x=0; x<ImageSize.Width; x++)
//		{
//			SColor color = getColor( fx*x );
//
//			for (u32 y=0; y<ImageSize.Height; y++)
//			{
//				tmp->setPixel( x,y,color );
//			}
//		}
//	}
//
//	return tmp;
//}
//
//// new
//ITexture*
//CLinearColorGradient::createTexture( IVideoDriver* driver, u32 w, u32 h, bool bVertical, const io::path& name ) const
//{
//	#if _DEBUG
//	os::Printer::log( "CLinearColorGradient::createTexture()", ELL_INFORMATION );
//	#endif // _DEBUG
//
//	if (!driver)
//	{
//		#if _DEBUG
//		os::Printer::log( "Can't create Texture without IVideoDriver (invalid pointer).", ELL_ERROR );
//		#endif // _DEBUG
//		return 0;
//	}
//
//	if (w==0 || h==0)
//	{
//		#if _DEBUG
//		os::Printer::log( "Can't create Texture of size zero.", ELL_ERROR );
//		#endif // _DEBUG
//		return 0;
//	}
//
//	IImage* tmp = createImage(w,h,bVertical);
//	if (!tmp)
//	{
//		#if _DEBUG
//		os::Printer::log( "Could not create Image", ELL_ERROR );
//		#endif // _DEBUG
//		return 0;
//	}
//
//	io::path TexName = name;
//	if (TexName.size() == 0)
//	{
//		TexName = getName();
//		TexName += io::path("_");
//		if (bVertical)
//			TexName += io::path("v");
//		else
//			TexName += io::path("h");
//		TexName += io::path("_");
//		TexName += (s32)w;
//		TexName += io::path("_x_");
//		TexName += (s32)h;
//	}
//
//	bool bMipMap = driver->getTextureCreationFlag( ETCF_CREATE_MIP_MAPS );
//	driver->setTextureCreationFlag( ETCF_CREATE_MIP_MAPS, false );
//	ITexture* tex = driver->addTexture( TexName, tmp, 0);
//	driver->setTextureCreationFlag( ETCF_CREATE_MIP_MAPS, bMipMap );
//	tmp->drop();
//
//	if (!tex)
//	{
//		#if _DEBUG
//		os::Printer::log( "Could not create Texture", ELL_ERROR );
//		#endif // _DEBUG
//		return 0;
//	}
//
//	return tex;
//}

bool
CLinearColorGradient::read ( io::IXMLReader* pReader )
{
	if (pReader)
		return false;
	return true;
}

bool
CLinearColorGradient::write ( io::IXMLWriter* pWriter ) const
{
	if (pWriter)
		return false;
	return true;
}
//
//// copy
//CLinearColorGradient&
//CLinearColorGradient::operator= ( const CLinearColorGradient& other)
//{
//	return *this;
//}
//
//// test for equality
//bool
//CLinearColorGradient::operator== ( const CLinearColorGradient& other) const
//{
//	return false;
//}
//
//SColor
//CLinearColorGradient::operator() ( f32 t ) const
//{
//	return getColor(t);
//}
//
//const CLinearColorGradient::MyColorStruct&
//CLinearColorGradient::operator[]	( u32 i ) const
//{
//	return Colors[i];
//}
//
//CLinearColorGradient::MyColorStruct&
//CLinearColorGradient::operator[]	( u32 i )
//{
//	return Colors[i];
//}
//
//CLinearColorGradient&
//CLinearColorGradient::operator+= ( const MyColorStruct& entry_to_add )
//{
//
//	return *this;
//}
//
//CLinearColorGradient&
//CLinearColorGradient::operator-= ( const MyColorStruct& entry_to_del )
//{
//	return *this;
//}
//
//CLinearColorGradient::MyColorStruct&
//CLinearColorGradient::MyColorStruct::operator= ( const MyColorStruct& other )
//{
//	Color = other.Color;
//	Position = other.Position;
//	return *this;
//}
//
//bool
//CLinearColorGradient::MyColorStruct::operator< ( const MyColorStruct& other ) const
//{
//	if (Position < other.Position)
//		return true;
//	else
//		return false;
//}
//
//bool
//CLinearColorGradient::MyColorStruct::operator> ( const MyColorStruct& other ) const
//{
//	if (Position > other.Position)
//		return true;
//	else
//		return false;
//}
//
//bool
//CLinearColorGradient::MyColorStruct::operator==	( const MyColorStruct& other ) const
//{
//	if ( core::equals( Position, other.Position ) )
//		return true;
//	else
//		return false;
//}
//
//bool
//CLinearColorGradient::MyColorStruct::operator!=	( const MyColorStruct& other ) const
//{
//	return (!( (*this)==other ));
//}
//
//bool
//CLinearColorGradient::MyColorStruct::operator<=	( const MyColorStruct& other ) const
//{
//	return ( ((*this) == other) || ((*this) < other) );
//}
//bool
//CLinearColorGradient::MyColorStruct::operator>=	( const MyColorStruct& other ) const
//{
//	return ( ((*this) == other) || ((*this) > other) );
//}

} // end namespace video

} // end namespace irr
