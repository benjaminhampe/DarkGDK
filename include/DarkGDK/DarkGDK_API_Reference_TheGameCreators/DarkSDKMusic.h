/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MUSIC COMMANDS ///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void dbLoadMusic			( LPSTR szFilename, int iID );
void dbLoadCDMusic			( int iTrackNumber, int iID );
void dbDeleteMusic			( int iID );

void dbPlayMusic			( int iID );
void dbLoopMusic			( int iID );
void dbStopMusic			( int iID );
void dbPauseMusic			( int iID );
void dbResumeMusic			( int iID );

void dbSetMusicVolume       ( int iID, int iVolume );
void dbSetMusicSpeed		( int iID, int iSpeed );

int  dbMusicExist			( int iID );
int  dbMusicPlaying			( int iID );
int  dbMusicLooping			( int iID );
int  dbMusicPaused			( int iID );
int  dbMusicVolume			( int iID );
int  dbMusicSpeed			( int iID );

int  dbGetNumberOfCDTracks  ( void );

void ConstructorMusic		( HWND hWnd );
void DestructorMusic		( void );
void SetErrorHandlerMusic	( LPVOID pErrorHandlerPtr );
void PassCoreDataMusic		( LPVOID pGlobPtr );
void RefreshD3DMusic		( int iMode );
void UpdateMusic			( void );
