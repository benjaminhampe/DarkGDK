// thc_object.cpp

#include "DarkGDK.h"
#include "thc_mesh.h"
#include "thc_free.h"
#include "thc_is.h"
#include "thc_delete.h"
namespace thc
{
	int ObjectFromMesh(int mesh,int tex)
	{
		if (IsMesh(mesh)==false) return 0;
		if (IsImage(tex)==false) tex=0;
		int obj=FreeObject();
		dbMakeObject(obj,mesh,tex);
		if (IsObject(obj)==false) return 0;
		return obj;
	}
	int ObjectFromMeshMemblock(int mem,int tex)
	{
		int mesh=MeshFromMemblock(mem);
		if (mesh==0) return 0;
		int obj=ObjectFromMesh(mesh,tex);
		MeshDelete(mesh);
		if (IsObject(obj)==false) return 0;
		return obj;
	}

}