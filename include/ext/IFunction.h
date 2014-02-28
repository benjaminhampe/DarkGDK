// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_INTERFACE_FUNCTION_H__
#define __IRR_INTERFACE_FUNCTION_H__

namespace irr
{
	///@class IFunction
	///@brief This class is a functor or callable object, 
	/// because it overloads the "function call" operator.
	/// It has no states, only interface.

	template <class T>
	class IFunction
	{
		public:
			/// @brief IFunction interface
			virtual T operator() ( const T& value ) const = 0;

	};

} // end namespace irr

#endif // __IRR_INTERFACE_FUNCTION_H__
