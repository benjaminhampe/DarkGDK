#include "CGUIVector3df.h"


#include <irrlicht.h>
#include <IGUIElement.h>

namespace irr{

CGUIVector3df::CGUIVector3df( const core::stringw& name, gui::IGUIEnvironment* env, gui::IGUIElement* parent, s32 id, const core::recti& rectangle )
: gui::IGUIElement( gui::EGUIET_ELEMENT, env, parent, id, rectangle)
, RangeMin(0), RangeMax(100), StepSize(1), Decimals(0), UseCheckBoxes(false), UseEditBoxes(false)
, lbl_name(0), lbl_x(0), chk_x(0), edt_x(0), lbl_y(0), chk_y(0), edt_y(0), lbl_z(0), chk_z(0), edt_z(0), btn_set(0), btn_reset(0)
{
    /// position
    const s32 w = rectangle.getWidth();
    const s32 h = rectangle.getHeight();

    s32 px = rectangle.UpperLeftCorner.X;
    s32 py = rectangle.UpperLeftCorner.Y;

    s32 c = 1+16+2;
    if (UseCheckBoxes)
    {
        c += 6;
    }

    s32 t = core::floor32( (f32)w / (f32)c );

    gui::IGUIFont* font = env->getSkin()->getFont( gui::EGDF_DEFAULT );

    core::dimension2du s_name(0,0);
    core::dimension2du s_x(0,0);
    core::dimension2du s_y(0,0);
    core::dimension2du s_z(0,0);
    if (font)
    {
        s_name = font->getDimension( name.c_str() );
        s_x = font->getDimension( L"X" );
        s_y = font->getDimension( L"Y" );
        s_z = font->getDimension( L"Z" );
    }

    s32 dy = h;

    s32 dx = t;
    btn_reset = env->addButton( core::recti(px,py,px+dx-1,py+dy-1), parent, -1, L"x"); px += dx;

    dx = 4*t;
    lbl_name = env->addStaticText( name.c_str(), core::recti(px,py,px+dx-1,py+dy-1), true, false, parent, -1, true); px += dx;

    dx = t;
    lbl_x = env->addStaticText( L"X", core::recti(px,py,px+dx-1,py+dy-1), true, false, parent, -1, true); px += dx;
if (UseCheckBoxes)
{
    dx = 2*t;
    chk_x = env->addCheckBox( true, core::recti(px,py,px+dx-1,py+dy-1), parent, -1, L""); px += dx;
}
    dx = 3*t;
    edt_x = env->addSpinBox( L"0", core::recti(px,py,px+dx-1,py+dy-1), true, parent, -1); px += dx;
    dx = t;
    lbl_y = env->addStaticText( L"Y", core::recti(px,py,px+dx-1,py+dy-1), true, false, parent, -1, true); px += dx;
if (UseCheckBoxes)
{
    dx = 2*t;
    chk_y = env->addCheckBox( true, core::recti(px,py,px+dx-1,py+dy-1), parent, -1, L""); px += dx;
}
    dx = 3*t;
    edt_y = env->addSpinBox( L"0", core::recti(px,py,px+dx-1,py+dy-1), true, parent, -1); px += dx;

    dx = t;
    lbl_z = env->addStaticText( L"Z", core::recti(px,py,px+dx-1,py+dy-1), true, false, parent, -1, true); px += dx;
if (UseCheckBoxes)
{
    dx = 2*t;
    chk_z = env->addCheckBox( true, core::recti(px,py,px+dx-1,py+dy-1), parent, -1, L""); px += dx;
}
    dx = 3*t;
    edt_z = env->addSpinBox( L"0", core::recti(px,py,px+dx-1,py+dy-1), true, parent, -1); px += dx;

    dx = 1*t;
    btn_set = env->addButton( core::recti(px,py,px+w-3,py+dy-1), parent, -1, L"[]"); px += dx;

if (edt_x)
{
    edt_x->setRange( RangeMin, RangeMax );
    edt_x->setStepSize( StepSize );
    edt_x->setDecimalPlaces( Decimals );
    edt_x->setValue( 0.0f );
}
if (edt_y)
{
    edt_y->setRange( RangeMin, RangeMax );
    edt_y->setStepSize( StepSize );
    edt_y->setDecimalPlaces( Decimals );
    edt_y->setValue( 0.0f );
}
if (edt_z)
{
    edt_z->setRange( RangeMin, RangeMax );
    edt_z->setStepSize( StepSize );
    edt_z->setDecimalPlaces( Decimals );
    edt_z->setValue( 0.0f );
}
if (btn_set)
{
    btn_set->setText(L"=");
}
}

CGUIVector3df::~CGUIVector3df()
{

}

//! called if an event happened.
bool CGUIVector3df::OnEvent(const SEvent& event)
{
	return IGUIElement::OnEvent(event);
}
//! draws the element and its children
void CGUIVector3df::draw()
{
	IGUIElement::draw();
}

void CGUIVector3df::setDecimalPlaces( s32 iDecimals )
{
    Decimals = iDecimals;
}

s32 CGUIVector3df::getDecimalPlaces( ) const
{
    return Decimals;
}

void CGUIVector3df::setRange( f32 fMin, f32 fMax )
{
    RangeMin = fMin;
    RangeMax = fMax;
}

void CGUIVector3df::setStepValue( f32 fStep )
{
    StepSize = fStep;
}

void CGUIVector3df::setValue( f32 fValue )
{
    edt_x->setValue( fValue );
    edt_y->setValue( fValue );
    edt_z->setValue( fValue );
}

void CGUIVector3df::setValue( const core::vector3df& value )
{
    edt_x->setValue( value.X );
    edt_y->setValue( value.Y );
    edt_z->setValue( value.Z );
}

core::vector3df CGUIVector3df::getValue() const
{
    core::vector3df v(0,0,0);
    if (edt_x) { v.X = edt_x->getValue(); }
    if (edt_y) { v.Y = edt_y->getValue(); }
    if (edt_z) { v.Z = edt_z->getValue(); }
    return v;
}

f32 CGUIVector3df::getRangeMin() const
{
    return RangeMin;
}

f32 CGUIVector3df::getRangeMax() const
{
    return RangeMax;
}

f32 CGUIVector3df::getStepValue() const
{
    return StepSize;
}

}
