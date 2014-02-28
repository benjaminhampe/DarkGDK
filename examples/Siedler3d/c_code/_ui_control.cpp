// _ui_control.cpp

#include "_ui_control.h"

#include "stdafx.h"
#include "DarkGDK.h"
#include "main.h"

#include "_ui_create.h"
#include "_game_types.h"

#include "thc_text.h"
#include "thc_mouse.h"
#include "thc_is.h"
#include "thc_memblock.h"
#include "thc_image.h"
#include "thc_timer.h"

using namespace thc;

Timed_Text timed_text_1;
Timed_Text timed_text_2;
Timed_Text timed_text_3;

/*
Timed_Text timed_text_1(0,30,2,0,0xFFFFFFFF,"Hallo ich bin Timed Text 1",timer.getTime(),20000000);
Timed_Text timed_text_2(0,100,3,0,0xFFFFFFFF,"Hallo ich bin Timed Text 2",timer.getTime(),25000000);
Timed_Text timed_text_3(0,170,3,0,0xFFFFFFFF,"Hallo ich bin Timed Text 3",timer.getTime(),30000000);
*/

////////////////////////////////////////////
void UI_Control()
////////////////////////////////////////////
{
	int size=(int)game.btn.size();
	int i,img=0;

	//### PASTE IMAGES ###
	for (i=0; i<size; i++)
	{
		if (game.btn[i].bVisible==true)
		{
			img=game.btn[i].img;
			if (IsImage(img)==true)
			{
				dbPasteImage(img,game.btn[i].x,game.btn[i].y,1);
			}
		}
	}
	//### BUTTON UNDER MOUSE ###
			 game.btn_under_mouse=getBTN_under_mouse();
	int mm=game.btn_under_mouse;

	//### DRAW NAME && INFO ###
	if (mm>=0)
	{
		drawName(mm);
	}
	
	//### MOUSECLICK CONTROL ###
	if (mouse.c==1)
	{	
		//Wenn linke Maustaste noch nicht gedrückt ist
		if(keys[1]==false)
		{	
			//Setze den Sperrflag, dass linke Maustaste gedrückt wird, und nicht doppelt ausgewertet wird
			keys[1]=true;
			
			//Wenn neuer Button existiert
			if(mm>=0)
			{	
				//Wenn irgendein Button aktiviert ist
				if(game.btn_active>=0)
				{	
					//Prüfe ob aktivierter Button == neuer Button
					if(game.btn_active==mm)
					{	
						//Wenn ja, dann deaktiviere Button
						game.btn_active=-1;
					}
					else
					{	
						//Wenn nein, dann aktiviere neuen Button
						game.btn_active=mm;
					}
				}
				//Wenn kein Button aktiviert ist, dann aktiviere neuen Button
				else
				{	
					game.btn_active=mm;
				}
			}
		}
		// Switch Modes
		if (game.btn_active>=0)
		{
			game.mode_ui=UI_NONE;
			if (game.btn[game.btn_active].name.compare("Todo Dice")==0)			game.mode_ui=UI_BUTTON_DICE;
			if (game.btn[game.btn_active].name.compare("Todo Play Card")==0)	game.mode_ui=UI_BUTTON_PLAY_CARD;
			if (game.btn[game.btn_active].name.compare("Todo Trade Card")==0)	game.mode_ui=UI_BUTTON_TRADE_CARD;
			if (game.btn[game.btn_active].name.compare("Todo Bank")==0)			game.mode_ui=UI_BUTTON_BANK;
			if (game.btn[game.btn_active].name.compare("Todo End Turn")==0)		game.mode_ui=UI_BUTTON_ENDTURN;
			if (game.btn[game.btn_active].name.compare("Todo Undo")==0)			game.mode_ui=UI_BUTTON_UNDO;
			if (game.btn[game.btn_active].name.compare("Kauf Strasse")==0)		game.mode_ui=UI_BUTTON_KAUF_STRASSE;
			if (game.btn[game.btn_active].name.compare("Kauf Siedlung")==0)		game.mode_ui=UI_BUTTON_KAUF_SIEDLUNG;
			if (game.btn[game.btn_active].name.compare("Kauf Stadt")==0)		game.mode_ui=UI_BUTTON_KAUF_STADT;
			if (game.btn[game.btn_active].name.compare("Kauf Ereigniskarte")==0)game.mode_ui=UI_BUTTON_KAUF_KARTE;
		}
		else
		{
			game.mode_ui=UI_NONE;
		}
	}
	//Wenn linke Maustaste nicht gedrückt wird, dann setze den Sperrflag zurück
	else
	{
		keys[1]=false;
	}

	//### ACTIVE BUTTON ###
	if (game.btn_active>=0)
	{
		int m1=game.btn[game.btn_active].x;
		int m2=game.btn[game.btn_active].y;
		int m3=game.btn[game.btn_active].dx+m1;
		int m4=game.btn[game.btn_active].dy+m2;
		drawRect(m1,m2,m3,m4,0);
	}

	//TEXTE
	StartText();
	size=(int)game.txt.size();
	for (i=0; i<size; i++)
	{
		if (game.txt[i].visible==true)
		{
			if (game.txt[i].left==true)
			{
				TextColor(1,game.txt[i].x,game.txt[i].y,0,(char*)game.txt[i].txt.c_str(),game.txt[i].color);
			}
			else
			{
				TextColor(1,game.txt[i].x,game.txt[i].y,1,(char*)game.txt[i].txt.c_str(),game.txt[i].color);
			}
		}
	}
	timed_text_1.draw();
	timed_text_2.draw();
	timed_text_3.draw();


	EndText();
}

