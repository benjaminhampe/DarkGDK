#ifndef __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_MATH_H__
#define __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_MATH_H__

#include <irrlicht.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#ifndef SAVE_DROP
	#define SAVE_DROP(x) {if((x)){(x)->drop();(x)=0;}}
#endif

#ifndef SAVE_DELETE
	#define SAVE_DELETE(x) {if((x)){delete (x); (x)=0;}}
#endif

namespace irr
{
	const f64 INV64_3 = 1.0/3.0;
	const f64 INV64_6 = 1.0/6.0;
	const f64 INV64_12 = 1.0/12.0;
	const f64 INV64_24 = 1.0/24.0;
	const f64 INV64_60 = 1.0/60.0;
	const f64 INV64_288 = 1.0/288.0;
	const f64 INV64_360 = 1.0/360.0;
	const f64 INV64_1440 = 1.0/1440.0;
	const f64 INV64_3600 = 1.0/3600.0;
	const f64 INV64_86400 = 1.0/86400.0;
	const f64 DIN_A0 = 841.0/1189.0;
	const f64 DIN_A1 = 594.0/841.0;
	const f64 DIN_A2 = 420.0/594.0;
	const f64 DIN_A3 = 297.0/420.0;
	const f64 DIN_A4 = 210.0/297.0;
	const f64 DIN_A5 = 148.0/210.0;
	const f64 DIN_A6 = 105.0/148.0;
	const f64 DIN_A7 = 74.0/105.0;
	const f64 DIN_A8 = 52.0/74.0;

	/////////////////////////
	////
	///
	/// MATH 1D
	///
	////
	/////////////////////////

	//template <class T> T sign(T value)
	//{
	//	if (value < T(0))
	//		return T(-1);
	//	else
	//		return T(1);
	//}
	//

	///@brief  isPowerOfTwo<T>
	template <class T>
	inline bool isSquare(const core::dimension2d<T>& v)
	{
			if (v.X != v.Y)
					return false;
			return true;
	}

	///@brief  isPowerOfTwo<T>
	// Quelle: http://en.wikipedia.org/wiki/Power_of_two
	template <class T>
	inline bool isPowerOfTwo(const T& zahl)
	{
			if ((zahl & (zahl-1)) == 0)
					return true;
			return false;
	}

	///@brief  isPowerOfTwo<T>
	template <class T>
	inline bool isPowerOfTwo(const core::dimension2d<T>& v)
	{
			return (isPowerOfTwo(v.Width) && isPowerOfTwo(v.Height));
	}

	///@brief  getPreviousPowerOfTwo<T>
	template <class T>
	inline T getPreviousPowerOfTwo(const T& zahl)
	{
			if (zahl<=T(2)) return T(2);
			T n=2;
			while (n<=zahl)
			{
					n<<1;
			}
			n>>1;
			return n;
	}

	///@brief  dbMin<T>
	template <class T>
	inline T dbMin(T a, T b)
	{
		if (a>b)
			return b;
		return a;
	}

	///@brief  dbMax<T>
	template <class T>
	inline T dbMax(T a, T b)
	{
		if (a<b)
			return b;
		return a;
	}

	///@brief  dbSignum
	s8 dbSign( s8 value );

	///@brief  dbSignum
	s16 dbSign( s16 value );

	///@brief  dbSignum
	s32 dbSign( s32 value );

	///@brief  dbSignum
	s32 dbSign( f32 value );

	///@brief  dbSignum
	s32 dbSign( f64 value );


	///@brief  dbWrapValue() - Bringt Winkel auf Intervall [0°,360°]
	f32 dbWrapValue(f32 degrees);

	///@brief  dbWrapValue() - Bringt Winkel auf Intervall [0°,360°]
	f64 dbWrapValue(f64 degrees);

	///@brief  dbCurveValue()
	f32 dbCurveValue(f32 degrees);

	///@brief  dbCurveValue()
	f64 dbCurveValue(f64 degrees);

	///@brief  dbDEG()
	f32 dbDEG(f32 rad);

	///@brief  dbDEG()
	f64 dbDEG(f64 rad);

	///@brief  dbRAD()
	f32 dbRAD(f32 deg);

	///@brief  dbRAD()
	f64 dbRAD(f64 deg);

	//inline u32 ftoi(f32 zahl)		{	u32 back = (*((u32*)&zahl));	return back;	}
	//inline u64 ftoi(f64 zahl)		{	u64 back = (*((u64*)&zahl));	return back;	}
	//inline f32 itof(u32 zahl)		{	return (f32)(*((u32*)&zahl));	}
	//inline f64 itof(u64 zahl)		{	return (f64)(*((u64*)&zahl));	}

	///@brief  dbFloor()
	s32 dbFloor(f32 value);

	///@brief  dbFloor()
	s64 dbFloor(f64 value);

	///@brief  dbCeil()
	s32 dbCeil(f32 value);

	///@brief  dbCeil()
	s64 dbCeil(f64 value);

	///@brief  dbSin()
	f32 dbSin(f32 deg);

	///@brief  dbSin()
	f64 dbSin(f64 deg);

