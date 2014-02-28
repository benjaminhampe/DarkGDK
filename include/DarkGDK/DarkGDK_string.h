#ifndef __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_TO_STRING_H__
#define __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_TO_STRING_H__

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

	// WORD to HEX-STRING
	// Urheber dieser Funktion ist Benjamin Hampe, bitte beachten Sie bei Verwendung die Lizenzbedingungen.
	// Template-Funktion zur Umwandlung einer Ganzzahl in einen hexadezimalen String (Ziffern 0..F)
	// Funktion ist für folgende Datentypen gedacht: u8,u16,u32,u64,s8,s16,s32,s64
	// es wird kein 0x vorangestellt, z.B. u8=255 --> "FF"
	template <class T>
	core::stringc dbHex(T word)
	{	s32 c = sizeof(word); // z.B. c = 4 Bytes = 32 Bit
		if (c<1) return core::stringc("Die Zahl muss mindestens ein Byte haben.");
		if (c>255) return core::stringc("Die Zahl darf maximal 255 Bytes haben.");
		core::stringc s;
		for (u8 i=0; i<c; i++) // iteriere bytezahl, z.B. i=0
		{	for (u8 g=0; g<2; g++) // iteriere Nibble 0 und 1, z.B. g=0
			{
				u8 byte = word >> ((c-i-1)<<3);	// z.B. 0xF8AA5BC2 >> 24 = 0x000000F8 = 0xF8
				u8 nibble;
				if (g==0)
					nibble = byte >> 4;	// z.B. 0xF8 >> 4 = 0x0F = 15 damit s+='F'
				else
					nibble = byte & 0x0F; // z.B. 0xF8 & 0x0F = 0x08 damit s+='8'

				if (nibble<10)
					s+=(wchar_t)(L'0'+nibble); // ASCII '0'...'9' = 48...57
				else
					s+=(wchar_t)(L'A'+(nibble-10));	// ASCII 'A'...'F' = 65...70
			}
		}
		return s;
	}

	template <class T> core::stringc dbStr(const core::CMatrix4<T>& m)
	{
		core::stringc txt("CMatrix4<T>\n");
		txt+=m(0,0); txt+=","; txt+=m(0,1); txt+=","; txt+=m(0,2); txt+=","; txt+=m(0,3); txt+="\n";
		txt+=m(1,0); txt+=","; txt+=m(1,1); txt+=","; txt+=m(1,2); txt+=","; txt+=m(1,3); txt+="\n";
		txt+=m(2,0); txt+=","; txt+=m(2,1); txt+=","; txt+=m(2,2); txt+=","; txt+=m(2,3); txt+="\n";
		txt+=m(3,0); txt+=","; txt+=m(3,1); txt+=","; txt+=m(3,2); txt+=","; txt+=m(3,3); txt+="\n";
		return txt;
	}

	template <class T> core::stringc dbStr(const core::CMatrix4<T>& m, const core::stringc& name)
	{
		core::stringc txt;
		txt+=name;
		txt+="\n";
		txt+=dbStr(m);
		return txt;
	}

	template <class T> core::stringc dbStr(const core::vector2d<T>& v)
	{
		core::stringc txt("");
		txt+=v.X; txt+=","; txt+=v.Y;
		return txt;
	}

	template <class T> core::stringc dbStr(const core::vector3d<T>& v)
	{
		core::stringc txt("");
		txt+=v.X;	txt+=","; txt+=v.Y;	txt+=","; txt+=v.Z;
		return txt;
	}

	template <class T> core::stringc dbStr(const core::dimension2d<T>& v)
	{
		core::stringc txt("");
		txt+=v.Width;	txt+=","; txt+=v.Height;
		return txt;
	}

	template <class T> core::stringc dbStr(const core::rect<T>& rc)
	{
		core::stringc txt("");
		txt+=dbStr<T>(rc.UpperLeftCorner);	txt+=","; txt+=dbStr<T>(rc.LowerRightCorner);
		return txt;
	}

	template <class T> core::stringc dbStr(const core::aabbox3d<T>& box)
	{
		core::stringc txt("");
		txt+=dbStr<T>(box.MinEdge); txt+=","; txt+=dbStr<T>(box.MaxEdge);
		return txt;
	}

	template <class T> core::stringc dbStr(const core::line3d<T>& v)
	{
		core::stringc txt("");
		txt+=dbStr<T>(v.start);	txt+=","; txt+=dbStr<T>(v.end);
		return txt;
	}

	template <class T> core::stringc dbStr(const core::plane3d<T>& v)
	{
		core::stringc txt("");
		txt+=dbStr<T>(v.Normal); txt+=","; txt+=v.D;
		return txt;
	}

	template <class T> core::stringc dbStr(const core::array<T>& a)
	{
		core::stringc s("[Array]\n");    // [Header]
		u32 c=a.size();
		s+=c;
		for (u32 i=0; i<c; ++i)
		{
			s+=dbStr<T>(a[i]);
			s+="\n";
		}
		s+="\n";
		return s;
	}

	core::stringc dbStr(const char* value);

	core::stringw dbStr(const wchar_t* value);

	core::stringc dbStr(u8 value);

	core::stringc dbStr(s8 value);

	core::stringc dbStr(u16 value);

	core::stringc dbStr(s16 value);

	core::stringc dbStr(u32 value);

	core::stringc dbStr(s32 value);

	core::stringc dbStr(f32 value);

	core::stringc dbStr(f64 value);

	core::stringc dbStr( const core::stringc& key, const core::stringc& value);

	// BOOL to STRING
	// Urheber dieser Funktion ist Benjamin Hampe, bitte beachten Sie bei Verwendung die Lizenzbedingungen.
	// Funktion zur Umwandlung eines Booleschen Wertes in einen String ("TRUE","FALSE" oder "true,false")
	core::stringc dbStr(bool value, bool capitals = true);

	// FLOAT to STRING
	// Urheber dieser Funktion ist Benjamin Hampe, bitte beachten Sie bei Verwendung die Lizenzbedingungen.
	// Umwandlung f32 in formattierten String beliebiger Präzision, mit Stringklasse der Irrlicht-Engine
	core::stringc dbStr(f32 value, s32 width, s32 frac);

	// DOUBLE to STRING
	// Urheber dieser Funktion ist Benjamin Hampe, bitte beachten Sie bei Verwendung die Lizenzbedingungen.
	// Umwandlung f64 in formattierten String beliebiger Präzision, mit Stringklasse der Irrlicht-Engine
	core::stringc dbStr(f64 value, s32 width, s32 frac);

	// SGUIEvent
	core::stringc dbStr(const SEvent::SGUIEvent& e);

	// SKeyInput
	core::stringc dbStr(const SEvent::SKeyInput& e);

	// SJoystickEvent
	core::stringc dbStr(const SEvent::SJoystickEvent& e);

	// SLogEvent
	core::stringc dbStr(const SEvent::SLogEvent& e);

	// SMouseInput
	core::stringc dbStr(const SEvent::SMouseInput& e);

	// EMOUSE_INPUT_EVENT
	core::stringc dbStr(EMOUSE_INPUT_EVENT e);

	// EGUI_EVENT_TYPE
	core::stringc dbStr(gui::EGUI_EVENT_TYPE e);

	core::stringc dbStr(io::IFileSystem& fs);

	core::stringc dbStr(const core::quaternion& v);

	core::stringc dbStr(E_DEVICE_TYPE e);

	core::stringc dbStr(video::ECOLOR_FORMAT e);

	core::stringc dbStr(video::E_DRIVER_TYPE e);

	core::stringc dbStr(video::E_ANTI_ALIASING_MODE e);

	core::stringc dbStr(const video::SColor& c);

	core::stringc dbStr(const video::SColorf& c);

	core::stringc dbStr(const video::S3DVertex& v);

	core::stringc dbStr(const video::SLight& light);

	core::stringc dbStr(const video::SMaterial& material);

	core::stringc dbStr(const SIrrlichtCreationParameters& params);

	core::stringc dbStr(video::IVideoModeList* modes);

	core::stringc dbStr(const scene::SMeshBuffer& meshBuffer);

	core::stringc dbStr(scene::ICameraSceneNode* cam);

	core::stringc dbStr(IrrlichtDevice* device);

	core::stringc dbStr(video::IVideoDriver* driver);
} // end namespace irr

#endif // __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_H__
