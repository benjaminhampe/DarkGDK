// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __SUNLIB_HAMPE_CALSKY_H_INCLUDED__
#define __SUNLIB_HAMPE_CALSKY_H_INCLUDED__

#include <irrTypes.h>
#include <irrMath.h>
#include "CSonnenstand.h"

namespace irr{
namespace astro{

	CSonnenstand 	calsky_sonnenstand( Real T, Real Breitengrad, Real ZeitSeitMittag);

} // end namespace astro
} // end namespace irr

#endif // __SUNLIB_HAMPE_CALSKY_H_INCLUDED__

