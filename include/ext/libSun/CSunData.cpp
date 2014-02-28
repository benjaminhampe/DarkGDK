// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CSunData.h"

#include <irrlicht.h>
#include <cstdlib>

#include "../irrUString.h"
#include "../IGUITTFont.h"
#include "../CGUITTFont.h"

#include "CSunCurve.h"
#include "CSonnenstand.h"
#include "Algorithms.h"

namespace irr{
// namespace astro{

// ----------------------------------- Class Implementation----------------------------------------------------
//! static
//! public
//! function

//void CSunData::showMessage ( gui::IGUIEnvironment* env, const core::stringw& txt, bool bModal )
//{
//	//! render frame
//	video::IVideoDriver* driver = env->getVideoDriver();
//	core::recti screen( core::position2di(0,0), driver->getScreenSize() );
//
//	video::ITexture* logo_tex = driver->getTexture( "../media/logo/dx9c.png");
//
//	gui::IGUIFont* font = env->getSkin()->getFont( gui::EGDF_DEFAULT );
//
//	driver->beginScene( true, true, video::SColor(255,255,255,255));
//
//	if (font)
//		font->draw( txt.c_str(), screen, video::SColor(255,0,0,0), true, true, 0 );
//
//		driver->draw2DImage( logo_tex, core::position2di( (screen.getWidth()-logo_tex->getSize().Width ) >> 1,screen.getHeight()>>2));
//		driver->endScene();
//	}
//}







// static class instantiation
CSunData* CSunData::create(s32 year, Real lon, Real lat, const core::stringw& location, u32 pointsPerDay, astro::ESS_COMPUTE_METHOD method, ILogger* logger )
{
	static CSunData* new_instance = new CSunData( year, lon, lat, location, pointsPerDay, method, logger );
	return new_instance;
}

//! Default constructor
CSunData::CSunData( ILogger* logger )
: Logger(logger), Method(astro::ESS_COUNT), PointsPerDay(0), Year(0), Lon(0), Lat(0), Loc(L"")
{}

// ------------------------------------------------------------------------------------------------------------
//! Value constructor
CSunData::CSunData(s32 year, Real lon, Real lat, const core::stringw& location, u32 pointsPerDay, astro::ESS_COMPUTE_METHOD method, ILogger* logger )
: Logger(logger), Method(astro::ESS_COUNT), PointsPerDay(0), Year(0), Lon(0), Lat(0), Loc(L"")
{
	// createData( s32 year, Real lon, Real lat, const core::stringw& location, u32 pointsPerDay, ESS_COMPUTE_METHOD method, ILogger* logger )
	createData( year, lon, lat, location, pointsPerDay, method, logger );
}

// ------------------------------------------------------------------------------------------------------------
//! Destructor
CSunData::~CSunData()
{
	clear();
}

// ------------------------------------------------------------------------------------------------------------

void CSunData::clear()
{
#ifdef _DEBUG
	if (Logger)
		Logger->log("CSunData::clear()");

#endif // _DEBUG

	for (u32 i=0; i<Curves.size(); i++)
	{
		astro::CSunCurve* p = Curves[i];
		if (p)
		{
			p->drop();
			Curves[i] = 0;
		}
	}
}

// ------------------------------------------------------------------------------------------------------------

void CSunData::createData( s32 year, Real lon, Real lat, const core::stringw& location, u32 pointsPerDay, astro::ESS_COMPUTE_METHOD method, ILogger* logger )
{
	Curves.reallocate( 100 );
	Curves.set_used( 0 );
	Method = method;
	Year = year;
	Lon = lon;
	Lat = lat;
	Loc = location;
	PointsPerDay = pointsPerDay;

    const s32 iDaysOfYear = core::DateTime(Year,1,1).getDaysOfYear();

#ifdef _DEBUG
	Logger = logger;

	if (Logger)
	{
		core::stringw txt = L"CSunData::create(";
		txt += year; txt += L",";
		txt += lon; txt += L",";
		txt += lat; txt += L",";
		txt += location; txt += L",";
		txt += pointsPerDay; txt += L",";
		txt += core::stringc( astro::ESS_COMPUTE_METHOD_NAMES[(u32)method] ); txt += L")";
		Logger->log( txt.c_str() );
	}
#endif // _DEBUG

	const video::SColor white(255,255,255,255);
    const video::SColor black(255,0,0,0);
    const video::SColor green(255,34,220,44);
    const video::SColor dark_green(255,0,100,0);
    const video::SColor light_green(255,107,142,35);
    const video::SColor dark_blue(255,70,130,180);
    const video::SColor light_blue(255,120,173,209);
    const video::SColor red(255,255,0,0);
    const video::SColor blue(255,0,0,255);
    const video::SColor yellow(255,255,255,0);
    const video::SColor orange(255,255,127,30);

    const f32 LineWidth = 1.0f;
    const s32 LineFactor = 1;
	const u16 full = 0xFFFF;		// 1111 1111 1111 1111 = FFFF
	const u16 dotted = 0xF0F0; 		// 0000 0001 0000 0001 = 0101
	const u16 dashed = 0xAAAA;      // 1010 1010 1010 1010 = AAAA
	const u16 dash_dotted = 0xFFCC; // 1111 1111 1100 1100 = FFCC

	//! Tageskurven
//	Curves.push_back( new CSunCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,1,1).getJD(), core::DateTime(Year,1,2).getJD(), PointsPerDay, Method, 2.f*LineWidth, dark_blue, full));
//	Curves.push_back( new CSunCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,2,1).getJD(), core::DateTime(Year,2,2).getJD(), PointsPerDay, Method, 2.f*LineWidth, dark_blue, full));
//	Curves.push_back( new CSunCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,3,1).getJD(), core::DateTime(Year,3,2).getJD(), PointsPerDay, Method, 2.f*LineWidth, dark_blue, full));
//	Curves.push_back( new CSunCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,4,1).getJD(), core::DateTime(Year,4,2).getJD(), PointsPerDay, Method, 2.f*LineWidth, dark_blue, full));
//	Curves.push_back( new CSunCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,5,1).getJD(), core::DateTime(Year,5,2).getJD(), PointsPerDay, Method, 2.f*LineWidth, dark_blue, full));
//	Curves.push_back( new CSunCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,6,1).getJD(), core::DateTime(Year,6,2).getJD(), PointsPerDay, Method, 2.f*LineWidth, dark_blue, full));
//	Curves.push_back( new CSunCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,7,1).getJD(), core::DateTime(Year,7,2).getJD(), PointsPerDay, Method, LineWidth, light_blue, full));
//	Curves.push_back( new CSunCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,8,1).getJD(), core::DateTime(Year,8,2).getJD(), PointsPerDay, Method, LineWidth, light_blue, full));
//	Curves.push_back( new CSunCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,9,1).getJD(), core::DateTime(Year,9,2).getJD(), PointsPerDay, Method, LineWidth, light_blue, full));
//	Curves.push_back( new CSunCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,10,1).getJD(),core::DateTime(Year,10,2).getJD(),PointsPerDay, Method, LineWidth, light_blue, full));
//	Curves.push_back( new CSunCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,11,1).getJD(),core::DateTime(Year,11,2).getJD(),PointsPerDay, Method, LineWidth, light_blue, full));
//	Curves.push_back( new CSunCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,12,1).getJD(),core::DateTime(Year,12,2).getJD(),PointsPerDay, Method, LineWidth, light_blue, full));
//	Curves.push_back( new CSunCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,6,21).getJD(),core::DateTime(Year,6,22).getJD(),PointsPerDay, Method, 2.f*LineWidth, red, dotted));
//	Curves.push_back( new CSunCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,12,21).getJD(),core::DateTime(Year,12,22).getJD(),PointsPerDay,Method,2.f*LineWidth, red, dotted));

	Curves.push_back( new astro::CSunCurve(astro::ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,6,21).getJD(),core::DateTime(Year,6,22).getJD(),PointsPerDay, Method, 3*LineWidth, blue, dotted));
	Curves.push_back( new astro::CSunCurve(astro::ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,12,21).getJD(),core::DateTime(Year,12,22).getJD(),PointsPerDay,Method,3*LineWidth, red, dotted));
	Curves.push_back( new astro::CSunCurve(astro::ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,1,1).getJD(), core::DateTime(Year,1,2).getJD(), PointsPerDay, Method, 2*LineWidth, white, full));
	Curves.push_back( new astro::CSunCurve(astro::ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,2,1).getJD(), core::DateTime(Year,2,2).getJD(), PointsPerDay, Method, 2*LineWidth, white, full));
	Curves.push_back( new astro::CSunCurve(astro::ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,3,1).getJD(), core::DateTime(Year,3,2).getJD(), PointsPerDay, Method, 2*LineWidth, white, full));
	Curves.push_back( new astro::CSunCurve(astro::ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,4,1).getJD(), core::DateTime(Year,4,2).getJD(), PointsPerDay, Method, 2*LineWidth, white, full));
	Curves.push_back( new astro::CSunCurve(astro::ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,5,1).getJD(), core::DateTime(Year,5,2).getJD(), PointsPerDay, Method, 2*LineWidth, white, full));
	Curves.push_back( new astro::CSunCurve(astro::ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,6,1).getJD(), core::DateTime(Year,6,2).getJD(), PointsPerDay, Method, 2*LineWidth, white, full));
	Curves.push_back( new astro::CSunCurve(astro::ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,7,1).getJD(), core::DateTime(Year,7,2).getJD(), PointsPerDay, Method, 2*LineWidth, light_blue, full));
	Curves.push_back( new astro::CSunCurve(astro::ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,8,1).getJD(), core::DateTime(Year,8,2).getJD(), PointsPerDay, Method, 2*LineWidth, light_blue, full));
	Curves.push_back( new astro::CSunCurve(astro::ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,9,1).getJD(), core::DateTime(Year,9,2).getJD(), PointsPerDay, Method, 2*LineWidth, light_blue, full));
	Curves.push_back( new astro::CSunCurve(astro::ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,10,1).getJD(),core::DateTime(Year,10,2).getJD(),PointsPerDay, Method, 2*LineWidth, light_blue, full));
	Curves.push_back( new astro::CSunCurve(astro::ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,11,1).getJD(),core::DateTime(Year,11,2).getJD(),PointsPerDay, Method, 2*LineWidth, light_blue, full));
	Curves.push_back( new astro::CSunCurve(astro::ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,12,1).getJD(),core::DateTime(Year,12,2).getJD(),PointsPerDay, Method, 2*LineWidth, light_blue, full));

	//! Stundenkurven (Analemmas)
	for (u32 hh=0; hh<24; ++hh)
	{
		astro::CSonnenstand s_min = sonnenstand( core::DateTime::JD(Year,1,1,hh,0,0), Lon, Lat, Method);
		astro::CSonnenstand s_max = s_min;

		for (u32 i=0; i<(u32)iDaysOfYear; i++)
		{
			Real jd_now = core::DateTime::JD( Year, (Real)i,0,0,0);
			jd_now += 0.5; // increase to 12:00
			astro::CSonnenstand s_now = astro::sonnenstand( jd_now, Lon, Lat, method);
			if (s_min.mHoehe > s_now.mHoehe)
			{
				s_min = s_now;
			}
			if (s_max.mHoehe < s_max.mHoehe)
			{
				s_max = s_now;
			}
		}

		u32 DayCount0 = core::DateTime::JD(Year,6,21)-core::DateTime::JD(Year-1,12,21);
		u32 DayCount1 = core::DateTime::JD(Year,12,21)-core::DateTime::JD(Year,6,22);

		// Juni bis Januar
		Curves.push_back( new astro::CSunCurve( astro::ESSD_CURVE_ANALEMMA, Loc, Lon, Lat,
			core::DateTime(Year,6,22,hh,0,0).getJD(),
			core::DateTime(Year,12,21,hh,0,0).getJD(),
			DayCount1, Method, 3.f*LineWidth, light_green, full ) );

		// Januar bis Juni
		Curves.push_back( new astro::CSunCurve( astro::ESSD_CURVE_ANALEMMA, Loc, Lon, Lat,
			core::DateTime(Year-1,12,21,hh,0,0).getJD(),
			core::DateTime(Year,6,21,hh,0,0).getJD(),
			DayCount0, Method, 4.f*LineWidth, dark_green, full ) );

	}

