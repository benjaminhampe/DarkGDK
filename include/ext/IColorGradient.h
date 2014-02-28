// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXTENSION_INTERFACE_I_COLOR_GRADIENT_H__
#define __IRR_EXTENSION_INTERFACE_I_COLOR_GRADIENT_H__

#include <irrlicht.h>

#include <../../source/Irrlicht/CImage.h>

#ifdef _DEBUG
#include <../../source/Irrlicht/os.h>
#endif // _DEBUG

namespace irr
{
namespace video
{
	/// @function convert SColor to formatted string
	//core::stringc toString( const SColor& color );

	/// @function convert SColorf to formatted string
	//core::stringc toString( const SColorf& color );


	/// /// /// /// /// /// /// /// /// /// /// ///

	/// format SColor to string

	/// /// /// /// /// /// /// /// /// /// /// ///


	REALINLINE core::stringc toString( const SColor& color )
	{
		core::stringc s("SColor(");
		s += color.getAlpha();
		s += ",";
		s += color.getRed();
		s += ",";
		s += color.getGreen();
		s += ",";
		s += color.getBlue();
		s += ")";
		return s;
	}

	REALINLINE core::stringc toString( const SColorf& color )
	{
		core::stringc s("SColorf(");
		s += color.getAlpha();
		s += ",";
		s += color.getRed();
		s += ",";
		s += color.getGreen();
		s += ",";
		s += color.getBlue();
		s += ")";
		return s;
	}

	/// @class IColorGradient ( pure virtual/abstract methods -> interface definition )
	class IColorGradient : public IReferenceCounted
	{
	public:

		/// @class MyColorStruct { f32 t; scolorf128 color }
		struct MyColorStruct
		{
			core::stringc Name;
			SColorf Color;
			f32 Position;			// in range 0..1

			/// @brief default constructor
			MyColorStruct( )
				: Name("SColorf(0,0,0,0),f32(0.0f)")
				, Color(SColorf(0,0,0,0))
				, Position(0)
			{ }

			/// @brief value constructor
			MyColorStruct( const SColor& color, f32 t )
				: Name("SColor(")
				, Color(SColorf(color))
				, Position(t)
			{
				// Name = "SColor(";
				Name += Color.getAlpha();
				Name += ",";
				Name += Color.getRed();
				Name += ",";
				Name += Color.getGreen();
				Name += ",";
				Name += Color.getBlue();
				Name += "),f32(";
				Name += Position;
				Name += ")";
			}

			/// @brief value constructor
			MyColorStruct( const SColorf& color, f32 t )
				: Name("SColorf(")
				, Color(color)
				, Position(t)
			{
				// Name = "SColorf(";
				Name += Color.getAlpha();
				Name += ",";
				Name += Color.getRed();
				Name += ",";
				Name += Color.getGreen();
				Name += ",";
				Name += Color.getBlue();
				Name += "),f32(";
				Name += Position;
				Name += ")";
			}

			/// @brief copy constructor
			MyColorStruct( const MyColorStruct& other)
				: Name(""), Color(SColorf(0,0,0,0)), Position(0.0f)
			{
				if ( this != &other )
				{
					Name = (other.Name);
					Color = (other.Color);
					Position = (other.Position);
				}
			}

			/// @brief copy operator
			MyColorStruct&	operator= ( const MyColorStruct& other )
			{
				if ( this == &other )
					return *this;

				Name = (other.Name);
				Color = (other.Color);
				Position = (other.Position);
				return *this;
			}

			/// @brief multiplies color times t in range 0..1
			virtual MyColorStruct&	operator* 	( f32 value )
			{
				value = core::clamp<f32>( value, 0.0f, 1.0f );
				Color.set(
					core::clamp<f32>( Color.getAlpha() * value, 0.f, 1.f ),
					core::clamp<f32>( Color.getRed() * value, 0.f, 1.f ),
					core::clamp<f32>( Color.getGreen() * value, 0.f, 1.f ),
					core::clamp<f32>( Color.getBlue() * value, 0.f, 1.f ) );
				return *this;
			}

			/// @brief lower than operator, only operating on t
			virtual bool operator< 	( const MyColorStruct& other ) const
			{
				if ( this == &other )
					return false;
				if ((this->Position) < other.Position)
					return true;
				else
					return false;
			}

