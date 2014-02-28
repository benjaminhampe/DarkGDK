// _player.cpp

#include "_player.h"

#include "stdafx.h"
#include "main.h"

#include "_ui_control.h"
#include "_game_types.h"

#include "thc_memblock.h"
#include "thc_image.h"
#include "thc_delete.h"

using namespace thc;


////////////////////////////////////////////
void PlayerCreate(string name, DWORD color, string icon, int type)
////////////////////////////////////////////
{
	PLAYER player;
	player.disabled=false;
	player.name=name;
	player.color=color;
	player.type=type;
	player.dice_1=0;
	player.dice_2=0;

	int mem,img;

	// PLAYER - ICON
	mem=MemblockLoad((char*)icon.c_str(),1);
	int memX=MemblockX(mem);
	int memY=MemblockY(mem);
	if((memX!=64) || (memY!=64))
	{
		int use=MemblockScale(mem,64,64);
		MemblockDelete(mem);
		mem=use;
	}
	img=ImageFromMemblock(mem);
	MemblockDelete(mem);
	player.icon=img;

	//Textur Holz
	mem=MemblockMultiplyWithColor(game.mem_holz,color,0.75f);
	img=ImageFromMemblock(mem);
	MemblockDelete(mem);
	player.tex_holz=ImageWorkAroundForMipmapUse(img);
	ImageDelete(img);

	// ICON STRASSE
	mem=MemblockSetColorKey(game.mem_icon_strasse,dbRGB(255,255,0));
	img=MemblockReplaceColor(mem,dbRGB(255,0,255),color);
	player.icon_strasse=ImageFromMemblock(img);
	MemblockDelete(mem);
	MemblockDelete(img);

	// ICON SIEDLUNG
	mem=MemblockSetColorKey(game.mem_icon_siedlung,dbRGB(255,255,0));
	img=MemblockReplaceColor(mem,dbRGB(255,0,255),color);
	player.icon_siedlung=ImageFromMemblock(img);
	MemblockDelete(mem);
	MemblockDelete(img);

	// ICON STADT
	mem=MemblockSetColorKey(game.mem_icon_stadt,dbRGB(255,255,0));
	img=MemblockReplaceColor(mem,dbRGB(255,0,255),color);
	player.icon_stadt=ImageFromMemblock(img);
	MemblockDelete(mem);
	MemblockDelete(img);

	// ICON BORDER
	img=MemblockFromColorWithBorder(64,64,0xFF112233,3,color);
	mem=MemblockSetColorKey(img,0xFF112233);
	player.icon_border=ImageFromMemblock(mem);
	MemblockDelete(img);
	MemblockDelete(mem);

	player.nSiegpunkte=0;
	player.nCards=0;
	player.nErz=0;
	player.nLehm=0;
	player.nHolz=0;
	player.nWeizen=0;
	player.nWolle=0;
	player.nStrasse=0;
	player.nSiedlung=0;
	player.nStadt=0;
	player.nKaufKarte=0;
	player.nKaufSiedlung=0;
	player.nKaufStadt=0;
	player.nKaufStrasse=0;
	player.nCardsRitter=0;
	player.nCardsSiegpunkte=0;
	player.nCardsEreignis=0;
	player.bBonusRittermacht=false;
	player.bBonusHandelsstrasse=false;
	player.bHafen3zu1=false;
	player.bHafenErz=false;
	player.bHafenHolz=false;
	player.bHafenLehm=false;
	player.bHafenWeizen=false;
	player.bHafenWolle=false;
	game.player.push_back(player);

	//PLAYER ICON//////////////////////////////////////////////
	int nr=(int)game.player.size();
	BUTTON btn;
	stringstream s;
	s<<"Player"<<nr;
	btn.name=s.str();
	btn.info=name;
	btn.bInfo=true;
	btn.bVisible=true;
	btn.bActive=false;	
	btn.type=nr-1;
	btn.dx=64;
	btn.dy=64;
	btn.x=5;
	btn.img=player.icon;																		
	if (nr==1)
	{
		btn.y=scr.y-190;
	}
	else
	{
		btn.y=5+(nr-2)*(btn.dy+20);
	}
	
	game.btn.push_back(btn);

	//PLAYER NAME + DICE////////////////////////////////////////////
	STATIC_TEXT txt;
	txt.color=color;
	txt.name=btn.name;
	s.str(""); s<<btn.info;
	txt.txt=s.str();
	txt.visible=true;
	txt.left=true;
	txt.x=btn.x;
	txt.y=btn.y+btn.dy;
	game.txt.push_back(txt);

	//PLAYER ICON BORDER//////////////////////////////////////////////	
	s.str(""); s<<"Border"<<nr;
	btn.name=s.str();
	btn.img=player.icon_border;																		
	game.btn.push_back(btn);
	
}
////////////////////////////////////////////
void SetFirstPlayer(int nr)
////////////////////////////////////////////
{
	int count=(int)game.player.size();		// Anzahl Player
	if (nr>=count) return;
	if (nr<0)	nr=game.n_active_player;
	game.n_first_player=nr;
}
////////////////////////////////////////////
void SetActivePlayer(int nr)
////////////////////////////////////////////
{
	int count=(int)game.player.size();		// Anzahl Player
	if (nr<0)	nr=nr+count;
	if (nr>=count) nr=nr-count;
	game.n_active_player=nr;
	//UI_Update();
}