#ifdef _DEBUG

	/// count created curves and print result to ILogger
	if (Logger)
	{
		u32 curveCount = 0;
		for (u32 i=0; i<Curves.size(); i++)
		{
			astro::CSunCurve* curve = Curves[i];
			if (curve)
			{
				curveCount++;
			}
		}
		if (curveCount != Curves.size())
		{
			core::stringc txt = "CurveCount (";
			txt += curveCount;
			txt += ") differs from ArraySize (";
			txt += Curves.size();
			txt += ")";
			Logger->log( txt.c_str(), ELL_ERROR);
		}
		else
		{
			core::stringc txt = "Created ";
			txt += Curves.size();
			txt += " curves";
			Logger->log( txt.c_str(), ELL_INFORMATION);
		}
	}
#endif // _DEBUG

}

// ------------------------------------------------------------------------------------------------------------

//! get full number of stored data-points
u32 CSunData::getPointCount() const
{
	u32 pointCount = 0;

	for (u32 i=0; i<Curves.size(); i++)
	{
		astro::CSunCurve* p = Curves[i];
		if (p)
		{
			pointCount += p->getPointCount();
		}
	}
	return pointCount;
}

// ------------------------------------------------------------------------------------------------------------

core::stringw CSunData::createName() const
{
	core::stringw name = Utils::sprintf( L"SSD_%ls_%lf_%lf_%s",
		Loc.c_str(), Lon, Lat, astro::ESS_COMPUTE_METHOD_NAMES[Method]);

	return name;
}

// ------------------------------------------------------------------------------------------------------------

core::stringw CSunData::toString() const
{
	core::stringw txt = L"<CSunData>\n";

	for (u32 i=0; i<Curves.size(); i++)
	{
//		CSunCurve* curve = Curves[i];
//		if (curve)
//		{
//			txt += curve->toString();
//		}
	}
//	txt += Loc; txt += L", ( ";
//	txt += Lon; txt += L", ";
//	txt += Lat;	txt += L")"; txt += L"Method = ";
//	txt += ESS_COMPUTE_METHOD_NAMES[Method]; txt += L"PlotType = ";
//	txt += ESSD_TYPE_NAMES[PlotType];
	txt += L"</CSunData>\n";
	return txt;
}

// ------------------------------------------------------------------------------------------------------------

bool CSunData::write( io::IXMLWriter* xml ) const
{
	if (!xml)
		return false;

	core::array<core::stringw> AttribNames;
	core::array<core::stringw> AttribValues;

	AttribNames.push_back(L"curves");
	AttribValues.push_back( core::stringw() += Curves.size() );

	xml->writeComment(L"Container for SunCurves");
	xml->writeLineBreak();
	xml->writeElement(L"CSunData", false, AttribNames, AttribValues);
	xml->writeLineBreak();

	const u32 curveCount = Curves.size();

	for (u32 i=0; i<curveCount; i++)
	{
		core::stringw comment(L"Curve ");
		comment += i+1;
		comment += L" of ";
		comment += curveCount;
		xml->writeComment( comment.c_str() );
		xml->writeLineBreak();

		astro::CSunCurve* curve = Curves[i];
		if (curve)
		{
			curve->write( xml );
		}
	}

	xml->writeClosingTag(L"CSunData");
	xml->writeLineBreak();
	return true;
}

// ------------------------------------------------------------------------------------------------------------

//! read from XML Stream
bool CSunData::read( io::IXMLReaderUTF8* xml )
{
	if (!xml)
		return false;

	return true;
}

// ------------------------------------------------------------------------------------------------------------

//! save to XML or text-file depending on given file-extension (uses UTF-8)
bool CSunData::save( const io::path& filename, io::IFileSystem* filesys ) const
{
//	if(Logger)
//	{
//		core::stringw txt = L"CSunData::save(\"";
//		txt += filename;
//		txt += L"\")";
//		Logger->log( txt.c_str() );
//	}
//
//	IrrlichtDevice* device = 0;
//
//	if ( !filesys )
//	{
//		SIrrlichtCreationParameters params;
//		params.DriverType = video::EDT_NULL;
//		params.LoggingLevel = ELL_NONE;
//		device = createDeviceEx( params );
//		if (!device)
//		{
//			if (Logger)
//				Logger->log("Could not create NullDevice for XML-Writing", ELL_ERROR);
//			return false;
//		}
//		filesys = device->getFileSystem();
//	}
//
//	if ( !filesys )
//	{
//		_IRR_DEBUG_BREAK_IF( !device );
//		if (device)
//			device->drop();
//		return false;
//	}
//
//	io::IWriteFile* file = filesys->createAndWriteFile( filename, false );
//	if (!file)
//	{
//		if (Logger)
//			Logger->log("Could not create IWriteFile", ELL_ERROR);
//		device->drop();
//		return false;
//	}
//
//	io::CXMLWriterUTF8* xml = new io::CXMLWriterUTF8( file );
//	file->drop();
//
//	if (!xml)
//	{
//		if (Logger)
//			Logger->log("Could not create CXMLWriterUTF8 from IWriteFile", ELL_ERROR);
//		if (device)
//			device->drop();
//		return false;
//	}
//
//	bool result = this->write( xml );
//
//	if (!result)
//	{
//		if (Logger)
//			Logger->log("Could not write XML file", ELL_ERROR);
//	}
//
//	xml->drop();
//
//	if (device)
//		device->drop();
//
//	return result;
	return true;
}

// ------------------------------------------------------------------------------------------------------------

//! load from XML or text-file depending on given file-extension (uses UTF-8)
bool CSunData::load( const io::path& filename, io::IFileSystem* filesys )
{

	return true;
}



// ------------------------------------------------------------------------------------------------------------
//! get bounding data-rect min/max
core::rectf CSunData::getBoundingRect() const
{
	core::rectf r_box( FLT_MAX, FLT_MAX, FLT_MIN, FLT_MIN );

	// loop curves
	u32 curveCount = getCurveCount();

	// loop curves
	for (u32 c=0; c<curveCount; c++)
	{
		// get curve
		astro::CSunCurve* curve = Curves[c];

		// if curve
		if (curve)
		{
			// loop curve-points
			for (u32 p=0; p<curve->getPointCount(); p++)
			{
				Real a_now = curve->getPoint(p).mAzimut;
				Real h_now = curve->getPoint(p).mHoehe;
				if (r_box.UpperLeftCorner.X > a_now )
					r_box.UpperLeftCorner.X = a_now;
				if (r_box.UpperLeftCorner.Y > h_now )
					r_box.UpperLeftCorner.Y = h_now;
				if (r_box.LowerRightCorner.X < a_now )
					r_box.LowerRightCorner.X = a_now;
				if (r_box.LowerRightCorner.Y < h_now )
					r_box.LowerRightCorner.Y = h_now;
			}
		}
	}

	return r_box;
}

//! get optimal bounding data-rect for display
core::rectf CSunData::getOptimalRect() const
{
	core::rectf r_opt( FLT_MAX, 0, FLT_MIN, 0 );

	// loop curves
	const u32 curveCount = getCurveCount();

	// loop curves
	for (u32 c=0; c<curveCount; c++)
	{
		// get curve
		astro::CSunCurve* curve = Curves[c];

		// if curve
		if (curve && curve->getPointCount()>0)
		{
			// loop curve-points
			for (u32 p=0; p<curve->getPointCount(); p++)
			{
				const astro::CSonnenstand& now = curve->getPoint(p);

				if ( now.mHoehe > 0.0 || core::equals( now.mHoehe, 0.0) )
				{
					if (r_opt.LowerRightCorner.Y < now.mHoehe )
						r_opt.LowerRightCorner.Y = now.mHoehe;

					if ( now.mAzimut <= 180.0 )
					{
						if (r_opt.UpperLeftCorner.X > now.mAzimut )
							r_opt.UpperLeftCorner.X = now.mAzimut;
					}
					else
					{
						if (r_opt.LowerRightCorner.X < now.mAzimut )
							r_opt.LowerRightCorner.X = now.mAzimut;
					}
				}
			}
		}
	}

	s32 i_x = 1+core::floor32( 0.1f*r_opt.getWidth() );
	s32 i_y = 1+core::floor32( 0.1f*r_opt.getHeight() );
	r_opt.UpperLeftCorner.X = -0.5f*(f32)i_x;
	r_opt.UpperLeftCorner.Y = -0.5f*(f32)i_y;
	r_opt.LowerRightCorner.X = 0.5f*(f32)i_x;
	r_opt.LowerRightCorner.Y = 0.5f*(f32)i_y;

	return r_opt;
}






Real CSunData::getSunRiseAzimuth() const
{
	Real min_azimuth = 360.0;

	for (u32 i=0; i<Curves.size(); i++)
	{
		astro::CSunCurve* curve = Curves[i];
		if ( curve )
		{
			Real now_azimuth = curve->getSunRiseAzimuth();

			if (min_azimuth > now_azimuth)
			{
				min_azimuth = now_azimuth;
			}
		}
	}

	return min_azimuth;
}

Real CSunData::getSunDuskAzimuth() const
{
	Real max_azimuth = 0.0;

	for (u32 i=0; i<Curves.size(); i++)
	{
		astro::CSunCurve* curve = Curves[i];
		if ( curve )
		{
			Real now_azimuth = curve->getSunDuskAzimuth();

			if (max_azimuth < now_azimuth)
			{
				max_azimuth = now_azimuth;
			}
		}
	}

	return max_azimuth;
}

	//! get sum of all sun points x n(0,1,0);
