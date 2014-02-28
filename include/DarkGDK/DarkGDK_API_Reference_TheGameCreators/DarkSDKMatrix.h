/////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEXT COMMANDS ////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void	dbMakeMatrix					( int iID, float fWidth, float fDepth,  int iXSegmented, int iZSegmented );
void	dbDeleteMatrix					( int iID );
void	dbFillMatrix					( int iID, float fHeight, int iTile );
void	dbGhostMatrixOn					( int iID );
void	dbGhostMatrixOff				( int iID );
void	dbPositionMatrix				( int iID, float fX, float fY, float fZ );
void	dbPrepareMatrixTexture			( int iID, int iImage, int iAcross, int iDown );
void	dbRandomizeMatrix				( int iID, int iHeight );
void	dbSetMatrixHeight				( int iID, int iX, int iZ, float fHeight );
void	dbSetMatrixNormal				( int iID, int iX, int iZ, float fX, float fY, float fZ );
void	dbSetMatrixTexture				( int iID, int iTextureMode, int iMipGen );
void	dbSetMatrixTile					( int iID, int iX, int iZ, int iTile );
void	dbSetMatrixWireframeOn			( int iID );
void	dbGhostMatrixOn					( int iID, int iMode );
void	dbSetMatrixWireframeOff			( int iID );
void	dbSetMatrix						( int iID, int bWireframe, int bTransparency, int bCull, int iFilter, int bLight, int bFog, int bAmbient );
void	dbShiftMatrixUp					( int iID );
void	dbShiftMatrixDown				( int iID );
void	dbShiftMatrixLeft				( int iID );
void	dbShiftMatrixRight				( int iID );
void	dbUpdateMatrix					( int iID );

void	dbSetMatrixTrim					( int iID, float fTrimX, float fTrimY );
void	dbSetMatrixPriority				( int iID, int iPriority );

void	dbPositionMatrix				( int iID, int iVector );
void	dbSetVector3ToMatrixPosition	( int iVector, int iID );
void	dbRotateMatrix					( int iID, int iVector );
void	dbSetVector3ToMatrixRotation	( int iVector, int iID );

float	dbMatrixPositionX				( int iID );
float	dbMatrixPositionY				( int iID );
float	dbMatrixPositionZ				( int iID );
float	dbGetGroundHeight				( int iID, float fX, float fZ );
float	dbGetMatrixHeight				( int iID, int iX, int iZ );
int		dbMatrixExist					( int iID );
int		dbMatrixTileCount				( int iID );
int		dbMatrixTilesExist				( int iID );
int		dbMatrixWireframeState			( int iID );

void	UpdateMatrix					( void );
void	UpdateLastMatrix				( void );
void	ConstructorMatrix				( HINSTANCE hSetup, HINSTANCE hImage );
void	DestructorMatrix				( void );
void	SetErrorHandlerMatrix			( LPVOID pErrorHandlerPtr );
void	PassCoreDataMatrix				( LPVOID pGlobPtr );
void	RefreshD3DMatrix				( int iMode );
