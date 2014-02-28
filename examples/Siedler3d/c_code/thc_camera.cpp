//! (c) 2007 _neo_cortex
//
// thc_camera.cpp

#include "thc_camera.h"
#include "DarkGDK.h"
#include "thc_mouse.h"

namespace thc
{
	CAMERA camera;
	CAMERA_OLD camera_old;

	void SetCameraActive(bool yesno)
	{
		camera.ACTIVE=yesno;
	}

	void CameraControl()
	{
		if (!camera.ACTIVE) return;
		if (!camera.UPDATE) return;
		//camera.x=dbCameraPositionX();
		//camera.y=dbCameraPositionY();
		//camera.z=dbCameraPositionZ();
		//camera.a=dbCameraAngleX();
		//camera.b=dbCameraAngleY();
		//camera.c=dbCameraAngleZ();
		camera.mx=0.0f;		camera.my=0.0f;		camera.mz=0.0f;
		camera.ma=0.0f;		camera.mb=0.0f;		camera.mc=0.0f;
		camera.UPDATE=false;
		camera.CHANGE=false;
		camera.MOVE=false;	camera.MOVE_X=false;		camera.MOVE_Y=false;		camera.MOVE_Z=false;
		camera.ROTATE=false;	camera.ROTATE_X=false;	camera.ROTATE_Y=false;	camera.ROTATE_Z=false;	

		if (camera.x!=camera_old.x)
		{
			camera.CHANGE=true;
			camera.MOVE=true;
			camera.MOVE_X=true;
			camera.mx=camera.x-camera_old.x;
			camera_old.x=camera.x;
		}
		if (camera.y!=camera_old.y)
		{
			camera.CHANGE=true;
			camera.MOVE=true;
			camera.MOVE_Y=true;
			camera.my=camera.y-camera_old.y;
			camera_old.y=camera.y;
		}
		if (camera.z!=camera_old.z)
		{
			camera.CHANGE=true;
			camera.MOVE=true;
			camera.MOVE_Z=true;
			camera.mz=camera.z-camera_old.z;
			camera_old.z=camera.z;
		}
		if (camera.a!=camera_old.a)
		{
			camera.CHANGE=true;
			camera.ROTATE=true;
			camera.ROTATE_X=true;
			camera.ma=camera.a-camera_old.a;
			camera_old.a=camera.a;
		}
		if (camera.b!=camera_old.b)
		{
			camera.CHANGE=true;
			camera.ROTATE=true;
			camera.ROTATE_Y=true;
			camera.mb=camera.b-camera_old.b;
			camera_old.b=camera.b;
		}
		if (camera.c!=camera_old.c)
		{
			camera.CHANGE=true;
			camera.ROTATE=true;
			camera.ROTATE_Z=true;
			camera.mc=camera.c-camera_old.c;
			camera_old.c=camera.c;
		}
	}
	void CameraFreeView (int iID, float move, float ystep, float xturn, float yturn)
	{
		if (!camera.ACTIVE) return;
		// Tastatur Steuerung
		if (dbUpKey()==1)			{	camera.UPDATE=true;	dbMoveCamera(    iID, move);		}
		if (dbDownKey()==1)		{	camera.UPDATE=true;	dbMoveCamera(    iID, -move);									}
		if (dbLeftKey()==1)		{	camera.UPDATE=true;	dbYRotateCamera( iID, dbWrapValue(camera.b-yturn));	}
		if (dbRightKey()==1)		{	camera.UPDATE=true;	dbYRotateCamera( iID, dbWrapValue(camera.b+yturn));	}
		if (dbScanCode()==201)  {	camera.UPDATE=true;	dbXRotateCamera( iID, dbWrapValue(camera.a+xturn));	}
		if (dbScanCode()==209) 	{	camera.UPDATE=true;	dbXRotateCamera( iID, dbWrapValue(camera.a-xturn));	}
		if (dbShiftKey()==1) 	{	camera.UPDATE=true;	dbPositionCamera(iID, camera.x,camera.y+ystep,camera.z);}
		if (dbControlKey()==1) 	{	camera.UPDATE=true;	dbPositionCamera(iID, camera.x,camera.y-ystep,camera.z);}

		// Maus Steuerung
		if ( mouse.c == 2)
		{

		if ( mouse.mx != 0.0f)	{	camera.UPDATE=true;	dbYRotateCamera(iID,dbCurveAngle(dbWrapValue(camera.b+mouse.mx),camera.b,2.5f));	}
		if ( mouse.my != 0.0f)	{	camera.UPDATE=true;	dbXRotateCamera(iID,dbCurveAngle(dbWrapValue(camera.a+mouse.my),camera.a,2.5f));	}
		if ( mouse.mz != 0.0f)	{	camera.UPDATE=true;	dbMoveCamera(iID,mouse.mz);}
		}
	}
	void CameraCylinder (int iID,float move, float ystep, float yturn)
	{
		if (!camera.ACTIVE) return;

		//Left
		if (dbLeftKey()==1)		
		{	
			camera.b=dbWrapValue(camera.b+yturn);
			float distXZ=dbSQRT(camera.x*camera.x+camera.z*camera.z);
			camera.x=dbNewXValue(camera.point.x,camera.b,-distXZ);
			camera.z=dbNewZValue(camera.point.z,camera.b,-distXZ);
			dbPositionCamera(iID,camera.x,camera.y,camera.z);
			dbPointCamera(iID,camera.point.x,camera.point.y,camera.point.z);
			camera.UPDATE=true;
		}
		//Right
		if (dbRightKey()==1)		
		{
			camera.b=dbWrapValue(camera.b-yturn);	
			float distXZ=dbSQRT(camera.x*camera.x+camera.z*camera.z);
			camera.x=dbNewXValue(camera.point.x,camera.b,-distXZ);
			camera.z=dbNewZValue(camera.point.z,camera.b,-distXZ);
			dbPositionCamera(iID,camera.x,camera.y,camera.z);
			dbPointCamera(iID,camera.point.x,camera.point.y,camera.point.z);
			camera.UPDATE=true;
		}
		//Shift
		if (dbShiftKey()==1)		
		{	
			camera.y += ystep;
			dbPositionCamera(iID,camera.x,camera.y,camera.z);
			dbPointCamera(iID,camera.point.x,camera.point.y,camera.point.z);
			camera.a=dbCameraAngleX(iID);
			camera.UPDATE=true;
		}
		//Strg
		if (dbControlKey()==1)	
		{	
			if (camera.y>=ystep)
			{
			camera.y -= ystep;
			dbPositionCamera(iID,camera.x,camera.y,camera.z);
			dbPointCamera(iID,camera.point.x,camera.point.y,camera.point.z);
			camera.a=dbCameraAngleX(iID);
			camera.UPDATE=true;
			}
		}
		//Up
		if (dbUpKey()==1)	
		{	
			dbMoveCamera(iID,move);
			camera.x=dbCameraPositionX(iID);
			camera.y=dbCameraPositionY(iID);
			camera.z=dbCameraPositionZ(iID);
			camera.UPDATE=true;
		}
		//Down
		if (dbDownKey()==1)
		{	
			dbMoveCamera(iID,-move);
			camera.x=dbCameraPositionX(iID);
			camera.y=dbCameraPositionY(iID);
			camera.z=dbCameraPositionZ(iID);
			camera.UPDATE=true;
		}
		//Mouse
		if (mouse.c==2)
		{
		if ( mouse.mx != 0.0f)	{	dbYRotateCamera(iID,dbCurveAngle(dbWrapValue(dbCameraAngleY(iID)+mouse.mx),dbCameraAngleY(iID),2.5f));	}
		if ( mouse.my != 0.0f)	{	dbXRotateCamera(iID,dbCurveAngle(dbWrapValue(dbCameraAngleX(iID)+mouse.my),dbCameraAngleX(iID),2.5f));	}
		if ( mouse.mz != 0.0f)	{	dbMoveCamera(iID,mouse.mz);}
		}	
	}

}