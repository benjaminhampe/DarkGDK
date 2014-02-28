#ifndef __IRR_C_DYNAMIC_RECTANGLE_MATRIX_H__
#define __IRR_C_DYNAMIC_RECTANGLE_MATRIX_H__

#include <cstdlib>
#include <cstdio>

#include <irrlicht.h>
#include <../../source/Irrlicht/os.h>
#include <../../source/Irrlicht/CImage.h>

#include <GL/gl.h>
#include <GL/glu.h>


#if defined(__GXX_EXPERIMENTAL_CXX0X) || __cplusplus >= 201103L
	#include <functional>
#endif

/// CMatrix_log/_error macros

#if defined(_DEBUG) || defined(DEBUG)
	#define CMatrix_log( args...) \
	{ \
		printf( args ); \
	}
	#define CMatrix_error( args... ) \
	{ \
		printf( stderr, args ); \
		fprintf( stdout, args ); \
	}
#else
	#define CMatrix_log( args... )
	#define CMatrix_error( args... ) \
	{ \
		fprintf( stderr, args ); \
	}
#endif

namespace irr
{
namespace core
{

	template <class ElementType>
    class CMatrix : public IReferenceCounted
	{
	private:
		u32 Rows;	/// number of rows ( y-direction )
		u32 Cols;	/// number of columns ( x-direction )
		u32 Size;	/// number of elements in matrix ( == Rows * Cols )
		u32 BitsPerElement; /// size in bits ( 32, 64 )
		ElementType** Data;	/// pointer to 2d field == array of rows ( each row is an arrays with "Cols" elements )
		core::stringc Name;
		bool IsIdentity;
		bool IsDeterminantDirty;
		u32 Rank; // ( Rank always lower or equal then the minimum of (Rows,Cols) == number of linear independant basevectors)
		ElementType Determinant;

	public:

	const static ElementType NullValue = 0.0;
	const static ElementType EinsValue = 1.0;

	static ElementType** createArray2d(u32 rows, u32 cols)
	{
		CMatrix_log( "CMatrix()\n");

		// fill with zeros with memset
		const u32 byte_count = (u32)sizeof(ElementType);

		// allocate memory for vector that stores vectors of rows
		ElementType** p =new ElementType*[rows];

		// allocate memory for each row vector
		for (u32 y=0; y<rows; y++)
		{
			p[y]=new ElementType[cols];
		}

		// wenn 64-bit
		if (byte_count == 8)
			memset( dynamic_cast<f64**>( &p ), 0, byte_count );
		// oder 32-bit
		else if (byte_count==4)
			memset32( dynamic_cast<ElementType**>( &p ), 0, byte_count );
		else

		return p;
	}

	void clear()
	{
		CMatrix_log( "CMatrix::clear()\n");

		/// delete 2D Array of Floats
		if (Data)
		{
			/// loop rows
			for (u32 i=0; i<Rows; i++)
			{
				/// delete each row
				ElementType* row = Data[i];
				if (row)
				{
					/// delete array
					delete [] row;

					Data[i] = 0;
				}
			}

			/// delete array of pointer to arrays
			delete [] Data;
			Data = 0;
		}

		Rows = 0;
		Cols = 0;
		Size = 0;
	}

	bool empty() const
	{
		CMatrix_log( "CMatrix::clear()\n");

		if (!Data)
			return true;
		else
			return false;
	}

	void fill( const ElementType& value )
	{
		CMatrix_log( "CMatrix::fill()\n");

		if (empty())
		{
			CMatrix_error( "CMatrix::fill() - No valid data-pointer.\n");
			return;
		}

		for (u32 y=0; y<Rows; y++)
		{
			for (u32 x=0; x<Cols; x++)
			{
				Data[y][x] = value;
			}
		}
	}


	bool resize(u32 rows, u32 cols, bool keepData, bool canShrink )
	{
		CMatrix_log( "CMatrix::resize(%d,%d)\n", rows, cols );

		clear();

		Rows = rows;
		Cols = cols;
		Size = Rows*Cols;
		Data = createArray2d( Rows, Cols );

		fill(0.0f);

		return true;
	}

	typedef core::vector2d<ElementType> TVector2d;

	TVector2d getMinMax() const
	{
		CMatrix_log( "CMatrix::getMinMax()\n" );

		if (!Data)
			return TVector2d( 0.0f, 0.0f );

		TVector2d result( FLT_MAX, FLT_MIN );

		for (u32 y=0; y<Rows; y++)
		{
			for (u32 x=0; x<Cols; x++)
			{
				const ElementType& value = Data[y][x];
				if ( result.X > value ) result.X = value;
				if ( result.Y < value ) result.Y = value;
			}
		}

		CMatrix_log( "min = %lf, max = %lf\n", (f64)result.X, (f64)result.Y );

		return result;
	}

