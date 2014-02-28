#include "DarkGDK_string.h"

#include <irrlicht.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

namespace irr
{
	core::stringc dbStr(const char* value)
	{
		return core::stringc(value);
	}

	core::stringw dbStr(const wchar_t* value)
	{
		return core::stringw(value);
	}

	core::stringc dbStr(u8 value)
	{
		return core::stringc(value);
	}
	core::stringc dbStr(s8 value) { return core::stringc(value);}
	core::stringc dbStr(u16 value) { return core::stringc(value);}
	core::stringc dbStr(s16 value) { return core::stringc(value);}
	core::stringc dbStr(u32 value) { return core::stringc(value);}
	core::stringc dbStr(s32 value) { return core::stringc(value);}
	core::stringc dbStr(f32 value) { return core::stringc(value);}
	core::stringc dbStr(f64 value) { return core::stringc(value);}

	core::stringc dbStr( const core::stringc& key, const core::stringc& value)
	{
		core::stringc s(key);
		s+=": "; s+=value;	s+=";";
		return s;
	}

	// BOOL to STRING
	// Urheber dieser Funktion ist Benjamin Hampe, bitte beachten Sie bei Verwendung die Lizenzbedingungen.
	// Funktion zur Umwandlung eines Booleschen Wertes in einen String ("TRUE","FALSE" oder "true,false")
	core::stringc dbStr(bool value, bool capitals)
	{	core::stringc s;
		if (value)
			if (capitals)
				s="TRUE";
			else
				s="true";
		else
			if (capitals)
				s="FALSE";
			else
				s="false";
		return s;
	}

	// FLOAT to STRING
	// Urheber dieser Funktion ist Benjamin Hampe, bitte beachten Sie bei Verwendung die Lizenzbedingungen.
	// Umwandlung f32 in formattierten String beliebiger Präzision, mit Stringklasse der Irrlicht-Engine
	core::stringc dbStr(f32 value, s32 width, s32 frac)
	{
//		core::stringc s;
//		std::ostringstream ss;
//		ss<<std::setprecision(frac)<<std::showpoint<<std::setw(width)<<value;
//		s = ss.str().c_str();
//		s = s.trim();
//		return s;
		core::stringc formatString = "%";
		formatString += width;
		formatString += ".";
		formatString += frac;
		formatString += "f";
		c8 char_buffer[32];
		snprintf( char_buffer, 32, formatString.c_str(), value );
		return core::stringc( char_buffer );
	}

	// DOUBLE to STRING
	// Urheber dieser Funktion ist Benjamin Hampe, bitte beachten Sie bei Verwendung die Lizenzbedingungen.
	// Umwandlung f64 in formattierten String beliebiger Präzision, mit Stringklasse der Irrlicht-Engine
	core::stringc dbStr(f64 value, s32 width, s32 frac)
	{
//		std::ostringstream ss;
//		ss<<std::setprecision(frac)<<std::showpoint<<std::setw(width)<<value;
//		s = ss.str().c_str();
//		s = s.trim();
//		return s;
		core::stringc formatString = "%";
		formatString += width;
		formatString += ".";
		formatString += frac;
		formatString += "lf";
		c8 char_buffer[32];
		snprintf( char_buffer, 32, formatString.c_str(), value );
		return core::stringc( char_buffer );
	}

	// SGUIEvent
	core::stringc dbStr(const SEvent::SGUIEvent& e)
	{
		core::stringc s("GUIEvent");
		return s;
	}

	// SKeyInput
	core::stringc dbStr(const SEvent::SKeyInput& e)
	{
		core::stringc s("KeyEvent");
		return s;
	}


	// SJoystickEvent
	core::stringc dbStr(const SEvent::SJoystickEvent& e)
	{
		core::stringc s("JoystickEvent");
		return s;
	}

	// SLogEvent
	core::stringc dbStr(const SEvent::SLogEvent& e)
	{
		core::stringc s("LogEvent");
		s+=e.Text;
		return s;
	}

	// SMouseInput
	core::stringc dbStr(const SEvent::SMouseInput& e)
	{
		core::stringc s("MouseEvent");
		s+="("; s+=e.X;
		s+=","; s+=e.Y;
		s+=","; s+=e.Wheel;
		s+=","; s+=e.isLeftPressed();
		s+=","; s+=e.isMiddlePressed();
		s+=","; s+=e.isRightPressed();
		s+=")";
		return s;
	}

	// EMOUSE_INPUT_EVENT
	core::stringc dbStr(EMOUSE_INPUT_EVENT e)
	{
		core::stringc s;
		switch(e)
		{
			case EMIE_MOUSE_MOVED: s+="EMIE_MOUSE_MOVED"; break;
			case EMIE_MOUSE_WHEEL: s+="EMIE_MOUSE_WHEEL"; break;
			case EMIE_LMOUSE_PRESSED_DOWN: s+="EMIE_LMOUSE_PRESSED_DOWN"; break;
			case EMIE_RMOUSE_PRESSED_DOWN: s+="EMIE_RMOUSE_PRESSED_DOWN"; break;
			case EMIE_MMOUSE_PRESSED_DOWN: s+="EMIE_MMOUSE_PRESSED_DOWN"; break;
			case EMIE_LMOUSE_LEFT_UP: s+="EMIE_LMOUSE_LEFT_UP"; break;
			case EMIE_RMOUSE_LEFT_UP: s+="EMIE_RMOUSE_LEFT_UP"; break;
			case EMIE_MMOUSE_LEFT_UP: s+="EMIE_MMOUSE_LEFT_UP"; break;
			case EMIE_LMOUSE_DOUBLE_CLICK: s+="EMIE_LMOUSE_DOUBLE_CLICK"; break;
			case EMIE_RMOUSE_DOUBLE_CLICK: s+="EMIE_RMOUSE_DOUBLE_CLICK"; break;
			case EMIE_MMOUSE_DOUBLE_CLICK: s+="EMIE_MMOUSE_DOUBLE_CLICK"; break;
			case EMIE_LMOUSE_TRIPLE_CLICK: s+="EMIE_LMOUSE_TRIPLE_CLICK"; break;
			case EMIE_RMOUSE_TRIPLE_CLICK: s+="EMIE_RMOUSE_TRIPLE_CLICK"; break;
			case EMIE_MMOUSE_TRIPLE_CLICK: s+="EMIE_MMOUSE_TRIPLE_CLICK"; break;
			default: break;
		}
		return s;
	}

