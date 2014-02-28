// thc_text.h
// aus Cloggy's D3D-DLL

#ifndef __THC_TEXT_H_INCLUDED__
#define __THC_TEXT_H_INCLUDED__

#include "stdafx.h"
#define D3DFVF_2D_VERTEX		(D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

namespace thc
{
	struct TransformedVertex			// D3D_FVF_2D_VERTEX
	{
		 float x, y, z, w;				// Position of vertex in 3D space
		 DWORD color;					// Colour of vertex
	};

	struct FontInfo
	{
		 LPSTR			sFontname;		// Font name (3D Text)
		 ID3DXFont*		pFont;			// Font ptr (2D Text)
		bool			bBold;			// Is bold (3D Text)
		bool			bItalic;		// Is italic (3D Text)
		int				iHeight;		// Font size (3D Text)
	};

	extern IDirect3DDevice9*	g_pD3DDevice;
	extern ID3DXSprite*			g_pTextSprite;
	extern DWORD				g_Forecolour;
	extern D3DVIEWPORT9			g_pViewPort;
	extern FontInfo*			fiFont;

	void InitTextD3D();
	void TextColor(int iFont, int iX, int iY, int iAlign, LPSTR pString, DWORD dwColour);
	void Text(int iFont, int iX, int iY, int iAlign, LPSTR pString);
	void StartText(void);
	void EndText(void);
	void SetFont(int iFont, LPSTR pFont, int iSize, int iBold, int iItalic, int iMeasurement);
	int  GetTextWidth(int iFont, LPSTR pString);
	int  GetTextHeight(int iFont, LPSTR pString);
}

#endif