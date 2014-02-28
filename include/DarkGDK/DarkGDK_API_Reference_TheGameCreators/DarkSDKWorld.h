/////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEXT COMMANDS ////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#define SDK_LPSTR DWORD

void	dbLoadBSP							( char* szFilename, char* szMap );
void	dbDeleteBSP							( void );
void	dbSetBSPCamera						( int iID );
void	dbSetBSPCameraCollision				( int iID, int iEntityID, float fRadius, int iResponse );
void	dbSetBSPObjectCollision				( int iID, int iEntityID, float fRadius, int iResponse );
void	dbSetBSPCollisionThreshhold			( int iID, float fSensitivity );
void	dbSetBSPCollisionOff				( int iID );
void	dbSetBSPCameraCollisionRadius		( int iID, int iEntityID, float fX, float fY, float fZ );
void	dbSetBSPObjectCollisionRadius		( int iID, int iEntityID, float fX, float fY, float fZ );
void	dbSetBSPCollisionHeightAdjustment	( int iID, float fHeight );
void	dbSetBSPMultiTexturingOn			( void );
void	dbSetBSPMultiTexturingOff			( void );
void	dbProcessBSPCollision				( int iID );

int		dbBSPCollisionHit					( int iID );
float	dbBSPCollisionX						( int iID );
float	dbBSPCollisionY						( int iID );
float	dbBSPCollisionZ						( int iID );

void	ConstructorWorld					( HINSTANCE hSetup, HINSTANCE hImage, HINSTANCE hCamera, HINSTANCE hObject );
void	DestructorWorld						( void );
void	SetErrorHandlerWorld				( LPVOID pErrorHandlerPtr );
void	PassCoreDataWorld					( LPVOID pGlobPtr );
void	RefreshD3DWorld						( int iMode );

void	dbStartBSP							( void );
void	dbEndBSP							( void );
void	dbUpdateBSP							( void );

void	dbSetBSPCollisionThreshold			( int iID, float fSensitivity );
