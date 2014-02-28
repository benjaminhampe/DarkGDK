// _cl.cpp

//#pragma warning(disable:4800)

#include "_cl.h"

#include "StdAfx.h"
#include "DarkGDK.h"
#include "main.h"

#include "_game_control.h"
#include "_ui_control.h"

#include "thc_text.h"
#include "thc_string.h"
#include "thc_camera.h"

using namespace thc;


//! constructor
COMMAND_LINE::COMMAND_LINE()	
{
	visible=false;
	old_key="";
	new_key="";
	key_any=false;
	key_circum_pressed=false;
	key_return_pressed=false;
	key_delete_pressed=false;
	key_goback_pressed=false;
	key_left_pressed=false;
	key_right_pressed=false;

	current="";
	log.resize(0);
	fn_names.resize(0);
	fn_argms.resize(0);
	font=4;
	cur_x=0;
	cur_y=0;
	cur_dy=10;
	cur_pos=0;
	rgb_back=0xAA0000FF; // transparentes blau
	rgb_text=0xFFFFFFFF; // weiss
};

//! destructor
COMMAND_LINE::~COMMAND_LINE()
{
	terminate();
};

//! Method :: getParamCount()
int COMMAND_LINE::getParamCount()
{
	return (int)fn_argms.size();
}

//! Method :: getFunctionCount()
int COMMAND_LINE::getFunctionCount()
{
	return (int)fn_names.size();
}

//! Method :: init()
void COMMAND_LINE::init()
{
	fn_names.push_back("show_waypoint_s");
	fn_names.push_back("show_waypoint_w");
	fn_names.push_back("show_dev_info");
	fn_names.push_back("ui_show_all");

}

//! Method :: parse()
void COMMAND_LINE::parse()
{
	int fn_found=-1;
	std::string parser=current;	
	std::string::size_type klammer_1=current.find("(");
	std::string::size_type klammer_2=current.find(")");

	// Prüfe ob Klammer im String enthalten ist
	if ((klammer_1==std::string::npos) || (klammer_2==std::string::npos))
	{
		log.push_back("Keine Klammern gefunden!");
		return;
	}
	else
	{
		parser=parser.substr(0,klammer_1);
		STRING_TOLOWER(parser);
	}

	int fn,fn_count=(int)fn_names.size();

	for (fn=0; fn<fn_count; fn++)
	{
		if (fn_names[fn].compare(parser)==0)
		{
			fn_found=fn;
		}
	}
	if (fn_found==-1)
	{
		stringstream s; s<<"Die Funktion "<<parser.c_str()<<" existiert nicht.";
		log.push_back(s.str());
	}
	else
	{
		stringstream s; s<<"Die Funktion "<<parser.c_str()<<" existiert und wird ausgeführt.";
		log.push_back(s.str());
		extract_parameter();
		int pc=getParamCount();	// parameter count


		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//! führe die gefundene funktion aus, 
		//! überprüfe jeweils ob die parameter stimmen.
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		
		//! Show_Waypoint_W(bool yesno)
		if (parser.compare("show_waypoint_w")==0)
		{
			if (!pc==1) { log_param_err(1,"bool yesno");	return; }
			bool yesno = (bool)atoi(fn_argms[0].c_str());
			Show_Waypoint_W(yesno);
		}

		//! Show_Waypoint_S(bool yesno)
		if (parser.compare("show_waypoint_s")==0)
		{
			if (!pc==1) { log_param_err(1,"bool yesno");	return; }
			bool yesno = (bool)atoi(fn_argms[0].c_str());
			Show_Waypoint_S(yesno);
		}
		//! Show_Dev_Info(bool yesno)
		if (parser.compare("show_dev_info")==0)
		{
			if (!pc==1) { log_param_err(1,"bool yesno");	return; }
			bool yesno = (bool)atoi(fn_argms[0].c_str());
			game.show_dev_info;
		}
		//! UI_Show_ALL(bool yesno)
		if (parser.compare("ui_show_all")==0)
		{
			if (!pc==1) { log_param_err(1,"bool yesno");	return; }
			bool yesno = (bool)atoi(fn_argms[0].c_str());
			UI_Show_All(yesno);
		}		
	}

}

void COMMAND_LINE::log_param_err(int param_needed, const char* param_info)
{
	int pc=getParamCount();
	stringstream s;
	s << "Anzahl der Parameter("<<pc<<") stimmt nicht("<<param_needed<<") : "<<param_info;
	log.push_back(s.str());
}

//! Method :: extract_parameter()
void COMMAND_LINE::extract_parameter()
{
	fn_argms.resize(0);

	std::string::size_type klammer_1=current.find("(");
	std::string::size_type klammer_2=current.find(")");

	// holt den String der alle paramter enthält
	std::string param_list=current.substr(klammer_1+1,klammer_2-klammer_1-1);
	log.push_back(param_list);
	
	std::string buffer_left;
	std::string buffer_right;
	while (!param_list.empty())
	{
		buffer_left="";
		buffer_right="";
		STRING_SPLIT(param_list,",",buffer_left,buffer_right);
		if (buffer_left.empty())
		{
			fn_argms.push_back(param_list);
			param_list="";
		}
		else
		{
			fn_argms.push_back(buffer_left);
			param_list=buffer_right;
		}
	}
	int c=(int)fn_argms.size();
	stringstream s;
	s << "Anzahl Parameter = "<<c;
	log.push_back(s.str());
}

