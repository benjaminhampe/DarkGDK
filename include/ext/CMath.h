// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXTENSION_MATH_H__
#define __IRR_EXTENSION_MATH_H__

#include <irrlicht.h>
#include <ctime>
#include <cmath>


namespace irr
{
	///@brief checks if the given coords are over ( on border or inside ) given rectangle
	bool isMouseOver( const core::position2di& pos, const core::recti& target_rect );

	///@brief set Parent Element Text ( i.e. the caption of a parent's window title )
	bool setText( gui::IGUIElement* element, const core::stringw& text );

	///@brief setVisible(false) to all SceneNodes
	bool hideAll( scene::ISceneManager* smgr );

	///@brief setVisible(true) to all SceneNodes
	bool showAll( scene::ISceneManager* smgr );

namespace core
{
	///@brief buildProjectionMatrixOrthoLH with 6 params, not 4 as irrlicht only does
	matrix4 buildProjectionMatrixOrthoLH( f32 left, f32 right, f32 bottom, f32 top, f32 zNear = 0.1f, f32 zFar = 1000.0f );

	///@brief create a recti from position2di and dimension2du
	inline recti makeRect( s32 x, s32 y, u32 w, u32 h)
	{
		return recti( position2di(x,y), dimension2du(w,h) );
	}

	template<class T>	vector2d<T> transformPoint2d(
		const vector2d<f32>& v_src,
		const rect<f32>& r_src,
		const rect<T>& r_dst )
	{
		vector2d<f32> v;

		// normalize 0..1
		v.X = (v_src.X - r_src.UpperLeftCorner.X) / r_src.getWidth();
		v.Y = (v_src.Y - r_src.UpperLeftCorner.Y) / r_src.getHeight();

		// scale
		v.X *= r_dst.getWidth();
		v.Y *= r_dst.getHeight();

		//translate
		v.X += r_dst.UpperLeftCorner.X;
		v.Y += r_dst.UpperLeftCorner.Y;

		return vector2d<T>(v.X,v.Y);
	}

//	typedef transformPoint2d<s32> transformPoint2di;
//
//	typedef transformPoint2d<f32> transformPoint2df;


//! Math-Extensions collected in Math Class
class Math
{
public:
	//! @brief Init class wide used randomizer
	//! @return nothing
	static void Randomize();

	//! @brief getRandomNumber(u32 max_random_number)
	//! @return random unsigned 32bit number
	static u32 Random(u32 seed);



	//! @brief abs<T>(T value)
	//! @return Absolute of a value of type |T|
	template <class T> T abs(T value)
	{
		if (value < T(0))
			return T(-1)*value;
		else
			return value;
	}

	//! @brief WrapAngle<T>(T value)
	//! @return Normalized angle in degrees in range [0,360]
	template<class T> static T WrapAngle(T x)
	{
		while (x < (T)0)
			x += (T)360;
		while (x > (T)360 || equals( x, (T)360) )
			x -= (T)360;

		//	x = fmod( (f64)x, 360.0);
		//	if (sizeof(x)<8)
		//	{
		//		x = fmodf(x,360);
		//	}
		//	else
		//	{
		//		x = fmod(x,360);
		//	}

		return x;
	}

	//! @brief WrapAngle180<T>(T value)
	//! @return Normalized angle in degrees in range [0,360]
	template<class T> static T WrapAngle180(T x)
	{
		while (x < -(T)180)
		{
			x += (T)360;
		}

		while (x > (T)180 || equals( x, (T)180))
		{
			x -= (T)360;
		}

		//		x = fmod(x + (T)180,(T)360);
		//		if (x < (T)0)
		//			x += (T)360;
		//
		return x;
	}

	//! @brief IntPart<T>( T realNumber ) == simple and safe cast to integer ( loosing the after comma part of realnumber )
	//! @return integer-part of a real-number
	template<class T> static s32 IntPart( T realNumber )
	{
		return static_cast<s32>(realNumber);
	}

	//! @brief FloatPart<T>( T realNumber ) == difference of original number with integer-part so rest is 0.f32-part
	//! @return f32ingpoint-part of a realnumber
	template<class T> static T FloatPart( T realNumber )
	{
		return realNumber-(T)IntPart(realNumber);
	}

	//! @brief RoundMedian( f32 realNumber )
	//! @return Round = int( f32 realnumber + 0.5f ) -> "dirty round" = einfacher cast auf s32 ( long signed integer ) bei vorheriger Addition von 0.5
	static f32 Round(f32 zahl);

	//! @brief RoundMedian( f64 realNumber )
	//! @return Round = int( f64 realnumber + 0.5 ) -> "dirty round" = einfacher cast auf s32 ( long signed integer ) bei vorheriger Addition von 0.5
	static f64 Round(f64 zahl);

