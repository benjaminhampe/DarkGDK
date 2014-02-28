#ifndef HEADER_FE81919916D7D577
#define HEADER_FE81919916D7D577

// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_C_SAW_OSCILLATOR_H__
#define __IRR_C_SAW_OSCILLATOR_H__

#include <irrlicht.h>

#include "IFunction.h"

/**
*
*\page Mathe
*  \f[
*   |I_2|=\left| \int_{0}^T \psi(t)
*             \left\{
*                u(a,t)-
*                \int_{\gamma(t)}^a
*                \frac{d\theta}{k(\theta,t)}
*                \int_{a}^\theta c(\xi)u_t(\xi,t)\,d\xi
*             \right\} dt
*          \right|
*  \f]
*
*/

namespace irr
{
	/// @brief class that simulates a digital saw/ramp oscillator
	template <class T>
	class CSawOscillator : public IFunction<T>
	{
		public:
			/// @brief class constructor
			explicit CSawOscillator(
				const T& freq = (T)440,
				const T& phase = (T)0,
				const T& amplitude_max = (T)1,
				const T& amplitude_min = (T)0 )
			{
				setFrequency( freq );
				setPhase( phase );
				setAmplitudeRange( amplitude_max, amplitude_min );
			}

			/// @brief class destructor
			virtual ~CSawOscillator()
			{

			}

			/// @brief setter
			virtual void setFrequency( const T& frequency )
			{
				Frequency = core::clamp<T>( frequency, (T)1, (T)22050 );
				Period = core::reciprocal( Frequency );
			}

			/// @brief setter
			virtual void setPhase( const T& phase )
			{
				Phase = core::clamp<T>( phase, T(0), T(1) );
			}

			/// @brief setter
			virtual void setAmplitudeRange( const T& amplitude_max, const T& amplitude_min )
			{
				//Amplitude = core::clamp<T>( amplitude, (T)0, (T)32767 );
				Amplitude_Min = amplitude_min;
				Amplitude_Max = amplitude_max;
			}

			/// @brief setter
			virtual void setAmplitudeMin( const T& amplitude_min )
			{
				Amplitude_Min = amplitude_min;
			}

			/// @brief setter
			virtual void setAmplitudeMax( const T& amplitude_max )
			{
				Amplitude_Max = amplitude_max;
			}

			/// @brief getter
			virtual T getFrequency( ) const
			{
				return Frequency;
			}

			/// @brief getter
			virtual T getPhase( ) const
			{
				return Phase;
			}

			/// @brief getter
			virtual T getAmplitudeMin( ) const
			{
				return Amplitude_Min;
			}

			/// @brief getter
			virtual T getAmplitudeMax( ) const
			{
				return Amplitude_Max;
			}

			///@brief implementation of interface IFunctionOfTime
			virtual T operator() ( const T& seconds ) const
			{
				const T t_modded = fmod( seconds - Period*Phase, Period );

				return ( Amplitude_Max - Amplitude_Min ) * Frequency * t_modded + Amplitude_Min;
			}

		private:

			T Frequency;
			T Period;
			T Phase;
			T Amplitude_Min;
			T Amplitude_Max;
	};

} // end namespace irr

#endif // __IRR_C_SAW_OSCILLATOR_H__

#endif // header guard 
