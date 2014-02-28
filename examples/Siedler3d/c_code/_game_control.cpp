//////////////////////////////////////////////////
//
// File : _game_init.cpp
//
//////////////////////////////////////////////////

#include "_game_control.h"

#include "stdafx.h"
#include "DarkGDK.h"
#include "main.h"

#include "_game_types.h"
#include "_mesh.h"
#include "_object.h"
#include "_ui_create.h"
#include "_ui_control.h"
#include "_player.h"
#include "_cl.h"

#include "thc_text.h"	
#include "thc_vector.h"
#include "thc_mouse.h"
#include "thc_camera.h"
#include "thc_free.h"
#include "thc_is.h"
#include "thc_exist.h"
#include "thc_string.h"
#include "thc_memblock.h"
#include "thc_image.h"
#include "thc_log.h"

using namespace thc;

////////////////////////////////////////////
void Game_Init( void )
////////////////////////////////////////////
{
	//LOCALS
	stringstream s;
	int i,img;

	//GLOBALS/////////////////////////////////////////////////////////////////////
	game.n_active_player=0;
	game.n_first_player=0;
	game.n_size=1000.0f;
	game.n_dice_1=1;
	game.n_dice_2=4;
	game.runde=0;
	
	//! Enumerations
	game.mode_game=RUNDE_1_DICE;
	game.mode_txt=TXT_RUNDE_1_WELCOME;
	game.mode_todo=TODO_NONE;
	game.mode_object=OBJECT_INIT;

	game.btn_active=-1;
	game.mode_ui=UI_NONE;	
	game.mode_ui_old=UI_NONE;
	
	game.info.resize(0);

	//RÄUBER/////////////////////////////////////////////////////////////////////
	game.obj_rauber=FreeObject();	
	dbLoadObject("media\\obj\\raeuber.x",game.obj_rauber);
	dbSetObject(game.obj_rauber,1,0,0,2,0,0,0);
	dbPositionObject(game.obj_rauber,0.0f,0.0f,0.0f);

	//IMAGES/////////////////////////////////////////////////////////////////////////////////
	game.img_way_S=ImageLoad("media\\gfx\\textures\\img_waypoint_strasse_tex.PNG",0);
	game.img_way_W=ImageLoad("media\\gfx\\textures\\img_waypoint_siedlung_tex.PNG",0);
	game.mem_holz=MemblockLoad("media\\gfx\\textures\\mem_holz.jpg",1);
	game.mem_icon_strasse=MemblockLoad("media\\gfx\\textures\\mem_icon_strasse.PNG",1);
	game.mem_icon_siedlung=MemblockLoad("media\\gfx\\textures\\mem_icon_siedlung.PNG",1);
	game.mem_icon_stadt=MemblockLoad("media\\gfx\\textures\\mem_icon_stadt.PNG",1);

	//WÜRFEL-TEXTUREN////////////////////////////////////////////////////////////////////////
	game.img_dice.resize(6);
	for (i=0; i<6; i++)
	{
		s.str("");
		s << "media\\gfx\\dice\\" << i+1 << ".PNG";
		img=ImageLoad((char*)s.str().c_str(),1);
		game.img_dice[i]=img;
	}

	/////////////////////////////MESH Templates//////////////////////////////////////////////
	game.mesh_chip=MakeMeshChip(100.0f,20.0f,20);
	game.mesh_hexagon=MakeMeshHexagon(game.n_size);
	game.mesh_strasse=MakeMeshStrasse(60.0f,20.0f,300.0f);
	game.mesh_siedlung=MakeMeshSiedlung(100.0f,100.0f,100.0f);
	game.mesh_stadt=MakeMeshStadt(200.0f,200.0f,100.0f);
	game.mesh_waypoint_strasse=MakeMeshChip(50.0f, 5.0f, 16);
	game.mesh_waypoint_siedlung=MakeMeshChip(70.0f, 10.0f, 16);
	/////////////////////////////W_POINTS//////////////////////////////////////////////
	game.vertex_W.resize(6);					
	game.vertex_W[0].x=0.0f;					game.vertex_W[0].z=game.n_size*0.50f;
	game.vertex_W[1].x=-game.n_size*0.5f;	game.vertex_W[1].z=game.n_size*0.25f;
	game.vertex_W[2].x=-game.n_size*0.5f;	game.vertex_W[2].z=-game.n_size*0.25f;
	game.vertex_W[3].x=0.0f;					game.vertex_W[3].z=-game.n_size*0.50f;
	game.vertex_W[4].x=game.n_size*0.5f;	game.vertex_W[4].z=-game.n_size*0.25f;
	game.vertex_W[5].x=game.n_size*0.5f;	game.vertex_W[5].z=game.n_size*0.25f;

	/////////////////////////////S_POINTS//////////////////////////////////////////////
	game.vertex_S.resize(6);
	for (int i=0; i<6; i++)
	{		
		game.vertex_W[i].y=0.0f;
		game.vertex_S[i].y=0.0f;
		if (i<5)
		{
			game.vertex_S[i].x=game.vertex_W[i].x+0.5f*(game.vertex_W[i+1].x-game.vertex_W[i].x);
			game.vertex_S[i].z=game.vertex_W[i].z+0.5f*(game.vertex_W[i+1].z-game.vertex_W[i].z);
		}
		else
		{
			game.vertex_S[5].x=game.vertex_W[5].x+0.5f*(game.vertex_W[0].x-game.vertex_W[5].x);
			game.vertex_S[5].z=game.vertex_W[5].z+0.5f*(game.vertex_W[0].z-game.vertex_W[5].z);
		}
	}

	LoadTextures_For_Tiles();
	LoadTextures_For_Chips();

	LoadTiles();
	LoadChips();

	Generate_Way_S();
	Generate_Way_W();
	Generate_Missing_Information_1();
	Generate_Missing_Information_2();
	Generate_Missing_Information_3();
	Generate_Missing_Information_4();
	Generate_Missing_Information_5();

	UI_Create();

	PlayerCreate("THC Lord Grisgram",dbRGB(255,0,0),"media\\gfx\\player\\juliuscaesar.png",0);
	PlayerCreate("Bilbo",dbRGB(255,255,0),"media\\gfx\\player\\sid.png",1);
	PlayerCreate("Gabba Gandalf",dbRGB(50,200,55),"media\\gfx\\player\\napoleon.png",1);
	PlayerCreate("Katherina",dbRGB(0,0,255),"media\\gfx\\player\\catherine.png",1);

	SetActivePlayer(0);
	SetFirstPlayer(0);
	UI_Show_Todo(false);
	UI_Show_Bauliste(false);
	UI_Update();

	Show_Waypoint_S(false);
	Show_Waypoint_W(false);

	game.show_dev_info=false;
	game.zeit=dbTimer();
	cl.init();

}

////////////////////////////////////////////
void Game_Control( void )
////////////////////////////////////////////
{
		MouseControl();
		CameraControl();
		CameraCylinder (0,30.0f,30.0f,1.5f);
		UI_Control();
		Runde_1_Control_Dice();
		Runde_2_Control_Place();
		Runde_3_Control_Loop();
		cl.control();

		// /*
		//PLAYERINFOS
		int button_count=(int)game.btn.size();
		int b,m1,m2,m3,m4;
		for (b=0; b<button_count; b++)
		{
			if (game.btn[b].name.compare(0,6,"Player")==0)
			{
				int p=game.btn[b].type;
				//int p=atoi(game.btn[b].name.substr(6,1).c_str())-1;
				m1=game.btn[b].x;
				m2=game.btn[b].y;
				m3=m1+game.btn[b].dx;
				m4=m2+game.btn[b].dy;
				if (MouseOver(m1,m2,m3,m4)==true)
				{
					drawInfo_Player(p, mouse.x+20, mouse.y, 1, 0, 0xFFFFFFFF, 0xA00000FF);
				}
			}
		}
		// */

		//### pick object
		if ((mouse.MOVE) || (camera.CHANGE))
		{
			if (IsObject(game.use_obj)==true) dbHideObject(game.use_obj);
			game.pick.obj=dbPickObject(mouse.x,mouse.y,1,1000);
			if (IsObject(game.use_obj)==true) dbShowObject(game.use_obj);
			// Auswertung für TYPE of PICK OBJECT
			// /*
			game.index_tile =getTile (game.pick.obj);
			game.index_way_w=getWay_W(game.pick.obj);
			game.index_way_s=getWay_S(game.pick.obj);
			// */

			if (camera.CHANGE==true)
			{
				Float3 a;
				a.x=-dbCameraPositionX();
				a.y=0.0f;
				a.z=-dbCameraPositionZ();
				Float3 b;
				b.x=0.0f;
				b.y=0.0f;
				b.z=1.0f;
				float w=dbWrapValue(VectorAngle(a,b));
				int obj,t,tile_count=(int)game.tiles.size();
				for(t=0; t<tile_count; t++)
				{
					obj=game.tiles[t].chip_obj;
					if (IsObject(obj))
					{
						dbRotateObject(obj,0.0f,w,0.0f);
						stringstream s;
						s<<"Winkel = "<<w;
						dbText(scr.x/2,scr.y/2,(char*)s.str().c_str());
					}
				}
			}
		}
		// /*
		if (game.show_dev_info==true)
		{
			drawInfo_Tile(game.index_tile,mouse.x+20,mouse.y+20,1,0,0xFFFFFFFF,0xA00000FF);
			drawInfo_Way_W(game.index_way_w,mouse.x+20,mouse.y+20,1,0,0xFFFFFFFF,0xA00000FF);
			drawInfo_Way_S(game.index_way_s,mouse.x+20,mouse.y+20,1,0,0xFFFFFFFF,0xA00000FF);
		}
		// */

		//### window caption
		stringstream s;
		s << "FPS(" << dbScreenFPS();
		s << "), CAM(";
		s << (int)camera.x << "," << (int)camera.y << "," << (int)camera.z << "|";
		s << (int)camera.a << "," << (int)camera.b << "," << (int)camera.c;
		s << "), M(" << mouse.x << "," << mouse.y << ")";
		s << "), POLY(" << dbStatistic(1);
		s << "), KEY(" << dbScanCode() << ")";
		dbSetWindowTitle((char *)s.str().c_str());

		drawInfoLog();

		//KEYBOARD
		int scan=dbScanCode();

		//TASTE :: F1 - Help Bauliste
		if (scan==59)
		{
			if (keys[59]==false)
			{
				keys[59]=true;
				setBTN_visible("Bauliste");
			}
		}
		else
		{
			keys[59]=false;
		}

}

////////////////////////////////////////////
void Game_Delete( void )
////////////////////////////////////////////
{
		cl.terminate();
}

