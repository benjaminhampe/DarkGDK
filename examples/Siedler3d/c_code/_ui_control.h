//###############################################################################################
// ui.h
//###############################################################################################
#ifndef __UI_CONTROL_H_INCLUDED__
#define __UI_CONTROL_H_INCLUDED__

#include "stdafx.h"
#include "thc_timer.h"
#include "thc_text.h"

using namespace thc;

//.................................................................................................
void UI_ResetActiveButton();
//void UI_Reset();
void UI_Update();
void UI_Control();
void UI_Show_All(bool yesno);
void UI_Show_Todo(bool yesno);
void UI_Show_TodoDice(bool yesno);
void UI_Show_TodoPlay(bool yesno);
void UI_Show_TodoTrade(bool yesno);
void UI_Show_TodoBank(bool yesno);
void UI_Show_TodoEnd(bool yesno);
void UI_Show_TodoUndo(bool yesno);
void UI_Show_Bauliste(bool yesno);

int  getBTN_under_mouse();				// Speichert in BUTTON game.btn_under_mouse
int  getBTN(const char* name);
int  getTXT(const char* name);
void setBTN_visible(const char* name);
void drawName(int index);
void drawInfoLog(void);
void drawText(int x, int y, int iFont, int iAlign, DWORD color, DWORD bgcolor, char* pTXT);
void drawRect(int x1, int y1, int x2, int y2, int size);
void drawInfo_Way_S(int index, int x, int y, int iFont, int iAlign, DWORD color, DWORD bgcolor);
void drawInfo_Way_W(int index, int x, int y, int iFont, int iAlign, DWORD color, DWORD bgcolor);
void drawInfo_Player(int index,int x, int y, int iFont, int iAlign, DWORD color, DWORD bgcolor);
void drawInfo_Tile( int index, int x, int y, int iFont, int iAlign, DWORD color, DWORD bgcolor);

class Timed_Text
{

private:

	int		_x;
	int		_y;
	int		_font;
	int		_align;
	DWORD	_color;
	string	_txt;
	int		_time_start;
	int		_time_to_live;

	bool	_active;
public:
	Timed_Text(int x=0, int y=0, int font=0, int align=0, DWORD color=0xFF000000, const char* txt="", int time_start=0, int time_to_live=0)
		:	_x(x),
			_y(y),
			_font(font),
			_align(align),
			_color(color),
			_txt(txt),
			_time_start(time_start),
			_time_to_live(time_to_live*1000)
	{
		if (_time_to_live>0) _active=true;
		else				 _active=false;
	};

	~Timed_Text(){};
	
	void setX	(int x)					{ _x=x;					};
	void setY	(int y)					{ _y=y;					};
	void setFont(int font)				{ _font=font;			};
	void setAlign(int align)			{ _align=align;			};
	void setColor(DWORD color)			{ _color=color;			};
	void setText(const char* txt)		{ _txt=txt;				};
	void setTimeStart(int start)		{ _time_start=start;	};
	void setTimeAlive(int alive)		
	{	
		_time_to_live=alive*1000;	
		if (alive>0) _active=true;
		else		 _active=false;
	};

	void set(int x, int y, int font, int align, DWORD color, const char* txt, int time_start, int time_to_live)
	{
		setX(x);
		setY(y);
		setFont(font);
		setAlign(align);
		setColor(color);
		setText(txt);
		setTimeStart(time_start);
		setTimeAlive(time_to_live);
	}

	int getX			(void)		{ return _x;				};
	int getY			(void)		{ return _y;				};
	int getFont			(void)		{ return _font;				};
	int getAlign		(void)		{ return _align;			};
	DWORD getColor		(void)		{ return _color;			};
	const char* getText	(void)		{ return _txt.c_str();		};
	int getTimeStart	(void)		{ return _time_start;		};
	int getTimeAlive	(void)		{ return _time_to_live/1000;};

	int getWidth		(void)		{ return GetTextWidth(_font,(char*)_txt.c_str());};
	int getHeight		(void)		{ return GetTextHeight(_font,(char*)_txt.c_str());};

	bool isActive		(void)		{ return _active;			};
	void Hide			(void)		{ _active=false; _time_to_live=0;};

	void draw(void)
	{
		if (_active==false) return;

		if (timer.getTime()-_time_start <= _time_to_live)
		{
			if (!_txt.empty())
			{
				TextColor(_font,_x,_y,_align,(char*)_txt.c_str(),_color);
			}
		}
		else
		{
			_active=false;
		}
	}
};

extern Timed_Text timed_text_1;
extern Timed_Text timed_text_2;
extern Timed_Text timed_text_3;

#endif