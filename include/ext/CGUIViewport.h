// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_C_GUI_VIEWPORT_2D_3D_H__
#define __IRR_EXT_C_GUI_VIEWPORT_2D_3D_H__

#include <irrlicht.h>

namespace irr
{
namespace gui
{

	///@brief class CGUIViewport
	class CGUIViewport : public IGUIElement
	{
	public:

		///@brief class constructor
		///@param smgr ISceneManager
		///@param env IGUIEnvironment
		///@param parent Parent element of this element
		///@param id Id of this element
		///@param rectangle Size of this element
		CGUIViewport(
			scene::ISceneManager* smgr,
			IGUIEnvironment* env,
			IGUIElement* parent,
			s32 id,
			const core::rect<s32>& rectangle );

		///@brief class destructor
		virtual ~CGUIViewport();

		///@brief called if an event happened.
		virtual bool OnEvent(const SEvent& event);

		///@brief draws the element and its children
		virtual void draw();

		///@brief add SceneNode to plot by adding to rootSceneNode
		virtual scene::ISceneNode* getRootSceneNode( ) { return Root; }

		///@brief get used SceneManager
		virtual scene::ISceneManager* getSceneManager( ) { return SceneManager; }

		///@brief get used Camera
		virtual scene::ICameraSceneNode* getCameraSceneNode( ) { return Camera; }

		///@brief get used GUIEnvironment
		virtual gui::IGUIEnvironment* getGUIEnvironment( ) { return Environment; }

		///@brief get ZoomRect
		virtual core::rectf getZoomRect( ) const { return ZoomRect;	}

		///@brief set ZoomRect
		virtual void setZoomRect( const core::rectf& zoomRect ) { ZoomRect = zoomRect; }

		///@brief get ZoomRect
		virtual f32 getZoomSpeed( ) const { return ZoomSpeed; }

		///@brief set ZoomRect
		virtual void setZoomSpeed( const f32& zoomSpeed ) { ZoomSpeed = zoomSpeed; }

		///@brief set ClearColor
		virtual void setClearColor( const video::SColor& color ) {	ClearColor = color; }

		///@brief get ClearColor
		virtual video::SColor getClearColor() const { return ClearColor; }

		// ///@brief Updates the absolute position, splits text if required
		// virtual void updateAbsolutePosition();

		///@brief Writes attributes of the element.
		virtual void serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options) const;

		///@brief Reads attributes of the element
		virtual void deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options);

	protected:
	private:

		scene::ISceneManager* SceneManager;
		scene::ISceneNode* Root;
		scene::ICameraSceneNode* Camera;

		core::rectf ZoomRect;
		f32 ZoomSpeed;
		core::vector3df ViewDir;

		video::SColor ClearColor;

		bool IsMouseOver;


	};

} // end namespace gui
} // end namespace irr

#endif // __IRR_EXT_C_GUI_VIEWPORT_2D_3D_H_