	/// get access ( public ) to raw data
	ElementType** getData()
	{
		return Data;
	}

	/// get Rows & Cols
	core::dimension2du getDimension() const
	{
		return core::dimension2du( Rows, Cols );
	}

	/// get Number of rows i have (y-dir)
	u32 getRows() const
	{
		return Rows;
	}

	/// get Number of columns i have (x-dir)
	u32 getCols() const
	{
		return Cols;
	}

	// /// get Product of Rows and Colums for linear memory access, its elementcount not the bytesize of allocated mem
	//u32 getSize() const { return Size; }

	/// get my Name
	core::stringc getName() const
	{
		return Name;
	}

	/// get my Name
	void setName( const core::stringc& name = "CMatrix" )
	{
		Name = name;
	}

	/// print CMatrix to String
	core::stringc toString() const
	{
		core::stringc s("CMatrix<ElementType>("); s+=Rows; s+=","; s+=Cols; s+=",";

		if (Name.size()>0)
		{
			s+=Name;	s+=",";
		}
		s+=") = { \n";

		if (Data)
		{
			for (u32 y=0; y<Rows; y++)
			{
				s+="\t{\t";
				for (u32 x=0; x<Cols; x++)
				{
					s+= core::floor32( (ElementType)Data[y][x] );
					if (x<Cols-1)
					{
						s+=" ";
					}
				}
				s+="\t}";
				if (y<Rows-1)
				{
					s+=",";
				}
				s+="\n";
			}
		}
		s+="};\n";

		return s;
	}

	/// secure access to value ( with out-of-bounds check )
	ElementType getElement(u32 row, u32 col) const
	{
		if ((row>=0) && (col>=0) && (row<Rows) && (col<Cols))
		{
			return Data[row][col];
		}
		else
		{
			return 0.0f;
		}
	}

	/// secure access to value ( with out-of-bounds check )
	ElementType getElement(u32 index) const
	{
		_IRR_DEBUG_BREAK_IF( index<0 );
		_IRR_DEBUG_BREAK_IF( index>= this->getSize() );
		u32 row = index / Cols;
		u32 col = index - row * Cols;
		if ((row>=0) && (col>=0) && (row<Rows) && (col<Cols))
		{
			return Data[row][col];
		}
		else
		{
			return 0.0f;
		}
	}

	/// secure access to value ( with out-of-bounds check )
	bool setElement(u32 row, u32 col, ElementType element)
	{
		_IRR_DEBUG_BREAK_IF( row < 0 );
		_IRR_DEBUG_BREAK_IF( col < 0 );
		_IRR_DEBUG_BREAK_IF( row >= Rows );
		_IRR_DEBUG_BREAK_IF( col >= Cols );
		if ((row<Rows) && (col<Cols))
		{
			Data[row][col] = element;
			return true;
		}

		return false;
	}

	/// secure access to value ( with out-of-bounds check )
	bool setElement(u32 index, ElementType element)
	{
		_IRR_DEBUG_BREAK_IF( index<0 );
		_IRR_DEBUG_BREAK_IF( index>= this->getSize() );
		u32 row = index / Cols;
		u32 col = index - row * Cols;
		if ((row>=0) && (col>=0) && (row<Rows) && (col<Cols))
		{
			Data[row][col] = element;
			return true;
		}

		return false;
	}

	///// secure access to value ( with out-of-bounds check )
	//const ElementType& operator() (u32 index) const
	//{
	//    return Data[ (index<getSize())?index:0 ];
	//}
	//
	///// secure access to value ( with out-of-bounds check )
	//ElementType& operator() (u32 index)
	//{
	//    return Data[ (index<getSize())?index:0 ];
	//}
	//
	///// secure access to value ( with out-of-bounds check )
	//const ElementType& operator() (u32 row, u32 col) const
	//{
	//    u32 index = row*Cols+col;
	//    return Data[ (index<getSize())?index:0 ];
	//}
	//
	///// secure access to value ( with out-of-bounds check )
	//ElementType& operator() (u32 row, u32 col)
	//{
	//    u32 index = row*Cols+col;
	//    return Data[ (index<getSize())?index:0 ];
	//}


	/// copy operator overload
	CMatrix& operator= ( const CMatrix& other )
	{
		#ifdef _DEBUG
		printf( "operator= ()\n" );
		#endif // _DEBUG

		return assign(other);
	}

