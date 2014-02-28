// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_HAMPE_SINCOS_TABLE_EXTENSIONS_H__
#define __IRR_HAMPE_SINCOS_TABLE_EXTENSIONS_H__

#include <irrlicht.h>

//-S
//-masm=intel
//#include <cstdio>
//asm(".intel_syntax noprefix");

namespace irr
{
namespace core
{

	inline void asmSinCos( f32 radians, f32& refSinusOut, f32& refCosinusOut )
	{
		asm(".intel_syntax noprefix");

		asm("fld radians");

		asm("fsincos");

		asm("mov ecx,[refSinusOut]");

		asm("mov edx,[refCosinusOut]");

		asm("fstp DWORD PTR[ecx]");

		asm("fstp DWORD PTR[edx]");

	} // end function asmSinCos


	//! sinus table
	template <class T>
	class TSinCosTable : public IReferenceCounted
	{
	public:
		struct SinCosPair // point on the unit-circle
		{
			T s;
			T c;
		};

		explicit TSinCosTable( u32 count = 36, T r_start = T(0.0), T r_end = T(2.0f*core::PI) )
		{
			u32 c = (count>0)?count:1;
			m_count = c;
			m_table = new SinCosPair[c];
			m_start = r_start;
			m_end = r_end;
			m_step = (m_end - m_start) / (T)c;

			T angle = m_start;

			for (u32 i=0; i<c; i++)
			{
				if (sizeof(T) < 8)
				{
//					m_table[i].s = sinf( angle );
//					m_table[i].c = cosf( angle );
					asmSinCos( (f32)angle, m_table[i].s, m_table[i].c );
				}
				else
				{
					m_table[i].s = sin( angle );
					m_table[i].c = cos( angle );
				}

				angle += m_step;
			}
		}
		~TSinCosTable() { if (m_table) delete [] m_table; }

		T& operator[] (u32 index) { index = index%m_count; return m_table[index]; }

		const T& operator[] (u32 index) const { index = index%m_count; return m_table[index]; }

		const T& getAngleStepRad() const { return m_step; }

		const T& getAngleStartRad() const { return m_start; }

		const T& getAngleEndRad() const { return m_end; }

	private:
		u32 m_count;
		SinCosPair* m_table;

		T m_step;
		T m_start;
		T m_end;

	}; // end class TSinTable


	//! sinus table
	template <class T>
	class TSinTable : public IReferenceCounted
	{
	public:
		explicit TSinTable( u32 count = 36, T radian_angle_start = T(0.0), T radian_angle_end = 2.0f*core::PI )
		{
			m_count = (count>0)?count:1;
			m_table = new T[m_count];
			m_angle_start = radian_angle_start;
			m_angle_end = radian_angle_end;
			m_angle_step = (m_angle_end - m_angle_start) / m_count;

			for (u32 i=0; i<m_count; i++)
			{
				if (sizeof(T) < 8)
				{	m_table[i] = sinf( m_angle_start + m_angle_step * i ); }
				else
				{	m_table[i] = sin( m_angle_start + m_angle_step * i ); }
			}
		}
		~TSinTable() { if (m_table) delete [] m_table; }

		T& operator[] (u32 index) { return m_table[index%m_count]; }

		const T& operator[] (u32 index) const { return m_table[index%m_count]; }

		const T& getAngleStepRad() const { return m_angle_step; }

		const T& getAngleStartRad() const { return m_angle_start; }

		const T& getAngleEndRad() const { return m_angle_end; }

	private:
		u32 m_count;
		T* m_table;

		T m_angle_step;
		T m_angle_start;
		T m_angle_end;

	}; // end class TSinTable

	//! cosinus table
	template <class T> class TCosTable  : public IReferenceCounted
	{
	public:
		explicit TCosTable( u32 count, T radian_angle_start = T(0), T radian_angle_end = 2.0f*core::PI )
		{
			m_count = (count>0)?count:1;
			m_table = new T[m_count];
			m_angle_start = radian_angle_start;
			m_angle_end = radian_angle_end;
			m_angle_step = (m_angle_end - m_angle_start) / m_count;

			for (u32 i=0; i<m_count; i++)
			{
				if (sizeof(T) < 8)
				{	m_table[i] = cosf( m_angle_start + m_angle_step * i ); }
				else
				{	m_table[i] = cos( m_angle_start + m_angle_step * i ); }
			}
		}
		~TCosTable() { if (m_table) delete [] m_table; }

		T& operator[] (u32 index) { return m_table[index%m_count]; }

		const T& operator[] (u32 index) const { return m_table[index%m_count]; }

		const T& getAngleStepRad() const { return m_angle_step; }

		const T& getAngleStartRad() const { return m_angle_start; }

		const T& getAngleEndRad() const { return m_angle_end; }

	private:
		u32 m_count;
		T* m_table;

		T m_angle_step;
		T m_angle_start;
		T m_angle_end;
	}; // end class TCosTable

