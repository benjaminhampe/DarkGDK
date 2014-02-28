// Copyright (C) 2008-2012 Benjamin Hampe
// This file uses parts of the "Irrlicht Engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "CMidi.h"

#include <irrlicht.h>

#ifdef _IRR_COMPILE_WITH_PORTMIDI_
#include <portmidi.h>
#endif // _IRR_COMPILE_WITH_PORTMIDI_

namespace irr
{
//
// Die folgende Tabelle zeigt, welche Nummern für welche Noten stehen
//Oktave||                     Notennummer
//   #  ||
//      || C   | C#  | D   | D#  | E   | F   | F#  | G   | G#  | A   | A#  | B
//-----------------------------------------------------------------------------
//   0  ||   0 |   1 |   2 |   3 |   4 |   5 |   6 |   7 |   8 |   9 |  10 | 11
//   1  ||  12 |  13 |  14 |  15 |  16 |  17 |  18 |  19 |  20 |  21 |  22 | 23
//   2  ||  24 |  25 |  26 |  27 |  28 |  29 |  30 |  31 |  32 |  33 |  34 | 35
//   3  ||  36 |  37 |  38 |  39 |  40 |  41 |  42 |  43 |  44 |  45 |  46 | 47
//   4  ||  48 |  49 |  50 |  51 |  52 |  53 |  54 |  55 |  56 |  57 |  58 | 59
//   5  ||  60 |  61 |  62 |  63 |  64 |  65 |  66 |  67 |  68 |  69 |  70 | 71
//   6  ||  72 |  73 |  74 |  75 |  76 |  77 |  78 |  79 |  80 |  81 |  82 | 83
//   7  ||  84 |  85 |  86 |  87 |  88 |  89 |  90 |  91 |  92 |  93 |  94 | 95
//   8  ||  96 |  97 |  98 |  99 | 100 | 101 | 102 | 103 | 104 | 105 | 106 | 107
//   9  || 108 | 109 | 110 | 111 | 112 | 113 | 114 | 115 | 116 | 117 | 118 | 119
//  10  || 120 | 121 | 122 | 123 | 124 | 125 | 126 | 127 |

void Test(ITimer* timer, ILogger* logger)
{
	if (!timer)
		return;

	if (!logger)
		return;

	srand( timer->getRealTime());

	core::stringc s;
	for ( s32 i=0; i<127; i++)
	{
		CMidiTools midiTools;
		s32 a = rand()%127;
		s="A "; s+=midiTools.getNameFromNote(a, true); s+=", Note = "; s+=a;
		s+=", B "; s+=midiTools.getNameFromNote(i, false); s+=", Note = "; s+=i;
		s+=", Count = "; s+=midiTools.getNoteCount(a,i);
		s+=" == "; s+=midiTools.getNoteCount(midiTools.getNameFromNote(a),midiTools.getNameFromNote(i));
		s+=", Frequency = A "; s+=midiTools.getFrequencyFromNote(a); s+=" B "; s+=midiTools.getFrequencyFromNote(i);
		s+=", notes = A "; s+=midiTools.getNoteFromFrequency(midiTools.getFrequencyFromNote(a)); s+=" B ";  s+=midiTools.getNoteFromFrequency(midiTools.getFrequencyFromNote(i));
		s+=", BlackKeys = "; s+=midiTools.getBlackKeyCount(a,i); s+=", WhiteKeys = "; s+=midiTools.getWhiteKeyCount(a,i);
		logger->log( s.c_str(), ELL_NONE );
	}
}

core::stringc CMidiTools::getNameFromNote( s32 midiNote, bool major) const
{
	core::stringc name;

	int note = midiNote%12; // RestDivision, Rest ist note innerhalb der Octave
	int octave = midiNote/12; // (Start-Rest)/12 ist exakte Oktave

	switch (note)
	{
		case 0: name+="C"; break;
		case 1: if (major) name+="C#"; else name+="Des"; break;
		case 2: name+="D"; break;
		case 3: if (major) name+="D#"; else name+="Es"; break;
		case 4: name+="E"; break;
		case 5: name+="F"; break;
		case 6: if (major) name+="F#"; else name+="Ges"; break;
		case 7: name+="G"; break;
		case 8: if (major) name+="G#"; else name+="Aes"; break;
		case 9: name+="A"; break;
		case 10: if (major) name+="A#"; else name+="B"; break;
		case 11: name+="H"; break;
		default: name+="?"; break;
	}

	switch (octave)
	{
		case 0: name+="-1"; break;
		case 1: name+="0"; break;
		case 2: name+="1"; break;
		case 3: name+="2"; break;
		case 4: name+="3"; break;
		case 5: name+="4"; break;
		case 6: name+="5"; break;
		case 7: name+="6"; break;
		case 8: name+="7"; break;
		case 9: name+="8"; break;
		case 10: name+="9"; break;
		case 11: name+="10"; break;
		default: name+="?"; break;
	}

	return name;
}

s32 CMidiTools::getNoteFromName( const core::stringc& name ) const
{
	return 0;
}
s32	CMidiTools::getNoteFromFrequency( f32 frequency ) const
{
	return 0;
}

bool CMidiTools::isBlackKey( s32 midiNote ) const
{
	bool black = false;

	midiNote %= 12;

	switch (midiNote)
	{
		case 1: black = true; break;
		case 3: black = true; break;
		case 6: black = true; break;
		case 8: black = true; break;
		case 10: black = true; break;
		default: break;
	}

	return black;
}

bool CMidiTools::isBlackKey( const core::stringc& name ) const
{
	return isBlackKey( getNoteFromName( name ) );
}

bool CMidiTools::isWhiteKey( s32 midiNote ) const
{
	return !isBlackKey( midiNote );
}

bool CMidiTools::isWhiteKey( const core::stringc& name ) const
{
	return !isBlackKey( getNoteFromName( name ) );
}

s32 CMidiTools::getNoteCount( s32 startNote, s32 endNote ) const
{
	if (endNote < startNote )
		core::swap(startNote, endNote);

	return endNote-startNote + 1;
}

s32 CMidiTools::getNoteCount( const core::stringc& startNote, const core::stringc& endNote ) const
{
	return getNoteCount ( getNoteFromName( startNote ), getNoteFromName( endNote ) );
}

f32 CMidiTools::getFrequencyFromNote( s32 midiNote ) const
{
	return 440.f*powf(2.f,(f32)(midiNote-69)/12.f);
}



s32 CMidiTools::getWhiteKeyCount( s32 startNote, s32 endNote ) const
{
	return getNoteCount(startNote, endNote) - getBlackKeyCount( startNote, endNote );
}

s32 CMidiTools::getWhiteKeyCount( const core::stringc& startNote, const core::stringc& endNote ) const
{
	return getWhiteKeyCount( getNoteFromName ( startNote ), getNoteFromName( endNote ) );
}

s32 CMidiTools::getBlackKeyCount( s32 startNote, s32 endNote ) const
{
	return 0;
}

s32 CMidiTools::getBlackKeyCount( const core::stringc& startNote, const core::stringc& endNote ) const
{
	return getBlackKeyCount( getNoteFromName ( startNote ), getNoteFromName( endNote ) );
}

} // END NAMESPACE IRR



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
//
// Standard MIDI File Format from Dustin Caldwell
//
// Das standard-MIDI-Format ist sehr widerspänstig. Betrachtet als ein Ganzes ist es ziemlich überwältigend. Egal, wie man es sieht, eine Musiksequenz so genau zu beschreiben, dass man es 1:1 wiedergeben kann ist keine einfache Sache. Trotz dieser Schwierigkeit ist der Aufbau des MIDI-Formates recht gut nachvollziehbar, wenn es einmal verstanden ist.
// An diesem Punkt muss ich sagen, dass ich keinesfalls ein Profi in Sachen MIDI oder MIDI-Dateien bin. Ich habe eine Gravis UltraSound Karte für meinen PC und nachdem ich ein paar Mididateien (.MID) gehört hatte, dachte ich "Ich würde gerne meine eigenen Mididateien machen". Mehrere nervenzerreißende Stunden später bemerkte ich, dass das wirklich ein hartes Stück Arbeit ist. Aber ich konnte einfach nicht zulassen, dass mich so ein "dummes" Dateiformat stoppt :)! Falls ihr irgendwelche Fehler in diesem Dokument findet, lasst es mich wissen und ich werde diesen Fehler beheben. Dieses Dokument beschreibt desweiteren nicht JEDES vorhandene Midi-Format und auch nicht jedes Midi-Kommando. Es ist nur ein Basisdokument, aus dem ein recht guter Midi-Player und Editor herauskommen soll :)!
//
//1. Übersicht
// Eine Midi-Datei (.MID) besteht aus 2 Teilen, Header-Chunks und Track-Chunks. Eine Midi-Datei enthält EINEN Header-Chunk, der das Dateiformat angibt usw. und eine bestimmte Anzahl an Track-Chunks.
//
//2. Header Chunk
// Der Header-Chunk befindet sich am Dateianfang und beschreibt die Datei in 3 Formen. Der Header-Chunk sieht immer so aus:
//
// 4D 54 68 64 00 00 00 06 ff ff nn nn dd dd
//
// Das ASCII-Äquivalent der ersten 4 Bytes ist "MThd". Nach dem "MThd" folgt die 4-Byte-Größe des Headers. Dieser wert beträgt immer 00 00 00 06, da der .Mid-Header immer eine größe von 6 Bytes hat.
//
//ff: ff gibt das Dateiformat an. Es gibt 3 Formate:
// 0 - eine Spur
// 1 - mehrere Spuren, synchron
// 2 - mehrere Spuren, nicht synchron
//
// "Eine Spur" ist eigentlich selbsterklärend - es kommt halt nur eine Spur im .MID vor. "Mehrere Spuren, synchron" heißt, dass alle Spuren synchron gespielt werden, in anderen Worten, sie starten alle gleichzeitig. Nicht-synchrone Spuren müssen nicht unbedingt gleichzeitig starten und können absolut asynchron sein.
//
//nn: nn gibt die Anzahl der Tracks in einer MIDI-Datei an.
//dd: dd gibt die Anzahl der Delta-time ticks pro Viertelnote an (mehr dazu später)
//
//
//3. Der Track-Chunk:
//
// Der Rest einer MID-Datei nach dem Header-Chunk besteht aus Track-Chunks. Jeder Track hat einen Header und kann so viele MIDI-Kommandos enthalten wie nötig.
// Der Kopf eines Tracks ähnelt sehr dem Datei-Header:
//
// 4D 54 72 6B xx xx xx xx
//
// Wie der Header besitzen die ersten 4 Byte ein ASCII-Äquivalent. Dieses mal ist es "MTrk". Die 4 Bytes nach "MTrk" beschreibt die Länge des Tracks (ohne den Track-Kopf) in Bytes.
// Dem folgend kommen Midi-Ereignisse. Diese Ereignisse sind identisch zu den Daten, die von MIDI-Ports auf einem Synthesizer geliefert werden, jedoch mit einem Unterschied. Vor dem Midi-Ereignis steht eine Delta-Zeit. Eine Delta-Zeit gibt die Anzahl an Ticks an, nach denen ein Midi-Ereignis ausgeführt werden soll. Die Anzahl der Ticks pro Viertelnote wurde vorher im Datei-Header-Chunk festgelegt. Diese Delta-Zeit ist ein Variablen-Längen-Verschlüsselter-Wert :). Dieses Format kann zwar verwirren, hat aber den Vorteil, dass keine kleinen Zahlen benötigt werden, die sinnlos Bytes verschwenden. Die Zahl wird konvertiert in ein 7-bit-Byte, wobei das wichtigste Bit jedes Bytes "1" beträgt, bis auf das letzte Byte der Nummer, das ein MSB (Most Significant Bit = Wichtigstes Bit [ganz links]) von 0 hat. Dies erlaubt, dass mit einem mal 1 Byte gelesen werden kann... wenn ein MBS von 0 erscheint, muss dies das letzte Byte der Nummer gewesen sein. Die Delta-Zeit sollte mindestens 4 Bytes lang sein. Darauf folgt ein Midi-Ereignis. Jedes MIDI-Ereignis besitzt ein Kommandobyte, dass ein MSB von 1 besitzt ( der Wert ist dann >=128). Eine Liste für vieler dieser Kommandos befindet sich in Anhang A. Jedes Kommando hat verschiedene Parameter und Längen, aber die Daten, die dann folgen haben immer ein MSB von 0 (<128). Die Ausnahme hierzu ist ein Meta-Ereignis, die Daten mit einem MSB von 1 haben. Wie auch immer, Meta-Ereignisse benötigen einen Längenparameter, die Verwirrung vermeiden sollen.
//
// Eine Feinheit, die für Verwirrung sorgen kann, ist der sog. "running mode". Das passiert, wenn das aktuelle Midi-Kommando weggelassen wird. Das heißt, dass das MIDI-Ereignis aus einer Delta-Zeit und ein einem Parameter, der zu dem Kommando leiten würde, währe dieses einbezogen, besteht :).
//
//4. Ende
//
// Falls diese Erklärung nur für nochmehr verwirrung über dieses Thema gesorgt haben sollte, enthalten die Anhänge Beispiele, die dem besseren Verständnis dienen sollten.
//
//
//
//Anhang A: Midi-Ereignis Kommandos
//
// jedes MIDI-Kommando hat 2 Teile. Der linken Nybble (Ein Nybble = 4 Bit) enthält das Kommando und rechte Nybble enthält den Kanal auf welchem das Kommando ausgeführt werden soll. Es gibt 16 Midi-Kanäle und 8 Midi-Kommandos (das Kommandonybble muss einen MSB von 1 haben). In der folgenden Tabelle gibt "x" den Kanal an.
//Hex	Binär	Daten	Beschreibung
// 8x	 1000xxxx	 nn vv	 Note aus
// nn=Noten-Nummer
// vv=Geschwindigkeit
// 9x	 1001xxxx	 nn vv	 Note an
// nn=Noten-Nummer
// vv=Geschwindigkeit
// Ax	 1010xxxx	 nn vv	 Noten-Abklingen
// nn=Note
// vv=Geschwindikkeit
// Bx	 1011xxxx	 cc vv	 Kontrolländerung
// cc=Kontrollnummer
// vv=Neuer Wert
// Cx	 1101xxxx	 cc	 Kanalausklang
// cc=Kanalnummer
// Ex	 1110xxxx	 bb tt	 Tonhöhenänderung
// bb=Boden
// tt=Höchster Wert
//
//
//
// Die folgende Tabelle zeigt Meta-Ereignisse, die keine Midi-Kanal.Nummer haben. Sie haben folgendes Format:
//
// FF xx nn dd
//
// Alle Meta-Ereignisse starten mit FF (#255), gefolgt vom Kommando (xx)m der Länge oder der Anzahl an Bytes, die die Daten enthalten (nn) und den eigentlichen Daten (dd).
//Hex	Binär	Daten	Beschreibung
// 00	 00000000	 nn ssss	 Setzt die Sequenz der Spur.
// nn=02 (Länge der 2-Byte Sequenznummer)
// ssss=Sequenznummer
// 01	 00000001	 nn tt ..	 Text.
// nn=Länge in Bytes des Textes
// tt=eigentlicher Text
// 02	 00000010	 nn tt ..	 Das gleiche wie "Text", aber benutzt
// als Copyright-info.
// nn tt=genauso wie im Textereignis
// 03	 00000011	 nn tt ..	 Sequenz oder Spurenname.
// nn tt=genauso wie im Textereignis
// 04	 00000100	 nn tt ..	 Spuren-Instrumenten -Name
// nn tt=genauso wie im Textereignis
// 05	 00000101	 nn tt ..	 Lyrik
// nn tt=genauso wie im Textereignis
// 06	 00000110	 nn tt .. 	 Marker
// nn tt=genauso wie im Textereignis
// 07	 00000111	 nn tt ..	 Hinweis
// nn tt=genauso wie im Textereignis
// 2F	 00101111	 00	 Dieses Ereignis muss am Ende jeder Spur kommen.
// 51	 01010001	 03 tttttt	 Neues Tempo
// tttttt=mikrosekunden/Viertelnote
// 58	 01011000	 04 nn dd ccbb	 Zeit Signatur ("Notenschlüssel")
// nn=Zähler der Zeitsignatur.
// dd=Nenner der Zeitsignatur.
// 2=viertel
// 3=achtel, usw.
// cc=Anzahl Ticks in einem Metronomschlag
// bb=anzahl 32tel-Noten zu einer Viertelnode
// 59	 01011001	 02 sf mi	 Feinabstimmung
// sf=(>128)Ton erhöhen/(<128) Ton niedersetzen
// 7=7 sharps)
// mi=hoch/tief (0=hoch, 1=tief)
// 7F	 01111111	 xx dd ..	 Sequenzinformationen
// xx=Anzahl an zu sendenden Bytes
// dd=Daten
//
//
//
// Die folgende Liste zeigt Systemnachichten, die seiner Kontrolle dienen. Sie haben keine MIDI-Kanal-Nummer. (Normalerweise kommen sie nur vor, um ein KeyBoard zu kontrollieren usw.)
//Hex	Binär	Daten	Beschreibung
// F8	 11111000	  	 Pause, falls eine Synchronisation notwendig ist
// FA	 11111010	  	 Starte Sequenz
// FB	 11111011	  	 Spiele gestoppte Sequenz weiter
// FC	 11111100	  	 Sequenz anhalten
//
//
//
// Die folgende Tabelle zeigt, welche Nummern für welche Noten stehen
//Oktave||                     Notennummer
//   #  ||
//      || C   | C#  | D   | D#  | E   | F   | F#  | G   | G#  | A   | A#  | B
//-----------------------------------------------------------------------------
//   0  ||   0 |   1 |   2 |   3 |   4 |   5 |   6 |   7 |   8 |   9 |  10 | 11
//   1  ||  12 |  13 |  14 |  15 |  16 |  17 |  18 |  19 |  20 |  21 |  22 | 23
//   2  ||  24 |  25 |  26 |  27 |  28 |  29 |  30 |  31 |  32 |  33 |  34 | 35
//   3  ||  36 |  37 |  38 |  39 |  40 |  41 |  42 |  43 |  44 |  45 |  46 | 47
//   4  ||  48 |  49 |  50 |  51 |  52 |  53 |  54 |  55 |  56 |  57 |  58 | 59
//   5  ||  60 |  61 |  62 |  63 |  64 |  65 |  66 |  67 |  68 |  69 |  70 | 71
//   6  ||  72 |  73 |  74 |  75 |  76 |  77 |  78 |  79 |  80 |  81 |  82 | 83
//   7  ||  84 |  85 |  86 |  87 |  88 |  89 |  90 |  91 |  92 |  93 |  94 | 95
//   8  ||  96 |  97 |  98 |  99 | 100 | 101 | 102 | 103 | 104 | 105 | 106 | 107
//   9  || 108 | 109 | 110 | 111 | 112 | 113 | 114 | 115 | 116 | 117 | 118 | 119
//  10  || 120 | 121 | 122 | 123 | 124 | 125 | 126 | 127 |

