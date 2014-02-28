// thc_math.cpp

#include "thc_math.h"
#include <math.h>

namespace thc
{
	int Round(float zahl)
	{
		float rest=zahl-(int)zahl;
		int erg;
		if (rest>=0.5f)
		{
			erg=(int)zahl+1;
		}
		else
		{
			erg=(int)zahl;
		}
		return erg;
	}
	float WrapAngle(float winkel)
	{
		float angle=winkel;
		while (angle<0.0f)
		{
			angle += 360.0f;
		}
		while (angle>=360.0f)
		{
			angle -= 360.0f;
		}
		return angle;		
	}
	float RotateX_2D(const float& x, const float& y, const float& winkel)
	{
	 		 const float bogen=winkel*DEGTORAD; 
			 return (float)cos(bogen)*x-(float)sin(bogen)*y;
	}
	float RotateY_2D(const float& x, const float& y, const float& winkel)
	{
	 		 const float bogen=winkel*DEGTORAD;
			 return (float)sin(bogen)*x+(float)cos(bogen)*y;
	}
}