/////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEXT COMMANDS ////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <d3dx9.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

bool			dbMakeVector2						( int iID );
bool			dbDeleteVector2						( int iID );
void			dbSetVector2						( int iID, float fX, float fY );
void			dbCopyVector2						( int iSource, int iDestination );
void			dbAddVector2						( int iResult, int iA, int iB );
void			dbSubtractVector2					( int iResult, int iA, int iB );
void			dbMultiplyVector2					( int iID, float fValue );
void			dbDivideVector2						( int iID, float fValue );
bool			dbIsEqualVector2					( int iA, int iB );
bool			dbIsNotEqualVector2					( int iA, int iB );
float			dbXVector2							( int iID );
float			dbYVector2							( int iID );
void			dbBCCVector2						( int iResult, int iA, int iB, int iC, float f, float g );
void			dbCatmullRomVector2					( int iResult, int iA, int iB, int iC, int iD, float s );
float			dbCCWVector2						( int iA, int iB );
float			dbDotProductVector2					( int iA, int iB );
void			dbHermiteVector2					( int iResult, int iA, int iB, int iC, int iD, float s );
float			dbLengthVector2						( int iID );
float			dbSquaredLengthVector2				( int iID );
void			dbLinearInterpolateVector2			( int iResult, int iA, int iB, float s );
void			dbMaximizeVector2					( int iResult, int iA, int iB );
void			dbMinimizeVector2					( int iResult, int iA, int iB );
void			dbNormalizeVector2					( int iResult, int iSource );
void			dbScaleVector2						( int iResult, int iSource, float s );
void			dbTransformCoordsVector2			( int iResult, int iSource, int iMatrix );

bool			dbMakeVector3						( int iID );
bool			dbDeleteVector3						( int iID );
void			dbSetVector3						( int iID, float fX, float fY, float fZ );
void			dbCopyVector3						( int iSource, int iDestination );
void			dbAddVector3						( int iResult, int iA, int iB );
void			dbSubtractVector3					( int iResult, int iA, int iB );
void			dbMultiplyVector3					( int iID, float fValue );
void			dbDivideVector3						( int iID, float fValue );
bool			dbIsEqualVector3					( int iA, int iB );
bool			dbIsNotEqualVector3					( int iA, int iB );
void			dbBCCVector3						( int iResult, int iA, int iB, int iC, float f, float g );
void			dbCatmullRomVector3					( int iResult, int iA, int iB, int iC, int iD, float s );
void  			dbCrossProductVector3				( int iResult, int iA, int iB );
void  			dbHermiteVector3					( int iResult, int iA, int iB, int iC, int iD, float s );
void  			dbLinearInterpolateVector3			( int iResult, int iA, int iB, float s );
void  			dbMaximizeVector3					( int iResult, int iA, int iB );
void  			dbMinimizeVector3					( int iResult, int iA, int iB );
void  			dbNormalizeVector3					( int iResult, int iSource );
void  			dbScaleVector3						( int iResult, int iSource, float s );
float 			dbDotProductVector3					( int iA, int iB );
float			dbLengthVector3						( int iID );
float			dbSquaredLengthVector3				( int iID );
void  			dbProjectVector3					( int iResult, int iSource, int iProjectionMatrix, int iViewMatrix, int iWorldMatrix );
void  			dbTransformCoordsVector3			( int iResult, int iSource, int iMatrix );
void  			dbTransformNormalsVector3			( int iResult, int iSource, int iMatrix );
float			dbXVector3							( int iID );
float			dbYVector3							( int iID );
float			dbZVector3							( int iID );