	typedef TSinTable<f32> CSinTablef;

	typedef TCosTable<f32> CCosTablef;


//
//int gcd( int a, int b ) {
//    int result ;
//    /* Compute Greatest Common Divisor using Euclid's Algorithm */
//    __asm__ __volatile__ ( "movl %1, %%eax;"
//                          "movl %2, %%ebx;"
//                          "CONTD: cmpl $0, %%ebx;"
//                          "je DONE;"
//                          "xorl %%edx, %%edx;"
//                          "idivl %%ebx;"
//                          "movl %%ebx, %%eax;"
//                          "movl %%edx, %%ebx;"
//                          "jmp CONTD;"
//                          "DONE: movl %%eax, %0;" : "=g" (result) : "g" (a), "g" (b)
//    );
//
//    return result ;
//}
//
//int main() {
//    int first, second ;
//    printf( "Enter two integers : " ) ;
//    scanf( "%d%d", &first, &second );
//
//    printf( "GCD of %d & %d is %d\n", first, second, gcd(first, second) ) ;
//
//    return 0 ;
//}
//
//asm("mov eax, 0xFF");
//    asm("mov _a, eax");
//	inline void asmSinCos( f32 radians, f32& refSinusOut, f32& refCosinusOut )
//	{
//		asm("fld radians");
//
//		asm("fsincos");
//
//		asm("mov ecx,[c]");
//
//		asm("mov edx,[s]");
//
//		asm("fstp  DWORD PTR[ecx]");
//
//		asm("fstp  DWORD PTR[edx]");
//
//	} // end function fastSinCos
//
//	inline f32 asmSQRT( f32 value )
//	{
//		f32 result;
//		asm("fld value");
//
//		asm("fsqrt");
//
//		asm("fstp result");
//
//		return result;
//
//	} // end function fastSQRT


//	inline void __fastcall fastSinCos4(f32 angle,f32 & s,f32 & c) {
//		__asm {
//			fld  angle                      //Lädt den angle auf den f32ing point register stack
//			fmul dword ptr[ToRadians]       //Multipliziert den winkel mit ToRadians um ihn ins Bogenmaß umzurechnen
//			//Dies führt die eigentliche Berechnung durch und packt den cosinus ins ecx register und den sinus ins edx register
//			fsincos
//			mov ecx,[c]                     //Kopiert den berechneten cosinus in den cosinus parameter
//			mov edx,[s]                     //Kopiert den berechneten sinus in den sinus parameter
//			fstp  DWORD PTR[ecx]            //Räumt das verwendete ecx Register wieder auf
//			fstp  DWORD PTR[edx]            //Räumt das verwendete edx Register wieder auf
//		}
//	}

//
//	void normalize(Vec3 * v) {
//	  __asm {
//		mov   eax,v
//		movss xmm0,[eax]Vec3.x
//		movss xmm1,[eax]Vec3.y
//		movss xmm2,[eax]Vec3.z
//
//		mulss xmm0,xmm0
//		mulss xmm1,xmm1
//		mulss xmm2,xmm2
//
//		addss xmm0,xmm1
//		addss xmm2,xmm0
//
//		movss xmm4,[eax]Vec3.x
//		movss xmm5,[eax]Vec3.y
//		movss xmm6,[eax]Vec3.z
//
//		rsqrtss xmm2,xmm2
//
//		mulss xmm4,xmm2
//		mulss xmm5,xmm2
//		mulss xmm6,xmm2
//
//		movss [eax]Vec3.x,xmm4
//		movss [eax]Vec3.y,xmm5
//		movss [eax]Vec3.z,xmm6
//	  } // asm
//	} // normalize
//
//
//	// Intel's sqrtInverse:
//	inline __declspec(naked) f32 __fastcall _sqrtInverse(f32 a) {
//	  __asm {
//		mov   eax,0be6eb508h
//		mov   DWORD PTR [esp-12],03fc00000h // 1.5 on the stack
//		sub   eax, DWORD PTR [esp+4]        // a
//		sub   DWORD PTR [esp+4],800000h     // a/2 a=Y0
//		shr   eax,1                         // first approx. in eax=R0
//		mov   DWORD PTR [esp-8],eax
//
//		fld   DWORD PTR [esp-8]              // r
//		fmul  st,st                          // r*r
//		fld   DWORD PTR [esp-8]              // r
//		fxch  st(1)
//		fmul  DWORD PTR [esp+4]              // a ; r*r*y0
//		fld   DWORD PTR [esp-12]             // load 1.5
//		fld   st(0)
//		fsub  st,st(2)                       // r1 = 1.5 - y1
//											 // x1 = st(3)
//											 // y1 = st(2)
//											 // 1.5 = st(1)
//											 // r1 = st(0)
//
//		fld   st(1)
//		fxch  st(1)
//		fmul  st(3),st	                 // y2=y1*r1*...
//		fmul  st(3),st	                 // y2=y1*r1*r1
//		fmulp st(4),st                       // x2=x1*r1
//		fsub  st,st(2)                       // r2=1.5-y2
//											 // x2=st(3)
//											 // y2=st(2)
//											 // 1.5=st(1)
//											 // r2 = st(0)
//
//		fmul  st(2),st	                 // y3=y2*r2*...
//		fmul  st(3),st                       // x3=x2*r2
//		fmulp st(2),st	                 // y3=y2*r2*r2
//		fxch  st(1)
//		fsubp st(1),st	                 // r3= 1.5 - y3
//											 // x3 = st(1)
//											 // r3 = st(0)
//		fmulp  st(1),st
//		ret 4
//	  }
//	}
//
//	// From http://www.lomont.org/Math/Papers/2003/InvSqrt.pdf
//	inline flt sqrtInverse2(flt n) { // Appears slower than ASM above.
//	  flt halfn = .5f*n;
//	  int i = *(int *)&n;
//	  i = 0x5f375a86 - (i>>1); // 0x5f3759df: original number.
//	  n = *(flt *)&i;
//	  n = n*(1.5f-halfn*n*n);
//	  return n;
//	} // sqrtInverse2
//
//	inline flt sqrtInverse(flt n) { if (n > RSQR(1.f/6.5192024e+018)) return _sqrtInverse(n); else return 0.f; }
//	inline flt rSqrt(flt n) { return n*sqrtInverse(n); }
//
//	// SSE
//
//	inline flt sqrtInverse(flt n) {
//	  __asm  {
//		movss   xmm0,n
//		rsqrtss xmm0,xmm0
//		movss   n,   xmm0
//	  }
//	  return n;
//	} // sqrtInverse
//
//	inline bool lessThanOrEqualZero(flt f) {
//	  return (long &)f <= 0;
//	} // lessThanOrEqualZero
//
//	inline f32 rSqrt(f32 n) {
//	  //  if (n <= 0.f) return 0.f; // 859
//	  if (lessThanOrEqualZero(n)) return 0.f; // 844
//	  __asm {
//		rsqrtss xmm0,n
//		mulss   xmm0,n
//		movss   n,xmm0
//	  }
//	  return n;
//	}
//

//	//! sinus table
//	class CSinCosTablef : public IReferenceCounted
//	{
//	public:
//		struct SinCosPair // point on the unit-circle
//		{
//			f32 sin_angle;
//			f32 cos_angle;
//		};
//
//	private:
//		core::array<SinCosPair> m_table;
//		f32 m_start_ang;
//		f32 m_end_ang;
//		f32 m_step_ang;
//
//	public:
//		explicit CSinCosTablef( u32 count = 36, f32 rad_start = 0.f, f32 rad_end = 2.0f*core::PI )
//		{
//			u32 c = (count>0)?count:1;
//			m_table.reallocate( c );
//			m_table.set_used( c );
//
//			m_start_ang = rad_start;
//			m_end_ang = rad_end;
//			m_step_ang = (rad_end - rad_start) / c;
//
//			f32 phi = rad_start;
//
//			for (u32 i=0; i<c; i++)
//			{
//				asmSinCos( phi, m_table[i].sin_angle, m_table[i].cos_angle );
//
//				phi += m_step_ang;
//			}
//
//		}
//		~CSinCosTablef() { m_table.clear(); }
//
//		const f32& getAngleStartRad() const { return m_start_ang; }
//
//		const f32& getAngleEndRad() const { return m_end_ang; }
//
//		const f32& getAngleStepRad() const { return m_step_ang; }
//
//
//		SinCosPair& operator[] (u32 index) { return m_table[index%m_table.size()]; }
//
//		const SinCosPair& operator[] (u32 index) const { return m_table[index%m_table.size()]; }
//
//
//
//	}; // end class TSinTable


} // end namespace core

typedef core::TSinTable<f32> dbSinTablef;
typedef core::TSinTable<f64> dbSinTabled;
typedef core::TCosTable<f32> dbCosTablef;
typedef core::TCosTable<f64> dbCosTabled;

} // end namespace irr


#endif // __IRR_HAMPE_SINCOS_TABLE_EXTENSIONS_H__
