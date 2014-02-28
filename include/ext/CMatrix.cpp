#include <CMatrix.h>

namespace irr
{
namespace core
{

/// Print me to string
//core::stringc CMatrix::toString() const
//{
//    // printf( "CMatrix::toString()\n" );
//    core::stringc s("CMatrix<f32>("); s+=Rows; s+=","; s+=Cols; s+=",";
//    if (Name.size()>0)
//    {
//        s+=Name;
//        s+=",";
//    }
//    s+=") = { \n";
//
//    if (Data)
//    {
//        for (u32 y=0; y<Rows; y++)
//        {
//            s+="\t{\t";
//            for (u32 x=0; x<Cols; x++)
//            {
//                s+= core::floor32( Data[y][x] );
//                if (x<Cols-1)
//                {
//                    s+=" ";
//                }
//            }
//            s+="\t}";
//            if (y<Rows-1)
//            {
//                s+=",";
//            }
//            s+="\n";
//        }
//    }
//    s+="};\n";
//
//    return s;
//}
//
///// Print me to stream
//void CMatrix::print( FILE* out ) const
//{
//    if (!out)
//        return;
//
//    // fprintf( out, "CMatrix::print()\n" );
//    fprintf( out, "%s\n", toString().c_str() );
//}
//
///// value contructor
//CMatrix::CMatrix( u32 rows, u32 cols )
//    : Rows(0), Cols(0), Size(0), Data(0), Name("")
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::value_constructor()\n" );
//    #endif
//    resize( rows, cols );
//}
//
///// copy contructor
//CMatrix::CMatrix( const CMatrix& other )
//    : Rows(0), Cols(0), Size(0), Data(0), Name("")
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::copy_constructor()\n" );
//    #endif // _DEBUG
//    assign( other );
//}
//
///// destructor
//CMatrix::~CMatrix()
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::destructor()\n" );
//    #endif // _DEBUG
//
//    clear();
//}
//
//bool CMatrix::resize(u32 rows, u32 cols, bool keepData, bool canShrink )
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::resize(%d,%d)\n", rows, cols );
//    #endif // _DEBUG
//
//    clear();
//
//    Rows = rows;
//    Cols = cols;
//    Size = Rows*Cols;
//    Data = new f32*[Rows];
//
//    /// array of rows / lines
//    for (u32 y=0; y<Rows; y++)
//    {
//        /// each line is an array of floats
//        Data[y]=new f32[Cols];
//
//        /// if line exists
//        if (Data[y])
//        {
//            /// fill with zero
//            for (u32 x=0; x<Cols; x++)
//            {
//                Data[y][x]=0.0f;
//            }
//        }
//    }
//
//    return true;
//}
//
///// destructor
//void CMatrix::clear()
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::clear()\n" );
//    #endif // _DEBUG
//
//    /// delete 2D Array of Floats
//   	if (Data)
//    {
//        /// loop rows
//        for (u32 i=0; i<Rows; i++)
//        {
//            /// delete each row
//            f32* row = Data[i];
//            if (row)
//            {
//                /// delete array
//                delete [] row;
//
//                Data[i] = 0;
//            }
//        }
//
//        /// delete array of pointer to arrays
//        delete [] Data;
//        Data = 0;
//    }
//
//    Rows = 0;
//    Cols = 0;
//    Size = 0;
//}
//
///// copy other CMatrix
//CMatrix& CMatrix::assign( const CMatrix& other )
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::assign()\n" );
//    #endif // _DEBUG
//
//    clear();
//    Rows = other.getRows();
//    Cols = other.getCols();
//    Size = other.getSize();
//    Name = other.getName();
//
//    resize( Rows, Cols );
//
//    for (u32 y=0; y<Rows; y++)
//    {
//        for (u32 x=0; x<Cols; x++)
//        {
//            Data[y][x] = other.getElement(y,x);
//        }
//    }
//    return *this;
//}
//
///// copy this function
//CMatrix CMatrix::clone() const
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::clone()\n" );
//    #endif // _DEBUG
//
//    return CMatrix( *this );
//}
//
////! Get Minimum and Maximum value inside Matrix-Data
//core::vector2df CMatrix::getMinMax() const
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::getMinMax()\n" );
//    #endif // _DEBUG
//
//	core::vector2df result( 0,0 );
//
//    if (!Data)
//        return result;
//
//    result = core::vector2df( FLT_MAX, FLT_MIN );
//
//	for (u32 y=0; y<Rows; y++)
//	{
//        for (u32 x=0; x<Cols; x++)
//        {
//            const f32& value = Data[y][x];
//            if ( result.X > value ) result.X = value;
//            if ( result.Y < value ) result.Y = value;
//        }
//	}
//
//	return result;
//}
//
//
//void CMatrix::fill(f32 value)
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::fill()\n");
//    #endif // _DEBUG
//
//    if (!Data)
//    {
//        printf( "CMatrix::fill() - No Data !!!\n");
//        return;
//    }
//
//    for (u32 y=0; y<Rows; y++)
//    {
//        for (u32 x=0; x<Cols; x++)
//        {
//            Data[y][x] = value;
//        }
//    }
//}
//
//void CMatrix::fillRandom(f32 minRandom, f32 maxRandom)
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::fillRandom()\n");
//    #endif // _DEBUG
//
//    const s32 diff_ = core::round32( core::abs_<s32>( maxRandom - minRandom ) );
//
////    if (diff)
////    {
//        for (u32 y=0; y<Rows; y++)
//        {
//            for (u32 x=0; x<Cols; x++)
//            {
//                s32 random_i_ = rand()%diff_;
//
//                f32 random_f_ = minRandom + (f32)random_i_;
//
//                Data[y][x] = random_f_;
//            }
//        }
////    }
//}
//
//void CMatrix::fillRandomNormalized()
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::fillRandomNormalized()\n");
//    #endif // _DEBUG
//
//    for (u32 y=0; y<Rows; y++)
//    {
//        for (u32 x=0; x<Cols; x++)
//        {
//            f32 value= core::reciprocal( (f32)(1+rand()) );
//            setElement(y,x,value);
//        }
//    }
//}
//
//
//bool CMatrix::swapRows( u32 row_a, u32 row_b )
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::swapRows()\n");
//    #endif // _DEBUG
//
//    if ( row_a == row_b )
//        return false;
//
//    if ( row_a >= Rows )
//        return false;
//
//    if ( row_b >= Rows )
//        return false;
//
//    /// save value at target position
//    f32* row = Data[row_a];
//
//    /// overwrite target position with new value
//    Data[row_a] = Data[row_b];
//
//    /// overwrite source position with save row-data
//    Data[row_b] = row;
//
//    return true;
//}
//
//bool CMatrix::shiftRow()
//{
//    #ifdef _DEBUG
////    printf( "CMatrix::shiftRows( 1 )\n" );
//    #endif // _DEBUG
//
//    u32 r = 1;
//    f32** b = new f32*[Rows];
//
//    if (!b)
//        return false;
//
//    u32 k = 0;
//    for (u32 i = r; i<Rows; i++)
//    {
//        b[i] = Data[k];
//        k++;
//    }
//
//    k = 0;
//    for (u32 i = Rows-r; i<Rows; i++)
//    {
//        b[k] = Data[i];
//        k++;
//    }
//
//    for (u32 i = 0; i<Rows; i++)
//    {
//        Data[i] = b[i];
//    }
//
//    delete [] b;
//
//    return true;
//}
//
//
//bool CMatrix::shiftRows( s32 rows )
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::shiftRows( %d )\n", rows);
//    #endif // _DEBUG
//
//    if (rows>0)
//    {
//        for (u32 y=0; y<Rows; y++)
//        {
//            s32 i = ( rows+(s32)y );
//
//            if (i<0) i += Rows;
//            if (i>=(s32)Rows) i -= (s32)Rows;
//            //%((s32)Rows);
//            u32 k = (u32)i;
////            k = Rows-1-k;
////            k = k % Rows;
//
//            /// save value at target position
//            f32* row = Data[y];
//
//            /// overwrite target position with new value
//            Data[y] = Data[k];
//
//            /// overwrite source position with save row-data
//            Data[k] = row;
//        }
//    }
//    else
//    {
//        rows = core::abs_<s32>(rows);
//
//        for (u32 y=0; y<Rows; y++)
//        {
//            u32 k = ( (u32)rows+y )%Rows ;
//
//            /// save value at target position
//            f32* row = Data[y];
//
//            /// overwrite target position with new value
//            Data[y] = Data[k];
//
//            /// overwrite source position with save row-data
//            Data[k] = row;
//        }
//
//    }
//
//    return true;
//}
//
///// added 11.09.2013
///// for use with audio-animator
///// @remarks should be slow, maybe this solution is insufficient
///// @todo compare speed with array of arrays
///// since there, only pointers have to be swapped/exchanged, and no data
//
//video::IImage* CMatrix::createImage( ) const
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::createImage()\n" );
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
//    const f32 height = mm.Y - mm.X;
//
//    for (u32 y = 0; y < core::min_<u32>(Rows, img->getDimension().Height); y++)
//    {
//        for (u32 x = 0; x < core::min_<u32>(Cols, img->getDimension().Width); x++)
//        {
//            f32 value = Data[y][x];
//            value -= mm.X;
//            value /= height;
//            value = core::clamp<f32>( value, 0.0f, 1.0f );
//            video::SColorf color( value, value, value, 1.0f );
//            img->setPixel( x, y, color.toSColor() );
//        }
//    }
//
//    return img;
//}
//
////video::IImage* CMatrix::createHeightMap( ) const
////{
////    #ifdef _DEBUG
////    printf( "CMatrix::createHeightMap()\n" );
////    #endif // _DEBUG
////
////    core::dimension2du img_size( Cols, Rows );
////    video::CImage* img = new video::CImage( video::ECF_A8R8G8B8, img_size);
////    if (!img)
////        return 0;
////
////    img->fill( 0xffffffff );
////
////    const core::vector2df mm = getMinMax();
////    const f32 height = mm.Y - mm.X;
////
////    for (u32 y = 0; y < core::min_<u32>(Rows, img->getDimension().Height); y++)
////    {
////        for (u32 x = 0; x < core::min_<u32>(Cols, img->getDimension().Width); x++)
////        {
////            f32 value = Data[y][x];
////            value -= mm.X;
////            value /= height;
////            value = core::clamp<f32>( value, 0.0f, 1.0f );
////            video::SColorf color( value, value, value, 1.0f );
////            img->setPixel( x, y, color.toSColor() );
////        }
////    }
////
////    return img;
////}
//
//video::ITexture* CMatrix::createTexture( video::IVideoDriver* driver ) const
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::createTexture()\n" );
//    #endif // _DEBUG
//
//    if (!driver)
//        return 0;
//
//    video::IImage* img = createImage();
//
//    video::ITexture* tex = driver->addTexture( "CMatrix::createTexture", img, 0 );
//
//    return tex;
//}
//
//
///// copy operator overload
//CMatrix& CMatrix::operator= ( const CMatrix& other )
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::operator= ()\n" );
//    #endif // _DEBUG
//
//    return assign(other);
//}
//
///// secure access to value ( with out-of-bounds check )
//f32 CMatrix::getElement(u32 row, u32 col) const
//{
//    _IRR_DEBUG_BREAK_IF( row < 0 );
//    _IRR_DEBUG_BREAK_IF( col < 0 );
//    _IRR_DEBUG_BREAK_IF( row >= Rows );
//    _IRR_DEBUG_BREAK_IF( col >= Cols );
//    if ((row>=0) && (col>=0) && (row<Rows) && (col<Cols))
//    {
//        return Data[row][col];
//    }
//    else
//    {
//        return 0.0f;
//    }
//}
//
///// secure access to value ( with out-of-bounds check )
//f32 CMatrix::getElement(u32 index) const
//{
//    _IRR_DEBUG_BREAK_IF( index<0 );
//    _IRR_DEBUG_BREAK_IF( index>= this->getSize() );
//    u32 row = index / Cols;
//    u32 col = index - row * Cols;
//    if ((row>=0) && (col>=0) && (row<Rows) && (col<Cols))
//    {
//        return Data[row][col];
//    }
//    else
//    {
//        return 0.0f;
//    }
//}
//
///// secure access to value ( with out-of-bounds check )
//bool CMatrix::setElement(u32 row, u32 col, f32 element)
//{
//    _IRR_DEBUG_BREAK_IF( row < 0 );
//    _IRR_DEBUG_BREAK_IF( col < 0 );
//    _IRR_DEBUG_BREAK_IF( row >= Rows );
//    _IRR_DEBUG_BREAK_IF( col >= Cols );
//    if ((row<Rows) && (col<Cols))
//    {
//        Data[row][col] = element;
//        return true;
//    }
//
//    return false;
//}
//
///// secure access to value ( with out-of-bounds check )
//bool CMatrix::setElement(u32 index, f32 element)
//{
//    _IRR_DEBUG_BREAK_IF( index<0 );
//    _IRR_DEBUG_BREAK_IF( index>= this->getSize() );
//    u32 row = index / Cols;
//    u32 col = index - row * Cols;
//    if ((row>=0) && (col>=0) && (row<Rows) && (col<Cols))
//    {
//        Data[row][col] = element;
//        return true;
//    }
//
//    return false;
//}
//
/////// secure access to value ( with out-of-bounds check )
////const f32& CMatrix::operator() (u32 index) const
////{
////    return Data[ (index<getSize())?index:0 ];
////}
////
/////// secure access to value ( with out-of-bounds check )
////f32& CMatrix::operator() (u32 index)
////{
////    return Data[ (index<getSize())?index:0 ];
////}
////
/////// secure access to value ( with out-of-bounds check )
////const f32& CMatrix::operator() (u32 row, u32 col) const
////{
////    u32 index = row*Cols+col;
////    return Data[ (index<getSize())?index:0 ];
////}
////
/////// secure access to value ( with out-of-bounds check )
////f32& CMatrix::operator() (u32 row, u32 col)
////{
////    u32 index = row*Cols+col;
////    return Data[ (index<getSize())?index:0 ];
////}
//
//
///// '+' operator overload
//CMatrix& CMatrix::operator+= ( const CMatrix& other )
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::operator+= ()\n");
//    #endif // _DEBUG
//
//    if ( *this == other )
//        return *this;
//
//    for (u32 y=0; y<Rows; y++)
//    {
//        for (u32 x=0; x<Cols; x++)
//        {
//            Data[y][x] = Data[y][x] + other.getElement(y,x);
//        }
//    }
//
//    return *this;
//}
//
///// '-' operator overload
//CMatrix& CMatrix::operator-= ( const CMatrix& other )
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::operator-= ()\n");
//    #endif // _DEBUG
//
//    if ( *this == other )
//        return *this;
//
//    for (u32 y=0; y<Rows; y++)
//    {
//        for (u32 x=0; x<Cols; x++)
//        {
//            Data[y][x] = Data[y][x] - other.getElement(y,x);
//        }
//    }
//
//    return *this;
//}
//
//// Compare me to another CMatrix,
//// test for equal row- and col-count first,
//// if true, then check element-wise for equality until false
//bool CMatrix::operator==(const CMatrix& other)
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::operator== ()\n");
//    #endif // _DEBUG
//
//    if (*this == other)
//        return false;   // !dangerous! if somebody turns this equality to true
//
//    const u32 r0 = getRows();
//    const u32 c0 = getCols();
//    const u32 r1 = other.getRows();
//    const u32 c1 = other.getCols();
//
//    // test equality for number of rows and columns first
//    if (r0!=r1) return false;
//    if (c0!=c1)	return false;
//
//    // then test for equality element-wise
//    for (u32 m=0; m<r0; m++)
//    {
//        for (u32 n=0; n<c0; n++)
//        {
//            if ( !core::equals( Data[m][n], other.getElement(m,n) ) )
//                return false;
//        }
//    }
//
//    // if really all same return true,
//    return true;
//}
//
///// inequality operator
//bool CMatrix::operator!=(const CMatrix& other)
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::operator!= ()\n");
//    #endif // _DEBUG
//    return ( *this == other );
//}
//
///// scale operator '/'
//CMatrix& operator/ ( const T& value )
//{
//    const f32 v = (f32)value;
//
//    if (!core::equals( v, 0.0f ))
//    {
//        for (u32 y=0; y<Rows; y++)
//        {
//            for (u32 x=0; x<Cols; x++)
//            {
//                Data[y][x] = Data[y][x] / v;
//            }
//        }
//    }
//
//    return *this;
//}
//
///// translation operator '+'
//template <class T>
//CMatrix& operator+ ( const T& value )
//{
//    for (u32 y=0; y<Rows; y++)
//    {
//        for (u32 x=0; x<Cols; x++)
//        {
//            Data[y][x] = Data[y][x] + (f32)value;
//        }
//    }
//
//    return *this;
//}
//
///// translation operator '-'
//template <class T>
//CMatrix& operator- ( const T& value )
//{
//    for (u32 y=0; y<Rows; y++)
//    {
//        for (u32 x=0; x<Cols; x++)
//        {
//            Data[y][x] = Data[y][x] - (f32)value;
//        }
//    }
//    return *this;
//}
//
//bool CMatrix::load( const core::stringc& filename ) const
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::load( %s )\n", filename.c_str() );
//    #endif // _DEBUG
//
//    return true;
//}
//
//bool CMatrix::save( const core::stringc& filename ) const
//{
//    #ifdef _DEBUG
//    printf( "CMatrix::save( %s )\n", filename.c_str() );
//    #endif // _DEBUG
//
//    return true;
//}

} // end namespace core

} // end namespace irr
