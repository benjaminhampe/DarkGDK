// thc_mesh.cpp

#include "DarkGDK.h"
#include "thc_free.h"
#include "thc_is.h"

namespace thc
{
	int MeshFromMemblock(int mem)
	{
		if (IsMemblock(mem)==0) return 0;
		int mesh=FreeMesh();
		dbMakeMeshFromMemblock(mesh,mem);
		if (IsMesh(mesh)==0) return 0;
		return mesh;
	}
}