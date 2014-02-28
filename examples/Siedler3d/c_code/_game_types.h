//_game_types.h

#ifndef __GAME_TYPES_H_INCLUDED__
#define __GAME_TYPES_H_INCLUDED__

#include "stdafx.h"
#include "thc_vector.h"
#include "thc_vertex.h"

using namespace thc;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//!
//!		ENUMERATIONS die das Spiel benötigt
//!
///////////////////////////////////////////////////////////////////////////////////////////////////////////


enum	MODE_GAME 	{	RUNDE_1_DICE,
						RUNDE_2_PLACE, 
						RUNDE_3_LOOP				
													};
enum	MODE_TXT	{	TXT_NONE,
						TXT_RUNDE_1_WELCOME,
						TXT_RUNDE_1_REDICE,
						TXT_RUNDE_2_WELCOME,
						TXT_RUNDE_3_WELCOME
													};
enum	MODE_UI 	{	UI_NONE,
						UI_BUTTON_DICE, 
						UI_BUTTON_PLAY_CARD,
						UI_BUTTON_TRADE_CARD,
						UI_BUTTON_BANK,
						UI_BUTTON_ENDTURN,
						UI_BUTTON_UNDO,
						UI_BUTTON_KAUF_STRASSE,
						UI_BUTTON_KAUF_SIEDLUNG,
						UI_BUTTON_KAUF_STADT,
						UI_BUTTON_KAUF_KARTE		
													};
enum	MODE_OBJECT	{	OBJECT_NONE,
						OBJECT_INIT,
						OBJECT_LOOP,
						OBJECT_DELETE				
													};
enum    MODE_TODO	{	TODO_NONE,
						TODO_END_ROUND,
						TODO_PLACE_RAUBER,
						TODO_LOOSE_HALF_CARDS,
						TODO_STEEL_CARD,
						TODO_WIN
													};

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//!
//!		STRUKTUREN die das Spiel benötigt
//!
///////////////////////////////////////////////////////////////////////////////////////////////////////////

struct PICK_OBJECT{	int obj,old;	};

struct STATIC_TEXT
{
	bool visible;
	int x,y;
	DWORD color;
	std::string name,txt;
	bool left;				 // ALIGN 0=center, 1=left
};
struct INFO
{
	DWORD color;
	std::string txt;
};
struct W_WAYPOINT
{
	std::vector<int> next_W;	// maximale Größe = 3
	std::vector<int> next_S;	// maximale Größe = 3
	std::vector<int> next_T;	// maximale Größe = 3

	bool disabled;					// 0 = frei zum bebauen, 1 = gesperrt, da ein Nachbar W_Waypoint schon bebaut ist
	short bebaut;					// 0 = frei zum bebauen, 1 = Siedlung, 2 = Stadt
	short player;					//-1 = frei zum bebauen, 0 = Player 1, 1 = Player 2, usw.
	int obj;					
	float x,y,z;
};
struct S_WAYPOINT
{
	std::vector<int> next_W;	// maximale Größe = 2
	std::vector<int> next_T;	// maximale Größe = 2
	short bebaut;					// 0 = frei zum bebauen, 1 = Strasse
	short player;					//-1 = frei zum bebauen, 0 = Player 1, usw.
	int obj;
	float x,y,z;
	int winkel;						// 0° = keine Drehung, 120° = Drehung, 240° = Drehung
	
};
struct TILE
{
	std::vector<S_WAYPOINT> way_S;	// eck-punkte
	std::vector<W_WAYPOINT> way_W;	// strassen-punkte
	std::string name;						// tile-name
	int type;								// 0 = Wasser,			1=Hafen3zu1,	2=HafenErz, 3=HafenHolz,	4=HafenLehm, 
												// 5 = HafenWeizen,	6=HafenWolle,	7=Wueste,	8=LandErz,		9=LandHolz, 
												// 10= LandLehm,		11=LandWeizen, 12=LandWolle
	bool raeuber;							// 0 = kein Räuber, 1=Räuber steht auf Tile
	int obj,tex;							// tile-object, tile-textur
	int chip_wert;							// zahlenchip-wert (von 2 bis 12 ohne 7)
	int chip_obj, chip_tex;				// zahlenchip-object
	float x,y,z;							// float koordinaten
	int winkel;								// 0°  = AB gültig, 60°= BC gültig, 120°= CD gültig, 180°= DE gültig,
												// 240°= EF gültig, 300= FA gültig 
												// (nur wichtig bei Häfen, da dort nur 2 W_WAYPOINTS existieren)
};
struct BUTTON
{
	bool bActive,bVisible,bInfo;
	std::string name,info;
	int img,x,y,dx,dy,type;
};
struct PLAYER
{
	bool disabled;			// sagt aus ob Player in der Runde aktiviert ist.
	std::string name;		// Player name
	DWORD color;			// Player color
	int type;				// Player type //0=Human, 1=CPU, 2=HumanTCP/IP, 3=HumanLAN

	short dice_1;			// Würfelwert
	short dice_2;			// Würfelwert

	int icon;				// Icon des Players 64x64
	int icon_border;		// Rahmen des Playericons 64x64
	int icon_strasse;		// Icon Strasse
	int icon_siedlung;		// Icon Siedlung
	int icon_stadt;			// Icon Stadt
	int tex_holz;			// Textur für Strassen, Siedlungen und Städte

	int nSiegpunkte;		// Anzahl Siegpunkte
	int nCards;				// Anzahl Rohstoffkarten
	int nErz;				// Anzahl Erz
	int nHolz;				// Anzahl Holz
	int nLehm;				// Anzahl Lehm
	int nWeizen;			// Anzahl Weizen
	int nWolle;				// Anzahl Wolle
	int nStrasse;			// Anzahl Strassen
	int nSiedlung;			// Anzahl Siedlungen
	int nStadt;				// Anzahl Städte
	
