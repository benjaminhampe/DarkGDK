#include "vdi2067.h"

#include <irrTypes.h>
#include "../irrDateTime.h"
#include "CSonnenstand.h"

namespace irr{
namespace astro{
namespace vdi2067{

/// Declaration

	Real 		deklination( Real J );

	Real 		zeitgleichung( Real J );

/// Implementation

//------------------------------------------------------------------------------------------
// 							FUNCTIONS
//------------------------------------------------------------------------------------------

// Funktion:	sonnendeklination()
// Parameter:	Real Tageswinkel J = 360 TagDesJahres / AnzTageImJahr
// Return:		Real Grad
//------------------------------------------------------------------------------------------
Real deklination(Real J)
//------------------------------------------------------------------------------------------
{
	Real declination(0.3948);
	declination -= 23.2559 * cos( core::DEGTORAD64*(J+9.1) );
	declination -=  0.3915 * cos( core::DEGTORAD64*(2.0*J+5.4) );
	declination -=  0.1764 * cos( core::DEGTORAD64*(3.0*J+20.6) );
	return declination;
}

// Funktion:	zeitgleichung()
// Parameter:	Real Tageswinkel J = 360? TagDesJahres / AnzTageImJahr
// Return:		Real Zeitabweichung in jdMinuten
//------------------------------------------------------------------------------------------
Real zeitgleichung(Real J)
//------------------------------------------------------------------------------------------
{
	// Differenz zwischen wahrer und mittlerer Sonnenzeit
	Real zgl = 0.0066;
	zgl += 7.3525 * cos( core::DEGTORAD64 * (J+85.9) );
	zgl += 9.9359 * cos( core::DEGTORAD64 * (2.0*J+108.9) );
	zgl += 0.3387 * cos( core::DEGTORAD64 * (3.0*J+105.2) );
	return zgl * core::INV_1440;
}

} // end namespace vdi2067

// Funktion:	zeitgleichung()
// Parameter:	s32 T = Tag im Jahr [1..365/366]
// Return:		Real in Bruchteilen von Stunden
//------------------------------------------------------------------------------------------
//hampe::CSonnenstand berechne_vdi2067(const Real& jdMEZ, const Real& lon, const Real& lat, bool log)
CSonnenstand vdi2067_sonnenstand(Real jdMEZ, Real lon, Real lat, bool bLog)
//------------------------------------------------------------------------------------------
{
	core::DateTime MEZ(jdMEZ);
	const Real dayOfYear = core::DateTime::getDayOfYear(MEZ.getJD());
	const Real daysOfYear = core::DateTime::getDaysOfYear(MEZ.getJD());
	const Real J = 360.0 * dayOfYear / daysOfYear;

	// WOZ = MEZ - 4.0*(15.0-lon) min + Zgl(T);
	const Real jdOrtskorrektur = 4.0*(15.0-lon)*core::INV_1440;
	const Real jdZeitgleichung = vdi2067::zeitgleichung(J);
	const Real jdWOZ = jdMEZ - jdOrtskorrektur + jdZeitgleichung;

	core::DateTime WOZ(jdWOZ);
	const Real omega = (Real)(12-WOZ.getHour())*15.0;

	Real hoehe = cos(core::DEGTORAD64*omega);
	const Real sinB = cos(core::DEGTORAD64*lat);
	const Real cosB = cos(core::DEGTORAD64*lat);
	const Real sinD = sin(core::DEGTORAD64*vdi2067::deklination(J));
	const Real cosD = cos(core::DEGTORAD64*vdi2067::deklination(J));
	hoehe = asin(hoehe*cosB*cosD-sinB*sinD);

	const Real sinH = sin(hoehe);
	const Real cosH = cos(hoehe);
	hoehe *= core::RADTODEG64;

	Real azimut = acos((sinH*sinB-sinD)/(cosH*cosB));
	azimut *= core::RADTODEG64;

	if (WOZ.getHour()<12)
		azimut = 180.0-azimut;
	else if (WOZ.getHour()>12)
		azimut = 180.0+azimut;
	else
		if (WOZ.getMinute()>0)
			azimut = 180.0+azimut;
		else
			if (WOZ.getSecond()>0)
				azimut = 180.0+azimut;
			else
				azimut = 180.0-azimut;

	return CSonnenstand( jdWOZ, azimut, hoehe, ESS_VDI2067);
}

} // end namespace astro
} // end namespace irr
