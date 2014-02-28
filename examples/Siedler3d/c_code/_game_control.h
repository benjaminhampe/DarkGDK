// _game_init.cpp

#ifndef __GAME_INIT_H_INCLUDED__
#define __GAME_INIT_H_INCLUDED__

#include "stdafx.h"

void Game_Init( void );
void Game_Delete( void );

void LoadTextures_For_Tiles( void );
void LoadTiles( void );
void LoadTextures_For_Chips( void );
void LoadChips( void );
void Generate_ZufallsArray(int anzahl,int *iarray);
void Generate_Way_W( void );
void Generate_Way_S( void );
void Generate_Missing_Information_1();
void Generate_Missing_Information_2();
void Generate_Missing_Information_3();
void Generate_Missing_Information_4();
void Generate_Missing_Information_5();

int FIND_WAY_W_that_equals_TILE_W(int tile_nr, int tile_w);
int FIND_WAY_S_that_equals_TILE_S(int tile_nr, int tile_w);

void Show_Waypoint_S(bool yesno);
void Show_Waypoint_W(bool yesno);
void AddInfo(int nr,char* pTXT);
void AddInfo(char* pTXT, DWORD color);

int getWay_S(int obj);
int getWay_W(int obj);
int getTile(int obj);
int getChip(int obj);

void Game_Control( void );

void PlaceDelete( void );
bool PlaceStrasse( void );
bool PlaceSiedlung( void );
bool PlaceStadt( void );

void Runde_1_Control_Dice( void );
void Runde_2_Control_Place( void );

void Runde_3_Control_Loop( void );
void Runde_3_Dice( void );
void Runde_3_PlaceRaeuber( void );
void Runde_3_SteelCard( void );
void Runde_3_LooseHalfCards( void );
void Runde_3_PlayCard( void );
void Runde_3_TradeCard( void );
void Runde_3_Bank( void );
void Runde_3_EndTurn( void );
void Runde_3_Win( void );
void Runde_3_BuyStrasse( void );
void Runde_3_BuySiedlung( void );
void Runde_3_BuyStadt( void );
void Runde_3_BuyCard( void );

void check_Possible_BuyStreet( void );
void check_Possible_BuySettlement( void );
void check_Possible_BuyCity( void );
void check_Possible_BuyCard( void );
void check_Bank();

bool check_Way_W_has_Hafen3zu1(int way_index);
bool check_Way_W_has_HafenErz(int way_index);
bool check_Way_W_has_HafenHolz(int way_index);
bool check_Way_W_has_HafenLehm(int way_index);
bool check_Way_W_has_HafenWeizen(int way_index);
bool check_Way_W_has_HafenWolle(int way_index);

#endif