	//! @brief Round( f32 realNumber, s32 stellen ) -> Rundet auf Anzahl Stellen nach dem Komma, Laufzeitoptimiert, 2.Parameter nur von 0 bis 8!!!, sonst Absturz!!!
	//! @return Round = int( (realNumber + 0.5f)*10^stellen ) / 10^stellen
	static f32 Round(f32 zahl, s32 stellen);

	//! @brief Round( f64 realnumber, s32 stellen )  -> Rundet auf Anzahl Stellen nach dem Komma, Laufzeitoptimiert, 2.Parameter nur von 0 bis 8!!!, sonst Absturz!!!
	//! @return Round = int( (realNumber + 0.5f)*10^stellen ) / 10^stellen
	static f64 Round(f64 zahl, s32 stellen);

	//! @brief Split<FloatType,IntType>( FloatType realNumber, FloatType& f_part, IntType& i_part )
	//! @return Split<FloatType,IntType>( FloatType realNumber, FloatType& f_part, IntType& i_part )
	template<class FloatType,class IntType> static void Split( const FloatType& realNumber, FloatType& f_part, IntType& i_part )
	{
		f_part = (FloatType)abs( modf( realNumber, *i_part ) );
	}

	//#ifdef USE_32BIT_FLOATS
	//	void Math::Split( f32 r, f32* i, f32* f)
	//	{
	//		*f = fabs( fmodf( r,*i ) );
	//	}
	//#else
	//	void Math::Split( f64 r, f64* i, f64* f)
	//	{
	//		*f = Math::abs<f64>( modf( r,i ) );
	//	}
	//#endif

	//! @brief integer exponential number
	//! @return integer exponential number
	static s32 s32_pow(s32 x, s32 p);

	//! @brief get the signum/vorzeichen of a realnumber
	//! @return get the signum/vorzeichen of a realnumber
	static s32 sign( f32 realnumber );

	//! @brief get the signum/vorzeichen of a realnumber
	//! @return get the signum/vorzeichen of a realnumber
	static s32 sign( f64 realnumber );

	//! @brief get next nearest power of two [1]
	//! @return get next nearest power of two [1]
	static u32 _nextPow2_loop( u32 n );

	//! @brief get next nearest power of two [2]
	//! @return get next nearest power of two [2]
	static u32 _next_power_of_2( u32 value );

	//! @brief get next nearest power of two [1]
	//! @return get next nearest power of two [1]
	//u32 _nextPow2( u32 x );

	//! @brief get next nearest power of two [1]
	//! @return get next nearest power of two [1]
	//u32 _nextPow2_IEEE( u32 n );

	//! @brief get minimum and maximum value inside array container per reference
	//! @return get next nearest power of two [1]
	/// <!-- MIN / MAX -->
	template <class T> void getMinMax( const array<T>& data, T& out_min, T& out_max )
	{
		out_min = (T)DBL_MAX;
		out_max = (T)DBL_MIN;

		const u32& count = data.size();

		if (count == 0) return;

		for (u32 i=0; i<count; i++)
		{
			const T& value = data[i];

			if (out_min > value)
			{
				out_min = value;
			}

			if (out_max < value)
			{
				out_max = value;
			}
		}
	}

	//! @brief ggT<T>(T a, T b)
	//! @return greatest common divisor gcd(a,b)
	template <class T> static T ggT( T a, T b)
	{
		T tmp;
		while (b!=0)
		{
			tmp=a%b;
			a=b;
			b=tmp;
		};

		return a;
	}

	//! @brief ggT2<T>(T a, T b)
	//! @return greatest common divisor gcd(a,b)
	template <class T> static T ggT2( T a,T b)
	{
		for(;;)
		{
			if(a==0) return b;
			b%=a;
			if(b==0) return a;
			a%=b;
		}
	}

	/// @page Statistics

	/// @brief Statistics - Arithmetic Average
	/// @return Statistics - Arithmetic Average ( arithmetisches Mittel )
	template <class T>  T x_arithm( const array<T>& data ) const
	{
		T result = (T)0;

		const u32& count = data.size();

		if (count == 0) return result;

		const T t_inv = (T)reciprocal( (f64)count );

		for (u32 i=0; i<count; i++)
		{
			result += data[i];
		}

		result *= t_inv; // factor 1/N

		return result;
	}

	/// @brief Statistics - Geometric Average
	/// @return Statistics - Geometric Average ( geometrisches Mittel )
	template <class T>  T x_geom( const array<T>& data ) const
	{
		f64 result = 0.0;

		const u32& count = data.size();

		if (count == 0) return (T)result;

		// Produkt aller Elemente
		for (u32 i=0; i<count; i++)
		{
			result *= (f64)data[i];
		}

		// n-te Wurzel
		result = pow( result, 1.0/(f64)count );

		return (T)result;
	}