	///@brief  dbCos()
	f32 dbCos(f32 deg);

	///@brief  dbCos()
	f64 dbCos(f64 deg);

	///@brief  dbTan()
	f32 dbTan(f32 deg);

	///@brief  dbTan()
	f64 dbTan(f64 deg);

	///@brief  dbSqrt()
	f32 dbSqrt(f32 value);

	///@brief  dbSqrt()
	f64 dbSqrt(f64 value);

	///@brief  dbABS<T> - Template function for abs() to any type
	// Urheber dieser Funktionen ist Benjamin Hampe, bitte beachten Sie bei Verwendung die Lizenzbedingungen.
	//template <class T> T dbABS(T value)
	//{
	//	if (value < T(0))
	//		return T(-1)*value;
	//	else
	//		return value;
	//}

	///@brief  dbAbs()
	s8  dbAbs(s8 value);

	///@brief  dbAbs()
	s16 dbAbs(s16 value);

	///@brief  dbAbs()
	s32 dbAbs(s32 value);

	///@brief  dbAbs()
	s64 dbAbs(s64 value);

	///@brief  dbAbs()
	f32 dbAbs(f32 value);

	///@brief  dbAbs()
	f64 dbAbs(f64 value);

	///@brief  dbInt() - Returns integer-part of a 32bit-float
	s32 dbInt( f32 zahl);

	///@brief  dbInt() - Returns integer-part of a 64bit-float
	s32 dbInt( f64 zahl);

	///@brief  dbFloor() - Returns floating-part of a 32bit-float
	f32 dbFloat( f32 zahl );

	///@brief  dbFloor() - Returns floating-part of a 64bit-float
	f64 dbFloat( f64 zahl );

	///@brief  dbSplit() - Split 32bit float to IntPart and FloatPart
	// Trennt Vorkomma- und Nachkommateil einer Fließkommazahl in 2 Variablen auf
	// !!! Beachte "frac" und "int" haben beide das gleiche Vorzeichen wie "zahl".
	// >> fraction = abs(fraction)
	void dbSplit( f32 zahl, f32 *integer, f32 *fraction);

	///@brief  dbSplit() - Split 64bit double to IntPart and FloatPart
	// Trennt Vorkomma- und Nachkommateil einer Fließkommazahl in 2 Variablen auf
	// !!! Beachte "frac" und "int" haben beide das gleiche Vorzeichen wie "zahl".
	// >> fraction = abs(fraction)
	void dbSplit( f64 zahl, f64 *integer, f64 *fraction);

	///@brief  dbRound() - Round up at 0.5
	f32 dbRound(f32 zahl);

	///@brief  dbRound() - Round up at 0.5
	f64 dbRound(f64 zahl);

	///@brief  dbRound() - Round up at 0.5
	f64 dbRound(f64 zahl, s32 stellen);

	///@brief  dbRound() - Round up at 0.5
	s32 dbNextPowerOfTwo(s32 zahl);


	//! @brief class dbSinCosPairf
	struct dbSinCosPairf // point on the unit-circle
	{
		f32 Sin;
		f32 Cos;
	};

	//! sinus + cosinus in one calculation as 32bit-floats
	inline void dbAsmSinCos( f32 radians, f32& refSinusOut, f32& refCosinusOut )
	{
		asm(".intel_syntax noprefix");
		asm("fld radians");
		asm("fsincos");
		asm("mov ecx,[refSinusOut]");
		asm("mov edx,[refCosinusOut]");
		asm("fstp DWORD PTR[ecx]");
		asm("fstp DWORD PTR[edx]");
	}

	//! @brief class dbSinCosTablef
	class dbSinCosTablef : public IReferenceCounted
	{
	public:
		explicit dbSinCosTablef( u32 count = 36, f32 r_start = 0.f, f32 r_end = 2.0f*core::PI )
		{
			u32 c = (count>0)?count:1;
			m_count = c;
			m_table = new dbSinCosPairf[c];
			m_start = r_start;
			m_end = r_end;
			m_step = (m_end - m_start) * core::reciprocal( (f32)c );

			f32 angle = m_start;

			for (u32 i=0; i<c; i++)
			{
				dbAsmSinCos( (f32)angle, m_table[i].Sin, m_table[i].Cos );

				angle += m_step;
			}
		}

		~dbSinCosTablef()
		{
			if (m_table)
				delete [] m_table;
		}

		dbSinCosPairf& operator[] (u32 index)
		{
			if (index>=m_count)
				index = index%m_count;
			return m_table[index];
		}

		const dbSinCosPairf& operator[] (u32 index) const
		{
			if (index>=m_count)
				index = index%m_count;

			return m_table[index];
		}

		const f32& getAngleStepRad() const { return m_step; }

		const f32& getAngleStartRad() const { return m_start; }

		const f32& getAngleEndRad() const { return m_end; }

	private:
		u32 m_count;
		dbSinCosPairf* m_table;

		f32 m_step;
		f32 m_start;
		f32 m_end;

	}; // end class TSinTable

} // end namespace irr

#endif // __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_H__
