// thc_mouse.cpp
#include "thc_mouse.h"
#include "DarkGDK.h"
#include "thc_vector.h"

namespace thc
{
	MOUSE mouse;
	MOUSE_OLD mouse_old;

	void MouseControl()
	{
		mouse.mx=0.0f;
		mouse.my=0.0f;
		mouse.mz=0.0f;
		mouse.c=dbMouseClick();
		mouse.x=dbMouseX();
		mouse.y=dbMouseY();
		mouse.z=dbMouseZ();
		mouse.MOVE=false;
		mouse.MOVE_X=false;
		mouse.MOVE_Y=false;
		mouse.MOVE_Z=false;
		if (mouse_old.x!=mouse.x) 
		{
			mouse.mx=(float)(mouse.x-mouse_old.x);
			mouse_old.x=mouse.x;
			mouse.MOVE=true;
			mouse.MOVE_X=true;
		}
		if (mouse_old.y!=mouse.y) 
		{
			mouse.my=(float)(mouse.y-mouse_old.y);
			mouse_old.y=mouse.y;
			mouse.MOVE=true;
			mouse.MOVE_Y=true;
		}
		if (mouse_old.z!=mouse.z) 
		{
			mouse.mz=(float)(mouse.z-mouse_old.z);
			mouse_old.z=mouse.z;
			mouse.MOVE=true;
			mouse.MOVE_Z=true;
		}
		if (mouse.CALC_CUT_WITH_XZ==true)
		{
			SchnittMausXZEbene_Control();
		}
	}

	bool MouseOver( int x1, int y1, int x2, int y2)
	{
		if ((mouse.x<x1) || (mouse.x>x2)) return false;
		if ((mouse.y<y1) || (mouse.y>y2)) return false;
		return true;
	}

	//#########################################################
	void SchnittMausXZEbene_Control()
	//#########################################################
	{
	Matrix3 XZEbene;
			  XZEbene.A.x = 0.0f;
			  XZEbene.A.y = 0.0f;
			  XZEbene.A.z = 0.0f;
			  XZEbene.B.x = 1.0f;
			  XZEbene.B.y = 0.0f;
			  XZEbene.B.z = 0.0f;
			  XZEbene.C.x = 0.0f;
			  XZEbene.C.y = 0.0f;
			  XZEbene.C.z = 1.0f;
	bool r = dbMakeVector3(2);	dbSetVector3(2,(float)mouse.x,(float)mouse.y, 1000.0f);

	//3D Maus Punkt
	Fast2DTransform(2);

	Float3 camPos;
	camPos.x=dbCameraPositionX();
	camPos.y=dbCameraPositionY();
	camPos.z=dbCameraPositionZ();

	//Vector use = 3DMaus-camPos
	mouse.pos3D.x=dbXVector3(2);
	mouse.pos3D.y=dbYVector3(2);
	mouse.pos3D.z=dbZVector3(2);

	mouse.use.x = mouse.pos3D.x-camPos.x;
	mouse.use.y = mouse.pos3D.y-camPos.y;
	mouse.use.z = mouse.pos3D.z-camPos.z;

	//Normalise
	mouse.use=VectorNormalise(mouse.use);

	//3D Maus Gerade
	mouse.gerade.A.x = camPos.x;
	mouse.gerade.A.y = camPos.y;
	mouse.gerade.A.z = camPos.z;
	mouse.gerade.B.x = camPos.x+mouse.use.x;
	mouse.gerade.B.y = camPos.y+mouse.use.y;
	mouse.gerade.B.z = camPos.z+mouse.use.z;

	//Schnitt
	mouse.SchnittXZEbene=SchnittGeradeEbene(mouse.gerade, XZEbene);

	r=dbDeleteVector3(2);

	}
}