	/// copy other CMatrix
	CMatrix& assign( const CMatrix& other )
	{
		#ifdef _DEBUG
		printf( "assign()\n" );
		#endif // _DEBUG

		clear();
		Rows = other.getRows();
		Cols = other.getCols();
		Size = other.getSize();
		Name = other.getName();

		resize( Rows, Cols );

		for (u32 y=0; y<Rows; y++)
		{
			for (u32 x=0; x<Cols; x++)
			{
				Data[y][x] = other.getElement(y,x);
			}
		}
		return *this;
	}

	/// copy this function
	CMatrix clone() const
	{
		return CMatrix( *this );
	}


//
//		/// set row-data ( replace ) with array-values
//		template <class T>
//		bool setRow( u32 row, const T* data, u32 elem_count, ElementType fillSpace = 0.0f )
//		{
//			if (!data)
//			{
//				printf("fillRow() - ERROR Cant set row of empty CMatrix, return false.\n");
//				return false;
//			}
//
//			if (row >= Rows)
//				return false;
//
//			u32 i_max = core::min_<u32>( elem_count, Cols);
//
//			T* p = const_cast<T*>(data);
//
//			for (u32 i=0; i<i_max; i++)
//			{
//				if (p)
//				{
//					ElementType value = (ElementType)(*p);
//					Data[row][i] = value;
//					p++;
//				}
//				else
//				{
//					break;
//				}
//			}
//
//			if (i_max < Cols)
//			{
//				for (u32 i=i_max; i<Cols; i++)
//				{
//					Data[row][i] = fillSpace;
//				}
//			}
//
//			return true;
//		}
//
//		/// set row-data ( replace ) with array-values
//		template <class T>
//		bool setRow( u32 row, const core::array<T>& data, bool bFillBounds = false, ElementType fillSpace = 0.0f )
//		{
//			if (!Data)
//			{
//				printf("fillRow() - ERROR Cant set row of empty CMatrix, return false.\n");
//				return false;
//			}
//
//			if (row >= Rows)
//				return false;
//
//			u32 i_max = core::min_<u32>( data.size(), Cols);
//
//			for (u32 i=0; i<i_max; i++)
//			{
//				Data[row][i] = (ElementType)data[i];
//			}
//
//			if (bFillBounds)
//			{
//				if (i_max < Cols)
//				{
//					for (u32 i=i_max; i<Cols; i++)
//					{
//						Data[row][i] = fillSpace;
//					}
//				}
//			}
//			return true;
//		}
//




	/// value contructor
	CMatrix( u32 rows, u32 cols )
		: Rows(0), Cols(0), Size(0), Data(0), Name("")
	{
		CMatrix_log( "CMatrix::CMatrix(%d,%d)\n", rows, cols );
		resize( rows, cols );
	}

	/// copy contructor
	CMatrix( const CMatrix& other )
		: Rows(0), Cols(0), Size(0), Data(0), Name("")
	{
		CMatrix_log( "CMatrix::CMatrix( CMatrix(%d,%d) )\n", other.getRows(), cols );
		assign( other );
	}

	/// destructor
	~CMatrix()
	{
		#ifdef _DEBUG
		printf( "destructor()\n" );
		#endif // _DEBUG

		clear();
	}


	// Compare me to another CMatrix,
	// test for equal row- and col-count first,
	// if true, then check element-wise for equality until false
	bool operator==(const CMatrix& other)
	{
		#ifdef _DEBUG
		printf( "operator== ()\n");
		#endif // _DEBUG

		if (*this == other)
			return false;   // !dangerous! if somebody turns this equality to true

		const u32 r0 = getRows();
		const u32 c0 = getCols();
		const u32 r1 = other.getRows();
		const u32 c1 = other.getCols();

		// test equality for number of rows and columns first
		if (r0!=r1) return false;
		if (c0!=c1)	return false;

		// then test for equality element-wise
		for (u32 m=0; m<r0; m++)
		{
			for (u32 n=0; n<c0; n++)
			{
				if ( !core::equals( Data[m][n], other.getElement(m,n) ) )
					return false;
			}
		}

		// if really all same return true,
		return true;
	}

	/// inequality operator
	bool operator!=(const CMatrix& other)
	{
		return ( *this == other );
	}


	/// translation operator '+'
	CMatrix& operator+ ( const ElementType& value )
	{
		for (u32 y=0; y<Rows; y++)
		{
			for (u32 x=0; x<Cols; x++)
			{
				Data[y][x] = Data[y][x] + value;
			}
		}

		return *this;
	}

