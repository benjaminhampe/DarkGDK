// thc_delete.h

#ifndef __THC_DELETE_H_INCLUDED__
#define __THC_DELETE_H_INCLUDED__

#include "DarkGDK.h"
#include "thc_is.h"

namespace thc
{
	void FileDelete(const char* pFile);
	void ImageDelete(int img);
	void MemblockDelete(int mem);
	void MeshDelete(int mesh);
	void ObjectDelete(int obj);
}

#endif