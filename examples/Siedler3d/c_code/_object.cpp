// _object.cpp

#include "_object.h"

#include "DarkGDK.h"
#include "main.h"

#include "thc_vertex.h"
#include "thc_free.h"
#include "thc_is.h"

using namespace thc;

	int CloneObject(int source_obj, float x, float y, float z, int tex)
	{
		if (IsImage(tex)==0) tex=0;
		int obj=FreeObject();		dbCloneObject(obj,source_obj);
		if (IsObject(obj)==0) return 0;
		dbTextureObject(obj,tex);
		dbPositionObject(obj,x,y,z);
		return obj;
	}

	int MakeObjectHexagon(float x, float y, float z, int tex)
	{
		int mesh=game.mesh_hexagon;
		if (IsMesh(mesh)==0) return 0;
		if (IsImage(tex)==0) tex=0;
		int obj=FreeObject();		dbMakeObject(obj,mesh,tex);
		if (IsObject(obj)==0) return 0;
		dbSetObject(obj,1,0,1,2,1,0,0);
		dbPositionObject(obj,x,y,z);
		return obj;
	}
	int MakeObjectChip(float x, float y, float z, int tex)
	{
		int mesh=game.mesh_chip;
		if (IsMesh(mesh)==0) return 0;
		if (IsImage(tex)==0) tex=0;
		int obj=FreeObject();		dbMakeObject(obj,mesh,tex);
		if (IsObject(obj)==0) return 0;
		dbSetObject(obj,1,0,1,2,1,0,0);
		dbPositionObject(obj,x,y,z);
		return obj;
	}
	int MakeObjectStrasse(float x, float y, float z, int tex)
	{
		int mesh=game.mesh_strasse;
		if (IsMesh(mesh)==0) return 0;
		if (IsImage(tex)==0) tex=0;
		int obj=FreeObject();		dbMakeObject(obj,mesh,tex);
		if (IsObject(obj)==0) return 0;
		dbSetObject(obj,1,0,1,2,1,0,0);
		dbPositionObject(obj,x,y,z);
		return obj;
	}
	int MakeObjectSiedlung(float x, float y, float z, int tex)
	{
		int mesh=game.mesh_siedlung;
		if (IsMesh(mesh)==0) return 0;
		if (IsImage(tex)==0) tex=0;
		int obj=FreeObject();		dbMakeObject(obj,mesh,tex);
		if (IsObject(obj)==0) return 0;
		dbSetObject(obj,1,0,1,2,1,0,0);
		dbPositionObject(obj,x,y,z);
		return obj;
	}

	int MakeObjectStadt(float x, float y, float z, int tex)
	{
		int mesh=game.mesh_stadt;
		if (IsMesh(mesh)==0) return 0;
		if (IsImage(tex)==0) tex=0;
		int obj=FreeObject();		dbMakeObject(obj,mesh,tex);
		if (IsObject(obj)==0) return 0;
		dbSetObject(obj,1,0,1,2,1,0,0);
		dbPositionObject(obj,x,y,z);
		return obj;
	}
	int MakeObjectWaypointStrasse(float x, float y, float z)
	{
		int mesh=game.mesh_waypoint_strasse;
		int bild=game.img_way_S;
		if (IsMesh(mesh)==0) return 0;
		if (IsImage(bild)==0) return 0;
		int obj=FreeObject();		dbMakeObject(obj,mesh,bild);
		if (IsObject(obj)==0) return 0;
		dbSetObject(obj,1,0,1,2,1,0,0);
		dbPositionObject(obj,x,y,z);
		return obj;
	}
	int MakeObjectWaypointSiedlung(float x, float y, float z)
	{
		int mesh=game.mesh_waypoint_siedlung;
		int bild=game.img_way_W;
		if (IsMesh(mesh)==0) return 0;
		if (IsImage(bild)==0) return 0;
		int obj=FreeObject();		dbMakeObject(obj,mesh,bild);
		if (IsObject(obj)==0) return 0;
		dbSetObject(obj,1,0,1,2,1,0,0);
		dbPositionObject(obj,x,y,z);
		return obj;
	}