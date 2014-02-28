/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BASIC 2D COMMANDS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void	dbCLS					( DWORD RGBBackColor );
void	dbInk					( DWORD RGBForeColor, DWORD RGBBackColor );
void	dbDot					( int iX, int iY );
void	dbBox					( int iLeft, int iTop, int iRight, int iBottom );
void	dbLine					( int iXa, int iYa, int iXb, int iYb );
void	dbCircle				( int iX, int iY, int iRadius );
void	dbElipse				( int iX, int iY, int iXRadius, int iYRadius );
DWORD	dbRgb					( int iRed, int iGreen, int iBlue );
int		dbRgbR					( DWORD iRGB );
int		dbRgbG					( DWORD iRGB );
int		dbRgbB					( DWORD iRGB );
DWORD	dbPoint					( int iX, int iY );

void	dbDot					( int iX, int iY, DWORD dwColor );
void	dbBox					( int iLeft, int iTop, int iRight, int iBottom, DWORD dw1, DWORD dw2, DWORD dw3, DWORD dw4 );
void	dbLockPixels			( void );
void	dbUnLockPixels			( void );
DWORD	dbGetPixelsPointer		( void );
DWORD	dbGetPixelsPitch		( void );

void	ConstructorBasic2D		( HINSTANCE );
void	DestructorBasic2D		( void );
void	SetErrorHandlerBasic2D	( LPVOID pErrorHandlerPtr );
void	PassCoreDataBasic2D		( LPVOID pGlobPtr );
void	RefreshD3DBasic2D		( int iMode );
void	UpdateBPPBasic2D		( void );
void	dbCopyArea				( int iDestX, int iDestY, int iWidth, int iHeight, int iSourceX, int iSourceY );

DWORD	dbRGB					( int iRed, int iGreen, int iBlue );
int		dbRGBR					( DWORD iRGB );
int		dbRGBG					( DWORD iRGB );
int		dbRGBB					( DWORD iRGB );
void	dbEllipse				( int iX, int iY, int iXRadius, int iYRadius );
void	dbUnlockPixels			( void );
