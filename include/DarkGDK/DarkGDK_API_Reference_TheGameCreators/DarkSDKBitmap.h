/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BITMAP COMMANDS //////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <d3d9.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void				dbCreateBitmap							( int iID, int iWidth, int iHeight );
void 				dbLoadBitmap 							( char* szFilename, int iID );
void 				dbSaveBitmap 							( char* szFilename, int iID );
void 				dbLoadBitmap 							( char* szFilename );
void 				dbSaveBitmap 							( char* szFilename );
void 				dbCopyBitmap 							( int iID, int iToID );
void 				dbCopyBitmap							( int iID, int iX1, int iY1, int iX2, int iY2, int iToID, int iToX1, int iToY1, int iToX2, int iToY2 );
void 				dbDeleteBitmap	 						( int iID );
void 				dbFlipBitmap 							( int iID );
void 				dbMirrorBitmap 							( int iID );
void 				dbFadeBitmap 							( int iID, int iFade );
void 				dbBlurBitmap 							( int iID, int iBlurLevel );
void 				dbSetCurrentBitmap 						( int iID );

int 				dbCurrentBitmap 						( void );
int 				dbBitmapExist 							( int iID );
int 				dbBitmapWidth 							( int iID );
int					dbBitmapHeight 							( int iID );
int 				dbBitmapDepth 							( int iID );
int 				dbBitmapMirrored 						( int iID );
int 				dbBitmapFlipped 						( int iID );
int 				dbBitmapExist 							( void );
int 				dbBitmapWidth 							( void );
int 				dbBitmapHeight 							( void );
int 				dbBitmapDepth 							( void );
int 				dbBitmapMirrored 						( void );
int 				dbBitmapFlipped 						( void );

void 				dbGetBitmapData							( int iID, DWORD* dwWidth, DWORD* dwHeight, DWORD* dwDepth, LPSTR* pData, DWORD* dwDataSize, bool bLockData );
void 				dbSetBitmapData							( int bitmapindex, DWORD dwWidth, DWORD dwHeight, DWORD dwDepth, LPSTR pData, DWORD dwDataSize );

void				ConstructorBitmap						( HINSTANCE );
void				DestructorBitmap						( void );
void				SetErrorHandlerBitmap					( LPVOID pErrorHandlerPtr );
void				PassCoreDataBitmap						( LPVOID pGlobPtr );
void				RefreshD3DBitmap						( int iMode );
void				UpdateBitmapZeroOfNewBackbufferBitmap	( void );