Real CSunData::getGlobalRadiationSum() const
{
	Real rad_sum = 0.0f;


	return rad_sum;
}

//! get sum of all sun points x n(x,y,z);
Real CSunData::getGlobalRadiationSumTo( const core::vector3df& plain_normale ) const
{
	Real rad_sum = 0.0f;

	u32 curveCount = this->getCurveCount();
	u32 pointCount = 0;

	for (u32 c=0; c<curveCount; c++)
	{
		const astro::CSunCurve* curve = this->getCurve( c );
		if (curve)
		{
			u32 pCount = curve->getPointCount();
			pointCount += pCount;
			for (u32 p=0; p<pointCount; p++)
			{
				const astro::CSonnenstand& s = curve->getPoint( p );

			}
		}
	}

	return rad_sum;
}













////! load settings from ini file
//bool CSunGraph::load(const io::path& fileName)
//{
//#ifdef _DEBUG
//	if (Logger)
//		Logger->log("CSunGraph::load()");
//#endif
//
//	std::ifstream i(fileName.c_str(), std::ios::in);
//	if (!i.is_open())
//	{
//		if (Logger)
//		{
//			core::stringw txt = "Could not read ";
//			txt += fileName.c_str();
//			Logger->log( txt.c_str(), ELL_ERROR );
//		}
//		return false;
//	}
//
//	return true;
//}
//

// ------------------------------------------------------------------------------------------------------------

//
////! save settings to ini file
//bool CSunGraph::save(const io::path& fileName)
//{
//#ifdef _DEBUG
//	if (Logger)
//		Logger->log("CSunGraph::save()");
//#endif
//	return false;
//}

// ------------------------------------------------------------------------------------------------------------

////! lade alles von XML datei
//bool CSunGraph::loadXML(const io::path& fileName)
//{
//#ifdef _DEBUG
//	if (Logger)
//		Logger->log("CSunGraph::loadXML()");
//#endif
//	// create the reader using one of the factory functions
//	std::ofstream ooo("CSunGraph_loadXML.log", std::ios::out);
//
//	io::IrrXMLReader* xmlReader = io::createIrrXMLReader(fileName.c_str());
//
//	if (xmlReader)
//	{
//		core::stringc className("SCurve");
//
//		SCurve* ssk = NULL;
//
//		// parse the file until end reached
//        io::EXML_NODE nodeType;
//        core::stringc nodeName;
//        core::stringc nodeData;
//        core::stringc nodeAttribName;
//        core::stringc nodeAttribValue;
//		u32 nodeAttribCount;
//
//		while(xmlReader && xmlReader->read())
//		{
//            nodeType = xmlReader->getNodeType();
//
//			switch(nodeType)
//			{
//				case io::EXN_ELEMENT:
//				{
//					ooo<<"<!-- EXN_ELEMENT -->"<<std::endl;
//                    nodeName = xmlReader->getNodeName();
//                    nodeAttribCount = xmlReader->getAttributeCount();
//					ooo<<nodeName.c_str()<<std::endl;
//					ooo<<"attrCount = "<<nodeAttribCount<<std::endl;
//					if (nodeAttribCount > 0)
//                    {
//                        for (u32 i = 0; i < nodeAttribCount; ++i)
//                        {
//                            nodeAttribName = xmlReader->getAttributeName(i);
//                            nodeAttribValue = xmlReader->getAttributeValue(i);
//                            ooo<<i+1<<"/"<<nodeAttribCount
//                            <<" => "
//                            <<nodeAttribName.c_str()
//                            <<" = "
//                            <<nodeAttribValue.c_str()
//                            <<";"
//                            <<std::endl;
//                        }
//                    }
//				} break;
//
//				case io::EXN_ELEMENT_END:
//				{
//					ooo<<"<!-- EXN_ELEMENT_END -->"<<std::endl;
//				} break;
//
//				case io::EXN_TEXT:
//				{
//					ooo<<"<!-- EXN_TEXT -->"<<std::endl;
//					core::stringc nodeData = xmlReader->getNodeData();
//					if (nodeData.size() == 0)
//                        ooo<<xmlReader->getNodeData()<<std::endl;
//				} break;
//
//				case io::EXN_NONE:
//				{
//					ooo<<"<!-- EXN_NONE -->"<<std::endl;
//					ooo<<"nodeName = "<<xmlReader->getNodeName()<<std::endl;
//					ooo<<"attrCount = "<<xmlReader->getAttributeCount()<<std::endl;
//					for (u32 i = 0; i<xmlReader->getAttributeCount(); ++i)
//					{
//                        ooo<<"Attribute ("<<i<<") = "<<xmlReader->getAttributeName(i)<<"="<<xmlReader->getAttributeValue(i)<<std::endl;
//					}
//					ooo<<"nodeData = "<<xmlReader->getNodeData()<<std::endl;
//
//				} break;
//
//				case io::EXN_COMMENT:
//				{
//					ooo<<"<!-- EXN_COMMENT -->"<<std::endl;
////					ooo<<"nodeName = "<<xmlReader->getNodeName()<<std::endl;
////					ooo<<"attrCount = "<<xmlReader->getAttributeCount()<<std::endl;
////					for (u32 i = 0; i<xmlReader->getAttributeCount(); ++i)
////					{
////                        ooo<<"Attribute ("<<i<<") = "<<xmlReader->getAttributeName(i)<<"="<<xmlReader->getAttributeValue(i)<<std::endl;
////					}
//                    core::stringc tmp = xmlReader->getNodeData();
//                    tmp.trim();
//					ooo<<tmp.c_str()<<std::endl;
//
//				} break;
//
//				case io::EXN_CDATA:
//				{
//					ooo<<"<!-- EXN_CDATA -->"<<std::endl;
//					ooo<<"nodeName = "<<xmlReader->getNodeName()<<std::endl;
//					ooo<<"attrCount = "<<xmlReader->getAttributeCount()<<std::endl;
//					for (u32 i = 0; i<xmlReader->getAttributeCount(); ++i)
//					{
//                        ooo<<"Attribute ("<<i<<") = "<<xmlReader->getAttributeName(i)<<"="<<xmlReader->getAttributeValue(i)<<std::endl;
//					}
//					ooo<<"nodeData = "<<xmlReader->getNodeData()<<std::endl;
//
//				} break;
//
//				case io::EXN_UNKNOWN:
//				{
//					ooo<<"<!-- EXN_UNKNOWN -->"<<std::endl;
//				} break;
//
//				default:
//					ooo<<"<!-- This should never happen. -->"<<std::endl;
//					break;
//			}
//		}
//
//		// delete the xmlReader parser after usage
//		delete xmlReader;
//	}
//
//	ooo.close();
//	return true;
//}

// ------------------------------------------------------------------------------------------------------------

////! speichere alles in XML dateien
//bool CSunGraph::saveXML(const io::path& fileName)
//{
//#ifdef _DEBUG
//	if (Logger)
//		Logger->log("CSunGraph::saveXML()\n");
//#endif
//
//	io::path saveName = fileName;
//	if (saveName.size()==0)
//	{
//		saveName = createName();
//		saveName += _IRR_TEXT(".xml");
//	}
//
//    IrrlichtDevice* device = createDevice(video::EDT_NULL);
//    if (!device)
//		return false;
//
//    io::IFileSystem* fs = device->getFileSystem();
//
//#if defined(_IRR_POSIX_API_)
//    io::IWriteFile* xmlFile = fs->createAndWriteFile(saveName);
//    io::IXMLWriter* xmlWriter = new io::CXMLWriterUTF8(xmlFile);
//#else
//	io::IXMLWriter* xmlWriter = fs->createXMLWriter(saveName);
//#endif
//    xmlWriter->writeXMLHeader();
//    xmlWriter->writeComment(L"CSunGraph::saveXML()");
//    xmlWriter->writeLineBreak();
//    xmlWriter->writeElement(L"CSunGraph");
//    xmlWriter->writeLineBreak();
//    for (u32 i=0; i<Curves.size(); ++i)
//    {
//		SCurve* curve = Curves[i];
//		if (curve)
//		{
////			curves->writeXML(xmlWriter);
////			xmlWriter->writeLineBreak();
//		}
//    }
//    xmlWriter->writeClosingTag(L"CSunGraph");
//    xmlWriter->writeLineBreak();
//    xmlWriter->drop();
//#if defined(_IRR_POSIX_API_)
//    xmlFile->drop();
//#endif
//    device->drop();
//	return true;
//}

// ------------------------------------------------------------------------------------------------------------

//
////! write SVG-Image to file
//bool CSunGraph::saveSVG( const io::path& fileName, const core::dimension2du& dstSize)
//{
//#ifdef _DEBUG
//	if (Logger)
//		Logger->log("CSunGraph::saveSVG()\n");
//#endif
//
//    io::IFileSystem* fs = Device->getFileSystem();
//	io::path name = fileName;
//	if (name.size()==0)
//	{
//		name = io::path(createName().c_str());
//		name+=".svg";
//	}
//#if defined(_IRR_POSIX_API_)
//    io::IWriteFile* xmlFile = fs->createAndWriteFile(name);
//    io::IXMLWriter* xmlWriter = new io::CXMLWriterUTF8(xmlFile);
//#else
//	io::IXMLWriter* xmlWriter = fs->createXMLWriter(name);
//#endif
//    if (!xmlWriter)
//    {
//        return false;
//    }
//
//    //! Write XML Header
//    xmlWriter->writeXMLHeader();
//    writeSVG(xmlWriter, dstSize);
//    xmlWriter->writeLineBreak();
//    xmlWriter->drop();
//#if defined(_IRR_POSIX_API_)
//    xmlFile->drop();
//#endif
//	return true;
//}
//
// ------------------------------------------------------------------------------------------------------------