	// EGUI_EVENT_TYPE
	core::stringc dbStr(gui::EGUI_EVENT_TYPE e)
	{
		core::stringc s;
		switch(e)
		{
			case gui::EGET_ELEMENT_FOCUS_LOST: s+="EGET_ELEMENT_FOCUS_LOST"; break;
			case gui::EGET_ELEMENT_FOCUSED: s+="EGET_ELEMENT_FOCUSED"; break;
			case gui::EGET_ELEMENT_HOVERED: s+="EGET_ELEMENT_HOVERED"; break;
			case gui::EGET_ELEMENT_LEFT: s+="EGET_ELEMENT_LEFT"; break;
			case gui::EGET_ELEMENT_CLOSED: s+="EGET_ELEMENT_CLOSED"; break;
			case gui::EGET_BUTTON_CLICKED: s+="EGET_BUTTON_CLICKED"; break;
			case gui::EGET_SCROLL_BAR_CHANGED: s+="EGET_SCROLL_BAR_CHANGED"; break;
			case gui::EGET_CHECKBOX_CHANGED: s+="EGET_CHECKBOX_CHANGED"; break;
			case gui::EGET_LISTBOX_CHANGED: s+="EGET_LISTBOX_CHANGED"; break;
			case gui::EGET_LISTBOX_SELECTED_AGAIN: s+="EGET_LISTBOX_SELECTED_AGAIN"; break;
			case gui::EGET_FILE_SELECTED: s+="EGET_FILE_SELECTED"; break;
			case gui::EGET_DIRECTORY_SELECTED: s+="EGET_DIRECTORY_SELECTED"; break;
			case gui::EGET_FILE_CHOOSE_DIALOG_CANCELLED: s+="EGET_FILE_CHOOSE_DIALOG_CANCELLED"; break;
			case gui::EGET_MESSAGEBOX_YES: s+="EGET_MESSAGEBOX_YES"; break;
			case gui::EGET_MESSAGEBOX_NO: s+="EGET_MESSAGEBOX_NO"; break;
			case gui::EGET_MESSAGEBOX_OK: s+="EGET_MESSAGEBOX_OK"; break;
			case gui::EGET_MESSAGEBOX_CANCEL: s+="EGET_MESSAGEBOX_CANCEL"; break;
			case gui::EGET_EDITBOX_ENTER: s+="EGET_EDITBOX_ENTER"; break;
			case gui::EGET_EDITBOX_CHANGED: s+="EGET_EDITBOX_CHANGED"; break;
			case gui::EGET_EDITBOX_MARKING_CHANGED: s+="EGET_EDITBOX_MARKING_CHANGED"; break;
			case gui::EGET_TAB_CHANGED: s+="EGET_TAB_CHANGED"; break;
			case gui::EGET_MENU_ITEM_SELECTED: s+="EGET_MENU_ITEM_SELECTED"; break;
			case gui::EGET_COMBO_BOX_CHANGED: s+="EGET_COMBO_BOX_CHANGED"; break;
			case gui::EGET_SPINBOX_CHANGED: s+="EGET_SPINBOX_CHANGED"; break;
			case gui::EGET_TABLE_CHANGED: s+="EGET_TABLE_CHANGED"; break;
			case gui::EGET_TABLE_HEADER_CHANGED: s+="EGET_TABLE_HEADER_CHANGED"; break;
			case gui::EGET_TABLE_SELECTED_AGAIN: s+="EGET_TABLE_SELECTED_AGAIN"; break;
			case gui::EGET_TREEVIEW_NODE_DESELECT: s+="EGET_TREEVIEW_NODE_DESELECT"; break;
			case gui::EGET_TREEVIEW_NODE_SELECT: s+="EGET_TREEVIEW_NODE_SELECT"; break;
			case gui::EGET_TREEVIEW_NODE_EXPAND: s+="EGET_TREEVIEW_NODE_EXPAND"; break;
			case gui::EGET_TREEVIEW_NODE_COLLAPS: s+="EGET_TREEVIEW_NODE_COLLAPS"; break;
			default: break;
		}
		return s;
	}

	core::stringc dbStr(io::IFileSystem& fs)
	{
		core::stringc txt;
		txt+="IFileSystem\n";
		txt+="WorkingDirectory = ";
		txt+=(fs.getWorkingDirectory().c_str());
		txt+="\n";
		return txt;
	}

	core::stringc dbStr(const core::quaternion& v)
	{
		core::stringc txt("");
		txt+=v.X;	txt+=","; txt+=v.Y;	txt+=","; txt+=v.Z;	txt+=","; txt+=v.W;
		return txt;
	}

	core::stringc dbStr(E_DEVICE_TYPE e)
	{
		core::stringc s;
		switch (e)
		{
			case EIDT_WIN32:	    s+="Win32";	        break;
			case EIDT_WINCE:	    s+="WinCE";	        break;
			case EIDT_X11:		    s+="X11";	        break;
			case EIDT_OSX:		    s+="OSX";	        break;
			case EIDT_SDL:		    s+="SD";	        break;
			case EIDT_FRAMEBUFFER:	s+="FrameBuffer";	break;
			case EIDT_CONSOLE:		s+="Console";	    break;
			default :		        s+="Best";	        break;
		}
		return s;
	}

