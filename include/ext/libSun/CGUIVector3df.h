#ifndef __IRR_C_GUI_VECTOR3DF_H__
#define __IRR_C_GUI_VECTOR3DF_H__

#include <irrlicht.h>
#include <IGUIElement.h>

namespace irr
{

class CGUIVector3df : public gui::IGUIElement
{
public:
    CGUIVector3df( const core::stringw& name, gui::IGUIEnvironment* env, gui::IGUIElement* parent, s32 id, const core::recti& rectangle );

    virtual ~CGUIVector3df();

    //! called if an event happened.
    virtual bool OnEvent(const SEvent& event);

    //! draws the element and its children
    virtual void draw();

    virtual void setDecimalPlaces( s32 iDecimals );

    virtual s32 getDecimalPlaces( ) const ;

    virtual void setRange( f32 fMin, f32 fMax );

    virtual void setStepValue( f32 fStep );

    virtual void setValue( f32 fValue );

    virtual void setValue( const core::vector3df& value );

    virtual core::vector3df getValue() const;

    virtual f32 getRangeMin() const;

    virtual f32 getRangeMax() const;

    virtual f32 getStepValue() const;

private:
    f32 RangeMin;
    f32 RangeMax;
    f32 StepSize;
    s32 Decimals;
    bool UseCheckBoxes;
    bool UseEditBoxes;
    gui::IGUIStaticText* lbl_name;

    gui::IGUIStaticText* lbl_x;
    gui::IGUICheckBox* chk_x;
    gui::IGUISpinBox* edt_x;

    gui::IGUIStaticText* lbl_y;
    gui::IGUICheckBox* chk_y;
    gui::IGUISpinBox* edt_y;

    gui::IGUIStaticText* lbl_z;
    gui::IGUICheckBox* chk_z;
    gui::IGUISpinBox* edt_z;

    gui::IGUIButton* btn_set;
    gui::IGUIButton* btn_reset;
};

} // end namespace irr

#endif // __IRR_C_GUI_VECTOR3DF_H__
