// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __SUNLIB_CLASS_SUNCURVE_H_INCLUDED__
#define __SUNLIB_CLASS_SUNCURVE_H_INCLUDED__

#include <irrTypes.h>

#include "CSonnenstand.h"

namespace irr{
namespace astro{

// ----------------------------------- Enumeration ----------------------------------------------
enum ESSD_CURVE_TYPE
{
	ESSD_CURVE_NORMAL,
	ESSD_CURVE_ANALEMMA
};

// ----------------------------------- Strings ----------------------------------------------
const c8* const ESSD_CURVE_TYPE_NAMES[] =
{
	"ESSD_CURVE_NORMAL", "ESSD_CURVE_ANALEMMA", "ESSD_CURVE_TYPE_COUNT"
};

// -------------------------------------- Class -------------------------------------------------
class CSunCurve : public IReferenceCounted
{
public:
	CSunCurve( ESSD_CURVE_TYPE type, const core::stringw& location, f64 lon, f64 lat, f64 jdStart, f64 jdEnd,
		u32 count, ESS_COMPUTE_METHOD method, f32 lineWidth = 1.0f, const video::SColor& color = video::SColor(255,0,0,0),
		u16 lineStipple = 0xFFFF);

	virtual ~CSunCurve();

	void clear();

	void create( ESSD_CURVE_TYPE type, const core::stringw& location, f64 lon, f64 lat, f64 jdStart, f64 jdEnd,
		u32 count, ESS_COMPUTE_METHOD method, f32 lineWidth = 1.0f, const video::SColor& color = video::SColor(255,0,0,0),
		u16 lineStipple = 0xFFFF);

	//! get number of points per day-curve
	virtual u32 getPointCount() const { return Data.size(); }

	//! get point by index
	virtual CSonnenstand& getPoint( u32 index )
	{
		_IRR_DEBUG_BREAK_IF( Data.size()==0 );
		_IRR_DEBUG_BREAK_IF( index >= Data.size() );
		return Data[index];
	}

	//! get point by index
	virtual const CSonnenstand& getPoint( u32 index ) const
	{
		_IRR_DEBUG_BREAK_IF( Data.size()==0 );
		_IRR_DEBUG_BREAK_IF( index >= Data.size() );
		return Data[index];
	}

	//! get curve-type
	virtual ESSD_CURVE_TYPE getCurveType() const { return CurveType; }

	//! get location-name
	virtual core::stringw getLocation() const { return Location; }

	//! get longitude ( in degrees )
	virtual f64 getLongitude() const { return Longitude; }

	//! get latitude ( in degrees )
	virtual f64 getLatitude() const { return Latitude; }

	//! get date-start in juliandaynumber
	virtual f64 getDateStart() const { return DateStart; }

	//! get date-end in juliandaynumber
	virtual f64 getDateEnd() const { return DateEnd; }

	//! get calculation-method
	virtual ESS_COMPUTE_METHOD getMethod() const { return Method; }

	//! get line-width
	virtual f32 getLineWidth() const { return LineWidth; }

	//! get line-color
	virtual video::SColor getLineColor() const { return LineColor; }

	//! get line-stipple pattern
	virtual u16 getLineStipple() const { return LineStipple; }

	//! get line-offset
	virtual s32 getLineOffset() const { return LineOffset; }

	//! get line-cap
	virtual u32 getLineCap() const { return LineCap; }

	//! get line-join
	virtual u32 getLineJoin() const { return LineJoin; }

	//! get fill-color
	virtual video::SColor getFillColor() const { return FillColor; }

	//! get raw data-string
	virtual core::stringw toString() const;

	virtual Real getSunRiseAzimuth() const
	{
		Real min_azimuth = 360.0;


		for (u32 i=0; i<Data.size(); i++)
		{
			if ( Data[i].mHoehe > 0 && Data[i].mAzimut < min_azimuth )
			{
				min_azimuth = Data[i].mAzimut;
			}
		}

		return min_azimuth;
	}

	virtual Real getSunDuskAzimuth() const
	{
		Real max_azimuth = 0.0;

		for (u32 i=0; i<Data.size(); i++)
		{
			if ( Data[i].mHoehe > 0 && Data[i].mAzimut > max_azimuth )
			{
				max_azimuth = Data[i].mAzimut;
			}
		}

		return max_azimuth;
	}

	//! write formatted to xml
	virtual bool write( io::IXMLWriter* xml ) const;

	//! get bounding-rect of contained data-points min/max
	virtual core::rectf getBoundingRect() const
	{
		core::rectf b( FLT_MAX, FLT_MAX, FLT_MIN, FLT_MIN );
		u32 pointCount = getPointCount();
		for (u32 p=0; p<pointCount; p++)
		{
			const astro::CSonnenstand& s = Data[p];
			if (b.UpperLeftCorner.X > s.mAzimut )
			{
				b.UpperLeftCorner.X = s.mAzimut;
			}
			if (b.UpperLeftCorner.Y > s.mHoehe )
			{
				b.UpperLeftCorner.Y = s.mHoehe;
			}

			if (b.LowerRightCorner.X < s.mAzimut )
			{
				b.LowerRightCorner.X = s.mAzimut;
			}
			if (b.LowerRightCorner.Y < s.mHoehe )
			{
				b.LowerRightCorner.Y = s.mHoehe;
			}
		}
		return b;
	}


private:
	ESSD_CURVE_TYPE CurveType;
	core::stringw Location;
	f64 Longitude;
	f64 Latitude;
	f64 DateStart;
	f64 DateEnd;
	ESS_COMPUTE_METHOD Method;

	f32 LineWidth;
	video::SColor LineColor;
	u16 LineStipple;
	s32 LineOffset;
	u32 LineCap;
	u32 LineJoin;

	video::SColor FillColor;

	core::array<CSonnenstand> Data;
};

} // end namespace astro
} // end namespace irr

#endif // __SUNLIB_CLASS_SUNCURVE_H_INCLUDED__
