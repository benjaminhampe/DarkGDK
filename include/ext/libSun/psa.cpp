// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

// This file is available in electronic form at http://www.psa.es/sdg/sunpos.htm

#include "psa.h"

#include <irrTypes.h>
#include "../irrDateTime.h"
#include "CSonnenstand.h"

//	// Declaration of some constants
//	#define twopi (2.0*core::PI64)
//	#define rad   (pi/180)
	#define dEarthMeanRadius     6371.01	// In km
	#define dAstronomicalUnit    149597890	// In km
//
namespace irr{
namespace astro{
namespace psa{
/// Declaration

	struct cTime
	{
		s32 iYear;
		s32 iMonth;
		s32 iDay;
		Real dHours;
		Real dMinutes;
		Real dSeconds;
	};

	struct cLocation
	{
		Real dLongitude;
		Real dLatitude;
	};

	struct cSunCoordinates
	{
		Real dZenithAngle;
		Real dAzimuth;
	};

	void sunpos(cTime udtTime, cLocation udtLocation, cSunCoordinates *udtSunCoordinates);


void sunpos(cTime udtTime, cLocation udtLocation, cSunCoordinates *udtSunCoordinates)
{
	// Main variables
	Real dElapsedJulianDays;
	Real dDecimalHours;
	Real dEclipticLongitude;
	Real dEclipticObliquity;
	Real dRightAscension;
	Real dDeclination;

	// Auxiliary variables
	Real dY;
	Real dX;

	// Calculate difference in days between the current Julian Day
	// and JD 2451545.0, which is noon 1 January 2000 Universal Time
	{
		Real dJulianDate;
		s32 liAux1;
		s32 liAux2;
		// Calculate time of the day in UT decimal hours
		dDecimalHours = udtTime.dHours + (udtTime.dMinutes
			+ udtTime.dSeconds / 60.0 ) / 60.0;
		// Calculate current Julian Day
		liAux1 =(udtTime.iMonth-14)/12;
		liAux2=(1461*(udtTime.iYear + 4800 + liAux1))/4 + (367*(udtTime.iMonth
			- 2-12*liAux1))/12- (3*((udtTime.iYear + 4900
		+ liAux1)/100))/4+udtTime.iDay-32075;
		dJulianDate=(Real)(liAux2)-0.5+dDecimalHours/24.0;
		// Calculate difference between current Julian Day and JD 2451545.0
		dElapsedJulianDays = dJulianDate-2451545.0;
	}

	// Calculate ecliptic coordinates (ecliptic longitude and obliquity of the
	// ecliptic in radians but without limiting the angle to be less than 2*Pi
	// (i.e., the result may be greater than 2*Pi)
	{
		Real dMeanLongitude;
		Real dMeanAnomaly;
		Real dOmega;
		dOmega=2.1429-0.0010394594*dElapsedJulianDays;
		dMeanLongitude = 4.8950630+ 0.017202791698*dElapsedJulianDays; // Radians
		dMeanAnomaly = 6.2400600+ 0.0172019699*dElapsedJulianDays;
		dEclipticLongitude = dMeanLongitude + 0.03341607*sin( dMeanAnomaly )
			+ 0.00034894*sin( 2*dMeanAnomaly )-0.0001134
			-0.0000203*sin(dOmega);
		dEclipticObliquity = 0.4090928 - 6.2140e-9*dElapsedJulianDays
			+0.0000396*cos(dOmega);
	}

	// Calculate celestial coordinates ( right ascension and declination ) in radians
	// but without limiting the angle to be less than 2*Pi (i.e., the result may be
	// greater than 2*Pi)
	{
		Real dSin_EclipticLongitude = sin( dEclipticLongitude );
		dY = cos( dEclipticObliquity ) * dSin_EclipticLongitude;
		dX = cos( dEclipticLongitude );
		dRightAscension = atan2( dY,dX );
		if( dRightAscension < 0.0 ) dRightAscension = dRightAscension + 2.0*core::PI64;
		dDeclination = asin( sin( dEclipticObliquity )*dSin_EclipticLongitude );
	}

	// Calculate local coordinates ( azimuth and zenith angle ) in degrees
	{
		Real dGreenwichMeanSiderealTime;
		Real dLocalMeanSiderealTime;
		Real dLatitudeInRadians;
		Real dHourAngle;
		Real dCos_Latitude;
		Real dSin_Latitude;
		Real dCos_HourAngle;
		Real dParallax;
		dGreenwichMeanSiderealTime = 6.6974243242 + 0.0657098283*dElapsedJulianDays + dDecimalHours;
		dLocalMeanSiderealTime = (dGreenwichMeanSiderealTime*15 + udtLocation.dLongitude)*core::DEGTORAD64;
		dHourAngle = dLocalMeanSiderealTime - dRightAscension;
		dLatitudeInRadians = udtLocation.dLatitude*core::DEGTORAD64;
		dCos_Latitude = cos( dLatitudeInRadians );
		dSin_Latitude = sin( dLatitudeInRadians );
		dCos_HourAngle= cos( dHourAngle );
		udtSunCoordinates->dZenithAngle = (acos( dCos_Latitude*dCos_HourAngle*cos(dDeclination) + sin( dDeclination )*dSin_Latitude));
		dY = -sin( dHourAngle );
		dX = tan( dDeclination )*dCos_Latitude - dSin_Latitude*dCos_HourAngle;
		udtSunCoordinates->dAzimuth = atan2( dY, dX );
		if ( udtSunCoordinates->dAzimuth < 0.0 )
			udtSunCoordinates->dAzimuth = udtSunCoordinates->dAzimuth + 2.0*core::PI64;
		udtSunCoordinates->dAzimuth = udtSunCoordinates->dAzimuth/core::DEGTORAD64;
		// Parallax Correction
		dParallax=(dEarthMeanRadius/dAstronomicalUnit)*sin(udtSunCoordinates->dZenithAngle);
		udtSunCoordinates->dZenithAngle=(udtSunCoordinates->dZenithAngle + dParallax)/core::DEGTORAD64;
	}

//	udtSunCoordinates->dAzimuth+=180.0;
//	while (udtSunCoordinates->dAzimuth>360.0)
//		udtSunCoordinates->dAzimuth-=360.0;
//	while (udtSunCoordinates->dAzimuth<0.0)
//		udtSunCoordinates->dAzimuth+=360.0;
}

} // end namespace psa

/// Implementation
CSonnenstand psa_sonnenstand(Real mJD, Real lon, Real lat)
{
	core::DateTime date(mJD);
	psa::cTime udtTime;
	udtTime.iYear = date.getYear();
	udtTime.iMonth = date.getMonth();
	udtTime.iDay = date.getDay();
	udtTime.dHours = date.getHour();
	udtTime.dMinutes = date.getMinute();
	udtTime.dSeconds = date.getSecond();

	psa::cLocation udtLocation;
	udtLocation.dLongitude = lon;
	udtLocation.dLatitude = lat;

	psa::cSunCoordinates udtSunCoordinates;
	psa::sunpos(udtTime, udtLocation, &udtSunCoordinates);

	return CSonnenstand(mJD, udtSunCoordinates.dAzimuth, 90.0-udtSunCoordinates.dZenithAngle, ESS_PSA);
}


} // end namespace astro
} // end namespace irr
