// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __SUNLIB_HAMPE_PSA_H_INCLUDED__
#define __SUNLIB_HAMPE_PSA_H_INCLUDED__

#include <irrTypes.h>
#include <irrMath.h>
#include "../irrDateTime.h"
#include "CSonnenstand.h"

// Original algorithm is available in electronic form at http://www.psa.es/sdg/sunpos.htm

namespace irr{
namespace astro{

	CSonnenstand psa_sonnenstand(Real mJD, Real lon, Real lat);

} // end namespace astro
} // end namespace irr

#endif // __SUNLIB_HAMPE_PSA_H_INCLUDED__