			/// @brief greater than operator, only operating on t
			virtual bool operator> 	( const MyColorStruct& other ) const
			{
				if ( this == &other )
					return false;
				if ((this->Position) < other.Position)
					return true;
				else
					return false;
			}
//
//			/// @brief equality operator, operating on both t and color
//			virtual bool operator==	( const MyColorStruct& other ) const
//			{
//				if ( *this == other )
//					return false;
//
//				if ( core::equals(*this.Position, other.Position)
//						&& (this->Name, other.Name)
//						&& (this->Color, other.Color) )
//				{
//					return true;
//				}
//				else
//				{
//					return false;
//				}
//			}
//
//			/// @brief inequality operator
//			virtual bool operator!=	( const MyColorStruct& other ) const
//			{
//				if ( *this == other )
//					return false;
//				else
//					return true;
//			}
//
//			/// @brief lower or equal than operator
//			virtual bool operator<=	( const MyColorStruct& other ) const
//			{
//				if ( ( *this == other ) || ( *this < other ) )
//					return true;
//				else
//					return false;
//			}
//
//			/// @brief greater or equal than operator
//			virtual bool operator>=	( const MyColorStruct& other ) const
//			{
//				if ( ( *this == other ) || ( *this > other ) )
//					return true;
//				else
//					return false;
//			}

		};

	protected:
		core::stringc Name;

		core::array<MyColorStruct> Colors;

	public:
		/// @brief get formatted self-decription ( text as stringc )
		virtual core::stringc toString( ) const = 0;

		/// return interpolated color t in range [0,1]
		virtual SColor getColor( f32 t ) const = 0;

		/// return interpolated color t in range [0,1]
		virtual SColorf getColorf( f32 t ) const = 0;

		/// @brief load from xml file-stream
		virtual bool read ( io::IXMLReader* pReader ) = 0;

		/// @brief save to xml file-stream
		virtual bool write ( io::IXMLWriter* pWriter ) const = 0;


		/// @brief value constructor ( default )
		explicit IColorGradient( core::stringc name = "", u32 color_count = 0 )
			: Name(name)
		{
			setColorCount( color_count, true );
		}

		/// @brief value destructor, erases used memory for stop-color-array
		virtual ~IColorGradient()
		{
			clear();
		}

		/// @brief set basename of color-gradient
		virtual void setName( const core::stringc& name )
		{
			Name = name;
		}

		/// @brief get basename of color-gradient
		virtual core::stringc getName( ) const
		{
			return Name;
		}

		/// @brief erase whole allocated memory by clearing the arrays
		virtual void clear()
		{
			Colors.clear();
		}

		/// @brief get size of stop-color-array
		virtual u32 getColorCount() const
		{
			return Colors.size();
		}

		/// @brief get size of stop-color-array
		virtual void setColorCount( u32 color_count, bool bFillZero = false )
		{
			Colors.reallocate( color_count );
			Colors.set_used( 0 );

//			/// erase content without reallocation
//			if (bFillZero && color)
//			{
				const SColorf zeroColor(0,0,0,0);
				const f32 zeroPosition(0.0f);
				const MyColorStruct myColor( zeroColor, zeroPosition );

				for (u32 i=0; i<color_count; i++)
				{
					Colors.push_back( myColor );
				}
//			}
		}

		/// @brief management of stop-color-array
		virtual void addColor( const SColor& stopColor, f32 t = 0.5f )
		{
			return addColor( SColorf(stopColor), t);
		}

		/// @brief management of stop-color-array
		virtual void addColor( const SColorf& stopColor, f32 t = 0.5f )
		{
			Colors.push_back( MyColorStruct( stopColor, core::clamp<f32>(t,0.f,1.f) ) );
		}

		/// @brief management of stop-color-array
		virtual bool setColor( u32 index, const SColor& stopColor, f32 t = 0.5f )
		{	const u32 c = getColorCount();
			if (index >= c ) return false;
			Colors[index].Color = SColorf(stopColor);
			Colors[index].Position = core::clamp<f32>( t, 0.0f, 1.0f );
			return true;
		}

		/// @brief management of stop-color-array
		virtual bool setColor( u32 index, const SColorf& stopColor, f32 t = 0.5f )
		{	const u32 c = getColorCount();
			if (index >= c) return false;
			Colors[index].Color = stopColor;
			Colors[index].Position = core::clamp<f32>( t, 0.0f, 1.0f );
			return true;
		}

		/// @brief get solid or transparency material
		virtual bool isTransparent( ) const
		{
			bool bTransparent = false;
			u32 i=0;
			u32 c=getColorCount();

			while (i<c)
			{
				if (Colors[i].Color.getAlpha() < 1.0f) // not 255
				{
					bTransparent = true;
					break;
				}
				i++; // dont ever forget again foo
			}
			return bTransparent;
		}

