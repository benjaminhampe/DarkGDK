// thc_camera.h			

#ifndef __THC_CAMERA_H_INCLUDED__
#define __THC_CAMERA_H_INCLUDED__

#include "thc_vector.h"

namespace thc
{
	struct CAMERA_OLD { float x,y,z,a,b,c;};
	struct CAMERA 
	{ 
		float x,y,z,a,b,c,mx,my,mz,ma,mb,mc; Float3 vec,use, point;
		bool ACTIVE,UPDATE, CHANGE, ROTATE, ROTATE_X, ROTATE_Y, ROTATE_Z, MOVE, MOVE_X, MOVE_Y, MOVE_Z;
	};

	extern CAMERA camera;
	extern CAMERA_OLD camera_old;

	void SetCameraActive(bool yesno);
	void CameraControl();
	void CameraFreeView (int iID, float move, float ystep, float xturn, float yturn);
	void CameraCylinder (int iID,float move, float ystep, float yturn);

	/*
	inline void CameraFreeView (int iID, float move, float ystep, float xturn, float yturn)
	{
		// Tastatur Steuerung
		if (dbUpKey()==1)			{	dbMoveCamera(    iID, move);									}
		if (dbDownKey()==1)		{	dbMoveCamera(    iID, -move);									}
		if (dbLeftKey()==1)		{	dbYRotateCamera( iID, dbWrapValue(camera.b-yturn));	}
		if (dbRightKey()==1)		{	dbYRotateCamera( iID, dbWrapValue(camera.b+yturn));	}
		if (dbScanCode()==201)  {	dbXRotateCamera( iID, dbWrapValue(camera.a+xturn));	}
		if (dbScanCode()==209) 	{	dbXRotateCamera( iID, dbWrapValue(camera.a-xturn));	}
		if (dbShiftKey()==1) 	{	dbPositionCamera(iID, camera.x,CameraPositionY(iID)+ystep,dbCameraPositionZ(iID));}
		if (dbControlKey()==1) 	{	dbPositionCamera(iID, dbCameraPositionX(iID),dbCameraPositionY(iID)-ystep,dbCameraPositionZ(iID));}

		// Maus Steuerung
		if ( mouse.c == 2)
		{

		if ( mouse.mx != 0.0f)	{	dbYRotateCamera(iID,dbCurveAngle(dbWrapValue(dbCameraAngleY(iID)+mouse.mx),dbCameraAngleY(iID),2.5f));	}
		if ( mouse.my != 0.0f)	{	dbXRotateCamera(iID,dbCurveAngle(dbWrapValue(dbCameraAngleX(iID)+mouse.my),dbCameraAngleX(iID),2.5f));	}
		if ( mouse.mz != 0.0f)	{	dbMoveCamera(iID,mouse.mz);}
		}
	}
	*/

}

#endif