//! Method :: terminate()
void COMMAND_LINE::terminate()
{

}

//! Method :: control()
void COMMAND_LINE::control()
{
	/////////////////////////////////////////
	// TASTATUR - STEUERUNG für Sichtbarkeit
	/////////////////////////////////////////
	int scan=dbScanCode();

	/////////////////////////////////////
	// Wenn COMMAND-LINE sichtbar ist
	/////////////////////////////////////
	if (visible==true)
	{
		
		//Lese Windows Keyboard buffer
		//=============================================
		
		char *key = NULL;		
		key = dbInKey();

		if (key != NULL) 
		{
			if (((int)*key>31) && ((int)*key<127))
			{
				new_key=key;
			
				if (old_key.compare(new_key)!=0)
				{
					key_any=false;
				}
				if (key_any==false)
				{
					old_key=new_key;
					int size=(int)current.size();

					if ((cur_pos>0) && (cur_pos<size))
					{
						current.insert(cur_pos,new_key);
					}
					else
					{
						current += new_key;
					}
					cur_pos++;
					key_any=true;
				}
			}
			if (key[0] == 0x00)
			{
				old_key="";
				key_any=false;
				key_goback_pressed=false;
			}
		}
		else
		{
			old_key="";
			key_any=false;
			key_goback_pressed=false;
		}
			
		free(key);

		// Draw BackgroundBox
		//===========================================================
		dbBox(0,0,::scr.x,100,rgb_back,rgb_back,rgb_back,rgb_back);
		StartText();
		
		// Draw Log STRINGS
		//=============================================
		int x=5, y=5;
		int size=(int)log.size();
		if (size>0)
		{
			int i;
			if (size>5)
			{
				for (i=size-5; i<size; i++)
				{
					TextColor(font,x,y,0,(char*)log[i].c_str(),rgb_text);
					y += cur_dy;
				}
			}
			else
			{
				for (i=0; i<size; i++)
				{
					TextColor(font,x,y,0,(char*)log[i].c_str(),rgb_text);
					y += cur_dy;
				}
			}
		}

		// Draw Current STRING
		//=============================================
		TextColor(font,x,y,0,(char*)current.c_str(),rgb_text);
		EndText();

		// TASTATUR :: ReturnKey()
		//=============================================
		if (dbReturnKey()==1)
		{
			if(key_return_pressed==false)
			{
				log.push_back(current);
				parse();
				current="";
				key_return_pressed=true;
			}
		}
		else
		{
			key_return_pressed=false;
		}
		// TASTATUR :: GoBackKey
		//=============================================
		if (scan==14)
		{
			if(key_goback_pressed==false)
			{
				int count=(int)current.size();
				if ((cur_pos-1>=0) && (cur_pos<=count))
				{
					current.erase(cur_pos-1,1);
					cur_pos -= 1;
					if (cur_pos<0) cur_pos=0;
				}
				key_goback_pressed=true;
			}
		}
		else
		{
			key_goback_pressed=false;
		}

		// TASTATUR :: LeftKey
		//=============================================
		if (dbLeftKey()==1)
		{
			if(key_left_pressed==false)
			{
				cur_pos -= 1;
				if (cur_pos<0) cur_pos=0;
				key_left_pressed=true;
			}
		}
		else
		{
			key_left_pressed=false;
		}

		// TASTATUR :: RightKey
		//=============================================
		if (dbRightKey()==1)
		{
			if(key_right_pressed==false)
			{
				cur_pos += 1;
				int count=(int)current.size();
				if (cur_pos>count) cur_pos=count;
				key_right_pressed=true;
			}
		}
		else
		{
			key_right_pressed=false;
		}

		// Draw Cursor
		//=============================================
		if (cur_pos==0)
		{
			cur_x=5;
		}
		else
		{
			cur_x=5+GetTextWidth(font,(char*)current.substr(0,cur_pos).c_str());
		}
		cur_y=y-2;
		dbInk(0xffffffff,0);
		dbLine(cur_x,cur_y,cur_x,cur_y+cur_dy+4);
	}
	/////////////////////////////////////////
	// TASTATUR - STEUERUNG für Sichtbarkeit
	/////////////////////////////////////////
	if (scan==41)
	{
		if (key_circum_pressed==false)	
		{
			if (visible==false)
			{
				visible=true;
				//dbClearEntryBuffer();
				SetCameraActive(false);
			}
			else
			{
				visible=false;
				SetCameraActive(true);
			}
			current="";
			key_circum_pressed=true;
		}
	}
	else
	{
		key_circum_pressed=false;
	}
}

COMMAND_LINE cl;