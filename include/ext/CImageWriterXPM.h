// Copyright (C) 2002-2012 Benjamin Hampe
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef _C_IMAGE_WRITER_XPM_H_INCLUDED__
#define _C_IMAGE_WRITER_XPM_H_INCLUDED__

#ifndef _IRR_COMPILE_WITH_XPM_WRITER_
#define _IRR_COMPILE_WITH_XPM_WRITER_
#endif // _IRR_COMPILE_WITH_XPM_WRITER_

#ifdef _IRR_COMPILE_WITH_XPM_WRITER_

#include "IrrCompileConfig.h"
#include <irrlicht.h>
#include <IImageWriter.h>
#include <SColor.h>
#include "irrMath.h"
//#include "CImageLoaderXPM.h"
//#include "IWriteFile.h"
//#include "CColorConverter.h"
//#include "irrString.h"
#include <../../source/Irrlicht/os.h>
#include <CMath.h>


namespace irr
{
namespace video
{

class CImageWriterXPM : public IImageWriter
{
public:
	//! constructor
	CImageWriterXPM();

	//! return true if this writer can write a file with the given extension
	virtual bool isAWriteableFileExtension(const io::path& filename) const;

	//! write image to file
	virtual bool writeImage(io::IWriteFile *file, IImage *image,u32 param) const;

private:
	static core::stringc valid_chars;

	core::stringc colorIndexToChars( u32 index, u32 bytesPerColor ) const;

	void endLine(io::IWriteFile *file) const;

	struct XPM_Color
	{
		SColor value;
		core::stringc key;
		XPM_Color(const SColor& color, const core::stringc& charCombi)
		: value(color), key(charCombi)
		{}
	};
};

} // namespace video
} // namespace irr

#endif // _IRR_COMPILE_WITH_XPM_WRITER_

#endif // _C_IMAGE_WRITER_XPM_H_INCLUDED__