	/// '+' operator overload
	CMatrix& operator+= ( const CMatrix& other )
	{
		if ( *this == other )
			return *this;

		for (u32 y=0; y<Rows; y++)
		{
			for (u32 x=0; x<Cols; x++)
			{
				Data[y][x] = Data[y][x] + other.getElement(y,x);
			}
		}

		return *this;
	}

	/// translation operator '-'
	CMatrix& operator- ( const ElementType& value )
	{
		for (u32 y=0; y<Rows; y++)
		{
			for (u32 x=0; x<Cols; x++)
			{
				Data[y][x] = Data[y][x] - value;
			}
		}
		return *this;
	}

	/// '-' operator overload
	CMatrix& operator-= ( const CMatrix& other )
	{
		if ( *this == other )
			return *this;

		for (u32 y=0; y<Rows; y++)
		{
			for (u32 x=0; x<Cols; x++)
			{
				Data[y][x] = Data[y][x] - other.getElement(y,x);
			}
		}

		return *this;
	}

	/// scale operator '*'
	CMatrix& operator* ( const ElementType& value )
	{
		for (u32 y=0; y<Rows; y++)
		{
			for (u32 x=0; x<Cols; x++)
			{
				Data[y][x] = Data[y][x] *value;
			}
		}
		return *this;
	}

	/// scale operator '/'
	CMatrix& operator/ ( const ElementType& value )
	{
		if (!core::equals( value, NullValue ))
		{
			const ElementType value_inv_factor = core::reciprocal( value );

			for (u32 y=0; y<Rows; y++)
			{
				for (u32 x=0; x<Cols; x++)
				{
					Data[y][x] = Data[y][x] * value_inv_factor;
				}
			}
		}

		return *this;
	}

	/// added 11.09.2013
	/// for use with audio-animator
	/// @remarks should be slow, maybe this solution is insufficient
	/// @todo compare speed with array of arrays
	/// since there, only pointers have to be swapped/exchanged, and no data

	video::IImage* createImage( ) const
	{
		#ifdef _DEBUG
		printf( "createImage()\n" );
		#endif // _DEBUG

		core::dimension2du img_size( Cols, Rows );
		video::CImage* img = new video::CImage( video::ECF_A8R8G8B8, img_size);
		if (!img)
			return 0;

		img->fill( 0xffffffff );

		const core::vector2df mm = getMinMax();
		const ElementType height = mm.Y - mm.X;

		for (u32 y = 0; y < core::min_<u32>(Rows, img->getDimension().Height); y++)
		{
			for (u32 x = 0; x < core::min_<u32>(Cols, img->getDimension().Width); x++)
			{
				ElementType value = Data[y][x];
				value -= mm.X;
				value /= height;
				value = core::clamp<ElementType>( value, 0.0f, 1.0f );
				video::SColorf color( value, value, value, 1.0f );
				img->setPixel( x, y, color.toSColor() );
			}
		}

		return img;
	}

	//video::IImage* createHeightMap( ) const
	//{
	//    #ifdef _DEBUG
	//    printf( "createHeightMap()\n" );
	//    #endif // _DEBUG
	//
	//    core::dimension2du img_size( Cols, Rows );
	//    video::CImage* img = new video::CImage( video::ECF_A8R8G8B8, img_size);
	//    if (!img)
	//        return 0;
	//
	//    img->fill( 0xffffffff );
	//
	//    const core::vector2df mm = getMinMax();
	//    const ElementType height = mm.Y - mm.X;
	//
	//    for (u32 y = 0; y < core::min_<u32>(Rows, img->getDimension().Height); y++)
	//    {
	//        for (u32 x = 0; x < core::min_<u32>(Cols, img->getDimension().Width); x++)
	//        {
	//            ElementType value = Data[y][x];
	//            value -= mm.X;
	//            value /= height;
	//            value = core::clamp<ElementType>( value, 0.0f, 1.0f );
	//            video::SColorf color( value, value, value, 1.0f );
	//            img->setPixel( x, y, color.toSColor() );
	//        }
	//    }
	//
	//    return img;
	//}

	video::ITexture* createTexture( video::IVideoDriver* driver ) const
	{
		#ifdef _DEBUG
		printf( "createTexture()\n" );
		#endif // _DEBUG

		if (!driver)
			return 0;

		video::IImage* img = createImage();

		video::ITexture* tex = driver->addTexture( "createTexture", img, 0 );

		return tex;
	}

