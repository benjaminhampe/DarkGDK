// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __SUNLIB_HAMPE_CLASS_SONNENSTAND_H_INCLUDED__
#define __SUNLIB_HAMPE_CLASS_SONNENSTAND_H_INCLUDED__

#include <irrlicht.h>

#include "../irrDateTime.h"

namespace irr{
namespace astro{

	// ----------------------------------- Enumeration ----------------------------------------------
    enum ESSD_TYPE
	{
		ESSDT_CARTESIAN=0, // pretty print DIN-A4 { dataRect min0-5° < x < max0+5°, 0° < y < 90° } with equaly sized cells fom beyond max of data
		ESSDT_POLAR,	   // polar projection
		ESSDT_INDICATOR,   // cylindric projection
  		ESSDT_POINT_CLOUD, // for debugging purposes
	//	ESSDT_LINES,
		ESSDT_COUNT
	};

	// ----------------------------------- Strings ----------------------------------------------
    const c8* const ESSD_TYPE_NAMES[] =
	{
		"ESSDT_CARTESIAN", "ESSDT_POLAR", "ESSDT_INDICATOR", "ESSDT_POINT_CLOUD", "ESSDT_LINES", "ESSDT_COUNT"
	};

	// ----------------------------------- Enumeration ----------------------------------------------
	enum ESS_COMPUTE_METHOD
	{
		ESS_WIKIPEDIA=0,
		ESS_QUASCHNING,
		ESS_CALSKY,
		ESS_PSA,
		ESS_NREL,
		ESS_VDI2067,
		ESS_VSOP,
		ESS_VSOP87,
		ESS_CALSKY_ONLINE,
		ESS_COUNT
	};

	// ----------------------------------- Enumeration ----------------------------------------------
	const c8* const ESS_COMPUTE_METHOD_NAMES[] =
	{
		"ESS_WIKIPEDIA", "ESS_QUASCHNING", "ESS_CALSKY", "ESS_PSA", "ESS_NREL",
		"ESS_VDI2067", "ESS_VSOP", "ESS_VSOP87", "ESS_CALSKY_ONLINE", "ESS_COUNT"
	};

	// -------------------------------------- Class -------------------------------------------------
	class CSonnenstand
	{
	public:
		CSonnenstand( );

		CSonnenstand( Real jd, Real azimut, Real hoehe, ESS_COMPUTE_METHOD method = ESS_WIKIPEDIA );

		CSonnenstand(const CSonnenstand& other);

		virtual ~CSonnenstand();

		virtual CSonnenstand& operator= (const CSonnenstand& other);

		virtual core::stringc toString( s32 decimals = -1 ) const;

		virtual core::stringc toXML() const;

		virtual bool read( io::IXMLReader* xml );

		virtual bool write( io::IXMLWriter* xml ) const;

		virtual bool operator== (const CSonnenstand& other) const;

		virtual bool operator!= (const CSonnenstand& other) const;

		virtual bool operator> (const CSonnenstand& other) const;

		virtual bool operator< (const CSonnenstand& other) const;

		virtual bool operator>= (const CSonnenstand& other) const;

		virtual bool operator<= (const CSonnenstand& other) const;
//		core::stringc str( bool bPrintDate = true, bool bPrintTime = true, bool bPrintZone = true ) const;

//		static core::vector2d<Real> projectVectorCartesian(
//			const core::vector2d<Real>& pos,
//			const core::rect<Real> bbox,
//			const core::rect<Real> viewport);

		virtual core::position2di projectCartesian2di( const core::rectf& data_rect, const core::recti& image_rect, bool invert_y = true) const;

		virtual core::position2df projectCartesian2df( const core::rectf& data_rect, const core::rectf& world_rect, bool invert_y = true) const;

	public:
		Real mJD, mAzimut, mHoehe;
		ESS_COMPUTE_METHOD mMethod;
	};

} // end namespace astro
} // end namespace irr

#endif	// __SUNLIB_HAMPE_CLASS_SONNENSTAND_H_INCLUDED__
