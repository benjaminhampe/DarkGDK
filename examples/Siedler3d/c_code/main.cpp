// ****************************
// Bennis Siedler von Catan 3D
// ****************************
#include "main.h"

#include "stdafx.h"
#include "DarkGDK.h"

#include "_game_control.h"
#include "_game_types.h"
#include "_cl.h"

#include "thc_text.h"
#include "thc_camera.h"
#include "thc_mouse.h"
#include "thc_log.h"
#include "thc_is.h"
#include "thc_delete.h"
#include "thc_desktop.h"
#include "thc_vertex.h"
#include "thc_vector.h"
#include "thc_mesh.h"
#include "thc_object.h"
#include "thc_backbuffer.h"
#include "thc_skybox.h"

#include "thc_memblock.h"
#include "thc_memblock_painting.h"
#include "thc_memblock_floodfill.h"
#include "thc_image.h"

using namespace thc;

GAME			game;
bool*			keys=new bool[256];
Integer3		scr={0,0,0};
string			app_dir="";
string			app_title="";
stringstream	info("");


void DarkGDK ( void )
{
	// LOGGING BEGIN
	//out_init();

	// APPLICATION DIR
	app_dir=dbGetDir();
	//out(app_dir);

	// Main Window
	dbFlushVideoMemory();
	dbSetWindowOn();
	dbSetWindowLayout(1,1,1);
	dbSetWindowTitle("Siedler3D (2007) von _Neo_Cortex");
	dbSetWindowPosition(100,100);
	dbSetDisplayMode(800,600,32);
	dbSyncOff();
	dbSyncOn();
	dbSyncRate(0);
	scr.x=dbScreenWidth();
	scr.y=dbScreenHeight();
	scr.z=dbScreenDepth();

	/*	ImageTest
	int mb0=MemblockFromColor(512,512,0xFF000000);
			MemblockDrawBoxA(mb0,5,5,440,400,0xFFFF0000);
			MemblockDrawBoxA(mb0,200,300,440,400,0xFFFF00FF);
			MemblockDrawBoxA(mb0,100,200,240,300,0xFF0000FF);

			MemblockSave("_save_rgb_0.png",mb0);
			MemblockFloodFill(mb0, 20, 20, 0xFFFFFF00, 0xFFFF0000);
			MemblockSave("_save_rgb_1.png",mb0);
			MemblockDelete(mb0);	
	*/

	THC_Skybox skybox;
	skybox.load("media\\gfx\\skybox\\skybox.ini");

	// Backdrop
	dbBackdropOn();
	dbColorBackdrop(0xFFFFFFFF);

	// Text Settings
	dbInk(0xFFFFFFFF,0xFFFFFFFF);
	dbDrawToFront();
	
	// Cloggys Text Funktionen
	InitTextD3D();
	SetFont(1,"Comic Sans MS",10,0,0,0);
	SetFont(2,"Comic Sans MS",20,1,0,0);
	SetFont(3,"Comic Sans MS",30,1,0,0);
	SetFont(4,"New Courier",10,1,0,0);
	SetFont(5,"Arial",9,0,0,0);
	SetFont(6,"Arial",12,0,0,0);

	// Camera Settings
	dbAutoCamOff();
	dbSetCameraRange(0,1.0f,100000.0f);
	camera.x=86.0f;
	camera.y=4241.0f;
	camera.z=-3300.0f;
	dbPositionCamera(0,camera.x,camera.y,camera.z);
	camera.point.x=0.0f;
	camera.point.y=0.0f;
	camera.point.z=0.0f;
	dbPointCamera(0,camera.point.x,camera.point.y,camera.point.z);
	camera.a=dbCameraAngleX(0);
	camera.b=dbCameraAngleY(0);
	camera.c=dbCameraAngleZ(0);
	SetCameraActive(true);

	/* Tetraeder Object Test
	Float3 A={0.0f,20.0f,0.0f};
	Float3 B={-10.0f,-10.0f,-10.0f};
	Float3 C={10.0f,-5.0f,-5.0f};
	Float3 D={0.0f,-10.0f,15.0f};

	int mem=MemblockCreate(12+12*36);
			MemblockHeader(mem,338,36,12);
			WriteVertexTetraeder(mem,12, 0.0f, 0.0f, 0.0f, A, B, C, D);

	int obj=ObjectFromMeshMemblock(mem,0);
			MemblockDelete(mem);
			dbSetObject(obj,1,0,0,2,0,0,0);

	stringstream caption;
	while ( LoopGDK ( ) )
	{
		if (dbEscapeKey()==1) return;

		//dbPasteImage(img,(scr.x-512)>>1,(scr.y-512)>>1,1);
		//dbBox(5,5,380,400,0x80FF0000,0x80FF0000,0x80FF0000,0x80FF0000);
		//dbBox(260,50,500,360,0x8000FF00,0x8000FF00,0x8000FF00,0x8000FF00);
		//dbBox(100,200,380,500,0x800000FF,0x800000FF,0x800000FF,0x800000FF);

		//dbRotateObject(obj,dbWrapValue(dbObjectAngleX(obj)+1.0f),dbWrapValue(dbObjectAngleY(obj)+1.0f),0.0f);
		caption.str("");
		caption<<"FPS = "<<dbScreenFPS();
		dbSetWindowTitle((char*)caption.str().c_str());
		dbSync ( );
	}
	*/

	// IntroText 1 (vor dem Laden des Spieles)
	dbSync();
	StartText();
		TextColor(6,5,scr.y-30,0,"Laden...",0xFFFFFFFF);
	EndText();

	// IntroImage 1 (vor dem Laden des Spieles)	
	int intro=ImageLoad("media\\gfx\\intro\\bush.png",1);
	if (IsImage(intro)==1) dbPasteImage(intro,(scr.x-442)/2,0,0);		dbSync();
	if (IsImage(intro)==1) dbDeleteImage(intro);

	// Spiel Laden...
	Game_Init();

	// IntroText 1 (vor dem Laden des Spieles)
	dbSync();
	StartText();
		TextColor(6,5,scr.y-30,0,"Fertig...",0xFFFFFFFF);
	EndText();

	// IntroImage 2 (nach dem Laden des Spieles)
	int intro_mem0=MemblockLoad("media\\gfx\\intro\\intro.JPG",1);
	int intro_mem1=MemblockScale(intro_mem0,scr.x,scr.y);
	MemblockDelete(intro_mem0);
	intro=ImageFromMemblock(intro_mem1);
	MemblockDelete(intro_mem1);
	if (IsImage(intro)==1) dbPasteImage(intro,0,0,0);
	dbSync();
	if (IsImage(intro)==1) dbDeleteImage(intro);


	DWORD pixel=0xFF000000;
	stringstream pixel_txt;
	dbColorBackdrop(dbRGB(0,0,0));	


	while ( LoopGDK ( ) )
	{
		if (dbEscapeKey()==1) 
		{
			int result=MessageBox(NULL,"Wollen sie das Programm beenden?","Siedler von Catan Exit.",4);
			if (result==6) return;
		}

		Game_Control();

		backbufferLOCK();
		pixel=backbufferGetPixel(mouse.x,mouse.y);
		backbufferUNLOCK();
		/*
		pixel_txt.str("");
		pixel_txt<<"Pixel = ("<<RGBA_R(pixel);
		pixel_txt<<","<<RGBA_G(pixel);
		pixel_txt<<","<<RGBA_B(pixel);
		pixel_txt<<","<<RGBA_A(pixel)<<")";

		StartText();
		TextColor(2,mouse.x+20,mouse.y+20,0,(char*)pixel_txt.str().c_str(),0xFFFFFFFF);
		EndText();
		
		backbufferLOCK();
		pixel=backbufferGetPixel(mouse.x,mouse.y);
		if (mouse.c==1)
		{
			backbufferDrawLine(0, 0, mouse.x, mouse.y, 0xFFFFFF00);
			backbufferDrawLine(0, scr.y, mouse.x, mouse.y, 0xFFFFFF00);
			backbufferDrawLine(scr.x, 0, mouse.x, mouse.y, 0xFFFFFF00);
			backbufferDrawLine(scr.x, scr.y, mouse.x, mouse.y, 0xFFFFFF00);
		}
		backbufferUNLOCK();
		*/

		dbSync ( );
	}
	Game_Delete();
	//delete [] fiFont;
	//delete [] keys;


}