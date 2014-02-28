// thc_log.h

#ifndef __THC_LOG_H_INCLUDED__
#define __THC_LOG_H_INCLUDED__

#include "stdafx.h"

namespace thc
{
	struct myDATE{ string datum, zeit;};

	extern myDATE heute;
	extern int log_count;

	string getTime();
	void out_init();
	void out(string& pTXT);
	void out(char* pC, string& pL);
	void out(char* pTXT);
	void out(char* pTXT, float p);
	void out(char* pTXT, int p);
	void out(char* pTXT, bool p);
	void out_objects();
	void out_images();
}

#endif