////////////////////////////////////////////
void LoadTextures_For_Tiles( void )
////////////////////////////////////////////
{
	string pLoad="media\\data\\standart_textures_for_tiles.thc";

	//Abbruchbedingungen
	if (IsFile(pLoad.c_str())==0) return;
	
	//locals
	string buffer;
	int count,i,tex;

	//TEX file open
	ifstream in(pLoad.c_str());
	if (in.is_open()==true)
	{
		//TEX count

		if (getline(in,buffer)) count=atoi(buffer.c_str());
		if (count==0) return;

		//TEX array DELETE content
		if (game.img_tile.size()>0)
		{
			for (int i=0; i<(int)game.img_tile.size(); i++)
				if (IsImage(game.img_tile[i])==true)
					dbDeleteImage(game.img_tile[i]);
		}

		//TEX array resize
		game.img_tile.resize(count);

		//TEX array fill
		for (i=0; i<(int)game.img_tile.size(); i++)
		{
			if (getline(in,buffer))
			{
				tex=ImageLoad((char*)buffer.c_str(),0);
				game.img_tile[i]=tex;
			}
		}		
	}
}
////////////////////////////////////
void LoadTiles( void )
////////////////////////////////////
{
	//filename
	string pLoad="media\\data\\standart_bauplan.thc";

	//OPEN filename
	ifstream in(pLoad.c_str());							// Deklariere Klasse IFSTREAM mit filename als Argument
	if (in.is_open()==false) return;						// Wenn Datei nicht geöffnet werden kann, dann beende Prozedur

	//DELETE Array Elements
	int tile_count=(int)game.tiles.size();				// Hole Array Größe
	if (tile_count>0)											// Wenn Array Größe > 0
	{	for (int i=0; i<tile_count; i++)						// Für alle Elemente in Array
			if (IsObject(game.tiles[i].obj)==true)		// Prüfe ob Objekt existiert
				dbDeleteObject(game.tiles[i].obj);		// Wenn ja, dann lösche Objekt
	}

	//RESET Array
	game.tiles.resize(0);

	//GET Anzahl-Tiles
	std::string buffer,rest;
	if (getline(in,buffer)) tile_count=atoi(buffer.c_str());		// Lese erste Zeile aus Datei
	if (tile_count<=0) return;												// Wenn Wert der ersten Zeile <=0, dann beende Prozedur
		
	//GET Anzahl-Texturen
	int tex_count=(int)game.img_tile.size();							// Hole Anzahl Tile-Texturen die vorher geladen wurden

	//locals
	int j,k,x,z,w,tex;
	TILE Tile;
	W_WAYPOINT way_W;	
	S_WAYPOINT way_S;

	//START FILLING
	for (j=0; j<tile_count; j++)
	{
		//Lese Zeile in std::string buffer
		if (getline(in,buffer))
		{
			//Reset Types
			Tile.way_S.resize(0);
			Tile.way_W.resize(0);
			Tile.chip_obj=0;
			Tile.chip_tex=0;
			Tile.chip_wert=0;
			Tile.name="";
			Tile.obj=0;
			Tile.tex=0;
			Tile.type=0;
			Tile.winkel=0;
			Tile.x=0.0f;
			Tile.y=0.0f;
			Tile.z=0.0f;
			Tile.raeuber=false;

			way_W.disabled=false;
			way_W.bebaut=0;
			way_W.next_S.resize(0);
			way_W.next_T.resize(0);
			way_W.next_W.resize(0);
			way_W.obj=0;
			way_W.player=-1;
			way_W.x=0.0f;
			way_W.y=0.0f;
			way_W.z=0.0f;

			way_S.bebaut=0;
			way_S.next_T.resize(0);
			way_S.next_W.resize(0);
			way_S.obj=0;
			way_S.player=-1;
			way_S.winkel=0;
			way_S.x=0.0f;
			way_S.y=0.0f;
			way_S.z=0.0f;

			//- LOAD-INFORMATION ---------------------------------------------------------------------
			STRING_SPLIT(buffer,",",rest,buffer);	Tile.name=rest;		
			STRING_SPLIT(buffer,",",rest,buffer);	tex=atoi(rest.c_str());
			STRING_SPLIT(buffer,",",rest,buffer);	x=atoi(rest.c_str());
			STRING_SPLIT(buffer,",",rest,buffer);	z=atoi(rest.c_str());
																w=atoi(buffer.c_str());											

			//- TEXTUR -------------------------------------------------------------------------------
			if(tex<tex_count)	Tile.tex=game.img_tile[tex];
			
			//- OBJECT -------------------------------------------------------------------------------
			Tile.x=(float)x*game.n_size*0.50f;
			Tile.z=(float)z*game.n_size*0.25f;
			Tile.obj=MakeObjectHexagon(Tile.x,Tile.y,Tile.z,Tile.tex);

			//- TYPE ---------------------------------------------------------------------------------
			if (Tile.name.compare("Wasser")==0)			Tile.type=0;
			if (Tile.name.compare("Hafen 3zu1")==0)	Tile.type=1;
			if (Tile.name.compare("Hafen Erz")==0)		Tile.type=2;
			if (Tile.name.compare("Hafen Holz")==0)	Tile.type=3;
			if (Tile.name.compare("Hafen Lehm")==0)	Tile.type=4;
			if (Tile.name.compare("Hafen Weizen")==0)	Tile.type=5;
			if (Tile.name.compare("Hafen Wolle")==0)	Tile.type=6;
			if (Tile.name.compare("Wueste")==0)			Tile.type=7;
			if (Tile.name.compare("Land Erz")==0)		Tile.type=8;
			if (Tile.name.compare("Land Holz")==0)		Tile.type=9;
			if (Tile.name.compare("Land Lehm")==0)		Tile.type=10;
			if (Tile.name.compare("Land Weizen")==0)	Tile.type=11;
			if (Tile.name.compare("Land Wolle")==0)	Tile.type=12;

			//- WINKEL -------------------------------------------------------------------------------
			Tile.winkel=w*60;

			//- WAYPOINTS ----------------------------------------------------------------------------
			
			// if Wasser dann lasse way_W und way_S leer
			if (Tile.name.compare("Wasser")==0)
			{
				
			}
			// if Wueste dann lasse way_W und way_S leer
			if (Tile.name.compare("Wueste")==0)
			{
				// if Wasser dann lasse way_W und way_S leer
			}
			// if Land dann fülle way_W und way_S komplett
			if (Tile.name.compare(0,4,"Land")==0)
			{
				for (k=0; k<6; k++)
				{
					way_W.x=game.vertex_W[k].x+Tile.x;
					way_W.y=game.vertex_W[k].y+Tile.y;
					way_W.z=game.vertex_W[k].z+Tile.z;

					way_S.x=game.vertex_S[k].x+Tile.x;
					way_S.y=game.vertex_S[k].y+Tile.y;
					way_S.z=game.vertex_S[k].z+Tile.z;

					Tile.way_W.push_back(way_W);
					Tile.way_S.push_back(way_S);
				}
			}
			if (Tile.name.compare(0,5,"Hafen")==0)
			{
				// if Hafen
				if (Tile.winkel==0)
				{
					for (k=0; k<2; k++)
					{
						way_W.x=game.vertex_W[k].x+Tile.x;					
						way_W.y=game.vertex_W[k].y+Tile.y;
						way_W.z=game.vertex_W[k].z+Tile.z;
						Tile.way_W.push_back(way_W);
					}
				}
				if (Tile.winkel==60)
				{
					for (k=1; k<3; k++)
					{
						way_W.x=game.vertex_W[k].x+Tile.x;					
						way_W.y=game.vertex_W[k].y+Tile.y;
						way_W.z=game.vertex_W[k].z+Tile.z;
						Tile.way_W.push_back(way_W);
					}
				}
				if (Tile.winkel==120)
				{
					for (k=2; k<4; k++)
					{
						way_W.x=game.vertex_W[k].x+Tile.x;					
						way_W.y=game.vertex_W[k].y+Tile.y;
						way_W.z=game.vertex_W[k].z+Tile.z;
						Tile.way_W.push_back(way_W);
					}
				}
				if (Tile.winkel==180)
				{
					for (k=3; k<5; k++)
					{
						way_W.x=game.vertex_W[k].x+Tile.x;					
						way_W.y=game.vertex_W[k].y+Tile.y;
						way_W.z=game.vertex_W[k].z+Tile.z;
						Tile.way_W.push_back(way_W);
					}
				}
				if (Tile.winkel==240)
				{
					for (k=4; k<6; k++)
					{
						way_W.x=game.vertex_W[k].x+Tile.x;					
						way_W.y=game.vertex_W[k].y+Tile.y;
						way_W.z=game.vertex_W[k].z+Tile.z;
						Tile.way_W.push_back(way_W);
					}
				}
				if (Tile.winkel==300)
				{
					way_W.x=game.vertex_W[5].x+Tile.x;					
					way_W.y=game.vertex_W[5].y+Tile.y;
					way_W.z=game.vertex_W[5].z+Tile.z;
					Tile.way_W.push_back(way_W);

					way_W.x=game.vertex_W[0].x+Tile.x;					
					way_W.y=game.vertex_W[0].y+Tile.y;
					way_W.z=game.vertex_W[0].z+Tile.z;
					Tile.way_W.push_back(way_W);
				}
			}	
			game.tiles.push_back(Tile);
		}
	}
}
////////////////////////////////////////////
void LoadTextures_For_Chips( void )
////////////////////////////////////////////
{
	if (!game.img_chip.empty())
	{
		for (int i=0; i<(int)game.img_chip.size(); i++)
			if (IsImage(game.img_chip[i])==true)
				dbDeleteImage(game.img_chip[i]);
	}
	game.img_chip.resize(10);
	game.img_chip[0]=ImageLoad("media\\gfx\\chips\\chip02.png",0);
	game.img_chip[1]=ImageLoad("media\\gfx\\chips\\chip03.png",0);
	game.img_chip[2]=ImageLoad("media\\gfx\\chips\\chip04.png",0);
	game.img_chip[3]=ImageLoad("media\\gfx\\chips\\chip05.png",0);
	game.img_chip[4]=ImageLoad("media\\gfx\\chips\\chip06.png",0);
	game.img_chip[5]=ImageLoad("media\\gfx\\chips\\chip08.png",0);
	game.img_chip[6]=ImageLoad("media\\gfx\\chips\\chip09.png",0);
	game.img_chip[7]=ImageLoad("media\\gfx\\chips\\chip10.png",0);
	game.img_chip[8]=ImageLoad("media\\gfx\\chips\\chip11.png",0);
	game.img_chip[9]=ImageLoad("media\\gfx\\chips\\chip12.png",0);
}
///////////////////////////////////////////////////////////////
void LoadChips( void )
///////////////////////////////////////////////////////////////
{
	int tile_count=(int)game.tiles.size();
	if (tile_count==0) return;

	string name;
	int t,land_count=0;
	for (t=0; t<tile_count; t++)
	{
		name=game.tiles[t].name;
		if (STRING_COMPARE(name,"Land Weizen")) land_count++; 
		if (STRING_COMPARE(name,"Land Holz")) land_count++;
		if (STRING_COMPARE(name,"Land Erz")) land_count++;
		if (STRING_COMPARE(name,"Land Lehm")) land_count++;
		if (STRING_COMPARE(name,"Land Wolle")) land_count++;
	}
	if (land_count==0) return;
	//_ASSERTE(land_count==18);

	int *zufall=new int[land_count];
	Generate_ZufallsArray(land_count,zufall);

	bool do_work;
	int zufall_index=0;
	float x,z,y=0.0f;
	int obj,tex,wert;
	for (t=0; t<tile_count; t++)
	{
		do_work=false;
		name=game.tiles[t].name;
		if (STRING_COMPARE(name,"Land Weizen")) do_work=true; 
		if (STRING_COMPARE(name,"Land Holz")) do_work=true;
		if (STRING_COMPARE(name,"Land Erz")) do_work=true;
		if (STRING_COMPARE(name,"Land Lehm")) do_work=true;
		if (STRING_COMPARE(name,"Land Wolle")) do_work=true;
		if (do_work==true)
		{
			wert=zufall[zufall_index];
			if (wert==2) tex=game.img_chip[0];
			if (wert==3) tex=game.img_chip[1];
			if (wert==4) tex=game.img_chip[2];
			if (wert==5) tex=game.img_chip[3];
			if (wert==6) tex=game.img_chip[4];
			if (wert==8) tex=game.img_chip[5];
			if (wert==9) tex=game.img_chip[6];
			if (wert==10) tex=game.img_chip[7];
			if (wert==11) tex=game.img_chip[8];
			if (wert==12) tex=game.img_chip[9];
			  x=game.tiles[t].x;
			  y=game.tiles[t].y;
			  z=game.tiles[t].z;
			obj=game.tiles[t].chip_obj;
			if (IsObject(obj)==true) dbDeleteObject(obj);
         obj=MakeObjectChip(x,y,z,tex);
			game.tiles[t].chip_wert=wert;
			game.tiles[t].chip_obj=obj;				
			game.tiles[t].chip_tex=tex;				
			zufall_index++;
		}
	}
	//_ASSERTE(zufall_index==17);
	SAFE_DELETE_ARRAY( zufall );
}
///////////////////////////////////////////////////////////////
void Generate_ZufallsArray(int anzahl,int *iarray)
///////////////////////////////////////////////////////////////
{
	// Startet Zufallsgenerator
	dbRandomize(dbTimer());
	int i;

	// # ARRAY #
	// rnd[0][i]=mögliche zahlen
	// rnd[1][i]=maximale anzahl pro möglicher zahlen
	// rnd[2][i]=aktuelle anzahl pro möglicher zahlen
	int **rnd;			// Zeiger
	int ROW=10;			// Anzahl Zeilen
	int COL=3;			// Anzahl Spalten
	rnd=new int*[ROW];
	for (i=0; i<ROW; i++)
		rnd[i]=new int[COL];

	int rest = anzahl % 10;
	int base = (anzahl - rest) / 10;

	// Setzt rnd[i][0]
	rnd[0][0]=2;	rnd[1][0]=3;	rnd[2][0]=4;	rnd[3][0]=5;	rnd[4][0]=6;
	rnd[5][0]=8;	rnd[6][0]=9;	rnd[7][0]=10;	rnd[8][0]=11;	rnd[9][0]=12;
	
	// Setzt rnd[i][1]  (z.B. anzahl chips = 18 => Verteilung : 1,2,2,2,2,2,2,2,2,1)
	for (i=0; i<10; i++)				{	rnd[i][1]=base;		}
	if (rest==1) {	for (i=5; i<6; i++)	{	rnd[i][1]++;	}	}
	if (rest==2) {	for (i=4; i<6; i++)	{	rnd[i][1]++;	}	}
	if (rest==3) {	for (i=4; i<7; i++)	{	rnd[i][1]++;	}	}
	if (rest==4) { for (i=3; i<7; i++)	{	rnd[i][1]++;	}	}
	if (rest==5) {	for (i=3; i<8; i++)	{	rnd[i][1]++;	}	}
	if (rest==6) {	for (i=2; i<8; i++)	{	rnd[i][1]++;	}	}
	if (rest==7) {	for (i=2; i<9; i++)	{	rnd[i][1]++;	}	}
	if (rest==8) {	for (i=1; i<9; i++)	{	rnd[i][1]++;	}	}
	if (rest==9) {	for (i=1; i<10;i++)	{	rnd[i][1]++;	}	}

	// Setzt rnd[i][2]
	for (i=0; i<10; i++)
		rnd[i][2]=0;

	// Generiert Zufallszahlen
	int index;
	int accept=0;
	for (i=0; i<anzahl; i++)
	{
		accept=0;
		do
		{
			index=dbRND(9);
			if (rnd[index][2]<rnd[index][1])
			{
				iarray[i]=rnd[index][0];
				rnd[index][2]++;
				accept=1;
			}
		} while (accept==0);
	}

	delete [] rnd;
}
////////////////////////////////////////////////////////////////////////////////////////////
void Generate_Way_W( void )
////////////////////////////////////////////////////////////////////////////////////////////
{
	
	int tile_count=(int)game.tiles.size();
	if (tile_count==0) return;
	game.way_W.resize(0);
		
	bool exist=false;
	float x,y,z;
	int n,t,ii,w,way_count;

	//--- loop tiles ------------------------------------------------------------
	for (t=0; t<tile_count; t++)
	{
		//check tiles type // kein 0 (wasser)
		if (game.tiles[t].type>0)
		{
			//--- loop tile waypoints --------------------------------------------------------
			n=game.tiles[t].way_W.size();
			for (ii=0; ii<n; ii++)
			{
				//3D-Position
				x=game.tiles[t].way_W[ii].x;
				y=game.tiles[t].way_W[ii].y;
				z=game.tiles[t].way_W[ii].z;
					
				//array size of waypoints
				way_count=(int)game.way_W.size();
				if (way_count>0)
				{
					exist=false;
					//--- loop global waypoints
					for (w=0; w<way_count; w++)
					{	
						//check if 3D-Position already exist
						if ((x-1.0f<game.way_W[w].x) &&
							 (x+1.0f>game.way_W[w].x) &&
							 (z-1.0f<game.way_W[w].z) && 
							 (z+1.0f>game.way_W[w].z))
						{
							exist=true;
							break;
						}
					}
				}
				if (exist==false)
				{
					W_WAYPOINT way;
					way.disabled=false;
					way.bebaut=0;
					way.player=-1;
					way.x=x;
					way.y=y;
					way.z=z;
					way.next_T.resize(0);
					way.next_S.resize(0);
					way.next_W.resize(0);
					way.obj=MakeObjectWaypointSiedlung(x,y,z);
					game.way_W.push_back(way);
				}
			}
		}
	}
	//-----FÜLLE ALLE WAYPOINTS mit INFORMATIONEN------------------------------------------	
	way_count=(int)game.way_W.size();
	for (w=0; w<way_count; w++)
	{
		x=game.way_W[w].x;
		y=game.way_W[w].y;
		z=game.way_W[w].z;
		for (t=0; t<tile_count; t++)
		{
			if (game.tiles[t].type>0)
			{
				n=(int)game.tiles[t].way_W.size();
				for (ii=0; ii<n; ii++)
				{
					if ((x-1.0f<game.tiles[t].way_W[ii].x) &&
						 (x+1.0f>game.tiles[t].way_W[ii].x) &&
						 (z-1.0f<game.tiles[t].way_W[ii].z) && 
						 (z+1.0f>game.tiles[t].way_W[ii].z))
					{
						game.way_W[w].next_T.push_back(t);
					}
				}
			}
		}
	}
	// ENDE
}
////////////////////////////////////////////////////////////////////////////////////////////
void Generate_Way_S( void )
////////////////////////////////////////////////////////////////////////////////////////////
{
	int tile_count=(int)game.tiles.size();
	if (tile_count==0) return;
	game.way_S.resize(0);
	
	bool exist=false;
	float x,y,z;
	int n,t,ii,w,way_count;

	//--- loop tiles ------------------------------------------------------------
	for (t=0; t<tile_count; t++)
	{
		//check tiles type // kein 0 (wasser)
		if (game.tiles[t].type>0)
		{
			//--- loop tile waypoints --------------------------------------------------------
			n=game.tiles[t].way_S.size();
			for (ii=0; ii<n; ii++)
			{
				//3D-Position
				x=game.tiles[t].way_S[ii].x;
				y=game.tiles[t].way_S[ii].y;
				z=game.tiles[t].way_S[ii].z;
					
				//array size of waypoints
				way_count=(int)game.way_S.size();
				if (way_count>0)
				{
					exist=false;
					//--- loop global waypoints
					for (w=0; w<way_count; w++)
					{	
						//check if 3D-Position already exist
						if ((x-1.0f<game.way_S[w].x) &&
							 (x+1.0f>game.way_S[w].x) &&
							 (z-1.0f<game.way_S[w].z) && 
							 (z+1.0f>game.way_S[w].z))
						{
							exist=true;
							break;
						}
					}
				}
				if (exist==false)
				{
					S_WAYPOINT way;
					way.bebaut=0;
					way.player=-1;
					if (ii==0) way.winkel=240;
					if (ii==1) way.winkel=0;
					if (ii==2) way.winkel=120;
					if (ii==3) way.winkel=240;
					if (ii==4) way.winkel=0;
					if (ii==5) way.winkel=120;
					way.x=x;
					way.y=y;
					way.z=z;
					way.next_T.resize(0);
					way.next_W.resize(0);
					way.obj=MakeObjectWaypointStrasse(x,y,z);
					game.way_S.push_back(way);
				}
			}
		}
	}

	//-----FÜLLE ALLE WAYPOINTS mit INFORMATIONEN------------------------------------------	
	way_count=(int)game.way_S.size();
	for (w=0; w<way_count; w++)
	{
		x=game.way_S[w].x;
		y=game.way_S[w].y;
		z=game.way_S[w].z;
		for (t=0; t<tile_count; t++)
		{
			if (game.tiles[t].type>0)
			{
				n=game.tiles[t].way_S.size();
				for (ii=0; ii<n; ii++)
				{
					if ((x-1.0f<game.tiles[t].way_S[ii].x) &&
						 (x+1.0f>game.tiles[t].way_S[ii].x) &&
						 (z-1.0f<game.tiles[t].way_S[ii].z) && 
						 (z+1.0f>game.tiles[t].way_S[ii].z))
					{
						game.way_S[w].next_T.push_back(t);
					}
				}
			}
		}
	}
}
//==========================================================================
//===	Diese Funktion Prüft ob die angegebene Position schon existiert
//=== Return : -1 -> falscher index oder way_W.next_W ist leer
//===           0 -> Position existiert nicht
//===          >0 -> Position existiert bei next_W[return]
//==========================================================================
/*
int Find_game_way_W_next_W(int index, float x, float y, float z)
{
	// Anzahl W_WAYPOINTS
	int c0=(int)game.way_W.size();
	if ((index<0) || (index>=c0)) return -2;

	// Anzahl W_WAYPOINTS.next_W
	int c1=(int)game.way_W[index].next_W.size();
	if (c1<=0) return -1;

	// Position von W_WAYPOINTS.next_W
	float next_x,next_z;
	int i,next_W;
	for (i=0; i<c1; i++)
	{
		next_W=game.way_W[index].next_W[i];
		if ((next_W>=0) && (next_W<c0))
		{
			next_x=game.way_W[next_W].x;
			next_z=game.way_W[next_W].z;
			if ((next_x-1.0f<x) && (next_x+1.0f>x) && (next_z-1.0f<z) && (next_z+1.0f>z))
			{
				return i;
			}
		}
	}
	return 0;
}
*/
//==========================================================================
//===	Diese Funktionen füllen alle Strukturen, die nocht nicht gefüllt werden konnten
//=== 1. game.way_W.next_W
//=== 2. game.way_W.next_S
//=== 3. game.way_S.next_W
//=== 4. game.tiles.way_W		game.way_W muss kopiert werden
//=== 5. game.tiles.way_S		game.way_S muss kopiert werden
//==========================================================================

