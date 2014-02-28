/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ANIMATION COMMANDS ///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void dbDeleteAnimation				( int animindex );
void dbPlayAnimation				( int animindex );
void dbStopAnimation				( int animindex );
void dbPauseAnimation				( int animindex );
void dbResumeAnimation				( int animindex );
void dbLoopAnimation				( int animindex );
void dbPlayAnimation				( int animindex, int x1, int y1 );
void dbPlayAnimation				( int animindex, int x1, int y1, int x2, int y2 );
void dbPlayAnimationToImage			( int animindex, int imageindex, int x1, int y1, int x2, int y2 );
void dbPlayAnimationToBitmap		( int animindex, int bitmapindex, int x1, int y1, int x2, int y2 );
void dbLoopAnimationToBitmap		( int animindex, int bitmapindex, int x1, int y1, int x2, int y2 );
void dbPlaceAnimation				( int animindex, int x1, int y1, int x2, int y2);

int  dbAnimationExist				( int animindex );
int  dbAnimationPlaying				( int animindex );
int  dbAnimationPaused				( int animindex );
int  dbAnimationLooping				( int animindex );
int  dbAnimationPositionX			( int animindex );
int  dbAnimationPositionY			( int animindex );
int  dbAnimationWidth				( int animindex );
int  dbAnimationHeight				( int animindex );

void dbLoadAnimation				( char* szFilename, int iIndex );
void dbLoadDVDAnimation				( int animindex );
void dbSetAnimationVolume			( int animindex, int ivolume );
void dbSetAnimationSpeed			( int animindex, int ispeed );
void dbSetDVDChapter				( int animindex, int iTitle, int iChapterNumber );

int  dbAnimationVolume				( int animindex );
int  dbAnimationSpeed				( int animindex );
int  dbTotalDVDChapters				( int animindex, int iTitle );

void ConstructorAnimation			( void );
void DestructorAnimation			( void );
void SetErrorHandlerAnimation		( LPVOID pErrorHandlerPtr );
void PassCoreDataAnimation			( LPVOID pGlobPtr );
void RefreshD3DAnimation			( int iMode );

void dbPreventTextureLock			( bool bDoNotLock );
void dbUpdateAllAnimation			( void );
