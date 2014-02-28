// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __SUNLIB_HAMPE_CALSKY_ONLINE_H_INCLUDED__
#define __SUNLIB_HAMPE_CALSKY_ONLINE_H_INCLUDED__

#include <irrTypes.h>
#include <irrMath.h>
#include "CSonnenstand.h"

namespace irr{
namespace astro{

	/// Calsky online-server request using SFML-Network for HTTP connection
	/// These functions have to build a valid request and have to parse the results
	/// As servers can change their data-representation all time, these parsers can fail without reason and no warning
	/// worse would be corrupted data without any hint that its incorrect, so pls use with care
	/// The other CalSky algorithm is a fast offline approximation from an external source valid within years 2008 till 2028
	/// with an estimated maximum error of 3 min. at 65° North ( more higher latitudes have higher errors )

	/// @return One sun-position from one request, but this seems much much inefficient

	CSonnenstand calsky_online( Real lon, Real lat, Real jdTime );

	/// @return Array of sun-position from one request, use this
	core::array<CSonnenstand> calsky_online( Real lon, Real lat, Real jdStart, Real jdEnd, u32 count );


} // end namespace astro
} // end namespace irr

#endif // __SUNLIB_HAMPE_CALSKY_ONLINE_H_INCLUDED__

