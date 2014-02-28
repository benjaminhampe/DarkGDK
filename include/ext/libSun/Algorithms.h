// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __SUNLIB_HAMPE_ALGORITHMS_H_INCLUDED__
#define __SUNLIB_HAMPE_ALGORITHMS_H_INCLUDED__

#include <irrlicht.h>
#include <cstdlib>
#include <ctime>

#include "../irrDateTime.h"
#include "CSonnenstand.h"

namespace irr{
namespace astro	{

	core::stringc ArrayToString( const core::array<CSonnenstand>& data, const core::stringc& name = "");

	/// @return array of sun-positions from SpaceTime coords (lon,lat,start_time,end_time,count) and specified method;
	/// @param lon 	- longitude, geographische Laenge in Grad
	/// @param lat 	- latitude, geographische Breite in Grad
	/// @param jdStart 	- astronomische Startzeit ( JulianDayNumber ) meistens JD(year,1,1)
	/// @param jdEnd 	- astronomische Endzeit ( JulianDayNumber ) meistens JD(year+1,1,1)
	/// @param count 	- Anzahl von Array-Elementen == Anzahl berechneter Punkte, meistens getDaysOfYear(year) [365..366]
	///
	/// @example [2] If you like to calculate the time-equation ... do
	///
	///				createData( lon, lat, JD(year,1,1), JD(year+1,1,1), getDaysOfYear(year), method);
	///
	/// @example [2] If you like to calculate the sun-positions over one day and every hour ( 24 points ) ... do
	///
	///				createData( lon, lat, JD(year,1,day), JD(year,1,day+1), 24, method);
	///
	/// @example [3] If you like to draw sun-positions to a big image use more points and connect them with (straight) lines
	///				The more points you have, the more rounded/curved your image will look like, but with the tradeoff of speed.
	///
	core::array<CSonnenstand> createData( Real lon, Real lat, Real jdStart, Real jdEnd, u32 count, ESS_COMPUTE_METHOD method = ESS_WIKIPEDIA );





	// This function calls all other functions, and should be used
	CSonnenstand sonnenstand(Real jd, Real lon, Real lat, ESS_COMPUTE_METHOD method = ESS_WIKIPEDIA );

	CSonnenstand find_sunrise_of_day( Real jd, Real lon, Real lat, ESS_COMPUTE_METHOD method, u32 maxIter = 10000 );
	CSonnenstand find_sunset_of_day( Real jd, Real lon, Real lat, ESS_COMPUTE_METHOD method, u32 maxIter = 10000 );
	CSonnenstand find_max_sunpos_of_day( Real jd, Real lon, Real lat, ESS_COMPUTE_METHOD method, u32 maxIter = 10000 );

} // end namespace astro
} // end namespace irr

#endif // __SUNLIB_HAMPE_ALGORITHMS_H_INCLUDED__
