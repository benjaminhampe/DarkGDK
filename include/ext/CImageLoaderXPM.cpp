// Copyright (C) 2002-2012 Benjamin Hampe
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include <CImageLoaderXPM.h>

#ifdef _IRR_COMPILE_WITH_XPM_LOADER_

namespace irr
{
namespace video
{

//! creates a loader which is able to load tgas
IImageLoader* createImageLoaderXPM()
{
	return new CImageLoaderXPM();
}

//! returns true if the file maybe is able to be loaded by this class
//! based on the file extension (e.g. ".tga")
bool CImageLoaderXPM::isALoadableFileExtension(const io::path& filename) const
{
	return core::hasFileExtension ( filename, "tga" );
}

//! returns true if the file maybe is able to be loaded by this class
bool CImageLoaderXPM::isALoadableFileFormat(io::IReadFile* file) const
{
	if (!file)
		return false;

	return true;
}

//! creates a surface from the file
IImage* CImageLoaderXPM::loadImage(io::IReadFile* file) const
{
#if defined(__WITH_XPM_DEBUG_OUTPUT__)
	os::Printer::log("CImageLoaderXPM::loadImage()...", ELL_INFORMATION);
#endif

	// abort
	if (!file)
	{
		os::Printer::log("Could not open file.", ELL_ERROR);
		return 0;
	}

	// get file size in bytes
	const u32 fileSize = file->getSize();

	// abort
	if (fileSize == 0)
	{
		os::Printer::log("Invalid file-size.", ELL_ERROR);
		return 0;
	}

	// create memory buffer for file
	c8* bytes = new c8[fileSize];

	// abort
	if (!bytes)
	{
		os::Printer::log("Could not allocate buffer.", ELL_ERROR);
		return 0;
	}

	// just to make sure
	file->seek( 0 );

	// begin reading
	const u32 charCount = file->read(bytes, fileSize);

	if (charCount != fileSize)
	{
		os::Printer::log("Could not read all bytes, may result in corrupted image.", ELL_WARNING);
	}

	// copy buffer to string, delete buffer
	core::stringc irrStr = bytes;
	delete [] bytes;

	// split string on line-end characters '\r' and '\n', skip empty lines
	core::array< core::stringc > lines;
	irrStr.split( lines, "\r\n", 2, true, false);

#if defined(__WITH_XPM_DEBUG_OUTPUT__)
	os::Printer::log( core::sprintf("File has %i lines.", lines.size()).c_str(), (lines.size()<2)?ELL_ERROR:ELL_NONE);
#endif

	// purge all unwanted white-space chars at beginning and end of lines
	for (u32 line = 0; line<lines.size(); line++)
	{
		lines[line].trim();
	}

	// remove all C-Style comments the quick way //, /* /**, ///, //! -> just erase all lines starting with '/'
	u32 line = 0;
	while (line < lines.size())
	{
		if (lines[line].size()>0)
		{
			if (lines[line][0]=='/')
			{
				lines.erase(line,1);
				line--;
			}
		}
		else
		{
			lines.erase(line,1);
			line--;
		}
		line++;
	}

	// --> now the data is most likely pure XPM-image data

/////////////////////////////////////////////////////////////////////////////////
//
//
//
/////////////////////////////////////////////////////////////////////////////////

	// infos to extract from data
	IImage* result = 0;

	// locals
	core::array< XPM_Color > xpmColors; // final array containing all unique colors and their ascii combination
	core::stringc xpmName, xpmColorKey, xpmColorType, xpmColorValue;
	c8 xpmNameBuf[1024];	memset(xpmNameBuf, 0, 1024);
	u32 xpmWidth, xpmHeight, xpmColorCount, xpmBytesPerColor;
	u32 x=0, y=0;	// current pixel position
	core::stringc s; // s=current-line-string
	s32 i=0, p=0;	 // i=current-line-index, p = position of a char within current line
	u8 CurrentState = 0;






	while ( i < (s32)lines.size() )
	{
		s = lines[i]; // copy current line in work-string

		// extract name
		if (i==0)
		{
			sscanf(s.c_str(), "static const char *const %s[] = {", xpmNameBuf);
		}
		// extract header
		else if (i==1)
		{
			sscanf(s.c_str(), "\"%i %i %i %i\",", &xpmWidth, &xpmHeight, &xpmColorCount, &xpmBytesPerColor);
		}
		// extract colors & pixels
		else
		{
			// extract colors
			if (CurrentState == 0)
			{
				p = s.findFirst('\"');
				if (p==-1)
					p=0;

				xpmColorKey = s.subString(p, xpmBytesPerColor, false);
				p+=xpmBytesPerColor;
				s = s.subString(p, s.size()-p-1, false);

				c8 xpmColorTypeBuf[8];
				c8 xpmColorValueBuf[8];

				sscanf(s.c_str(), " %s %s\",", xpmColorTypeBuf, xpmColorValueBuf);

				xpmColorType = xpmColorTypeBuf;
				xpmColorValue = xpmColorValueBuf;
				xpmColorType.trim();
				xpmColorValue.trim();
				xpmColorType.make_lower();
				xpmColorValue.make_lower();

//				if (xpmColorType != core::stringc("c"))
//					os::Printer::log( core::sprintf("Could not determine color-type %s.", xpmColorType.c_str()).c_str(), ELL_WARNING);

				if (xpmColorValue == core::stringc("none"))
				{
					xpmColors.push_back( XPM_Color(xpmColorKey, SColor(0,0,0,0)) );
				}
				else
				{
					if (xpmColorValue.size()>=7)
					{
						u32 r(0),g(0),b(0);
						sscanf( xpmColorValue.c_str(), "#%02x%02x%02x", &r, &g, &b);
						xpmColors.push_back( XPM_Color(xpmColorKey, SColor(255,r,g,b)) );
					}
					else
					{
						// os::Printer::log( core::sprintf("Could not read color-value %s.", xpmColorValue.c_str()).c_str(), ELL_WARNING);
						os::Printer::log( "Could not read color-value.", ELL_WARNING);
					}
				}

				if (( i-2 >= (s32)xpmColorCount) || (xpmColors.size() >= xpmColorCount))
				{
					result = new CImage(ECF_A8R8G8B8, core::dimension2du(xpmWidth, xpmHeight));
					if (!result)
						break;
					result->fill(0);
					CurrentState++;
				}

			}
			// extract pixels
			else if (CurrentState == 1)
			{
				if ( y >= result->getDimension().Height)
					break;

				p = s.findFirst('\"');
				if (p==-1)
					p=0;
				else
					p++;
				x=0;

				while (x < result->getDimension().Width)
				{
					core::stringc key = s.subString(p, xpmBytesPerColor, false);

					bool found = false;
					u32 index=0;
					while (index<xpmColors.size())
					{
						if (key == xpmColors[index].key)
						{
							found = true;
							break;
						}
						index++;
					}

					if (found)
					{
						result->setPixel(x,y,xpmColors[index].value);
					}

					p += xpmBytesPerColor;
					x++;
				}
				y++;
			}
			else
			{
				break;
			}
		}
		i++;
	}
	return result;
}

} // end namespace video
} // end namespace irr

#endif // _IRR_COMPILE_WITH_XPM_LOADER_
