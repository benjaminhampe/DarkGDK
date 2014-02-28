// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef IRR_EXT_RENDER_BIG_IMAGES_H_INCLUDED
#define IRR_EXT_RENDER_BIG_IMAGES_H_INCLUDED

#include <irrlicht.h>

namespace irr
{
namespace video
{

bool renderToImage(
    IrrlichtDevice* device,
    IImage* dst,
    s32 nSamples = 1,
    const SColor& clearColor = SColor(0,0,0,0),
    bool renderGUI = false,
    bool debugLog = false);

bool blitImageToImage(
	IImage* dst,
	core::position2di dstPos,
	IImage* src,
	const core::recti& srcRect,
	bool debugLog = false );

} // end namespace video
} // end namespace irr
#endif
