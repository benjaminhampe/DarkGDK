// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CSonnenstand.h"

#include <irrlicht.h>

#include <iostream>

//#include "mathExt.h"

#include "../irrUtils.h"

#include "../irrDateTime.h"

#ifdef _DEBUG
	#include <../source/Irrlicht/os.h>
#endif // _DEBUG



namespace irr{
namespace astro{

CSonnenstand::CSonnenstand( )
	: mJD(0.0), mAzimut(0.0), mHoehe(0.0), mMethod( ESS_COUNT )
{}

CSonnenstand::CSonnenstand(Real jd, Real azimut, Real hoehe, ESS_COMPUTE_METHOD method )
	: mJD(jd), mAzimut(azimut), mHoehe(hoehe), mMethod( method )
{
//	if( mHoehe >= 90.0 && mHoehe<180.0)
//	{
//		mHoehe -= 90.0;
//		mAzimut -= 180.0;
//		while (mAzimut<0.0)
//		{
//			mAzimut += 360.0;
//		}
//		while (mAzimut>=360.0)
//		{
//			mAzimut -= 360.0;
//		}
//	}
}

CSonnenstand::CSonnenstand(const CSonnenstand& other)
{
	this->mJD = other.mJD;
	this->mAzimut = other.mAzimut;
	this->mHoehe = other.mHoehe;
	this->mMethod = other.mMethod;
}

CSonnenstand::~CSonnenstand()
{}

CSonnenstand& CSonnenstand::operator= (const CSonnenstand& other)
{
	if (*this == other)
		return *this;

	this->mJD = other.mJD;
	this->mAzimut = other.mAzimut;
	this->mHoehe = other.mHoehe;
	this->mMethod = other.mMethod;
	return *this;
}

core::stringc CSonnenstand::toString( s32 decimals ) const
{
	core::stringc s = "Sonnenstand( ";
	if (mMethod>=0 && mMethod<ESS_COUNT)
	{
		s+="m=";
		s+=ESS_COMPUTE_METHOD_NAMES[(u32)mMethod];
		s+=", ";
	}
	s+="jd=";
	if (decimals == -1)
	{ s+=mJD; }
	else
	{ s+=core::Math::Round( mJD, decimals ); }
	s+=", a=";
	if (decimals == -1)
	{ s+=mAzimut; }
	else
	{ s+=core::Math::Round( mAzimut, decimals ); }
	s+=", h=";
	if (decimals == -1)
	{ s+=mHoehe; }
	else
	{ s+=core::Math::Round( mHoehe, decimals ); }
	s+=" );";
//#ifdef _DEBUG
//	s+=" datetime=\"";
//	core::DateTime dt( mJD );
//	s+=dt.getYear(); s+=".";
//	s+=dt.getMonth(); s+=".";
//	s+=dt.getDay();	s+=" ";
//	s+=dt.getHour(); s+=":";
//	s+=dt.getMinute(); s+=":";
//	s+=dt.getSecond();
//	s+=" GMT (";
//	s+=dt.getGMT(); s+=", ";
//	s+=dt.getTimezone();
//	s+=")\"";
//#endif // _DEBUG
//	s+="method="; s+=ESS_COMPUTE_METHOD_NAMES[(u32)mMethod];
//	s+=",time_jd="; s+=mJD;
//	s+=",space_h="; s+=mAzimut;
//	s+=",space_y="; s+=mHoehe;
//	s+="</CSonnenstand>";

	return s;
}

core::stringc CSonnenstand::toXML() const
{
	core::stringc s = "<CSonnenstand";
	if (mMethod>=0 && mMethod<ESS_COUNT)
	{
		s+=ESS_COMPUTE_METHOD_NAMES[(u32)mMethod];
	}
	s+="\" jd=\""; s+=mJD;
	s+="\" a=\""; s+=mAzimut;
	s+="\" h=\""; s+=mHoehe;
	s+="\" />";
//#ifdef _DEBUG
//	s+=" datetime=\"";
//	core::DateTime dt( mJD );
//	s+=dt.getYear(); s+=".";
//	s+=dt.getMonth(); s+=".";
//	s+=dt.getDay();	s+=" ";
//	s+=dt.getHour(); s+=":";
//	s+=dt.getMinute(); s+=":";
//	s+=dt.getSecond();
//	s+=" GMT (";
//	s+=dt.getGMT(); s+=", ";
//	s+=dt.getTimezone();
//	s+=")\"";
//#endif // _DEBUG
//	s+="method="; s+=ESS_COMPUTE_METHOD_NAMES[(u32)mMethod];
//	s+=",time_jd="; s+=mJD;
//	s+=",space_h="; s+=mAzimut;
//	s+=",space_y="; s+=mHoehe;
//	s+="</CSonnenstand>";

	return s;
}

bool CSonnenstand::write( io::IXMLWriter* xml ) const
{
	if (!xml)
		return false;

	xml->writeElement(
		L"CSonnenstand", true,
		L"jd", core::stringw(mJD).c_str(),
		L"a", core::stringw(mAzimut).c_str(),
		L"h", core::stringw(mHoehe).c_str(),
		L"m", core::stringw( core::stringc(ESS_COMPUTE_METHOD_NAMES[(u32)mMethod])).c_str()
//	#ifdef _DEBUG
//		,L"datetime", s.c_str()
//	#endif // _DEBUG
	);

//#ifdef _DEBUG
//	core::DateTime dt( mJD );
//	core::stringw s(L"");
//	s+=dt.getYear(); s+=L".";
//	s+=dt.getMonth(); s+=L".";
//	s+=dt.getDay();	s+=L" ";
//	s+=dt.getHour(); s+=L":";
//	s+=dt.getMinute(); s+=L":";
//	s+=dt.getSecond();
//	s+=L" GMT (";
//	s+=dt.getGMT(); s+=L", ";
//	s+=dt.getTimezone();
//	s+=L")";
//#endif // _DEBUG


	xml->writeLineBreak();

	return true;
}

bool CSonnenstand::read( io::IXMLReader* xml )
{
	if (!xml)
		return false;

	core::stringw nodeName = xml->getNodeName();

	if (!nodeName.equals_ignore_case( core::stringw(L"CSonnenstand") ))
		return false;

	core::stringw strJD = xml->getAttributeValue(L"jd");
	core::stringw strAzimut = xml->getAttributeValue(L"azimut");
	core::stringw strElevation = xml->getAttributeValue(L"hoehe");
	core::stringw strMethod = xml->getAttributeValue(L"method");
	strJD.trim();
	strAzimut.trim();
	strElevation.trim();
	strMethod.trim();

	bool bSuccess = true;

	if (strJD.size() == 0)
	{
		#ifdef _DEBUG
		os::Printer::log( "CSonnenstand::readXML(): Could not read JulianDayNumber.", ELL_ERROR );
		#endif // _DEBUG
		bSuccess = false;
	}
	else
	{
		wchar_t* wpEndPtr;
		mJD = wcstod(strJD.c_str(), &wpEndPtr);
	}

	if (strAzimut.size() == 0)
	{
		#ifdef _DEBUG
		os::Printer::log( "CSonnenstand::readXML(): Could not read Azimut.", ELL_ERROR );
		#endif // _DEBUG
		bSuccess = false;
	}
	else
	{
		wchar_t* wpEndPtr;
		mAzimut = wcstod(strAzimut.c_str(), &wpEndPtr);
	}

	if (strElevation.size() == 0)
	{
		#ifdef _DEBUG
		os::Printer::log( "CSonnenstand::readXML(): Could not read Elevation.", ELL_ERROR );
		#endif // _DEBUG
		bSuccess = false;
	}
	else
	{
		wchar_t* wpEndPtr;
		mHoehe = wcstod(strElevation.c_str(), &wpEndPtr);
	}

	if (strMethod.size() == 0)
	{
		#ifdef _DEBUG
		os::Printer::log( "CSonnenstand::readXML(): Could not read Method.", ELL_ERROR );
		#endif // _DEBUG
		bSuccess = false;
	}
	else
	{
		bool found = false;
		for (u32 i=0; i<ESS_COUNT; i++)
		{
			if (strMethod.equals_ignore_case( ESS_COMPUTE_METHOD_NAMES[i] ))
			{
				found = true;
				mMethod = (ESS_COMPUTE_METHOD)i;
				break;
			}
		}

		if (!found)
		{
			#ifdef _DEBUG
			os::Printer::log( "CSonnenstand::readXML(): Could not find Method.", ELL_WARNING );
			#endif // _DEBUG
			mMethod = ESS_WIKIPEDIA;
		}
	}

	return bSuccess;
}

bool CSonnenstand::operator== (const CSonnenstand& other) const
{
	return (   core::equals(this->mJD, other.mJD) &&
				core::equals(this->mAzimut, other.mAzimut) &&
				core::equals(this->mHoehe, other.mHoehe) &&
				this->mMethod == other.mMethod );
}

bool CSonnenstand::operator!= (const CSonnenstand& other) const
{
	return !(*this==other);
}

bool CSonnenstand::operator> (const CSonnenstand& other) const
{
	return ((this->mJD > other.mJD) && (this->mAzimut > other.mAzimut) && (this->mHoehe > other.mHoehe));
}

bool CSonnenstand::operator< (const CSonnenstand& other) const
{
	return ((this->mJD < other.mJD) && (this->mAzimut < other.mAzimut) && (this->mHoehe < other.mHoehe));
}

bool CSonnenstand::operator>= (const CSonnenstand& other) const
{
	return ((*this > other) || (*this == other));
}

bool CSonnenstand::operator<= (const CSonnenstand& other) const
{
	return ((*this < other) || (*this == other));
}

core::position2di CSonnenstand::projectCartesian2di( const core::rectf& r_data, const core::recti& r_dst, bool invert_y ) const
{
	core::position2df data_origin(180,0);
	core::position2df image_origin( r_dst.UpperLeftCorner.X + r_dst.getWidth()/2, r_dst.LowerRightCorner.Y );

	core::position2di final_coords(0,0);
	// mirror x
	// final_coords.X = (s32) ( (360.0-(mAzimut - r_data.UpperLeftCorner.X) ) / r_data.getWidth() * (f32)r_dst.getWidth() + (f32)r_dst.UpperLeftCorner.X );
	final_coords.X = (s32) ( (mAzimut - (Real)data_origin.X) / ((Real)r_data.getWidth() * 0.5) *  (Real)r_dst.getWidth() );
	final_coords.X += image_origin.X;

	final_coords.Y = (s32) ( mHoehe / (Real)r_data.getHeight() * (f32)r_dst.getHeight() );
	if (invert_y)
	{
        final_coords.Y = image_origin.Y - final_coords.Y;
	}

	return final_coords;
}

core::position2df CSonnenstand::projectCartesian2df( const core::rectf& data_rect, const core::rectf& world_rect, bool invert_y) const
{
	core::position2df data_origin(180,0);
	core::position2df world_origin( world_rect.UpperLeftCorner.X + world_rect.getWidth()/2, world_rect.LowerRightCorner.Y );

	core::position2df final_coords(0,0);
	// mirror x
	// final_coords.X = (s32) ( (360.0-(mAzimut - r_data.UpperLeftCorner.X) ) / r_data.getWidth() * (f32)r_dst.getWidth() + (f32)r_dst.UpperLeftCorner.X );
	final_coords.X = ( (mAzimut - (Real)data_origin.X) / ((Real)data_rect.getWidth() * 0.5) *  (Real)world_rect.getWidth() );
	final_coords.X += world_origin.X;

	final_coords.Y = ( mHoehe / (Real)data_rect.getHeight() * (f32)world_rect.getHeight() );
    if (invert_y)
    {
        final_coords.Y = world_origin.Y - final_coords.Y;
    }

	return final_coords;

}

} // end namespace astro
} // end namespace irr