	/// @brief Statistics - Harmonic Average
	/// @return Statistics - Harmonic Average ( harmonisches Mittel )
	template <class T>  T x_harm( const array<T>& data ) const
	{
		f64 result = 0.0;

		const u32& count = data.size();

		if (count == 0) return (T)result;

		for (u32 i=0; i<count; i++)
		{
			result += 1.0/(f64)data[i];
		}

		result = (f64)count / result;

		return (T)result;
	}

	/// @brief Statistics - Quadratic Average
	/// @return Statistics - Quadratic Average ( quadratisches Mittel )
	template <class T>  T x_quad( const array<T>& data ) const
	{
		f64 result = 0.0;

		const u32& count = data.size();

		if (count == 0) return (T)result;

		for (u32 i=0; i<count; i++)
		{
			result += (f64)(data[i]*data[i]);
		}

		result /= (f64)count;

		result = core::squareroot( result );

		return (T)result;
	}

	/// @brief Statistics - Cubic Average
	/// @return Statistics - Cubic Average ( kubisches Mittel )
	template <class T>  T x_cubic( const array<T>& data ) const
	{
		f64 result = 0.0;

		const u32& count = data.size();

		if (count == 0) return (T)result;

		for (u32 i=0; i<count; i++)
		{
			T value = data[i];
			value *= (value*value);
			result += value;
		}

		result /= (f64)count;

		result = pow( result, 1.0/3.0 );

		return (T)result;
	}
	/// @brief Statistics - Function Median
	/// @return Statistics - Function Median ( Mittelwert einer Funktion )
	template <class T>  T getMedian( const array<T>& data ) const
	{
		T result = (T)0;

		const u32& count = data.size();

		if (count == 0) return result;

		T t_min = (T)DBL_MAX;
		T t_max = (T)DBL_MIN;

		for (u32 i=0; i<count; i++)
		{
			T value = data[i];
			if (t_min > value)
			{	t_min = value;
			}
			if (t_max < value)
			{	t_max = value;
			}
		}

		const T t_range = t_max - t_min;
		const T t_range_inv = (T)reciprocal( (f64)(t_range) );
		const T t_delta = t_range / count;

		for (u32 i=0; i<count; i++)
		{
			T value = data[i] * t_delta;
			result += value;
		}

		result *= t_range_inv;

		return result;
	}

	/// @brief Statistics - Standard Deviation
	/// @return Statistics - Standard Deviation ( Standardabweichung )
	template <class T>  T getStdDeviation( const array<T>& data ) const
	{
		f64 result = 0.0;

		const u32& count = data.size();

		if (count == 0) return (T)result;

		f64 average = (f64)x_arithm( data );

		for (u32 i=0; i<count; i++)
		{
			f64 value = (f64)data[i];
			value -= average;
			value *= value;
			result += value;
		}

		if (count>1)
			result /= (f64)(count-1);

		result = core::squareroot( result );

		return (T)result;
	}

	/// @brief Statistics - Standard Error
	/// @return Statistics - Standard Error ( mittlerer quadratischer Fehler == Breite der Streuung des Mittelwertes )
	template <class T>  T getStdError( const array<T>& data ) const
	{
		f64 result = 0.0;

		const u32& count = data.size();

		if (count == 0) return (T)result;

		result = getStdDeviation( data );

		result /= core::squareroot( (f64)count );

		return (T)result;
	}