////! write SVG-Image to XML-Stream
//bool CSunGraph::writeSVG( io::IXMLWriter* pWriter, const core::dimension2du& dstSize) // DINA4_300DPI(3508,2480);
//{
//#ifdef _DEBUG
//	if (Logger)
//		Logger->log("CSunGraph::writeSVG()\n");
//#endif
//    if (!pWriter)
//        return false;
//
////    f32 px = (f32)dstSize.Width/3508.0f; // 18 + 2 cells in x direction
////    f32 py = (f32)dstSize.Height/2480.0f
////    f32 aspect0 = (f32)dstSize.Width / (f32)dstSize.Height;
////    core::dimension2du graphSize;
////    f32 ssdGraphAspect = (f32)ssdGraphSize.Width / (f32)ssdGraphSize.Height;
////    f32 aspect1 = (f32)dstSize.Width / (f32)dstSize.Height;
//
//    pWriter->grab();
//
//    const video::SColor black(255,0,0,0);
//    const video::SColor white(255,255,255,255);
//
//// HEADER END
//
//    // var holding dst-size in floats
//    const core::dimension2df fSize( (f32)dstSize.Width, (f32)dstSize.Height);
//
//	const core::vector2df pixelSize = core::vector2df( core::reciprocal((f32)dstSize.Width), core::reciprocal((f32)dstSize.Height));
//
//    io::writeSVG_Tag(pWriter,
//                     core::position2df(0,0),
//                     core::dimension2df(dstSize.Width, dstSize.Height),
//                     core::rectf(0,0,dstSize.Width, dstSize.Height));
//
//    //! TITLE tag
//    pWriter->writeElement(L"title", false);
//    pWriter->writeText(L"CSunGraph");
//    pWriter->writeClosingTag(L"title");
//    pWriter->writeLineBreak();
//
//    //! DESC tag
//    pWriter->writeElement(L"desc", false);
//    pWriter->writeText(L"SVG Image of calculated sunpath-indicator graph");
//    pWriter->writeClosingTag(L"desc");
//    pWriter->writeLineBreak();
//
//    //! TEXT
//    io::writeSVG_Text(pWriter, 10, 50, L"SVG CSunGraph", 20);
//    io::writeSVG_Text(pWriter, 10, dstSize.Height-10, L"SVG CSunGraph", 20);
//    io::writeSVG_Text(pWriter, dstSize.Width-500, 50, L"SVG CSunGraph", 20);
//    io::writeSVG_Text(pWriter, dstSize.Width-500, dstSize.Height-10, L"SVG CSunGraph", 20);
//
//// HEADER END
//
//    //! calculate the min/max of data available
//    const core::rect<f64> dataRect = getBoundingDataRect();
//
//    // default data rect we like to view
//    core::rect<f64> viewRect = getBoundingRect();
//
//    //! write txt as text
//    core::stringw txt(L"dataRect ( ");
//    txt+=dataRect.UpperLeftCorner.X; txt+=L", ";
//    txt+=dataRect.UpperLeftCorner.Y; txt+=L", ";
//    txt+=dataRect.LowerRightCorner.X; txt+=L", ";
//    txt+=dataRect.LowerRightCorner.Y; txt+=L"; ";
//    txt+=dataRect.getWidth(); txt+=L", ";
//    txt+=dataRect.getHeight(); txt+=L")";
//    io::writeSVG_Text(pWriter, 10, 120, txt.c_str(), 16);
//
//    //! write txt as text
//    txt=L"viewRect ( ";
//    txt+=viewRect.UpperLeftCorner.X; txt+=L", ";
//    txt+=viewRect.UpperLeftCorner.Y; txt+=L", ";
//    txt+=viewRect.LowerRightCorner.X; txt+=L", ";
//    txt+=viewRect.LowerRightCorner.Y; txt+=L"; ";
//    txt+=viewRect.getWidth(); txt+=L", ";
//    txt+=viewRect.getHeight(); txt+=L")";
//    io::writeSVG_Text(pWriter, 10, 150, txt.c_str(), 16);
//
//    //! calculate the best dst size in pixels for our graph depending on aspect of viewRect
//
//    //writeSVG_GroupTranslate( )
////    core::position2df graphPos(0,0);
////    core::dimension2df graphSize(fSize.Width*dataRect.getWidth(), dataRect.getHeight());
////
//    //! draw CoordSystem for SSD-Graph
//    const f32 fScaleX = (f32)dstSize.Width/(f32)viewRect.getWidth();
//    const f32 fScaleY = (f32)dstSize.Height/(f32)viewRect.getHeight();
////
//////    io::writeSVG_GroupTranslate(pWriter, 180.0f-dataRect.UpperLeftCorner.X, -dataRect.UpperLeftCorner.Y);
//////    io::writeSVG_GroupTranslate(pWriter,  viewRect.UpperLeftCorner.X,  viewRect.UpperLeftCorner.Y);
////
////    io::writeSVG_GroupScale(pWriter, (f32)(graphSize.Width/(f64)dataRect.getWidth()), (f32)(graphSize.Height/(f64)dataRect.getHeight());
////
////    //! draw CoordSystem for SSD-Graph
////    core::vector2df fPoint0(    (f32)((f64)fScaleX*(180.0-viewRect.UpperLeftCorner.X)),
////                                surfaceRect.getHeight()-(f32)((f64)fScaleY*(0.0-viewRect.UpperLeftCorner.Y)));
////    core::vector2df fPointLeft( (f32)0.0f, (f32)fPoint0.Y);
////    core::vector2df fPointRight((f32)viewRect.getWidth(), (f32)fPoint0.Y);
////    core::vector2df fPointTop(  (f32)fPoint0.X, (f32)0.0f);
////    core::vector2df fPointBottom((f32)fPoint0.X, (f32)viewRect.getHeight());
////
////    //! draw CoordSystem for SSD-Graph
////    io::writeSVG_Line(pWriter, fPointLeft.X, fPointLeft.Y, fPointRight.X, fPointRight.Y, video::SColor(255,0,0,0), 5.0f);
////    io::writeSVG_Line(pWriter, fPointTop.X, fPointTop.Y, fPointBottom.X, fPointBottom.Y, video::SColor(255,0,0,0), 5.0f);
////    io::writeSVG_Circle(pWriter, fPoint0.X, fPoint0.Y, 20, video::SColor(255,0,0,0), 5.0f, video::SColor(127,255,255,255) );
////
////    //! draw CoordSystem for SSD-Graph
////    for (s32 gradY=0; gradY<(s32)(viewRect.LowerRightCorner.Y); gradY+=10)
////    {
////        core::vector2df fPoint( 0.0f,
////                                (f32)dstSize.Height-(f32)((f64)fScaleY*((f64)gradY-viewRect.UpperLeftCorner.Y)));
////
////        core::stringw txt(L""); txt+=gradY; txt+=L'\u00B0'; // txt+=L"&#x00B0;";
////        io::writeSVG_Text(pWriter, fPoint.X-20.0f, fPoint.Y+32.0f, txt, 16, video::SColor(255,0,0,0), video::SColor(0,0,0,0), 1.0f, L"Verdana", 400);
////        io::writeSVG_Line(pWriter, fPoint.X, fPoint.Y, viewRect.getWidth()-fPoint.X, fPoint.Y, video::SColor(255,0,0,0), 1.0f);
////    }
////
////    //! draw CoordSystem for SSD-Graph
////    f32 fPointEndY = surfaceRect.getHeight()-(f32)((f64)fScaleY*(dataRect.LowerRightCorner.Y-dataRect.UpperLeftCorner.Y));
////    for (s32 gradX=viewRect.UpperLeftCorner.X; gradX<viewRect.LowerRightCorner.X; gradX+=10)
////    {
////        core::vector2df fPoint( (f32)((f64)fScaleX*((f64)gradX-viewRect.UpperLeftCorner.X)),
////                                surfaceRect.getHeight()-(f32)((f64)fScaleY*(0.0-viewRect.UpperLeftCorner.Y)));
////
////
////        core::stringw txt(L""); txt+=gradX; txt+=L'\u00B0'; // txt+=L"&#x00B0;";
////        io::writeSVG_Text(pWriter, fPoint.X-20.0f, fPoint.Y+32.0f, txt, 16, video::SColor(255,0,0,0), video::SColor(0,0,0,0), 1.0f, L"Verdana", 400);
////        io::writeSVG_Line(pWriter, fPoint.X, fPoint.Y, fPoint.X, fPointEndY, video::SColor(255,200,200,200), 1.0f);
////    }
//
//
////	<g transform="translate(0.000000,1000.000000)">
////	<g transform="scale(4.724324,-13.777778)">
////	<g transform="translate(5.000000,-0.000000)">
//
//    // DINA4_300DPI(3508,2480);
//    io::writeSVG_GroupTranslate(pWriter, 0,  1000);
//    io::writeSVG_GroupScale(pWriter, fScaleX,  -fScaleY);
//    io::writeSVG_GroupTranslate(pWriter, -viewRect.UpperLeftCorner.X,  -viewRect.UpperLeftCorner.Y);
//
//    //! draw curves as paths (moveTo, lineTo)
//    for (u32 c=0; c<Curves.size(); ++c)
//    {
//        SCurve* curve = Curves[c];
//        if (curve)
//        {
//            //! precalculate dataPoints into view(box)-space
//            core::array<core::vector2df> mPoints;
//            mPoints.reallocate( curve->Curves.size() );
//            mPoints.set_used(0);
//
//            u32 i = 0;
//            while ( i < curve->Curves.size() )
//            {
//                if ((curve->Curves[i].mAzimut >= core::min_(viewRect.UpperLeftCorner.X, viewRect.LowerRightCorner.X)) &&
//                    (curve->Curves[i].mAzimut <= core::max_(viewRect.UpperLeftCorner.X, viewRect.LowerRightCorner.X)) &&
//                    (curve->Curves[i].mHoehe >= core::min_(viewRect.UpperLeftCorner.Y, viewRect.LowerRightCorner.Y)) &&
//                    (curve->Curves[i].mHoehe <= core::max_(viewRect.UpperLeftCorner.Y, viewRect.LowerRightCorner.Y)))
//                {
//                    mPoints.push_back( core::vector2df( (f32)(curve->Curves[i].mAzimut), (f32)(curve->Curves[i].mHoehe)));
//                }
////                else
////                {
////                  f32 x = (f32)((f64)fScaleX*(curve->Curves[i].mAzimut-viewRect.UpperLeftCorner.X));
////                  f32 y = (f32)((f64)dstSize.Height - (f64)fScaleY*(curve->Curves[i].mHoehe-viewRect.UpperLeftCorner.Y));
////                    f32 x = (f32)curve->Curves[i].mAzimut;
////                    f32 y = (f32)curve->Curves[i].mHoehe;
////
////                }
//                i++;
//            }
//
//
//            //! write infos from data as XML-Comment
//            core::stringw comment(L"sonnenstandskurve::writeSVG()");
//            comment+=STR_LINEBREAK;
//            comment+=L"type "; comment+=curve->mType; comment+=STR_LINEBREAK;		// Ortsname
//            comment+=L"location "; comment+=curve->Location; comment+=STR_LINEBREAK;		// Ortsname
//            comment+=L"longitude "; comment+=curve->Longitude; comment+=STR_LINEBREAK;	// Laengengrad
//            comment+=L"latitude "; comment+=curve->Latitude; comment+=STR_LINEBREAK;	// Breitengrad
//            comment+=L"jd_start "; comment+=curve->mDateStart; comment+=STR_LINEBREAK; 	// Julianische Tageszahl
//            comment+=L"jd_end "; comment+=curve->mDateEnd; comment+=STR_LINEBREAK;		// Julianische Tageszahl
//            comment+=L"method "; comment+=curve->Method; comment+=STR_LINEBREAK;    	// BerechnungsMethod
//            comment+=L"linecolor "; comment+=curve->mLineColor.color; comment+=STR_LINEBREAK;	// Graphik
//            comment+=L"linewith "; comment+=curve->LineWidth; comment+=STR_LINEBREAK;	// Graphik
//            comment+=L"linestipple "; comment+=curve->LineStipple; comment+=STR_LINEBREAK;	// Graphik
//            comment+=L"count "; comment+=curve->Curves.size(); comment+=STR_LINEBREAK;	// Anzahl Messwerte (Iterationen)
//            pWriter->writeComment(comment.c_str());
//            pWriter->writeLineBreak();
//
//            //! write SVG_Path, one per curve, not closing, only MoveTo and LineTo
//            // todo: writeSVG_Path(pWriter, mPoints, curve->mLineColor, curve->LineWidth);
//            // writeSVG_Path( pWriter, )
//
//            //! write SVG_Line
//            // <line x1="0" y1="0" x2="200" y2="200" style="stroke:rgb(255,0,0);stroke-width:2"/>
//            for (u32 i=1; i<mPoints.size(); ++i)
//            {
//                io::writeSVG_Line(pWriter,
//                              mPoints[i-1].X,
//                              mPoints[i-1].Y,
//                              mPoints[i].X,
//                              mPoints[i].Y,
//                              curve->mLineColor,
//                              2.0f*curve->LineWidth*pixelSize.X / fScaleX);
//            }
//            if (curve->getCurveType() != ESSD_CURVE_ANALEMMA)
//            {
//                //! write SVG_Circle for each data-point
//                for (u32 i=0; i<mPoints.size(); ++i)
//                {
//                    io::writeSVG_Circle(pWriter,
//                                    mPoints[i].X,
//                                    mPoints[i].Y,
//                                    2.0f*curve->LineWidth*pixelSize.X / fScaleX,
//                                    curve->mLineColor,
//                                    curve->LineWidth*pixelSize.X / fScaleX,
//                                    video::SColor(127,255,255,255));
//                }
//            }
//        }
//    }
//    pWriter->writeClosingTag(L"g");
//    pWriter->writeLineBreak();
//    pWriter->writeClosingTag(L"g");
//    pWriter->writeLineBreak();
//    pWriter->writeClosingTag(L"g");
//    pWriter->writeLineBreak();
//    pWriter->writeClosingTag(L"svg");
//    pWriter->writeLineBreak();
//    pWriter->drop();
//    return true;
//}

