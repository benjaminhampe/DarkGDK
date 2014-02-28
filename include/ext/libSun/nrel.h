// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __SUNLIB_HAMPE_NREL_H_INCLUDED__
#define __SUNLIB_HAMPE_NREL_H_INCLUDED__

/*============================================================================
*
*    NAME:  nrel.h
*
*    Contains:
*        S_solpos     (computes the solar position and intensity
*                      from time and place)
*            INPUTS:     (from posdata)
*                          year, month, day, hour, minute, second,
*                          latitude, longitude, timezone, interval
*            OPTIONAL:   (from posdata; defaults from S_init function)
*                            press   DEFAULT 1013.0 (standard pressure)
*                            temp    DEFAULT   10.0 (standard temperature)
*                            tilt    DEFAULT    0.0 (horizontal panel)
*                            aspect  DEFAULT  180.0 (South-facing panel)
*                            sbwid   DEFAULT    7.6 (shadowband width)
*                            sbrad   DEFAULT   31.7 (shadowband radius)
*                            sbsky   DEFAULT   0.04 (shadowband sky factor)
*
*            OUTPUTS:    (posdata) daynum, amass, ampress, azim, cosinc,
*                        elevref, etr, etrn, etrtilt, prime,
*                        sbcf, sretr, ssetr, unprime, zenref
*
*            RETURNS:   Long int status code (defined in solpos.h)
*
*    Usage:
*         In calling program, along with other 'includes', insert:
*
*              #include "solpos.h"
*
*    Martin Rymes
*    National Renewable Energy Laboratory
*    25 March 1998
*----------------------------------------------------------------------------*/

#include <irrTypes.h>
#include "CSonnenstand.h"

namespace irr{
namespace astro{

    CSonnenstand nrel_sonnenstand(f64 mJD, f64 geoL, f64 geoB);

} // end namespace astro
} // end namespace irr

#endif // __SUNLIB_HAMPE_NREL_H_INCLUDED__