	core::stringc dbStr(video::ECOLOR_FORMAT e)
	{
		core::stringc s;
		switch (e)
		{
			case video::ECF_A1R5G5B5:		s+="A1R5G5B5"; break;
			case video::ECF_R5G6B5:		s+="R5G6B5"; break;
			case video::ECF_R8G8B8:		s+="R8G8B8"; break;
			case video::ECF_A8R8G8B8:		s+="A8R8G8B8"; break;
			case video::ECF_R16F:			s+="R16F"; break;
			case video::ECF_G16R16F:		s+="G16R16F"; break;
			case video::ECF_A16B16G16R16F:	s+="A16B16G16R16F";	break;
			case video::ECF_R32F:			s+="R32F";break;
			case video::ECF_G32R32F:		s+="G32R32F";	    break;
			case video::ECF_A32B32G32R32F:	s+="A32B32G32R32F";	break;
			default :				s+="UNKNOWN";	    break;
		}
		return s;
	}
	core::stringc dbStr(video::E_DRIVER_TYPE e)
	{
		core::stringc s;
		switch (e)
		{
			case video::EDT_NULL:			s+="Null";	        break;
			case video::EDT_SOFTWARE:		s+="Software";	    break;
			case video::EDT_OPENGL:		    s+="OpenGl";        break;
			case video::EDT_BURNINGSVIDEO:	s+="BurningVideo";	break;
			case video::EDT_DIRECT3D8:		s+="DirectX 8.1";	break;
			case video::EDT_DIRECT3D9:		s+="DirectX 9.0c";	break;
			default :		                s+="Unknown";	    break;
		}
		return s;
	}

	core::stringc dbStr(video::E_ANTI_ALIASING_MODE e)
	{
		core::stringc s;
		switch (e)
		{
			case video::EAAM_OFF:			s+="EAAM_OFF";	        break;
			case video::EAAM_SIMPLE:		s+="EAAM_SIMPLE";	    break;
			case video::EAAM_FULL_BASIC:	s+="EAAM_FULL_";	break;
			case video::EAAM_POINT_SMOOTH:	s+="EAAM_POINT_SMOOTH";	break;
			case video::EAAM_LINE_SMOOTH:	s+="EAAM_LINE_SMOOTH";	break;
			case video::EAAM_QUALITY:		s+="EAAM_QUALITY";	    break;
			case video::EAAM_ALPHA_TO_COVERAGE: s+="EAAM_ALPHA_TO_COVERAGE";	break;
					default :		        s+="Unknown";	        break;
		}
		return s;
	}

	core::stringc dbStr(const video::SColor& c)
	{
		core::stringc txt("");
		txt+=c.getAlpha();	txt+=","; txt+=c.getRed();	txt+=","; txt+=c.getGreen();	txt+=","; txt+=c.getBlue();
		return txt;
	}

	core::stringc dbStr(const video::SColorf& c)
	{
		core::stringc txt("");
		txt+=c.a;	txt+=","; txt+=c.r;	txt+=","; txt+=c.g;	txt+=","; txt+=c.b;
		return txt;
	}

	core::stringc dbStr(const video::S3DVertex& v)
	{
		core::stringc txt("");
		txt+=dbStr<f32>(v.Pos);	txt+=","; txt+=dbStr<f32>(v.Normal); txt+=","; txt+=dbStr(v.Color); txt+=","; txt+=dbStr<f32>(v.TCoords);
		return txt;
	}

	core::stringc dbStr(const video::SLight& light)
	{
		core::stringc txt("video::SLight\n");
		txt+="Type = "; txt+=light.Type; txt+="\n";
		txt+="Position = "; txt+=dbStr(light.Position); txt+="\n";
		txt+="Direction = "; txt+=dbStr(light.Direction); txt+="\n";
		txt+="Radius = "; txt+=light.Radius; txt+="\n";
		txt+="AmbientColor = "; txt+=dbStr(light.AmbientColor); txt+="\n";
		txt+="DiffuseColor = "; txt+=dbStr(light.DiffuseColor); txt+="\n";
		txt+="SpecularColor = "; txt+=dbStr(light.SpecularColor); txt+="\n";
		txt+="Attenuation = "; txt+=dbStr(light.Attenuation); txt+="\n";
		txt+="OuterCone = "; txt+=light.OuterCone; txt+="\n";
		txt+="InnerCone = "; txt+=light.InnerCone; txt+="\n";
		txt+="Falloff = "; txt+=light.Falloff; txt+="\n";
		txt+="CastShadows = "; txt+=light.CastShadows; txt+="\n";
		return txt;
	}

	core::stringc dbStr(const video::SMaterial& material)
	{
		core::stringc txt("video::SMaterial\n");
		txt+="AmbientColor = "; txt+=dbStr(material.AmbientColor); txt+="\n";
		txt+="MaterialType = "; txt+=material.MaterialType; txt+="\n";
		txt+="DiffuseColor = "; txt+=dbStr(material.DiffuseColor); txt+="\n";
		txt+="EmissiveColor = "; txt+=dbStr(material.EmissiveColor); txt+="\n";
		txt+="SpecularColor = "; txt+=dbStr(material.SpecularColor); txt+="\n";
		txt+="Shininess = "; txt+=material.Shininess; txt+="\n";
		txt+="MaterialTypeParam = "; txt+=material.MaterialTypeParam; txt+="\n";
		txt+="MaterialTypeParam2 = "; txt+=material.MaterialTypeParam2; txt+="\n";
		txt+="Thickness = "; txt+=material.Thickness; txt+="\n";
		txt+="ZBuffer = "; txt+=material.ZBuffer; txt+="\n";
		txt+="AntiAliasing = "; txt+=material.AntiAliasing; txt+="\n";
		txt+="ColorMask = "; txt+=material.ColorMask; txt+="\n";
		txt+="ColorMaterial = "; txt+=material.ColorMaterial; txt+="\n";
		txt+="Wireframe = "; txt+=material.Wireframe; txt+="\n";
		txt+="PointCloud = "; txt+=material.PointCloud; txt+="\n";
		txt+="GouraudShading = "; txt+=material.GouraudShading; txt+="\n";
		txt+="Lighting = "; txt+=material.Lighting; txt+="\n";
		txt+="ZWriteEnable = "; txt+=material.ZWriteEnable; txt+="\n";
		txt+="BackfaceCulling = "; txt+=material.BackfaceCulling; txt+="\n";
		txt+="FrontfaceCulling = "; txt+=material.FrontfaceCulling; txt+="\n";
		txt+="FogEnable = "; txt+=material.FogEnable; txt+="\n";
		txt+="NormalizeNormals = "; txt+=material.NormalizeNormals; txt+="\n";
		return txt;
	}