////////////////////////////
void UI_ResetActiveButton()
////////////////////////////
{
	game.btn_active=-1;
	game.mode_ui=UI_NONE;
}

//////////////////////
void UI_Update()
//////////////////////
{
	int nr=game.n_active_player;

	// Player :: 3 Unique Colored Icons
	game.btn[getBTN("Anzahl Strasse")].img		=	game.player[nr].icon_strasse;
	game.btn[getBTN("Anzahl Siedlung")].img		=	game.player[nr].icon_siedlung;
	game.btn[getBTN("Anzahl Stadt")].img		=	game.player[nr].icon_stadt;

	// Player :: Tausche Avatar Icons
	int player_count=(int)game.player.size();
	stringstream s,t;
	
	for (int p=0; p<player_count; p++)
	{
		//TOKEN :: PlayerName
		s.str(""); s<<"Player"<<p+1;
		
			//Set Player Icons
			game.btn[getBTN(s.str().c_str())].img=game.player[nr].icon;
			game.btn[getBTN(s.str().c_str())].type=nr;
			//Set Player Names
			t.str(""); 
			t << game.player[nr].name << " (" << (game.player[nr].dice_1+game.player[nr].dice_2) << ")";
			game.txt[getTXT(s.str().c_str())].txt=t.str();
			game.txt[getTXT(s.str().c_str())].color=0xFFFFFFFF;

		//TOKEN :: PlayerBorder
		s.str(""); s<<"Border"<<p+1;

			//Set PlayerBorder
			game.btn[getBTN(s.str().c_str())].img=game.player[nr].icon_border;

		nr++;
		if (nr>=player_count) nr=0;
	}


//BUTTONS SICHTBARKEIT
// Anzahl Erz
	nr=game.n_active_player;
	if(game.player[nr].nErz>0)
		game.btn[getBTN("Anzahl Erz")].bVisible=true;
	else
		game.btn[getBTN("Anzahl Erz")].bVisible=false;

// Anzahl Holz
	if(game.player[nr].nHolz>0)
		game.btn[getBTN("Anzahl Holz")].bVisible=true;
	else
		game.btn[getBTN("Anzahl Holz")].bVisible=false;
	
// Anzahl Lehm
	if(game.player[nr].nLehm>0)	
		game.btn[getBTN("Anzahl Lehm")].bVisible=true;
	else
		game.btn[getBTN("Anzahl Lehm")].bVisible=false;

// Anzahl Weizen
	if(game.player[nr].nWeizen>0)	
		game.btn[getBTN("Anzahl Weizen")].bVisible=true;
	else
		game.btn[getBTN("Anzahl Weizen")].bVisible=false;

// Anzahl Wolle
	if(game.player[nr].nWolle>0)
		game.btn[getBTN("Anzahl Wolle")].bVisible=true;
	else
		game.btn[getBTN("Anzahl Wolle")].bVisible=false;

// Anzahl Strasse
	if(game.player[nr].nStrasse>0)
		game.btn[getBTN("Anzahl Strasse")].bVisible=true;
	else
		game.btn[getBTN("Anzahl Strasse")].bVisible=false;

// Anzahl Siedlung
	if(game.player[nr].nSiedlung>0)	
		game.btn[getBTN("Anzahl Siedlung")].bVisible=true;
	else
		game.btn[getBTN("Anzahl Siedlung")].bVisible=false;

// Anzahl Stadt
	if(game.player[nr].nStadt>0)
		game.btn[getBTN("Anzahl Stadt")].bVisible=true;
	else
		game.btn[getBTN("Anzahl Stadt")].bVisible=false;

// Kauf Strasse
	if(game.player[nr].nKaufStrasse>0)
		game.btn[getBTN("Kauf Strasse")].bVisible=true;
	else
		game.btn[getBTN("Kauf Strasse")].bVisible=false;

// Kauf Siedlung
	if(game.player[nr].nKaufSiedlung>0)	
		game.btn[getBTN("Kauf Siedlung")].bVisible=true;
	else
		game.btn[getBTN("Kauf Siedlung")].bVisible=false;

// Kauf Stadt
	if(game.player[nr].nKaufStadt>0)
		game.btn[getBTN("Kauf Stadt")].bVisible=true;
	else
		game.btn[getBTN("Kauf Stadt")].bVisible=false;

// Kauf Karte
	if(game.player[nr].nKaufKarte>0)
		game.btn[getBTN("Kauf Ereigniskarte")].bVisible=true;
	else
		game.btn[getBTN("Kauf Ereigniskarte")].bVisible=false;

// Ritterkarte
	if(game.player[nr].nCardsRitter>0)
		game.btn[getBTN("Ritterkarte")].bVisible=true;
	else
		game.btn[getBTN("Ritterkarte")].bVisible=false;

// Siegpunktkarte
	if(game.player[nr].nCardsSiegpunkte>0)
		game.btn[getBTN("Siegpunktkarte")].bVisible=true;
	else
		game.btn[getBTN("Siegpunktkarte")].bVisible=false;

// Ereigniskarte
	if(game.player[nr].nCardsEreignis>0)
		game.btn[getBTN("Ereigniskarte")].bVisible=true;
	else
		game.btn[getBTN("Ereigniskarte")].bVisible=false;

// Bonus Rittermacht
	if(game.player[nr].bBonusRittermacht==true)
		game.btn[getBTN("Bonus Rittermacht")].bVisible=true;
	else
		game.btn[getBTN("Bonus Rittermacht")].bVisible=false;

// Bonus Handelsstrasse
	if(game.player[nr].bBonusHandelsstrasse==true)	
		game.btn[getBTN("Bonus Handelsstrasse")].bVisible=true;
	else
		game.btn[getBTN("Bonus Handelsstrasse")].bVisible=false;

	//if(game.player[game.n_active_player].bHafen3zu1==true;
	//if(game.player[game.n_active_player].bHafenErz==true;
	//if(game.player[game.n_active_player].bHafenHolz==true;
	//if(game.player[game.n_active_player].bHafenLehm==true;
	//if(game.player[game.n_active_player].bHafenWeizen==true;
	//if(game.player[game.n_active_player].bHafenWolle==true;

	//TEXTE ERSTELLEN
	int index;
	int c=0;
	// Anzahl Erz
	if(game.player[nr].nErz>c)
	{  index=getTXT("Anzahl Erz");
		s.str(""); s<<game.player[nr].nErz;		
		game.txt[index].txt=s.str();
		game.txt[index].visible=true;
	}	else	{	game.txt[getTXT("Anzahl Erz")].visible=false;	}

	// Anzahl Holz
	if(game.player[nr].nHolz>c)
	{  index=getTXT("Anzahl Holz");
		s.str(""); s<<game.player[nr].nHolz;		
		game.txt[index].txt=s.str();
		game.txt[index].visible=true;
	}	else	{	game.txt[getTXT("Anzahl Holz")].visible=false;	}

	// Anzahl Lehm
	if(game.player[nr].nLehm>c)
	{  index=getTXT("Anzahl Lehm");
		s.str(""); s<<game.player[nr].nLehm;		
		game.txt[index].txt=s.str();
		game.txt[index].visible=true;
	}	else	{	game.txt[getTXT("Anzahl Lehm")].visible=false;	}

	// Anzahl Weizen
	if(game.player[nr].nWeizen>c)
	{  index=getTXT("Anzahl Weizen");
		s.str(""); s<<game.player[nr].nWeizen;		
		game.txt[index].txt=s.str();
		game.txt[index].visible=true;
	}	else	{	game.txt[getTXT("Anzahl Weizen")].visible=false;	}

	// Anzahl Wolle
	if(game.player[nr].nWolle>c)
	{  index=getTXT("Anzahl Wolle");
		s.str(""); s<<game.player[nr].nWolle;		
		game.txt[index].txt=s.str();
		game.txt[index].visible=true;
	}	else	{	game.txt[getTXT("Anzahl Wolle")].visible=false;	}

	// Anzahl Strasse
	if(game.player[nr].nStrasse>c)
	{  index=getTXT("Anzahl Strasse");
		s.str(""); s<<game.player[nr].nStrasse;		
		game.txt[index].txt=s.str();
		game.txt[index].visible=true;
	}	else	{	game.txt[getTXT("Anzahl Strasse")].visible=false;	}

	// Anzahl Siedlung
	if(game.player[nr].nSiedlung>c)
	{  index=getTXT("Anzahl Siedlung");
		s.str(""); s<<game.player[nr].nSiedlung;		
		game.txt[index].txt=s.str();
		game.txt[index].visible=true;
	}	else	{	game.txt[getTXT("Anzahl Siedlung")].visible=false;	}

	// Anzahl Stadt
	if(game.player[nr].nStadt>c)
	{  index=getTXT("Anzahl Stadt");
		s.str(""); s<<game.player[nr].nStadt;		
		game.txt[index].txt=s.str();
		game.txt[index].visible=true;
	}	else	{	game.txt[getTXT("Anzahl Stadt")].visible=false;	}

	// Kauf Strasse
	if(game.player[nr].nKaufStrasse>c)
	{  index=getTXT("Kauf Strasse");
		s.str(""); s<<game.player[nr].nKaufStrasse;		
		game.txt[index].txt=s.str();
		game.txt[index].visible=true;
	}	else	{	game.txt[getTXT("Kauf Strasse")].visible=false;	}

	// Kauf Siedlung
	if(game.player[nr].nKaufSiedlung>c)
	{  index=getTXT("Kauf Siedlung");
		s.str(""); s<<game.player[nr].nKaufSiedlung;		
		game.txt[index].txt=s.str();
		game.txt[index].visible=true;
	}	else	{	game.txt[getTXT("Kauf Siedlung")].visible=false;	}

	// Kauf Stadt
	if(game.player[nr].nKaufStadt>c)
	{  index=getTXT("Kauf Stadt");
		s.str(""); s<<game.player[nr].nKaufStadt;		
		game.txt[index].txt=s.str();
		game.txt[index].visible=true;
	}	else	{	game.txt[getTXT("Kauf Stadt")].visible=false;	}

	// Kauf Ereigniskarte
	if(game.player[nr].nKaufKarte>c)
	{  index=getTXT("Kauf Ereigniskarte");
		s.str(""); s<<game.player[nr].nKaufKarte;		
		game.txt[index].txt=s.str();
		game.txt[index].visible=true;
	}	else	{	game.txt[getTXT("Kauf Ereigniskarte")].visible=false;	}

	// Ritterkarte
	if(game.player[nr].nCardsRitter>c)
	{  index=getTXT("Ritterkarte");
		s.str(""); s<<game.player[nr].nCardsRitter;		
		game.txt[index].txt=s.str();
		game.txt[index].visible=true;
	}	else	{	game.txt[getTXT("Ritterkarte")].visible=false;	}

	// Siegpunktkarte
	if(game.player[nr].nCardsSiegpunkte>c)
	{  index=getTXT("Siegpunktkarte");
		s.str(""); s<<game.player[nr].nCardsSiegpunkte;		
		game.txt[index].txt=s.str();
		game.txt[index].visible=true;
	}	else	{	game.txt[getTXT("Siegpunktkarte")].visible=false;	}

	// Ereigniskarte
	if(game.player[nr].nCardsEreignis>c)
	{  index=getTXT("Ereigniskarte");
		s.str(""); s<<game.player[nr].nCardsEreignis;		
		game.txt[index].txt=s.str();
		game.txt[index].visible=true;
	}	else	{	game.txt[getTXT("Ereigniskarte")].visible=false;	}

}
////////////////////////////////////////////
void UI_Show_All(bool yesno)
////////////////////////////////////////////
{
	int c,count=(int)game.btn.size();

	for (c=0; c<count; c++)
	{
		if (game.btn[c].bVisible==false) game.btn[c].bVisible=yesno;
	}
	count=(int)game.txt.size();
	for (c=0; c<count; c++)
	{
		if (game.txt[c].visible==false) game.txt[c].visible=yesno;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
void UI_Show_Todo(bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	game.btn[getBTN("Todo Dice")].bVisible=yesno;
	game.btn[getBTN("Todo Play Card")].bVisible=yesno;
	game.btn[getBTN("Todo Trade Card")].bVisible=yesno;
	game.btn[getBTN("Todo Bank")].bVisible=yesno;
	game.btn[getBTN("Todo End Turn")].bVisible=yesno;
	game.btn[getBTN("Todo Undo")].bVisible=yesno;
}
////////////////////////////////////////////////////////////////////////////////////////////
void UI_Show_TodoDice(bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	game.btn[getBTN("Todo Dice")].bVisible=yesno;
}
////////////////////////////////////////////////////////////////////////////////////////////
void UI_Show_TodoPlay(bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	game.btn[getBTN("Todo Play Card")].bVisible=yesno;
}
////////////////////////////////////////////////////////////////////////////////////////////
void UI_Show_TodoTrade(bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	game.btn[getBTN("Todo Trade Card")].bVisible=yesno;
}
////////////////////////////////////////////////////////////////////////////////////////////
void UI_Show_TodoBank(bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	game.btn[getBTN("Todo Bank")].bVisible=yesno;
}
////////////////////////////////////////////////////////////////////////////////////////////
void UI_Show_TodoEnd(bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	game.btn[getBTN("Todo End Turn")].bVisible=yesno;
}
////////////////////////////////////////////////////////////////////////////////////////////
void UI_Show_TodoUndo(bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	game.btn[getBTN("Todo Undo")].bVisible=yesno;
}
////////////////////////////////////////////
void UI_Show_Bauliste(bool yesno)
////////////////////////////////////////////
{
	game.btn[getBTN("Bauliste")].bVisible=yesno;
}
////////////////////////////////////////////
int getBTN_under_mouse()
////////////////////////////////////////////
{
	int count=(int)game.btn.size();
	int index;
	int m1,m2,m3,m4;
	for (index=0; index<count; index++)
	{
		if (game.btn[index].bVisible==true)
		{
			m1=game.btn[index].x;
			m2=game.btn[index].y;
			m3=m1+game.btn[index].dx;
			m4=m2+game.btn[index].dy;
			if (MouseOver(m1,m2,m3,m4)==true)
			{
				return index;
			}
		}
	}
	return -1;
}
////////////////////////////////////////////
int  getBTN(const char* name)
////////////////////////////////////////////
{
	int count=(int)game.btn.size();
	int index=-1;
	for (index=0; index<count; index++)
	{
		if (game.btn[index].name.compare(name)==0) return index;
	}
	stringstream s; s << "Name :: "<<name<<" :: existiert nicht im Array btn.";
	MessageBoxA(NULL,s.str().c_str(),"Fehler",0);
	exit(1);
}
////////////////////////////////////////////
int  getTXT(const char* name)
////////////////////////////////////////////
{
	int count=(int)game.txt.size();
	int index=-1;
	for (index=0; index<count; index++)
	{
		if (game.txt[index].name.compare(name)==0) return index;
	}
	stringstream s; s << "Name :: "<<name<<" :: existiert nicht im Array txt.";
	MessageBoxA(NULL,s.str().c_str(),"Fehler",0);
	exit(1);
}
////////////////////////////////////////////
void setBTN_visible(const char* name)
////////////////////////////////////////////
{
	int count=(int)game.btn.size();
	int index;
	for (index=0; index<count; index++)
	{
		if (strcmp(name,game.btn[index].name.c_str())==0)
		{
			bool visible=game.btn[index].bVisible;
			//Bauliste		
			if (strcmp(name,"Bauliste")==0)
			{
				if (visible==true)
					game.btn[index].bVisible=false;
				else
					game.btn[index].bVisible=true;
			}
			return;
		}
	}
	MessageBoxA(NULL,"Name existiert nicht im Array btn.","Fehler",0);
}
////////////////////////////////////////////
void  drawName(int index)
////////////////////////////////////////////
{
	int dx=GetTextWidth(1,(char*)game.btn[index].name.c_str())+2;
	int dy=GetTextHeight(1,(char*)game.btn[index].name.c_str());
	int x=mouse.x+20;
	int y=mouse.y+20;
	if (x<0) x=0;
	if (y<0) y=0;
	if (x+dx>scr.x) x=scr.x-dx;
	if (y+dy>scr.y) y=scr.y-dy;
	DWORD color=dbRGB(255,255,0);
	dbBox(x,y,x+dx,y+dy,color,color,color,color);
	StartText();
	TextColor(1,x+1,y,0,(char*)game.btn[index].name.c_str(),RGBA(0,0,0,255));
	EndText();
}
////////////////////////////////////////////
void  drawInfoLog(void)
////////////////////////////////////////////
{
		int font=5;
		//! info-log-array-size
		int info_count=(int)game.info.size();

		//! get maximum width
		int i,use=0,max=0;
		if (info_count<20)
		{
			for (i=0; i<info_count; i++)
			{
				use=GetTextWidth(font,(char*)game.info[i].txt.c_str());
				if (use>max) max=use;
			}
		}
		else
		{
			for (i=info_count-20; i<info_count; i++)
			{
				use=GetTextWidth(font,(char*)game.info[i].txt.c_str());
				if (use>max) max=use;
			}
		}

		//! draw box
		int x=scr.x-max-10;
		int y=100;
		int d=15;
		DWORD color=0x33FFFFFF;
		dbBox(x,y,scr.x,y+d*info_count,color,color,color,color);

		//! draw info-log-array
		if (info_count>0) 
		{
			StartText();
			if (info_count<20)
			{
				for (i=0; i<info_count; i++)
					TextColor(font,scr.x-5,y+d*i,2,(char*)game.info[i].txt.c_str(),game.info[i].color);
			}
			else
			{
				for (i=info_count-20; i<info_count; i++)
					TextColor(font,scr.x-5,y+d*(i-info_count+20),2,(char*)game.info[i].txt.c_str(),game.info[i].color);
			}
			EndText();
		}
}
////////////////////////////////////////////////////////////////////////////////////////////
void  drawText(int x, int y, int iFont, int iAlign, DWORD color, DWORD bgcolor, char* pTXT)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int dx=GetTextWidth(1,pTXT)+2;
	int dy=GetTextHeight(1,pTXT);
	if (x<0) x=0;
	if (y<0) y=0;
	if (x+dx>scr.x) x=scr.x-dx;
	if (y+dy>scr.y) y=scr.y-dy;
	dbBox(x,y,x+dx,y+dy,bgcolor,bgcolor,bgcolor,bgcolor);
	StartText();
	TextColor(iFont,x+1,y,iAlign,pTXT,color);
	EndText();
}
////////////////////////////////////////////////////////////////////////////////////////////
void drawRect(int x1, int y1, int x2, int y2, int size)
////////////////////////////////////////////////////////////////////////////////////////////
{
	dbInk(game.player[game.n_active_player].color,0);
	dbLine(x1,y1,x2-1,y1);
	dbLine(x1,y1,x1,y2-1);
	dbLine(x1,y2-1,x2-1,y2-1);
	dbLine(x2-1,y1,x2-1,y2-1);
	dbInk(dbRGB(255,255,255),0);
}
////////////////////////////////////////////////////////////////////////////////////////////
void drawInfo_Player(int index, int x, int y, int iFont, int iAlign, DWORD color, DWORD bgcolor)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if ((index<0) || (index>=count)) return;

	std::vector<std::string> v;
	std::vector<int> dx;
	int dy=GetTextHeight(iFont,"Hi");
	int i,max_x=0,max_y=0,size;
	std::stringstream s;

	for (i=0; i<31; i++)
	{
		s.str("");
		if (i==0 ) s << "Player Nr." << index+1;
		if (i==1 ) s << "Player Name = " << game.player[index].name;
		if (i==2 ) s << "Player Type = " << game.player[index].type;
		if (i==3 ) s << "Player Disabled = " << game.player[index].disabled;
		if (i==4 ) s << "Color = " << game.player[index].color;
		if (i==5 ) s << "Dice = " << game.player[index].dice_1 + game.player[index].dice_2;
		if (i==6 ) s << "nSiegpunkte = " << game.player[index].nSiegpunkte;
		if (i==7 ) s << "nKaufStrasse = " << game.player[index].nKaufStrasse;
		if (i==8 ) s << "nKaufSiedlung = " << game.player[index].nKaufSiedlung;
		if (i==9 ) s << "nKaufStadt = " << game.player[index].nKaufStadt;
		if (i==10) s << "nKaufKarte = " << game.player[index].nKaufKarte;
		if (i==11) s << "nCards = " << game.player[index].nCards;
		if (i==12) s << "nErz = " << game.player[index].nErz;
		if (i==13) s << "nHolz = " << game.player[index].nHolz;
		if (i==14) s << "nLehm = " << game.player[index].nLehm;
		if (i==15) s << "nWeizen = " << game.player[index].nWeizen;
		if (i==16) s << "nWolle = " << game.player[index].nWolle;
		if (i==17) s << "nStrasse = " << game.player[index].nStrasse;
		if (i==18) s << "nSiedlung = " << game.player[index].nSiedlung;
		if (i==19) s << "nStadt = " << game.player[index].nStadt;
		if (i==20) s << "nCardsRitter = " << game.player[index].nCardsRitter;
		if (i==21) s << "nCardsSiegpunkte = " << game.player[index].nCardsSiegpunkte;
		if (i==22) s << "nCardsEreignis = " << game.player[index].nCardsEreignis;
		if (i==23) s << "bHafen3zu1 = " << game.player[index].bHafen3zu1;
		if (i==24) s << "bHafenErz = " << game.player[index].bHafenErz;
		if (i==25) s << "bHafenHolz = " << game.player[index].bHafenHolz;
		if (i==26) s << "bHafenLehm = " << game.player[index].bHafenLehm;
		if (i==27) s << "bHafenWeizen = " << game.player[index].bHafenWeizen;
		if (i==28) s << "bHafenWolle = " << game.player[index].bHafenWolle;
		if (i==29) s << "bBonusRittermacht = " << game.player[index].bBonusRittermacht;
		if (i==30) s << "bBonusHandelsstrasse = " << game.player[index].bBonusHandelsstrasse;

		v.push_back(s.str());	
		dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
	}

	size=(int)v.size();
	for (i=0; i<size; i++)
	{
		if (dx[i]>max_x) max_x=dx[i];
	}
	max_y = size*dy;

	if (x<0) x=0;
	if (y<0) y=0;
	if (x+max_x>scr.x) x=scr.x-max_x;
	if (y+max_y>scr.y) y=scr.y-max_y;
	dbBox(x,y,x+max_x,y+max_y,bgcolor,bgcolor,bgcolor,bgcolor);
	StartText();
	for (i=0; i<size; i++)
	{
		TextColor(iFont,x+1,y+i*dy,iAlign,(char*)v[i].c_str(),color);
	}
	EndText();
}

