/////////////////////////////////////////////////////////////////////////////////////////////////////////
// IMAGE COMMANDS ///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <d3d9.h>
#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void 				dbLoadImage					( char* szFilename, int iID );
void 				dbLoadImage					( char* szFilename, int iID, int TextureFlag );
void 				dbLoadImage					( char* szFilename, int iID, int TextureFlag, int iDivideTextureSize );
void 				dbSaveImage					( char* szFilename, int iID );
void 				dbSaveImage					( char* szFilename, int iID, int iCompressionMode );
void 				dbGetImage					( int iID, int iX1, int iY1, int iX2, int iY2 );
void 				dbGetImage					( int iID, int iX1, int iY1, int iX2, int iY2, int iTextureFlag );
void 				dbPasteImage				( int iID, int iX, int iY );
void 				dbPasteImage				( int iID, int iX, int iY, int iFlag );
void 				dbDeleteImage				( int iID );						
void 				dbRotateImage				( int iID, int iAngle );			
int  				dbImageExist				( int iID );

void  				dbSetImageColorKey			( int iR, int iG, int iB );
void  				dbSaveIconFromImage			( char* pFilename, int iID );
DWORD 				dbLoadIcon					( char* pFilename );
void  				dbFreeIcon					( DWORD dwIconHandle );

void 				dbGetImageData				( int iID, DWORD* dwWidth, DWORD* dwHeight, DWORD* dwDepth, LPSTR* pData, DWORD* dwDataSize, bool bLockData );
void 				dbSetImageData				( int iID, DWORD dwWidth, DWORD dwHeight, DWORD dwDepth, LPSTR pData, DWORD dwDataSize );

LPDIRECT3DTEXTURE9	dbGetImagePointer			( int iID );
LPDIRECT3DTEXTURE9	dbMakeImage					( int iID, int iWidth, int iHeight );
LPDIRECT3DTEXTURE9	dbMakeImageUsage			( int iID, int iWidth, int iHeight, DWORD dwUsage );
LPDIRECT3DTEXTURE9	dbMakeImageJustFormat		( int iID, int iWidth, int iHeight, D3DFORMAT Format );
LPDIRECT3DTEXTURE9	dbMakeImageRenderTarget		( int iID, int iWidth, int iHeight, D3DFORMAT Format );
LPDIRECT3DTEXTURE9	dbGetImagePointer			( int iID );
int					dbGetImageWidth				( int iID );
int					dbGetImageHeight			( int iID );
void 				dbPasteImage				( int iID, int iX, int iY );
void 				dbPasteImage				( int iID, int iX, int iY, int iFlag );

void 				ConstructorImage			( HINSTANCE hSetup );
void 				DestructorImage				( void );
void 				SetErrorHandlerImage		( LPVOID pErrorHandlerPtr );
void 				PassSpriteInstanceImage		( HINSTANCE hSprite );
void				RefreshD3DImage				( int iMode );
void				PassCoreDataImage			( LPVOID pGlobPtr );

int					dbLoadImageInternal			( char* szFilename );
int					dbLoadImageInternal			( char* szFilename, int iDivideTextureSize );

bool 				dbGetImageExist				( int iID );
LPSTR 				dbGetImageName				( int iID );

void				dbSetImageSharing			( bool bMode );
void				dbSetImageMemory			( int iMode );

void				dbLockImage					( int iID );
void				dbUnlockImage				( int iID );
void				dbWriteImage				( int iID, int iX, int iY, int iA, int iR, int iG, int iB );
void				dbGetImage					( int iID, int iX, int iY, int* piR, int* piG, int* piB );

void				dbSetImageMipmapMode		( bool bMode );
void 				dbSetImageMipmapType 		( int iType );
void				dbSetImageMipmapBias 		( float fBias );
void 				dbSetImageMipmapNum  		( int iNum );
void 				dbSetImageTranslucency 		( int iID, int iPercent );

void				dbSetImageCubeFace			( int iID, LPDIRECT3DCUBETEXTURE9 pCubeMap, int iFace );
void				dbGetImageCubeFace			( int iID, LPDIRECT3DCUBETEXTURE9* ppCubeMap, int* piFace );

bool 				dbLoadImageEx				( char* szFilename, int iID );

float				dbGetImageUMax				( int iID );
float				dbGetImageVMax				( int iID );

void				dbStretchImage				( int iID, int iSizeX, int iSizeY );
