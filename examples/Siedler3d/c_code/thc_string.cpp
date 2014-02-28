// thc_string.cpp

#include "thc_string.h"
#include "stdafx.h"

namespace thc
{
	void STRING_TRIM(string& str)
	{
		string::size_type pos = str.find_last_not_of(' ');
		if(pos != string::npos) 
		{
			str.erase(pos + 1);
			pos = str.find_first_not_of(' ');
			if(pos != string::npos) str.erase(0, pos);
		}
		else 
			str.erase(str.begin(), str.end());
	}
	void STRING_TOLOWER(string& Name)
	{
		for( unsigned int i = 0; i < Name.size( ); i++ )
		Name[i] = tolower( Name[i] );
	}
	void STRING_TOUPPER(string& Name)
	{
		for( unsigned int i = 0; i < Name.size( ); i++ )
		Name[i] = toupper( Name[i] );
	}
	bool STRING_COMPARE(string str1, string str2)
	{
		if (str1.size()!=str2.size())
		{	
			return false;
		}
		else
		{
			if (strcmp(	str1.c_str(),str2.c_str())==0) 
					return true;
			else	
					return false;
		}
	}
	void STRING_SPLIT(const string& full, const string& find, string& left, string& right)
	{  
		string::size_type pos = full.find(find.c_str());
		if (pos == string::npos) return;
		left=full.substr(0,pos);
		right=full.substr(pos+1);
	}
	void STRING_RSPLIT(const string& full, const string& find, string& left, string& right)
	{  
		string::size_type pos = full.rfind(find.c_str());
		if (pos == string::npos) return;
		left=full.substr(0,pos);
		right=full.substr(pos+1);
	}
	void STRING_LEFT(const string& full, const string& find, string& left)
	{  
		string::size_type pos = full.find(find.c_str());
		if (pos == string::npos) return;
		left=full.substr(0,pos);
	}
	void STRING_RIGHT(const string& full, const string& find, string& right)
	{ 
		string::size_type pos = full.find(find.c_str());
		if (pos == string::npos) return;
		right=full.substr(pos+1);
	}
	void STRING_RLEFT(const string& full, const string& find, string& left)
	{ 
		string::size_type pos = full.rfind(find.c_str());
		if (pos == string::npos) return;
		left=full.substr(0,pos);
	}
	void STRING_RRIGHT(const string& full, const string& find, string& right)
	{	
		string::size_type pos = full.rfind(find.c_str());
		if (pos == string::npos) return;
		right=full.substr(pos+1);
	}
	string STRING_GETPATH (const string& full)
	{
		string path="";
		string::size_type pos = full.rfind("\\");
		if (pos == string::npos) return path;
		path=full.substr(0,pos);
		STRING_TRIM(path);
		return path;
	}

}