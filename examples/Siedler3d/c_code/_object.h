// _object.h

#ifndef __GAME_OBJECTS_H_INCLUDED__
#define __GAME_OBJECTS_H_INCLUDED__

	int CloneObject(int source_obj, float x, float y, float z, int tex);
	int MakeObjectHexagon(float x, float y, float z, int tex);
	int MakeObjectChip(float x, float y, float z, int tex);
	int MakeObjectStrasse(float x, float y, float z, int tex);
	int MakeObjectSiedlung(float x, float y, float z, int tex);
	int MakeObjectStadt(float x, float y, float z, int tex);
	int MakeObjectWaypointStrasse(float x, float y, float z);
	int MakeObjectWaypointSiedlung(float x, float y, float z);

#endif