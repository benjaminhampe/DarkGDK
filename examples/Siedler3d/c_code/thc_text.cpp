// thc_text.cpp
#pragma once
#include "thc_text.h"
#include "stdafx.h"
#include "DarkGDK.h"
#include "global.h"
#include "globstruct.h"

namespace thc
{

	IDirect3DDevice9*	g_pD3DDevice=NULL;
	ID3DXSprite*		g_pTextSprite=NULL;
	DWORD				g_Forecolour=0xFF000000;
	D3DVIEWPORT9		g_pViewPort;
	FontInfo*			fiFont=new FontInfo[20];

// Initialize
void InitTextD3D()
{
	// Grab device pointer
	g_pD3DDevice = dbGetDirect3DDevice();

	// Create sprite for 2D text
	if (g_pTextSprite != NULL) SAFE_RELEASE(g_pTextSprite);
	HRESULT hr = D3DXCreateSprite(g_pD3DDevice, &g_pTextSprite);

	// Default font
	SetFont(1, "Arial", 15, 0, 0, 0);
	for (int i = 1; i < 20; i++)
		fiFont[i] = fiFont[0];

	// Default drawing colour
	g_Forecolour = D3DCOLOR_ARGB(255, 255, 255, 255);
}

// Even prettier 2D text than the function below (Overriding colour)
void TextColor(int iFont, int iX, int iY, int iAlign, LPSTR pString, DWORD dwColour)
{
	// Valid font ID
	if ((iFont < 1) || (iFont > 20))
		return;
	else
		iFont--;

	RECT rctBox = {iX, iY, iX, 0};
	//RECT rctBox = {iX, iY, 0, 0};

	// Alignment
	switch (iAlign)
	{
		// Left
		case 0:
			fiFont[iFont].pFont->DrawText(g_pTextSprite, pString, -1, &rctBox, DT_NOCLIP, dwColour);
			break;
		// Center
		case 1:
			rctBox.left -= 5000;
			rctBox.right += 5000;
			fiFont[iFont].pFont->DrawText(g_pTextSprite, pString, -1, &rctBox, DT_NOCLIP | DT_CENTER, dwColour);
			break;
		// Right
		case 2:
			rctBox.left -= 5000;
			fiFont[iFont].pFont->DrawText(g_pTextSprite, pString, -1, &rctBox, DT_NOCLIP | DT_RIGHT, dwColour);
			break;
	}
}
// Pretty 2D text
void Text(int iFont, int iX, int iY, int iAlign, LPSTR pString)
{
	TextColor(iFont, iX, iY, iAlign, pString, g_Forecolour);
}

// Erm...Start Text
void StartText(void)
{

	g_pViewPort.X = 0;
    g_pViewPort.Y = 0;
    g_pViewPort.Width = g_pGlob->dwWindowWidth;
    g_pViewPort.Height = g_pGlob->dwWindowHeight;
	// TODO: Should these be CameraNear/Far?
    g_pViewPort.MinZ = 0.0f;
    g_pViewPort.MaxZ = 1.0f;
	g_pD3DDevice->SetViewport(&g_pViewPort);


	g_pTextSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_DEPTH_BACKTOFRONT);

	//g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	//g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	//g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE); 
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL); 
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, (DWORD)100); 
	//g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); 
}

// Again erm...End Text
void EndText(void)
{
	g_pTextSprite->End();
}

// Initialize a font
void SetFont(int iFont, LPSTR pFont, int iSize, int iBold, int iItalic, int iMeasurement)
{
	// Valid font ID
	if ((iFont < 1) || (iFont > 20))
		return;
	else
		iFont--;

	// Add details to font arrays
	fiFont[iFont].sFontname = pFont;
	fiFont[iFont].bBold = (iBold != 0);
	fiFont[iFont].bItalic = (iItalic != 0);

	iSize=-iSize;
	if (iMeasurement != 0)
	{
		// Calculate font size in pixels
		HDC hDC = GetDC(NULL);
		iSize = iSize * GetDeviceCaps(hDC, LOGPIXELSY) / 72;
		ReleaseDC(NULL, hDC);
	}
	fiFont[iFont].iHeight = iSize;

	HRESULT HR = D3DXCreateFont(g_pD3DDevice, iSize, 0, ((iBold != 0) ? FW_BOLD : FW_NORMAL), 1, ((iItalic != 0) ? true : false), DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH || FF_DONTCARE, pFont, &fiFont[iFont].pFont);

	fiFont[iFont].pFont->PreloadGlyphs(0, 255);
}

// These commands really need better names...I believe this returns the text width...but who knows for sure
int GetTextWidth(int iFont, LPSTR pString)
{
	// Valid font ID
	if ((iFont < 1) || (iFont > 20))
		return 0;
	else
		iFont--;

	RECT rctBounding;

	fiFont[iFont].pFont->DrawText(g_pTextSprite, pString, -1, &rctBounding, DT_CALCRECT, 0);

	return (rctBounding.right - rctBounding.left);
}

// Another dodgy name
int GetTextHeight(int iFont, LPSTR pString)
{
	// Valid font ID
	if ((iFont < 1) || (iFont > 20))
		return 0;
	else
		iFont--;

	RECT rctBounding;

	fiFont[iFont].pFont->DrawText(g_pTextSprite, pString, -1, &rctBounding, DT_CALCRECT, 0);

	return (rctBounding.bottom - rctBounding.top);
}
}