/***************************************************************
 * Name:      CGUISunPlot.h
 * Author:    Benjamin Hampe (BenjaminHampe@gmx.de)
 * License:	  LGPL
 **************************************************************/

#ifndef __IRR_C_GUI_COLOR_PICKER_H__
#define __IRR_C_GUI_COLOR_PICKER_H__

#include <irrlicht.h>

#include "CSunData.h"

namespace irr
{
namespace gui
{
	class CGUISunPlot : public IGUIElement
	{
	public:

		//! constructor
		CGUISunPlot( IGUIEnvironment* env, IGUIElement* parent, s32 id, const core::recti& rectangle);

		//! destructor
		virtual ~CGUISunPlot();

		//! called if an event happened.
		virtual bool OnEvent(const SEvent& event);

		//! draws the element and its children
		virtual void draw();

		//! Writes attributes of the element.
		virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const;

		//! Reads attributes of the element
		virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options);

        //! get plot-dimension
        virtual s32 getWidth( ) const;

        //! get plot-dimension
        virtual s32 getHeight( ) const;

        //! clear all
        void clear( );

        //! create shapes from stored data-pointer
        void create( );

        //! Set new data-pointer, create or clear internal render-infos if nessecary
		void setData( CSunData* data = 0 );

        core::matrix4 LookAt( const core::vector3df& eye, const core::vector3df& target, const core::vector3df& up );
	protected:
	private:
        core::matrix4 ProjectionMatrix;

        bool IsDirty;
        CSunData* Data;

        core::aabbox3df BoundingBox;
        core::array<scene::IMeshBuffer*> MeshBuffer;
        core::array<scene::E_PRIMITIVE_TYPE> PrimTypes;

	}; // END CLASS

} // END NAMESPACE GUI
} // END NAMESPACE IRR

#endif // __IRR_C_GUI_COLOR_PICKER_H__

