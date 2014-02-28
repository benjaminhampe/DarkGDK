// thc_log.cpp

#include "thc_log.h"
#include "DarkGDK.h"
#include "stdafx.h"

namespace thc
{
	myDATE heute;
	int log_count = 0;

	string getTime()
	{
        SYSTEMTIME st;
        GetSystemTime(&st);
		stringstream s;
		s<<"["<<log_count<<"]["<<st.wYear<<","<<st.wMonth<<","<<st.wDay<<"][";
		s<<st.wHour<<"h,"<<st.wMinute<<"m,"<<st.wSecond<<"s,"<<st.wMilliseconds<<"ms] ";
		log_count++;
		return s.str();
	}

	void out_init()
	{
		log_count=0;
		ofstream fout("log.thc");
		fout << getTime() << "*** THC LOGGING BEGIN ***" << endl;
	}
	void out(string& pTXT)
	{
		ofstream fout("log.thc",ios::app);
		fout << getTime() << pTXT<< endl;
	}
	void out(char* pC, string& pL)
	{
		ofstream fout("log.thc",ios::app);
		fout << getTime() << pC << pL << endl;
	}
	void out(char* pTXT)
	{
		ofstream fout("log.thc",ios::app);
		fout << getTime() << pTXT << endl;
	}
	void out(char* pTXT, float p)
	{
		ofstream fout("log.thc",ios::app);
		fout << getTime() << pTXT << " " << p << endl;
	}
	void out(char* pTXT, int p)
	{
		ofstream fout("log.thc",ios::app);
		fout << getTime() << pTXT << " " << p << endl;
	}
	void out(char* pTXT, bool p)
	{
		ofstream fout("log.thc",ios::app);
		fout << getTime() << pTXT << " " << p << endl;
	}
	void out_objects()
	{
		ofstream fout("log_objects.thc");
		fout << "Alle Objecte werden gecheckt." << endl;
		int count=0;
		for (int i=1; i<1000; i++)
		{
			fout << "ObjectNr." << i << " = " << dbObjectExist(i) << endl;
			if (dbObjectExist(i)) count++;
		}
		fout << "Anzahl Objecte = " << count << endl;
	}
	void out_images()
	{
		ofstream fout("log_images.thc");
		fout << "Alle Images werden gecheckt." << endl;
		int count=0;
		for (int i=1; i<1000; i++)
		{
			fout << "ImageNr." << i << " = " << dbImageExist(i) << endl;
			if (dbImageExist(i)) count++;
		}
		fout << "Anzahl Images = " << count << endl;
	}
}