		/// @brief get solid or transparent material-type
		virtual E_MATERIAL_TYPE getMaterialType( ) const
		{	if (isTransparent())
				return EMT_TRANSPARENT_ALPHA_CHANNEL;
			else
				return EMT_SOLID;
		}

		/// @brief get solid or transparent color-format
		virtual ECOLOR_FORMAT getColorFormat( ) const
		{	if (isTransparent())
				return ECF_A8R8G8B8;
			else
				return ECF_R8G8B8;
		}

		/// @brief create image from colorgradient
		virtual IImage* createImage(
			u32 w,
			u32 h,
			bool bVertical = false ) const
		{
			#if _DEBUG
			os::Printer::log( "createImage()", ELL_INFORMATION );
			#endif // _DEBUG

			if (w==0 || h==0)
			{
				#if _DEBUG
				os::Printer::log( "Can't create Image of size zero.", ELL_ERROR );
				#endif // _DEBUG
				return 0;
			}

			IImage* img = (IImage*)new CImage( this->getColorFormat(), core::dimension2du(w,h) );
			if (!img)
			{
				#if _DEBUG
				os::Printer::log( "Could not create CImage", ELL_ERROR );
				#endif // _DEBUG
				return 0;
			}

			const core::dimension2du& ImageSize = img->getDimension();

			// vertical filling
			if ( bVertical )
			{
				const f32 fy = 1.0f / (f32)h;

				for (u32 y=0; y<ImageSize.Height; y++)
				{
					SColor color = getColor( fy*y );

					for (u32 x=0; x<ImageSize.Width; x++)
					{
						img->setPixel( x,y,color );
					}
				}

			}
			// horizontal filling
			else
			{
				const f32 fx = 1.0f / (f32)w ;

				for (u32 x=0; x<ImageSize.Width; x++)
				{
					SColor color = getColor( fx*x );

					for (u32 y=0; y<ImageSize.Height; y++)
					{
						img->setPixel( x,y,color );
					}
				}
			}

			return img;
		}

		/// @brief create texture from colorgradient
		virtual ITexture* createTexture(
			video::IVideoDriver* driver,
			u32 w,
			u32 h,
			bool bVertical = false,
			const io::path& name = "" ) const
		{
			#if _DEBUG
			os::Printer::log( "createTexture()", ELL_INFORMATION );
			#endif // _DEBUG

			if (!driver)
			{
				#if _DEBUG
				os::Printer::log( "Can't create Texture without IVideoDriver (invalid pointer).", ELL_ERROR );
				#endif // _DEBUG
				return 0;
			}

			if (w==0 || h==0)
			{
				#if _DEBUG
				os::Printer::log( "Can't create Texture of size zero.", ELL_ERROR );
				#endif // _DEBUG
				return 0;
			}

			IImage* img = createImage(w,h,bVertical);
			if (!img)
			{
				#if _DEBUG
				os::Printer::log( "Could not create Image", ELL_ERROR );
				#endif // _DEBUG
				return 0;
			}

			io::path TexName = name;
			if (TexName.size() == 0)
			{
				TexName = getName();
				TexName += io::path("_");
				if (bVertical)
					TexName += io::path("v");
				else
					TexName += io::path("h");
				TexName += io::path("_");
				TexName += (s32)w;
				TexName += io::path("_x_");
				TexName += (s32)h;
			}

			bool bMipMap = driver->getTextureCreationFlag( ETCF_CREATE_MIP_MAPS );
			driver->setTextureCreationFlag( ETCF_CREATE_MIP_MAPS, false );
			ITexture* tex = driver->addTexture( TexName, img, 0);
			driver->setTextureCreationFlag( ETCF_CREATE_MIP_MAPS, bMipMap );
			img->drop();

			if (!tex)
			{
				#if _DEBUG
				os::Printer::log( "Could not create Texture", ELL_ERROR );
				#endif // _DEBUG
				return 0;
			}

			return tex;
		}

		/// @brief create texture from colorgradient
		virtual bool saveImage(
			IVideoDriver* driver,
			const io::path& filename = "test_colorgradient.png",
			u32 w = 1024, u32 h = 1024, bool bVertical = false )
		{
			if (!driver)
			{
				printf("Invalid pointer to IVieoDriver\n");
				return false;
			}

			IImage* img = createImage( w, h, bVertical );
			if (!img)
			{
				printf("Could not create image from ColorGradient\n");
				return false;
			}

			if (!driver || !driver->writeImageToFile(img, filename ) )
			{
				printf("Could not save image from ColorGradient to file\n");
				return false;
			}

			return true;
		}


	};


} // end namespace video

} // end namespace irr

#endif // ICOLORGRADIENT_H
