// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_C_PULSE_OSCILLATOR_H__
#define __IRR_C_PULSE_OSCILLATOR_H__

#include <irrlicht.h>

#include "IFunction.h"

namespace irr
{
	///@brief class that simulates a digital pulse/rectangle/square oscillator
	template <class T>
	class CPulseOscillator : public IFunction<T>
	{
		public:

		///@brief class contructor
		explicit
		CPulseOscillator(
			const T& freq = (T)440,
			const T& phase = (T)0,
			const T& pulsewidth = (T)0.5,
			const T& amplitude_max = (T)1,
			const T& amplitude_min = (T)0 )
		{
			setFrequency( freq );
			setPhase( phase );
			setPulseWidth( pulsewidth );
			setAmplitudeRange( amplitude_max, amplitude_min );
		}

		///@brief class destructor
		virtual ~CPulseOscillator()
		{

		}

		///@brief setter
		virtual void setFrequency( const T& frequency )
		{
			Frequency = core::clamp<T>( frequency, (T)1, (T)22050 );
			Period = core::reciprocal( Frequency );
		}

		///@brief getter
		virtual T getFrequency( ) const
		{
			return Frequency;
		}

		///@brief setter
		virtual void setPhase( const T& phase )
		{
			Phase = core::clamp<T>( phase, T(0), T(1) );
		}

		///@brief getter
		virtual T getPhase( ) const
		{
			return Phase;
		}

		///@brief setter
		virtual void setPulseWidth( const T& pulseWidth )
		{
			PulseWidth = core::clamp<T>( pulseWidth, T(0), T(1) );
		}

		///@brief getter
		virtual T getPulseWidth( ) const
		{
			return PulseWidth;
		}

		/// @brief setter
		virtual void setAmplitudeRange( const T& amplitude_max, const T& amplitude_min )
		{
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

			const T t_pulse = Period*PulseWidth;

			if ( t_modded <= t_pulse && t_modded >= T(0) )
				return Amplitude_Max;
			else
				return Amplitude_Min;
		}

	private:
		T Period;
		T Frequency;
		T Phase;
		T PulseWidth;
		T Amplitude_Min;
		T Amplitude_Max;
	};

} // end namespace irr

#endif // __IRR_C_PULSE_OSCILLATOR_H__