// ------------------------------------------------------------------------------------------------------------

//	//! create data
//
//	switch (PlotType)
//	{
//		case ESSDT_CARTESIAN:
//		{
//			//! Stundenkurven (Analemmas)
//			for (u32 hh=0; hh<24; ++hh)
//			{
//				Curves.push_back( new SCurve( ESSD_CURVE_ANALEMMA, Loc, Lon, Lat,
//					core::DateTime(Year,1,21,hh,0,0).getJD(),
//					core::DateTime(Year+1,1,21,hh,0,0).getJD(),
//					DayCount, Method, LineWidth, white, dash_dotted ) );
//			}
//
//			//! Tageskurven
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,1,1).getJD(), core::DateTime(Year,1,2).getJD(), PointsPerDay, Method, LineWidth, green1, full));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,2,1).getJD(), core::DateTime(Year,2,2).getJD(), PointsPerDay, Method, LineWidth, green1, full));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,3,1).getJD(), core::DateTime(Year,3,2).getJD(), PointsPerDay, Method, LineWidth, green1, full));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,4,1).getJD(), core::DateTime(Year,4,2).getJD(), PointsPerDay, Method, LineWidth, green1, full));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,5,1).getJD(), core::DateTime(Year,5,2).getJD(), PointsPerDay, Method, LineWidth, green1, full));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,6,1).getJD(), core::DateTime(Year,6,2).getJD(), PointsPerDay, Method, LineWidth, green1, full));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,7,1).getJD(), core::DateTime(Year,7,2).getJD(), PointsPerDay, Method, LineWidth, green2, dashed));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,8,1).getJD(), core::DateTime(Year,8,2).getJD(), PointsPerDay, Method, LineWidth, green2, dashed));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,9,1).getJD(), core::DateTime(Year,9,2).getJD(), PointsPerDay, Method, LineWidth, green2, dashed));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,10,1).getJD(), core::DateTime(Year,10,2).getJD(), PointsPerDay, Method, LineWidth, green2, dashed));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,11,1).getJD(), core::DateTime(Year,11,2).getJD(), PointsPerDay, Method, LineWidth, green2, dashed));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,12,1).getJD(), core::DateTime(Year,12,2).getJD(), PointsPerDay, Method, 2.f*LineWidth, green2, dashed));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,6,21).getJD(), core::DateTime(Year,6,22).getJD(), PointsPerDay, Method, 2.f*LineWidth, red, dotted));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,12,21).getJD(), core::DateTime(Year,12,22).getJD(), PointsPerDay, Method, 2.f*LineWidth, blue, dotted));
//
//		} break;
//		case ESSDT_INDICATOR:
//		{
//			//! Tageskurven
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,3,21).getJD(), core::DateTime(Year,3,22).getJD(), PointsPerDay, Method, LineWidth, green1, full));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,9,21).getJD(), core::DateTime(Year,9,22).getJD(), PointsPerDay, Method, LineWidth, green2, dashed));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,6,21).getJD(), core::DateTime(Year,6,22).getJD(), PointsPerDay, Method, 2.f*LineWidth, red, dotted));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,12,21).getJD(), core::DateTime(Year,12,22).getJD(), PointsPerDay, Method, 2.f*LineWidth, blue, dotted));
//
//		} break;
//		case ESSDT_POLAR:
//		{
//			//! Stundenkurven (Analemmas)
//			for (u32 hh=0; hh<24; ++hh)
//			{
//				Curves.push_back(new SCurve(ESSD_CURVE_ANALEMMA, Loc, Lon, Lat, core::DateTime(Year,1,21,hh).getJD(), core::DateTime(Year+1,1,21,hh).getJD(), DayCount, Method, 2.0f*LineWidth, white, dash_dotted));
//			}
//
//			//! Tageskurven
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,1,1).getJD(), core::DateTime(Year,1,2).getJD(), PointsPerDay, Method, LineWidth, green1, full));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,2,1).getJD(), core::DateTime(Year,2,2).getJD(), PointsPerDay, Method, LineWidth, green1, full));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,3,1).getJD(), core::DateTime(Year,3,2).getJD(), PointsPerDay, Method, LineWidth, green1, full));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,4,1).getJD(), core::DateTime(Year,4,2).getJD(), PointsPerDay, Method, LineWidth, green1, full));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,5,1).getJD(), core::DateTime(Year,5,2).getJD(), PointsPerDay, Method, LineWidth, green1, full));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,6,1).getJD(), core::DateTime(Year,6,2).getJD(), PointsPerDay, Method, LineWidth, green1, full));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,7,1).getJD(), core::DateTime(Year,7,2).getJD(), PointsPerDay, Method, LineWidth, green2, dashed));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,8,1).getJD(), core::DateTime(Year,8,2).getJD(), PointsPerDay, Method, LineWidth, green2, dashed));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,9,1).getJD(), core::DateTime(Year,9,2).getJD(), PointsPerDay, Method, LineWidth, green2, dashed));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,10,1).getJD(), core::DateTime(Year,10,2).getJD(), PointsPerDay, Method, LineWidth, green2, dashed));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,11,1).getJD(), core::DateTime(Year,11,2).getJD(), PointsPerDay, Method, LineWidth, green2, dashed));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,12,1).getJD(), core::DateTime(Year,12,2).getJD(), PointsPerDay, Method, 2.f*LineWidth, green2, dashed));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,6,21).getJD(), core::DateTime(Year,6,22).getJD(), PointsPerDay, Method, 2.f*LineWidth, red, dotted));
//			Curves.push_back(new SCurve(ESSD_CURVE_NORMAL, Loc, Lon, Lat, core::DateTime(Year,12,21).getJD(), core::DateTime(Year,12,22).getJD(), PointsPerDay, Method, 2.f*LineWidth, blue, dotted));
//
//		} break;
//		case ESSDT_POINT_CLOUD:
//		{
//			//! alle Tageskurven 1.1.Year bis 1.1.Year+1
//			for (u32 d=1; d<(u32)DayCount; ++d)
//			{
//				Curves.push_back( new SCurve(
//					ESSD_CURVE_NORMAL, Loc, Lon, Lat,
//					core::DateTime(Year, (f64)d).getJD(),
//					core::DateTime(Year,(f64)d+1).getJD(),
//					PointsPerDay, Method, 3.5f*LineWidth, yellow, full));
//			}
//		} break;
//		default: break;
//	}