	core::stringc dbStr(const SIrrlichtCreationParameters& params)
	{
		core::stringc txt("SIrrlichtCreationParameters\n");
		txt+=dbStr("WindowId", core::stringc(long(params.WindowId)));
		txt+=dbStr("DeviceType", dbStr(params.DeviceType));
		txt+=dbStr("DriverType", dbStr(params.DriverType));
		txt+=dbStr("WindowSize", dbStr(params.WindowSize));
		txt+=dbStr("Bits", core::stringc(params.Bits));
		txt+=dbStr("LoggingLevel", dbStr(params.LoggingLevel));
		txt+=dbStr("ZBufferBits", dbStr(params.ZBufferBits));
		txt+=dbStr("Stencilbuffer", core::stringc(params.Stencilbuffer));
		txt+=dbStr("Fullscreen", core::stringc(params.Fullscreen));
		txt+=dbStr("Vsync", core::stringc(params.Vsync));
		txt+=dbStr("AntiAlias", dbStr(params.AntiAlias));
		txt+=dbStr("WithAlphaChannel", core::stringc(params.WithAlphaChannel));
		txt+=dbStr("Doublebuffer", core::stringc(params.Doublebuffer));
		txt+=dbStr("IgnoreInput", core::stringc(params.IgnoreInput));
		txt+=dbStr("Stereobuffer", core::stringc(params.Stencilbuffer));
		txt+=dbStr("HighPrecisionFPU", core::stringc(params.HighPrecisionFPU));
		return txt;
	}

	core::stringc dbStr(video::IVideoModeList* modes)
	{
		core::stringc txt("video::IVideoModeList\n");
		txt+="DesktopResolution = ";
		txt+=dbStr<u32>(modes->getDesktopResolution()); txt+=","; txt+=modes->getDesktopDepth(); txt+="\n";

		const s32 c = modes->getVideoModeCount();
		txt+="VideoModeCount = "; txt+=c; txt+="\n";
		if (c>0)
		{
			for (s32 i=0; i<c; ++i)
			{
				txt+=dbStr<u32>(modes->getVideoModeResolution(i));
				txt+=",";
				txt+=modes->getVideoModeDepth(i);
				txt+="\n";
			}
		}
		return txt;
	}



	core::stringc dbStr(const scene::SMeshBuffer& meshBuffer)
	{
		core::stringc txt;
		txt+="scene::SMeshBuffer\n";
		return txt;
	}
	core::stringc dbStr(const scene::SMesh& mesh)
	{
		core::stringc txt;
		txt+="scene::SMesh\n";
		return txt;
	}


	// ICameraSceneNode
	core::stringc dbStr(scene::ICameraSceneNode* cam)
	{
		if (!cam) return core::stringc("Error in dbStr(ICameraSceneNode*). No valid pointer.");
		core::stringc txt;
		txt+=cam->getAbsolutePosition().X; txt+=",";
		txt+=cam->getAbsolutePosition().Y; txt+=",";
		txt+=cam->getAbsolutePosition().Z;
		return txt;
	}