// Durchsucht alle WAY_W nach dem WAY_W des TILE(nr,w_index).
int FIND_WAY_W_that_equals_TILE_W(int tile_nr, int tile_w)
{
	int tile_count=(int)game.tiles.size();
	if((tile_nr<0) || (tile_nr>=tile_count)) return -1;

	int tile_way_w_count=(int)game.tiles[tile_nr].way_W.size();
	if((tile_w<0) || (tile_w>=tile_way_w_count)) return -1;

	const float x0=game.tiles[tile_nr].way_W[tile_w].x;
	const float z0=game.tiles[tile_nr].way_W[tile_w].z;
	
	int way_w_count=(int)game.way_W.size();
	if (way_w_count==0) return -1;
	int i;
	float x,z;
	for (i=0; i<way_w_count; i++)
	{
		x=game.way_W[i].x;
		z=game.way_W[i].z;
		if ((x-1.0f<x0) && (x+1.0f>x0) && (z-1.0f<z0) && (z+1.0f>z0))
		{
			return i;
		}
	}
	return -1;
}
//////////////////////////////////
////									////
//// FÜLLE game.way_W.next_W	////
////									////
//////////////////////////////////
void Generate_Missing_Information_1()
{
	int index1,index2,index3,result, exist;
	int v0,v1,v2,v3, c0,c1,c2,c3;
	float x1,x2,z1,z2;
	
	// FÜR ALLE W_WAYPOINTS
	///////////////////////////////////////////////////////////////
	// Durchlaufe das gesammte Array der Waypoints für Siedlungen
	// um jeden Waypoint füllen zu können
	///////////////////////////////////////////////////////////////
	c0=(int)game.way_W.size();	if (c0<=0) return;
	for (v0=0; v0<c0; v0++)	
	{
		// FÜR ALLE NEXT_T
		/////////////////////////////////////////////////////////////
		// bestimme die Anzahl an Nachbar-Tiles die der Waypoint hat
		// und durchlaufe alle Nachbar-Tiles
		// indem next_T als index des Tiles-Arrays benutzt wird
		/////////////////////////////////////////////////////////////
		c1=(int)game.way_W[v0].next_T.size();
		if (c1>0)
		{
			for (v1=0; v1<c1; v1++)
			{
				index1=game.way_W[v0].next_T[v1];	// lege Index in Variable ab, zur Vereinfachung

				// FÜR ALLE W_WAYPOINTS des TILES
				//////////////////////////////////////////////////////////////////////////////
				// bestimme die Anzahl an W_Waypoints die der Tile hat und durchlaufe alle.
				// Prüfe ob die Position des game.tiles.way_W 
				// mit der Pos des game.way_W übereinstimmt
				//////////////////////////////////////////////////////////////////////////////
				c2=(int)game.tiles[index1].way_W.size();
				if (c2>0)
				{
					x1=game.way_W[v0].x;		// X-Position des aktuellen game.way_W
					z1=game.way_W[v0].z;		// Z-Position des aktuellen game.way_W
					for (v2=0; v2<c2; v2++)
					{
						x2=game.tiles[index1].way_W[v2].x;	// X-Position des aktuellen Way_W des aktuellen Tiles
						z2=game.tiles[index1].way_W[v2].z;	// Z-Position des aktuellen Way_W des aktuellen Tiles
						index2=-1;
						index3=-1;
						if ((x1-1.0f<x2) && (x1+1.0f>x2) && (z1-1.0f<z2) && (z1+1.0f>z2)) // Vergleiche Position
						{
							//////////////////////////////////////////////////////////////////////////////			
							// Wenn ja, dann bestimme die 2 Indices der Waypoints des Tiles, die game.way_W.next_W
							// hinzugefügt werden sollen, unterscheide dabei zwischen Häfen und Land
							//////////////////////////////////////////////////////////////////////////////
							// Für Hafen
							if (c2==2)
							{
								if (v2==0)
								{
									index2=1;
								}
								if (v2==1)
								{
									index2=0;
								}
							}
							// Für Land
							if (c2==6)
							{
								if (v2==0)	{	index2=1;	index3=5;	}
								if (v2==1)	{	index2=2;	index3=0;	}
								if (v2==2)	{	index2=3;	index3=1;	}
								if (v2==3)	{	index2=4;	index3=2;	}
								if (v2==4)	{	index2=5;	index3=3;	}
								if (v2==5)	{	index2=0;	index3=4;	}
							}
							///////////////////////////////////////////////////////////////////////////////
							// Durchlaufe alle game.way_W.next_W um zu prüfen, ob sie schon vorhanden sind
							// d.h. 1. vergleiche Indices von game.way_W.next_W mit index2
							// und  2. vergleiche Indices von game.way_W.next_W mit index3
							///////////////////////////////////////////////////////////////////////////////
							// 1.
							if (index2>=0)
							{
								result=FIND_WAY_W_that_equals_TILE_W(index1, index2);
								if (result>=0)
								{
									c3=(int)game.way_W[v0].next_W.size();
									exist=0;
									if (c3>0)
									{
										for (v3=0; v3<c3; v3++)
										{
											if (game.way_W[v0].next_W[v3]==result) exist=1;
										}
									}
									if (exist==0)
									{
										game.way_W[v0].next_W.push_back(result);
									}
								}
							}
							// (2.)
							if (index3>=0)
							{
								result=FIND_WAY_W_that_equals_TILE_W(index1, index3);
								if (result>=0)
								{
									c3=(int)game.way_W[v0].next_W.size();
									exist=0;
									if (c3>0)
									{
										for (v3=0; v3<c3; v3++)
										{
											if (game.way_W[v0].next_W[v3]==result) exist=1;
										}
									}
									if (exist==0)
									{
										game.way_W[v0].next_W.push_back(result);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
// Durchsucht alle WAY_S nach dem WAY_S des TILE(nr,w_index).
int FIND_WAY_S_that_equals_TILE_S(int tile_nr, int tile_w)
{
	int tile_count=(int)game.tiles.size();
	if((tile_nr<0) || (tile_nr>=tile_count)) return -1;

	int tile_way_w_count=(int)game.tiles[tile_nr].way_S.size();
	if((tile_w<0) || (tile_w>=tile_way_w_count)) return -1;

	const float x0=game.tiles[tile_nr].way_S[tile_w].x;
	const float z0=game.tiles[tile_nr].way_S[tile_w].z;
	
	int way_w_count=(int)game.way_S.size();
	if (way_w_count==0) return -1;
	int i;
	float x,z;
	for (i=0; i<way_w_count; i++)
	{
		x=game.way_S[i].x;
		z=game.way_S[i].z;
		if ((x-1.0f<x0) && (x+1.0f>x0) && (z-1.0f<z0) && (z+1.0f>z0))
		{
			return i;
		}
	}
	return -1;
}
//////////////////////////////////
////									////
//// FÜLLE game.way_W.next_S	////
////									////
//////////////////////////////////
void Generate_Missing_Information_2()
{
	int index1,index2,index3,result, exist;
	int v0,v1,v2,v3, c0,c1,c2,c3;
	float x1,x2,z1,z2;
	
	// FÜR ALLE W_WAYPOINTS
	///////////////////////////////////////////////////////////////
	// Durchlaufe das gesammte Array der Waypoints für Siedlungen
	// um jeden Waypoint füllen zu können
	///////////////////////////////////////////////////////////////
	c0=(int)game.way_W.size();	if (c0<=0) return;
	for (v0=0; v0<c0; v0++)	
	{
		// FÜR ALLE NEXT_T
		/////////////////////////////////////////////////////////////
		// bestimme die Anzahl an Nachbar-Tiles die der Waypoint hat
		// und durchlaufe alle Nachbar-Tiles
		// indem next_T als index des Tiles-Arrays benutzt wird
		/////////////////////////////////////////////////////////////
		c1=(int)game.way_W[v0].next_T.size();
		if (c1>0)
		{
			for (v1=0; v1<c1; v1++)
			{
				index1=game.way_W[v0].next_T[v1];	// lege Index in Variable ab, zur Vereinfachung

				// FÜR ALLE W_WAYPOINTS des TILES
				//////////////////////////////////////////////////////////////////////////////
				// bestimme die Anzahl an W_Waypoints die der Tile hat und durchlaufe alle.
				// Prüfe ob die Position des game.tiles.way_W 
				// mit der Pos des game.way_W übereinstimmt
				//////////////////////////////////////////////////////////////////////////////
				c2=(int)game.tiles[index1].way_W.size();
				if (c2>0)
				{
					x1=game.way_W[v0].x;		// X-Position des aktuellen game.way_W
					z1=game.way_W[v0].z;		// Z-Position des aktuellen game.way_W
					for (v2=0; v2<c2; v2++)
					{
						x2=game.tiles[index1].way_W[v2].x;	// X-Position des aktuellen Way_W des aktuellen Tiles
						z2=game.tiles[index1].way_W[v2].z;	// Z-Position des aktuellen Way_W des aktuellen Tiles
						index2=-1;
						index3=-1;
						if ((x1-1.0f<x2) && (x1+1.0f>x2) && (z1-1.0f<z2) && (z1+1.0f>z2)) // Vergleiche Position
						{
							//////////////////////////////////////////////////////////////////////////////			
							// Wenn ja, dann bestimme die 2 Indices der Waypoints des Tiles, die game.way_W.next_W
							// hinzugefügt werden sollen.
							//////////////////////////////////////////////////////////////////////////////
							// Für Land
							if (c2==6)
							{
								if (v2==0)	{	index2=0;	index3=5;	}
								if (v2==1)	{	index2=1;	index3=0;	}
								if (v2==2)	{	index2=2;	index3=1;	}
								if (v2==3)	{	index2=3;	index3=2;	}
								if (v2==4)	{	index2=4;	index3=3;	}
								if (v2==5)	{	index2=5;	index3=4;	}
							}
							///////////////////////////////////////////////////////////////////////////////
							// Durchlaufe alle game.way_W.next_W um zu prüfen, ob sie schon vorhanden sind
							// d.h. 1. vergleiche Indices von game.way_W.next_W mit index2
							// und  2. vergleiche Indices von game.way_W.next_W mit index3
							///////////////////////////////////////////////////////////////////////////////
							// (1.) INDEX_2
							if (index2>=0)
							{
								result=FIND_WAY_S_that_equals_TILE_S(index1, index2);
								if (result>=0)
								{
									c3=(int)game.way_W[v0].next_S.size();
									exist=0;
									if (c3>0)
									{
										for (v3=0; v3<c3; v3++)
										{
											if (game.way_W[v0].next_S[v3]==result) exist=1;
										}
									}
									if (exist==0)
									{
										game.way_W[v0].next_S.push_back(result);
									}
								}
							}
							// (2.) INDEX_3
							if (index3>=0)
							{
								// sucht den Array Index des Waypoints S aus game.way_S,
								// der mit dem berechneten Waypoint S aus game.tiles[index1].way_S[index3]
								// übereinstimmt
								result=FIND_WAY_S_that_equals_TILE_S(index1, index3);
								// wenn der gesuchte Array Index existiert
								if (result>=0)
								{
									// prüfe ob Array Index in next_S schon vorhanden ist
									c3=(int)game.way_W[v0].next_S.size();
									exist=0;
									if (c3>0)
									{
										for (v3=0; v3<c3; v3++)
										{
											if (game.way_W[v0].next_S[v3]==result) exist=1;
										}
									}
									// wenn Array Index in next_S nicht existiert, dann füge ein
									if (exist==0)
									{
										game.way_W[v0].next_S.push_back(result);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
//////////////////////////////////
////									////
//// FÜLLE game.way_S.next_W	////
////									////
//////////////////////////////////
void Generate_Missing_Information_3()
{
	int index1,index2,index3,result, exist;
	int v0,v1,v2,v3, c0,c1,c2,c3;
	float x1,x2,z1,z2;
	
	// FÜR ALLE S_WAYPOINTS
	///////////////////////////////////////////////////////////////
	// Durchlaufe das gesammte Array der Waypoints für Strassen
	// um jeden Waypoint füllen zu können
	///////////////////////////////////////////////////////////////
	c0=(int)game.way_S.size();	if (c0<=0) return;
	for (v0=0; v0<c0; v0++)	
	{
		// FÜR ALLE NEXT_T
		/////////////////////////////////////////////////////////////
		// bestimme die Anzahl an Nachbar-Tiles die der Waypoint hat
		// und durchlaufe alle Nachbar-Tiles
		// indem next_T als index des Tiles-Arrays benutzt wird
		/////////////////////////////////////////////////////////////
		c1=(int)game.way_S[v0].next_T.size();
		if (c1>0)
		{
			for (v1=0; v1<c1; v1++)
			{
				index1=game.way_S[v0].next_T[v1];	// lege Index in Variable ab, zur Vereinfachung

				// FÜR ALLE S_WAYPOINTS des TILES
				//////////////////////////////////////////////////////////////////////////////
				// bestimme die Anzahl an S_Waypoints die der Tile hat und durchlaufe alle.
				// Prüfe ob die Position des game.tiles.way_S 
				// mit der Pos des game.way_S übereinstimmt
				//////////////////////////////////////////////////////////////////////////////
				c2=(int)game.tiles[index1].way_S.size();
				if (c2>0)
				{
					x1=game.way_S[v0].x;		// X-Position des aktuellen game.way_W
					z1=game.way_S[v0].z;		// Z-Position des aktuellen game.way_W
					for (v2=0; v2<c2; v2++)
					{
						x2=game.tiles[index1].way_S[v2].x;	// X-Position des aktuellen Way_W des aktuellen Tiles
						z2=game.tiles[index1].way_S[v2].z;	// Z-Position des aktuellen Way_W des aktuellen Tiles
						index2=-1;
						index3=-1;
						if ((x1-1.0f<x2) && (x1+1.0f>x2) && (z1-1.0f<z2) && (z1+1.0f>z2)) // Vergleiche Position
						{
							//////////////////////////////////////////////////////////////////////////////			
							// Wenn ja, dann bestimme die 2 Indices der Waypoints des Tiles, die game.way_W.next_W
							// hinzugefügt werden sollen.
							//////////////////////////////////////////////////////////////////////////////
							// Für Hafen
							if (c2==2)
							{
								index2=0;
								index3=1;
							}

							// Für Land
							if (c2==6)
							{
								if (v2==0)	{	index2=1;	index3=0;	}
								if (v2==1)	{	index2=2;	index3=1;	}
								if (v2==2)	{	index2=3;	index3=2;	}
								if (v2==3)	{	index2=4;	index3=3;	}
								if (v2==4)	{	index2=5;	index3=4;	}
								if (v2==5)	{	index2=0;	index3=5;	}
							}
							///////////////////////////////////////////////////////////////////////////////
							// Durchlaufe alle game.way_W.next_W um zu prüfen, ob sie schon vorhanden sind
							// d.h. 1. vergleiche Indices von game.way_W.next_W mit index2
							// und  2. vergleiche Indices von game.way_W.next_W mit index3
							///////////////////////////////////////////////////////////////////////////////
							// (1.) INDEX_2
							if (index2>=0)
							{
								result=FIND_WAY_W_that_equals_TILE_W(index1, index2);
								if (result>=0)
								{
									c3=(int)game.way_S[v0].next_W.size();
									exist=0;
									if (c3>0)
									{
										for (v3=0; v3<c3; v3++)
										{
											if (game.way_S[v0].next_W[v3]==result) exist=1;
										}
									}
									if (exist==0)
									{
										game.way_S[v0].next_W.push_back(result);
									}
								}
							}
							// (2.) INDEX_3
							if (index3>=0)
							{
								// sucht den Array Index des Waypoints S aus game.way_S,
								// der mit dem berechneten Waypoint S aus game.tiles[index1].way_S[index3]
								// übereinstimmt
								result=FIND_WAY_W_that_equals_TILE_W(index1, index3);
								// wenn der gesuchte Array Index existiert
								if (result>=0)
								{
									// prüfe ob Array Index in next_S schon vorhanden ist
									c3=(int)game.way_S[v0].next_W.size();
									exist=0;
									if (c3>0)
									{
										for (v3=0; v3<c3; v3++)
										{
											if (game.way_S[v0].next_W[v3]==result) exist=1;
										}
									}
									// wenn Array Index in next_S nicht existiert, dann füge ein
									if (exist==0)
									{
										game.way_S[v0].next_W.push_back(result);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
//=============================================================
//===
//=== 4. game.tiles.way_W		game.way_W muss kopiert werden
//===	Wobei obj in wahrheit den index im array way_w enthält
//=============================================================
void Generate_Missing_Information_4()
{
	int v0,v1,v2, index;
	float x1,z1, x2,z2;

	int c0=(int)game.tiles.size();
	int c1;
	int c2=(int)game.way_W.size();

	// Suche Waypoint W der mit Tile Waypoint W übereinstimmt
	// Für alle TILES
	for (v0=0; v0<c0; v0++)
	{
		//Für alle max. 6 way_W in TILES (wenn Landtile)
		c1=(int)game.tiles[v0].way_W.size();
		if (c1>0)
		{
			for (v1=0; v1<c1; v1++)
			{
				x1=game.tiles[v0].way_W[v1].x;
				z1=game.tiles[v0].way_W[v1].z;
				index=-1;
				// Für alle way_W
				for (v2=0; v2<c2; v2++)
				{
					x2=game.way_W[v2].x;
					z2=game.way_W[v2].z;

					//Vergleiche Position
					if ((x1-1.0f<x2)&&(x1+1.0f>x2)&&(z1-1.0f<z2)&&(z1+1.0f>z2))
					{
						index=v2;
					}
				}
				// Wenn way_W Array Index gefunden wurde, dann kopiere Way_W in Tiles.way_W
				// und nutze obj als Speicherung vom Index und nicht der Objectnummer,
				// da wir die ObjNr. nicht brauchen, da sie in way_W schon vorkommt.
				if (index>=0)
				{
					int size;
					game.tiles[v0].way_W[v1].obj		=	index;
					game.tiles[v0].way_W[v1].bebaut	=	game.way_W[index].bebaut;
					game.tiles[v0].way_W[v1].disabled=	game.way_W[index].disabled;
					game.tiles[v0].way_W[v1].player	=	game.way_W[index].player;
					game.tiles[v0].way_W[v1].x			=	game.way_W[index].x;
					game.tiles[v0].way_W[v1].y			=	game.way_W[index].y;
					game.tiles[v0].way_W[v1].z			=	game.way_W[index].z;

					// NEXT_W
					size=(int)game.way_W[index].next_W.size();
					game.tiles[v0].way_W[v1].next_W.resize(0);
					for (v2=0; v2<size; v2++)
					{
						game.tiles[v0].way_W[v1].next_W.push_back(game.way_W[index].next_W[v2]);
					}

					// NEXT_S
					size=(int)game.way_W[index].next_S.size();
					game.tiles[v0].way_W[v1].next_S.resize(0);
					for (v2=0; v2<size; v2++)
					{
						game.tiles[v0].way_W[v1].next_S.push_back(game.way_W[index].next_S[v2]);
					}

					// NEXT_T
					size=(int)game.way_W[index].next_T.size();
					game.tiles[v0].way_W[v1].next_T.resize(0);
					for (v2=0; v2<size; v2++)
					{
						game.tiles[v0].way_W[v1].next_T.push_back(game.way_W[index].next_T[v2]);
					}
				}
			}
		}
	}
}
//=============================================================
//===
//=== 5. game.tiles.way_S		game.way_S muss kopiert werden
//===
//=============================================================
void Generate_Missing_Information_5()
{
	int v0,v1,v2, index;
	float x1,z1, x2,z2;

	int c0=(int)game.tiles.size();
	int c1;
	int c2=(int)game.way_S.size();

	// Für alle TILES
	for (v0=0; v0<c0; v0++)
	{
		//Für alle max. 6 way_S in TILES (wenn Landtile)
		c1=(int)game.tiles[v0].way_S.size();
		if (c1>0)
		{
			for (v1=0; v1<c1; v1++)
			{
				x1=game.tiles[v0].way_S[v1].x;
				z1=game.tiles[v0].way_S[v1].z;
				index=-1;
				// Für alle way_S
				for (v2=0; v2<c2; v2++)
				{
					x2=game.way_S[v2].x;
					z2=game.way_S[v2].z;

					//Vergleiche Position
					if ((x1-1.0f<x2)&&(x1+1.0f>x2)&&(z1-1.0f<z2)&&(z1+1.0f>z2))
					{
						index=v2;
					}
				}
				// Wenn way_W Array Index gefunden wurde, dann kopiere Way_W in Tiles.way_W
				// und nutze obj als Speicherung vom Index und nicht der Objectnummer,
				// da wir die ObjNr. nicht brauchen, da sie in way_W schon vorkommt.
				if (index>=0)
				{
					int size;
					game.tiles[v0].way_S[v1].obj		=	index;
					game.tiles[v0].way_S[v1].bebaut	=	game.way_S[index].bebaut;
					game.tiles[v0].way_S[v1].winkel	=	game.way_S[index].winkel;
					game.tiles[v0].way_S[v1].player	=	game.way_S[index].player;
					game.tiles[v0].way_S[v1].x			=	game.way_S[index].x;
					game.tiles[v0].way_S[v1].y			=	game.way_S[index].y;
					game.tiles[v0].way_S[v1].z			=	game.way_S[index].z;

					// NEXT_W
					size=(int)game.way_S[index].next_W.size();
					game.tiles[v0].way_S[v1].next_W.resize(0);
					for (v2=0; v2<size; v2++)
					{
						game.tiles[v0].way_S[v1].next_W.push_back(game.way_S[index].next_W[v2]);
					}

					// NEXT_T
					size=(int)game.way_S[index].next_T.size();
					game.tiles[v0].way_S[v1].next_T.resize(0);
					for (v2=0; v2<size; v2++)
					{
						game.tiles[v0].way_S[v1].next_T.push_back(game.way_S[index].next_T[v2]);
					}
				}
			}
		}
	}
}

void Show_Waypoint_S(bool yesno)
{
	int obj,i,count=(int)game.way_S.size();
	for (i=0; i<count; i++)
	{
		// Wenn Object existiert
		obj=game.way_S[i].obj;
		if (IsObject(obj)==true)
		{	
			// Show Object
			if (yesno==true)
			{	
				if (dbObjectVisible(obj)==0)	dbShowObject(obj);
			}
			// Hide Object
			else
			{	
				// Wenn Way_S nicht bebaut ist, verstecke ihn.
				if (game.way_S[i].bebaut==0)
				{
					if (dbObjectVisible(obj)==1)	dbHideObject(obj);
				}
			}
		}
	}
}
void Show_Waypoint_W(bool yesno)
{
	int obj,i,count=(int)game.way_W.size();
	for (i=0; i<count; i++)
	{
		obj=game.way_W[i].obj;
		if (IsObject(obj)==true)
		{
			if (yesno==true)
			{
				// Wenn Nachbar Way_W schon bebaut ist, dann zeige diesen Way_W nicht an.
				// Flag disabled wird in PlaceSiedlung() und PlaceStadt() gesetzt.
				if (game.way_W[i].disabled==false)
				{
					// Show
					if (dbObjectVisible(obj)==0)	dbShowObject(obj);
				}
				else
				{
					// Hide
					if (dbObjectVisible(obj)==1)	dbHideObject(obj);
				}
			}
			else
			{
				// Wenn Way_W schon bebaut ist, dann verstecke ihn nicht.
				if (game.way_W[i].bebaut==0)
				{
					// Hide
					if (dbObjectVisible(obj)==1)	dbHideObject(obj);
				}
			}
		}
	}
}

void AddInfo(int nr,char* pTXT)
{
	INFO info;
	info.color=game.player[nr].color;
	stringstream s;
	s<<"("<<nr+1<<") "<<game.player[nr].name<<" "<<pTXT;
	info.txt=s.str();
	game.info.push_back(info);
}
void AddInfo(char* pTXT, DWORD color)
{
	INFO info;
	info.color=color;
	info.txt=pTXT;
	game.info.push_back(info);
}

int getWay_S(int obj)
{
	if (obj<1) return -1;
	int size=(int)game.way_S.size();
	if (size==0) return -1;
	int found=-1;
	for (int i=0; i<size; i++)
	{
		if (obj==game.way_S[i].obj)	found=i;
	}
	return found;
}
int getWay_W(int obj)
{
	if (obj<1) return -1;
	int size=(int)game.way_W.size();
	if (size==0) return -1;
	int found=-1;
	for (int i=0; i<size; i++)
	{
		if (game.way_W[i].disabled==false)
		{
			if (obj==game.way_W[i].obj)	found=i;
		}
	}
	return found;
}
int getTile(int obj)
{
	if (obj<1) return -1;
	int size=game.tiles.size();
	if (size==0) return -1;
	int found=-1;
	for (int i=0; i<size; i++)
		if (obj==game.tiles[i].obj) found=i;
	return found;
}
int getChip(int obj)
{
	if (obj<1) return -1;
	int size=game.tiles.size();
	if (size==0) return -1;
	int found=-1;
	for (int i=0; i<size; i++)
	if (obj==game.tiles[i].chip_obj)
		found=i;
	return found;
}

////////////////////////////////////////////
void Runde_1_Control_Dice( void )
////////////////////////////////////////////
{
	if (game.mode_game!=RUNDE_1_DICE) return;

	//TXT WELCOME
	if (game.mode_txt==TXT_RUNDE_1_WELCOME)
	{
		if ((dbTimer()-game.zeit>0000) && (dbTimer()-game.zeit<3000))
		{
			StartText();
			TextColor(3, dbScreenWidth()/2, 40, 1, "Willkommen zu Neocortex",0xEFFFFFFF);
			TextColor(2, dbScreenWidth()/2, 85, 1, "Siedler von Catan 3D",0xEFFFFFFF);
			EndText();
		}
		if ((dbTimer()-game.zeit>3000) && (dbTimer()-game.zeit<6000))
		{
			StartText();
			TextColor(3, dbScreenWidth()/2, 40, 1, "Runde 1",dbRGB(255,255,255));
			TextColor(2, dbScreenWidth()/2, 85, 1, "Auslosung welcher Spieler beginnen darf.",dbRGB(255,255,255));
			EndText();
		}
		if ((dbTimer()-game.zeit>6000) && (dbTimer()-game.zeit<9000))
		{
			StartText();
			TextColor(3, dbScreenWidth()/2, 40, 1, (char*)game.player[game.n_active_player].name.c_str(),game.player[game.n_active_player].color);
			TextColor(2, dbScreenWidth()/2, 85, 1, "Sie duerfen nun wuerfeln.",dbRGB(255,255,255));
			EndText();
		}
		if (dbTimer()-game.zeit>9000)
		{
			game.mode_txt=TXT_NONE;
			AddInfo("- RUNDE 1 -",0xFFFFFFFF);
			SetActivePlayer(0);
			SetFirstPlayer(0);
			UI_Show_Todo(false);
			UI_Show_TodoDice(true);
			UI_ResetActiveButton();
			UI_Update();
			AddInfo(0,"beginnt.");
		}
	}
	//TXT REDICE
	if (game.mode_txt==TXT_RUNDE_1_REDICE)
	{
		timed_text_1.Hide();
		timed_text_2.Hide();
		timed_text_3.Hide();
		if ((dbTimer()-game.zeit>0100) && (dbTimer()-game.zeit<3000))
		{
			StartText();
			TextColor(3, dbScreenWidth()/2, 40, 1, "Runde 1 - Wiederholung",0xFFFFFFFF);
			TextColor(2, dbScreenWidth()/2, 85, 1, "Mehrere Spieler haben die groesste Augenzahl",0xFFFFFFFF);
			EndText();
		}
		if (dbTimer()-game.zeit>3000)
		{
			game.mode_txt=TXT_NONE;
			AddInfo("- RUNDE 1 Wiederholung -",0xFFFFFFFF);
			SetActivePlayer(0);
			SetFirstPlayer(0);
			UI_Show_Todo(false);
			UI_Show_TodoDice(true);
			UI_ResetActiveButton();
			UI_Update();
		}
	}

	//UI BUTTON DICE 
	if (game.mode_ui==UI_BUTTON_DICE)
	{
		timed_text_1.Hide();
		timed_text_2.Hide();
		timed_text_3.Hide();

		//Wuerfeln
		srand((unsigned int)time(NULL));
		game.n_dice_1=rand()%6+1;
		game.n_dice_2=rand()%6+1;
		game.btn[getBTN("Dice1")].img=game.img_dice[game.n_dice_1-1];
		game.btn[getBTN("Dice2")].img=game.img_dice[game.n_dice_2-1];

		//Update Player Dice
		int n=game.n_active_player;
		int dice=game.n_dice_1+game.n_dice_2;
		game.player[n].dice_1=game.n_dice_1;
		game.player[n].dice_2=game.n_dice_2;
		
		//TEXT :: Player Name
		stringstream s;
		s << "("<<n+1<<")"<<game.player[n].name << " (" << dice << ")";
		game.txt[getTXT("Player1")].txt=s.str();

		//TEXT :: Log
		s.str("");	s << "Wurfelt" << dice;
		AddInfo(n,(char*)s.str().c_str());

		//TEXT :: Timed
		timed_text_1.set(scr.x/2,40,3,1,game.player[n].color,game.player[n].name.c_str(),timer.getTime(),2000);
		s.str(""); s<<"Wurf Ergebnis = "<<dice;
		timed_text_2.set(scr.x/2,80,3,1,0xffffffff,s.str().c_str(),timer.getTime(),2000);

		//UI-Update
		UI_Show_Todo(false);
		UI_Show_TodoDice(false);
		UI_Show_TodoEnd(true);
		UI_ResetActiveButton();
		UI_Update();
	}
	//UI BUTTON ENDTURN
	if (game.mode_ui==UI_BUTTON_ENDTURN)
	{
		timed_text_1.Hide();
		timed_text_2.Hide();
		timed_text_3.Hide();
		AddInfo(game.n_active_player,"beendet");
		Next_Player_Clockwise();

		if (true==IsRoundEnded())
		{
			UI_Show_Todo(false);
		}
		else
		{
			UI_Show_Todo(false);
			UI_Show_TodoDice(true);
			UI_Show_TodoEnd(false);
			UI_ResetActiveButton();
			AddInfo(game.n_active_player,"beginnt");
			
			//Timed Text (1.)
			timed_text_1.set(scr.x/2,40,3,1,game.player[game.n_active_player].color,game.player[game.n_active_player].name.c_str(),timer.getTime(),2000);
			//Timed Text (2.)
			stringstream s; s<<"ist an der Reihe";
			timed_text_2.set(scr.x/2,80,3,1,0xffffffff,s.str().c_str(),timer.getTime(),2000);
		}
		UI_Update();

	}
	//TODO END ROUND
	if (game.mode_todo==TODO_END_ROUND)
	{
		int max=0;
		int max_player=0;
		int max_count=0;
		int count=(int)game.player.size();
		int i;
		// get max. Augen
		for (i=0; i<count; i++)
		{
			// Wenn max kleiner Player Dice1+Dice2
			if(max<game.player[i].dice_1+game.player[i].dice_2)
			{
				max=game.player[i].dice_1+game.player[i].dice_2;
				max_player=i;
			}
		}
		// check if more than one player have max. Augen
		for (i=0; i<count; i++)
		{
			if (max==game.player[i].dice_1+game.player[i].dice_2)
			{
				max_count++;
			}
		}

		if(max_count>1)
		{
			AddInfo("Mehrfach gleiche Augenzahlen",0xFFFFFFFF);
			SetActivePlayer(0);	
			game.mode_txt=TXT_RUNDE_1_REDICE;		//_ASSERTE(game.mode_txt==WELCOME_REDICE);
			game.runde=0;
		}
		else
		{
			stringstream s; s<<game.player[max_player].name<<" hat mit "<<max<<" Augen gewonnen.";
			AddInfo((char*)s.str().c_str(),0xFFFFFFFF);
			SetActivePlayer(max_player);
			SetFirstPlayer(max_player);
			game.mode_game=RUNDE_2_PLACE;
			game.mode_txt=TXT_RUNDE_2_WELCOME;
			game.runde=1;
		}
		UI_Show_Todo(false);
		UI_ResetActiveButton();
		UI_Update();
		game.mode_todo=TODO_NONE;
		game.mode_ui_old=UI_NONE;
		game.zeit=dbTimer();
		game.use_count_1=0;	// Counts placed strassen
		game.use_count_2=0;	// Counts placed siedlungen
	}
}
////////////////////////////////////////////
void Runde_2_Control_Place( void )
////////////////////////////////////////////
{
	if(game.mode_game!=RUNDE_2_PLACE) return;

	//! TXT WELCOME
	if (game.mode_txt==TXT_RUNDE_2_WELCOME)
	{
		timed_text_1.Hide();
		timed_text_2.Hide();
		timed_text_3.Hide();

		if ((dbTimer()-game.zeit>0100) && (dbTimer()-game.zeit<3000))
		{
			StartText();
			TextColor(3, scr.x/2, 40, 1, "Runde 2",0xFFFFFFFF);
			TextColor(2, scr.x/2, 85, 1, "Setzen der Siedlungen und Strassen.",0xFFFFFFFF);
			EndText();
		}
		if ((dbTimer()-game.zeit>3000) && (dbTimer()-game.zeit<6000))
		{
			StartText();
			TextColor(3, scr.x/2, 40, 1, (char*)game.player[game.n_active_player].name.c_str(),game.player[game.n_active_player].color);
			TextColor(2, scr.x/2, 85, 1, "Sie duerfen zuerst setzen.",0xFFFFFFFF);
			EndText();
		}
		if (dbTimer()-game.zeit>6000)
		{
			AddInfo("- RUNDE 2 -",0xFFFFFFFF);
			Player_SetKaufStrasse(-1,1);
			Player_SetKaufSiedlung(-1,1);
			UI_Show_Todo(false);
			UI_ResetActiveButton();
			UI_Update();
			game.mode_txt=TXT_NONE;

			//TEXT :: Log
			AddInfo(game.n_active_player,"beginnt");
		}
	}

	//! UI BUTTON ENDTURN
	if (game.mode_ui==UI_BUTTON_ENDTURN)
	{
		timed_text_1.Hide();
		timed_text_2.Hide();
		timed_text_3.Hide();

		//TEXT :: Log
		int nr=game.n_active_player;
		AddInfo(nr,"beendet");

		if (game.runde==1)	Next_Player_Clockwise();
		if (game.runde==2)	Next_Player_CounterClockwise();
		
		if (IsRoundEnded()==false)
		{
			Player_SetKaufStrasse(-1,1);
			Player_SetKaufSiedlung(-1,1);
		}

		//TEXT :: Log
		nr=game.n_active_player;
		AddInfo(nr,"beginnt");
		stringstream s;

		//TEXT H1
		s.str(""); s<<game.player[nr].name;
		timed_text_1.setFont(2);
		timed_text_1.setColor(game.player[nr].color);
		timed_text_1.setText(s.str().c_str());
		timed_text_1.setTimeAlive(2000);

		//TEXT H2
		s.str(""); s<<"Sie duerfen jetzt setzen";
		timed_text_2.setFont(2);
		timed_text_2.setColor(0xFFFFFFFF);
		timed_text_2.setText(s.str().c_str());
		timed_text_2.setTimeAlive(2000);

		UI_Show_Todo(false);
		UI_ResetActiveButton();
		UI_Update();
		game.use_count_1=0;
		game.use_count_2=0;
	}

	//! TODO END ROUND
	if (game.mode_todo==TODO_END_ROUND)
	{
		UI_Show_Todo(false);
		UI_ResetActiveButton();
		if (game.runde==2)
		{
			Player_SetKaufStrasse(-1,0);
			Player_SetKaufSiedlung(-1,0);
			game.runde=3;
			game.mode_game=RUNDE_3_LOOP;
			game.mode_txt=TXT_RUNDE_3_WELCOME;
			game.zeit=dbTimer();
		}
		if (game.runde==1)
		{
			SetFirstPlayer(game.n_active_player-1);
			SetActivePlayer(game.n_active_player-1);
			Player_SetKaufStrasse(-1,1);
			Player_SetKaufSiedlung(-1,1);
			game.runde=2;
			game.mode_txt=TXT_NONE;
		}
		game.mode_todo=TODO_NONE;
		UI_Update();
	}

	PlaceDelete();
	
	if (game.mode_ui==UI_BUTTON_KAUF_STRASSE)			PlaceStrasse();
	if (game.mode_ui==UI_BUTTON_KAUF_SIEDLUNG)			PlaceSiedlung();
}

////////////////////////////////////////////
void Runde_3_Control_Loop()
////////////////////////////////////////////
{
	if(game.mode_game!=RUNDE_3_LOOP) return;

	if(game.mode_txt==TXT_RUNDE_3_WELCOME)
	{
		timed_text_1.Hide();
		timed_text_2.Hide();
		timed_text_3.Hide();

		if ((dbTimer()-game.zeit>0100) && (dbTimer()-game.zeit<3000))
		{
			StartText();
			TextColor(3, scr.x/2, 40, 1, "Runde 3",0xFFFFFFFF);
			TextColor(2, scr.x/2, 85, 1, "Hauptspiel beginnt.",0xFFFFFFFF);
			EndText();
		}
		if (dbTimer()-game.zeit>3000)
		{
			game.mode_txt=TXT_NONE;
			SetFirstPlayer(0);
			SetActivePlayer(0);
			UI_Show_Todo(false);
			UI_Show_TodoDice(true);
			UI_Update();
			UI_ResetActiveButton();
		}
	}
	
	PlaceDelete();
	if(game.mode_ui==UI_BUTTON_DICE)			Runde_3_Dice();
	if(game.mode_ui==UI_BUTTON_PLAY_CARD)		Runde_3_PlayCard();
	if(game.mode_ui==UI_BUTTON_TRADE_CARD)		Runde_3_TradeCard();
	if(game.mode_ui==UI_BUTTON_BANK)			Runde_3_Bank();
	if(game.mode_ui==UI_BUTTON_ENDTURN)			Runde_3_EndTurn();
	if(game.mode_ui==UI_BUTTON_KAUF_STRASSE)	Runde_3_BuyStrasse();
	if(game.mode_ui==UI_BUTTON_KAUF_SIEDLUNG)	Runde_3_BuySiedlung();
	if(game.mode_ui==UI_BUTTON_KAUF_STADT)		Runde_3_BuyStadt();
	if(game.mode_ui==UI_BUTTON_KAUF_KARTE)		Runde_3_BuyCard();

	if(game.mode_todo==TODO_PLACE_RAUBER)		Runde_3_PlaceRaeuber();
	if(game.mode_todo==TODO_STEEL_CARD)			Runde_3_SteelCard();
	if(game.mode_todo==TODO_LOOSE_HALF_CARDS)	Runde_3_LooseHalfCards();
	if(game.mode_todo==TODO_WIN)				Runde_3_Win();
}

//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
void Runde_3_Dice()
{
	timed_text_1.Hide();
	timed_text_2.Hide();
	timed_text_3.Hide();

	//Wuerfeln
	srand((unsigned int)time(NULL));
	game.n_dice_1=rand()%6+1;
	game.n_dice_2=rand()%6+1;
	game.btn[getBTN("Dice1")].img=game.img_dice[game.n_dice_1-1];
	game.btn[getBTN("Dice2")].img=game.img_dice[game.n_dice_2-1];

	//Update Player Dice
	int n=game.n_active_player;
	int dice=game.player[n].dice_1+game.player[n].dice_2;
	game.player[n].dice_1=game.n_dice_1;
	game.player[n].dice_2=game.n_dice_2;

	//TEXT :: Player Name
	stringstream s;	s << game.player[n].name << " (" << dice << ")";
	game.txt[getTXT("Player1")].txt=s.str();

	//TEXT :: Log
	s.str(""); s<<"Wurfelt "<<dice;
	AddInfo(n,(char*)s.str().c_str());

	//TEXT H1
	s.str(""); s<<game.player[n].name;
	timed_text_1.setFont(2);
	timed_text_1.setColor(game.player[n].color);
	timed_text_1.setText(s.str().c_str());
	timed_text_1.setTimeAlive(2000);

	//TEXT H2
	s.str(""); s<<"Wurf Ergebnis = "<<dice;
	timed_text_2.setFont(2);
	timed_text_2.setColor(0xFFFFFFFF);
	timed_text_2.setText(s.str().c_str());
	timed_text_2.setTimeAlive(2000);

	// Verteile RESSOURCEN	
	if (dice==7)
	{
		game.mode_todo=TODO_PLACE_RAUBER;
	}
	else
	{
		int tile_count=(int)game.tiles.size();
		int t,t_type,w,way_count,windex;
		int bebaut,player;
		int add_value;
		for (t=0; t<tile_count; t++)
		{
			if ((game.tiles[t].chip_wert==dice) && (game.tiles[t].raeuber==false))
			{
				way_count=(int)game.tiles[t].way_W.size();
				if (way_count>0)
				{
					for (w=0; w<way_count; w++)
					{
						add_value=0;						// anzahl ressourcen die addiert werden sollen
						t_type=game.tiles[t].type;		// ressourcen typ ()
						windex=game.tiles[t].way_W[w].obj;
						player=game.way_W[windex].player;
						bebaut=game.way_W[windex].bebaut;
						if (bebaut>0)
						{
							if (bebaut==1)	add_value=1;
							if (bebaut==2)	add_value=2;
							if (t_type==8)	Player_AddErz(player,add_value);
							if (t_type==9)	Player_AddHolz(player,add_value);
							if (t_type==10)	Player_AddLehm(player,add_value);
							if (t_type==11)	Player_AddWeizen(player,add_value);
							if (t_type==12)	Player_AddWolle(player,add_value);
						}
					}
				}
			}
		}
	}
	// CHECKS
	check_Possible_BuyStreet();
	check_Possible_BuySettlement();
	check_Possible_BuyCity();
	check_Possible_BuyCard();
	check_Bank();
							
	//UI-Update
	UI_Show_TodoDice(false);
	UI_Show_TodoEnd(true);
	UI_ResetActiveButton();
	UI_Update();
}
//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
void Runde_3_PlaceRaeuber()
{
		stringstream s,t;
		s<<"Spieler Nr." << game.n_active_player+1;
		t<<game.player[game.n_active_player].name << " sie duerfen den Raueber setzen.";
		MessageBox(NULL,t.str().c_str(),s.str().c_str(),0);
		UI_ResetActiveButton();
		game.mode_todo=TODO_NONE;
}

//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
void Runde_3_SteelCard()
{
	check_Bank();

	UI_Update();
}
//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
void Runde_3_LooseHalfCards()
{
	check_Bank();

	UI_Update();
}
//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
void Runde_3_PlayCard()
{
	check_Bank();

	UI_Update();

}

//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
void Runde_3_TradeCard()
{
	check_Bank();

	UI_Update();

}

//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
void Runde_3_Bank()
{
	check_Bank();

	UI_Update();

}

//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
void Runde_3_EndTurn()
{
	int nr=game.n_active_player;
	timed_text_1.Hide();
	timed_text_2.Hide();
	timed_text_3.Hide();

	AddInfo(nr,"beendet");
	
	Next_Player_Clockwise();

	nr=game.n_active_player;
	AddInfo(nr,"beginnt");


		timed_text_1.setText(game.player[nr].name.c_str());
		timed_text_1.setColor(game.player[nr].color);
		timed_text_1.setTimeAlive(2000);
		timed_text_1.setX(scr.x/2);		
		timed_text_1.setY(40);

		timed_text_2.setText("ist an der Reihe");
		timed_text_2.setColor(0xFFFFFFFF);
		timed_text_2.setTimeAlive(2000);
		timed_text_2.setX(scr.x/2);		
		timed_text_2.setY(85);

	UI_Show_Todo(false);
	UI_Show_TodoDice(true);
	UI_ResetActiveButton();
	check_Bank();

	UI_Update();
}

//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
void Runde_3_Win( void )
{

}

//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
void Runde_3_BuyStrasse()
{
	if (PlaceStrasse()==true)
	{
		int nr=game.n_active_player;
		game.player[nr].nHolz--;
		game.player[nr].nLehm--;
		check_Bank();
		UI_Update();
	}
}

//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
void Runde_3_BuySiedlung()
{
	if (PlaceSiedlung()==true)
	{
		int nr=game.n_active_player;
		game.player[nr].nHolz--;
		game.player[nr].nLehm--;
		game.player[nr].nWeizen--;
		game.player[nr].nWolle--;
		check_Bank();
		UI_Update();
	}
}
//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
void Runde_3_BuyStadt()
{
	if (PlaceStadt()==true)
	{
		//int nr=game.n_active_player;
		//game.player[nr].nErz-=3;
		//game.player[nr].nWeizen-=2;
		check_Bank();
		UI_ResetActiveButton();
		UI_Update();
	}
}
//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
void Runde_3_BuyCard()
{
	check_Bank();

	UI_ResetActiveButton();
	UI_Update();

}
//!/////////////////////////////////////// 
void check_Possible_BuyStreet( void )
//!/////////////////////////////////////// 
{
	int player_count=(int)game.player.size();
	int p;
	int	anz_buy;
	int anz_lehm;
	int anz_holz;
	for (p=0; p<player_count; p++)
	{
		anz_lehm=game.player[p].nLehm;
		anz_holz=game.player[p].nHolz;
		anz_buy=0;
		if ((anz_lehm>=1) && (anz_holz>=1))
		{
			do
			{
				anz_buy++;
				anz_lehm--;
				anz_holz--;
			}
			while((anz_holz>=1) &&(anz_lehm>=1));
		}
		game.player[p].nKaufStrasse=anz_buy;
	}
}
//!/////////////////////////////////////// 
void check_Possible_BuySettlement( void )
//!/////////////////////////////////////// 
{
	int player_count=(int)game.player.size();
	int p;
	int	anz_buy;
	int anz_lehm;
	int anz_holz;
	int anz_weizen;
	int anz_wolle;
	for (p=0; p<player_count; p++)
	{
		anz_lehm=game.player[p].nLehm;
		anz_holz=game.player[p].nHolz;
		anz_wolle=game.player[p].nWolle;
		anz_weizen=game.player[p].nWeizen;
		anz_buy=0;
		if ((anz_lehm>=1) && (anz_holz>=1) && (anz_wolle>=1) && (anz_weizen>=1))
		{
			do
			{
				anz_buy++;
				anz_lehm--;
				anz_holz--;
				anz_wolle--;
				anz_weizen--;
			}
			while((anz_holz>=1) && (anz_lehm>=1) && (anz_wolle>=1) && (anz_weizen>=1));
		}
		game.player[p].nKaufSiedlung=anz_buy;
	}
}
//!/////////////////////////////////////// 
void check_Possible_BuyCity( void )
//!/////////////////////////////////////// 
{
	int player_count=(int)game.player.size();
	int p;
	int	anz_buy;
	int anz_erz;
	int anz_weizen;
	int anz_wolle;
	for (p=0; p<player_count; p++)
	{
		anz_erz=game.player[p].nErz;
		anz_wolle=game.player[p].nWolle;
		anz_weizen=game.player[p].nWeizen;
		anz_buy=0;
		if ((anz_erz>=3) && (anz_wolle>=1) && (anz_weizen>=1))
		{
			do
			{
				anz_buy++;
				anz_erz -= 3;
				anz_wolle--;
				anz_weizen--;
			}
			while((anz_erz>=3) && (anz_wolle>=1) && (anz_weizen>=1));
		}
		game.player[p].nKaufStadt=anz_buy;
	}
}
//!/////////////////////////////////////// 
void check_Possible_BuyCard( void )
//!/////////////////////////////////////// 
{
	int player_count=(int)game.player.size();
	int p;
	int	anz_buy;
	int anz_erz;
	int anz_weizen;
	int anz_wolle;
	for (p=0; p<player_count; p++)
	{
		anz_erz=game.player[p].nErz;
		anz_wolle=game.player[p].nWolle;
		anz_weizen=game.player[p].nWeizen;
		anz_buy=0;
		if ((anz_erz>=1) && (anz_wolle>=1) && (anz_weizen>=1))
		{
			do
			{
				anz_buy++;
				anz_erz--;
				anz_wolle--;
				anz_weizen--;
			}
			while((anz_erz>=1) && (anz_wolle>=1) && (anz_weizen>=1));
		}
		game.player[p].nKaufStadt=anz_buy;
	}
}
//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
void check_Bank()
{
	int nr=game.n_active_player;
	int anz_erz=game.player[nr].nErz;
	int anz_holz=game.player[nr].nHolz;
	int anz_lehm=game.player[nr].nLehm;
	int anz_weizen=game.player[nr].nWeizen;
	int anz_wolle=game.player[nr].nWolle;

	bool b_3zu1=game.player[nr].bHafen3zu1;
	bool b_erz=game.player[nr].bHafenErz;
	bool b_holz=game.player[nr].bHafenHolz;
	bool b_lehm=game.player[nr].bHafenLehm;
	bool b_weizen=game.player[nr].bHafenWeizen;
	bool b_wolle=game.player[nr].bHafenWolle;

	if (anz_erz>=4)		{	UI_Show_TodoBank(true);		return;		}
	if (anz_holz>=4)	{	UI_Show_TodoBank(true);		return;		}
	if (anz_lehm>=4)	{	UI_Show_TodoBank(true);		return;		}
	if (anz_weizen>=4)	{	UI_Show_TodoBank(true);		return;		}
	if (anz_wolle>=4)	{	UI_Show_TodoBank(true);		return;		}

	if (b_3zu1==true)
	{
	if (anz_erz>=3)		{	UI_Show_TodoBank(true);		return;		}
	if (anz_holz>=3)	{	UI_Show_TodoBank(true);		return;		}
	if (anz_lehm>=3)	{	UI_Show_TodoBank(true);		return;		}
	if (anz_weizen>=3)	{	UI_Show_TodoBank(true);		return;		}
	if (anz_wolle>=3)	{	UI_Show_TodoBank(true);		return;		}
	}

	if (b_erz==true)		{	if (anz_erz>=2)		{	UI_Show_TodoBank(true);		return;		}	}
	if (b_holz==true)		{	if (anz_holz>=2)	{	UI_Show_TodoBank(true);		return;		}	}
	if (b_lehm==true)		{	if (anz_lehm>=2)	{	UI_Show_TodoBank(true);		return;		}	}
	if (b_weizen==true)		{	if (anz_weizen>=2)	{	UI_Show_TodoBank(true);		return;		}	}
	if (b_wolle==true)		{	if (anz_wolle>=2)	{	UI_Show_TodoBank(true);		return;		}	}

	UI_Show_TodoBank(false);
}
//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
bool check_Way_W_has_Hafen3zu1(int way_index)
{
	// Waycount
	int way_count=(int)game.way_W.size();

	// Abbruchbedingung
	if((way_index<0) || (way_index>=way_count)) return false;

	// Tilecount
	int tile_count=(int)game.tiles.size();

	// Loop Tiles von Way W
	int next_count=(int)game.way_W[way_index].next_T.size();

	// Abbruchbedingung
	if (next_count<=0) return false;

	// Loop Next_Tiles
	int n, tile_index;
	for (n=0; n<next_count; n++)
	{
		tile_index=game.way_W[way_index].next_T[n];
		if ((tile_index>=0) && (tile_index<tile_count))
		{
			if(game.tiles[tile_index].type==1) return true;
		}
	}
	return false;
}
//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
bool check_Way_W_has_HafenErz(int way_index)
{
	// Waycount
	int way_count=(int)game.way_W.size();

	// Abbruchbedingung
	if((way_index<0) || (way_index>=way_count)) return false;

	// Tilecount
	int tile_count=(int)game.tiles.size();

	// Loop Tiles von Way W
	int next_count=(int)game.way_W[way_index].next_T.size();

	// Abbruchbedingung
	if (next_count<=0) return false;

	// Loop Next_Tiles
	int n, tile_index;
	for (n=0; n<next_count; n++)
	{
		tile_index=game.way_W[way_index].next_T[n];
		if ((tile_index>=0) && (tile_index<tile_count))
		{
			if(game.tiles[tile_index].type==2) return true;
		}
	}
	return false;
}
//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
bool check_Way_W_has_HafenHolz(int way_index)
{
	// Waycount
	int way_count=(int)game.way_W.size();

	// Abbruchbedingung
	if((way_index<0) || (way_index>=way_count)) return false;

	// Tilecount
	int tile_count=(int)game.tiles.size();

	// Loop Tiles von Way W
	int next_count=(int)game.way_W[way_index].next_T.size();

	// Abbruchbedingung
	if (next_count<=0) return false;

	// Loop Next_Tiles
	int n, tile_index;
	for (n=0; n<next_count; n++)
	{
		tile_index=game.way_W[way_index].next_T[n];
		if ((tile_index>=0) && (tile_index<tile_count))
		{
			if(game.tiles[tile_index].type==3) return true;
		}
	}
	return false;
}
//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
bool check_Way_W_has_HafenLehm(int way_index)
{
	// Waycount
	int way_count=(int)game.way_W.size();

	// Abbruchbedingung
	if((way_index<0) || (way_index>=way_count)) return false;

	// Tilecount
	int tile_count=(int)game.tiles.size();

	// Loop Tiles von Way W
	int next_count=(int)game.way_W[way_index].next_T.size();

	// Abbruchbedingung
	if (next_count<=0) return false;

	// Loop Next_Tiles
	int n, tile_index;
	for (n=0; n<next_count; n++)
	{
		tile_index=game.way_W[way_index].next_T[n];
		if ((tile_index>=0) && (tile_index<tile_count))
		{
			if(game.tiles[tile_index].type==4) return true;
		}
	}
	return false;
}
//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
bool check_Way_W_has_HafenWeizen(int way_index)
{
	// Waycount
	int way_count=(int)game.way_W.size();

	// Abbruchbedingung
	if((way_index<0) || (way_index>=way_count)) return false;

	// Tilecount
	int tile_count=(int)game.tiles.size();

	// Loop Tiles von Way W
	int next_count=(int)game.way_W[way_index].next_T.size();

	// Abbruchbedingung
	if (next_count<=0) return false;

	// Loop Next_Tiles
	int n, tile_index;
	for (n=0; n<next_count; n++)
	{
		tile_index=game.way_W[way_index].next_T[n];
		if ((tile_index>=0) && (tile_index<tile_count))
		{
			if(game.tiles[tile_index].type==5) return true;
		}
	}
	return false;
}
//!/////////////////////////////////////// 
//!
//!
//!///////////////////////////////////////
bool check_Way_W_has_HafenWolle(int way_index)
{
	// Waycount
	int way_count=(int)game.way_W.size();

	// Abbruchbedingung
	if((way_index<0) || (way_index>=way_count)) return false;

	// Tilecount
	int tile_count=(int)game.tiles.size();

	// Loop Tiles von Way W
	int next_count=(int)game.way_W[way_index].next_T.size();

	// Abbruchbedingung
	if (next_count<=0) return false;

	// Loop Next_Tiles
	int n, tile_index;
	for (n=0; n<next_count; n++)
	{
		tile_index=game.way_W[way_index].next_T[n];
		if ((tile_index>=0) && (tile_index<tile_count))
		{
			if(game.tiles[tile_index].type==6) return true;
		}
	}
	return false;
}


////////////////////////////////////////////
void PlaceDelete()
////////////////////////////////////////////
{
		//NONE
	if (game.mode_ui==UI_NONE)
	{
		if (game.mode_ui_old!=UI_NONE)
		{
			mouse.CALC_CUT_WITH_XZ=false;
			if (IsObject(game.use_obj)==true) dbDeleteObject(game.use_obj);
			game.mode_ui_old=UI_NONE;
			Show_Waypoint_S(0);
			Show_Waypoint_W(0);
		}
	}

}
////////////////////////////////////////////
bool PlaceStrasse()
////////////////////////////////////////////
{
	bool did_it=false;

	if (game.mode_ui_old==UI_NONE)					game.mode_object=OBJECT_INIT;
	if (game.mode_ui_old==UI_BUTTON_KAUF_STRASSE)	game.mode_object=OBJECT_LOOP;
	if (game.mode_ui_old==UI_BUTTON_KAUF_SIEDLUNG)	game.mode_object=OBJECT_DELETE;
	if (game.mode_ui_old==UI_BUTTON_KAUF_STADT)		game.mode_object=OBJECT_DELETE;
	
	if (game.mode_object==OBJECT_INIT)
	{
		mouse.CALC_CUT_WITH_XZ=true;
		game.use_obj=MakeObjectStrasse(0.0f,0.0f,0.0f,game.player[game.n_active_player].tex_holz);
		game.mode_ui_old=UI_BUTTON_KAUF_STRASSE;		
		Show_Waypoint_S(1);
	}
	if (game.mode_object==OBJECT_DELETE)
	{
		mouse.CALC_CUT_WITH_XZ=false;
		if (IsObject(game.use_obj)==true) dbDeleteObject(game.use_obj);
		game.mode_ui_old=UI_NONE;
		Show_Waypoint_W(0);
	}
	
	if (game.mode_object==OBJECT_LOOP)
	{
		StartText();
		TextColor(3,scr.x/2,40,1,"Platziere Strasse...",0xD0FFFFFF);
		EndText();
		int index=getWay_S(game.pick.obj);
		if (index>=0)
		{
			if (IsObject(game.use_obj_2)==false)
			{
				game.use_obj_2=game.way_S[index].obj;
				if (IsObject(game.use_obj_2)==true) dbGhostObjectOn(game.use_obj_2);
			}
			dbYRotateObject(game.use_obj,(float)game.way_S[index].winkel);
			dbPositionObject(game.use_obj,game.way_S[index].x,game.way_S[index].y,game.way_S[index].z);
			if (mouse.c==1)
			{
				if(keys[2]==false)
				{	
					keys[2]=true;
					if (game.way_S[index].bebaut==0) 	
					{
						int  nr=game.n_active_player;
						int   t=game.player[nr].tex_holz;
						float w=(float)game.way_S[index].winkel;
						float x=game.way_S[index].x;
						float y=game.way_S[index].y;
						float z=game.way_S[index].z;
						int obj=MakeObjectStrasse(x,y,z,t);
						dbYRotateObject(obj,w);
						game.way_S[index].obj=obj;
						game.way_S[index].bebaut=1;
						game.way_S[index].player=nr;
						if (IsObject(game.use_obj)==true) dbDeleteObject(game.use_obj);
						if (IsObject(game.use_obj_2)==true) dbDeleteObject(game.use_obj_2);
						game.player[nr].nStrasse++;
						game.use_count_1++;

						if ((game.use_count_1==1) && (game.use_count_2==1)) 
						{
							UI_Show_TodoEnd(1);
						}
						Player_SetKaufStrasse(-1,0);
						UI_Update();
						UI_ResetActiveButton();
						AddInfo(nr,"baut Strasse");
						did_it=true;
					}
				}
			}
			else
			{
				keys[2]=false;
			}
		}
		else
		{
			if (IsObject(game.use_obj_2)==true)
			{
				dbGhostObjectOff(game.use_obj_2);
				game.use_obj_2=-1;
			}
			dbYRotateObject(game.use_obj,0.0f);
			dbPositionObject(game.use_obj,mouse.SchnittXZEbene.x,mouse.SchnittXZEbene.y,mouse.SchnittXZEbene.z);
		}
	}
	return did_it;
}
////////////////////////////////////////////
bool PlaceSiedlung()
////////////////////////////////////////////
{
	bool did_it=false;

	if (game.mode_ui_old==UI_NONE)					game.mode_object=OBJECT_INIT;
	if (game.mode_ui_old==UI_BUTTON_KAUF_STRASSE)	game.mode_object=OBJECT_DELETE;
	if (game.mode_ui_old==UI_BUTTON_KAUF_SIEDLUNG)	game.mode_object=OBJECT_LOOP;
	if (game.mode_ui_old==UI_BUTTON_KAUF_STADT)		game.mode_object=OBJECT_DELETE;

	if (game.mode_object==OBJECT_INIT)
	{
		mouse.CALC_CUT_WITH_XZ=true;
		game.use_obj=MakeObjectSiedlung(0.0f,0.0f,0.0f,game.player[game.n_active_player].tex_holz);
		game.mode_ui_old=UI_BUTTON_KAUF_SIEDLUNG;		
		Show_Waypoint_W(1);
	}

	if (game.mode_object==OBJECT_DELETE)
	{
		mouse.CALC_CUT_WITH_XZ=false;
		if (IsObject(game.use_obj)==true) dbDeleteObject(game.use_obj);
		game.mode_ui_old=UI_NONE;
		Show_Waypoint_S(0);
	}

	if (game.mode_object==OBJECT_LOOP)
	{
		StartText();
		TextColor(3,scr.x/2,40,1,"Platziere Siedlung...",0xD0FFFFFF);
		EndText();

		int index=getWay_W(game.pick.obj);
		if (index>=0)
		{
			//drawInfo_WaypointSiedlung(index,mouse.x+20,mouse.y+20,1,0,dbRGB(0,0,0),dbRGB(255,255,0));
			if (IsObject(game.use_obj_2)==false)
			{
				game.use_obj_2=game.way_W[index].obj;
				if (IsObject(game.use_obj_2)==true) dbGhostObjectOn(game.use_obj_2);
			}
			dbPositionObject(game.use_obj,game.way_W[index].x,game.way_W[index].y,game.way_W[index].z);
			if (mouse.c==1)
			{
				if(keys[2]==false)
				{	
					keys[2]=true;
					// Wenn ausgewählt, prüfe ob bebaut==0 und disabled==false
					if (game.way_W[index].disabled==false)
					{
						if (game.way_W[index].bebaut==0) 	
						{
							int	 nr=game.n_active_player;
							int   t=game.player[nr].tex_holz;
							float x=game.way_W[index].x;
							float y=game.way_W[index].y;
							float z=game.way_W[index].z;
							int obj=MakeObjectSiedlung(x,y,z,t);
							game.way_W[index].obj=obj;
							game.way_W[index].bebaut=1;
							game.way_W[index].player=nr;
							if (IsObject(game.use_obj)==true) dbDeleteObject(game.use_obj);
							if (IsObject(game.use_obj_2)==true) dbDeleteObject(game.use_obj_2);
							game.player[nr].nSiedlung++;
							game.player[nr].nSiegpunkte++;
							game.use_count_2++;
							Player_SetKaufSiedlung(-1,0);
							bool has=false;
							has=check_Way_W_has_Hafen3zu1(index);	if(has==true) game.player[nr].bHafen3zu1=true;
							has=check_Way_W_has_HafenErz(index);	if(has==true) game.player[nr].bHafenErz=true;
							has=check_Way_W_has_HafenHolz(index);	if(has==true) game.player[nr].bHafenHolz=true;
							has=check_Way_W_has_HafenLehm(index);	if(has==true) game.player[nr].bHafenLehm=true;
							has=check_Way_W_has_HafenWeizen(index);	if(has==true) game.player[nr].bHafenWeizen=true;
							has=check_Way_W_has_HafenWolle(index);	if(has==true) game.player[nr].bHafenWolle=true;

							if ((game.use_count_1==1) && (game.use_count_2==1)) 
							UI_Show_TodoEnd(1);

							UI_Update();
							UI_ResetActiveButton();
							AddInfo(nr,"baut Siedlung");

							did_it=true;
							// suche die nachbarn und deaktiviere sie
							int c=(int)game.way_W[index].next_W.size();
							if (c>0)
							{
								int w;
								for(w=0; w<c; w++)
								{
									game.way_W[game.way_W[index].next_W[w]].disabled=true;
								}
							}
							Show_Waypoint_W(1);
						}
						else
						{
							MessageBox(NULL,"Dieses Feld ist schon bebaut.","Fehler",0);
						}
					}
					else
					{
						MessageBox(NULL,"Dieses Feld ist nicht bebaubar.","Fehler",0);
					}
				}
			}
			else
			{
				keys[2]=false;
			}
		}
		else
		{
			if (IsObject(game.use_obj_2)==true)
			{
				dbGhostObjectOff(game.use_obj_2);
				game.use_obj_2=-1;
			}
			dbPositionObject(game.use_obj,mouse.SchnittXZEbene.x,mouse.SchnittXZEbene.y,mouse.SchnittXZEbene.z);
		}
	}
	return did_it;
}
////////////////////////////////////////////
bool PlaceStadt()
////////////////////////////////////////////
{
	return true;
}

