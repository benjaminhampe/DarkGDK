// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CSunCurve.h"

#include "../irrDateTime.h"

#include "Algorithms.h"



namespace irr{
namespace astro{

// ----------------------------------- Class Implementation----------------------------------------------------

//	ESSD_CURVE_TYPE CurveType;
//	core::stringw Location;
//	f64 Longitude;
//	f64 Latitude;
//	f64 DateStart;
//	f64 DateEnd;
//	u32 PointsPerDay;
//	ESS_COMPUTE_METHOD Method;
//	f32 LineWidth;
//	video::SColor LineColor;
//	u16 LineStipple;
//	s32 LineFactor;
//	u32 LineMiter;
//	core::array<CSonnenstand> Data;

CSunCurve::CSunCurve(
	ESSD_CURVE_TYPE type, const core::stringw& location, f64 lon, f64 lat, f64 jdStart, f64 jdEnd,
	u32 count, ESS_COMPUTE_METHOD method, f32 lineWidth, const video::SColor& color,
	u16 lineStipple )
: CurveType(type)
, Location(location)
, Longitude(lon)
, Latitude(lat)
, DateStart(jdStart)
, DateEnd(jdEnd)
, Method(method)
, LineWidth(lineWidth)
, LineColor(color)
, LineStipple(lineStipple)
, LineOffset(0)
, LineCap(0)
, LineJoin(0)
, FillColor(0,0,0,0)
{
//	Data = createData( lon, lat, jdStart, jdEnd, count, method );
//
//	core::array<CSonnenstand> createData( Real lon, Real lat, Real jdStart, Real jdEnd, u32 count, ESS_COMPUTE_METHOD method)
//	{
//	core::array<CSonnenstand> data;
	Data.reallocate( count );
	Data.set_used( 0 );

	Real deltaT = (jdEnd-jdStart) / (Real)count;
	Real jdNow = jdStart;

	for (u32 i=0; i<count; i++)
	{
		CSonnenstand s = sonnenstand(jdNow, lon, lat, method);
		// if (s.mHoehe > -1.0)
		Data.push_back( s );
		jdNow += deltaT;
	}
}

CSunCurve::~CSunCurve()
{
	clear();
}

void CSunCurve::clear()
{
	Data.clear();
}

core::stringw CSunCurve::toString() const
{
	core::stringw txt = L"<CSunCurve>\n";
	for (u32 i=0; i<getPointCount(); i++)
	{
		const CSonnenstand& point = Data[i];

		txt += L"\t"; txt += point.toString(); txt += L"\n";
	}
	txt += L"</CSunCurve>\n";
	return txt;
}

// ------------------------------------------------------------------------------------------------------------

bool CSunCurve::write( io::IXMLWriter* xml ) const
{
	if (!xml)
		return false;

	xml->writeComment(L"Container for SunPositions");
	xml->writeLineBreak();

	core::array<core::stringw> AttribNames;
	core::array<core::stringw> AttribValues;

	AttribNames.push_back(L"type");
	AttribNames.push_back(L"loc");
	AttribNames.push_back(L"lon");
	AttribNames.push_back(L"lat");
	AttribNames.push_back(L"date-start");

	AttribNames.push_back(L"date-end");
	AttribNames.push_back(L"points");
	AttribNames.push_back(L"method");
	AttribNames.push_back(L"line-width");
	AttribNames.push_back(L"line-color");

	AttribNames.push_back(L"line-stipple");
	AttribNames.push_back(L"line-offset");
	AttribNames.push_back(L"line-cap");
	AttribNames.push_back(L"line-join");

	AttribValues.push_back( core::stringw(ESSD_CURVE_TYPE_NAMES[(u32)CurveType]) );
	AttribValues.push_back( Location );
	AttribValues.push_back( core::stringw(L"") += Longitude );
	AttribValues.push_back( core::stringw(L"") += Latitude );
	AttribValues.push_back( core::stringw(L"") += DateStart );

	AttribValues.push_back( core::stringw(L"") += DateEnd );
	AttribValues.push_back( core::stringw(L"") += Data.size() );
	AttribValues.push_back( core::stringw(ESS_COMPUTE_METHOD_NAMES[(u32)Method]) );
	AttribValues.push_back( core::stringw(L"") += LineWidth );

	core::stringw s_color("SColor(");
	s_color += LineColor.getAlpha(); s_color += L",";
	s_color += LineColor.getRed(); s_color += L",";
	s_color += LineColor.getGreen(); s_color += L",";
	s_color += LineColor.getBlue(); s_color += L")";

	AttribValues.push_back( s_color );
	AttribValues.push_back( core::stringw(L"") += LineStipple );
	AttribValues.push_back( core::stringw(L"") += LineOffset );
	AttribValues.push_back( core::stringw(L"") += LineCap );
	AttribValues.push_back( core::stringw(L"") += LineJoin );

	xml->writeElement(L"CSunCurve", false, AttribNames, AttribValues);
	xml->writeLineBreak();

	for (u32 i=0; i<Data.size(); i++)
	{
		Data[i].write( xml );
	}

	xml->writeClosingTag(L"CSunCurve");
	xml->writeLineBreak();
	return true;
}


} // end namespace astro
} // end namespace irr

