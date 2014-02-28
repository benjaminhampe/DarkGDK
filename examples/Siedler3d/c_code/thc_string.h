// thc_string.h

#ifndef __THC_STRING_H_INCLUDED__
#define __THC_STRING_H_INCLUDED__

#include "stdafx.h"

namespace thc
{
	bool STRING_COMPARE(string str1, string str2);
	void STRING_TRIM(string& str);
	void STRING_TOLOWER(string& Name);
	void STRING_TOUPPER(string& Name);
	void STRING_SPLIT	(const string& full, const string& find, string& left, string& right);
	void STRING_RSPLIT	(const string& full, const string& find, string& left, string& right);
	void STRING_LEFT	(const string& full, const string& find, string& left);
	void STRING_RIGHT	(const string& full, const string& find, string& right);
	void STRING_RLEFT	(const string& full, const string& find, string& left);
	void STRING_RRIGHT	(const string& full, const string& find, string& right);
	string STRING_GETPATH (const string& full);	// gibt den Pfad eines Dateinamens zurück
}

#endif