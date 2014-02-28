/////////////////////////////////////////////////////////////////////////////////////////////////////////
// LIGHT COMMANDS ///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void	dbMakeLight						( int iID );
void	dbDeleteLight					( int iID );

void	dbSetPointLight					( int iID, float fX, float fY, float fZ );
void	dbSetSpotLight					( int iID, float fInner, float fOuter );
void	dbSetDirectionalLight			( int iID, float fX, float fY, float fZ );
void	dbSetLightRange					( int iID, float fRange );

void	dbPositionLight					( int iID, float fX, float fY, float fZ );
void	dbRotateLight					( int iID, float fX, float fY, float fZ );
void	dbPointLight					( int iID, float fX, float fY, float fZ );

void	dbHideLight						( int iID );
void	dbShowLight						( int iID );

void	dbSetLightToObject				( int iID, int iObjectID );
void	dbSetLightToObjectOrientation	( int iID, int iObjectID );
void	dbColorLight					( int iID, DWORD dwColor );
void	dbColorLight					( int iID, int iR, int iG, int iB );

void	dbSetNormalizationOn			( void );
void	dbSetNormalizationOff			( void );

void	dbSetAmbientLight				( int iPercent );
void	dbColorAmbientLight				( DWORD dwColor );

void	dbFogOn							( void );
void	dbFogOff						( void );
void	dbFogColor						( DWORD dwColor );
void	dbFogColor						( int iR, int iG, int iB );
void	dbFogDistance					( int iDistance );
void	dbFogDistance					( int iStartDistance, int iFinishDistance );

void	dbPositionLight					( int iID, int iVector );
void	dbSetVector3ToLightPosition		( int iVector, int iID );
void	dbRotateLight					( int iID, int iVector );
void	dbSetVector3ToLightRotation		( int iVector, int iID );

int		dbLightExist					( int iID );
int		dbLightType						( int iID );
float	dbLightPositionX				( int iID );
float	dbLightPositionY				( int iID );
float	dbLightPositionZ				( int iID );
float	dbLightDirectionX				( int iID );
float	dbLightDirectionY				( int iID );
float	dbLightDirectionZ				( int iID );
int		dbLightVisible					( int iID );
float	dbLightRange					( int iID );

void	dbSetLightSpecular				( int iID, float fA, float fR, float fG, float fB );
void	dbSetLightAmbient				( int iID, float fA, float fR, float fG, float fB );
void	dbSetLightFalloff				( int iID, float fValue );
void	dbSetLightAttenuation0			( int iID, float fValue );
void	dbSetLightAttenuation1			( int iID, float fValue );
void	dbSetLightAttenuation2			( int iID, float fValue );

void	dbSetLightSpecularOn			( void );
void	dbSetLightSpecularOff			( void );

void	ConstructorLight				( HINSTANCE hSetup );
void	DestructorLight					( void );
void	SetErrorHandlerLight			( LPVOID pErrorHandlerPtr );
void	PassCoreDataLight				( LPVOID pGlobPtr );
void	RefreshD3DLight					( int iMode );

void	dbSetLightToObjectPosition		( int iID, int iObjectID );
