#include "wikipedia.h"

#include "../irrUtils.h"

#include "../irrDateTime.h"

#include "CSonnenstand.h"



namespace irr{
namespace astro{


//	Wikipedia
CSonnenstand wikipedia_sonnenstand(Real jd, Real lon, Real lat)
{
	// Ekliptikalkoordinaten der Sonne
	const Real j2000 = 2451545.0;
	const Real n = jd-j2000;

	Real L = 280.460 + 0.9856474 * n;
	Real g = 357.528 + 0.9856003 * n;

	// clip angles to 0°..359° intervall
	L=core::Math::WrapAngle<Real>(L);
	g=core::Math::WrapAngle<Real>(g);

	const Real bg = g*core::DEGTORAD64;

	// Ekliptikale Länge
//	Real excentricity = 0.0167;
//	Real A = L + (2e * sin(g) + 5*e*e/4 sin(2g) ) * 180 / pi;

	// Real A = L + 1.915 * sin(core::DEGTORAD64*g) + 0.020 * sin(2.0*core::DEGTORAD64*g);
	const Real bA = L + 1.915 * sin(bg) + 0.020 * sin(2.0*bg);
	//const Real bA = A;

	// Äquatorialkoordinaten
	Real epsilon = 23.439 - 0.0000004 * n;
	// unknown correction
	epsilon = core::Math::WrapAngle180(epsilon);

	const Real be = epsilon*core::DEGTORAD64;

	const Real deklination = core::RADTODEG64*asin(sin(be)*sin(bA));

	Real alpha = core::RADTODEG64*atan(cos(be)*tan(bA));

// unknown correction
	if (cos(bA)<0.0)
		alpha += 180.0;

	// Horizontalkoordinaten: Azimut, H?he
	Real jD0 = (Real)floor(jd)+0.5; //JD(year,month,day,0,0,0);//JD(year,month,day,0,0,0);
	Real T0 = (jD0-j2000)/36525.0;
	Real Sternzeit = 6.697376 + 2400.05134 * T0 + 1.002738*24.0*(Real)core::Math::FPart(jd+0.5);
	Real Sternzeit2 = Sternzeit - (Real)floor(Sternzeit/24.0)*24.0;
	Real Stundenwinkel = Sternzeit2 * 15.0;
	Real StundenwinkelFruehling = Stundenwinkel + lon;
	Real tau = StundenwinkelFruehling - alpha;

	// Berechnung Azimut
	const Real bt = core::DEGTORAD64*tau;
	const Real bl = core::DEGTORAD64*lat;
	const Real bd = core::DEGTORAD64*deklination;

	Real nenner = cos(bt)*sin(bl) - tan(bd)*cos(bl);
	Real Azimut = core::RADTODEG64*atan2(nenner, sin(bt));
//	Real Azimut = core::RADTODEG64*atan(sin(bt)/nenner);
//	if (nenner < (Real)0)
//		Azimut += (Real)180;

//	Azimut=core::Math::WrapAngle180(Azimut);

	// Berechnung Hoehe
	Real Hoehe = cos(bd)*cos(bt)*cos(bl) + sin(bd)*sin(bl);
	Hoehe = core::RADTODEG64*asin(Hoehe);

	// Korrektur wegen Refraktion
	Real R = core::RADTODEG64*(1.02/tan( core::DEGTORAD64*(Hoehe+(10.3/Hoehe+5.11))));
	Real HoeheR = Hoehe + R/60.0;

//	if (log)
//	{
//		o<<L"<pre>\n"
//			<<L"Wikipedia CSonnenstand ["
//			<<L"jd="<<jd<<L", "
//			<<toStringGeoB(lat)<<L", "
//			<<toStringGeoL(lon)<<L"]\n"
//			<<L"\n"
//			<<L"n="<<n<<L"\n"
//			<<L"L="<<L<<L"\n"
//			<<L"g="<<g<<L"\n"
//			<<L"L="<<L<<L"\n"
//			<<L"g="<<g<<L"\n"
//			<<L"A="<<A<<L"\n"
//			<<L"epsilon="<<epsilon<<L"\n"
//			<<L"alpha="<<alpha<<L"\n"
//			<<L"deklination="<<deklination<<L"\n"
//			<<L"jd0="<<jD0<<L"\n"
//			<<L"T0="<<T0<<L"\n"
//			<<L"Sternzeit="<<Sternzeit<<L"\n"
//			<<L"Sternzeit2="<<Sternzeit2<<L"\n"
//			<<L"Stundenwinkel="<<Stundenwinkel<<L"\n"
//			<<L"StundenwinkelFruehling="<<StundenwinkelFruehling<<L"\n"
//			<<L"tau="<<tau<<L"\n"
//			<<L"Azimut="<<Azimut<<L"\n"
//			<<L"Azimut="<<Azimut<<L"\n"
//			<<L"Hoehe="<<Hoehe<<L"\n"
//			<<L"R="<<R<<L"\n"
//			<<L"HoeheR="<<HoeheR<<L"\n"
//			<<L"</pre>\n";
//	}
//	Azimut+=180.0;
//	while (Azimut > 360.0)
//	{
//		Azimut -= 360.0;
//	}
//	while (Azimut < 0.0)
//	{
//		Azimut += 360.0;
//	}
//	Azimut += 180.0f;


	return CSonnenstand(jd,Azimut,HoeheR,ESS_WIKIPEDIA);

}

} // end namespace astro
} // end namespace irr