	/// @brief Statistics - analyzeData<T>( array<T> ) --> Test given data-set with all known functions
	/// @return Statistics - analyzeData<T>( array<T> ) --> Analyze Data and print to string
	template <class T>  stringc analyzeData( const array<T>& data, bool bPrintDataToo = false ) const
	{
		stringc txt("Statistical Analysis of LinearData (array) with ");

		const u32& count = data.size();

		txt += count;
		txt += " elements:";

		if (count == 0)
		{
			txt += " nothing todo.";
			return txt;
		}

		txt += "\n";

		T v0,v1; getMinMax( data, v0, v1);
		T v3 = x_arithm( data );
		T v4 = x_geom( data );
		T v5 = x_harm( data );
		T v6 = x_quad( data );
		T v7 = x_cubic( data );
		T v8 = getStdDeviation( data );
		T v9 = getStdError( data );

		txt += "Minimum = "; txt += v0; txt += "\n";
		txt += "Maximum = "; txt += v1; txt += "\n";
		txt += "Range = "; txt += v1-v0; txt += "\n";
		txt += "x_arithm = "; txt += v3; txt += "\n";
		txt += "x_geom = "; txt += v4; txt += "\n";
		txt += "x_harm = "; txt += v5; txt += "\n";
		txt += "x_quad = "; txt += v6; txt += "\n";
		txt += "x_cubic = "; txt += v7; txt += "\n";
		txt += "StdDeviation = "; txt += v8; txt += "\n";
		txt += "StdError = "; txt += v9; txt += "\n";

		if (bPrintDataToo)
		{
			for (u32 i=0; i<count; i++)
			{
				txt += "Data["; txt+=i; txt+="] = "; txt+=data[i]; txt+="\n";
			}
		}
		return txt;
	}

}; // end class

} // end namespace core
} // end namespace irr


	// /// @brief Statistics - Arithmetic Average
	// /// @return Arithmetic Average ( Arithmetisches Mittel )
	// template <class T>  T x_arithm( const T* data, u32 count ) const
	// {
		// T result = (T)0;

		// if (count == 0) return result;

		// const T t_inv = (T)reciprocal( (f64)count );

		// for (u32 i=0; i<count; i++)
		// {
			// result += data[i];
		// }

		// result *= t_inv; // factor 1/N

		// return result;
	// }

	// /// @brief Statistics - Geometric Average
	// /// @return Geometric Average ( geometrisches Mittel )
	// template <class T>  T x_geom( const T* data, u32 count ) const
	// {
		// f64 result = 0.0;

		// if (count == 0) return (T)result;

		// // Produkt aller Elemente
		// for (u32 i=0; i<count; i++)
		// {
			// result *= (f64)data[i];
		// }

		// // n-te Wurzel
		// result = std::pow( result, 1.0/(f64)count );

		// return (T)result;
	// }


	// /// <!-- Harmonic Average ( harmonisches Mittel ) -->
	// template <class T>  T x_harm( const T* data, u32 count ) const
	// {
		// f64 result = 0.0;

		// if (count == 0) return (T)result;

		// for (u32 i=0; i<count; i++)
		// {
			// result += 1.0/(f64)data[i];
		// }

		// result = (f64)count / result;

		// return (T)result;
	// }


	// /// <!-- Quadratic Average ( quadratisches Mittel ) -->
	// template <class T>  T x_quad( const T* data, u32 count ) const
	// {
		// f64 result = 0.0;

		// if (count == 0) return (T)result;

		// for (u32 i=0; i<count; i++)
		// {
			// result += (f64)(data[i]*data[i]);
		// }

		// result /= (f64)count;

		// result = std::sqrt( result );

		// return (T)result;
	// }


	// /// <!-- Cubic Average ( kubisches Mittel ) -->
	// template <class T>  T x_cubic( const T* data, u32 count ) const
	// {
		// f64 result = 0.0;

		// if (count == 0) return (T)result;

		// for (u32 i=0; i<count; i++)
		// {
			// T value = data[i];
			// value *= (value*value);
			// result += value;
		// }

		// result /= (f64)count;

		// result = std::pow( result, 1.0/3.0 );

		// return (T)result;
	// }

	// /// <!-- MEDIAN ( Mittelwert einer Funktion ) -->
	// template <class T>  T getMedian( const T* data, u32 count ) const
	// {
		// T result = (T)0;
		// if (count == 0) return result;

		// T t_min = (T)DBL_MAX;
		// T t_max = (T)DBL_MIN;

		// for (u32 i=0; i<count; i++)
		// {
			// T value = data[i];
			// if (t_min > value)
			// {	t_min = value;
			// }
			// if (t_max < value)
			// {	t_max = value;
			// }
		// }

		// const T t_range = t_max - t_min;
		// const T t_range_inv = (T)reciprocal( (f64)(t_range) );
		// const T t_delta = t_range / count;

		// for (u32 i=0; i<count; i++)
		// {
			// T value = data[i] * t_delta;
			// result += value;
		// }

		// result *= t_range_inv;

		// return result;
	// }

	// /// <!-- Standard Deviation ( Standardabweichung ) -->
	// template <class T>  T getStdDeviation( const T* data, u32 count ) const
	// {
		// f64 result = 0.0;

		// if (count == 0) return (T)result;

		// f64 average = (f64)x_arithm( data );

		// for (u32 i=0; i<count; i++)
		// {
			// f64 value = (f64)data[i];
			// value -= average;
			// value *= value;
			// result += value;
		// }

		// if (count>1)
			// result /= (f64)(count-1);

		// result = std::sqrt( result );

		// return (T)result;
	// }

	// /// <!-- Average quadratic error ( mittlerer quadrat. Fehler == Breite der Streuung des Mittelwertes ) -->
	// template <class T>  T getStdError( const T* data, u32 count ) const
	// {
		// f64 result = 0.0;

		// if (count == 0) return (T)result;

		// result = getStdDeviation( data, count );

		// result /= std::sqrt( (f64)count );

		// return (T)result;
	// }


#endif // __IRR_EXTENSION_MATH_H__
