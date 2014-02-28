// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __SUNLIB_CLASS_SUNDATA_H_INCLUDED__
#define __SUNLIB_CLASS_SUNDATA_H_INCLUDED__

#include <irrlicht.h>

#include "../CXMLWriterUTF8.h"

#include "../irrUtils.h"

#include "../irrDateTime.h"

#include "CSonnenstand.h"

#include "Algorithms.h"

#include "CSunCurve.h"

namespace irr{


// -------------------------------------- Class -------------------------------------------------
class CSunData : public IReferenceCounted
{
public:
	/** Default constructor */
	// dont call create
	CSunData( ILogger* logger = 0 );

	/** Value constructor */
	// calls create
	CSunData( s32 year, Real lon, Real lat
		, const core::stringw& location
		, u32 pointsPerDay = 24*60
		, astro::ESS_COMPUTE_METHOD method = astro::ESS_WIKIPEDIA
		, ILogger* logger = 0 );

	/** Destructor */
	//! calls clear
	virtual ~CSunData();

	//! createData
	void createData( s32 year, Real lon, Real lat
		, const core::stringw& location
		, u32 pointsPerDay = 24*60
		, astro::ESS_COMPUTE_METHOD method = astro::ESS_WIKIPEDIA
		, ILogger* logger = 0 );



	//! clear
	void clear();

	//! get number of curves
	virtual u32 getCurveCount() const { return Curves.size(); }

	//! get curve data
	virtual const astro::CSunCurve* getCurve( u32 i ) const
	{
		_IRR_DEBUG_BREAK_IF( i >= Curves.size() );
		return Curves[i];
	}

	virtual astro::CSunCurve* getCurve( u32 i )
	{
		_IRR_DEBUG_BREAK_IF( i >= Curves.size() );
		return Curves[i];
	}

	//! get curve data
	virtual const core::array<astro::CSunCurve*>& getCurveData() const { return Curves; }

	//! get calculation method
	virtual astro::ESS_COMPUTE_METHOD getMethod() const { return Method; }

	//! get number of points per day-curve
	virtual u32 getPointsPerDay() const { return PointsPerDay; }

	//! get full number of stored data-points
	virtual u32 getPointCount() const;

	//! get year
	virtual s32 getYear() const { return Year; }

	//! get geographical longitude ( in degrees )
	virtual f64 getLongitude() const { return Lon; }

	//! get geographical longitude ( in degrees )
	virtual f64 getLatitude() const { return Lat; }

	//! get name of location
	virtual core::stringw getLocation() const { return Loc; }

	//! create a string
	virtual core::stringw toString() const;

	//! create a 'unique' name from internal values
	virtual core::stringw createName() const;

	//! write to XML Stream
	virtual bool write( io::IXMLWriter* xml ) const;

	//! read from XML Stream
	virtual bool read( io::IXMLReaderUTF8* xml );

	//! save to XML or text-file depending on given file-extension (uses UTF-8)
	virtual bool save( const io::path& filename, io::IFileSystem* filesys = 0 ) const;

	//! load from XML or text-file depending on given file-extension (uses UTF-8)
	virtual bool load( const io::path& filename, io::IFileSystem* filesys = 0 );

	//! get bounding data-rect min/max
	virtual core::rectf getBoundingRect() const;

	//! get optimal bounding data-rect for display
	virtual core::rectf getOptimalRect() const;

	//! get approximated first sun height >= 0.0 ( 0.0 < azimuth )
	virtual Real getSunRiseAzimuth() const;

	//! get approximated last sun height >= 0.0 ( 180.0 < azimuth )
	virtual Real getSunDuskAzimuth() const;

	//! get sum of all sun points x n(0,1,0);
//	virtual Real getSunRadiusInMinuteAngle() const;

	//! get sum of all sun points x n(0,1,0);
	virtual Real getGlobalRadiationSum() const;

	//! get sum of all sun points x n(x,y,z);
	virtual Real getGlobalRadiationSumTo( const core::vector3df& plain_normale ) const;

public:
	ILogger* Logger;
	astro::ESS_COMPUTE_METHOD Method;
	u32 PointsPerDay;
	s32 Year;
	f64 Lon;
	f64 Lat;
	core::stringw Loc;
	core::array<astro::CSunCurve*> Curves;

protected:

private:

public:
//	virtual bool renderToImage (
//		gui::IGUIEnvironment* env, const core::rectf& data_rect,
//		video::IImage* dst, const core::recti& pos, ILogger* logger) const;

	static CSunData* create(s32 year, Real lon, Real lat, const core::stringw& location, u32 pointsPerDay, astro::ESS_COMPUTE_METHOD method, ILogger* logger );


};


} // end namespace irr

#endif // __SUNLIB_CLASS_SUNDATA_H_INCLUDED__
