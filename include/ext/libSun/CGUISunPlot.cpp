/***************************************************************
 * Name:      CGUISunPlot.h
 * Author:    Benjamin Hampe (BenjaminHampe@gmx.de)
 * License:	  LGPL
 **************************************************************/

#include "CGUISunPlot.h"

#include <irrlicht.h>
#include <../source/Irrlicht/CSceneManager.h>

#include "../irrTypedef.h"
#include "../irrImage.h"
#include "../ImageTool.h"

#include "CSonnenstand.h"
#include "CSunCurve.h"
#include "CSunData.h"

namespace irr{
namespace gui{

//! get plot-dimension
s32 CGUISunPlot::getWidth( ) const
{
    return AbsoluteRect.getWidth();
}

//! get plot-dimension
s32 CGUISunPlot::getHeight( ) const
{
    return AbsoluteRect.getHeight();
}


core::matrix4 CGUISunPlot::LookAt( const core::vector3df& eye, const core::vector3df& target, const core::vector3df& up )
{
    core::vector3df zaxis = (target - eye);    // The "look-at" vector.
    zaxis.normalize();
    core::vector3df xaxis = (up.crossProduct(zaxis)).normalize();// The "right" vector.
    xaxis.normalize();
    core::vector3df yaxis = zaxis.crossProduct(xaxis);     // The "up" vector.

    // Create a 4x4 orientation matrix from the right, up, and at vectors
    core::matrix4 dir;
    dir(0,0) = xaxis.X; dir(0,1) = yaxis.X; dir(0,2) = zaxis.X; dir(0,3) = 0;
    dir(1,0) = xaxis.Y; dir(1,1) = yaxis.Y; dir(1,2) = zaxis.Y; dir(1,3) = 0;
    dir(2,0) = xaxis.Z; dir(2,1) = yaxis.Z; dir(2,2) = zaxis.Z; dir(2,3) = 0;
    dir(3,0) = 0;       dir(3,1) = 0;       dir(3,2) = 0;       dir(3,3) = 1;

    // Create a 4x4 translation matrix by negating the eye position.
    core::matrix4 pos = core::IdentityMatrix;
    pos(3,0) = -eye.X;
    pos(3,1) = -eye.Y;
    pos(3,2) = -eye.Z;

    // Combine the orientation and translation to compute the view matrix
    return ( pos * dir );
}

//! constructor
CGUISunPlot::CGUISunPlot( IGUIEnvironment* env, IGUIElement* parent, s32 id, const core::recti& rectangle)
: IGUIElement(EGUIET_ELEMENT, env, parent, id, rectangle)
, IsDirty(false), Data(0)
{

}
//! destructor
CGUISunPlot::~CGUISunPlot()
{

}



//! Create from stored data-pointer
void CGUISunPlot::create( )
{
    if (!Data)
    {
        IsDirty = false;
        return;
    }

    const video::SColor SC_NULL(0,0,0,0);
    const video::SColor SC_BLACK(255,0,0,0);
    const video::SColor SC_WHITE(255,255,255,255);

    u32 curveCount = Data->getCurveCount();

    MeshBuffer.reallocate( curveCount );
    MeshBuffer.set_used( 0 );
    PrimTypes.reallocate( curveCount );
    PrimTypes.set_used( 0 );

    const s32 w = AbsoluteRect.getWidth();
    const s32 h = AbsoluteRect.getHeight();

    const core::rectf r_optimal = Data->getOptimalRect();
    //const core::recti r_canvas(-1,-1,1,1); // wrong, must be r_canvas
    const core::rectf r_canvas( -1, -1, 1, 1 ); // wrong, must be r_canvas

    video::SMaterial defaultMaterial;
    defaultMaterial.MaterialType = video::EMT_SOLID;
    defaultMaterial.Wireframe = false;
    defaultMaterial.Lighting = false;
    defaultMaterial.FogEnable = false;

    for (u32 i=0; i<curveCount; i++)
    {
        astro::CSunCurve* curve = Data->getCurve(i);
        if (curve)
        {
            u32 vertexCount = curve->getPointCount();

            /// create EPT_LINE_STRIP
            if (vertexCount>1)
            {
                scene::SMeshBuffer* buffer = new scene::SMeshBuffer();
                if (buffer)
                {
                    buffer->Material = defaultMaterial;
                    buffer->BoundingBox.reset( 0,0,0 );
                    buffer->Vertices.reallocate( vertexCount );
                    buffer->Vertices.set_used( 0 );
                    buffer->Indices.reallocate( vertexCount );
                    buffer->Indices.set_used( 0 );

                    video::SColor color = curve->getLineColor();
                    for (u32 j=0; j<vertexCount; j++)
                    {
                        const astro::CSonnenstand& s = curve->getPoint(j);
                        core::position2df pos = s.projectCartesian2df( r_optimal, r_canvas, false );
                        u32 index = buffer->Vertices.size();

                        buffer->Vertices.push_back( video::S3DVertex( pos.X, pos.Y, 0, 0,0,-1, color, 0,0 ) );
                        buffer->Indices.push_back( index );
                    }

                    buffer->recalculateBoundingBox();
                    BoundingBox.addInternalBox( buffer->getBoundingBox() );

                    MeshBuffer.push_back( buffer );
                    PrimTypes.push_back( scene::EPT_LINE_STRIP );
                }
            }
        }

    }

}

//! Set new data-pointer, create or clear internal render-infos if nessecary
void CGUISunPlot::setData( CSunData* data )
{
    if (!data)
        clear();

    Data = data;

    create();
}

//! draws the element and its children
void CGUISunPlot::draw()
{
    video::IVideoDriver* driver = Environment->getVideoDriver();
    gui::IGUIFont* font = Environment->getSkin()->getFont(EGDF_DEFAULT);

    const video::SColor SC_NULL(0,0,0,0);
    const video::SColor SC_BLACK(255,0,0,0);
    const video::SColor SC_WHITE(255,255,255,255);
    const video::SColor SC_YELLOW(255,255,255,0);
    const video::SColor SC_RED(255,255,0,0);
    const video::SColor SC_GREEN(255,0,255,0);
    const video::SColor SC_BLUE(255,0,0,255);

    const s32 x = AbsoluteRect.UpperLeftCorner.X;
    const s32 y = AbsoluteRect.UpperLeftCorner.Y;
    const s32 w = getWidth();
    const s32 h = getHeight();

    const core::recti viewport(x+1,y+1,x+w-1,y+h-1);

    if (!Data)
    {

        font->draw( L"No Data available", viewport, SC_RED, true, true);
        return;
    }



    const core::recti viewport_old = driver->getViewPort();

   ProjectionMatrix.buildProjectionMatrixOrthoLH( (f32)viewport.getWidth(),(f32)viewport.getHeight(), 0.1f,10000.0f);
    //ProjectionMatrix *= LookAt( core::vector3df(0,0,-100),core::vector3df(0,0,100), core::vector3df(0,1,0) );

    driver->setViewPort( viewport );
    //core::matrix4 scaleMatrix;
    //scaleMatrix.setScale( core::vector3df(10,10, 1) );
    //driver->setTransform( video::ETS_WORLD, scaleMatrix );
    driver->setTransform( video::ETS_WORLD, core::IdentityMatrix );
    driver->setTransform( video::ETS_VIEW, core::IdentityMatrix );
    driver->setTransform( video::ETS_PROJECTION, ProjectionMatrix );
    //driver->setTransform( video::ETS_PROJECTION, core::IdentityMatrix );
    //driver->beginScene(true,true,SC_BLACK);
//    driver->draw2DLine( core::position2di(x,y), core::position2di(x+w-1,y+h-1), SC_WHITE );
//    driver->draw2DLine( core::position2di(x+w-1,y), core::position2di(x,y+h-1), SC_WHITE );
//
//
//    driver->draw2DRectangle( SC_WHITE, r_image );

    u32 bufferCount = MeshBuffer.size();
    for (u32 i=0; i<bufferCount; i++)
    {
        scene::IMeshBuffer* p = MeshBuffer[i];
        if (p)
        {
            driver->setMaterial( p->getMaterial() );
            video::drawMeshBufferEx( driver, p, PrimTypes[i] );
        }
    }


    driver->setViewPort( viewport_old );

//    driver->draw2DRectangle( SC_BLUE, viewport );

    core::stringw txt;
    txt = L""; txt += Data->getLocation();
    txt += L" "; txt += Data->getYear();
    txt += L" "; txt += Data->getLongitude();
    txt += L" "; txt += Data->getLatitude();

    // core::DateTime dt( Data->getYear(), 1, 1, 0,0,0);

    txt += L"\nCurveCount = "; txt += Data->getCurveCount();
    txt += L"\nBufferCount = "; txt += MeshBuffer.size();
    txt += L"\nPrimTypeCount = "; txt += PrimTypes.size();

    core::dimension2du txt_size = font->getDimension( txt.c_str() );

    core::recti r_txt( core::position2di(x+5,y+5), txt_size);

    font->draw( txt, r_txt, SC_BLACK, false, false);


    // IGUIElement::draw();
}

//! called if an event happened.
bool CGUISunPlot::OnEvent(const SEvent& event)
{
	return IGUIElement::OnEvent(event);
}

//! Clear all
void CGUISunPlot::clear( )
{
    BoundingBox.reset(0,0,0);

    u32 bufferCount = MeshBuffer.size();
    for (u32 i=0; i<bufferCount; i++)
    {
        scene::IMeshBuffer* p = MeshBuffer[i];
        if (p)
        {
            p->drop();
        }
        MeshBuffer[i]=0;
    }

    MeshBuffer.clear();
    PrimTypes.clear();
    IsDirty = false;
}


//! Writes attributes of the element.
void CGUISunPlot::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const
{

}

//! Reads attributes of the element
void CGUISunPlot::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options)
{

}

} // END NAMESPACE GUI
} // END NAMESPACE IRR


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
