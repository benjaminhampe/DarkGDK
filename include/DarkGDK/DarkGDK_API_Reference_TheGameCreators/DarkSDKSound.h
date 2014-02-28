/////////////////////////////////////////////////////////////////////////////////////////////////////////
// SOUND COMMANDS ///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <mmreg.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void	dbLoadSound				( LPSTR szFilename, int iID );
void	dbLoadSound				( LPSTR szFilename, int iID, int iFlag );
void	dbCloneSound			( int iDestination, int iSource );
void	dbDeleteSound			( int iID );

void	dbPlaySound				( int iID );
void	dbPlaySound				( int iID, int iOffset );
void	dbLoopSound				( int iID );
void	dbLoopSound				( int iID, int iStart );
void	dbLoopSound				( int iID, int iStart, int iEnd );
void	dbLoopSound				( int iID, int iStart, int iEnd, int iInitialPos );

void	dbStopSound				( int iID );
void	dbResumeSound			( int iID );
void	dbPauseSound			( int iID );

void	dbSetSoundPan			( int iID, int iPan );
void	dbSetSoundSpeed			( int iID, int iFrequency );
void	dbSetSoundVolume		( int iID, int iVolume );

void	dbRecordSound			( int iID );
void	dbRecordSound			( int iID, int iCaptureDuration );
void	dbStopRecordingSound	( void );
void	dbSaveSound				( LPSTR szFilename, int iID );

void	dbLoad3DSound			( LPSTR szFilename, int iID );
void	dbPositionSound			( int iID, float fX, float fY, float fZ );
void	dbPositionListener		( float fX, float fY, float fZ );
void	dbRotateListener		( float fX, float fY, float fZ );
void	dbScaleListener			( float fScale );
void	dbSetEAX				( int iEffect );

int		dbSoundExist         	( int iID );
int		dbSoundType          	( int iID );
int		dbSoundPlaying       	( int iID );
int		dbSoundLooping       	( int iID );
int		dbSoundPaused        	( int iID );
int		dbSoundPan           	( int iID );
int		dbSoundSpeed			( int iID );
int		dbSoundVolume			( int iID );

float	dbSoundPositionX		( int iID );
float	dbSoundPositionY		( int iID );
float	dbSoundPositionZ		( int iID );
float	dbListenerPositionX		( void );
float	dbListenerPositionY		( void );
float	dbListenerPositionZ		( void );
float	dbListenerAngleX		( void );
float	dbListenerAngleY		( void );
float	dbListenerAngleZ		( void );

float	dbGetSoundPositionX		( int iID );
float	dbGetSoundPositionY		( int iID );
float	dbGetSoundPositionZ		( int iID );
float	dbGetListenerPositionX	( int iID );
float	dbGetListenerPositionY	( int iID );
float	dbGetListenerPositionZ	( int iID );
float	dbGetListenerAngleX		( int iID );
float	dbGetListenerAngleY		( int iID );
float	dbGetListenerAngleZ		( int iID );

void	ConstructorSound		( HWND hWnd );
void	DestructorSound			( void );
void	SetErrorHandlerSound	( LPVOID pErrorHandlerPtr );
void	PassCoreDataSound		( LPVOID pGlobPtr );
void	RefreshD3DSound			( int iMode );
void	UpdateSound				( void );

void    dbGetSoundData			( int iID, DWORD* dwBitsPerSecond, DWORD* Frequency, DWORD* Duration, LPSTR* pData, DWORD* dwDataSize, bool bLockData, WAVEFORMATEX* wfx );
void    dbSetSoundData			( int iID, DWORD dwBitsPerSecond, DWORD Frequency, DWORD Duration, LPSTR pData, DWORD dwDataSize, WAVEFORMATEX wfx );
