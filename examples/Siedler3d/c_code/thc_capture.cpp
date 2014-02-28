// thc_capture.cpp

#include "thc_capture.h"
#include "stdafx.h"
#include "globstruct.h"

namespace thc
{

	int CaptureDesktopToImageFile(LPSTR pSave) 
	{
		HWND    hWndSc = ::GetDesktopWindow();
		return CaptureWindowToImageFile(hWndSc,pSave);
	}
	int CaptureScreenToImageFile(LPSTR pSave) 
	{
		HWND    hWndSc = g_pGlob->hWnd;
		return CaptureWindowToImageFile(hWndSc,pSave);
	}

	int CaptureWindowToImageFile(HWND hWndSc, LPSTR pSave)
	{
		// Bild aufnehmen
		if (!hWndSc) return 0;
		RECT		rc;
		::GetWindowRect(hWndSc, &rc);

		int nWidth  = rc.right  - rc.left;
		int nHeight = rc.bottom - rc.top;

		HDC     hdc    = ::GetDC(hWndSc);
		HDC     memDC  = ::CreateCompatibleDC(hdc);
		HBITMAP hbm    = ::CreateCompatibleBitmap(hdc, nWidth, nHeight);
		HBITMAP hbmOld = (HBITMAP)::SelectObject(memDC, hbm);

	   // ::BringWindowToTop(hWnd);
	   int ret = ::BitBlt(memDC, 0, 0, nWidth,  nHeight, hdc, rc.left, rc.top, SRCCOPY);
		// The BitBlt function performs a bit-block transfer of
		// the color data corresponding to a rectangle of pixels
		// from the specified source device context into a destination device context.
		//
		//	BOOL BitBlt(
		//		HDC hdcDest, // handle to destination DC
		//		int nXDest,  // x-coord of destination upper-left corner
		//		int nYDest,  // y-coord of destination upper-left corner
		//		int nWidth,  // width of destination rectangle
		//		int nHeight, // height of destination rectangle
		//		HDC hdcSrc,  // handle to source DC
		//		int nXSrc,   // x-coordinate of source upper-left corner
		//		int nYSrc,   // y-coordinate of source upper-left corner
		//		DWORD dwRop  // raster operation code
		// );
		/////////////////////////////////////////////////////////////////
		// Bilddaten ermitteln
		BITMAPINFO bmi;
		ZeroMemory(&bmi, sizeof(bmi));
		bmi.bmiHeader.biSize         = sizeof(BITMAPINFOHEADER);
		bmi.bmiHeader.biWidth        = nWidth;
		bmi.bmiHeader.biHeight       = nHeight;
		bmi.bmiHeader.biBitCount     = 24;
		bmi.bmiHeader.biPlanes       = 1;
		bmi.bmiHeader.biCompression  = BI_RGB;
		bmi.bmiHeader.biSizeImage    = 32 * nWidth * nHeight / 8;

		BYTE *pbBits = new BYTE[bmi.bmiHeader.biSizeImage];

		::GetDIBits(    memDC,
						hbm,
						0,
						bmi.bmiHeader.biHeight,
						pbBits,
						&bmi,
						DIB_RGB_COLORS
					);

			// The GetDIBits function retrieves the bits of the specified compatible
			// bitmap and copies them into a buffer as a DIB using the specified format.

			// int GetDIBits(
			//		HDC hdc,           // handle to DC
			//		HBITMAP hbmp,      // handle to bitmap
			//		UINT uStartScan,   // first scan line to set
			//		UINT cScanLines,   // number of scan lines to copy
			//		LPVOID lpvBits,    // array for bitmap bits
			//		LPBITMAPINFO lpbi, // bitmap data buffer
			//		UINT uUsage        // RGB or palette index
			// );

		BITMAPFILEHEADER bfh;
		bfh.bfType      = ('M' << 8) + 'B';
		bfh.bfSize      = sizeof(BITMAPFILEHEADER)
						   + bmi.bmiHeader.biSizeImage
						   + sizeof(BITMAPINFOHEADER);
		bfh.bfReserved1 = 0;
		bfh.bfReserved2 = 0;
		bfh.bfOffBits   = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

		/////////////////////////////////////////////////////////////////
		// Bilddaten speichern
		HANDLE hfile = CreateFileA( (LPCSTR)pSave,
									GENERIC_WRITE,
									0,
									0,
									OPEN_ALWAYS,
									0,
									0
								);

		DWORD dwWritten;
		WriteFile(hfile, &bfh,           sizeof(bfh),               &dwWritten, NULL);
		WriteFile(hfile, &bmi.bmiHeader, sizeof(BITMAPINFOHEADER),  &dwWritten, NULL);
		WriteFile(hfile, pbBits,         bmi.bmiHeader.biSizeImage, &dwWritten, NULL);
		CloseHandle(hfile);

		::SelectObject(memDC, hbmOld);
		::DeleteDC(memDC);
		::ReleaseDC(hWndSc, hdc);
		::DeleteObject(hbm);
		delete[] pbBits;
		 return 1;
	}

}	// END NAMESPACE