	//
	//		virtual ElementType det() const;
	//		virtual ElementType subMatrix( u32 y, u32 x ) const;
	//		virtual ElementType subDet( u32 y, u32 x ) const;



	void fillRandom(ElementType minRandom, ElementType maxRandom)
	{
		#ifdef _DEBUG
		printf( "fillRandom()\n");
		#endif // _DEBUG

		const s32 diff_ = core::round32( core::abs_<s32>( maxRandom - minRandom ) );

	//    if (diff)
	//    {
			for (u32 y=0; y<Rows; y++)
			{
				for (u32 x=0; x<Cols; x++)
				{
					s32 random_i_ = rand()%diff_;

					ElementType random_f_ = minRandom + (ElementType)random_i_;

					Data[y][x] = random_f_;
				}
			}
	//    }
	}

	void fillRandomNormalized()
	{
		#ifdef _DEBUG
		printf( "fillRandomNormalized()\n");
		#endif // _DEBUG

		for (u32 y=0; y<Rows; y++)
		{
			for (u32 x=0; x<Cols; x++)
			{
				ElementType value= core::reciprocal( (ElementType)(1+rand()) );
				setElement(y,x,value);
			}
		}
	}


//		/// math functions Part I
////		CMatrix& toIdentity();
////		bool isIdentity();
//
//		/// create IdentityMatrix ( all zero but diagonale-elements filled with 1, Einheitsmatrix E / IdentityMatrix I == neutral element of matrix-multiplication )
//		virtual void makeIdentity()
//		{
//			fill( 0.0f );
//
//			u32 min_xy = core::min_<u32>( Rows, Cols );
//
//			for (u32 diagonale=0; diagonale<min_xy; diagonale++)
//			{
//				Data[diagonale][diagonale] = 1.0f;
//			}
//
//			IsIdentity = true;
//		}
//

	bool swapRows( u32 row_a, u32 row_b )
	{
		#ifdef _DEBUG
		printf( "swapRows()\n");
		#endif // _DEBUG

		if ( row_a == row_b )
			return false;

		if ( row_a >= Rows )
			return false;

		if ( row_b >= Rows )
			return false;

		/// save value at target position
		ElementType* row = Data[row_a];

		/// overwrite target position with new value
		Data[row_a] = Data[row_b];

		/// overwrite source position with save row-data
		Data[row_b] = row;

		return true;
	}

	bool shiftRow()
	{
		#ifdef _DEBUG
	//    printf( "shiftRows( 1 )\n" );
		#endif // _DEBUG

		u32 r = 1;
		ElementType** b = new ElementType*[Rows];

		if (!b)
			return false;

		u32 k = 0;
		for (u32 i = r; i<Rows; i++)
		{
			b[i] = Data[k];
			k++;
		}

		k = 0;
		for (u32 i = Rows-r; i<Rows; i++)
		{
			b[k] = Data[i];
			k++;
		}

		for (u32 i = 0; i<Rows; i++)
		{
			Data[i] = b[i];
		}

		delete [] b;

		return true;
	}


	bool shiftRows( s32 rows )
	{
		#ifdef _DEBUG
		printf( "shiftRows( %d )\n", rows);
		#endif // _DEBUG

		if (rows>0)
		{
			for (u32 y=0; y<Rows; y++)
			{
				s32 i = ( rows+(s32)y );

				if (i<0) i += Rows;
				if (i>=(s32)Rows) i -= (s32)Rows;
				//%((s32)Rows);
				u32 k = (u32)i;
	//            k = Rows-1-k;
	//            k = k % Rows;

				/// save value at target position
				ElementType* row = Data[y];

				/// overwrite target position with new value
				Data[y] = Data[k];

				/// overwrite source position with save row-data
				Data[k] = row;
			}
		}
		else
		{
			rows = core::abs_<s32>(rows);

			for (u32 y=0; y<Rows; y++)
			{
				u32 k = ( (u32)rows+y )%Rows ;

				/// save value at target position
				ElementType* row = Data[y];

				/// overwrite target position with new value
				Data[y] = Data[k];

				/// overwrite source position with save row-data
				Data[k] = row;
			}

		}

		return true;
	}

	bool load( const core::stringc& filename ) const
	{
		#ifdef _DEBUG
		printf( "load( %s )\n", filename.c_str() );
		#endif // _DEBUG
		return true;
	}

	bool save( const core::stringc& filename ) const
	{
		#ifdef _DEBUG
		printf( "save( %s )\n", filename.c_str() );
		#endif // _DEBUG

		return true;
	}


	};

} // end namespace core

} // end namespace irr

#endif // MATRIX_H
