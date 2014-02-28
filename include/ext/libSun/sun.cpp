///
/// @mainpage Sonnenstandsdiagramme (c) 2008 - 2011 by BenjaminHampe@gmx.de
///
/// Diese Software ist für jegliche, nicht kommerzielle Verwendung freigegeben.
/// @section Was kann diese Software?
///
/// <ul>
/// <li>Sonnenstandsdiagramme berechnen</li>
/// <li>2D/3D Graphen erstellen</li>
/// <li>viele Erweiterungen für die Irrlicht-Engine</li>
/// <li>eigene 2D Bibliothek zur Manipulation von Bildern</li>
/// <li>eigene Font Bibliothek zum Rendern von Text auf Bildern</li>
/// <li>lesen und schreiben von Graphikformaten SVG,XPM</li>
/// <li>portabel</li>
/// </ul>
/// <br>
///
/// @section Extensions to Irrlicht-Engine 1.7.2
///

#include "sun.h"

#include "../irrUtils.h"

namespace irr
{

} // end namespace irr

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
/// @author 	(c) 2008 - 2011 by BenjaminHampe@gmx.de
/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
irr::core::stringc dbStrGeo(irr::f64 geo)
{
    irr::core::stringc tmp;
    irr::f64 a,b,c;
    geo = irr::core::Math::WrapAngle(geo);
    a = irr::core::Math::IPart(geo);
    b = (geo-a)*60.0;
    c = (((geo-a)*60.0)-irr::core::Math::IPart(b))*60.0;
    if (a<10.0) tmp += "0";
    tmp += (irr::s32)a;
    tmp += "deg";
    if (b<10.0) tmp += "0";
    tmp += (irr::s32)b;
    tmp += "'";
    if (c<10.0) tmp += "0";
    tmp += irr::Utils::formatValue(c,2);
    tmp += "\"";
    return tmp;
}

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
/// @author 	(c) 2008 - 2011 by BenjaminHampe@gmx.de
/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
/// Longitude
irr::core::stringc dbStrLon(irr::f64 geo)
{
    return irr::core::stringc("O ")+dbStrGeo(geo);
}

/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
/// @author 	(c) 2008 - 2011 by BenjaminHampe@gmx.de
/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// ///
/// Latitude
irr::core::stringc dbStrLat(irr::f64 geo)
{
    return irr::core::stringc("N ")+dbStrGeo(geo);
}

