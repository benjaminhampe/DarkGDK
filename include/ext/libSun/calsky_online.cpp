// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "calsky_online.h"

#include "../irrDateTime.h"
#include "CSonnenstand.h"

#include "calsky.h"

namespace irr{
namespace astro{
namespace calsky{

} // end namespace calsky

	CSonnenstand calsky_online( Real lon, Real lat, Real jdTime )
	{
		return calsky_sonnenstand( lon, lat, jdTime );
	}

	/// @return Array of sun-position from one request, use this
	core::array<CSonnenstand> calsky_online( Real lon, Real lat, Real jdStart, Real jdEnd, u32 count )
	{
		core::array<CSonnenstand> container;

		Real jdStep = (jdEnd - jdStart) / (Real)count;
		Real jdNow = jdStart;

		for (u32 i=0; i<count; i++)
		{
			container.push_back( calsky_sonnenstand( jdNow, lon, lat) );
			jdNow += jdStep;
		}

		return container;
	}


} // end namespace astro
} // end namespace irr
