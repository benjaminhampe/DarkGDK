/////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAMERA COMMANDS //////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <d3dx9.h>
#include <windows.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void		dbPositionCamera				( float fX, float fY, float fZ );
void		dbRotateCamera					( float fX, float fY, float fZ );
void		dbXRotateCamera					( float fX );
void		dbYRotateCamera					( float fY );
void		dbZRotateCamera					( float fZ );
void		dbPointCamera					( float fX, float fY, float fZ );
void		dbMoveCamera					( float fStep );
void		dbSetCameraRange 				( float fFront, float fBack );
void		dbSetCameraView 				( int iLeft, int iTop, int iRight, int iBottom );
void		dbClearCameraView 				( DWORD dwColorValue );
void		dbSetCameraRotationXYZ 			( void );
void		dbSetCameraRotationZYX			( void );
void		dbSetCameraFOV 					( float fAngle );
void		dbSetCameraAspect 				( float fAspect );
void		dbSetCameraToFollow 			( float fX, float fY, float fZ, float fAngle, float fDistance, float fHeight, float fSmooth, int iCollision );
void		dbAutoCamOn						( void );
void		dbAutoCamOff 					( void );
void		dbTurnCameraLeft 				( float fAngle );
void		dbTurnCameraRight 				( float fAngle );
void		dbPitchCameraUp 				( float fAngle );
void		dbPitchCameraDown 				( float fAngle );
void		dbRollCameraLeft 				( float fAngle );
void		dbRollCameraRight				( float fAngle );
void		dbSetCameraToObjectOrientation	( int iObjectID );

void		dbBackdropOn					( void ); 
void		dbBackdropOff					( void ); 
void		dbColorBackdrop					( DWORD dwColor ); 
void		dbColorBackdrop					( int iID, DWORD dwColor );
void		dbBackdropTexture				( int iImage ); 
void		dbBackdropScroll				( int iU, int iV ); 

float		dbCameraPositionX				( void );
float		dbCameraPositionY				( void );
float		dbCameraPositionZ				( void );
float		dbCameraAngleX					( void );
float		dbCameraAngleY					( void );
float		dbCameraAngleZ					( void );

void		dbMakeCamera					( int iID );
void		dbDeleteCamera					( int iID );
void		dbSetCurrentCamera				( int iID );
void		dbSetCameraToImage				( int iID, int iImage, int iWidth, int iHeight );
void		dbSetCameraToImage				( int iID, int iImage, int iWidth, int iHeight, int iGenAlpha );
void		dbResetCamera					( int iID );
void		dbMoveCameraLeft  				( int iID, float fStep );
void		dbMoveCameraRight 				( int iID, float fStep );
void		dbMoveCameraUp    				( int iID, float fStep );
void		dbMoveCameraDown				( int iID, float fStep );

void		dbControlCameraUsingArrowKeys	( int iID, float fVelocity, float fTurnSpeed );

void		dbPositionCamera				( int iID, int iVector );
void		dbSetVector3ToCameraPosition	( int iVector, int iID );
void		dbRotateCamera					( int iID, int iVector );
void		dbSetVector3ToCameraRotation	( int iVector, int iID );

void		dbPositionCamera				( int iID, float fX, float fY, float fZ );
void		dbRotateCamera    				( int iID, float fX, float fY, float fZ );
void		dbXRotateCamera   				( int iID, float fX );
void		dbYRotateCamera   				( int iID, float fY );
void		dbZRotateCamera   				( int iID, float fZ );
void		dbPointCamera     				( int iID, float fX, float fY, float fZ );
void		dbMoveCamera      				( int iID, float fStep );
void		dbSetCameraRange  				( int iID, float fFront, float fBack );
void		dbSetCameraView					( int iID, int iLeft, int iTop, int iRight, int iBottom );
void		dbClearCameraView				( int iID, DWORD dwColorValue );
void		dbClearCameraView				( int iID, int iRed, int iGreen, int iBlue );
void		dbSetCameraRotationXYZ			( int iID );
void		dbSetCameraRotationZYX			( int iID );
void		dbSetCameraFOV					( int iID, float fAngle );
void		dbSetCameraAspect				( int iID, float fAspect );
void		dbSetCameraToFollow 			( int iID, float fX, float fY, float fZ, float fAngle, float fDistance, float fHeight, float fSmooth, int iCollision );
void		dbTurnCameraLeft  				( int iID, float fAngle );
void		dbTurnCameraRight 				( int iID, float fAngle );
void		dbPitchCameraUp   				( int iID, float fAngle );
void		dbPitchCameraDown 				( int iID, float fAngle );
void		dbRollCameraLeft  				( int iID, float fAngle );
void		dbRollCameraRight				( int iID, float fAngle );
void		dbSetCameraToObjectOrientation	( int iID, int iObjectID );

void		dbBackdropOn					( int iID );
void		dbBackdropOff					( int iID );
void		dbBackdropColor					( DWORD dwColor );
void		dbBackdropTexture				( int iID, int iImage );
void		dbBackdropScroll				( int iID, int iU, int iV );

float		dbCameraPositionX				( int iID );
float		dbCameraPositionY 				( int iID );
float		dbCameraPositionZ	 			( int iID );
float		dbCameraAngleX		  			( int iID );
float		dbCameraAngleY	    			( int iID );
float		dbCameraAngleZ    				( int iID );
float		dbCameraLookX	 				( int iID );
float		dbCameraLookY	 				( int iID );
float		dbCameraLookZ 					( int iID );

void*		dbGetCameraInternalData			( int iID );

void		UpdateCamera					( void );
void		ConstructorCamera 				( HINSTANCE hSetup, HINSTANCE hImage );
void		DestructorCamera				( void );
void		SetErrorHandlerCamera			( LPVOID pErrorHandlerPtr );
void		PassCoreDataCamera				( LPVOID pGlobPtr );
void		RefreshD3DCamera 				( int iMode );

void		dbSetAutoCam					( float fX, float fY, float fZ, float fRadius );
void 		dbCameraInternalUpdate			( int iID );

void  		dbStartScene					( void );
int   		dbFinishScene					( void );
int			dbFinishSceneEx					( bool bKnowInAdvanceCameraIsUsed );

void  		dbStartSceneEx					( int iMode );
int	  		dbGetRenderCamera				( void );

D3DXMATRIX	dbGetViewMatrix					( int iID );
D3DXMATRIX	dbGetProjectionMatrix			( int iID );

void		dbTextureBackdrop				( int iImage ); 
void		dbScrollBackdrop				( int iU, int iV ); 
void		dbTextureBackdrop				( int iID, int iImage );
void		dbScrollBackdrop				( int iID, int iU, int iV );

void		dbSetCameraClip					( int iID, int iOnOff, float fX, float fY, float fZ, float fNX, float fNY, float fNZ );

void		dbRunCode						( int iMode );

/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