	int nKaufStrasse;		//Anzahl, wieviele Aktionen Kaufen möglich sind
	int nKaufSiedlung;   //Anzahl, wieviele Aktionen Kaufen möglich sind
	int nKaufStadt;      //Anzahl, wieviele Aktionen Kaufen möglich sind
	int nKaufKarte;      //Anzahl, wieviele Aktionen Kaufen möglich sind

	int nCardsRitter;		// Anzahl Ritterkarten
	int nCardsSiegpunkte;// Anzahl Siegpunktkarten
	int nCardsEreignis;	// Anzahl Ereigniskarten

	bool bBonusRittermacht;
	bool bBonusHandelsstrasse;

	bool bHafen3zu1;		// Has Player Hafen-3zu1
	bool bHafenErz;		// Has Player Hafen-Erz
	bool bHafenHolz;		// Has Player Hafen-Holz
	bool bHafenLehm;		// Has Player Hafen-Lehm
	bool bHafenWeizen;	// Has Player Hafen-Weizen
	bool bHafenWolle;		// Has Player Hafen-Wolle

};	

struct GAME
{  
//Game Globals
	PICK_OBJECT		pick;				// object nummer des objectes unter der maus
	int				obj_rauber;		// object nummer des räubers
	int				n_active_player;//index des aktiven spielers
	int				n_first_player;//index des start spielers
	float				n_size;			// enthält aktuellen würfelwert
	short				n_dice_1;		// enthält aktuellen würfelwert
	short				n_dice_2;		// enthält aktuellen würfelwert
	int btn_under_mouse;				// enthält index des buttons unter der maus (-1=kein button unter maus)
	int btn_active;					// enthält index des buttons der aktiv ist (-1=kein aktiver button)

	enum MODE_GAME mode_game;		// Gibt an in welcher Phase sich das Spiel befindet
	enum MODE_TXT mode_txt;			// Gibt an welche Texte vor dem eigentlichen Spielen angezeigt werden
	enum MODE_UI mode_ui;			// Modi für die einzelnen Button der UI, die geklickt werden können
	enum MODE_UI mode_ui_old;		// Modi für die einzelnen Button der UI, die geklickt werden können
	enum MODE_OBJECT mode_object;	// Modi für Objekterstellung, Benutzung und Löschung
	enum MODE_TODO mode_todo;		// Modi für Spielaktionen wie End Round (End Turn wird durch Button gesteuert)
									// Räuber, Steel Card, Ereigniskarten, 
									// also alles was als UI Button nicht existiert.

	int use_obj;						// temporäres object das global sein soll
	int use_obj_2;						// temporäres object das global sein soll
	int use_count_1;
	int use_count_2;
	int zeit;							// variable für dbTimer() Zeit
	bool any_flag;						// temporäres flag das global sein soll
	int runde;							// zählt wieviele runden schon gespielt wurden

//Buttons	
	std::vector<BUTTON> btn;		// enthält auch die Playericons
	std::vector<STATIC_TEXT> txt;			// enthält auch die Playernamen
	std::vector<INFO> info;
//Images
	std::vector<int> img_dice;		// TEXTUREN für Würfel
	std::vector<int> img_tile;		// TEXTUREN für Tiles
	std::vector<int> img_chip;		// TEXTUREN für Zahlenchips
	int img_way_S;						// TEXTUR für S_WAYPOINT
	int img_way_W;						// TEXTUR für W_WAYPOINT
	int mem_holz;						// TEXTUR Template for Players
	int mem_icon_strasse;			// TEXTUR Template for Players
	int mem_icon_siedlung;			// TEXTUR Template for Players
	int mem_icon_stadt;				// TEXTUR Template for Players
//Meshes
	int mesh_chip;						// MESH Template for Zahlenchips
	int mesh_hexagon;					// MESH Template for Tiles
	int mesh_waypoint_strasse;		// MESH Template for Waypoints
	int mesh_waypoint_siedlung;	// MESH Template for Waypoints
	int mesh_strasse;					// MESH Template for Players
	int mesh_siedlung;				// MESH Template for Players
	int mesh_stadt;					// MESH Template for Players
//Objects
	std::vector<TILE>			tiles;				// ARRAY TILES
	std::vector<PLAYER>		player;				// ARRAY PLAYER
	std::vector<W_WAYPOINT>	way_W;				// ARRAY WAYPOINT SIEDLUNG
	std::vector<S_WAYPOINT>	way_S;				// ARRAY WAYPOINT STRASSE	
//Punkte
	std::vector<Float3> vertex_W;					// PUNKTE :: wird von makemeshhexagon einmal gefüllt
	std::vector<Float3> vertex_S;					// PUNKTE :: wird von makemeshhexagon einmal gefüllt

	int index_tile;
	int index_way_w;
	int index_way_s;
	int index_player;
	bool show_dev_info;
};
struct SKYBOX
{
	string name;					// skybox name
	float radius_x,radius_y;   // skybox größe
	float diff_x,diff_y;			// größe der koordinaten überlappung -> clamping-ersatz, default 0
	string lt,dn,bk;				// textur-namen, NegX(left), NegY(down),NegZ(back)
	string rt,up,ft;				// textur-namen, PosX(right),PosY(up),  PosZ(front)
	vector<int> tex;				// textur-image-nummern (vector-size=6)
	int up_x,up_y,dn_x,dn_y;	// x,y-rotationswinkel der Deck/Bodenfläche in grad
};

#endif