////////////////////////////////////////////////////////////////////////////////////////////
void drawInfo_Tile(int index, int x, int y, int iFont, int iAlign, DWORD color, DWORD bgcolor)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int size=(int)game.tiles.size();
	if ((index<0) || (index>=size)) return;

	std::vector<std::string> v;
	std::vector<int> dx;
	std::stringstream s;
	int dy=GetTextHeight(iFont,"Hi");
	int i,max_x=0,max_y=0;

	for (i=0; i<9; i++)
	{
		s.str("");
		if (i==0 ) s << "Tile Nr."			 << index;
		if (i==1 ) s << "Tile Name = "	 << game.tiles[index].name;
		if (i==2 ) s << "Tile Type = "	 << game.tiles[index].type;
		if (i==3 ) s << "Tile Obj/Tex = " << game.tiles[index].obj<<" / "<<game.tiles[index].tex;
		if (i==4 ) s << "Tile Raeuber = " << game.tiles[index].raeuber;
		if (i==5 ) s << "Chip Wert = "	 << game.tiles[index].chip_wert;
		if (i==6 ) s << "Chip Obj/Tex = " << game.tiles[index].chip_obj << " / " << game.tiles[index].chip_tex;
		if (i==7 ) s << "Tile Winkel = "  << game.tiles[index].winkel;
		if (i==8 ) s << "Tile Pos = ("	 << game.tiles[index].x<<", "<<game.tiles[index].y<<", "<<game.tiles[index].z<<")";

		v.push_back(s.str());	
		dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
	}
	// WAY_W
	size=(int)game.tiles[index].way_W.size();
	s.str(""); s << "Anzahl way_W = " << size;
	v.push_back(s.str());	
	dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
	if (size>0)
	{
		for (i=0; i<size; i++)
		{
			s.str(""); s << "Nr." << i << " Index = " << game.tiles[index].way_W[i].obj << ", Pos(";
			s << game.tiles[index].way_W[i].x<<", " << game.tiles[index].way_W[i].y <<", "<< game.tiles[index].way_W[i].z << ")";
			v.push_back(s.str());	
			dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
		}
	}
	// WAY_S
	size=(int)game.tiles[index].way_S.size();
	s.str(""); s << "Anzahl way_S = " << size;
	v.push_back(s.str());	
	dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
	if (size>0)
	{
		for (i=0; i<size; i++)
		{
			s.str(""); s << "Nr." << i << " Obj = " << game.tiles[index].way_S[i].obj<< ", Pos(";
			//s << ", Winkel = " << game.tiles[index].way_S[i].winkel ;
			s << game.tiles[index].way_S[i].x<<", " << game.tiles[index].way_S[i].y <<", "<< game.tiles[index].way_S[i].z << ")";
			v.push_back(s.str());	
			dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
		}
	}
	// Find biggest dx and calculate dy
	size=(int)v.size();
	for (i=0; i<size; i++)
	{
		if (dx[i]>max_x) max_x=dx[i];
	}
	max_y = size*dy;

	// Draw Text
	if (x<0) x=0;
	if (y<0) y=0;
	if (x+max_x>scr.x) x=scr.x-max_x;
	if (y+max_y>scr.y) y=scr.y-max_y;
	dbBox(x,y,x+max_x,y+max_y,bgcolor,bgcolor,bgcolor,bgcolor);
	StartText();
	for (i=0; i<size; i++)
	{
		TextColor(iFont,x+1,y+i*dy,iAlign,(char*)v[i].c_str(),color);
	}
	EndText();
}
////////////////////////////////////////////////////////////////////////////////////////////
void drawInfo_Way_S(int index, int x, int y, int iFont, int iAlign, DWORD color, DWORD bgcolor)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int size=(int)game.way_S.size();
	if ((index<0) || (index>=size)) return;

	std::vector<std::string> v;
	std::vector<int> dx;
	std::stringstream s;

	int dy=GetTextHeight(iFont,"Hi");
	int i,max_x=0,max_y=0;

	for (i=0; i<6; i++)
	{
		s.str("");
		if (i==0 ) s << "way_S :: Nr."		<< index;
		if (i==1 ) s << "way_S :: bebaut = "<< game.way_S[index].bebaut;
		if (i==2 ) s << "way_S :: player = "<< game.way_S[index].player;
		if (i==3 ) s << "way_S :: Obj = "	<< game.way_S[index].obj;
		if (i==4 ) s << "way_S :: Winkel = "<< game.way_S[index].winkel;
		if (i==5 ) s << "way_S :: Pos = ("	<< game.way_S[index].x<<", "<<game.way_S[index].y<<", "<<game.way_S[index].z<<")";

		v.push_back(s.str());	
		dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
	}
	// NEXT_W
	size=(int)game.way_S[index].next_W.size();
	s.str(""); s << "Anzahl next_W = " << size;
	v.push_back(s.str());	
	dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
	if (size>0)
	{
		for (i=0; i<size; i++)
		{
			s.str(""); s << "Nr." << i << " ,Index = " << game.way_S[index].next_W[i];
			v.push_back(s.str());	
			dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
		}
	}

	// NEXT_T
	size=(int)game.way_S[index].next_T.size();
	s.str(""); s << "Anzahl next_T = " << size;
	v.push_back(s.str());	
	dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
	if (size>0)
	{
		for (i=0; i<size; i++)
		{
			s.str(""); s << "Nr." << i << " ,Index = " << game.way_S[index].next_T[i];
			v.push_back(s.str());	
			dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
		}
	}

	// Find biggest dx and calculate dy
	size=(int)v.size();
	for (i=0; i<size; i++)
	{
		if (dx[i]>max_x) max_x=dx[i];
	}
	max_y = size*dy;

	// Draw Text
	if (x<0) x=0;
	if (y<0) y=0;
	if (x+max_x>scr.x) x=scr.x-max_x;
	if (y+max_y>scr.y) y=scr.y-max_y;
	dbBox(x,y,x+max_x,y+max_y,bgcolor,bgcolor,bgcolor,bgcolor);
	StartText();
	for (i=0; i<size; i++)
	{
		TextColor(iFont,x+1,y+i*dy,iAlign,(char*)v[i].c_str(),color);
	}
	EndText();

}
////////////////////////////////////////////////////////////////////////////////////////////
void drawInfo_Way_W(int index, int x, int y, int iFont, int iAlign, DWORD color, DWORD bgcolor)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int size=(int)game.way_S.size();
	if ((index<0) || (index>=size)) return;

	std::vector<std::string> v;
	std::vector<int> dx;
	std::stringstream s;

	int dy=GetTextHeight(iFont,"Hi");
	int i,max_x=0,max_y=0;

	for (i=0; i<6; i++)
	{
		s.str("");
		if (i==0 ) s << "way_W :: Nr."		<< index;
		if (i==1 ) s << "way_W :: disabled = "<< game.way_W[index].disabled;
		if (i==2 ) s << "way_W :: bebaut = "<< game.way_W[index].bebaut;
		if (i==3 ) s << "way_W :: player = "<< game.way_W[index].player;
		if (i==4 ) s << "way_W :: Obj = "	<< game.way_W[index].obj;
		if (i==5 ) s << "way_W :: Pos = ("	<< game.way_W[index].x<<", "<<game.way_W[index].y<<", "<<game.way_W[index].z<<")";

		v.push_back(s.str());	
		dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
	}
	// NEXT_W
	size=(int)game.way_W[index].next_W.size();
	s.str(""); s << "Anzahl next_W = " << size;
	v.push_back(s.str());	
	dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
	if (size>0)
	{
		for (i=0; i<size; i++)
		{
			s.str(""); s << "Nr." << i << " ,Index = " << game.way_W[index].next_W[i];
			v.push_back(s.str());	
			dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
		}
	}

	// NEXT_S
	size=(int)game.way_W[index].next_S.size();
	s.str(""); s << "Anzahl next_S = " << size;
	v.push_back(s.str());	
	dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
	if (size>0)
	{
		for (i=0; i<size; i++)
		{
			s.str(""); s << "Nr." << i << " ,Index = " << game.way_W[index].next_S[i];
			v.push_back(s.str());	
			dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
		}
	}

	// NEXT_T
	size=(int)game.way_W[index].next_T.size();
	s.str(""); s << "Anzahl next_T = " << size;
	v.push_back(s.str());	
	dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
	if (size>0)
	{
		for (i=0; i<size; i++)
		{
			s.str(""); s << "Nr." << i << " ,Index = " << game.way_W[index].next_T[i];
			v.push_back(s.str());	
			dx.push_back(GetTextWidth(1,(char*)s.str().c_str())+2);
		}
	}

	// Find biggest dx and calculate dy
	size=(int)v.size();
	for (i=0; i<size; i++)
	{
		if (dx[i]>max_x) max_x=dx[i];
	}
	max_y = size*dy;

	// Draw Text
	if (x<0) x=0;
	if (y<0) y=0;
	if (x+max_x>scr.x) x=scr.x-max_x;
	if (y+max_y>scr.y) y=scr.y-max_y;
	dbBox(x,y,x+max_x,y+max_y,bgcolor,bgcolor,bgcolor,bgcolor);
	StartText();
	for (i=0; i<size; i++)
	{
		TextColor(iFont,x+1,y+i*dy,iAlign,(char*)v[i].c_str(),color);
	}
	EndText();

}

