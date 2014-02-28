#ifndef HEADER_29620677C5FD619F
#define HEADER_29620677C5FD619F

// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_C_ADSR_ENVELOPE_H__
#define __IRR_C_ADSR_ENVELOPE_H__

#include <irrlicht.h>

#include "IFunction.h"

namespace irr
{
	/// @brief class that simulates a digital saw/ramp oscillator
	template <class T>
	class CADSREnvelope : public IFunction<T>
	{
		public:
			enum E_MONOTONIC_TYPE
			{
//				EMTT_CONSTANT,
				EMTT_LINEAR=0,
				EMTT_QUADRATIC,
//				EMTT_CUBIC,
//				EMTT_SQUAREROOT,
//				EMTT_EXPONENTIAL,
//				EMTT_LOGARITHMIC,
				EMTT_COUNT
			};

			/// @brief class constructor
			explicit CADSREnvelope(
				const T& a = (T)0.01 /* in seconds */,
				const T& d = (T)0.1 /* in seconds */,
				const T& s = (T)0.7 /* in range [0,1] of amplitude_range ( max - min ) */,
				const T& r = (T)0.3 /* in seconds */,
				const E_MONOTONIC_TYPE& type = EMTT_LINEAR )
			{
				set( a, d, s, r, type );
//				setAttack( a );
//				setDecay( d );
//				setSustain( s );
//				setRelease( r );
				// setAmplitudeRange( amplitude_max, amplitude_min );
			}

			/// @brief class destructor
			virtual ~CADSREnvelope()
			{

			}

			/// @brief setter
			virtual void set(
				const T& a,
				const T& d,
				const T& s,
				const T& r,
				const E_MONOTONIC_TYPE& type = EMTT_LINEAR )
			{
				A = a;
				D = d;
				S = s;
				R = r;
				Max = T(1);
				Min = T(0);
				TypeA = type;
				TypeD = type;
				TypeR = type;
			}

			///@brief implementation of interface IFunctionOfTime
			virtual T operator() ( const T& seconds ) const
			{
				//const T Period = T(.001*(A+D+R)); // convert to seconds
				//const T t = fmod( seconds, Period ); // modulo to first period
				const T t = seconds;

				const T Range = (Max-Min);

				const T zero(0);

				switch (TypeA)
				{
					case EMTT_LINEAR:
					{
						if ( t < zero )
						{
							return zero;
						}
						else if ( t < A ) /// Attack
						{
							T m = Range*core::reciprocal(A);
							T n = Min;
							return m*t+n;
						}
						else if ( (t > A) && (t <= (A+D)) ) /// Decay
						{
							T m = (S-T(1))*Range*core::reciprocal(D);
							T b = A+D;
							T n = S*Range + Min;

							return m*(t-b)+n;
						}
						else
						{
							return S*Range + Min;
						}
					}
					break;

					default:
						break;
				}

				// nothing so far
				return zero;
			}

			/// @brief getter
			virtual T getAttack( ) const
			{
				return A;
			}

			/// @brief getter
			virtual E_MONOTONIC_TYPE getAttackType( ) const
			{
				return TypeA;
			}

			/// @brief getter
			virtual T getDecay( ) const
			{
				return D;
			}

			/// @brief getter
			virtual E_MONOTONIC_TYPE getDecayType( ) const
			{
				return TypeD;
			}

			/// @brief getter
			virtual T getSustain( ) const
			{
				return S;
			}

			/// @brief getter
			virtual T getRelease( ) const
			{
				return R;
			}

			/// @brief getter
			virtual E_MONOTONIC_TYPE getReleaseType( ) const
			{
				return TypeR;
			}

			/// @brief getter
			virtual T getMin( ) const
			{
				return Min;
			}

			/// @brief getter
			virtual T getMax( ) const
			{
				return Max;
			}

			/// @brief setter
			virtual void setAttack( const T& a )
			{
				A = a;
			}
			/// @brief setter
			virtual void setDecay( const T& d )
			{
				D = d;
			}
			/// @brief setter
			virtual void setSustain( const T& s )
			{
				S = s;
			}
			/// @brief setter
			virtual void setRelease( const T& r )
			{
				R = r;
			}
			/// @brief setter
			virtual void setMinMax( const T& y_max, const T& y_min )
			{
				//Amplitude = core::clamp<T>( amplitude, (T)0, (T)32767 );
				Min = y_min;
				Max = y_max;
			}

			/// @brief setter
			virtual void setMin( const T& y_min )
			{
				Min = y_min;
			}

			/// @brief setter
			virtual void setMax( const T& y_max )
			{
				Max = y_max;
			}

		private:
			T A;
			T D;
			T S;
			T R;
			T Min;
			T Max;
			E_MONOTONIC_TYPE TypeA;
			E_MONOTONIC_TYPE TypeD;
			E_MONOTONIC_TYPE TypeR;
	};

} // end namespace irr

#endif // __IRR_C_ADSR_ENVELOPE_H__

#endif // header guard 
