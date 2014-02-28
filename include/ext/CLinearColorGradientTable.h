// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXTENSION_C_LIENAR_COLOR_GRADIENT_WITH_LOOKUP_TABLE_H__
#define __IRR_EXTENSION_C_LIENAR_COLOR_GRADIENT_WITH_LOOKUP_TABLE_H__

#include <irrlicht.h>

#include "IColorGradient.h"

namespace irr
{
	namespace video
	{
		/// @class CLinearColorGradientTable

		class CLinearColorGradientTable : public IColorGradient
		{
			core::array<SColorf> LookUpTable;
			f32 InvLookUpTableSize;
		public:

			/// @brief value-constructor
			explicit CLinearColorGradientTable( u32 color_count = 0, u32 table_size = 1024);

			/// @brief set base-name of color-gradient
			virtual ~CLinearColorGradientTable();

			/// @brief get formatted self-decription ( text as stringc )
			virtual core::stringc toString( ) const;

			/// @brief load from xml file-stream
			virtual bool read ( io::IXMLReader* pReader );

			/// @brief save to xml file-stream
			virtual bool write ( io::IXMLWriter* pWriter ) const;

			/// @brief erase whole allocated memory by clearing the arrays
			virtual void clear()
			{
				LookUpTable.clear();
				IColorGradient::clear();
			}

			/// @brief get size of array-elements in color-lookup-table
			virtual u32 getTableSize() const
			{
				return LookUpTable.size();
			}

			/// @brief management of lookup-table
			virtual void setTableSize( u32 table_size = 1024,	bool bFillZero = false )
			{
				LookUpTable.reallocate( table_size );
				LookUpTable.set_used( table_size );

				/// erase content without reallocation
				if (bFillZero)
				{
					const SColorf zeroColor(0,0,0,0);

					for (u32 i=0; i<LookUpTable.size(); i++)
					{
						LookUpTable[i] = zeroColor;
					}
				}

				if (table_size > 1)
				{
					InvLookUpTableSize = core::reciprocal( (f32)(table_size-1) );
				}
				else
				{
					InvLookUpTableSize = 0.0f;
				}

			}

			/// @brief calculate new lookup-table-colors from stop-color-array
			virtual void updateTable()
			{
				#if _DEBUG
					printf( "CLinearColorGradientTable::updateTable()\n" );
				#endif // _DEBUG

				const u32 lut_count = LookUpTable.size();

				if (lut_count == 0)
				{
					return;
				}

				if (lut_count == 1)
				{
					return;
				}


				/// loop lookup-table
				for (u32 i=0; i<lut_count; i++)
				{
					/// calculate current 't'

					f32 t = (f32)i * InvLookUpTableSize;

					t = core::clamp<f32>( t, 0.0f, 1.0f);

					/// find corresponding neighbor-colors

					bool found_greater_t = false;
					u32 greater_t_index = 0;

					for (u32 c=0; c<getColorCount(); c++)
					{
						const f32 pos = Colors[c].Position;

						if ( t < pos )
						{
							found_greater_t = true;
							greater_t_index = c;
							break;
						}
						else if ( core::equals( t, pos ) )
						{
							greater_t_index = c;
							break;
						}
					}

					if (!found_greater_t)
					{
						LookUpTable[i] = Colors[getColorCount()-1].Color;
					}
					else
					{
						/// interpolate color between neighbors
						const SColorf& A = Colors[greater_t_index-1].Color;
						const SColorf& B = Colors[greater_t_index].Color;
						const f32 min_t = Colors[greater_t_index-1].Position;
						const f32 max_t = Colors[greater_t_index].Position;
						const f32 dx = core::abs_<f32>( (t - min_t) / (max_t - min_t) );
						const f32 fa = A.getAlpha() + dx*( B.getAlpha() - A.getAlpha() );
						const f32 fr = A.getRed() + dx*( B.getRed() - A.getRed() );
						const f32 fg = A.getGreen() + dx*( B.getGreen() - A.getGreen() );
						const f32 fb = A.getBlue() + dx*( B.getBlue() - A.getBlue() );

						LookUpTable[i] = SColorf( fr,fg,fb,fa );
					}


				#if _DEBUG
					core::stringc dText("LookUpTable[");
					dText += i;
					dText += "], t=";
					dText += t;
					dText += ", t_index=";
					dText += greater_t_index;
					dText += ", color=";
					dText += video::toString( LookUpTable[i].toSColor() );
					printf( "%s\n", dText.c_str() );
				#endif // _DEBUG

				}
			}

			/// @brief get stopcolor
			virtual SColor getColor( f32 t ) const
			{
				return getColorf(t).toSColor();
			}

			/// @brief get stopcolor
			virtual SColorf getColorf( f32 t ) const
			{
				t = core::clamp<f32>( t, 0.0f, 1.0f);

				const u32 table_size = LookUpTable.size();

				if (table_size==0)
					return SColor(0,0,0,0);

				// modulo count/number of colors to be in array-index-bounds [0,count-1]
				const u32 index = ((u32)core::round32( t*(f32)table_size )) % table_size;

				_IRR_DEBUG_BREAK_IF( index >= table_size )
				return LookUpTable[ index ];
			}
		};

	} // end namespace video

} // end namespace irr

#endif // __IRR_EXTENSION_C_LIENAR_COLOR_GRADIENT_WITH_LOOKUP_TABLE_H__
