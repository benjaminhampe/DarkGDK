#ifndef __SUNLIB_HAMPE_VDI2067_H_INCLUDED__
#define __SUNLIB_HAMPE_VDI2067_H_INCLUDED__

#include <irrTypes.h>
#include "CSonnenstand.h"

namespace irr{
namespace astro{

	CSonnenstand vdi2067_sonnenstand( Real jdMEZ, Real lon, Real lat, bool bLog = false );

} // end namespace astro
} // end namespace irr

#endif // __SUNLIB_HAMPE_VDI2067_H_INCLUDED__