//void UI_ShowIconTodoDice(bool yesno);
//void UI_ShowIconTodoPlayCard(bool yesno);
//void UI_ShowIconTodoTradeCard(bool yesno);
//void UI_ShowIconTodoBank(bool yesno);
//void UI_ShowIconTodoEndTurn(bool yesno);
/*
////////////////////////////////////////////////////////////////////////////////////////////
void UI_ShowTodoDice(bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int i,count=(int)game.btn.size();
	for (i=0; i<count; i++)
	{
		if(game.btn[i].name.compare("Todo Dice")==0)
		{	game.btn[i].bVisible=yesno;
			return;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
void UI_ShowTodoPlayCard(bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int i,count=(int)game.btn.size();
	for (i=0; i<count; i++)
	{
		if(game.btn[i].name.compare("Todo Play Card")==0)
		{	game.btn[i].bVisible=yesno;
			return;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
void UI_ShowTodoTradeCard(bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int i,count=(int)game.btn.size();
	for (i=0; i<count; i++)
	{
		if(game.btn[i].name.compare("Todo Trade Card")==0)
		{	game.btn[i].bVisible=yesno;
			return;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
void UI_ShowTodoBank(bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int i,count=(int)game.btn.size();
	for (i=0; i<count; i++)
	{
		if(game.btn[i].name.compare("Todo Bank")==0)
		{	game.btn[i].bVisible=yesno;
			return;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////
void UI_ShowTodoEndTurn(bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int i,count=(int)game.btn.size();
	for (i=0; i<count; i++)
	{
		if(game.btn[i].name.compare("Todo End Turn")==0)
		{	game.btn[i].bVisible=yesno;
			return;
		}
	}
}
*/

/*
//////////////////////
void UI_Reset()
//////////////////////
{
	//locals
	bool visible=false;
	int i,count;

	//HIDE BUTTONS
	count=(int)game.btn.size();
	for (i=0; i<count; i++)
	{
		visible=false;
		if (game.btn[i].name.compare(0,6,"Player")==0) visible=true;
		game.btn[i].bVisible=visible;
	}
	//HIDE TEXTE
	count=(int)game.txt.size();
	for (i=0; i<count; i++)
	{
		visible=false;
		if (game.txt[i].name.compare(0,6,"Player")==0) visible=true;
		game.txt[i].visible=visible;
	}

	//SHOW DICE1 && DICE2 and PLAYERICONS
	game.btn[getBTN("Dice1")].bVisible=true;
	game.btn[getBTN("Dice2")].bVisible=true;
	

}
*/