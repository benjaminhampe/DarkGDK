#include "DarkGDK_math.h"

namespace irr{



/////////////////////////
////
///
/// MATH 1D
///
////
/////////////////////////

///@brief  dbSignum
s8 dbSign( s8 value )
{
	if (value < 0 )
		return s8(-1);
	else
		return s8(1);
}

///@brief  dbSignum
s16 dbSign( s16 value )
{
	if (value < 0 )
		return s16(-1);
	else
		return s16(1);
}

///@brief  dbSignum
s32 dbSign( s32 value )
{
	if (value < 0 )
		return s32(-1);
	else
		return s32(1);
}

///@brief  dbSignum
s32 dbSign( f32 value )
{
	if (value < 0.0f )
		return s32(-1);
	else
		return s32(1);
}

///@brief  dbSignum
s32 dbSign( f64 value )
{
	if (value < 0.0 )
		return s32(-1);
	else
		return s32(1);
}


///@brief dbWrapValue() - Bring angle to intervall [0°,360°]
f32 dbWrapValue(f32 degrees)
{
	const f32 minValue(0.0f);
	const f32 maxValue(360.0f);
	while (degrees>maxValue)  degrees -= maxValue;
	while (degrees<minValue) degrees += maxValue;
	return degrees;
}

///@brief dbWrapValue() - Bring angle to intervall [0°,360°]
f64 dbWrapValue(f64 degrees)
{
	const f64 minValue(0.0);
	const f64 maxValue(360.0);
	while (degrees>maxValue)  degrees -= maxValue;
	while (degrees<minValue) degrees += maxValue;
	return degrees;
}

///@brief  dbDEG() -
f32 dbDEG(f32 rad)
{
	return core::RADTODEG*rad;
}

///@brief  dbDEG() -
f64 dbDEG(f64 rad)
{
	return core::RADTODEG64*rad;
}

///@brief  dbRAD() -
f32 dbRAD(f32 deg)
{
	return core::DEGTORAD*deg;
}

///@brief  dbRAD() -
f64 dbRAD(f64 deg)
{
	return core::DEGTORAD64*deg;
}

///@brief  dbFloor() -
s32 dbFloor(f32 value)
{
	return core::floor32( value );
}

///@brief  dbFloor() -
s64 dbFloor(f64 value)
{
	return (s64)floor(value);
}

///@brief  dbCeil() -
s32 dbCeil(f32 value)
{
	return core::ceil32( value );
}

///@brief  dbCeil() -
s64 dbCeil(f64 value)
{
	return (s64)ceil(value);
}

///@brief  dbSin() -
f32 dbSin(f32 deg)
{
	return sinf(deg*core::DEGTORAD);
}

///@brief  dbSin() -
f64 dbSin(f64 deg)
{
	return sin(deg*core::DEGTORAD64);
}

///@brief  dbCos() -
f32 dbCos(f32 deg)
{
	return cosf(deg*core::DEGTORAD);
}

///@brief  dbCos() -
f64 dbCos(f64 deg)
{
	return cos(deg*core::DEGTORAD64);
}

///@brief  dbTan() -
f32 dbTan(f32 deg)
{
	return tanf(deg*core::DEGTORAD);
}

///@brief  dbTan() -
f64 dbTan(f64 deg)
{
	return tan(deg*core::DEGTORAD64);
}

///@brief  dbSqrt() -
f32 dbSqrt(f32 value)
{
	return sqrtf(value);
}

///@brief  dbSqrt() -
f64 dbSqrt(f64 value)
{
	return sqrt(value);
}

///@brief  dbAbs() - Absolute positive of a number
s8  dbAbs(s8 value)
{
	return core::abs_<s8>(value);
}

///@brief  dbAbs() - Absolute positive of a number
s16 dbAbs(s16 value)
{
	return core::abs_<s16>(value);
}

///@brief  dbAbs() - Absolute positive of a number
s32 dbAbs(s32 value)
{
	return core::abs_<s32>(value);
}

///@brief  dbAbs() - Absolute positive of a number
s64 dbAbs(s64 value)
{
	return core::abs_<s64>(value);
}

///@brief  dbAbs() - Absolute positive of a number
f32 dbAbs(f32 value)
{
	return core::abs_<f32>(value);
}

///@brief  dbAbs() - Absolute positive of a number
f64 dbAbs(f64 value)
{
	return core::abs_<f64>(value);
}


///@brief  dbRound() - round up at 0.5
f32 dbRound(f32 zahl)
{
	return f32( s32( zahl<0.0f ? zahl-0.5f : zahl+0.5f ) );
}

///@brief  dbRound() - round up at 0.5
f64 dbRound(f64 zahl)
{
	return f64( s32( zahl<0.0 ? zahl-0.5 : zahl+0.5 ) );
}

///@brief  dbRound() - round up at 0.5
f64 dbRound(f64 zahl, s32 stellen)
{
	f64 v[] = { 1, 1e1, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8 };
	return (f64)dbFloor(zahl * v[stellen] + 0.5) / v[stellen];
}

///@brief  getNextPowerOfTwo()
s32 dbNextPowerOfTwo(s32 zahl)
{
	if (zahl<=0) return 128;
	s32 i=0;
	while (zahl > (2<<i))
	{
		i++;
	}
	return (2<<i);
}

///@brief  dbIntPart() - Returns integer part of a 32bit-float
s32 dbInt( f32 zahl)
{
	return (s32)zahl;
}

///@brief  dbIntPart() - Returns integer part of a 64bit-float
s32 dbInt( f64 zahl)
{
	return (s32)zahl;
}

///@brief  dbFloatPart() - Returns .floating part of a 32bit-float
f32 dbFloat( f32 zahl )
{
	return zahl-(f32)dbInt(zahl);
}

///@brief  dbFloatPart() - Returns .floating part of a 64bit-float
f64 dbFloat( f64 zahl )
{
	return zahl-(f64)dbInt(zahl);
}

/// Split 32bit float to IntPart and FloatPart
// Trennt Vorkomma- und Nachkommateil einer Fließkommazahl in 2 Variablen auf
// !!! Beachte "frac" und "int" haben beide das gleiche Vorzeichen wie "zahl".
// >> fraction = abs(fraction)
void dbSplit( f32 zahl, f32 *integer, f32 *fraction)
{
	*fraction = core::abs_<f32>( modff(zahl,integer) );
}

/// Split 64bit double to IntPart and FloatPart
// Trennt Vorkomma- und Nachkommateil einer Fließkommazahl in 2 Variablen auf
// !!! Beachte "frac" und "int" haben beide das gleiche Vorzeichen wie "zahl".
// >> fraction = abs(fraction)
void dbSplit( f64 zahl, f64 *integer, f64 *fraction)
{
	*fraction = abs( modf(zahl,integer) );
}

} // end namespace irr
