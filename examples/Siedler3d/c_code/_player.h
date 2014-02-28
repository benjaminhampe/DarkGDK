//_player.h

#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__

#include "stdafx.h"

void PlayerCreate(string name, DWORD color, string icon, int type);
void SetFirstPlayer(int nr);
void SetActivePlayer(int nr);
void Next_Player_Clockwise( void );
void Next_Player_CounterClockwise( void );
void Player_SetKaufStrasse(int player, int c);
void Player_SetKaufSiedlung(int player, int c);
void Player_SetKaufStadt(int player, int c);
void Player_SetKaufKarte(int player, int c);
void Player_AddErz(int player, int c);
void Player_AddHolz(int player, int c);
void Player_AddLehm(int player, int c);
void Player_AddWeizen(int player, int c);
void Player_AddWolle(int player, int c);
void Player_AddStrasse(int player, int c);
void Player_AddSiedlung(int player, int c);
void Player_AddStadt(int player, int c);
void Player_AddRitterkarte(int player, int c);
void Player_AddSiegpunktkarte(int player, int c);
void Player_AddEreigniskarte(int player, int c);
void Player_SetBonusRittermacht(int player, bool yesno);
void Player_SetBonusHandelsmacht(int player, bool yesno);
void Player_SetHafen3zu1(int player, bool yesno);
void Player_SetHafenErz(int player, bool yesno);
void Player_SetHafenHolz(int player, bool yesno);
void Player_SetHafenLehm(int player, bool yesno);
void Player_SetHafenWeizen(int player, bool yesno);
void Player_SetHafenWolle(int player, bool yesno);
bool IsRoundEnded(void);
#endif