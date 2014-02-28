// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CLinearColorGradientTable.h"

#ifdef _DEBUG
#include <../source/Irrlicht/os.h>
#endif // _DEBUG

#include <../../source/Irrlicht/CImage.h>

namespace irr
{

namespace video
{

CLinearColorGradientTable :: CLinearColorGradientTable( u32 color_count, u32 table_size )
: IColorGradient("", color_count), InvLookUpTableSize(0.0f)
{
	#if _DEBUG
		os::Printer::log( "CLinearColorGradientTable::ctr()", ELL_INFORMATION );
	#endif // _DEBUG
    setTableSize( table_size, true );
}

CLinearColorGradientTable::~CLinearColorGradientTable()
{
	#if _DEBUG
		os::Printer::log( "CLinearColorGradientTable::dtr()", ELL_INFORMATION );
	#endif // _DEBUG
	clear();
}

core::stringc CLinearColorGradientTable :: toString( ) const
{
	const u32 color_count = getColorCount();

	// print number of colors used
	core::stringc s("CLinearColorGradientTable[");
	s += color_count;

	// print name
	if (Name.size()>0)
	{
		s += Name;
		s += ", ";
	}

	// print
	s += "] = {\n";

	// print colors
	for (u32 i=0; i<color_count; i++)
	{
		s += "\t{ ";
		s += video::toString( Colors[i].Color.toSColor() );
		s += ", ";
		s += Colors[i].Position;
		s += " }";

		if (i<color_count)
		{
			s += ",";
		}

		s += "\n";
	}

	// print
	s += "};\n";
	return s;
}

bool CLinearColorGradientTable :: read( io::IXMLReader* pXml )
{
	if (!pXml)
		return false;

	// empty for now

	return true;
}

bool
CLinearColorGradientTable :: write ( io::IXMLWriter* pXml ) const
{
	if (!pXml)
		return false;

	// empty for now

	return true;
}

} // end namespace video

} // end namespace irr
