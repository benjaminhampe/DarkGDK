#ifndef HEADER_15A170968DBC8E6
#define HEADER_15A170968DBC8E6

// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_C_COMBINED_OSCILLATOR_H__
#define __IRR_C_COMBINED_OSCILLATOR_H__

#include <irrlicht.h>

#include "IFunction.h"

namespace irr
{
	/// @brief class that simulates a digital saw/ramp oscillator
	template <class T>
	class CCombinedOscillator : public IFunction<T>
	{
		public:
			/// @brief class constructor
			explicit CCombinedOscillator() : InvCount(0), Envelope(0)
			{
			}

			/// @brief class destructor
			virtual ~CCombinedOscillator()
			{

			}

			/// @brief setter
			virtual void setEnvelope( IFunction<T>* envelope )
			{
				Envelope = envelope;
			}

			/// @brief getter
			virtual IFunction<T>* getEnvelope()
			{
				return Envelope;
			}

			/// @brief setter
			virtual void addOscillator( IFunction<T>* osc )
			{
				if (osc)
				{
					Oscillator.push_back( osc );
					u32 count = Oscillator.size();
					if (count>0)
						InvCount = core::reciprocal( (T)count );
					else
						InvCount = T(0);
				}
			}

			/// @brief getter
			virtual IFunction<T>* getOscillator( u32 index )
			{
				_IRR_DEBUG_BREAK_IF( index >= getOscillatorCount() )
				return Oscillator[index];
			}

			/// @brief getter
			virtual u32 getOscillatorCount( ) const
			{
				return Oscillator.size();
			}

			///@brief implementation of interface IFunction<T>
			virtual T operator() ( const T& seconds ) const
			{
				/// init value to zero
				T value(0);

				/// accumulate all oscillators
				for (u32 i=0; i<Oscillator.size(); ++i)
				{
					IFunction<T>* osc = Oscillator[i];
					if (osc)
					{
						value += ((*osc)(seconds));
					}
				}

				/// multiply with inverse of OscillatorCount
				value *= InvCount;

				/// multiply with Envelope curve (i.e. ADSR), if exist
				if (Envelope)
					value *= ((*Envelope)(seconds));

				return value;
			}

		private:
			T InvCount;
			core::array<IFunction<T>*> Oscillator;
			IFunction<T>* Envelope;
	};

} // end namespace irr

#endif // __IRR_C_SAW_OSCILLATOR_H__

#endif // header guard 
