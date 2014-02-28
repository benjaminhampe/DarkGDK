/////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEXT COMMANDS ////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

bool	dbMake							( int iID, DWORD dwFlush, DWORD dwDiscard, float fRadius, int iImage );
void	dbDelete						( int iID );
void	dbSetColor						( int iID, int iRed, int iGreen, int iBlue );
void	dbSetTime						( int iID, float fTime );

void	dbMakeParticles					( int iID, int iImageIndex, int maxParticles, float fRadius );
void	dbDeleteParticles				( int iID );

void	dbSetParticleSpeed				( int iID, float fTime );
void	dbSetParticleEmmissions			( int iID, int iNumber );
void	dbSetParticleVelocity			( int iID, float fVelocity );
void	dbPositionParticles				( int iID, float fX, float fY, float fZ );
void	dbPositionParticleEmmissions	( int iID, float fX, float fY, float fZ );
void	dbColorParticles				( int iID, int iRed, int iGreen, int iBlue );
void	dbRotateParticles				( int iID, float fX, float fY, float fZ );
void	dbSetParticleGravity			( int iID, float fGravity );
void	dbSetParticleChaos				( int iID, float fChaos );
void	dbSetParticleLife				( int iID, int iLifeValue );
void	dbSetParticleFloor				( int iID, int iFlag );
void	dbGhostParticlesOn				( int iID, int iMode );
void	dbGhostParticlesOff				( int iID );
void	dbGhostParticlesOn				( int iID, int iMode, float fPercentage );

void	dbHideParticles					( int iID );
void	dbShowParticles					( int iID );

void	dbMakeSnowParticles				( int iID, int iImageIndex, int maxParticles, float fX, float fY, float fZ, float fWidth, float fHeight, float fDepth );
void	dbMakeFireParticles				( int iID, int iImageIndex, int maxParticles, float fX, float fY, float fZ, float fWidth, float fHeight, float fDepth );

void	dbPositionParticles				( int iID, int iVector );
void	dbSetVector3ToParticlesPosition	( int iVector, int iID );
void	dbRotateParticles				( int iID, int iVector );
void	dbSetVector3ToParticlesRotation	( int iVector, int iID );

bool	dbParticlesExist				( int iID );
float	dbParticlesPositionX			( int iID );
float	dbParticlesPositionY			( int iID );
float	dbParticlesPositionZ			( int iID );

void	ConstructorParticles			( HINSTANCE hSetup, HINSTANCE hImage );
void	DestructorParticles				( void );
void	SetErrorHandlerParticles		( LPVOID pErrorHandlerPtr );
void	PassCoreDataParticles			( LPVOID pGlobPtr );
void	RefreshD3DParticles				( int iMode );
void	UpdateParticles					( void );

void	dbSetParticleEmissions				( int iID, int iNumber );
void	dbPositionParticleEmissions		( int iID, float fX, float fY, float fZ );