	core::stringc dbStr(IrrlichtDevice* device)
	{
		if (!device) return core::stringc("");

		core::stringc txt("IrrlichtDevice\n");
		txt+=dbStr(device->getType()); txt+=" ";
		txt+=dbStr(device->getVideoDriver()->getDriverType()); txt+="-Device\n";
		txt+="Version = "; txt+=device->getVersion(); txt+="\n";
		txt+="Plattform = "; txt+=device->getType(); txt+="\n";
		txt+="Betriebssystem = "; txt+=device->getOSOperator()->getOperatingSystemVersion(); txt+="\n";
		u32 MHz; device->getOSOperator()->getProcessorSpeedMHz(&MHz);
		txt+="Prozessor in MHz = "; txt+=MHz; txt+="\n";
		u32 RAM_Total, RAM_Avail; device->getOSOperator()->getSystemMemory(&RAM_Total, &RAM_Avail);
		txt+="Arbeitsspeicher Gesamt in MByte = "; txt+=RAM_Total; txt+="\n";
		txt+="Arbeitsspeicher Frei in MByte = "; txt+=RAM_Avail; txt+="\n";
		txt+="Supports Null VideoDriver ? = "; txt+=device->isDriverSupported(video::EDT_NULL); txt+="\n";
		txt+="Supports Software VideoDriver ? = "; txt+=device->isDriverSupported(video::EDT_SOFTWARE); txt+="\n";
		txt+="Supports Burning VideoDriver ? = "; txt+=device->isDriverSupported(video::EDT_BURNINGSVIDEO); txt+="\n";
		txt+="Supports OpenGL VideoDriver ? = "; txt+=device->isDriverSupported(video::EDT_OPENGL); txt+="\n";
		txt+="Supports DirectX 8.1 VideoDriver ? = "; txt+=device->isDriverSupported(video::EDT_DIRECT3D8); txt+="\n";
		txt+="Supports DirectX 9.0c VideoDriver ? = "; txt+=device->isDriverSupported(video::EDT_DIRECT3D9); txt+="\n";
		txt+="Is Window Fullscreen = "; txt+=device->isFullscreen(); txt+="\n";
		txt+="Is Window Active = "; txt+=device->isWindowActive(); txt+="\n";
		txt+="Is Window Focused = "; txt+=device->isWindowFocused(); txt+="\n";
		txt+="Is Window Minimized = "; txt+=device->isWindowMinimized(); txt+="\n";

		txt+="\nVideoModeList\n";
		txt+="DesktopResolution = ";
		txt+=device->getVideoModeList()->getDesktopResolution().Width;
		txt+=",";
		txt+=device->getVideoModeList()->getDesktopResolution().Height;
		txt+=",";
		txt+=device->getVideoModeList()->getDesktopDepth();
		txt+="\n";

		s32 s = device->getVideoModeList()->getVideoModeCount();
		txt+="VideoModeCount = ";
		txt+=s;
		txt+="\n";
		if (s>0)
		{
			for (s32 i=0; i<s; ++i)
			{
				txt+=device->getVideoModeList()->getVideoModeResolution(i).Width;
				txt+=",";
				txt+=device->getVideoModeList()->getVideoModeResolution(i).Height;
				txt+=",";
				txt+=device->getVideoModeList()->getVideoModeDepth(i);
				txt+="\n";
			}
		}

	// VideoDriver
		video::IVideoDriver* driver = device->getVideoDriver();

		txt+="\nVideoDriver\n";
		txt+="Renderer = "; txt+=driver->getName(); txt+="\n";
		txt+="GPU Name = "; txt+=driver->getVendorInfo(); txt+="\n";
		txt+="ColorFormat = ";	txt+=dbStr(driver->getColorFormat());
		txt+="CurrentRenderTargetSize = ";	txt+=dbStr(driver->getCurrentRenderTargetSize()); txt+="\n";
		txt+="DynamicLightCount = "; txt+=driver->getDynamicLightCount(); txt+="\n";
	//	if (c>0)
	//	{
	//		for (u32 i=0; i<c; ++i)
	//		{
	//			txt+=dbStr(driver->getDynamicLight(i));
	//		}
	//	}
		txt+="FPS = "; txt+=driver->getFPS(); txt+="\n";
		txt+="MaterialRendererCount = "; txt+=driver->getMaterialRendererCount(); txt+="\n";
		txt+="MaximalDynamicLightAmount = "; txt+=driver->getMaximalDynamicLightAmount(); txt+="\n";
		txt+="MaximalPrimitiveCount = "; txt+=driver->getMaximalPrimitiveCount(); txt+="\n";
		txt+="MaxTextureSize = "; txt+=dbStr(driver->getMaxTextureSize()); txt+="\n";
		txt+="PrimitiveCountDrawn = "; txt+=driver->getPrimitiveCountDrawn(); txt+="\n";
		txt+="ScreenSize = "; txt+=dbStr(driver->getScreenSize()); txt+="\n";
		txt+="TextureCreationFlag(ETCF_ALWAYS_32_BIT) = "; txt+=driver->getTextureCreationFlag(video::ETCF_ALWAYS_32_BIT); txt+="\n";
		txt+="TextureCount = "; txt+=driver->getTextureCount(); txt+="\n";
		txt+="Transform(video::ETS_WORLD) = "; txt+=dbStr(driver->getTransform(video::ETS_WORLD)); txt+="\n";
		txt+="Transform(video::ETS_VIEW) = "; txt+=dbStr(driver->getTransform(video::ETS_VIEW)); txt+="\n";
		txt+="Transform(video::ETS_PROJECTION) = "; txt+=dbStr(driver->getTransform(video::ETS_PROJECTION)); txt+="\n";
		txt+="Transform(video::ETS_TEXTURE_0) = "; txt+=dbStr(driver->getTransform(video::ETS_TEXTURE_0)); txt+="\n";
		txt+="Transform(video::ETS_TEXTURE_1) = "; txt+=dbStr(driver->getTransform(video::ETS_TEXTURE_1)); txt+="\n";
		txt+="Transform(video::ETS_TEXTURE_2) = "; txt+=dbStr(driver->getTransform(video::ETS_TEXTURE_2)); txt+="\n";
		txt+="Transform(video::ETS_TEXTURE_3) = "; txt+=dbStr(driver->getTransform(video::ETS_TEXTURE_3)); txt+="\n";
		txt+="ViewPort = "; txt+=dbStr(driver->getViewPort()); txt+="\n";
		txt+="queryFeature(video::EVDF_RENDERprintOprintARGET) = "; txt+=driver->queryFeature(video::EVDF_RENDER_TO_TARGET); txt+="\tIs driver able to render to a surface? "; txt+="\n";
		txt+="queryFeature(video::EVDFprintEXTURE_NSQUARE) = "; txt+=driver->queryFeature(video::EVDF_TEXTURE_NSQUARE); txt+="\tAre non-square textures supported? "; txt+="\n";
		txt+="queryFeature(video::EVDFprintEXTURE_NPOT) = "; txt+=driver->queryFeature(video::EVDF_TEXTURE_NPOT); txt+="\tAre non-power-of-two textures supported? "; txt+="\n";
		txt+="queryFeature(video::EVDF_HARDWAREprintL) = "; txt+=driver->queryFeature(video::EVDF_HARDWARE_TL); txt+="\tIs hardeware transform and lighting supported?"; txt+="\n";
		txt+="queryFeature(video::EVDF_MULTITEXTURE) = "; txt+=driver->queryFeature(video::EVDF_MULTITEXTURE); txt+="\tAre multiple textures per material possible?"; txt+="\n";
		txt+="queryFeature(video::EVDF_BILINEAR_FILTER) = "; txt+=driver->queryFeature(video::EVDF_BILINEAR_FILTER); txt+="\tIs driver able to render with a bilinear filter applied?"; txt+="\n";
		txt+="queryFeature(video::EVDF_MIP_MAP) = "; txt+=driver->queryFeature(video::EVDF_MIP_MAP); txt+="\tCan the driver handle mip maps?"; txt+="\n";
		txt+="queryFeature(video::EVDF_MIP_MAP_AUTO_UPDATE) = "; txt+=driver->queryFeature(video::EVDF_MIP_MAP_AUTO_UPDATE); txt+="\tCan the driver update mip maps automatically?"; txt+="\n";
		txt+="queryFeature(video::EVDF_STENCIL_BUFFER) = "; txt+=driver->queryFeature(video::EVDF_STENCIL_BUFFER); txt+="\tAre stencilbuffers switched on and does the device support stencil buffers?"; txt+="\n";
		txt+="queryFeature(video::EVDF_VERTEX_SHADER_1_1) = "; txt+=driver->queryFeature(video::EVDF_VERTEX_SHADER_1_1); txt+="\tIs Vertex Shader 1->1 supported?"; txt+="\n";
		txt+="queryFeature(video::EVDF_VERTEX_SHADER_2_0) = "; txt+=driver->queryFeature(video::EVDF_VERTEX_SHADER_2_0); txt+="\tIs Vertex Shader 2->0 supported?"; txt+="\n";
		txt+="queryFeature(video::EVDF_VERTEX_SHADER_3_0) = "; txt+=driver->queryFeature(video::EVDF_VERTEX_SHADER_3_0); txt+="\tIs Vertex Shader 3->0 supported?"; txt+="\n";
		txt+="queryFeature(video::EVDF_PIXEL_SHADER_1_1) = "; txt+=driver->queryFeature(video::EVDF_PIXEL_SHADER_1_1); txt+="\tIs Pixel Shader 1->1 supported?\n";
		txt+="queryFeature(video::EVDF_PIXEL_SHADER_1_2) = "; txt+=driver->queryFeature(video::EVDF_PIXEL_SHADER_1_2); txt+="\tIs Pixel Shader 1->2 supported?\n";
		txt+="queryFeature(video::EVDF_PIXEL_SHADER_1_3) = "; txt+=driver->queryFeature(video::EVDF_PIXEL_SHADER_1_3); txt+="\tIs Pixel Shader 1->3 supported?\n";
		txt+="queryFeature(video::EVDF_PIXEL_SHADER_1_4) = "; txt+=driver->queryFeature(video::EVDF_PIXEL_SHADER_1_4); txt+="\tIs Pixel Shader 1->4 supported?\n";
		txt+="queryFeature(video::EVDF_PIXEL_SHADER_2_0) = "; txt+=driver->queryFeature(video::EVDF_PIXEL_SHADER_2_0); txt+="\tIs Pixel Shader 2->0 supported?\n";
		txt+="queryFeature(video::EVDF_PIXEL_SHADER_3_0) = "; txt+=driver->queryFeature(video::EVDF_PIXEL_SHADER_3_0); txt+="\tIs Pixel Shader 3->0 supported?\n";
		txt+="queryFeature(video::EVDF_ARB_VERTEX_PROGRAM_1) = "; txt+=driver->queryFeature(video::EVDF_ARB_VERTEX_PROGRAM_1); txt+="\tAre ARB vertex programs v1->0 supported?\n";
		txt+="queryFeature(video::EVDF_ARB_FRAGMENT_PROGRAM_1) = "; txt+=driver->queryFeature(video::EVDF_ARB_FRAGMENT_PROGRAM_1); txt+="\tAre ARB fragment programs v1->0 supported?\n";
		txt+="queryFeature(video::EVDF_ARB_GLSL) = "; txt+=driver->queryFeature(video::EVDF_ARB_GLSL); txt+="\tIs GLSL supported?\n";
		txt+="queryFeature(video::EVDF_HLSL) = "; txt+=driver->queryFeature(video::EVDF_HLSL); txt+="\tIs HLSL supported?\n";
		txt+="queryFeature(video::EVDF_FRAMEBUFFER_OBJECT) = "; txt+=driver->queryFeature(video::EVDF_FRAMEBUFFER_OBJECT); txt+="\tAre framebuffer objects supported?\n";
		txt+="queryFeature(video::EVDF_VERTEX_BUFFER_OBJECT) = "; txt+=driver->queryFeature(video::EVDF_VERTEX_BUFFER_OBJECT); txt+="\tAre vertex buffer objects supported?\n";
		txt+="queryFeature(video::EVDF_ALPHA_TO_COVERAGE) = "; txt+=driver->queryFeature(video::EVDF_ALPHA_TO_COVERAGE); txt+="\tSupports Alpha To Coverage\n";
		txt+="queryFeature(video::EVDF_COLOR_MASK) = "; txt+=driver->queryFeature(video::EVDF_COLOR_MASK); txt+="\tSupports Color masks ?(disabling color planes in output)\n";
		txt+="queryFeature(video::EVDF_MULTIPLE_RENDERprintARGETS) = "; txt+=driver->queryFeature(video::EVDF_MULTIPLE_RENDER_TARGETS); txt+="\tSupports multiple render targets at once?\n";
		txt+="queryFeature(video::EVDF_MRT_BLEND) = "; txt+=driver->queryFeature(video::EVDF_MRT_BLEND); txt+="\tSupports separate blend settings for multiple render targets?\n";
		txt+="queryFeature(video::EVDF_MRT_COLOR_MASK) = "; txt+=driver->queryFeature(video::EVDF_MRT_COLOR_MASK); txt+="\tSupports separate color masks for multiple render targets?\n";
		txt+="queryFeature(video::EVDF_MRT_BLEND_FUNC) = "; txt+=driver->queryFeature(video::EVDF_MRT_BLEND_FUNC); txt+="\tSupports separate blend functions for multiple render targets?\n";
		txt+="queryFeature(video::EVDF_GEOMETRY_SHADER) = "; txt+=driver->queryFeature(video::EVDF_GEOMETRY_SHADER); txt+="\tSupports geometry shaders?\n";
		return txt;
	}


