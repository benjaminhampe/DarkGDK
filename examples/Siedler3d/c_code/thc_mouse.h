// thc_mouse.h

#ifndef __THC_MOUSE_H_INCLUDED__
#define __THC_MOUSE_H_INCLUDED__

#include "DarkGDK.h"
#include "thc_vector.h"

namespace thc
{
	struct MOUSE { int c,x,y,z; float mx,my,mz; bool MOVE, MOVE_X, MOVE_Y, MOVE_Z, CALC_CUT_WITH_XZ;
						Float3 use,pos3D, SchnittXZEbene; Gerade3 gerade;	};
	struct MOUSE_OLD { int x,y,z; };

	extern MOUSE mouse;
	extern MOUSE_OLD mouse_old;

	void MouseControl();
	bool MouseOver( int x1, int y1, int x2, int y2);
	void SchnittMausXZEbene_Control();
}

#endif