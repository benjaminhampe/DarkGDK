// _mesh.h

#ifndef __GAME_MESHES_H_INCLUDED__
#define __GAME_MESHES_H_INCLUDED__


int MakeMeshHexagon(float size);
int MakeMeshChip(float size, float height, int segments);
int MakeMeshStrasse(float a, float b, float c);
int MakeMeshSiedlung(float a, float b, float c);
int MakeMeshStadt(float a, float b, float c);

#endif