// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "calsky.h"

#include "../irrDateTime.h"
#include "CSonnenstand.h"

namespace irr{
namespace astro{
namespace calsky{

/// Declaration

	// Höhe des Sonnenmittelpunktes bei Aufgang
	// 50 Bogenminuten über mathematischen Horizont
	const Real 		HOEHE_AUFGANG = -(50.0/60.0) * irr::core::DEGTORAD64;

	Real 			calsky_deklination( Real T);
	Real 			calsky_zeitdifferenz( Real Deklination, Real Breitengrad);
	Real 			calsky_zeitgleichung( Real T);
	Real 			calsky_aufgang( Real T, Real Breitengrad);
	Real 			calsky_untergang( Real T, Real Breitengrad);
	Real 			calsky_refraktion( Real Hoehe);
	void			calsky_refraktion( CSonnenstand& input );

/// Implementation

//	Calsky
//------------------------------------------------------------------------------------------
// 							FUNCTIONS
//------------------------------------------------------------------------------------------

// Funktion:	sonnendeklination()
// Parameter:	s32 T = Tag im Jahr [1..365/366]
// Return:		Real Winkel in Bogenmass
//------------------------------------------------------------------------------------------
Real calsky_deklination(Real T)
//------------------------------------------------------------------------------------------
{
	// Deklination der Sonnen in Radians
	// Formula 2008 by Arnold(at)Barmettler.com,
	// fit to 20 Years of avarage declinations (2008-2017)
	return 0.409526325277017 * sin(0.0169060504029192 * (T - 80.0856919827619));

}

// Funktion:	zeitdifferenz()
// Parameter:	Real Deklination
// Parameter:	Real Breitengrad
// Return:		Real in Bruchteilen von Stunden
//------------------------------------------------------------------------------------------
Real calsky_zeitdifferenz(Real Deklination, Real Breitengrad)
//------------------------------------------------------------------------------------------
{
	// Dauer des halben Tagbogens in Stunden:
	// Zeit von Sonnenaufgang (H?he h) bis zum h?chsten Stand im S?den
	Real ergebnis = sin(HOEHE_AUFGANG);
	ergebnis -= sin(Breitengrad)*sin(Deklination);
	ergebnis /= cos(Breitengrad)*cos(Deklination);
	ergebnis = acos(ergebnis);
	ergebnis *= 12.0;
	ergebnis /= core::PI64;
	return ergebnis;
}

// Funktion:	zeitgleichung()
// Parameter:	s32 T = Tag im Jahr [1..365/366]
// Return:		Real in Bruchteilen von Stunden
//------------------------------------------------------------------------------------------
Real calsky_zeitgleichung(Real T)
//------------------------------------------------------------------------------------------
{
	// Differenz zwischen wahrer und mittlerer Sonnenzeit
	// Formula 2008 by Arnold(at)Barmettler.com,
	// fit to 20 Years of avarage equation of time (2008-2017)
	Real ergebnis = 0.0;
	ergebnis -= 0.170869921174742*sin(0.0336997028793971 * T + 0.465419984181394);
	ergebnis -= 0.129890681040717*sin(0.0178674832556871 * T - 0.167936777524864);
	return ergebnis;
}

// Funktion:	aufgang()
// Parameter:	s32 T = Tag im Jahr [1..365/366]
// Return:		Real in Bruchteilen von Stunden
//------------------------------------------------------------------------------------------
Real calsky_aufgang(Real T, Real Breitengrad)
//------------------------------------------------------------------------------------------
{
	Real DK = calsky_deklination(T);
	return 12.0 - calsky_zeitdifferenz(DK, Breitengrad) - calsky_zeitgleichung(T);
}

// Funktion:	untergang()
// Parameter:	s32 T = Tag im Jahr [1..365/366]
// Return:		Real in Bruchteilen von Stunden
//------------------------------------------------------------------------------------------
Real calsky_untergang(Real T, Real Breitengrad)
//------------------------------------------------------------------------------------------
{
	Real DK = calsky_deklination(T);
	return 12.0 + calsky_zeitdifferenz(DK, Breitengrad) - calsky_zeitgleichung(T);
}

// Funktion:	Refraktion()
// Parameter:	Referenz auf Instanz der Klasse hampe::CSonnenstand
// Return:		Referenz auf gleiche Instanz mit ver?ndertem Hoehenwinkel
//------------------------------------------------------------------------------------------
Real calsky_refraktion(Real Hoehe) // Hoehe in Grad!
//hampe::CSonnenstand& Refraktion(hampe::CSonnenstand &input)
//------------------------------------------------------------------------------------------
{
	// N?herungsl?sung f?r die Refraktion der Sonne
	// bei 'Hoehe' ?ber dem mathematischen Horizont
	// Refraktion betr?gt bei Sonnenaufgang 34 Bogenminuten = 0.56667?
	// Falls die H?he der Sonne nicht genauer als auf 0.5? gew?nscht ist,
	// kann diese Funktion ignoriert werden.

	// Umrechnung in Bogenmass
	Hoehe *= core::DEGTORAD64;
	// Real Hoehe = RAD64*input.getHoehe(); // Lokale Kopie, Gradmass]

	Real P=1013.25; // Luftdruck der Standard-Atmosph?re in mbar (hPa)
	Real T=15.0 + 273.15; // Temperatur der Standard-Atmosph?re in Kelvin

	// R?ckgabewert (Default = 0)
	Real R=0.0;

	// (Hoehe>=15?) -> einfache Formel
	if (Hoehe>=15.0*core::DEGTORAD64)
	{
		R += P/T;
		R /= tan(Hoehe); // tan() verlangt Argument in Bogenmass, Ergebnis auch in Bogenmass
		R *= 0.00452;
		// R *= RAD64; // Umwandlung in Bogenmass
	}

	// ( -1? < Hoehe < 15?) -> aufwendigerere (quadratische) Formel
	else if (Hoehe>-1.0*core::DEGTORAD64)
	{
		R += P * (0.1594 + 0.0196*Hoehe + 0.00002*Hoehe*Hoehe);
		R /= T * (1.0000 + 0.5050*Hoehe + 0.08450*Hoehe*Hoehe);
		// R *= RAD64; // Umwandlung in Bogenmass
	}

	return R; // Refraktion im Bogenmass
	// input.setHoehe(input.getHoehe()+R);
	// return input;

}

// Funktion:	Refraktion()
// Parameter:	Referenz auf Instanz der Klasse hampe::CSonnenstand
// Return:		Referenz auf gleiche Instanz mit ver?ndertem Hoehenwinkel
//------------------------------------------------------------------------------------------
void calsky_refraktion( CSonnenstand& input ) // Hoehe in Grad!
//------------------------------------------------------------------------------------------
{
	input.mHoehe += calsky_refraktion(input.mHoehe);
}

} // end namespace calsky

// Funktion:	berechne_nach_vdi2067()
// Parameter:	s32 T = Tag im Jahr [1..365/366]
// Parameter:	Real Breitengrad im Bogenmass
// Parameter:	Real ZeitSeitMittag
// Return:		hampe::CSonnenstand
//------------------------------------------------------------------------------------------
CSonnenstand calsky_sonnenstand(Real T, Real Breitengrad, Real ZeitSeitMittag)
//------------------------------------------------------------------------------------------
{
	// Berechnet Azimut und H?he der Sonne (ohne Refraktion)
	Real DK = calsky::calsky_deklination(T);
	Real sindec = sin(DK);
	Real cosdec = cos(DK);

	// Stundenwinkel seit wahrem Mittag im Bogenmass
	// 1.0027379: Faktor f?r Sternzeitkorrektur
	// 1.0/365.25: Fortschreiten der Rektaszension der Sonne in einem Tag in Grad
	Real stundenwinkel = ZeitSeitMittag*(1.0027379-1.0/365.35)*15.0*core::DEGTORAD64;
	Real sintau = sin(stundenwinkel);
	Real costau = cos(stundenwinkel);
	Real sinlat = sin(Breitengrad);
	Real coslat = cos(Breitengrad);

	Real N = -cosdec * sintau;
	Real D = sindec * coslat - cosdec * costau * sinlat;

	Real jd = core::DateTime::JD(2010,1,0)+T;
	Real Azimut = atan2(N,D);

	// Norden = 0;
	// Osten  = 1*Pi/2;
	// Süden  = 2*Pi/2;
	// Westen = 3*Pi/2;
	if (Azimut < 0.0) Azimut += 2.0*core::PI64;

	// Hoehe des Sonnenmittelpunktes
	Real Hoehe = asin( sindec * sinlat + cosdec * costau * coslat);

	return CSonnenstand( jd, core::RADTODEG64*Azimut, core::RADTODEG64*Hoehe, ESS_CALSKY);
}

} // end namespace astro
} // end namespace irr
