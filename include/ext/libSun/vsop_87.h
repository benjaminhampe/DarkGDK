#ifndef __SUNLIB_HAMPE_VSOP87_H_INCLUDED__
#define __SUNLIB_HAMPE_VSOP87_H_INCLUDED__

	#include <irrTypes.h>
	#include "CSonnenstand.h"

namespace irr{
namespace astro{

	CSonnenstand 		vsop87_sonnenstand(f64 jd, f64 geoL, f64 geoB);

} // end namespace astro
} // end namespace irr
#endif // __SUNLIB_HAMPE_VSOP_H_INCLUDED__

