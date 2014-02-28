// _ui_create.cpp


#include "_ui_create.h"
#include "_game_types.h"

#include "stdafx.h"
#include "DarkGDK.h"
#include "main.h"

#include "thc_memblock.h"
#include "thc_image.h"
#include "thc_delete.h"

using namespace thc;


//.................................................................................................
void UI_Create()
{
	stringstream s;
	int img,mem;
	BUTTON btn;
	STATIC_TEXT txt;
	txt.color=0xFFFFFFFF;

	game.btn.resize(0);
	game.txt.resize(0);


	//BUTTON/////////////////////BAULISTE/////////////////////////////////////////
	btn.name="Bauliste";
	btn.info="";
	btn.bInfo=false;
	btn.bActive=false;
	btn.bVisible=false;
	btn.type=0;
	btn.dx=276;
	btn.dy=394;
	btn.x=(scr.x-btn.dx)/2;
	btn.y=(scr.y-btn.dy)/2;
	mem=MemblockLoad("media\\gfx\\textures\\img_bauliste.png",1);
	img=MemblockSetColorKey(mem,dbRGB(255,0,255));
	btn.img=ImageFromMemblock(img);
	MemblockDelete(mem);
	MemblockDelete(img);
	game.btn.push_back(btn);

	//BUTTON/////////////////////ZWEI WÜRFEL/////////////////////////////////////////
	btn.name="Dice1";	
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=true;
	btn.bActive=false;		
	btn.type=0;
	btn.x=scr.x-100;
	btn.y=5;
	btn.dx=45;
	btn.dy=45;	
	btn.img=0;								game.btn.push_back(btn);
	
	btn.name="Dice2";	
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=true;
	btn.bActive=false;		
	btn.type=0;
	btn.x=scr.x-50;
	btn.y=5;
	btn.dx=45;
	btn.dy=45;
	btn.img=0;								game.btn.push_back(btn);

	//TODO (0.) DICE ///////////////////////////////////////////////////////////////////////////////////
	btn.name="Todo Dice"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.x=scr.x/2-190;	
	btn.y=1;	
	btn.dx=68;	
	btn.dy=28;
	btn.img=ImageLoad("media\\gfx\\todo\\todo_wuerfel.png",1);		game.btn.push_back(btn);

	//TODO (1.) Play Card //////////////////////////////////////////////////////////////////////////////
	btn.name="Todo Play Card"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.x=scr.x/2-112;	
	btn.y=1;	
	btn.dx=68;	
	btn.dy=28;
	btn.img=ImageLoad("media\\gfx\\todo\\todo_playcard.png",1);		game.btn.push_back(btn);

	//TODO (2.) Trade Card //////////////////////////////////////////////////////////////////////////////
	btn.name="Todo Trade Card"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.x=scr.x/2-34;	
	btn.y=1;	
	btn.dx=68;	
	btn.dy=28;
	btn.img=ImageLoad("media\\gfx\\todo\\todo_trade.png",1);			game.btn.push_back(btn);

	//TODO (3.) Bank //////////////////////////////////////////////////////////////////////////////
	btn.name="Todo Bank"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.x=scr.x/2+44;	
	btn.y=1;	
	btn.dx=68;	
	btn.dy=28;
	btn.img=ImageLoad("media\\gfx\\todo\\todo_bank.png",1);			game.btn.push_back(btn);

	//TODO (4.) End Turn //////////////////////////////////////////////////////////////////////////////
	btn.name="Todo End Turn"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.x=scr.x/2+122;	
	btn.y=1;	
	btn.dx=68;	
	btn.dy=28;
	btn.img=ImageLoad("media\\gfx\\todo\\todo_endturn.png",1);		game.btn.push_back(btn);

	//TODO (9.) Undo //////////////////////////////////////////////////////////////////////////////
	btn.name="Todo Undo"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.x=scr.x/2-233;	
	btn.y=1;	
	btn.dx=33;	
	btn.dy=28;
	mem=MemblockLoad("media\\gfx\\todo\\todo_undo.png",1);
	img=MemblockSetColorKey(mem,dbRGB(255,255,0));	
	btn.img=ImageFromMemblock(img); 
	MemblockDelete(mem); 
	MemblockDelete(img);															game.btn.push_back(btn);

	//TODO (5.) Kauf Strasse //////////////////////////////////////////////////////////////////////////////
	btn.name="Kauf Strasse";															
	btn.info="";																		
	btn.bInfo=false;																	
	btn.bVisible=false;													
	btn.bActive=false;	
	btn.type=0;
	btn.x=317;	
	btn.y=scr.y-69;	
	btn.dx=64;	
	btn.dy=64;
	mem=MemblockLoad("media\\gfx\\todo\\todo_kauf_strasse.png",1);
	img=MemblockSetColorKey(mem,dbRGB(255,0,255));
	btn.img=ImageFromMemblock(img); 
	MemblockDelete(mem); 
	MemblockDelete(img);															game.btn.push_back(btn);

	txt.name=btn.name;
	txt.txt="0";
	txt.visible=false;
	txt.x=btn.x+btn.dx/2;
	txt.y=btn.y-20;																game.txt.push_back(txt);

	//TODO (6.) Kauf Siedlung //////////////////////////////////////////////////////////////////////////////
	btn.name="Kauf Siedlung"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=true;
	btn.bActive=false;	
	btn.type=0;
	btn.x=386;	
	btn.y=scr.y-69;	
	btn.dx=64;	
	btn.dy=64;
	mem=MemblockLoad("media\\gfx\\todo\\todo_kauf_siedlung.png",1);
	img=MemblockSetColorKey(mem,dbRGB(255,0,255));
	btn.img=ImageFromMemblock(img); 
	MemblockDelete(mem); 
	MemblockDelete(img);															game.btn.push_back(btn);

	txt.name=btn.name;
	txt.txt="0";
	txt.visible=false;
	txt.x=btn.x+btn.dx/2;
	txt.y=btn.y-20;																game.txt.push_back(txt);

	//TODO (7.) Kauf Stadt //////////////////////////////////////////////////////////////////////////////
	btn.name="Kauf Stadt"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.x=455;	
	btn.y=scr.y-69;	
	btn.dx=64;	
	btn.dy=64;
	mem=MemblockLoad("media\\gfx\\todo\\todo_kauf_stadt.png",1);
	img=MemblockSetColorKey(mem,dbRGB(255,0,255));
	btn.img=ImageFromMemblock(img); 
	MemblockDelete(mem); 
	MemblockDelete(img);															game.btn.push_back(btn);

	txt.name=btn.name;
	txt.txt="0";
	txt.visible=false;
	txt.x=btn.x+btn.dx/2;
	txt.y=btn.y-20;																game.txt.push_back(txt);

	//TODO (8.) Kauf Ereigniskarte //////////////////////////////////////////////////////////////////////////////
	btn.name="Kauf Ereigniskarte"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.x=524;	
	btn.y=scr.y-67;	
	btn.dx=40;	
	btn.dy=60;
	mem=MemblockLoad("media\\gfx\\todo\\todo_kauf_ereignis_karte.png",1);
	img=MemblockSetColorKey(mem,dbRGB(255,0,255));
	btn.img=ImageFromMemblock(img); 
	MemblockDelete(mem); 
	MemblockDelete(img);														game.btn.push_back(btn);

	txt.name=btn.name;
	txt.txt="0";
	txt.visible=false;
	txt.x=btn.x+btn.dx/2;
	txt.y=btn.y-20;															game.txt.push_back(txt);

	//ROHSTOFF (0.) Erz //////////////////////////////////////////////////////////////////////////////
	btn.name="Anzahl Erz"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.x=5;	
	btn.y=scr.y-65;	
	btn.dx=40;	
	btn.dy=60;
	btn.img=ImageLoad("media\\gfx\\karten\\karte_erz.png",1);	game.btn.push_back(btn);

	txt.name=btn.name;
	txt.txt="0";
	txt.visible=false;
	txt.x=btn.x+btn.dx/2;
	txt.y=btn.y-20;															game.txt.push_back(txt);

	//ROHSTOFF (1.) Holz //////////////////////////////////////////////////////////////////////////////
	btn.name="Anzahl Holz"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.x=50;	
	btn.y=scr.y-65;	
	btn.dx=40;	
	btn.dy=60;
	btn.img=ImageLoad("media\\gfx\\karten\\karte_holz.png",1);	game.btn.push_back(btn);

	txt.name=btn.name;
	txt.txt="0";
	txt.visible=false;
	txt.x=btn.x+btn.dx/2;
	txt.y=btn.y-20;															game.txt.push_back(txt);

	//ROHSTOFF (2.) Lehm //////////////////////////////////////////////////////////////////////////////
	btn.name="Anzahl Lehm"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.x=95;	
	btn.y=scr.y-65;	
	btn.dx=40;	
	btn.dy=60;
	btn.img=ImageLoad("media\\gfx\\karten\\karte_lehm.png",1);	game.btn.push_back(btn);

	txt.name=btn.name;
	txt.txt="0";
	txt.visible=false;
	txt.x=btn.x+btn.dx/2;
	txt.y=btn.y-20;															game.txt.push_back(txt);

	//ROHSTOFF (3.) Weizen //////////////////////////////////////////////////////////////////////////////
	btn.name="Anzahl Weizen"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.x=140;
	btn.y=scr.y-65;	
	btn.dx=40;	
	btn.dy=60;
	btn.img=ImageLoad("media\\gfx\\karten\\karte_weizen.png",1); game.btn.push_back(btn);

	txt.name=btn.name;
	txt.txt="0";
	txt.visible=false;
	txt.x=btn.x+btn.dx/2;
	txt.y=btn.y-20;															game.txt.push_back(txt);

	//ROHSTOFF (4.) Wolle //////////////////////////////////////////////////////////////////////////////
	btn.name="Anzahl Wolle"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.x=185;	
	btn.y=scr.y-65;	
	btn.dx=40;	
	btn.dy=60;
	btn.img=ImageLoad("media\\gfx\\karten\\karte_wolle.png",1);	game.btn.push_back(btn);

	txt.name=btn.name;
	txt.txt="0";
	txt.visible=false;
	txt.x=btn.x+btn.dx/2;
	txt.y=btn.y-20;															game.txt.push_back(txt);

	//BONUS (0.) Rittermacht //////////////////////////////////////////////////////////////////////////////
	btn.name="Bonus Rittermacht"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.dx=128;	
	btn.dy=128;
	btn.x=scr.x-btn.dx;	
	btn.y=128;	
	mem=MemblockLoad("media\\gfx\\karten\\bonus_rittermacht.PNG",1);
	img=MemblockSetColorKey(mem,dbRGB(255,0,255));
	btn.img=ImageFromMemblock(img); 
	MemblockDelete(mem); 
	MemblockDelete(img);														game.btn.push_back(btn);
	
	//BONUS (1.) Handelsstrasse //////////////////////////////////////////////////////////////////////////////
	btn.name="Bonus Handelsstrasse"; 
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;	
	btn.dx=128;	
	btn.dy=128;
	btn.x=scr.x-btn.dx;	
	btn.y=256;	
	mem=MemblockLoad("media\\gfx\\karten\\bonus_handelsstrasse.PNG",1);
	img=MemblockSetColorKey(mem,dbRGB(255,0,255));
	btn.img=ImageFromMemblock(img); 
	MemblockDelete(mem); 
	MemblockDelete(img);														game.btn.push_back(btn);

	//EREIGNIS (0.) Ritter //////////////////////////////////////////////////////////////////////////////
	btn.name="Ritterkarte";	
	btn.type=0;	
	s.str("");
	s << "Ritterkarte" << endl;
	s << "Sie koennen den Raeuber neusetzen,"<<endl;
	s << "und von einem Spieler, der an dem Feld" << endl;
	s << "eine Siedlung oder eine Stadt besitzt" << endl;
	s << "genau eine Rohstoffkarte ziehen.";
	btn.info=s.str();
	btn.bInfo=true;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.x=scr.x-225;	
	btn.y=scr.y-105;	
	btn.dx=70;	
	btn.dy=100;
	btn.img=ImageLoad("media\\gfx\\karten\\karte_ritter.png",1);	game.btn.push_back(btn);

	txt.name=btn.name;
	txt.txt="0";
	txt.visible=false;
	txt.x=btn.x+btn.dx/2;
	txt.y=btn.y-20;																game.txt.push_back(txt);

	//EREIGNIS (1.) Siegpunkt //////////////////////////////////////////////////////////////////////////////
	btn.name="Siegpunktkarte";	
	btn.type=1;	
	s.str("");
	s << "Siegpunkt" << endl;
	s << "Sie erhalten einen zusaetzlichen"<<endl;
	s << "Siegpunkt der ihnen nicht genommen" << endl;
	s << "werden kann.";
	btn.info=s.str();
	btn.bInfo=true;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.x=scr.x-150;	
	btn.y=scr.y-105;	
	btn.dx=70;	
	btn.dy=100;
	btn.img=ImageLoad("media\\gfx\\karten\\karte_siegpunkt.png",1);	game.btn.push_back(btn);

	txt.name=btn.name;
	txt.txt="0";
	txt.visible=false;
	txt.x=btn.x+btn.dx/2;
	txt.y=btn.y-20;																	game.txt.push_back(txt);

	//EREIGNIS (2.) Aktionskarte //////////////////////////////////////////////////////////////////////////////
	btn.name="Ereigniskarte";	
	btn.type=2;	
	s.str("");
	s << "Aktionskarte" << endl;
	s << "Sie koennen 2 Rohstoffkarten"<<endl;
	s << "ihrer Wahl von der Bank nehmen.";
	btn.info=s.str();
	btn.bInfo=true;
	btn.bVisible=true;
	btn.bActive=false;
	btn.x=0;	
	btn.x=scr.x-75;	
	btn.y=scr.y-105;	
	btn.dx=70;	
	btn.dy=100;
	btn.img=ImageLoad("media\\gfx\\karten\\karte_ereignis.png",1);		game.btn.push_back(btn);

	txt.name=btn.name;
	txt.txt="0";
	txt.visible=false;
	txt.x=btn.x+btn.dx/2;
	txt.y=btn.y-20;																	game.txt.push_back(txt);

	//BUTTON///////////////////////////ICON STRASSE///////////////////////////////////////////
	btn.name="Anzahl Strasse";
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.dx=24;
	btn.dy=24;
	btn.x=230;
	btn.y=scr.y-29;
	btn.img=0;																		game.btn.push_back(btn);

	txt.name=btn.name;
	txt.txt="0";
	txt.visible=false;
	txt.x=btn.x+btn.dx/2;
	txt.y=btn.y-20;																game.txt.push_back(txt);

	//BUTTON///////////////////////////ICON SIEDLUNG//////////////////////////////////////////
	btn.name="Anzahl Siedlung";
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.dx=24;
	btn.dy=24;
	btn.x=259;
	btn.y=scr.y-29;
	btn.img=0;																		game.btn.push_back(btn);

	txt.name=btn.name;
	txt.txt="0";
	txt.visible=false;
	txt.x=btn.x+btn.dx/2;
	txt.y=btn.y-20;																game.txt.push_back(txt);

	//BUTTON///////////////////////////ICON STADT//////////////////////////////////////////////
	btn.name="Anzahl Stadt";
	btn.info="";
	btn.bInfo=false;
	btn.bVisible=false;
	btn.bActive=false;	
	btn.type=0;
	btn.dx=24;
	btn.dy=24;
	btn.x=288;
	btn.y=scr.y-29;
	btn.img=0;																		game.btn.push_back(btn);

	txt.name=btn.name;
	txt.txt="0";
	txt.visible=false;
	txt.x=btn.x+btn.dx/2;
	txt.y=btn.y-20;																game.txt.push_back(txt);

}