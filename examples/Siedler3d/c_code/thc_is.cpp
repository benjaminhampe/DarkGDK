// thc_is.cpp

#include "stdafx.h"
#include "DarkGDK.h"


#include "thc_is.h"
#include "thc_string.h"

namespace thc
{
	bool IsMemblock( int iID )
	{
		if (iID <= 0)					return false;
		if (dbMemblockExist(iID)==0 )	return false;
		return true;
	}
	bool IsImage(int iID)
	{
		if (iID <= 0)				return false;
		if (dbImageExist(iID)==0 )	return false;
		return true;
	}
	bool IsObject( int iID )
	{
		if (iID <= 0)				return false;
		if (dbObjectExist(iID)==0)	return false;
		return true;
	}
	bool IsMesh(int iID)
	{
		if (iID <= 0)				return false;
		if (dbMeshExist(iID)==0 )	return false;
		return true;
	}

	bool IsFile(const char* szFile)
	{
		// Abbruchbedingung
		if (!szFile) return false;

		// Versuche die Datei zu öffnen
		ifstream in(szFile);

		// Wenn Datei nicht geöffnet werden kann -> ABBRUCH
		if (in.is_open()==false)
		{
			stringstream s;
			s << "Die Datei " << szFile << " konnte nicht geoeffnet werden.";
			MessageBoxA(0, (LPCSTR)s.str().c_str() ,"Fehler in IsFile()",0);
			return false;
		}

		// Schliesse Datei und beende Funktion erfolgreich
		in.close();
		return true;
	}
	bool IsImageFile(const char* szFile)
	{
		// Abbruchbedingung
		if (!szFile) return false;

		// Versuche die Datei zu öffnen
		ifstream in(szFile);

		// Wenn Datei nicht geöffnet werden kann -> ABBRUCH
		if (in.is_open()==false)
		{
			stringstream s;	s << "Die Datei " << szFile << " konnte nicht geoeffnet werden.";
			MessageBoxA(0, (LPCSTR)s.str().c_str() ,"Fehler in IsFile()",0);
			return false;
		}
		in.close();		

		// Wandele szFile in std::string
		string file=szFile;

		// Suche nach "." in Dateinamen
		string::size_type pos = file.rfind(".");

		// Wenn "." nicht existiert -> ABBRUCH
		if (pos == string::npos)
		{
			stringstream s;	s << "Die Datei " << szFile << " hat keine Dateiendung.";
			MessageBoxA(0, (LPCSTR)s.str().c_str() ,"Fehler in IsFile()",0);
			return false;
		}

		// Hole String von "." bis Ende
		string ext=file.substr(pos+1);
		STRING_TOLOWER(ext);

		// Prüfe ob Dateiendung bekannt ist und unterstützt wird.
		if ((STRING_COMPARE(ext,"png")==0) &&
			(STRING_COMPARE(ext,"bmp")==0) &&
			(STRING_COMPARE(ext,"dib")==0) &&
			(STRING_COMPARE(ext,"dds")==0) &&
			(STRING_COMPARE(ext,"tga")==0) &&
			(STRING_COMPARE(ext,"jpg")==0) &&
			(STRING_COMPARE(ext,"jpeg")==0))
		{
			stringstream s;	s << "Die Datei " << szFile << " wird nicht unterstützt.";
			MessageBoxA(0, (LPCSTR)s.str().c_str() ,"Fehler in IsFile()",0);
			return false;
		}
		return true;
	}
}