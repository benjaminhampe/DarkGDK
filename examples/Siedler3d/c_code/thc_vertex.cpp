// thc_vertex.cpp

#include "thc_vertex.h"
#include "thc_vector.h"
#include "thc_memblock.h"
#include "thc_is.h"
#include "DarkGDK.h"


namespace thc
{
	//////////////////////////////////////////////////////////////////
	inline void MemblockWriteFloat(int mem, int pos, float value)
	//////////////////////////////////////////////////////////////////
	{
		dbWriteMemblockFloat(mem,pos,value);
	}
	//////////////////////////////////////////////////////////////////
	void WriteVertex ( int mem, int pos, vertex V )
	//////////////////////////////////////////////////////////////////
	{
		// pos = pos + 36
		if (IsMemblock(mem)==0) return;
		MemblockWriteFloat(mem,pos+0, V.x);
		MemblockWriteFloat(mem,pos+4, V.y);
		MemblockWriteFloat(mem,pos+8, V.z);
		MemblockWriteFloat(mem,pos+12,V.nx);
		MemblockWriteFloat(mem,pos+16,V.ny);
		MemblockWriteFloat(mem,pos+20,V.nz);
		MemblockWriteDword(mem,pos+24,V.color);
		MemblockWriteFloat(mem,pos+28,V.u);
		MemblockWriteFloat(mem,pos+32,V.v);
	}
	///////////////////////////////////////////////////////////////////////////
	void WriteVertex ( int mem, int pos, float x, float y, float z, float nx, float ny, float nz, DWORD color, float u, float v)
	///////////////////////////////////////////////////////////////////////////
	{
		// pos = pos + 36
		if (mem==0) return;
		if (dbMemblockExist(mem)==0) return;
		MemblockWriteFloat(mem,pos+0, x);
		MemblockWriteFloat(mem,pos+4, y);
		MemblockWriteFloat(mem,pos+8, z);
		MemblockWriteFloat(mem,pos+12,nx);
		MemblockWriteFloat(mem,pos+16,ny);
		MemblockWriteFloat(mem,pos+20,nz);
		MemblockWriteDword(mem,pos+24,color);
		MemblockWriteFloat(mem,pos+28,u);
		MemblockWriteFloat(mem,pos+32,v);
	}
	////////////////////////////////////////////////////////////////////////////
	void WriteVertexTriangle ( int mem, int pos, vertex A, vertex B, vertex C)
	////////////////////////////////////////////////////////////////////////////
	{
		//`...B			pos = pos + 3*36
		//`../.\
		//`./...\
		//`A-----C

		if (mem==0) return;
		if (dbMemblockExist(mem)==0) return;

		// calculate normale = (AB x AC)/|AB x AC|
		A.nx = B.x-A.x;		A.ny = B.y-A.y;		A.nz = B.z-A.z;
		B.nx = C.x-A.x;		B.ny = C.y-A.y;		B.nz = C.z-A.z;
		C.nx = A.ny*B.nz-A.nz*B.ny;
		C.ny = A.nz*B.nx-A.nx*B.nz;
		C.nz = A.nx*B.ny-A.ny*B.nx;
		float bb = sqrt(C.nx*C.nx+C.ny*C.ny+C.nz*C.nz);
		C.nx /= bb;  C.ny /= bb;  C.nz /= bb;
		A.nx = C.nx; A.ny = C.ny; A.nz = C.nz;
		B.nx = C.nx; B.ny = C.ny; B.nz = C.nz;

		WriteVertex(mem,pos+0*36,A);		
		WriteVertex(mem,pos+1*36,B);
		WriteVertex(mem,pos+2*36,C);
	}
	///////////////////////////////////////////////////////////////////////////////////
	void WriteVertexPlain ( int mem, int pos, vertex A, vertex B, vertex C, vertex D)
	///////////////////////////////////////////////////////////////////////////////////
	{
		//..B---C			pos = pos + 6*36
		//..|../|
		//..|/..|
		//..A---D
		WriteVertexTriangle ( mem, pos,      A, B, C);
		WriteVertexTriangle ( mem, pos+3*36, C, D, A);
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	void WriteVertexPlain ( int mem, int pos, vertex A, vertex B, vertex C, vertex D, float du, float dv)
	///////////////////////////////////////////////////////////////////////////////////////////////////////
	{
		//..B---C			pos = pos + 6*36
		//..|../|
		//..|/..|
		//..A---D
		A.u=0.0f;	A.v=dv;
		B.u=0.0f;	B.v=0.0f;
		C.u=du;		C.v=0.0f;
		D.u=du;		D.v=dv;
		WriteVertexTriangle ( mem, pos,      A, B, C);
		WriteVertexTriangle ( mem, pos+3*36, C, D, A);
	}
	//////////////////////////////////////////////////
	void WriteVertexHexagon (int mem, int pos, float x, float y, float z, float size)
	//////////////////////////////////////////////////
	{
		//.......A.........	pos = pos + 12*36
		//..B....|....F....
		//..|....|....|....
		//..|....|....|....
		//..C....|....E....
		//.......D.........

		if (mem==0) return;
		if (dbMemblockExist(mem)==0) return;

		// Vertices
		vertex A	= {x+0.0f		,	y,z+size*0.50f, 0.0f,1.0f,0.0f,0xffffffff,0.5f,	0.0f};
		vertex B	= {x-size*0.5f	,	y,z+size*0.25f, 0.0f,1.0f,0.0f,0xffffffff,0.0f,	0.25f};
		vertex C	= {x-size*0.5f	,	y,z-size*0.25f, 0.0f,1.0f,0.0f,0xffffffff,0.0f,	0.75f};
		vertex D	= {x+0.0f		,	y,z-size*0.50f, 0.0f,1.0f,0.0f,0xffffffff,0.5f,	1.0f};
		vertex E	= {x+size*0.5f	,	y,z-size*0.25f, 0.0f,1.0f,0.0f,0xffffffff,1.0f,	0.75f};
		vertex F	= {x+size*0.5f	,  y,z+size*0.25f, 0.0f,1.0f,0.0f,0xffffffff,1.0f,	0.25f};

		WriteVertexTriangle ( mem, pos +  0*36, A,F,E );
		WriteVertexTriangle ( mem, pos +  3*36, E,D,A );
		WriteVertexTriangle ( mem, pos +  6*36, D,C,B );
		WriteVertexTriangle ( mem, pos +  9*36, B,A,D );
	}
	////////////////////////////////////////////////////////////////////////////////////////////////
	void WriteVertexBox ( int mem, int pos, float x, float y, float z, float a, float b, float c)
	////////////////////////////////////////////////////////////////////////////////////////////////
	{
		//.....F -------- G	pos = pos + 36*36
		//..../|........ /|
		//.../.|......../.|
		//..E--------- H..|
		//..|..|.......|..|
		//..|..B ------|- C
		//..|./........|./
		//..|/.........|/
		//..A -------- D

		if (mem==0) return;
		if (dbMemblockExist(mem)==0) return;
		
		//Globale UV Minimum
		float uv;
		if (b>a) uv=a; else uv=b;
		if (c<uv) uv=c;

		vertex A = {-0.5f*a+x,	-0.5f*b+y,	-0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex B = {-0.5f*a+x,	-0.5f*b+y,	 0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex C = { 0.5f*a+x,	-0.5f*b+y,	 0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex D = { 0.5f*a+x,	-0.5f*b+y,	-0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex E = {-0.5f*a+x,	 0.5f*b+y,	-0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex F = {-0.5f*a+x,	 0.5f*b+y,	 0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex G = { 0.5f*a+x,	 0.5f*b+y,	 0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex H = { 0.5f*a+x,	 0.5f*b+y,	-0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};

		//ABCD und EFGH
		//if (c>a) uv=a; else uv=c; //-> Lokales UV Minimum nur für diese Fläche
		WriteVertexPlain(mem,pos,D,C,B,A,a/uv,c/uv); pos += 6*36;
		WriteVertexPlain(mem,pos,E,F,G,H,a/uv,c/uv); pos += 6*36;

		//AEHD und BFGC
		//if (b>a) uv=a; else uv=b; //-> Lokales UV Minimum nur für diese Fläche
		WriteVertexPlain(mem,pos,A,E,H,D,a/uv,b/uv); pos += 6*36;
		WriteVertexPlain(mem,pos,C,G,F,B,a/uv,b/uv); pos += 6*36;

		//BFEA und CGHD
		//if (c>b) uv=b; else uv=c; //-> Lokales UV Minimum nur für diese Fläche
		WriteVertexPlain(mem,pos,B,F,E,A,c/uv,b/uv); pos += 6*36;
		WriteVertexPlain(mem,pos,D,H,G,C,c/uv,b/uv); pos += 6*36;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////
	void WriteVertexBoxWithoutBottom ( int mem, int pos, float x, float y, float z, float a, float b, float c)
	////////////////////////////////////////////////////////////////////////////////////////////////
	{
		//.....F -------- G	pos = pos + 30*36
		//..../|........ /|
		//.../.|......../.|
		//..E--------- H..|
		//..|..|.......|..|
		//..|..B ------|- C
		//..|./........|./
		//..|/.........|/
		//..A -------- D

		if (mem==0) return;
		if (dbMemblockExist(mem)==0) return;
		
		//Globale UV Minimum
		float uv;
		if (b>a) uv=a; else uv=b;
		if (c<uv) uv=c;

		vertex A = {-0.5f*a+x,	-0.5f*b+y,	-0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex B = {-0.5f*a+x,	-0.5f*b+y,	 0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex C = { 0.5f*a+x,	-0.5f*b+y,	 0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex D = { 0.5f*a+x,	-0.5f*b+y,	-0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex E = {-0.5f*a+x,	 0.5f*b+y,	-0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex F = {-0.5f*a+x,	 0.5f*b+y,	 0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex G = { 0.5f*a+x,	 0.5f*b+y,	 0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex H = { 0.5f*a+x,	 0.5f*b+y,	-0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};

		//ABCD und EFGH
		//if (c>a) uv=a; else uv=c; //-> Lokales UV Minimum nur für diese Fläche
		//WriteVertexPlain(mem,pos,D,C,B,A,a/uv,c/uv); pos += 6*36;
		WriteVertexPlain(mem,pos,E,F,G,H,a/uv,c/uv); pos += 6*36;

		//AEHD und BFGC
		//if (b>a) uv=a; else uv=b; //-> Lokales UV Minimum nur für diese Fläche
		WriteVertexPlain(mem,pos,A,E,H,D,a/uv,b/uv); pos += 6*36;
		WriteVertexPlain(mem,pos,C,G,F,B,a/uv,b/uv); pos += 6*36;

		//BFEA und CGHD
		//if (c>b) uv=b; else uv=c; //-> Lokales UV Minimum nur für diese Fläche
		WriteVertexPlain(mem,pos,B,F,E,A,c/uv,b/uv); pos += 6*36;
		WriteVertexPlain(mem,pos,D,H,G,C,c/uv,b/uv); pos += 6*36;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////
	void WriteVertexBoxWithoutBottom_Top ( int mem, int pos, float x, float y, float z, float a, float b, float c)
	////////////////////////////////////////////////////////////////////////////////////////////////
	{
		//.....F -------- G	pos = pos + 24*36
		//..../|........ /|
		//.../.|......../.|
		//..E--------- H..|
		//..|..|.......|..|
		//..|..B ------|- C
		//..|./........|./
		//..|/.........|/
		//..A -------- D

		if (mem==0) return;
		if (dbMemblockExist(mem)==0) return;
		
		//Globale UV Minimum
		float uv;
		if (b>a) uv=a; else uv=b;
		if (c<uv) uv=c;

		vertex A = {-0.5f*a+x,	-0.5f*b+y,	-0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex B = {-0.5f*a+x,	-0.5f*b+y,	 0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex C = { 0.5f*a+x,	-0.5f*b+y,	 0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex D = { 0.5f*a+x,	-0.5f*b+y,	-0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex E = {-0.5f*a+x,	 0.5f*b+y,	-0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex F = {-0.5f*a+x,	 0.5f*b+y,	 0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex G = { 0.5f*a+x,	 0.5f*b+y,	 0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};
		vertex H = { 0.5f*a+x,	 0.5f*b+y,	-0.5f*c+z,	0.0f, 1.0f, 0.0f, 0xffffffff, 0.0f,0.0f};

		//ABCD und EFGH
		//if (c>a) uv=a; else uv=c; //-> Lokales UV Minimum nur für diese Fläche
		//WriteVertexPlain(mem,pos,D,C,B,A,a/uv,c/uv); pos += 6*36;
		//WriteVertexPlain(mem,pos,E,F,G,H,a/uv,c/uv); pos += 6*36;

		//AEHD und BFGC
		//if (b>a) uv=a; else uv=b; //-> Lokales UV Minimum nur für diese Fläche
		WriteVertexPlain(mem,pos,A,E,H,D,a/uv,b/uv); pos += 6*36;
		WriteVertexPlain(mem,pos,C,G,F,B,a/uv,b/uv); pos += 6*36;

		//BFEA und CGHD
		//if (c>b) uv=b; else uv=c; //-> Lokales UV Minimum nur für diese Fläche
		WriteVertexPlain(mem,pos,B,F,E,A,c/uv,b/uv); pos += 6*36;
		WriteVertexPlain(mem,pos,D,H,G,C,c/uv,b/uv); pos += 6*36;
	}
	////////////////////////////////////////////////////////////////////////////////
	void WriteVertexCircle	( int mem, int pos, float x, float y, float z, float radius, int segments )
	////////////////////////////////////////////////////////////////////////////////
	{
		//......*P1........	pos = pos + 3*segments * 36
		//....*..|..*......
		//...*...|...*.....
		//..P2...M...P4....
		//...*.......*.....
		//....*.....*......
		//......*P3........

		if (mem==0) return;
		if (dbMemblockExist(mem)==0) return;

		// Local Variables
		float winkel = 360.0f/(float)segments;
		float phi;
		int i;

		// Array :: Eckpunkte + Mittelpunkt
		vertex *useVertex = new vertex[segments+1];

		// UV - Mittelpunkt
		useVertex[0].x	= x;
		useVertex[0].z	= z;
		useVertex[0].u	= 0.5f;
		useVertex[0].v	= 0.5f;

		// Gültig für alle Vertices : Y-Koordinate + Normale + Color
		for ( i=0; i<segments+1; i++ )
		{
			useVertex[i].y=y;
			useVertex[i].nx=0.0f;
			useVertex[i].ny=1.0f;
			useVertex[i].nz=0.0f;
			useVertex[i].color=dbRGB(255,255,255);
		}

		// Punkte 1 bis Segments+1
		for (i=1; i<segments+1; i++ )
		{
			phi=(float)(i-1)*winkel;
			useVertex[i].x	=	x+(float)(-dbSin(phi)*radius);
			useVertex[i].z	=	z+(float)(dbCos(phi)*radius);
			useVertex[i].u	=	(float)(0.5f-dbSin(phi)*0.5f);
			useVertex[i].v	=	(float)(0.5f-dbCos(phi)*0.5f);
		}

		// Vertices RunTimeVar Mempos for writing in memblock
		int mempos=pos;

		// Schreibe Memblock
		for ( i=0; i<segments; i++ )
		{
			// Memblock Index
			mempos += 3*36*i;

			// 1. Vertex von jedem Dreieck = Ursprung
			

			// 2. und 3. Vertex von jedem Dreieck
			if (i==segments-1)
			{
				WriteVertexTriangle ( mem, mempos, useVertex[0], useVertex[i+1],useVertex[1] );	
			}
			else
			{
				WriteVertexTriangle ( mem, mempos, useVertex[0], useVertex[i+1],useVertex[i+2] );	
			}
		}
		delete [] useVertex;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	void WriteVertexCylinder ( int mem, int pos, float x, float y, float z, float radius, float height, int segments )
	/////////////////////////////////////////////////////////////////////////////////////////////////
	{
		//.......*Q1*......
		//....*../.../*....
		//...*..*P1./..*...	pos = pos + 12*segments * 36
		//...**..|./*..Q4..
		//...*...|/..*/....
		//..P2...M...P4....
		//...*../.Q3.*.....
		//....*/./..*......
		//......*P3........

		if (mem==0) return;
		if (dbMemblockExist(mem)==0) return;
		
		// Local Variables
		int vertices = 12*segments;
		float winkel = 360.0f/(float)segments;
		float phi;
		int i;

		// Vertices Array enthält Eckpunkte + 2*Mittelpunkte
		int anzahl_punkte=2+2*segments;
		vertex *useVertex = new vertex[anzahl_punkte];

		// Gültig für alle Punkte
		for ( i=0; i<anzahl_punkte; i++ )
		{
			useVertex[i].color=dbRGB(255,255,255);
		}

		// Punkte 0 bis Segments-1 = Deckfläche
		for ( i=0; i<segments; i++ )
		{
			phi=(float)i*winkel;
			useVertex[i].x	=	x+(float)(-dbSin(phi)*radius);
			useVertex[i].y	=	y+height*0.5f;
			useVertex[i].z	=	z+(float)(dbCos(phi)*radius);
			useVertex[i].u	=	(float)(0.5f-dbSin(phi)*0.5f);
			useVertex[i].v	=	(float)(0.5f-dbCos(phi)*0.5f);
			useVertex[i].nx	=	0.0f;
			useVertex[i].ny	=	1.0f;
			useVertex[i].nz	=	0.0f;
		}

		// Punkte Segments+2 bis 2*segments+2 = Bodenfläche
		for ( i=segments; i<2*segments; i++ )
		{
			useVertex[i].x	=	useVertex[i-segments].x;
			useVertex[i].y	=  y-0.5f * height;
			useVertex[i].z	=	useVertex[i-segments].z;
			useVertex[i].u	=	useVertex[i-segments].u;
			useVertex[i].v	=	useVertex[i-segments].v;
			useVertex[i].nx	=	0.0f;
			useVertex[i].ny	=  1.0f;
			useVertex[i].nz	=	0.0f;
		}

		// Punkt 0 = Mitte Deckfläche
		useVertex[anzahl_punkte-2].x	=	x;
		useVertex[anzahl_punkte-2].y	=	y+0.5f * height;
		useVertex[anzahl_punkte-2].z	=	z;
		useVertex[anzahl_punkte-2].u	=	0.5f;
		useVertex[anzahl_punkte-2].v	=	0.5f;
		useVertex[anzahl_punkte-2].nx	=	0.0f;
		useVertex[anzahl_punkte-2].ny	=	1.0f;
		useVertex[anzahl_punkte-2].nz	=	0.0f;

		// Punkt 1 = Mitte Bodenfläche
		useVertex[anzahl_punkte-1].x	=	x;
		useVertex[anzahl_punkte-1].y	=  y-0.5f * height;
		useVertex[anzahl_punkte-1].z	=	z;
		useVertex[anzahl_punkte-1].u	=	0.5f;
		useVertex[anzahl_punkte-1].v	=	0.5f;
		useVertex[anzahl_punkte-1].nx	=	0.0f;
		useVertex[anzahl_punkte-1].ny	= -1.0f;
		useVertex[anzahl_punkte-1].nz	=	0.0f;

		int mempos	=	pos;

		// ~~~~~~~~~~~~~~~
		// 1. Deckfläche
		// ~~~~~~~~~~~~~~~
		for ( i=0; i<segments; i++ )
		{
			if (i==segments-1)
				WriteVertexTriangle( mem, mempos, useVertex[anzahl_punkte-2], useVertex[0], useVertex[i]);
			else
				WriteVertexTriangle( mem, mempos, useVertex[anzahl_punkte-2], useVertex[i+1], useVertex[i]);
			mempos += 3*36;
		}
		// ~~~~~~~~~~~~~~~
		// 2. Bodenfläche
		// ~~~~~~~~~~~~~~~
		for ( i=0; i<segments; i++ )
		{
			// Memblock Index
			if (i==segments-1)
				WriteVertexTriangle(	mem,	mempos, useVertex[anzahl_punkte-1]
													, useVertex[i+segments]
													, useVertex[segments]			);
			else
				WriteVertexTriangle(	mem,	mempos, useVertex[anzahl_punkte-1]
													, useVertex[i+segments]
													, useVertex[i+segments+1]		);
			mempos += 3*36;
		}
		// ~~~~~~~~~~~~~~~
		// 3. Mantelfläche
		// ~~~~~~~~~~~~~~~
		for ( i=0; i<segments; i++ )
		{
			if (i==segments-1)
			{
				// A'B'AB
				WriteVertexPlain( mem, mempos	,	useVertex[i+segments]	,useVertex[i]
														,	useVertex[0]				,useVertex[segments],1.0f,1.0f);
			}
			else
			{
				// ABCD
				WriteVertexPlain( mem, mempos	,	useVertex[i+segments],	useVertex[i]
														,	useVertex[i+1],			useVertex[i+segments+1],1.0f,1.0f);

			}
			mempos += 6*36;
		}
		
		delete [] useVertex;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	void WriteVertexCylinderWithoutBottom( int mem, int pos, float x, float y, float z, float radius, float height, int segments )
	/////////////////////////////////////////////////////////////////////////////////////////////////
	{
		//.......*Q1*......
		//....*../.../*....
		//...*..*P1./..*...	pos = pos + 9*segments * 36
		//...**..|./*..Q4..
		//...*...|/..*/....
		//..P2...M...P4....
		//...*../.Q3.*.....
		//....*/./..*......
		//......*P3........

		if (mem==0) return;
		if (dbMemblockExist(mem)==0) return;
		
		// Local Variables
		float winkel = 360.0f/(float)segments;
		float phi;
		int i;

		// Vertices Array enthält Eckpunkte + 2*Mittelpunkte
		int anzahl_punkte=2+2*segments;
		vertex *useVertex = new vertex[anzahl_punkte];

		// Gültig für alle Punkte
		for ( i=0; i<anzahl_punkte; i++ )
		{
			useVertex[i].color=dbRGB(255,255,255);
		}

		// Punkte 0 bis Segments-1 = Deckfläche
		for ( i=0; i<segments; i++ )
		{
			phi=(float)i*winkel;
			useVertex[i].x	=	x+(float)(-dbSin(phi)*radius);
			useVertex[i].y	=	y+height*0.5f;
			useVertex[i].z	=	z+(float)(dbCos(phi)*radius);
			useVertex[i].u	=	(float)(0.5f-dbSin(phi)*0.5f);
			useVertex[i].v	=	(float)(0.5f-dbCos(phi)*0.5f);
			useVertex[i].nx	=	0.0f;
			useVertex[i].ny	=	1.0f;
			useVertex[i].nz	=	0.0f;
		}

		// Punkte Segments+2 bis 2*segments+2 = Bodenfläche
		for ( i=segments; i<2*segments; i++ )
		{
			useVertex[i].x	=	useVertex[i-segments].x;
			useVertex[i].y	=  y-0.5f * height;
			useVertex[i].z	=	useVertex[i-segments].z;
			useVertex[i].u	=	useVertex[i-segments].u;
			useVertex[i].v	=	useVertex[i-segments].v;
			useVertex[i].nx	=	0.0f;
			useVertex[i].ny	=  1.0f;
			useVertex[i].nz	=	0.0f;
		}

		// Punkt 0 = Mitte Deckfläche
		useVertex[anzahl_punkte-2].x	=	x;
		useVertex[anzahl_punkte-2].y	=	y+0.5f * height;
		useVertex[anzahl_punkte-2].z	=	z;
		useVertex[anzahl_punkte-2].u	=	0.5f;
		useVertex[anzahl_punkte-2].v	=	0.5f;
		useVertex[anzahl_punkte-2].nx	=	0.0f;
		useVertex[anzahl_punkte-2].ny	=	1.0f;
		useVertex[anzahl_punkte-2].nz	=	0.0f;

		// Punkt 1 = Mitte Bodenfläche
		useVertex[anzahl_punkte-1].x	=	x;
		useVertex[anzahl_punkte-1].y	=  y-0.5f * height;
		useVertex[anzahl_punkte-1].z	=	z;
		useVertex[anzahl_punkte-1].u	=	0.5f;
		useVertex[anzahl_punkte-1].v	=	0.5f;
		useVertex[anzahl_punkte-1].nx	=	0.0f;
		useVertex[anzahl_punkte-1].ny	= -1.0f;
		useVertex[anzahl_punkte-1].nz	=	0.0f;

		int mempos	=	pos;

		// ~~~~~~~~~~~~~~~
		// 1. Deckfläche
		// ~~~~~~~~~~~~~~~
		for ( i=0; i<segments; i++ )
		{
			if (i==segments-1)
				WriteVertexTriangle( mem, mempos, useVertex[anzahl_punkte-2], useVertex[0], useVertex[i]);
			else
				WriteVertexTriangle( mem, mempos, useVertex[anzahl_punkte-2], useVertex[i+1], useVertex[i]);
			mempos += 3*36;
		}
		// ~~~~~~~~~~~~~~~
		// 2. Mantelfläche
		// ~~~~~~~~~~~~~~~
		for ( i=0; i<segments; i++ )
		{
			if (i==segments-1)
			{
				// A'B'AB
				WriteVertexPlain( mem, mempos	,	useVertex[i+segments]	,useVertex[i]
														,	useVertex[0]				,useVertex[segments],1.0f,1.0f);
			}
			else
			{
				// ABCD
				WriteVertexPlain( mem, mempos	,	useVertex[i+segments],	useVertex[i]
														,	useVertex[i+1],			useVertex[i+segments+1],1.0f,1.0f);

			}
			mempos += 6*36;
		}
		
		delete [] useVertex;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	void WriteVertexDach(int mem, int pos, float x, float y, float z, float a, float b, float c)
	/////////////////////////////////////////////////////////////////////////////////////////////////
	{
		// pos = pos + 18 * 38 // = 2 Plains + 2 Triangles ( ONHE BODEN !!! ))
		//     F
		//    /|\
		//   / | \
		// C|- E -|B
		//  | / \ |
		// D|/- -\|A

		if (mem==0) return;
		if (dbMemblockExist(mem)==0) return;

		vertex A = { x+a*0.5f,	y,		z-c*0.5f, 0.0f,1.0f,0.0f, 0xffffffff, 0.0f,0.0f};
		vertex B = { x+a*0.5f,	y,		z+c*0.5f, 0.0f,1.0f,0.0f, 0xffffffff, 0.0f,0.0f};
		vertex C = { x-a*0.5f,	y,		z+c*0.5f, 0.0f,1.0f,0.0f, 0xffffffff, 0.0f,0.0f};
		vertex D = { x-a*0.5f,	y,		z-c*0.5f, 0.0f,1.0f,0.0f, 0xffffffff, 0.0f,0.0f};
		vertex E = { x,			y+b,	z-c*0.5f, 0.0f,1.0f,0.0f, 0xffffffff, 0.0f,0.0f};
		vertex F = { x,			y+b,	z+c*0.5f, 0.0f,1.0f,0.0f, 0xffffffff, 0.0f,0.0f};

		//Dach links CFED
		C.u=0.0;	C.v=1.0;
		D.u=1.0;	D.v=1.0;
		E.u=1.0;	E.v=0.0;
		F.u=0.0;	F.v=0.0;
		WriteVertexPlain( mem, pos, C, F, E, D);		pos += 6*36;

		//Dach rechts AEFB
		A.u=0.0;	A.v=1.0;
		B.u=1.0;	B.v=1.0;
		F.u=1.0;	F.v=0.0;
		E.u=0.0;	E.v=0.0;
		WriteVertexPlain( mem, pos, A, E, F, B); 		pos += 6*36;

		//Dach front DEA
		D.u=0.0;	D.v=1.0;
		A.u=1.0;	A.v=1.0;
		E.u=0.5;	E.v=0.0;
		WriteVertexTriangle( mem, pos, D, E, A); 		pos += 3*36;

		//Dach back BFC
		B.u=0.0; B.v=1.0;
		C.u=1.0; C.v=1.0;
		F.u=0.5; F.v=0.0;
		WriteVertexTriangle( mem, pos, B, F, C); 		pos += 3*36;

	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	void WriteVertexSiedlung(int mem, int pos, float x, float y, float z, float a, float b, float c)
	/////////////////////////////////////////////////////////////////////////////////////////////////
	{
		// pos = pos + 42 * 36 (BoxOhneBoden/Dach + Dach =24+18=42)
		//     F
		//    /|\
		//   / | \
		// C|- E -|B
		//  | / \ |
		// D|/- -\|A
		//  |     |
		// I|-----|H
		//  |     |
		// J|-----|G

		WriteVertexBoxWithoutBottom_Top(mem,pos, x, y+b*0.25f, z, a, b*0.5f, c);	pos += 24*36;
		WriteVertexDach(mem,pos, x, y+b*0.5f, z, a, b*0.5f, c);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	void WriteVertexStadt(int mem, int pos, float x, float y, float z, float a, float b, float c)
	/////////////////////////////////////////////////////////////////////////////////////////////////
	{
		//` pos = pos + 72 * 36 (BoxOhneBoden + Siedlung = 30+42=72)
		//`            F
		//`           /|\
		//`          / | \
		//`        C|- E -|B
		//`         | / \ |
		//`        D|/- -\|A
		//`         |     |
		//`K|------I|-----|H
		//` |       |     |
		//`L|------J|-----|G
		//` |             |
		//`O|-------------|N
		//` |             |
		//`P|-------------|M
		WriteVertexBoxWithoutBottom(mem,pos,x,y+b*0.25f,z,a,b*0.5f,c);		pos += 30*36;
		WriteVertexSiedlung(mem, pos, x+0.25f*a, y+0.5f*b, z, a*0.5f, b*0.5f, c);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////
	void WriteVertexTetraeder(int mem, int pos, float x, float y, float z, Float3 A, Float3 B, Float3 C, Float3 D)
	/////////////////////////////////////////////////////////////////////////////////////////////////
	{
		// pos = pos + 12*36 (4 Dreiecke)
		
		//			A
		//	     /	|  \	
		//	   /	D    \
		//	 /	/	M	\  \
		//	B	-	-	-	C
		// h = AM
		
		vertex vA = { x+A.x,	y+A.y,	z+A.z, 0.0f,1.0f,0.0f, 0xffffffff, 0.0f,0.0f};
		vertex vB = { x+B.x,	y+B.y,	z+B.z, 0.0f,1.0f,0.0f, 0xffff0000, 0.0f,0.0f};
		vertex vC = { x+C.x,	y+C.y,	z+C.z, 0.0f,1.0f,0.0f, 0xff00ff00, 0.0f,0.0f};
		vertex vD = { x+D.x,	y+D.y,	z+D.z, 0.0f,1.0f,0.0f, 0xff0000ff, 0.0f,0.0f};

		WriteVertexTriangle(mem,pos,vB,vA,vC);	pos += 3*36;
		WriteVertexTriangle(mem,pos,vD,vA,vB);	pos += 3*36;
		WriteVertexTriangle(mem,pos,vC,vA,vD);	pos += 3*36;
		WriteVertexTriangle(mem,pos,vC,vD,vB);	pos += 3*36;


	}
}