////////////////////////////////////////////
void Next_Player_Clockwise( void )
////////////////////////////////////////////
{
	// PLAYER COUNT
	int player_count=(int)game.player.size();

	// inc++ active player number
	game.n_active_player++;
	if(game.n_active_player>=player_count)
	{	game.n_active_player-=player_count;
	}
	
	//if active player = first player -> Runde vollständig -> SWITCH MODE TO END_ROUND
	if (game.n_active_player==game.n_first_player)
	{
		game.mode_todo=TODO_END_ROUND;
		return;
	}
	SetActivePlayer(game.n_active_player);
}

////////////////////////////////////////////
void Next_Player_CounterClockwise( void )
////////////////////////////////////////////
{
	// PLAYER COUNT
	int player_count=(int)game.player.size();

	// dec-- active player number
	game.n_active_player--;
	if(game.n_active_player<0)
	{	game.n_active_player+=player_count;
	}
	
	//if active player = first player -> Runde vollständig -> SWITCH MODE TO END_ROUND
	if (game.n_active_player==game.n_first_player)
	{
		game.mode_todo=TODO_END_ROUND;
		return;
	}
	SetActivePlayer(game.n_active_player);
}

////////////////////////////////////////////////////////////////////////////////////////////
void Player_SetKaufStrasse(int player, int c)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();

	if (player==-2)
	{
		for (player=0; player<count; player++)
		{
			game.player[player].nKaufStrasse=c;	
		}
		return;
	}

	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].nKaufStrasse=c;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_SetKaufSiedlung(int player, int c)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();

	if (player==-2)
	{
		for (player=0; player<count; player++)
		{
			game.player[player].nKaufSiedlung=c;	
		}
		return;
	}

	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].nKaufSiedlung=c;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_SetKaufStadt(int player, int c)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if (player==-2)
	{
		for (player=0; player<count; player++)
		{
			game.player[player].nKaufStadt=c;	
		}
		return;
	}
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].nKaufStadt=c;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_SetKaufKarte(int player, int c)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();

	if (player==-2)
	{
		for (player=0; player<count; player++)
		{
			game.player[player].nKaufKarte=c;	
		}
		return;
	}

	if((player<0) || (player>count))
		player=game.n_active_player;
	game.player[player].nKaufKarte=c;

}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_AddErz(int player, int c)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].nErz += c;
	if (game.player[player].nErz<0) game.player[player].nErz=0;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_AddHolz(int player, int c)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].nHolz += c;
	if (game.player[player].nHolz<0) game.player[player].nHolz=0;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_AddLehm(int player, int c)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].nLehm += c;
	if (game.player[player].nLehm<0) game.player[player].nLehm=0;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_AddWeizen(int player, int c)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].nWeizen += c;
	if (game.player[player].nWeizen<0) game.player[player].nWeizen=0;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_AddWolle(int player, int c)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].nWolle += c;
	if (game.player[player].nWolle<0) game.player[player].nWolle=0;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_AddStrasse(int player, int c)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].nStrasse += c;
	if (game.player[player].nStrasse<0) game.player[player].nStrasse=0;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_AddSiedlung(int player, int c)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].nSiedlung += c;
	if (game.player[player].nSiedlung<0) game.player[player].nSiedlung=0;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_AddStadt(int player, int c)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].nStadt += c;
	if (game.player[player].nStadt<0) game.player[player].nStadt=0;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_AddRitterkarte(int player, int c)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].nCardsRitter += c;
	if (game.player[player].nCardsRitter<0) game.player[player].nCardsRitter=0;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_AddSiegpunktkarte(int player, int c)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].nCardsSiegpunkte += c;
	if (game.player[player].nCardsSiegpunkte<0) game.player[player].nCardsSiegpunkte=0;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_AddEreigniskarte(int player, int c)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].nCardsEreignis += c;
	if (game.player[player].nCardsEreignis<0) game.player[player].nCardsEreignis=0;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_SetBonusRittermacht(int player, bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].bBonusRittermacht = yesno;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_SetBonusHandelsmacht(int player, bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].bBonusHandelsstrasse=yesno;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_SetHafen3zu1(int player, bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].bHafen3zu1=yesno;

}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_SetHafenErz(int player, bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].bHafenErz=yesno;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_SetHafenHolz(int player, bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].bHafenHolz=yesno;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_SetHafenLehm(int player, bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].bHafenLehm=yesno;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_SetHafenWeizen(int player, bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].bHafenWeizen=yesno;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Player_SetHafenWolle(int player, bool yesno)
////////////////////////////////////////////////////////////////////////////////////////////
{
	int count=(int)game.player.size();
	if((player<0) || (player>count))	player=game.n_active_player;
	game.player[player].bHafenWolle=yesno;
}
////////////////////////////////////////////////////////////////////////////////////////////
bool IsRoundEnded(void)
////////////////////////////////////////////////////////////////////////////////////////////
{
	if (game.mode_todo==TODO_END_ROUND) return true;
	return false;
}

