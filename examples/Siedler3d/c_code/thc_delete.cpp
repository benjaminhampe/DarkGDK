// thc_delete.cpp

#include "thc_delete.h"
#include "thc_is.h"
#include "DarkGDK.h"

namespace thc
{
	void FileDelete(const char* pFile)
	{
		if (IsFile(pFile)==1) dbDeleteFile((char*)pFile);
	}
	void ImageDelete(int img)
	{
		if (IsImage(img)) dbDeleteImage(img);
	}
	void MemblockDelete(int mem)
	{
		if (IsMemblock(mem)) dbDeleteMemblock(mem);
	}
	void MeshDelete(int mesh)
	{
		if (IsMesh(mesh)) dbDeleteMesh(mesh);
	}
	void ObjectDelete(int obj)
	{
		if (IsObject(obj)) dbDeleteObject(obj);
	}
}