// Copyright (C) 2002-2012 Nikolaus Gebhardt, Benjamin Hampe
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_IMAGE_LOADER_XPM_H_INCLUDED__
#define __C_IMAGE_LOADER_XPM_H_INCLUDED__

#include "IrrCompileConfig.h"

#define _IRR_COMPILE_WITH_XPM_LOADER_

#ifndef _IRR_COMPILE_WITH_XPM_DEBUG_OUTPUT_
#define _IRR_COMPILE_WITH_XPM_DEBUG_OUTPUT_
#endif // _IRR_COMPILE_WITH_XPM_DEBUG_OUTPUT_

#ifdef _IRR_COMPILE_WITH_XPM_LOADER_

//#include "IReadFile.h"
//#include "os.h"
//#include "CColorConverter.h"
//#include "CImage.h"
//#include "irrString.h"

#include <irrTypes.h>
#include <irrArray.h>
#include <irrString.h>
#include <IReadFile.h>
#include <iso646.h>
#include <IImageLoader.h>
#include <SColor.h>
#include <../../source/Irrlicht/os.h>
#include <../../source/Irrlicht/CColorConverter.h>
#include <../../source/Irrlicht/CImage.h>

#if defined(_IRR_COMPILE_WITH_XPM_DEBUG_OUTPUT_)
	#include <iostream>
	#include <fstream>
#endif

namespace irr
{
namespace video
{

/* XPM */
const irr::c8* const irr_xpm[] = {
"16 16 6 1",
" 	c None",
".	c #FFFFFF",
"+	c #000000",
"@	c #9A9A9A",
"#	c #FEFEFE",
"$	c #F7F7F7",
"................",
"................",
"................",
"................",
"..++............",
"..++............",
"..++..++++.++++.",
"..++..++@#.++@#.",
"..++..++$..++$..",
"..++..++...++...",
"..++..++...++...",
"..++..++...++...",
"................",
"................",
"................",
"................"};

//! creates a loader which is able to load tgas
IImageLoader* createImageLoaderXPM();

class CImageLoaderXPM : public IImageLoader
{
public:

	//! returns true if the file maybe is able to be loaded by this class
	//! based on the file extension (e.g. ".tga")
	virtual bool isALoadableFileExtension(const io::path& filename) const;

	//! returns true if the file maybe is able to be loaded by this class
	virtual bool isALoadableFileFormat(io::IReadFile* file) const;

	//! creates a surface from the file
	virtual IImage* loadImage(io::IReadFile* file) const;

private:
	struct XPM_Color
	{
		core::stringc key;
		SColor value;
		XPM_Color(const core::stringc& colorKey, const SColor& colorValue)
		: key(colorKey), value(colorValue)
		{}
	};
};

} // end namespace video
} // end namespace irr

#endif // _IRR_COMPILE_WITH_XPM_LOADER_

#endif

