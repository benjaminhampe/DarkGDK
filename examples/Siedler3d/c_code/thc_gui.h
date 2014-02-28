// thc_gui.h

#ifndef __THC_GUI_SYSTEM_H_INCLUDED__
#define __THC_GUI_SYSTEM_H_INCLUDED__

#include "stdafx.h"
#include "thc_text.h"
#include "thc_timer.h"


class THC_GUI_Window
{
	protected:
		int _x,_y,_dx,_dy;
		string _caption;
		bool _visible;
		bool _focused;
		BYTE _alpha;

	public:
	THC_GUI_Window(int x=0, int y=0, int dx=100, int dy=100, string caption="thc_window", BYTE alpha=255)
		:	_x(x), _y(y), _dx(dx), _dy(dy), _caption(caption), _alpha(alpha);
	{
		_visible=true;
		_focused=false;
	}
	virtual ~THC_GUI_Window() {};

	virtual void draw() = 0;


};
*/


#endif