//
////! static
////! public class-member
////! of type member-function
//bool CSunData::renderToImage ( gui::IGUIEnvironment* env, const core::rectf& r_data,
//		video::IImage* dst,	const core::recti& r_dst, ILogger* logger) const
//{
//	if (!env) return false;
//	if (!dst) return false;
//
//	const core::recti r_image( core::position2di(0,0), dst->getDimension() );
//
//	if (r_dst.getWidth() == 0 || r_dst.getHeight() == 0) return false;
//
//	video::IVideoDriver* driver = env->getVideoDriver();
//	if (!driver)
//		return false;
//
//	video::CImageFactory* factory = new video::CImageFactory( logger );
//	if (!factory)
//		return false;
//
////	showMessage( env, L"Calculate Image...", false );
//	//! load fonts
////	showMessage ( env, L"Load fonts...", false );
//
//	bool bAntiAliased = false;
//	bool bTransparent = false;
//	gui::IGUIFont* font = env->getFont( _IRR_TEXT("../media/fonts/Lucida_Console_Regular_8_AA_Alpha.xml") );
//	gui::CGUITTFont* fontTitle = gui::CGUITTFont::create( env, _IRR_TEXT("../media/fonts/ttf/chicomono.ttf"), 72, bAntiAliased, bTransparent );
//	gui::CGUITTFont* fontBig = gui::CGUITTFont::create( env, _IRR_TEXT("../media/fonts/ttf/chicomono.ttf"), 64, bAntiAliased, bTransparent );
//	gui::CGUITTFont* fontMed = gui::CGUITTFont::create( env, _IRR_TEXT("../media/fonts/ttf/chicomono.ttf"), 32, bAntiAliased, bTransparent );
//	gui::CGUITTFont* fontDataTitle = gui::CGUITTFont::create( env, _IRR_TEXT("../media/fonts/ttf/courbd.ttf"), 24, bAntiAliased, bTransparent );
//	gui::CGUITTFont* fontSmall = gui::CGUITTFont::create( env, _IRR_TEXT("../media/fonts/ttf/chicomono.ttf"), 24, bAntiAliased, bTransparent );
//	gui::CGUITTFont* fontAxisText = gui::CGUITTFont::create( env, _IRR_TEXT("../media/fonts/ttf/chicomono.ttf"), 16, bAntiAliased, bTransparent );
//	gui::CGUITTFont* fontHour = gui::CGUITTFont::create( env, _IRR_TEXT("../media/fonts/ttf/Georgia_Bold.ttf"), 36, bAntiAliased, bTransparent );
//	gui::CGUITTFont* font14 = gui::CGUITTFont::create( env, _IRR_TEXT("../media/fonts/ttf/chicomono.ttf"), 16, bAntiAliased, bTransparent );
//
//	//! draw background
////	showMessage ( env, L"Draw Background...", false );
//	core::dimension2du tile_size(32,32);
//	video::SColor tile_color_a(64,127,127,127);
//	video::SColor tile_color_b(192,208,208,208);
//	video::SColor grid_color(255,255,255,255);
//
//	const s32 w = dst->getDimension().Width;
//	const s32 h = dst->getDimension().Height;
//	const s32 cells_needed_x = core::floor32( 0.1f * r_data.getWidth() );
//	const s32 cells_needed_y = core::floor32( 0.1f * r_data.getHeight() );
//	const s32 cell_w = core::floor32( (f32)r_dst.getWidth() / (f32)cells_needed_x ); // actual tile-size width in px
//	const s32 cell_h = cell_w; 									// actual tile-size height in px
//	const s32 c_x = r_dst.UpperLeftCorner.X;
//	const s32 c_y = r_dst.UpperLeftCorner.Y;
//	const s32 c_w = r_dst.getWidth();
//	const s32 c_h = r_dst.getHeight();
//	const core::recti r_canvas_border( c_x - cell_w, c_y - 2*cell_h, c_x + c_w + cell_w-1, c_y + c_h + 2*cell_h-1);
//	const core::recti r_grid_left( c_x, c_y, c_x+c_w/2, c_y+c_h-1);
//	const core::recti r_grid_right( c_x+c_w/2+1, c_y, c_x+c_w, c_y+c_h-1);
//
//	const core::rectf r_data_max = getBoundingRect();
//	const core::rectf r_data_opt = getOptimalRect();
//
//	core::stringw txt;
//
////	showMessage( env, L"Create Image...", false );
//
//	factory->drawCheckered( dst, r_dst, tile_size, tile_color_a, tile_color_b );
//	factory->drawGrid( dst, r_dst, tile_size, grid_color);
//	factory->drawLine( dst, r_dst, video::SC_Yellow);
//	// factory->drawLine( dst, core::recti(w-1,0,0,h-1), video::SC_Yellow);
//	// factory->drawCircle( dst, core::position2di(w/2,h/2), core::s32_min(w/2,h/2), video::SC_Blue);
//
//	//! draw watermark
//	s32 tx = r_dst.UpperLeftCorner.X;
//	s32 ty = r_dst.UpperLeftCorner.Y;
//	factory->drawText( dst, driver, fontTitle, tx,ty, L"_neo_cortex", video::SC_White, -1,-1, 0);
//
//	//! draw canvas
//#ifdef _DEBUG
//	//! draw dst border
//	factory->drawRoundRect( dst, r_dst, cell_w, cell_h, video::SC_White, 10, false);
////	factory->drawLine( dst, core::position2di( 0, c_y), core::position2di( w-1, c_y), video::SC_Black);
////	factory->drawLine( dst, core::position2di( 0, c_y + c_h-1 ), core::position2di( w-1, c_y + c_h-1), video::SC_Black);
//#endif // _DEBUG
//
//	//! PART 1 draw canvas ( round border [ video::SC_White ] + filled rect [ four colors ] + Grid )
//	factory->drawRoundRect( dst, r_canvas_border, cell_w, cell_h, video::SColor(245,255,255,255), false);
//
//	const video::SColor t_red(192,255,0,0);
//	const video::SColor t_green(203,0,255,0);
//	const video::SColor t_blue(183,0,0,255);
//	const video::SColor t_yellow(192,255,255,0);
//	factory->drawRect( dst, r_dst, t_red, t_green, t_blue, t_yellow, 0);
//
//	// factory->drawRect( dst, r_dst, video::SColor(64,255,255,255), 0, false);
//
//	//! END PART 1
//
//	u32 curveCount = 0;
//
//	//! draw data-points as point-cloud of yellow cirlces
////	curveCount = data->getCurveCount();
////	for (u32 c=0; c<curveCount; c++)
////	{
////		astro::CSunCurve* curve = data->getCurve(c);
////		if (curve)
////		{
////			u32 pointCount = curve->getPointCount();
////
////			core::array<core::position2di> points;
////			points.reallocate( pointCount );
////			points.set_used( 0 );
////
////			for (u32 l=0; l<pointCount; l++)
////			{
////				const astro::CSonnenstand& s = curve->getPoint(l);
////				points.push_back( s.projectCartesian2di( r_data, r_dst, true ) );
////			}
////
////			for (u32 l=0; l<points.size()-1; l++)
////			{
////				factory->drawCircle( dst, points[l], 10, video::SColor(0,255,255,255), 0, false);
////
//////				video::CImageFactory::SPointList point_list = factory->traverseLine( points[l], points[l+1]);
////
//////				for (u32 p=0; p<point_list.size(); p++)
//////				{
//////					factory->drawImage( brush, dst, point_list[p],brush->getDimension(), false, true);
//////				}
////
////				// factory->drawTexturedLine( dst, points[l], points[l+1], lineColor, false);
////			}
////
////			curve = 0;
////		}
////	}
//
//
//	//! draw curves
//	curveCount = getCurveCount();
//	for (u32 c=0; c<curveCount; c++)
//	{
//		const astro::CSunCurve* curve = getCurve(c);
//		if (curve)
//		{
//			u32 pointCount = curve->getPointCount();
//
//			core::array<core::position2di> points;
//			points.reallocate( pointCount );
//			points.set_used( 0 );
//
//			for (u32 l=0; l<pointCount; l++)
//			{
//				const astro::CSonnenstand& s = curve->getPoint(l);
//
//				points.push_back( s.projectCartesian2di( r_data, r_dst, true ) );
//			}
//
//			video::SColor lineColor = curve->getLineColor();
//
//			for (u32 l=0; l<points.size()-1; l++)
//			{
//				factory->drawLine( dst, points[l], points[l+1], lineColor, false);
//
//				f32 radius = curve->getLineWidth();
//				if (radius<=0.1f)
//					radius = 1.0f;
//				factory->drawCircle( dst, points[l], radius, lineColor, 0, false);
//
////				video::CImageFactory::SPointList point_list = factory->traverseLine( points[l], points[l+1]);
//
////				for (u32 p=0; p<point_list.size(); p++)
////				{
////					factory->drawImage( brush, dst, point_list[p],brush->getDimension(), false, true);
////				}
//
//				// factory->drawTexturedLine( dst, points[l], points[l+1], lineColor, false);
//			}
//
//			curve = 0;
//		}
//	}
//
//	//! temporary container for points of interest
//	core::array<astro::CSonnenstand> ssd_points;
//
//	//! draw 14 analemma points ( 12 days ( each first of months ) + 21. Jun (Max) + 21.Dez ( Min )
//	ssd_points.reallocate( 14 );
//	ssd_points.set_used( 0 );
//
//	//! push maximum
//	f64 jd_now = core::DateTime::JD( getYear(),6,21,11,0,0);
//	ssd_points.push_back( astro::sonnenstand( jd_now, getLongitude(), getLatitude(), getMethod() ) );
//
//	//! push minimum
//	jd_now = core::DateTime::JD( getYear(),12,21,11,0,0);
//	ssd_points.push_back( astro::sonnenstand( jd_now, getLongitude(), getLatitude(), getMethod() ) );
//
//	//! push days 1.M.year 11:00:00 for M [1..12]
//	for (u32 month=0; month<12; month++)
//	{
//		jd_now = core::DateTime::JD( getYear(),1+month,1, 11,0,0 );
//		ssd_points.push_back( astro::sonnenstand( jd_now, getLongitude(), getLatitude(), getMethod() ) );
//	}
//
//	//! calculate projected 2d coords and draw as circle + text beside
//	for (u32 i=0; i<ssd_points.size(); i++)
//	{
//		core::position2di pos = ssd_points[i].projectCartesian2di( r_data, r_dst, true);
//
//
//		core::stringw txt = L"";
//		s32 hAlign = -1;
//		s32 vAlign = -1;
//
//		s32 distance = 5;
//		core::position2di off_0( 0,-distance);
//		core::position2di off_1( 0,distance);
//		core::position2di off_2( 2*distance,0);
//		core::position2di off_3( -2*distance,0);
//		core::position2di offset(0,0);
//		switch (i)
//		{
//			case 0: txt = L"21.Jun"; hAlign = 0; vAlign = 1; offset = off_0; break;
//			case 1: txt = L"21.Dez"; hAlign = 0; vAlign = -1; offset = off_1; break;
//			case 2: txt = L"1.Jan"; hAlign = 1; vAlign = 0; offset = off_3; break;
//			case 3: txt = L"1.Feb"; hAlign = 1; vAlign = 0; offset = off_3; break;
//			case 4: txt = L"1.Mar"; hAlign = 1; vAlign = 0; offset = off_3; break;
//			case 5: txt = L"1.Apr"; hAlign = 1; vAlign = 0; offset = off_3; break;
//			case 6: txt = L"1.Mai"; hAlign = -1; vAlign = 0; offset = off_2; break;
//			case 7: txt = L"1.Jun"; hAlign = -1; vAlign = 0; offset = off_2; break;
//			case 8: txt = L"1.Jul"; hAlign = 1; vAlign = 0; offset = off_3; break;
//			case 9: txt = L"1.Aug"; hAlign = 1; vAlign = 0; offset = off_3; break;
//			case 10: txt = L"1.Sep"; hAlign = -1; vAlign = 0; offset = off_2; break;
//			case 11: txt = L"1.Okt"; hAlign = -1; vAlign = 0; offset = off_2; break;
//			case 12: txt = L"1.Nov"; hAlign = -1; vAlign = 0; offset = off_2; break;
//			case 13: txt = L"1.Dez"; hAlign = -1; vAlign = 0; offset = off_2; break;
//			default: break;
//		}
//
//		factory->drawCircle( dst, pos, 5, getCurve(i)->getLineColor(), 1, false);
//		factory->drawText( dst, driver, fontMed, pos.X+offset.X, pos.Y+offset.Y, txt, getCurve(i)->getLineColor(), hAlign, vAlign, 0, false);
//	}
//
//
//	//! draw hour texts
//	ssd_points.reallocate( 24 );
//	ssd_points.set_used( 0 );
//
//	for (u32 i=0; i<24; i++)
//	{
//		Real jd_now = core::DateTime::JD( getYear(), 6,21,i, 0,0);
//		ssd_points.push_back( astro::sonnenstand(jd_now, getLongitude(), getLatitude(), getMethod() ) );
//	}
//
//	for (u32 i = 0; i<ssd_points.size(); i++)
//	{
//		core::position2di pos = ssd_points[i].projectCartesian2di( r_data, r_dst, true);
//		//!@todo: txt += actual hour by ssd_jd date
//		core::stringw txt = L""; txt += i;
//		core::dimension2du txt_size = fontHour->getDimension( txt.c_str() );
//		factory->drawText( dst, driver, fontHour, pos.X, pos.Y-20, txt, video::SC_White, 0, 1, 0, false );
//		factory->drawText( dst, driver, fontHour, pos.X+txt_size.Width-2, pos.Y-20-txt_size.Height/2, L"h", video::SC_White, 0, 1, 0, false );
//	}
//#ifdef _DEBUG
//
//	//! draw 365-366 circles
//	u32 uDaysOfYear = core::DateTime::getDaysOfYear( getYear() );
//	ssd_points.reallocate( uDaysOfYear );
//	ssd_points.set_used( 0 );
//	for (u32 d = 0; d<uDaysOfYear; d++)
//	{
//		Real jd_now = core::DateTime::JD( getYear(),(Real)(d+1) );
//		jd_now += 9.0*core::INV_24;
//		ssd_points.push_back( astro::sonnenstand( jd_now, getLongitude(), getLatitude(), getMethod() ) );
//	}
//
//	for (u32 i = 0; i<ssd_points.size(); i++)
//	{
//		core::position2di pos = ssd_points[i].projectCartesian2di( r_data, r_dst, true);
//		factory->drawCircle( dst, pos, 1, video::SC_White );
//	}
//
//	for (u32 i = 0; i<ssd_points.size(); i++)
//	{
//		if ( i % 10 == 1)
//		{
//			core::position2di pos = ssd_points[i].projectCartesian2di( r_data, r_dst, true);
//			factory->drawCircle( dst, pos, 2, video::SC_Red );
//			factory->drawLine( dst, pos, pos+core::position2di(-25,0), video::SC_White, false);
//		}
//	}
//
//
//	//! draw 14 analemma points ( 12 days ( each first of months ) + 21. Jun (Max) + 21.Dez ( Min )
//	ssd_points.reallocate( 14 );
//	ssd_points.set_used( 0 );
//
//	//! push maximum
//	jd_now = core::DateTime::JD( getYear(),6,21,9,0,0);
//	ssd_points.push_back( astro::sonnenstand( jd_now, getLongitude(), getLatitude(), getMethod() ) );
//
//	//! push minimum
//	jd_now = core::DateTime::JD( getYear(),12,21,9,0,0);
//	ssd_points.push_back( astro::sonnenstand( jd_now, getLongitude(), getLatitude(), getMethod() ) );
//
//	//! push days 1.M.year 11:00:00 for M [1..12]
//	for (u32 month=0; month<12; month++)
//	{
//		jd_now = core::DateTime::JD( getYear(), 1+month, 1, 9, 0, 0 );
//		ssd_points.push_back( astro::sonnenstand( jd_now, getLongitude(), getLatitude(), getMethod() ) );
//	}
//
//	//! calculate projected 2d coords and draw as circle + text beside
//	for (u32 i=0; i<ssd_points.size(); i++)
//	{
//		video::SColor color = video::SC_White;
//		core::stringw txt = L"";
//		s32 hAlign = -1;
//		s32 vAlign = -1;
//
//		s32 distance = 5;
//		core::position2di off_0( 0,-distance);
//		core::position2di off_1( 0,distance);
//		core::position2di off_2( 2*distance,0);
//		core::position2di off_3( -2*distance,0);
//		core::position2di offset(0,0);
//
//		core::position2di pos = ssd_points[i].projectCartesian2di( r_data, r_dst, true);
//
//
//		switch (i)
//		{
//			case 0: txt = L"21.Jun"; hAlign = 0; vAlign = 1; offset = off_0; color = video::SC_Blue; break;
//			case 1: txt = L"21.Dez"; hAlign = 0; vAlign = -1; offset = off_1; color = video::SC_Red; break;
//			case 2: txt = L"1.Jan"; hAlign = 1; vAlign = 0; offset = off_3; color = video::SC_DarkGreen; break;
//			case 3: txt = L"1.Feb"; hAlign = 1; vAlign = 0; offset = off_3; color = video::SC_DarkGreen; break;
//			case 4: txt = L"1.Mar"; hAlign = 1; vAlign = 0; offset = off_3; color = video::SC_DarkGreen; break;
//			case 5: txt = L"1.Apr"; hAlign = 1; vAlign = 0; offset = off_3; color = video::SC_DarkGreen; break;
//			case 6: txt = L"1.Mai"; hAlign = -1; vAlign = 0; offset = off_2; color = video::SC_DarkGreen; break;
//			case 7: txt = L"1.Jun"; hAlign = -1; vAlign = 0; offset = off_2; color = video::SC_DarkGreen; break;
//			case 8: txt = L"1.Jul"; hAlign = 1; vAlign = 0; offset = off_3; color = video::SC_LightGreen; break;
//			case 9: txt = L"1.Aug"; hAlign = 1; vAlign = 0; offset = off_3; color = video::SC_LightGreen; break;
//			case 10: txt = L"1.Sep"; hAlign = -1; vAlign = 0; offset = off_2; color = video::SC_LightGreen; break;
//			case 11: txt = L"1.Okt"; hAlign = -1; vAlign = 0; offset = off_2; color = video::SC_LightGreen; break;
//			case 12: txt = L"1.Nov"; hAlign = -1; vAlign = 0; offset = off_2; color = video::SC_LightGreen; break;
//			case 13: txt = L"1.Dez"; hAlign = -1; vAlign = 0; offset = off_2; color = video::SC_LightGreen; break;
//			default: break;
//		}
//		factory->drawCircle( dst, pos, 5, color, 1, false);
//		factory->drawText( dst, driver, font14, pos.X+offset.X, pos.Y+offset.Y, txt, color, hAlign, vAlign, 0, false);
//	}
//
//	//! draw points of 10:00 showing alls days of year
//	ssd_points.reallocate( 9 );
//	ssd_points.set_used( 0 );
//	ssd_points.push_back( astro::CSonnenstand( 0,0,90) ); // ssd_left_top
//	ssd_points.push_back( astro::CSonnenstand( 0,180,90) ); //  ssd_center_top
//	ssd_points.push_back( astro::CSonnenstand( 0,360,90) ); //  ssd_right_top
//	ssd_points.push_back( astro::CSonnenstand( 0,0,45) ); // ssd_left_middle
//	ssd_points.push_back( astro::CSonnenstand( 0,180,45) ); //  ssd_center_middle
//	ssd_points.push_back( astro::CSonnenstand( 0,360,45) ); //  ssd_right_middle
//	ssd_points.push_back( astro::CSonnenstand( 0,0,0) ); // ssd_left_bottom
//	ssd_points.push_back( astro::CSonnenstand( 0,180,0) ); //  ssd_center_bottom
//	ssd_points.push_back( astro::CSonnenstand( 0,360,0) ); //  ssd_right_bottom
//
//	//! calculate projected 2d coords and draw as circle + text beside
//	for (u32 i=0; i<ssd_points.size(); i++)
//	{
//		s32 hAlign = -1;
//		s32 vAlign = -1;
//		video::SColor color = video::SC_White;
//		core::stringw txt = L"[";
//		txt+=core::floor32( ssd_points[i].mAzimut );
//		txt+=L",";
//		txt+=core::floor32( ssd_points[i].mHoehe );
//		txt+=L"]";
//		core::position2di pos = ssd_points[i].projectCartesian2di( r_data, r_dst, true);
//		factory->drawText( dst, driver, font14, pos.X+10, pos.Y, txt, color, hAlign, vAlign, 0, false);
//	}
//#endif // _DEBUG
//
//
//	//! PART 2
//	factory->drawRect( dst, core::recti( 0, c_y+c_h, w-1, h-1),video::SC_Null, 0, false);
//	factory->drawRect( dst, core::recti(c_x-2*cell_w,c_y+c_h,c_x+c_w+2*cell_w, c_y+c_h+2*cell_h), video::SC_White, 0, false);
//	factory->drawGrid( dst, r_grid_left, core::dimension2du(cell_w,cell_h), video::SC_White, true, true);
//	factory->drawGrid( dst, r_grid_right, core::dimension2du(cell_w,cell_h), video::SC_White, false, true);
//	factory->drawRect( dst, r_dst, video::SC_Black, 2, false);
//
//	// bool render axis arrow
//	// bool bVertical == 0, default render horizontal ( x-axis )
//	// 				  == 1, render vertical ( y-axis )
//	// bool bHideText == false, default render all text
//	// 				  == true, render no text
//	// bool bHideArrow == false, default render arrow
//	// 				  == true, render no arrow
//	// f32 fMin, fMax, fValue, fStep
//	//
//
//	//! render texts for negative -x axis
//	core::position2df dir(-1,0);
//	core::position2df pos( c_x+c_w/2,c_y+c_h+2 );
//	f32 fMin = r_data.UpperLeftCorner.X;
//	f32 fMax = 180.0f;
//	s32 iStepCount = core::abs_<s32>( core::floor32( 0.05f*(fMax-fMin) ) );
//	f32 fStep = 0.5f*(f32)c_w / (f32)iStepCount;
//
//	f32 x = pos.X;
//	u32 i = 0;
//	while ( i < iStepCount )
//	{
//		f32 f_angle = 180.0f-10.0f*(f32)i;
//		core::position2di pos0 = astro::CSonnenstand( 0, f_angle, 0).projectCartesian2di( r_data, r_dst, true);
//		core::stringw txt = L""; txt += core::floor32(0.1f*f_angle); txt += L"°";
//		factory->drawText( dst, driver, fontAxisText, pos0.X, pos0.Y, txt, video::SC_Black, 1, 0, 0, false );
//		i++;
//	}
//
//	//! render texts for positive +x axis
//	dir = core::position2df( 1,0 );
//	pos = core::position2df ( c_x+c_w/2,c_y+c_h+2 );
//	fMin = 180.0f;
//	fMax = r_data.LowerRightCorner.X;
//	iStepCount = core::abs_<s32>( core::floor32( 0.05f*(fMax-fMin) ) );
//	fStep = 0.5f*(f32)c_w / (f32)iStepCount;
//
//	x = pos.X;
//	i = 0;
//	while ( i < iStepCount )
//	{
//		f32 f_angle = 180.0f+10.0f*(f32)i;
//		core::position2di pos0 = astro::CSonnenstand( 0, f_angle, 0 ).projectCartesian2di( r_data, r_dst, true);
//		core::stringw txt = L""; txt += core::floor32(0.1f*f_angle); txt += L"°";
//		factory->drawText( dst, driver, fontAxisText, pos0.X, pos0.Y, txt, video::SC_Black, 1, 0, 0, false );
//		i++;
//	}
//
//	//! render texts for positive +y axis
//	dir = core::position2df( 0,1 );
//	pos = core::position2df ( c_x+c_w/2-8,c_y+c_h+2 );
//	fMin = r_data.UpperLeftCorner.Y;
//	fMax = r_data.LowerRightCorner.Y;
//	iStepCount = core::abs_<s32>( core::floor32( 0.05f*(fMax-fMin) ) );
//	fStep = 0.5f*(f32)c_h / (f32)iStepCount;
//
//	// bool render horizontal axis
//	f32 y = c_y + c_h;
//	i = 0;
//	while ( i < iStepCount )
//	{
//		f32 f_angle = 0.0f+10.0f*(f32)i;
//		core::position2di pos0 = astro::CSonnenstand( 0, f_angle, 0).projectCartesian2di( r_data, r_dst, true);
//		core::stringw txt = L""; txt += core::floor32(0.1f*f_angle); txt += L"°";
//		factory->drawText( dst, driver, fontAxisText, pos.X, pos.Y, txt, video::SC_Black, 1, 0, 0, false );
//		i++;
//	}
//
//	//! draw text North
//	factory->drawText( dst, driver, fontMed, c_x+c_w,c_y-cell_h/2, L"North", video::SC_Black, 0,1, 0);
//
//	//! draw text South
//	factory->drawText( dst, driver, fontMed, c_x+c_w/2,c_y+c_h+cell_h/2, L"South", video::SC_Black, 0,-1, 0);
//
//	//! draw text East
//	factory->drawText( dst, driver, fontMed, c_x+c_w/2-9*cell_w,c_y+c_h+cell_h/2, L"East", video::SC_Black, 0,-1, 0);
//
//	//! draw text West
//	factory->drawText( dst, driver, fontMed, c_x+c_w/2+9*cell_w,c_y+c_h+cell_h/2, L"West", video::SC_Black, 0,-1, 0);
//
//	//! draw text author
//	factory->drawText( dst, driver, fontMed, c_x+c_w-10,c_y-10, L"_neo_cortex", video::SC_Black, 1,1, 0);
//
//	//! draw text ssd
//	factory->drawText( dst, driver, fontBig, w/2,c_y-cell_h/2, L"Sonnenstandsdiagramm", video::SC_Black, 0,1, 0);
//
//	//! draw text: ssd-title
//	txt = L"";
//	txt += getLocation();
//	txt += L" ";
//	txt += getYear();
//	txt += L" [";
//	txt += Utils::sprintf( "%3.2f", getLongitude() );
//	txt += L"°O,";
//	txt += Utils::sprintf( "%3.2f", getLatitude() );
//	txt += L"°N] (curves=";
//	txt += curveCount;
//	txt += L"), Method=";
//	txt += astro::ESS_COMPUTE_METHOD_NAMES[ (u32)getMethod() ];
//	txt += L"";
//	factory->drawText( dst, driver, fontTitle, c_x+c_w/2,c_y+cell_h, txt.c_str(), video::SC_White, 0,1, 0);
//
//#ifdef _DEBUG
//
//	//! draw text: image_rect
//	txt = core::stringw( Utils::toString( r_image, "r_image") );
//	factory->drawText( dst, driver, fontMed, c_x + 10,c_y+1*cell_h, txt.c_str(), video::SC_White, -1,1, 0);
//
//	//! draw text: r_dst
//	txt = core::stringw( Utils::toString( r_dst, "r_dst") );
//	factory->drawText( dst, driver, fontMed, c_x + 10,c_y+2*cell_h, txt.c_str(), video::SC_White, -1,1, 0);
//
//	//! draw text: r_data
//	txt = core::stringw( Utils::toString( r_data, "r_data") );
//	factory->drawText( dst, driver, fontMed, c_x + 10,c_y+3*cell_h, txt.c_str(), video::SC_White, -1,1, 0);
//
//	//! draw text: data_bounding_rect
//	txt = core::stringw( Utils::toString( r_data_max, "r_data_max") );
//	factory->drawText( dst, driver, fontMed, c_x + 10,c_y+4*cell_h, txt.c_str(), video::SC_White, -1,1, 0);
//
//	//! draw text: data_optimal_rect
//	txt = core::stringw( Utils::toString( r_data_opt, "r_data_opt" ) );
//	factory->drawText( dst, driver, fontMed, c_x + 10,c_y+5*cell_h, txt.c_str(), video::SC_White, -1,1, 0);
//
//	//! draw text: cell_wh
//	txt = core::stringw( Utils::toString( core::recti(core::position2di(0,0), core::dimension2du(cell_w,cell_h)), "r_cell_dimension") );
//	factory->drawText( dst, driver, fontMed, c_x + 10,c_y+6*cell_h, txt.c_str(), video::SC_White, -1,1, 0);
//
//
//#endif // _DEBUG
//
//	//! END PART 2
//
//
//	{
//
//		f32 glob_rad_sum = getGlobalRadiationSum();
//
//		core::stringw txt = L"Global Radiation Sum per square meter and year = ";
//		txt += glob_rad_sum;
//		txt += " Joule";
//		s32 x = c_x+c_w/2;
//		s32 y = c_y+c_h+cell_h;
//		factory->drawText( dst, driver, fontMed, x, y, txt.c_str(), video::SC_Black, 0, -1, 0, false );
//
//	}
//
//	if (factory)
//		delete factory;
//}


