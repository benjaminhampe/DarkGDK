// _mesh.cpp
#pragma once
#include "DarkGDK.h"

#include "thc_vertex.h"
#include "thc_free.h"

using namespace thc;


	int MakeMeshHexagon(float size)
	{
		int mem = FreeMemblock();
		dbMakeMemblock(mem,12+12*36);
		dbWriteMemblockDword(mem,0,338);
		dbWriteMemblockDword(mem,4,36);
		dbWriteMemblockDword(mem,8,12);
		WriteVertexHexagon(mem,12,0.0f,0.0f,0.0f,size);
		
		int mesh=FreeMesh();
		dbMakeMeshFromMemblock(mesh,mem);
		dbDeleteMemblock(mem);
		if (dbMeshExist(mesh)==0) return 0;
		return mesh;
	}
	int MakeMeshChip(float size, float height, int segments)
	{
		int mem = FreeMemblock();
		if (segments<6) segments=6;
		dbMakeMemblock(mem,12+9*segments*36);
		dbWriteMemblockDword(mem,0,338);
		dbWriteMemblockDword(mem,4,36);
		dbWriteMemblockDword(mem,8,9*segments);
		WriteVertexCylinderWithoutBottom(mem,12,0.0f,height*0.5f,0.0f,size,height,segments);
		
		int mesh=FreeMesh();
		dbMakeMeshFromMemblock(mesh,mem);
		dbDeleteMemblock(mem);
		if (dbMeshExist(mesh)==0) return 0;
		return mesh;
	}
	int MakeMeshStrasse(float a, float b, float c)
	{
		int mem = FreeMemblock();
		dbMakeMemblock(mem,12+30*36);
		dbWriteMemblockDword(mem,0,338);
		dbWriteMemblockDword(mem,4,36);
		dbWriteMemblockDword(mem,8,30);
		WriteVertexBoxWithoutBottom(mem,12,0.0f,b*0.5f,0.0f,a,b,c);
		
		int mesh=FreeMesh();
		dbMakeMeshFromMemblock(mesh,mem);
		dbDeleteMemblock(mem);

		if (dbMeshExist(mesh)==0) return 0;
		return mesh;
	}
	int MakeMeshSiedlung(float a, float b, float c)
	{
		int mem = FreeMemblock();
		dbMakeMemblock(mem,12+42*36);
		dbWriteMemblockDword(mem,0,338);
		dbWriteMemblockDword(mem,4,36);
		dbWriteMemblockDword(mem,8,42);
		WriteVertexSiedlung(mem,12,0.0f,0.0f,0.0f,a,b,c);
		
		int mesh=FreeMesh();
		dbMakeMeshFromMemblock(mesh,mem);
		dbDeleteMemblock(mem);
		if (dbMeshExist(mesh)==0) return 0;
		return mesh;
	}
	int MakeMeshStadt(float a, float b, float c)
	{
		int mem = FreeMemblock();
		dbMakeMemblock(mem,12+72*36);
		dbWriteMemblockDword(mem,0,338);
		dbWriteMemblockDword(mem,4,36);
		dbWriteMemblockDword(mem,8,72);
		WriteVertexStadt(mem,12,0.0f,0.0f,0.0f,a,b,c);
		
		int mesh=FreeMesh();
		dbMakeMeshFromMemblock(mesh,mem);
		dbDeleteMemblock(mem);
		if (dbMeshExist(mesh)==0) return 0;
		return mesh;
	}