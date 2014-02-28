// thc_desktop.cpp

#include "thc_desktop.h"
#include "stdafx.h"
#include "DarkGDK.h"

namespace thc
{

	int DesktopX ( void ){ 	return GetSystemMetrics(SM_CXSCREEN);}
	int DesktopY ( void ){ 	return GetSystemMetrics(SM_CYSCREEN);}
	int DesktopZ ( void )
	{ 
		HDC hDC=GetDC(NULL);
		int bpp=GetDeviceCaps(hDC,BITSPIXEL);
		ReleaseDC(NULL,hDC);
		return bpp;
	}
	int thcDesktopHz ( void )
	{
		HDC hDC=GetDC(NULL);
		int dhz=GetDeviceCaps(hDC,VREFRESH);
		ReleaseDC(NULL,hDC);
		return dhz;
	}

	int ScreenX( void )	{	return dbScreenWidth();		}
	int ScreenY( void )	{	return dbScreenHeight();	}
	int ScreenZ( void )	{	return dbScreenDepth();		}

} // END NAMESPACE