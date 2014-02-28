// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXTENSION_C_LIENAR_COLOR_GRADIENT_H__
#define __IRR_EXTENSION_C_LIENAR_COLOR_GRADIENT_H__

#include <irrlicht.h>

#include "IColorGradient.h"

namespace irr
{
	namespace video
	{
		/// @class CLinearColorGradient

		class CLinearColorGradient : public IColorGradient
		{
		public:

			CLinearColorGradient( u32 color_count = 2 ); // const SColor& startColor = SColor(0,0,0,0), const SColor& endColor = SColor(255,255,255,255) );

			virtual ~CLinearColorGradient();

			virtual core::stringc toString( ) const;

			virtual void clear();

			// read from opened xml file
			virtual bool read( io::IXMLReader* pReader );
			// write to opened xml file
			virtual bool write	( io::IXMLWriter* pWriter ) const;

			/// interface IColorGradient

			virtual SColor getColor( f32 t ) const;

			virtual SColorf getColorf( f32 t ) const;

			/// ADDED: 02.04.2013
			// swap two colors based on their indices in array
			virtual bool 					swapColor 	( u32 i1, u32 i2 );
			// sort array by increasing t
			virtual CLinearColorGradient& 	sort 		( bool bReverse = false );

			// sort array by increasing t
			virtual CLinearColorGradient& 	sortQuick 	( bool bReverse = false );
			// sort array by increasing t
			virtual CLinearColorGradient& 	sortBubble	( bool bReverse = false );
			// sort array randomly
			virtual CLinearColorGradient& 	randomize 	( ITimer* timer );


//			// copy operator
//			virtual CLinearColorGradient& 	operator= 	( const CLinearColorGradient& other);
//			// equality operator
//			virtual bool 					operator==	( const CLinearColorGradient& other) const;
//			// get SColor at t in range [0..1]
//			virtual video::SColor			operator()	( f32 t ) const;
//			// read-only access to array-elements
//			virtual const MyColorStruct&	operator[]	( u32 i ) const;
//			// write access to array-elements
//			virtual MyColorStruct& 			operator[]	( u32 i );
//			// add MyColorStruct to array
//			virtual CLinearColorGradient& 	operator+= 	( const MyColorStruct& entry_to_add );
//			// del MyColorStruct from array
//			virtual CLinearColorGradient& 	operator-= 	( const MyColorStruct& entry_to_del );

		};

		class CRadialColorGradient : public IReferenceCounted
		{
		public:

			CRadialColorGradient(  );

			virtual ~CRadialColorGradient();

		private:
		};


	} // end namespace video

} // end namespace irr


#endif // IRRCOLORGRADIENTS_H
