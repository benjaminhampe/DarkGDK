// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXTENSION_COLOR_CONSTANTS_H__
#define __IRR_EXTENSION_COLOR_CONSTANTS_H__

#include <irrlicht.h>

namespace irr
{
	namespace video
	{
		//! standard argb colors
		const SColor SC_Null(0,0,0,0);
		const SColor SC_Transparent = SC_Null;
		const SColor SC_Black(255,0,0,0);
		const SColor SC_White(255,255,255,255);
		const SColor SC_Opaque = SC_White;
		const SColor SC_HalfBlack(127,0,0,0);
		const SColor SC_HalfWhite(127,255,255,255);
		const SColor SC_GhostBlack(64,0,0,0);
		const SColor SC_GhostWhite(64,255,255,255);
		const SColor SC_LightRed(255,255,142,155);
		const SColor SC_DarkRed(255,155,50,50);
		const SColor SC_Red(255,255,0,0);
		const SColor SC_LightGreen(255,107,142,35);
		const SColor SC_DarkGreen(255,0,100,0);
		const SColor SC_Green(255,0,255,0);
		const SColor SC_LightBlue(255,120,173,209);
		const SColor SC_DarkBlue(255,70,130,180);
		const SColor SC_Blue(255,0,0,255);
		const SColor SC_Violett(255,255,0,255);
		const SColor SC_Marin(255,155,200,255);
		const SColor SC_Yellow(255,255,255,0);
		const SColor SC_Orange(255,255,127,30);
		const SColor SC_HL2(255,255,127,30);
		const SColor SC_Sky(255,255,127,30);
		const SColor SC_Sun(255,255,127,30);
		const SColor SC_Venus(255,255,127,30);
		const SColor SC_Moon(255,255,127,30);
		const SColor SC_Mars(255,255,127,30);
		const SColor SC_Saturn(255,255,127,30);

	} // end namespace video

} // end namespace irr


#endif // __IRR_EXTENSION_COLOR_CONSTANTS_H__
