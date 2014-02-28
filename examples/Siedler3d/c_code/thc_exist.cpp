// thc_exist.cpp

#include "thc_exist.h"
#include "stdafx.h"


namespace thc
{
	bool file_exist(string pFile)
	{
		ifstream in(pFile.c_str());
		bool exist=in.is_open();
		if (in.is_open()==false)
		{
			stringstream s;
			s << "Die Datei " << pFile << " konnte nicht geoeffnet werden.";
			MessageBoxA(0, (LPCSTR)s.str().c_str() ,"Fehler in file_exist()",0);
			return false;
		}
		return true;
	}
}