#include "vsop_87.h"

#include <irrTypes.h>
#include <irrMath.h>
#include "../irrDateTime.h"
#include "CSonnenstand.h"

#include "vsop.h"

namespace irr{
namespace astro {

CSonnenstand vsop87_sonnenstand(f64 jd, f64 geoL, f64 geoB)
{
	return vsop_sonnenstand( jd, geoL, geoB);
}

} // end namespace astro
} // end namespace irr