bool			dbMakeVector4						( int iID );
bool			dbDeleteVector4						( int iID );
void  			dbSetVector4						( int iID, float fX, float fY, float fZ, float fW );
void  			dbCopyVector4						( int iSource, int iDestination );
void  			dbAddVector4						( int iResult, int iA, int iB );
void  			dbSubtractVector4					( int iResult, int iA, int iB );
void  			dbMultiplyVector4					( int iID, float fValue );
void  			dbDivideVector4						( int iID, float fValue );
bool			dbIsEqualVector4					( int iA, int iB );
bool			dbIsNotEqualVector4					( int iA, int iB );
float			dbXVector4							( int iID );
float			dbYVector4							( int iID );
float			dbZVector4							( int iID );
float			dbWVector4							( int iID );
void  			dbBCCVector4						( int iResult, int iA, int iB, int iC, float f, float g );
void  			dbCatmullRomVector4					( int iResult, int iA, int iB, int iC, int iD, float s );
void  			dbHermiteVector4					( int iResult, int iA, int iB, int iC, int iD, float s );
float			dbLengthVector4						( int iID );
float			dbSquaredLengthVector4				( int iID );
void  			dbLinearInterpolateVector4			( int iResult, int iA, int iB, float s );
void  			dbMaximizeVector4					( int iResult, int iA, int iB );
void  			dbMinimizeVector4					( int iResult, int iA, int iB );
void  			dbNormalizeVector4					( int iResult, int iSource );
void  			dbScaleVector4						( int iResult, int iSource, float s );
void  			dbTransformVector4					( int iResult, int iSource, int iMatrix );

bool			dbMakeMatrix4						( int iID );
bool			dbDeleteMatrix4						( int iID );
void  			dbCopyMatrix4						( int iSource, int iDestination );
void  			dbAddMatrix4						( int iResult, int iA, int iB );
void  			dbSubtractMatrix4					( int iResult, int iA, int iB );
void  			dbMultiplyMatrix4					( int iResult, int iA, int iB );
void  			dbMultiplyMatrix4					( int iID, float fValue );
void  			dbDivideMatrix4						( int iID, float fValue );
bool			dbIsEqualMatrix4					( int iA, int iB );
bool			dbIsNotEqualMatrix4					( int iA, int iB );
void  			dbSetIdentityMatrix4				( int iID );
float			dbInverseMatrix4					( int iResult, int iSource );
bool			dbIsIdentityMatrix4					( int iID );
void  			dbBuildLookAtRHMatrix4				( int iResult, int iVectorEye, int iVectorAt, int iVectorUp );
void  			dbBuildLookAtLHMatrix4				( int iResult, int iVectorEye, int iVectorAt, int iVectorUp );
void  			dbBuildOrthoRHMatrix4				( int iResult, float fWidth, float fHeight, float fZNear, float fZFar );
void  			dbBuildOrthoLHMatrix4				( int iResult, float fWidth, float fHeight, float fZNear, float fZFar );
void  			dbBuildPerspectiveRHMatrix4			( int iResult, float fWidth, float fHeight, float fZNear, float fZFar );
void  			dbBuildPerspectiveLHMatrix4			( int iResult, float fWidth, float fHeight, float fZNear, float fZFar );
void  			dbBuildFovRHMatrix4					( int iResult, float fFOV, float fAspect, float fZNear, float fZFar );
void  			dbBuildFovLHMatrix4					( int iResult, float fFOV, float fAspect, float fZNear, float fZFar );
void  			dbBuildReflectionMatrix4			( int iResult, float a, float b, float c, float d );
void  			dbBuildRotationAxisMatrix4			( int iResult, int iVectorAxis, float fAngle );
void  			dbRotateXMatrix4					( int iID, float fAngle );
void  			dbRotateYMatrix4					( int iID, float fAngle );
void  			dbRotateZMatrix4					( int iID, float fAngle );
void  			dbRotateYPRMatrix4					( int iID, float fYaw, float fPitch, float fRoll );
void  			dbScaleMatrix4						( int iID, float fX, float fY, float fZ );
void  			dbTranslateMatrix4					( int iID, float fX, float fY, float fZ );
void  			dbTransposeMatrix4					( int iResult, int iSource );
void  			dbWorldMatrix4						( int iID );
void  			dbViewMatrix4						( int iID );
void  			dbProjectionMatrix4					( int iID );

void			Constructor3DMaths					( HINSTANCE hSetup );
void			Destructor3DMaths					( void );
void			SetErrorHandler3DMaths				( LPVOID pErrorHandlerPtr );
void			PassCoreData3DMaths					( LPVOID pGlobPtr );
void			RefreshD3D3DMaths					( int iMode );

D3DXVECTOR2		dbGetVector2 						( int iID );
D3DXVECTOR3		dbGetVector3 						( int iID );
D3DXVECTOR4		dbGetVector4 						( int iID );
D3DXMATRIX		dbGetMatrix							( int iID );
int				dbGet3DMathsExist					( int iID );
