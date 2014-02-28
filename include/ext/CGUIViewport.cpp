// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CGUIViewport.h"
#include "CMath.h"
#include <GL/gl.h>
#include <GL/glu.h>

#include "CAutoMeshSceneNode.h"
#include "geometry.h"

namespace irr
{
namespace gui
{


//! constructor
CGUIViewport::CGUIViewport(	scene::ISceneManager* smgr,	IGUIEnvironment* env,
	IGUIElement* parent, s32 id, const core::rect<s32>& rectangle)
: IGUIElement( EGUIET_ELEMENT, env, parent, id, rectangle)
, SceneManager(smgr), Root(0), Camera(0)
, ZoomRect(-1,-3,10,3), ZoomSpeed(1), ViewDir(0,0,1)
, ClearColor(video::SColor(255,0,0,0))
, IsMouseOver(false)
{
	#ifdef _DEBUG
	setDebugName("CGUIViewport");
	#endif

	setTabStop(false);
	setTabOrder(-1);

	s32 w = AbsoluteRect.getWidth(); // in pixels
	s32 h = AbsoluteRect.getHeight(); // in pixels

	_IRR_DEBUG_BREAK_IF( !SceneManager )

	Root = SceneManager->addEmptySceneNode( SceneManager->getRootSceneNode(), -1);

	_IRR_DEBUG_BREAK_IF( !Root )

	Camera = SceneManager->addCameraSceneNode( Root, core::vector3df(0,100,-100), core::vector3df(0,0,100), -1, false);

	_IRR_DEBUG_BREAK_IF( !Camera )

	Root->setVisible( false );

	/// Prepare some SceneNodes for x,y Axis and Grid

//	gui::IGUIFont* font = Environment->getBuiltInFont();

//	scene::ITextSceneNode* textNode00 = SceneManager->addTextSceneNode(
//		font, L"(0,0)", TextColor, SceneManager->getRootSceneNode(), core::vector3df(0,0,0) );
//
//

	scene::IMesh* mesh = scene::createHexagonMesh();

	scene::IMeshSceneNode* node = SceneManager->addMeshSceneNode(
		mesh, Root, -1, core::vector3df(0,0,0), core::vector3df(0,0,0), core::vector3df(1,1,1) );

	if (mesh) mesh->drop();

	if (node)
	{
		node->setMaterialTexture( 0, Environment->getVideoDriver()->getTexture("../../media/tex/pioneers/gras.jpg"));
		node->setDebugDataVisible( scene::EDS_BBOX );
	}



	Environment->setFocus(this);
}



//! destructor
CGUIViewport::~CGUIViewport()
{
	if (Root)
	{
		Root->setVisible( false );
		Root->drop();
	}

}

//! draws the element and its children
void CGUIViewport::draw()
{
	if (!IsVisible)
		return;

	if (!SceneManager)
	{
		printf("CGUIViewport::Has no SceneManager\n");
		return;
	}

	video::IVideoDriver* driver = Environment->getVideoDriver();
	if (!driver)
		return;

	/// deactivate all other SceneNodes than my own Root

	_IRR_DEBUG_BREAK_IF( !SceneManager )
	_IRR_DEBUG_BREAK_IF( !Root )

	scene::hideAll( SceneManager );

	if (Root)
		Root->setVisible( true );

	/// store Viewport
	const core::recti old_Viewport = driver->getViewPort();

	/// set Viewport
	driver->setViewPort( AbsoluteRect );

	/// store Camera
	scene::ICameraSceneNode* old_Camera = SceneManager->getActiveCamera();

	/// set Camera
	if (Camera)
	{
		/// create ProjectionMatrix ( Ortho2D )
//		core::matrix4 ortho = buildProjectionMatrixOrthoLH( ZoomRect.UpperLeftCorner.X, ZoomRect.LowerRightCorner.X,
//			ZoomRect.UpperLeftCorner.Y, ZoomRect.LowerRightCorner.Y, .1f, 1000.0f );

//		core::matrix4 ortho;
//		ortho.buildProjectionMatrixOrthoLH( ZoomRect.getWidth(), ZoomRect.getHeight(), 1.0f, 1000.0f );

		/// set ProjectionMatrix ( Ortho2D )
//		Camera->setProjectionMatrix( ortho );
//		Camera->setPosition( core::vector3df(0,0,0) );
//		Camera->setTarget( core::vector3df(0,0,100) );

		SceneManager->setActiveCamera( Camera );
	}

	SceneManager->drawAll();

	/// restore viewport
	driver->setViewPort( old_Viewport );

//	driver->endScene();

	/// restore scene
	scene::showAll( SceneManager );

	if (Root)
		Root->setVisible( false );

	if (old_Camera)
		SceneManager->setActiveCamera( old_Camera );


	/// set Text of ParentWindow
//
//	if (Parent && ((Parent->getType())==EGUIET_WINDOW))
//	{
//		core::stringc txt = "AbsoluteRect = { ";
//		txt += AbsoluteRect.UpperLeftCorner.X; txt += ", ";
//		txt += AbsoluteRect.UpperLeftCorner.Y; txt += ", ";
//		txt += AbsoluteRect.LowerRightCorner.X; txt += ", ";
//		txt += AbsoluteRect.LowerRightCorner.Y; txt += "}";
//		txt += ", AbsoluteClippingRect = { ";
//		txt += AbsoluteClippingRect.UpperLeftCorner.X; txt += ", ";
//		txt += AbsoluteClippingRect.UpperLeftCorner.Y; txt += ", ";
//		txt += AbsoluteClippingRect.LowerRightCorner.X; txt += ", ";
//		txt += AbsoluteClippingRect.LowerRightCorner.Y; txt += "}";
//		core::setText( Parent, txt );
//	}

	if (IsMouseOver)
	{
		driver->draw2DRectangleOutline( AbsoluteRect, video::SColor(255,255,128,0) );
	}
	// draw children
	IGUIElement::draw();
//
////	const bool focus = Environment->hasFocus(this);
//
////	IGUISkin* skin = Environment->getSkin();
////	if (!skin)
////		return;
//
//	/// create caption text
//	core::stringw t = L"CGUIViewport | Shapes = "; t += Shapes.size();
//	t += L" | Texts = "; t += Texts.size();
//	t += L" | ZoomRect = { ";
//	t += ZoomRect.UpperLeftCorner.X; t += L", ";
//	t += ZoomRect.UpperLeftCorner.Y; t += L", ";
//	t += ZoomRect.LowerRightCorner.X; t += L", ";
//	t += ZoomRect.LowerRightCorner.Y; t += L" }";
//	t += L" | AbsoluteRect = { x="; t += AbsoluteRect.UpperLeftCorner.X;
//	t += L", y="; t += AbsoluteRect.UpperLeftCorner.Y;
//	t += L", w="; t += AbsoluteRect.getWidth();
//	t += L", h="; t += AbsoluteRect.getHeight();
//	t += L"}";


}

//! called if an event happened.
bool CGUIViewport::OnEvent(const SEvent& event)
{
	if (IsEnabled)
	{
		// OnMouse(event);

		switch(event.EventType)
		{
			case EET_MOUSE_INPUT_EVENT:
			{
				//	if (event.EventType != EET_MOUSE_INPUT_EVENT)
				//		return false;

				const SEvent::SMouseInput& e = event.MouseInput;

				const core::position2di mouse_pos(e.X,e.Y);

				switch(e.Event)
				{
					/// MouseMove
					case EMIE_MOUSE_MOVED:
					{
						IsMouseOver = isMouseOver( mouse_pos, AbsoluteRect );
					}
					break;

					/// MouseWheel
					case EMIE_MOUSE_WHEEL:
					{
						// const core::position2di mouse_pos(e.X, e.Y);

						if (e.Wheel > 0.0f )
						{
							ZoomRect.UpperLeftCorner.X *= 0.9f;
							ZoomRect.UpperLeftCorner.Y *= 0.9f;
							ZoomRect.LowerRightCorner.X *= 0.9f;
							ZoomRect.LowerRightCorner.Y *= 0.9f;
						}
						else
						{
							ZoomRect.UpperLeftCorner.X *= 1.1f;
							ZoomRect.UpperLeftCorner.Y *= 1.1f;
							ZoomRect.LowerRightCorner.X *= 1.1f;
							ZoomRect.LowerRightCorner.Y *= 1.1f;
						}
						return true;
					}
					break;

					//	case EMIE_LMOUSE_LEFT_UP:
					//		if (Environment->hasFocus(this))
					//		{
					//			if (!InMenu) {
					//				if (!DoubleClicked) {
					//					CursorPos = getCursorPos(event.MouseInput.X, event.MouseInput.Y);
					//					if (MouseMarking)
					//					{
					//						setTextMarkers( MarkBegin, CursorPos );
					//					}
					//
					//					//Scrollbar->setPos(getLineFromPos(CursorPos));
					//					calculateScrollPos();
					//
					//				}
					//				MouseMarking = false;
					//				DoubleClicked = false;
					//			}
					//			return true;
					//		}
					//		break;


					//	case EMIE_RMOUSE_LEFT_UP:
					//		{
					//			if (Environment->hasFocus(this))
					//			{
					//			}
					//			return true;
					//			break;
					//		}
					//	case EMIE_LMOUSE_DOUBLE_CLICK:
					//		{
					//			return true;
					//			break;
					//		}
					//	case EMIE_LMOUSE_TRIPLE_CLICK:
					//		{
					//			break;
					//		}
					//	case EMIE_LMOUSE_PRESSED_DOWN:
					//		{
					//			if (!Environment->hasFocus(this))
					//			{
					//				return true;
					//			}
					//		}
					//		return true;
					//	case EMIE_RMOUSE_PRESSED_DOWN:
					//		{
					//			if (!Environment->hasFocus(this))
					//			{
					//			}
					//		}
					//		return true;
					default:
						break;
				}
			}
			break;
			//
			//		case EET_KEY_INPUT_EVENT:
			//			if (processKey(event))
			//				return true;
			//			break;
			//

			default:
				break;
		}
	}

	return IGUIElement::OnEvent(event);
}

//! Writes attributes of the element.
void CGUIViewport::serializeAttributes(io::IAttributes* out, io::SAttributeReadWriteOptions* options=0) const
{
	// IGUIEditBox::serializeAttributes(out,options);
//	out->addBool  ("OverrideColorEnabled",OverrideColorEnabled );
//	out->addColor ("OverrideColor",       OverrideColor);
//	// out->addFont("OverrideFont",OverrideFont);
//	out->addInt   ("MaxChars",            Max);
//	out->addBool  ("WordWrap",            WordWrap);
//	out->addBool  ("MultiLine",           MultiLine);
//	out->addBool  ("AutoScroll",          AutoScroll);
//	out->addBool  ("PasswordBox",         PasswordBox);
//	core::stringw ch = L" ";
//	ch[0] = PasswordChar;
//	out->addString("PasswordChar",        ch.c_str());
//	out->addEnum  ("HTextAlign",          HAlign, GUIAlignmentNames);
//	out->addEnum  ("VTextAlign",          VAlign, GUIAlignmentNames);
//
	IGUIElement::serializeAttributes(out,options);
}


//! Reads attributes of the element
void CGUIViewport::deserializeAttributes(io::IAttributes* in, io::SAttributeReadWriteOptions* options=0)
{
	IGUIElement::deserializeAttributes(in,options);

//	setOverrideColor(in->getAttributeAsColor("OverrideColor"));
//	enableOverrideColor(in->getAttributeAsBool("OverrideColorEnabled"));
//	setMax(in->getAttributeAsInt("MaxChars"));
//	setWordWrap(in->getAttributeAsBool("WordWrap"));
//	setMultiLine(in->getAttributeAsBool("MultiLine"));
//	setAutoScroll(in->getAttributeAsBool("AutoScroll"));
//	core::stringw ch = in->getAttributeAsStringW("PasswordChar");
//
//	if (!ch.size())
//		setPasswordBox(in->getAttributeAsBool("PasswordBox"));
//	else
//		setPasswordBox(in->getAttributeAsBool("PasswordBox"), ch[0]);
//
//	setTextAlignment( (EGUI_ALIGNMENT) in->getAttributeAsEnumeration("HTextAlign", GUIAlignmentNames),
//		(EGUI_ALIGNMENT) in->getAttributeAsEnumeration("VTextAlign", GUIAlignmentNames));

	// setOverrideFont(in->getAttributeAsFont("OverrideFont"));
}

//
//bool CGUIViewport::isMouseOver( const core::position2di& pos, const core::recti& target_rect )
//{
//	bool result(false);
//	if (pos.X >= target_rect.UpperLeftCorner.X)
//		if (pos.X <= target_rect.LowerRightCorner.X)
//			if (pos.Y >= target_rect.UpperLeftCorner.Y)
//				if (pos.Y <= target_rect.LowerRightCorner.Y)
//					result = true;
//	return result;
//}
//
////! set Parent Element Text ( i.e. the caption of a parent's window title )
//bool CGUIViewport::setText( gui::IGUIElement* element, const core::stringw& text )
//{
//	if (!element)
//		return false;
//
//	element->setText( text.c_str() );
//
//	return true;
//}
//
///// setVisible(false) to all SceneNodes
//bool CGUIViewport::hideAll( scene::ISceneManager* smgr )
//{
//	_IRR_DEBUG_BREAK_IF( !smgr )
////	if (!smgr)
////	{
////		printf("CGUIViewport::hideAll()::Invalid pointer to ISceneManager\n");
////		return false;
////	}
//
//	scene::ISceneNode* root = smgr->getRootSceneNode();
//
//	_IRR_DEBUG_BREAK_IF( !root )
////	if (!root)
////	{
////		printf("CGUIViewport::hideAll()::Invalid pointer to root ISceneNode\n");
////		return false;
////	}
//
//	const core::list<scene::ISceneNode*>& Nodes = root->getChildren();
//
//	core::list<scene::ISceneNode*>::ConstIterator it = Nodes.begin();
//
//	while( it != Nodes.end() )
//	{
//		if ((*it))
//		{
//			(*it)->setVisible( false );
//		}
//
//		it++;
//	}
//
//	return true;
//}
//
///// setVisible(true) to all SceneNodes
//bool CGUIViewport::showAll( scene::ISceneManager* smgr )
//{
//	_IRR_DEBUG_BREAK_IF( !smgr )
//
//	if (!smgr)
//		return false;
//
//	scene::ISceneNode* root = smgr->getRootSceneNode();
//
//	_IRR_DEBUG_BREAK_IF( !root )
//
//	if (!root)
//		return false;
//
//	const core::list<scene::ISceneNode*>& Nodes = root->getChildren();
//
//	core::list<scene::ISceneNode*>::ConstIterator it = Nodes.begin();
//
//	while( it != Nodes.end() )
//	{
//		if (*it)
//		{
//			(*it)->setVisible( true );
//		}
//
//		it++;
//	}
//
//	return true;
//}
//
//core::matrix4 CGUIViewport::buildProjectionMatrixOrthoLH( f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar )
//{
//	core::matrix4 M;
//	_IRR_DEBUG_BREAK_IF( core::equals(left,right) ); //divide by zero
//	_IRR_DEBUG_BREAK_IF( core::equals(top,bottom) ); //divide by zero
//	_IRR_DEBUG_BREAK_IF( core::equals(zNear,zFar) ); //divide by zero
//
//	//	2/(r-l)      0            0           0
//	//	0            2/(t-b)      0           0
//	//	0            0            1/(zf-zn)   0
//	//	(l+r)/(l-r)  (t+b)/(b-t)  zn/(zn-zf)  1
//
//	M[0] = 2.f/(right-left);
//	M[1] = 0.f;
//	M[2] = 0.f;
//	M[3] = 0.f;
//
//	M[4] = 0.f;
//	M[5] = 2.f/(top-bottom);
//	M[6] = 0.f;
//	M[7] = 0.f;
//
//	M[8] = 0.f;
//	M[9] = 0.f;
//	M[10] = 1.f/(zFar-zNear);
//	M[11] = 0.f;
//
//	M[12] = (left+right)/(left-right);
//	M[13] = (top+bottom)/(bottom-top);
//	M[14] = zNear/(zNear-zFar);
//	M[15] = 1.f;
//
//	return M;
//}


} // end namespace gui
} // end namespace irr