//
///// @return data as opengl display list
//GLuint
//Sonnenstandskurve::glGenList(const core::zoom2df& zoomRect, const core::rect2di& imageRect )
//{
//   return 0;
//}
//
//void
//Sonnenstandskurve::glDraw(const core::zoom2df& zoomRect, const core::rect2di& imageRect )
//{
//  irr::u32 size = Data.size();
//  if (size<2) return;
//
//  f32 old_line_width;
//  glGetFloatv(GL_LINE_WIDTH, &old_line_width);
//
//  u8 r = ARGB_R(LineColor);
//  u8 g = ARGB_G(LineColor);
//  u8 b = ARGB_B(LineColor);
//  u8 a = ARGB_A(LineColor);
//
//  irr::s32 x1,y1,x2,y2;
////
////	f32 x1 = 0.0f;
////	f32 y1 = 0.0f;
////	f32 x2 = 0.0f;
////	f32 y2 = 0.0f;
//  bool lineStipple = false;
//  glLineWidth(LineWidth);
//  glEnable(GL_LINE_STIPPLE);
//  glLineStipple(1, LineStipple);
//  lineStipple = true;
//
//   GLuint white = 0xFFFFFFFF;
//   GLuint black = 0xFF000000;
//   GLuint yellow= 0xFFFFFF00;
//  GLuint red   = 0xFFFF0000;
//   GLuint green = 0xFF00FF00;
//   GLuint blue  = 0xFF0000FF;
//   GLuint orange= 0xFFFF8020;
//
//   f32 z(500);
//
//   glBegin(GL_QUADS);
//   glColor4uiv(&white);
//   glVertex3f(0,0,z);
//   glVertex3f(0,1050,z);
//   glVertex3f(1680,1050,z);
//   glVertex3f(1680,0,z);
//   glEnd(); z--;
//
//  glBegin(GL_LINES);
//  glColor4uiv(&black);
//  for (GLuint j=0; j<168; j++) { glVertex3f(j*10,0,0); glVertex3f(j*10,1050,0); }
//  for (GLuint i=0; i<105; i++) { glVertex3f(0,i*10,0); glVertex3f(1680,i*10,0); }
//  glEnd(); z--;
////	glBegin(GL_LINES);
////
////	glColor4i(r,g,b,a);
////	for (irr::u32 p=0; p<size-1; ++p)
////	{
////		x1 = (irr::s32)Round(days_[p]->Data[0].azimut_*(irr::f64)imageRect.getWidth()/360.0)+imageRect.getX();
////		y1 = imageRect.getHeight()-(irr::s32)Round(Data[p].hoehe_*(irr::f64)imageRect.getHeight()/360.0)+imageRect.getY();
////		x2 = (irr::s32)Round(days_[p+1][0].azimut_*(f32)imageRect.getWidth()/360.0)+imageRect.getX();
////		y2 = imageRect.getHeight()-((irr::s32)Round(Data[p+1].hoehe_*(f32)imageRect.getHeight()/360.0)+imageRect.getY());
////		glVertex2i(x1, y1);
////		glVertex2i(x2, y2);
////	}
////
////	glEnd();
////	glDisable(GL_LINE_STIPPLE);
////	glLineWidth(old_line_width);
//}
//
///// @return data as irrlicht mesh (3d triangles)
//irr::core::stringw
//Sonnenstandskurve::Mesh3D()
//{
//   irr::core::stringw mesh;
//   return mesh;
//}
//
///// @brief sort data by azimut [ smallest to highest ], [-360...360]
//void
//Sonnenstandskurve::sort()
//{
//
//}
//
///// @return sun position of first! sunrise
//Sonnenstand
//Sonnenstandskurve::sunrise()
//{
//   return Sonnenstand(0,0,0);
//}
//
///// @return sun position of first! sunset
//Sonnenstand
//Sonnenstandskurve::sunset()
//{
//   return Sonnenstand(0,0,0);
//}
//
///// @return sun position of highest sun elevation
//Sonnenstand
//Sonnenstandskurve::zenit()
//{
//   return Sonnenstand(0,0,0);
//}
//
///// @return array index of sun position of first! sunrise
//irr::s32
//Sonnenstandskurve::index_of_sunrise()
//{
//   return 0;
//}
//
///// @return array index of sun position of first! sunset
//irr::s32
//Sonnenstandskurve::index_of_sunset()
//{
//   return 0;
//}
//
///// @return array index of sun position of highest sun elevation
//irr::s32
//Sonnenstandskurve::index_of_zenit()
//{
//   return 0;
//}
//
///// @return julian day of first! sunrise
//irr::f64
//Sonnenstandskurve::time_of_sunrise()
//{
//   return 0.0;
//}
//
///// @return julian day of first! sunset
//irr::f64
//Sonnenstandskurve::time_of_sunset()
//{
//   return 0.0;
//}
//
///// @return julian day of highest sun elevation
//irr::f64
//Sonnenstandskurve::time_of_zenit()
//{
//   return 0.0;
//}
//
////! @class Sonnenstandsdiagramm
//
////! constructor
//Sonnenstandsdiagramm::Sonnenstandsdiagramm()
//: Location("Dresden")
//, Year(2011)
//, Longitude(13.2)
//, Latitude(51.23)
//, Method(CalMethod::VSOP87)
//, Computations(24*60)
//, Type(PlotType::CARTESIAN)
//{}
//
////! constructor
//Sonnenstandsdiagramm::Sonnenstandsdiagramm
//(
//  const irr::core::stringw& name,
//  irr::s32 year,
//  irr::f64 geoEast,
//  irr::f64 geoNord,
//  const CalMethod& method,
//  const PlotType& plotType
//)
//: Location(name)
//, Year(year)
//, Longitude(geoEast)
//, Latitude(geoNord)
//, Method(method)
//, Computations(24*60)
//, Type(plotType)
//{}
//
////! destructor
//Sonnenstandsdiagramm::~Sonnenstandsdiagramm()
//{
//	if (Days.size()>0)
//	{
//		for (irr::u32 i=0; i<Days.size(); ++i)
//		{
//			Sonnenstandskurve* kurve = Days[i];
//			kurve->Data.clear();
//			delete kurve;
//			kurve = NULL;
//		}
//		Days.clear();
//	}
//
//	if (Hours.size()>0)
//	{
//		for (irr::u32 i=0; i<Hours.size(); ++i)
//		{
//			Sonnenstandskurve* kurve = Hours[i];
//			kurve->Data.clear();
//			delete kurve;
//			kurve = NULL;
//		}
//		Hours.clear();
//	}
//}
//
//void
//Sonnenstandsdiagramm::defaults()
//{
//	Location = L"Dresden";
//	Year = 2011;
//	Longitude = 13.2;
//	Latitude = 51.7;
//	Method = CalMethod::CALSKY;
//	Computations = 24*60;
//	irr::u32 Width = 1680;
//	irr::u32 Height = 1050;
//	irr::f64 Aspect = DIN_A4;
//
//	Days.clear();
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year,6,21), JD(Year, 6,22), 3.0f, 0xFF00FF00, 0xFFFF)); // Maximum (
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year,12,21),JD(Year,12,22), 2.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year,3,21), JD(Year, 3,22), 2.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year,9,21), JD(Year, 9,22), 3.0f, 0xFFFF0000, 0xFFFF)); // Minimum
//
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 1,1), JD(Year,1,2), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 2,1), JD(Year,2,2), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 3,1), JD(Year,3,2), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 4,1), JD(Year,4,2), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 5,1), JD(Year,5,2), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 6,1), JD(Year,6,2), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 7,1), JD(Year,7,2), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 8,1), JD(Year,8,2), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 9,1), JD(Year,9,2), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year,10,1), JD(Year,10,2), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year,11,1), JD(Year,11,2), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year,12,1), JD(Year,12,2), 1.0f, 0xFFFF0000, 0xFFFF));
//
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 1,21), JD(Year,1,22), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 2,21), JD(Year,2,22), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 3,21), JD(Year,3,22), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 4,21), JD(Year,4,22), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 5,21), JD(Year,5,22), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 6,21), JD(Year,6,22), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 7,21), JD(Year,7,22), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 8,21), JD(Year,8,22), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year, 9,21), JD(Year,9,22), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year,10,21), JD(Year,10,22), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year,11,21), JD(Year,11,22), 1.0f, 0xFFFF0000, 0xFFFF));
//	Days.push_back(new Sonnenstandskurve( Location, Method, Computations, Longitude, Longitude, JD(Year,12,21), JD(Year,12,22), 1.0f, 0xFFFF0000, 0xFFFF));
//
//
//// 	Analemmas
//
//	irr::u32 DaysOfYear = getDaysOfYear(Year);
//	Hours.reallocate(24);
//
//	for (irr::u32 i=0; i<Hours.size(); ++i)
//	{
//		// Alle Stundenlinien (Analemmas) mit Messpunkten für alle Tages des Jahres (Inkrement 1.0 == 1 Tag)
//		Hours[i] = new Sonnenstandskurve(
//			Location, Method, Computations,
//			Longitude, Latitude,
//			JD(Year, 1, 21, i, 0, 0),
//			JD(Year+1, 1, 21, i, 0, 0),
//			1.0f, 0xFF000000, 0x7777);
//	}
//
//} // END FUNCTION defaults()
//
//
//irr::core::stringw
//Sonnenstandsdiagramm::xml()
//{
//	irr::core::stringw s(L"");
//	s+=xml::tag("sonnenstandsdiagramm", xml::attribute("size", irr::core::stringc(sizeof(Sonnenstandsdiagramm))));
//	s+=xml::tag("location","",Location);
//	s+=xml::tag("year","",irr::core::stringc(Year));
//	s+=xml::tag("longitude","",irr::core::stringc(Longitude));
//	s+=xml::tag("latitude","",irr::core::stringc(Latitude));
//	s+=xml::tag("method","",dbStr(Method));
//	s+=xml::tag("computations","",irr::core::stringc(Computations));
//	s+=xml::tag("days","",irr::core::stringc(Days.size()));
//	s+=xml::tag("hours","",irr::core::stringc(Hours.size()));
//
//	for (irr::u32 i=0; i<Days.size(); ++i)
//	{
//		Sonnenstandskurve* kurve = Days[i];
//		s+=kurve->xml();
//		s+="\n";
//	}
//	for (irr::u32 i=0; i<Hours.size(); ++i)
//	{
//		Sonnenstandskurve* kurve = Hours[i];
//		s+=kurve->xml();
//		s+="\n";
//	}
//	s+=xml::end("sonnenstandsdiagramm");
//	return s;
//}
//
//io::path
//Sonnenstandsdiagramm::getUniqueFilename()
//{
//	io::path f0 = fs->getWorkingDirectory();
//	io::path f1;
//	f0+="/";
//	f0+=Location;
//	f0+="_";
//	f0+=Year;
//	f0+="_";
//	f0+=dbStr(Method);
//	f1=f0;
//	f0+=".txt";
//	f1+=".xml";
//	return f1;
//}
//
//bool
//Sonnenstandsdiagramm::load(const io::path& filename) //! lade XML datei
//{
//	//    // create the reader using one of the factory functions
//	//    wfstream logger("XML_Parser_log.txt", ios::in);
//	//    logger<<L"Begin"<<endl;
//	//
//	//    io::IrrXMLReader* xmlReader = io::createIrrXMLReader(filename.c_str());
//	//
//	//    if (!xmlReader) return;
//	//
//	//    irr::core::stringw nodeName;
//	//    irr::core::stringw nodeData;
//	//    irr::core::stringw nodeAttr;
//	//    irr::core::stringw className(L"Sonnenstandskurve");
//	//
//	//    Sonnenstandskurve* ssk = NULL;
//	//    irr::u32 attrCount;
//	//
//	//    // parse the file until end reached
//	//    while(xmlReader && xmlReader->read())
//	//    {
//	//        switch(xmlReader->getNodeType())
//	//        {
//	//        case io::EXN_UNKNOWN:
//	//            break;
//	//
//	//        case io::EXN_TEXT:
//	//
//	//            nodeName = xmlReader->getNodeName();
//	//            nodeData = xmlReader->getNodeData();
//	//            attrCount = xmlReader->getAttributeCount();
//	//
//	//            logger<<L"nodeName = "<<nodeName.c_str()<<endl;
//	//            logger<<L"nodeData = "<<nodeData.c_str()<<endl;
//	//            logger<<L"nodeType = EXN_TEXT"<<endl;
//	//            logger<<L"attrCount = "<<attrCount<<endl;
//	//            for (irr::u32 a = 0;  a<attrCount; ++a)
//	//            {
//	//                logger<<L"Attribute ("<<a<<L") = "<<xmlReader->getAttributeName(a)<<endl;
//	//            }
//	//
//	//            if (nodeName==className)
//	//            {
//	//                ssk = new Sonnenstandskurve;
//	//                Days.push_back(ssk);
//	//            }
//	//            break;
//	//
//	////						if (irr::core::stringw(L"model")==xmlReader->getNodeName())
//	////							nodeAttr = xmlReader->getAttributeValue("file");
//	////						else
//	////						if (!strcmp("messageText", xmlReader->getNodeName())
//	////							nodeAttr = xmlReader->getAttributeValue("caption");
//	//        case io::EXN_ELEMENT:
//	//            break;
//	//        case io::EXN_CDATA:
//	//            break;
//	//        case io::EXN_COMMENT:
//	//            break;
//	//        case io::EXN_NONE:
//	//            break;
//	//        default:
//	//            break;
//	//        }
//	//    }
//	//    // delete the xmlReader parser after usage
//	//    delete xmlReader;
//	//
//	//    logger.close();
//	return false;
//}
//
//bool
//Sonnenstandsdiagramm::save(const io::path& filename) const //! speichere XML datei
//{
//	return false;
//}
//
//
//
//irr::u32
//Sonnenstandsdiagramm::getDayCount() const
//{
//	return Days.size();
//}
//irr::u32
//Sonnenstandsdiagramm::getHourCount() const
//{
//	return Hours.size();
//}
//
////! Durchsuche nach MinMax
//core::vector2d<irr::f64>
//Sonnenstandsdiagramm::getMin() const
//{
//	core::vector2d<irr::f64> m(500,500);
//
//	irr::u32 size = Days.size();
//	for (irr::u32 x=0; x<size; ++x)
//	{
//		Sonnenstandskurve* kurve = Days[x];
//		for (irr::u32 y=0; y < (kurve->Data.size()); ++y)
//		{
//			Sonnenstand& sonne = kurve->Data[y];
//
//			if (m.X>sonne.Azimut)
//				m.X=sonne.Azimut;
//			if (m.Y>sonne.Hoehe)
//				m.Y=sonne.Hoehe;
//		}
//	}
//	return m;
//}
//
////! Durchsuche nach Max
//core::vector2d<irr::f64>
//Sonnenstandsdiagramm::getMax() const
//{
//	core::vector2d<irr::f64> m(-500,-500);
//
//	irr::u32 size = Days.size();
//	for (irr::u32 x=0; x<size; ++x)
//	{
//		Sonnenstandskurve* kurve = Days[x];
//		for (irr::u32 y=0; y < (kurve->Data.size()); ++y)
//		{
//			Sonnenstand& sonne = kurve->Data[y];
//
//			if (m.X<sonne.Azimut)
//				m.X=sonne.Azimut;
//			if (m.Y<sonne.Hoehe)
//				m.Y=sonne.Hoehe;
//		}
//	}
//	return m;
//}
//
////! Durchsuche nach MinMax
//core::rect<irr::f64>
//Sonnenstandsdiagramm::getBoundingRect() const
//{
//	core::rect<irr::f64> minmax(360,90,-360,-90);
//	irr::u32 size = Days.size();
//	for (irr::u32 x=0; x<size; ++x)
//	{
//		Sonnenstandskurve* kurve = Days[x];
//		for (irr::u32 y=0; y<(kurve->Data.size()); ++y)
//		{
//			Sonnenstand& sonne = kurve->Data[y];
//			if (minmax.UpperLeftCorner.X>sonne.Azimut)
//				minmax.UpperLeftCorner.X=sonne.Azimut;
//			if (minmax.UpperLeftCorner.Y>sonne.Hoehe)
//				minmax.UpperLeftCorner.Y=sonne.Hoehe;
//			if (minmax.LowerRightCorner.X<sonne.Azimut)
//				minmax.LowerRightCorner.X=sonne.Azimut;
//			if (minmax.LowerRightCorner.Y<sonne.Hoehe)
//				minmax.LowerRightCorner.Y=sonne.Hoehe;
//		}
//	}
//	return minmax;
//}
//
//irr::core::stringw
//Sonnenstandsdiagramm::svg(irr::u32 w, irr::u32 h) const
//{
//	irr::core::stringw final;    // IRR String that will be returned
//	ostringstream s;        // STL StringStream
//	s<<xml::header();       // printing SVG/XML code to StringStream
//	s<<svg::header(0,0,w,h,"px", 0,0,1680,1050,0xFFFFFFFF);
//	s<<xml::comment("(c) 2009-2011 by Benjamin Hampe");
//
//// Gitternetz
//	irr::f64 x = 0.0;
//	irr::f64 y = 0.0;
//	irr::f64 cx = 0.5*w;
//	irr::f64 cy = 0.5*h;
//
//	s<<svg::line(cx,y,cx,y+100, svg::stroke(0xFF000000, 1, svg::Metric::PX, 0x7777));
//	s<<svg::line(x,cy,x+100,cy, svg::stroke(0xFF000000, 1, svg::Metric::PX, 0x5858));
//
//// Tageslinien
//
//	for (irr::u32 k=0; k<(Days.size()); ++k)
//	{
//		irr::u32 c=0;
//		irr::core::stringc dataStr("");
//		Sonnenstandskurve* kurve = Days[k];
//		for (irr::u32 i=0; i<(kurve->Data.size()); ++i)
//		{
//			Sonnenstand& sonne = kurve->Data[i];
//			core::vector2d<irr::f64> v(dbWrap360(180.0+sonne.Azimut), 90.0-sonne.Hoehe);
//			if (v.Y>=0.0)
//			{
//				//v.X = (v.X)*w/360.0;
//				//v.Y = (v.Y)*h/90.0;
//				//				v.X /= 360.0;
//				//				v.Y /= 110.0;
//				//				v.X *= w;
//				//				v.Y *= h;
//				//				v.X += 0.5*w;
//				//v.X += 0.5*imgX;
//				//				v.Y += 0.5*imgY;
//
//				if (c==0)
//					dataStr+="M ";
//				else
//					dataStr+=" L ";
//
//				dataStr+=v.X;
//				dataStr+=",";
//				dataStr+=v.Y;
//				c++;
//			}
//		}
//		s<<"<path "
//		 <<xml::attribute("fill","none")
//		 <<svg::stroke( kurve->LineColor,
//						kurve->LineWidth,
//						svg::Metric::PX,
//						kurve->LineStipple)
//		 <<xml::attribute("d",dataStr)
//		 <<" />\n";
//	}
//
//
//	// Analemmas
//
//	irr::core::stringc dataStr("");
//	for (irr::u32 i=0; i<Hours.size(); ++i)
//	{
//		irr::u32 c=0;
//		Sonnenstandskurve* kurve = Hours[i];
//		irr::u32 n = kurve->Data.size();
//		dataStr="";
//		for (irr::u32 j=0; j<n; ++n)
//		{
//			Sonnenstand& sonne = kurve->Data[j];
//
//			core::vector2d<irr::f64> v(dbWrap360(180.0+sonne.Azimut), 90.0-sonne.Hoehe);
//
//			if (v.Y>=0.0)
//			{
//				//v.X /= 180.0; // [-1..1]
//				//v.Y /= 90.0; // [-1..1]
//				//v.X *= w;
//				//v.Y *= h;
//				//v.X += 0.5*w;
//				//v.Y += y;
//				//v.X += x;
//				if (c==0)
//					dataStr+="M ";
//				else
//					dataStr+=" L ";
//
//				dataStr+=v.X;
//				dataStr+=",";
//				dataStr+=v.Y;
//				c++;
//			}
//
//		}
//
//		s<<"<path "
//		 <<xml::attribute("fill","none")
//		 <<svg::stroke( kurve->LineColor,
//						kurve->LineWidth,
//						svg::Metric::PX,
//						kurve->LineStipple)
//		 <<xml::attribute("d",dataStr)
//		 <<" />\n";
//
//	}
//	s<<svg::dot(cx, cy);
//	s<<svg::dot(x, y);
//	s<<svg::dot(x+w, y);
//	s<<svg::dot(x+w, y+h);
//	s<<svg::dot(x, y+h);
//	s<<svg::end();
//
//	final = s.str().c_str();
//	return final;
//}
//
//
//video::ITexture*
//Sonnenstandsdiagramm::render(irr::IrrlichtDevice* device, irr::s32 imgX, irr::s32 imgY) const
//{
//	video::ITexture* tex = (video::ITexture*)0;
//	/*
//	if (!device) return;
//	const irr::u32 w = device->getVideoDriver()->getCurrentRenderTargetSize().Width;
//	const irr::u32 h = device->getVideoDriver()->getCurrentRenderTargetSize().Height;
//	//  glClearColor(1, 1, 1, 1);   // Hintergrundfarbe
//	//	glClearDepth( 1.0 );		// Tiefentest deaktiviert
//	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	glDisable( GL_LIGHTING );	// Licht deaktiviert
//	glShadeModel( GL_SMOOTH );	// kein Antialiasing
//	glDisable( GL_DEPTH_TEST );	// Tiefentest deaktiviert
//	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
//	glViewport(0,0,width,height);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0, width, 0, height, -100.0, 100.0); // DIN A4 - quer
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	f32 AspectRatio = (f32)w/(f32)h;
//
//	//	gluOrtho2D(0.f,100.0f,,0);
//	//	glTranslatef(0.5f*w, 0.5f*h,0);
//	*/
//	if (!device)
//	{
//		return 0;
//	}
//
//	GLuint list = glGenLists(1);
//	glNewList(list,GL_COMPILE);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity();
//	glOrtho(0,imgX,0,imgY,-100,100);
//	glBegin(GL_LINE_STRIP);
//	glDisable(GL_LINE_STIPPLE);
//	glLineWidth(1.0f);
//
//	for (irr::u32 k=0; k<(Days.size()); ++k)
//	{
//		Sonnenstandskurve* kurve = Days[k];
//		for (irr::u32 m=0; m < (kurve->Data.size()); ++m)
//		{
//			Sonnenstand& sonne = kurve->Data[m];
//			irr::f64 x = (sonne.Azimut+180.0)*(irr::f64)imgX/360.0;
//			irr::f64 y = imgY-(90.0-sonne.Hoehe)*(irr::f64)imgY/360.0;
//			irr::u32 glc;
//			video::SColor color;
//			color.color = kurve->LineColor;
//			color.toOpenGLColor((u8*)&glc);
//			glColor4ubv((GLubyte*)&glc);
//			glVertex2d(x,y);
//		}
//	}
//
//	glEnable(GL_LINE_STIPPLE);
//	glLineStipple(1,0xFFFF);
//	glLineWidth(1.0f);
//	for (irr::u32 k=0; k<24; ++k)
//	{
//		cout << "render OpenGL hour-line "<<k<<endl;
//
//		Sonnenstandskurve* kurve = Hours[k];
//		for (irr::u32 m=0; m< (kurve->Data.size()); ++m)
//		{
//			Sonnenstand& sonne =kurve->Data[m];
//			irr::f64 x = (sonne.Azimut+180.0)*(irr::f64)imgX/360.0;
//			irr::f64 y = imgY-(90.0-sonne.Hoehe)*(irr::f64)imgY/360.0;
//			irr::u32 glc;
//			video::SColor color;
//			color.color = kurve->LineColor;
//			color.toOpenGLColor((u8*)&glc);
//			glColor4ubv((GLubyte*)&glc);
//			glVertex2d(x,y);
//		}
//	}
//	glDisable(GL_LINE_STIPPLE);
//	glEnd();
//	glEndList();
//
//	video::IVideoDriver* driver = device->getVideoDriver();
//
//	tex = driver->addRenderTargetTexture(core::dimension2du(imgX,imgY), "rt", video::ECF_A8R8G8B8);
//	if (!tex)
//	{
//		cout << " OffScreenRenderTargetTexture konnte nicht erstellt werden!!!\n";
//		cout << " Sollen krassere Maßnahmen ergriffen werden?\nJa/Nein: "<<flush;
//		char buf[32];
//		cin >> buf;
//		if (tolower(buf[0])=='y' || tolower(buf[0])=='j')
//		{
//			cout<<"Nächster Versuch beginnt..."<<endl;
//		}
//		else
//		{
//			exit(1);
//		}
//	}
//	video::SColor bg(255,255,255,255);
//	driver->beginScene(true,true,bg);
//	driver->setRenderTarget(tex,true,true,bg);
//	glCallList(list);
//	driver->endScene();
////             video::IImage* img=driver->createImage(tex, core::dimension2di(0,0), tex->getOriginalSize());
////             driver->writeImageToFile(img,uri);
//	return tex;
//}
//
//Sonnenstandskurve*
//Sonnenstandsdiagramm::getDay(irr::u32 i)
//{
//	if (i<=Days.size())
//		i=Days.size()-1;
//	return Days[i];
//}
//
//Sonnenstandskurve*
//Sonnenstandsdiagramm::getHour(irr::u32 i)
//{
//	if (i<=Hours.size())
//		i=Hours.size()-1;
//	return Hours[i];
//}
