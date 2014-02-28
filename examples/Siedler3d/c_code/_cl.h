// cl.h Command Line Interface and Parser
#ifndef __GAME_COMMAND_LINE_H_INCLUDED__
#define __GAME_COMMAND_LINE_H_INCLUDED__

#include "StdAfx.h"

class COMMAND_LINE
{
	private:
	bool visible;
	std::string old_key;
	std::string new_key;
	bool key_any;
	bool key_circum_pressed;
	bool key_return_pressed;
	bool key_delete_pressed;
	bool key_goback_pressed;
	bool key_left_pressed;
	bool key_right_pressed;
	std::string current;
	std::vector<std::string> log;
	std::vector<std::string> fn_names;
	std::vector<std::string> fn_argms;

	int font;
	int cur_x;
	int cur_y;
	int cur_dy;
	int cur_pos;
	DWORD rgb_back;
	DWORD rgb_text;

	public :
	COMMAND_LINE();
	~COMMAND_LINE();

	void init();
	void control();
	void parse();
	void extract_parameter(); // löscht fn_argms, füllt fn_argms mit allen gefundenen Parametern
	void terminate();
	int getParamCount();
	int getFunctionCount();
	void log_param_err(int param_needed, const char* param_info);
};

extern COMMAND_LINE cl;

#endif

// (c) 2007 _neo_cortex