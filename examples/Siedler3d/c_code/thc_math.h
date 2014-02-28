// thc_math.h

#ifndef __THC_MATH_H_INCLUDED__
#define __THC_MATH_H_INCLUDED__

	const float PI = 3.14159265f;
	const float DEGTORAD = PI/180.0f;
	const float RADTODEG = 180.0f/PI;

namespace thc
{
	int Round(float zahl);
	float WrapAngle(float winkel);
	float RotateX_2D(const float& x, const float& y, const float& winkel);
	float RotateY_2D(const float& x, const float& y, const float& winkel);

}

#endif