	core::stringc dbStr(video::IVideoDriver* driver)
	{
		core::stringc txt;
		txt+="video::IVideoDriver\n";
		txt+="ColorFormat = "; txt+=dbStr(driver->getColorFormat()); txt+="\n";
		txt+="CurrentRenderTargetSize = "; txt+=dbStr(driver->getCurrentRenderTargetSize()); txt+="\n";
		txt+="DriverType = "; txt+=dbStr(driver->getDriverType()); txt+="\n";

		u32 c = driver->getDynamicLightCount();
		txt+="DynamicLightCount = "; txt+=c; txt+="\n";
		if (c>0)
		{
			for (u32 i=0; i<c; ++i)
			{
				txt+=dbStr(driver->getDynamicLight(i));
			}
		}
		//txt+=driver->getExposedVideoData();
		txt+="FPS = "; txt+=driver->getFPS(); txt+="\n";
		//txt+="Material2D = "; txt+=driver->getMaterial2D(); txt+="\n";
		txt+="MaterialRendererCount = "; txt+=driver->getMaterialRendererCount(); txt+="\n";
		//txt+="MaterialRenderer = "; txt+=driver->getMaterialRenderer(); txt+="\n";
		//txt+="MaterialRendererName = "; txt+=driver->getMaterialRendererName(); txt+="\n";
		txt+="MaximalDynamicLightAmount = "; txt+=driver->getMaximalDynamicLightAmount(); txt+="\n";
		txt+="MaximalPrimitiveCount = "; txt+=driver->getMaximalPrimitiveCount(); txt+="\n";
		txt+="MaxTextureSize = "; txt+=dbStr(driver->getMaxTextureSize()); txt+="\n";
		txt+="Name = "; txt+=driver->getName(); txt+="\n";
		txt+="PrimitiveCountDrawn = "; txt+=driver->getPrimitiveCountDrawn(); txt+="\n";
		txt+="ScreenSize = "; txt+=dbStr(driver->getScreenSize()); txt+="\n";
		txt+="TextureCreationFlag(ETCF_ALWAYS_32_BIT) = "; txt+=driver->getTextureCreationFlag(video::ETCF_ALWAYS_32_BIT); txt+="\n";
		txt+="TextureCount = "; txt+=driver->getTextureCount(); txt+="\n";
	//	txt+="TextureByIndex = "; txt+=driver->getTextureByIndex(); txt+="\n";
		txt+="Transform(video::ETS_WORLD) = "; txt+=dbStr(driver->getTransform(video::ETS_WORLD)); txt+="\n";
		txt+="Transform(video::ETS_VIEW) = "; txt+=dbStr(driver->getTransform(video::ETS_VIEW)); txt+="\n";
		txt+="Transform(video::ETS_PROJECTION) = "; txt+=dbStr(driver->getTransform(video::ETS_PROJECTION)); txt+="\n";
		txt+="Transform(video::ETS_TEXTURE_0) = "; txt+=dbStr(driver->getTransform(video::ETS_TEXTURE_0)); txt+="\n";
		txt+="Transform(video::ETS_TEXTURE_1) = "; txt+=dbStr(driver->getTransform(video::ETS_TEXTURE_1)); txt+="\n";
		txt+="Transform(video::ETS_TEXTURE_2) = "; txt+=dbStr(driver->getTransform(video::ETS_TEXTURE_2)); txt+="\n";
		txt+="Transform(video::ETS_TEXTURE_3) = "; txt+=dbStr(driver->getTransform(video::ETS_TEXTURE_3)); txt+="\n";
	//	txt+="VendorInfo = "; txt+=driver->getVendorInfo(); txt+="\n";
		txt+="ViewPort = "; txt+=dbStr(driver->getViewPort()); txt+="\n";
		txt+="queryFeature(video::EVDF_RENDER_TO_TARGET) = "; txt+=driver->queryFeature(video::EVDF_RENDER_TO_TARGET); txt+="\tIs driver able to render to a surface? "; txt+="\n";
		txt+="queryFeature(video::EVDF_TEXTURE_NSQUARE) = "; txt+=driver->queryFeature(video::EVDF_TEXTURE_NSQUARE); txt+="\tAre non-square textures supported? "; txt+="\n";
		txt+="queryFeature(video::EVDF_TEXTURE_NPOT) = "; txt+=driver->queryFeature(video::EVDF_TEXTURE_NPOT); txt+="\tAre non-power-of-two textures supported? "; txt+="\n";
		txt+="queryFeature(video::EVDF_HARDWARE_TL) = "; txt+=driver->queryFeature(video::EVDF_HARDWARE_TL); txt+="\tIs hardeware transform and lighting supported?"; txt+="\n";
		txt+="queryFeature(video::EVDF_MULTITEXTURE) = "; txt+=driver->queryFeature(video::EVDF_MULTITEXTURE); txt+="\tAre multiple textures per material possible?"; txt+="\n";
		txt+="queryFeature(video::EVDF_BILINEAR_FILTER) = "; txt+=driver->queryFeature(video::EVDF_BILINEAR_FILTER); txt+="\tIs driver able to render with a bilinear filter applied?"; txt+="\n";
		txt+="queryFeature(video::EVDF_MIP_MAP) = "; txt+=driver->queryFeature(video::EVDF_MIP_MAP); txt+="\tCan the driver handle mip maps?"; txt+="\n";
		txt+="queryFeature(video::EVDF_MIP_MAP_AUTO_UPDATE) = "; txt+=driver->queryFeature(video::EVDF_MIP_MAP_AUTO_UPDATE); txt+="\tCan the driver update mip maps automatically?"; txt+="\n";
		txt+="queryFeature(video::EVDF_STENCIL_BUFFER) = "; txt+=driver->queryFeature(video::EVDF_STENCIL_BUFFER); txt+="\tAre stencilbuffers switched on and does the device support stencil buffers?"; txt+="\n";
		txt+="queryFeature(video::EVDF_VERTEX_SHADER_1_1) = "; txt+=driver->queryFeature(video::EVDF_VERTEX_SHADER_1_1); txt+="\tIs Vertex Shader 1->1 supported?"; txt+="\n";
		txt+="queryFeature(video::EVDF_VERTEX_SHADER_2_0) = "; txt+=driver->queryFeature(video::EVDF_VERTEX_SHADER_2_0); txt+="\tIs Vertex Shader 2->0 supported?"; txt+="\n";
		txt+="queryFeature(video::EVDF_VERTEX_SHADER_3_0) = "; txt+=driver->queryFeature(video::EVDF_VERTEX_SHADER_3_0); txt+="\tIs Vertex Shader 3->0 supported?"; txt+="\n";
		txt+="queryFeature(video::EVDF_PIXEL_SHADER_1_1) = "; txt+=driver->queryFeature(video::EVDF_PIXEL_SHADER_1_1); txt+="\tIs Pixel Shader 1->1 supported?\n";
		txt+="queryFeature(video::EVDF_PIXEL_SHADER_1_2) = "; txt+=driver->queryFeature(video::EVDF_PIXEL_SHADER_1_2); txt+="\tIs Pixel Shader 1->2 supported?\n";
		txt+="queryFeature(video::EVDF_PIXEL_SHADER_1_3) = "; txt+=driver->queryFeature(video::EVDF_PIXEL_SHADER_1_3); txt+="\tIs Pixel Shader 1->3 supported?\n";
		txt+="queryFeature(video::EVDF_PIXEL_SHADER_1_4) = "; txt+=driver->queryFeature(video::EVDF_PIXEL_SHADER_1_4); txt+="\tIs Pixel Shader 1->4 supported?\n";
		txt+="queryFeature(video::EVDF_PIXEL_SHADER_2_0) = "; txt+=driver->queryFeature(video::EVDF_PIXEL_SHADER_2_0); txt+="\tIs Pixel Shader 2->0 supported?\n";
		txt+="queryFeature(video::EVDF_PIXEL_SHADER_3_0) = "; txt+=driver->queryFeature(video::EVDF_PIXEL_SHADER_3_0); txt+="\tIs Pixel Shader 3->0 supported?\n";
		txt+="queryFeature(video::EVDF_ARB_VERTEX_PROGRAM_1) = "; txt+=driver->queryFeature(video::EVDF_ARB_VERTEX_PROGRAM_1); txt+="\tAre ARB vertex programs v1->0 supported?\n";
		txt+="queryFeature(video::EVDF_ARB_FRAGMENT_PROGRAM_1) = "; txt+=driver->queryFeature(video::EVDF_ARB_FRAGMENT_PROGRAM_1); txt+="\tAre ARB fragment programs v1->0 supported?\n";
		txt+="queryFeature(video::EVDF_ARB_GLSL) = "; txt+=driver->queryFeature(video::EVDF_ARB_GLSL); txt+="\tIs GLSL supported?\n";
		txt+="queryFeature(video::EVDF_HLSL) = "; txt+=driver->queryFeature(video::EVDF_HLSL); txt+="\tIs HLSL supported?\n";
		txt+="queryFeature(video::EVDF_FRAMEBUFFER_OBJECT) = "; txt+=driver->queryFeature(video::EVDF_FRAMEBUFFER_OBJECT); txt+="\tAre framebuffer objects supported?\n";
		txt+="queryFeature(video::EVDF_VERTEX_BUFFER_OBJECT) = "; txt+=driver->queryFeature(video::EVDF_VERTEX_BUFFER_OBJECT); txt+="\tAre vertex buffer objects supported?\n";
		txt+="queryFeature(video::EVDF_ALPHA__TO_COVERAGE) = "; txt+=driver->queryFeature(video::EVDF_ALPHA_TO_COVERAGE); txt+="\tSupports Alpha To Coverage\n";
		txt+="queryFeature(video::EVDF_COLOR_MASK) = "; txt+=driver->queryFeature(video::EVDF_COLOR_MASK); txt+="\tSupports Color masks ?(disabling color planes in output)\n";
		txt+="queryFeature(video::EVDF_MULTIPLE_RENDER_TARGETS) = "; txt+=driver->queryFeature(video::EVDF_MULTIPLE_RENDER_TARGETS); txt+="\tSupports multiple render targets at once?\n";
		txt+="queryFeature(video::EVDF_MRT_BLEND) = "; txt+=driver->queryFeature(video::EVDF_MRT_BLEND); txt+="\tSupports separate blend settings for multiple render targets?\n";
		txt+="queryFeature(video::EVDF_MRT_COLOR_MASK) = "; txt+=driver->queryFeature(video::EVDF_MRT_COLOR_MASK); txt+="\tSupports separate color masks for multiple render targets?\n";
		txt+="queryFeature(video::EVDF_MRT_BLEND_FUNC) = "; txt+=driver->queryFeature(video::EVDF_MRT_BLEND_FUNC); txt+="\tSupports separate blend functions for multiple render targets?\n";
		txt+="queryFeature(video::EVDF_GEOMETRY_SHADER) = "; txt+=driver->queryFeature(video::EVDF_GEOMETRY_SHADER); txt+="\tSupports geometry shaders?\n";
		return txt;
	}

} // end namespace irr
