// *********************************
//		Benni's  Vertex  Baukasten
// *********************************

#ifndef __THC_VERTEX_H_INCLUDED__
#define __THC_VERTEX_H_INCLUDED__

#include <windows.h>
#include "thc_vector.h"

namespace thc
{
	struct vertex 
	{ 
		float x,y,z,nx,ny,nz;
		DWORD color; 
		float u,v;
	};

	void WriteVertex(int mem, int pos, vertex V );
	void WriteVertex(int mem, int pos, float x, float y, float z, float nx, float ny, float nz, DWORD color, float u, float v);
	void WriteVertexTriangle(int mem, int pos, vertex A, vertex B, vertex C);
	void WriteVertexPlain(int mem, int pos, vertex A, vertex B, vertex C, vertex D);
	void WriteVertexPlain(int mem, int pos, vertex A, vertex B, vertex C, vertex D, float du, float dv);
	void WriteVertexHexagon(int mem, int pos, float x, float y, float z, float size);
	void WriteVertexBox(int mem, int pos, float x, float y, float z, float a, float b, float c);
	void WriteVertexBoxWithoutBottom(int mem, int pos, float x, float y, float z, float a, float b, float c);
	void WriteVertexBoxWithoutBottom_Top(int mem, int pos, float x, float y, float z, float a, float b, float c);
	void WriteVertexCircle(int mem, int pos, float x, float y, float z, float radius, int segments );
	void WriteVertexCylinder(int mem, int pos, float x, float y, float z, float radius, float height, int segments );
	void WriteVertexCylinderWithoutBottom(int mem, int pos, float x, float y, float z, float radius, float height, int segments );
	void WriteVertexDach(int mem, int pos, float x, float y, float z, float a, float b, float c);
	void WriteVertexSiedlung(int mem, int pos, float x, float y, float z, float a, float b, float c);
	void WriteVertexStadt(int mem, int pos, float x, float y, float z, float a, float b, float c);
	void WriteVertexTetraeder(int mem, int pos, float x, float y, float z, Float3 A, Float3 B, Float3 C, Float3 D);
}

#endif