#ifndef HEADER_4B7437BDB254847A
#define HEADER_4B7437BDB254847A

// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_C_SINE_OSCILLATOR_H__
#define __IRR_C_SINE_OSCILLATOR_H__

#include <irrlicht.h>

#include "IFunction.h"

namespace irr
{
	/// @brief class that simulates a digital sine oscillator
	template <class T>
	class CSineOscillator : public IFunction<T>
	{
		public:
			///@brief constant for 2*PI
			const T TWO_PI = (T)(core::PI64*2.0);

		public:
			/// @brief class constructor
			CSineOscillator( const T& freq = (T)440, const T& phase = (T)0, const T& amp = (T)1)
			{
				setFrequency( freq );
				setPhase( phase );
				setAmplitude( amp );
			}

			/// @brief class destructor
			virtual ~CSineOscillator()
			{

			}

			/// @brief implementation for interface IFunctionOfTime
			virtual T operator() ( const T& seconds ) const _IRR_OVERRIDE_
			{
				return Amplitude*sin( TWO_PI*seconds*Frequency + Phase );
			}

			/// @brief setter
			virtual void setFrequency( const T& frequency )
			{
				Frequency = core::clamp<T>( frequency, (T)1, (T)22050 );
			}

			/// @brief setter
			virtual void setPhase( const T& phase )
			{
				Phase = core::clamp<T>( phase, T(0), T(1) );
			}

			/// @brief setter
			virtual void setAmplitude( const T& amplitude )
			{
				Amplitude = core::clamp<T>( amplitude, (T)0, (T)32767 );
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
			virtual T getAmplitude( ) const
			{
				return Amplitude;
			}

		private:

			T Frequency;
			T Phase;
			T Amplitude;
	};

} // end namespace irr

#endif // __IRR_C_SINE_OSCILLATOR_H__

#endif // header guard 
