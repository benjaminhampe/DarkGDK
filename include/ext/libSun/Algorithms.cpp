// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "Algorithms.h"

#include <irrlicht.h>

#include <iostream>

#include "../irrUtils.h"

#include "../irrDateTime.h"

#include "wikipedia.h"
#include "psa.h"
#include "nrel.h"
#include "calsky.h"
#include "calsky_online.h"
#include "vsop.h"
#include "vdi2067.h"
#include "vsop_87.h"

namespace irr
{
namespace astro
{
	//!
	core::stringc ArrayToString( const core::array<CSonnenstand>& data, const core::stringc& name)
	{
		core::stringc result = "Array ";

		const u32& count = data.size();

		if (name.size()>0)
		{
			result += name;
		}
		result += " with ";
		result += count;
		result += " element(s):\n";

		core::stringc line;
		for (u32 i=0; i<count; i++)
		{
			line = "Element [";
			line += i;
			line += "] = ";
			line += data[i].toString();
			line += "\n";
			result += line;
		}

		return result;
	}

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

/// @return array of sun-positions from SpaceTime coords (lon,lat,start_time,end_time,count) and specified method;
/// @param lon 	- longitude, geographische Laenge in Grad
/// @param lat 	- latitude, geographische Breite in Grad
/// @param jdStart 	- astronomische Startzeit ( JulianDayNumber ) meistens JD(year,1,1)
/// @param jdEnd 	- astronomische Endzeit ( JulianDayNumber ) meistens JD(year+1,1,1)
/// @param count 	- Anzahl von Array-Elementen == Anzahl berechneter Punkte, meistens getDaysOfYear(year) [365..366]

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///

core::array<CSonnenstand> createData( Real lon, Real lat, Real jdStart, Real jdEnd, u32 count, ESS_COMPUTE_METHOD method)
{
	core::array<CSonnenstand> data;
	data.reallocate( count );
	data.set_used( 0 );

	Real jd_step = (jdEnd-jdStart) / (Real)count;
	Real jd_now = jdStart;

	for (u32 i=0; i<count; i++)
	{
		CSonnenstand s = sonnenstand(jd_now, lon, lat, method);
		if (s.mHoehe > 0.0 || core::equals(s.mHoehe, 0.0) )
		{
			data.push_back( s );
		}
		jd_now += jd_step;
	}

	return data;
}

//	enum ESS_COMPUTE_METHOD
//	{
//		ESS_WIKIPEDIA=0,
//		ESS_QUASCHNING,
//		ESS_CALSKY,
//		ESS_PSA,
//		ESS_NREL,
//		ESS_VDI2067,
//		ESS_VSOP,
//		ESS_VSOP87,
//		ESS_CALSKY_ONLINE,
//		ESS_COUNT
//	};

/// @todo: Only expose this function as interface to sunLib
CSonnenstand sonnenstand(Real jd, Real lon, Real lat, ESS_COMPUTE_METHOD method)
{
	CSonnenstand pos(0,0,0,ESS_COUNT);
	switch (method)
	{
		case ESS_WIKIPEDIA:		pos = wikipedia_sonnenstand(jd,lon,lat); break;
		case ESS_QUASCHNING:	pos = vdi2067_sonnenstand(jd,lon,lat); break;
		case ESS_CALSKY:		pos = calsky_sonnenstand(jd,lat,lon); break;
		case ESS_PSA:		    pos = psa_sonnenstand(jd,lon,lat); break;
		case ESS_NREL:		    pos = nrel_sonnenstand(jd,lon,lat); break;
		case ESS_VDI2067:		pos = vdi2067_sonnenstand(jd,lon,lat); break;
		case ESS_VSOP:		    pos = vsop_sonnenstand(jd,lon,lat); break;
		case ESS_VSOP87:		pos = vsop_sonnenstand(jd,lon,lat); break;
		case ESS_CALSKY_ONLINE:	pos = calsky_online(jd,lat,lon); break;
		default: break;
	}
	return pos;
}

//! return sunpos of maximum zenith-angle of this one day defined by jd = core::DateTime::JD(year,month,day)
CSonnenstand find_sunrise_of_day( Real jd, Real lon, Real lat, ESS_COMPUTE_METHOD method, u32 maxIter )
{
	// u32 maxIter = 10000;
	core::DateTime date( jd );
	Real timeStart = core::DateTime::JD(date.getYear(), date.getMonth(), date.getDay(), 0,0,0,0);
//	Real timeEnd = core::DateTime::JD(date.getYear(), date.getMonth(), date.getDay()+1, 0,0,0,0);
	Real timeStep = core::reciprocal( (Real)maxIter );
	Real timeNow = timeStart;
	CSonnenstand s_max = sonnenstand(jd,lon,lat,method);
	for (u32 i=0; i<maxIter; i++)
	{
		CSonnenstand s_now = sonnenstand( timeNow, lon, lat, method);

		if ( s_max.mHoehe < s_now.mHoehe )
		{
			// s_max = s_now;
			s_max.mJD = timeNow;
			s_max.mHoehe = s_now.mHoehe;
			s_max.mAzimut = s_now.mAzimut;
		}

		timeNow += timeStep;
	}

	return s_max;
}

/// @todo: Only expose this function as interface to sunLib
CSonnenstand find_sunset_of_day( Real jd, Real lon, Real lat, ESS_COMPUTE_METHOD method, u32 maxIter)
{
	core::DateTime date( jd );
	Real timeStart = core::DateTime::JD(date.getYear(), date.getMonth(), date.getDay(), 0,0,0,0);
//	Real timeEnd = core::DateTime::JD(date.getYear(), date.getMonth(), date.getDay()+1, 0,0,0,0);
	Real timeStep = core::reciprocal( (Real)maxIter );
	Real timeNow = timeStart;
	CSonnenstand s_max = sonnenstand(jd,lon,lat,method);
	for (u32 i=0; i<maxIter; i++)
	{
		CSonnenstand s_now = sonnenstand( timeNow, lon, lat, method);

		if ( s_max.mHoehe < s_now.mHoehe )
		{
			// s_max = s_now;
			s_max.mJD = timeNow;
			s_max.mHoehe = s_now.mHoehe;
			s_max.mAzimut = s_now.mAzimut;
		}

		timeNow += timeStep;
	}

	return s_max;
}

/// @todo: Only expose this function as interface to sunLib
CSonnenstand find_max_sunpos_of_day( Real jd, Real lon, Real lat, ESS_COMPUTE_METHOD method, u32 maxIter)
{
	core::DateTime date( jd );
	Real timeStart = core::DateTime::JD(date.getYear(), date.getMonth(), date.getDay(), 0,0,0,0);
//	Real timeEnd = core::DateTime::JD(date.getYear(), date.getMonth(), date.getDay()+1, 0,0,0,0);
	Real timeStep = core::reciprocal( (Real)maxIter );
	Real timeNow = timeStart;
	CSonnenstand s_max = sonnenstand(jd,lon,lat,method);
	for (u32 i=0; i<maxIter; i++)
	{
		CSonnenstand s_now = sonnenstand( timeNow, lon, lat, method);

		if ( s_max.mHoehe < s_now.mHoehe )
		{
			// s_max = s_now;
			s_max.mJD = timeNow;
			s_max.mHoehe = s_now.mHoehe;
			s_max.mAzimut = s_now.mAzimut;
		}

		timeNow += timeStep;
	}

	return s_max;
}

} // end namespace astro
} // end namespace irr
