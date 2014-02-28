// thc_capture.h

#ifndef __IMAGE_DLL_CAPTURE_H_INCLUDED__
#define __IMAGE_DLL_CAPTURE_H_INCLUDED__

#include "stdafx.h"

namespace thc
{
	int CaptureDesktopToImageFile(LPSTR pSave); 
	int CaptureScreenToImageFile(LPSTR pSave); 
	int CaptureWindowToImageFile(HWND hWndSc, LPSTR pSave);
}
#endif

