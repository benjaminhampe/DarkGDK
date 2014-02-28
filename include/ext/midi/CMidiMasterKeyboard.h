//
// Filename:      CMidiMasterKeyboard.h
// Programmer:    Benjamin Hampe <benjaminhampe@gmx.de>
// Creation Date: Do Feb 15 12:29:45 PST 2012
// Last Modified: Fr Feb 16 15:14:04 PST 2012
// URL:
// Syntax:        GNU C/C++
//
// Description:   The example program shows how to open MIDI output,
//                send a MIDI message, and close MIDI output using the
//                PortMidi C library instead of accessing.
//
#ifndef __C_MIDI_MASTER_KEYBOARD_M_AUDIO_KEYSTATION_88_PRO_H__
#define __C_MIDI_MASTER_KEYBOARD_M_AUDIO_KEYSTATION_88_PRO_H__

#include <portmidi.h>
#include <irrlicht.h>

#include "CGUIMAudioSlider.h"
#include "CGUIMAudioButton.h"
#include "CGUIMAudioModWheel.h"
#include "CGUIMAudioPitchWheel.h"
#include "CGUIMAudioKnobSlider.h"
#include "CGUIMAudioLCD.h"
#include "CGUIMAudioLED.h"
#include "CGUIMAudioPushButton.h"
//#include "CGUIMAudioPianoKey.h"

class CMidiMasterKeyboard : public irr::IEventReceiver
{
public:

	CMidiMasterKeyboard(
		irr::IrrlichtDevice* irrDevice,
		const irr::core::recti& irrRect,
		const irr::video::SColor& irrColor,
		bool new_thread);

	~CMidiMasterKeyboard();

	virtual bool 										OnEvent(const irr::SEvent& event);

	void 												Panic();

	static irr::core::stringc 							GetName(int midiNote, bool major);

private:
	irr::IrrlichtDevice* 								Device;
	irr::gui::IGUIWindow* 								Win;
	irr::core::stringw 									WinTitle;
	irr::core::recti 									WinRect;
	irr::video::ITexture* 								BGTexture;
	irr::video::SColor	 								BGColor;
	irr::gui::IGUICheckBox* 							PowerButton;
	irr::gui::IGUIButton* 								PanicButton;
//	irr::gui::IGUICheckBox* 							RepeatNote;
//	irr::gui::IGUISpinBox* 								RepeatTime;
//	irr::gui::IGUIListBox* 								LogBox; // replaced with LCD
	irr::gui::IGUIComboBox* 							MidiInputBox;
	irr::gui::IGUIComboBox* 							MidiOutputBox;
	irr::gui::IGUIListBox* 								MidiMessageInputBox;
	irr::gui::IGUIListBox* 								MidiMessageOutputBox;

	struct MasterKeyboardKey
	{
		irr::core::stringw Name;
		int MidiNote;
		int BindKey;
		int Octave;
		irr::gui::IGUIButton* Button;
		irr::gui::IGUIStaticText* Label;
	};

	irr::core::array<MasterKeyboardKey> 				Keys;
	irr::core::array<irr::gui::CGUIMAudioButton*> 		Buttons;
	irr::core::array<irr::gui::CGUIMAudioPushButton*> 	PushButtons;
	irr::core::array<irr::gui::CGUIMAudioSlider*> 		Sliders;
	irr::core::array<irr::gui::CGUIMAudioKnobSlider*> 	Knobs;
	irr::core::array<irr::gui::CGUIMAudioLCDDisplay*> 	LCD;
	irr::core::array<irr::gui::CGUIMAudioLED*> 			Lamps;
	irr::core::array<irr::gui::IGUIStaticText*> 		Texts;
	irr::gui::CGUIMAudioPitchWheel* 					PitchWheel;
	irr::gui::CGUIMAudioPitchWheel* 					ModulationWheel;

	PmDeviceID 											DefaultMidiInputDeviceID;
	PmDeviceID 											DefaultMidiOutputDeviceID;
	int 												CurrentMidiChannel;
	int 												CurrentMidiProgram;
	int 												MasterVolume;
	int 												MasterPan;
//	int 												MasterNoteOffSwitch;

	PortMidiStream* MidiOutputStream;

private:
	void createWindow();
	void createControls();
	void createKeys();
	void openMidi();
	void closeMidi();
};

//Regler (MSB):
//
// 0  Bank Select MSB
// 1  Modulation
// 2  Breath Controller
// 3  nicht definiert
// 4  Foot Pedal
// 5  Portamento Time
// 6  DataEntry MSB
// 7  Volume
// 8  Balance
// 9  nicht definiert
// 10  Panpot
// 11  Expression
// 12-15 nicht definiert
// 16  General Purpose 1
// 17  General Purpose 2
// 18  General Purpose 3
// 19  General Purpose 4
// 20 - 31 nicht definiert	Regler (LSB):
//
// 32  Bank Select LSB
// 33  Modulation LSB
// 34  Breath Controller LSB
// 35  LSB
// 36  Foot Pedal LSB
// 37  Portamento Time LSB
// 38  DataEntry LSB
// 39  Volume LSB
// 40  Balance LSB
// 41  LSB
// 42  Panpot LSB
// 43  Expression LSB
// 44 - 47 nichtdefiniert LSB
// 48  General Purpose 1 LSB
// 49  General Purpose 2 LSB
// 50  General Purpose 3 LSB
// 51  General Purpose 4 LSB
// 52-63 nicht definiert LSB
//
//
//Schalter:
//
// 64  Sustain Pedal (Damper)
// 65  Portamento
// 66  Sustenuto
// 67  Soft Pedal
// 68  nicht definiert
// 69  Hold 2
// 70 nicht definiert
// 71 Harmonic Content (XG)
// 72  Release Time (XG)
// 73 Attack Time (XG)
// 74 Brightness (XG)
// 75 - 79 nicht definiert
// 80  General Purp 5
// 81  General Purp 6
// 82  General Purp 7
// 83  General Purp 8
// 84 - 90 nicht definiert
// 91  External Effects Depth
// 92  Tremolo Depth
// 93  Chorus Depth
// 94  Celeste Depth
// 95  Phaser Depth
// 96  Data Increment
// 97  Data Decrement
// 98  Non Registered Parameter LSB
// 99  Non Registered Parameter MSB
//100  Registered Parameter LSB
//101  Registered Parameter MSB
//102 - 120 nicht definiert
//
//Channel Mode Messages:
//
//121  Reset All Controllers
//122  Local Control Off
//123  All Notes Off
//124  Omni Mode Off
//125  Omni Mode On
//126  Mono Mode On = Poly Mode Off
//127  Poly Mode On = Mono Mode Off
#endif
