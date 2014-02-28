// Copyright (C) 2002-2012 Nikolaus Gebhardt, Benjamin Hampe
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include <CImageWriterXPM.h>

#ifdef _IRR_COMPILE_WITH_XPM_WRITER_

namespace irr
{
namespace video
{

IImageWriter* createImageWriterXPM()
{
	return new CImageWriterXPM;
}

CImageWriterXPM::CImageWriterXPM()
{
#ifdef _DEBUG
	setDebugName("CImageWriterXPM");
#endif
}

bool CImageWriterXPM::isAWriteableFileExtension(const io::path& filename) const
{
	return (core::hasFileExtension( filename, "xpm" ) ||
			core::hasFileExtension( filename, "h") ||
			core::hasFileExtension( filename, "hpp") ||
			core::hasFileExtension( filename, "txt"));
}

void CImageWriterXPM::endLine(io::IWriteFile *file) const
{
	#if defined(_IRR_WINDOWS_API_)
		file->write("\r\n",2 );
	#elif defined(_IRR_POSIX_API_)
		file->write("\n",1 );
	#else
		file->write("\r",1 );
	#endif
}

//void CImageWriterXPM::writeString(io::IWriteFile *file, const core::stringc& txt)
//{
//	file->write( txt.c_str(), txt.size() );
//}

core::stringc CImageWriterXPM::valid_chars = " .+@#$%&*=-;>,')!~{]^/(_:<[}|1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`";


core::stringc CImageWriterXPM::colorIndexToChars( u32 index, u32 bytesPerColor ) const
{
	core::stringc result;

	u32 i = index;
	c8* buf = new c8[bytesPerColor];
	u32 byteIndex = 0;

	while (byteIndex < bytesPerColor)
	{
		i = index / core::Math::s32_pow( valid_chars.size(), bytesPerColor - byteIndex );
		buf[ bytesPerColor - byteIndex - 1 ] = valid_chars[ i%valid_chars.size() ];
		byteIndex++;
	}

	result = buf;
	delete [] buf;
	return result;
}


bool CImageWriterXPM::writeImage(io::IWriteFile *file, IImage *image,u32 param) const
{
	// abort
	if (!file)
		return false;

	if (!image)
		return false;

	// size of source-image
    core::dimension2du Size = image->getDimension();

    // abort
    if (Size == core::dimension2du(0,0))
        return false;

	// create array to hold all unique RGB colors
    core::array< XPM_Color > colors(Size.Width*Size.Height);
    colors.set_used(0);

	// loop image and find all unique colors
    for (u32 y=0; y<Size.Height; y++)
    {
        for (u32 x=0; x<Size.Width; x++)
        {
        	// get color
            SColor color = image->getPixel(x,y);

            // set alpha const to 255
            color.setAlpha(255);

            // loop color array to see if color already stored
            bool found = false;
            for (u32 i=0; i<colors.size(); i++)
            {
                if (colors[i].value == color)
                {
                    found = true;
                    break;
                }
            }

            // if not found in array, color is unique --> store
            if (!found)
            {
            	XPM_Color data(color,"");
                colors.push_back(data);
            }
        }
    }

	// calculate needed bytes to store one color
	u32 bytesPerColor = 1;
	u32 k = colors.size();
	while (k>=valid_chars.size())
	{
		k/=valid_chars.size();
		bytesPerColor++;
	}

	// now give every unique color a corresponding byte-combination out of valid_chars
	u32 c=0;
	while ( c < colors.size() )
	{
		colors[c].key = colorIndexToChars(c, bytesPerColor);
		c++;
	}

	// fileName
	core::stringc fileName = file->getFileName();
	fileName.make_lower();
	fileName.replace('\\','/');

	// fileBaseName erase path
	core::stringc fileBaseName = fileName;
	s32 pos = fileBaseName.findLast('/');
	if (pos != -1)
	{
		fileBaseName = fileBaseName.subString(pos+1, fileBaseName.size()-(pos+1));
	}

	// fileBaseName erase extension
	pos = fileBaseName.findLast('.');
	if (pos != -1)
	{
		fileBaseName = fileBaseName.subString(0,pos);
	}

	// XPM-Header
	// static const char *const wxwin32x32_xpm[] = {
	// "32 32 407 2",
	// "  	c None",

	// /* XPM */
	file->write("/* XPM */",9);
	endLine(file);

	// static const char *const wxwin32x32_xpm[] = {
	core::stringc s;
	s="static const char *const "; s+=fileBaseName; s+="_xpm[] = {";
	file->write(s.c_str(),s.size() );
	endLine(file);

	// "32 32 407 2"
	// Breite des Bildes (in Pixel)
	// Höhe des Bildes (in Pixel)
	// Anzahl der Farben im Bild
	// Anzahl der Zeichen pro Pixelwert
	// (X-Position des „Hotspots") --> MausCursor
	// (Y-Position des „Hotspots") --> MausCursor
	s="\""; s+=image->getDimension().Width;
	s+=" "; s+=image->getDimension().Height;
	s+=" "; s+=colors.size();
	s+=" "; s+=bytesPerColor; s+="\",";
	file->write(s.c_str(),s.size() );
	endLine(file);

	// write color-table
	// "  	c None",
	// ". 	c #7373C1",
	// "+ 	c #6E6EBF",
	// "@ 	c #6B6BBF",
	// "# 	c #6868BF",
	// "$ 	c #6464BF",
	// "Z+	c #FF4A4A",
	// "`+	c #FF4545",
	// " @	c #E73535",
	// "`@	c #B8B819",
	// " #	c #B7B717",
	// "0#	c #C50000",

	for (u32 i=0; i<colors.size(); i++)
	{
		file->write("\"",1);
		file->write( colors[i].key.c_str(), colors[i].key.size() );
		file->write(" c ",3);

		// format color #RRGGBB
		c8 buf[7];
		const SColor& c = colors[i].value;
		sprintf(buf,"#%02x%02x%02x", c.getRed(), c.getGreen(), c.getBlue());
		core::stringc tmp = buf;
		tmp.make_upper();
		file->write(tmp.c_str(), tmp.size());

		file->write("\",",2);
		endLine(file);
	}

	// write pixels
//	"                                                                ",
//	"                                                                ",
//	"                                                                ",
//	"                                                                ",
//	"                      . + @ # $ % & * =                         ",
//	"                  - ; > , ' ) ! ~ { ] ^ / (                     ",
//	"                _ : < [ } | 1 2 3 4 5 6 7 8 9                   ",
//	"                0 a b b c 2 3 4 5 6 d e f g h                   ",
//	"                i j k l 2 4 5 6 d e f m n o p                   ",
//	"                q r s t u 6 d e f m n v w x y                   ",
//	"                z A B | C D f m E F G H I J K                   ",
//	"                L M 1 N O m n P Q H R S T U V W X Y Z `  ...+.  ",
//	"                p @.#.$.%.&.*.=.-.;.>.,.'.).!.~.{.].^./.(._.:.<.",
//	"  [.}.|.1.2.3.4.5.6.6 7.&.8.I ;.9.0.a.b.c.d.e.f.g.h.i.j.k.l.m.n.",
//	"}.o.p.q.r.s.t.u.v.w.O x.y.;.9.0.z.A.B.C.D.E.F.h.i.G.k.l.H.I.J.K.",
//	"L.M.N.O.P.Q.R.S.T.U.V.e W.0.z.A.X.Y.Z.`.d. +.+G.k.l.H.I.J.++@+#+",
//	"$+%+&+*+R.S.=+-+;+>+,+'+)+A.X.Y.!+~+{+]+^+/+(+_+H.I.J.:+<+[+}+|+",
//	"1+2+3+4+=+-+5+6+7+8+9+0+a+b+c+d+e+f+g+h+i+j+k+I.l+m+n+o+p+q+r+s+",
//	"t+u+v+w+5+6+7+x+y+z+A+B+C+D+E+F+G+H+I+J+K+h.L+++M+N+p+O+P+Q+R+S+",
//	"T+U+2+V+7+x+y+W+X+Y+Z+`+ @.@        +@@@#@$@%@&@*@O+P+Q+R+=@-@;@",
//	">@,@'@)@y+!@~@{@Z+`+]@^@/@(@        _@:@<@[@}@O+P+Q+R+=@-@|@1@2@",
//	"3@4@5@7+6@7@8@9@0@a@b@c@d@e@        f@g@h@i@j@Q+R+=@-@|@1@k@l@m@",
//	"n@y+o@p@{@9@0@a@b@c@q@r@s@t@        u@v@i@w@Q+=@-@|@1@k@l@x@y@z@",
//	"A@p@-+B@0@a@b@c@q@r@C@D@E@F@        G@H@I@J@K@L@M@N@O@P@Q@R@S@T@",
//	"U@7@4@V@b@c@q@r@C@D@W@X@Y@Z@          `@ #.#+#@###$#%#&#*#=#=#  ",
//	"-#;#>#,#q@r@C@D@W@X@'#)#!#~#                                    ",
//	"{#(@]#^#/#(#_#:#<#[#}#|#1#                                      ",
//	"    2#3#4#5#6#7#8#9#1#0#                                        ",
//	"                                                                ",
//	"                                                                ",
//	"                                                                ",
//	"                                                                "

	// buffer for current line
	core::stringc line;

	// loop
	for (u32 y=0; y<Size.Height; y++)
	{
		line = "\"";
		for (u32 x=0; x<Size.Width; x++)
		{
			// current pixel
			SColor colorNow = image->getPixel(x,y);
			colorNow.setAlpha(255);

			// search color in color-table
			u32 i=0;
			while (i<colors.size())
			{
				if (colors[i].value == colorNow)
				{
					break;
				}
				i++;
			}

			// write found color-table color
			line+=colors[i].key;
		}
		line+="\"";
		if (y < Size.Height-1)
			line+=",";
		else
			line+="};";

		file->write(line.c_str(),line.size() );
		endLine(file);
	}

	return true;
}

} // namespace video
} // namespace irr

#endif // _IRR_COMPILE_WITH_XPM_WRITER_