// } // end namespace astro
} // end namespace irr

//
//	//! PART 2
//	factory->drawRect( image, core::recti( 0, c_y+c_h, w-1, h-1), video::SColor(0,0,0,0), 0, false);
//	factory->drawRect( image, core::recti(c_x-2*cell_w,c_y+c_h,c_x+c_w+2*cell_w, c_y+c_h+2*cell_h), white, 0, false);
//	factory->drawGrid( image, r_grid_left, core::dimension2du(cell_w,cell_h), white, true, true);
//	factory->drawGrid( image, r_grid_right, core::dimension2du(cell_w,cell_h), white, false, true);
//	factory->drawRect( image, r_dst, black, 2, false);
//
//	// bool render axis arrow
//	// bool bVertical == 0, default render horizontal ( x-axis )
//	// 				  == 1, render vertical ( y-axis )
//	// bool bHideText == false, default render all text
//	// 				  == true, render no text
//	// bool bHideArrow == false, default render arrow
//	// 				  == true, render no arrow
//	// f32 fMin, fMax, fValue, fStep
//	//
//
//	//! render texts for negative -x axis
//	core::position2df dir(-1,0);
//	core::position2df pos( c_x+c_w/2,c_y+c_h+2 );
//	f32 fMin = r_data.UpperLeftCorner.X;
//	f32 fMax = 180.0f;
//	s32 iStepCount = core::abs_<s32>( core::floor32( 0.05f*(fMax-fMin) ) );
//	f32 fStep = 0.5f*(f32)c_w / (f32)iStepCount;
//
//	f32 x = pos.X;
//	u32 i = 0;
//	while ( i < iStepCount )
//	{
//		f32 f_angle = 180.0f-10.0f*(f32)i;
//		core::position2di pos0 = astro::CSonnenstand( 0, f_angle, 0).projectCartesian2di( r_data, r_dst, true);
//		core::stringw txt = L""; txt += core::floor32(0.1f*f_angle); txt += L"°";
//		factory->drawText( image, driver, fontAxisText, pos0.X, pos0.Y, txt, black, 1, 0, 0, false );
//		i++;
//	}
//
//	//! render texts for positive +x axis
//	dir = core::position2df( 1,0 );
//	pos = core::position2df ( c_x+c_w/2,c_y+c_h+2 );
//	fMin = 180.0f;
//	fMax = r_data.LowerRightCorner.X;
//	iStepCount = core::abs_<s32>( core::floor32( 0.05f*(fMax-fMin) ) );
//	fStep = 0.5f*(f32)c_w / (f32)iStepCount;
//
//	x = pos.X;
//	i = 0;
//	while ( i < iStepCount )
//	{
//		f32 f_angle = 180.0f+10.0f*(f32)i;
//		core::position2di pos0 = astro::CSonnenstand( 0, f_angle, 0 ).projectCartesian2di( r_data, r_dst, true);
//		core::stringw txt = L""; txt += core::floor32(0.1f*f_angle); txt += L"°";
//		factory->drawText( image, driver, fontAxisText, pos0.X, pos0.Y, txt, black, 1, 0, 0, false );
//		i++;
//	}
//
//	//! render texts for positive +y axis
//	dir = core::position2df( 0,1 );
//	pos = core::position2df ( c_x+c_w/2-8,c_y+c_h+2 );
//	fMin = r_data.UpperLeftCorner.Y;
//	fMax = r_data.LowerRightCorner.Y;
//	iStepCount = core::abs_<s32>( core::floor32( 0.05f*(fMax-fMin) ) );
//	fStep = 0.5f*(f32)c_h / (f32)iStepCount;
//
//	// bool render horizontal axis
//	f32 y = c_y + c_h;
//	i = 0;
//	while ( i < iStepCount )
//	{
//		f32 f_angle = 0.0f+10.0f*(f32)i;
//		core::position2di pos0 = astro::CSonnenstand( 0, f_angle, 0).projectCartesian2di( r_data, r_dst, true);
//		core::stringw txt = L""; txt += core::floor32(0.1f*f_angle); txt += L"°";
//		factory->drawText( image, driver, fontAxisText, pos.X, pos.Y, txt, black, 1, 0, 0, false );
//		i++;
//	}


//	core::dimension2du tickCount( (u32)core::floor32( 0.05f*r_data.getWidth() ),(u32)core::floor32( 0.1f*r_data.getWidth() ) );
//	u32 stepX = core::s32_clamp( (f32)c_w / (f32)tickCount.Width, 0, 37 );
//	u32 stepY = (u32)core::abs_<s32>(0.1f*r_data.getHeight());
//
//	//! draw y-axis texts
//	ssd_points.reallocate( tick
//	ssd_points.set_used( 0 );
//
//	}
////
//	//! draw x-axis texts
//
//	ssd_points.reallocate(  );
//	ssd_points.set_used( 0 );
//
//	for (u32 i=0; i<=36; i++)
//	{
//		ssd_points.push_back( astro::CSonnenstand( 0, i*10, 0) );
//	}
//
//	for (u32 i = 0; i<ssd_points.size(); i++)
//	{
//		core::position2di pos = ssd_points[i].projectCartesian2di( r_data, r_dst, true);
//		core::stringw myt = L"";
//		myt += i;
//		if (i>0)
//			myt += L"0";
//		myt += L"°";
//		factory->drawText( image, driver, fontAxisText, pos.X+5, pos.Y+8, myt.c_str(), black, 0, -1, 0, false );
//	}

