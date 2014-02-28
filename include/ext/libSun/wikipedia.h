#ifndef __SUNLIB_HAMPE_WIKIPEDIA_H_INCLUDED__
#define __SUNLIB_HAMPE_WIKIPEDIA_H_INCLUDED__

#include <irrTypes.h>
#include "CSonnenstand.h"

namespace irr{
namespace astro{

/// Wikipedia
CSonnenstand wikipedia_sonnenstand(Real jd, Real lon, Real lat);

} // end namespace astro
} // end namespace irr

#endif // __SUNLIB_HAMPE_WIKIPEDIA_H_INCLUDED__

