
#ifndef __THC_TIMER_H_INCLUDED__
#define __THC_TIMER_H_INCLUDED__
// MICROTIMER.h

#include "stdafx.h"

class MicroTimer
{
	private:
	
	LARGE_INTEGER liFrequency;
	LARGE_INTEGER liTimeStart;
	LARGE_INTEGER liTime;
	
	public:

	MicroTimer()
	{
		QueryPerformanceFrequency(&liFrequency); 
		QueryPerformanceCounter( &liTime);
		QueryPerformanceCounter( &liTimeStart );
	};
	~MicroTimer()
	{};

	int			 getFreqency();

	void		 update();
	void		 setTime();
	int			 getTime();
	double		 getExactTime();

};

inline void MicroTimer::update()
{
	QueryPerformanceCounter( &liTime);
}

inline int MicroTimer::getFreqency()
{ 
	return (int)liFrequency.QuadPart; 
}

// setzt eine neue Startzeit
inline void MicroTimer::setTime()
{ 
	update();
	liTimeStart=liTime;
}

// gibt die Mikrosekunden als ganze Zahl zurück die seit dem letzen setTime() vergangen sind
inline int MicroTimer::getTime()
{
	update();
	return (int)((double)(1000000*(liTime.QuadPart-liTimeStart.QuadPart))/(double)liFrequency.QuadPart);
}

// gibt die Mikrosekunden als Komma Zahl zurück die seit dem letzen setTime() vergangen sind
inline double MicroTimer::getExactTime()
{
	update();
	return (double)(1000000*(liTime.QuadPart-liTimeStart.QuadPart))/(double)liFrequency.QuadPart;
}

// MICROTIMER -- GLOBAL
extern MicroTimer timer;

#endif