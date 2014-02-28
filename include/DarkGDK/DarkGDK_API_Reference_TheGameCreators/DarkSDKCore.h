/////////////////////////////////////////////////////////////////////////////////////////////////////////
// CORE COMMANDS ////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// INTERNAL FUNCTIONS ///////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

DWORD		dbGetGlobPtr				( void );
void		dbPassDLLs					( void );
void		dbPassErrorHandlerPtr		( LPVOID pErrorPtr );
void		dbPassCmdLineLineHandlerPtr	( LPVOID );
DWORD		dbInitDisplayEx				( DWORD dwDisplayType, DWORD dwWidth, DWORD dwHeight, DWORD dwDepth, HINSTANCE hInstance, LPSTR pApplicationName, HWND pParentHWND, DWORD dwInExStyle, DWORD dwInStyle);
DWORD		dbInitDisplay				( DWORD dwDisplayType, DWORD dwWidth, DWORD dwHeight, DWORD dwDepth, HINSTANCE hInstance, LPSTR pApplicationName );

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void		dbSyncOn				( void );
void		dbSyncOff				( void );
void		dbSync					( void );
void		dbSyncRate				( int dbiRate );
void		dbFastSync				( void );

void		dbCLS					( void );
void		dbSetCursor				( int iX, int iY );

void		dbPrint					( LONGLONG lValue );
void		dbPrint					( double dValue );
void		dbPrint					( LPSTR pString );
void		dbPrint					( void );
void		dbPrintC				( LONGLONG lValue );
void		dbPrintC				( double dValue );
void		dbPrintC				( LPSTR pString );

char*		dbInput					( void );

void		dbWait					( int dbiDelay );
void		dbSleep					( int dbiDelay );

void		dbWaitMouse				( void );
void		dbWaitKey				( void );
void		dbSuspendForKey			( void );
void		dbSuspendForMouse		( void );

void		dbDrawToBack			( void );
void		dbDrawToFront			( void );
void		dbDrawToCamera			( void );
void		dbDrawToScreen			( void );
void		dbDrawSpritesFirst		( void );
void		dbDrawSpritesLast		( void );

void		dbRandomize				( int dbiSeed );

float		dbCos					( float fValue );
float		dbSin					( float fAngle );
float		dbTan					( float fAngle );
float		dbAcos					( float fValue );
float		dbAsin					( float fValue );
float		dbAtan					( float fValue );
float		dbAtanFull				( float fA, float fB );
float		dbHcos					( float fAngle );
float		dbHsin					( float fAngle );
float		dbHtan					( float fAngle );
float		dbSqrt					( float fValue );
float		dbAbs					( float fValue );
float		dbInt					( float fValue );
float		dbExp					( float fExp );

int			dbRnd					( int dbr );
int			dbTimer					( void );
LONGLONG	dbPerformanceTimer		( void );

char*		dbInKey					( void );
char*		dbCl$					( void );
char*		dbGetDate$				( void );
char*		dbGetTime$				( void );

float		dbCurveValue			( float a, float da, float sp );
float		dbWrapValue				( float da );
float		dbNewXValue				( float x, float a, float b );
float		dbNewYValue				( float y, float a, float b );
float		dbNewZValue				( float z, float a, float b );
float		dbCurveAngle			( float a, float da, float sp );
void		dbAlwaysActiveOff		( void );
void		dbAlwaysActiveOn		( void );

int			dbRND					( int dbr );
float		dbCOS					( float fValue );
float		dbSIN					( float fAngle );
float		dbTAN					( float fAngle );
float		dbACOS					( float fValue );
float		dbASIN					( float fValue );
float		dbATAN					( float fValue );
float		dbATANFULL				( float fA, float fB );
float		dbHCOS					( float fAngle );
float		dbHSIN					( float fAngle );
float		dbHTAN					( float fAngle );
float		dbSQRT					( float fValue );
float		dbABS					( float fValue );
float		dbINT					( float fValue );
float		dbEXP					( float fExp );
char*		dbCL					( void );
char*		dbGetDate				( void );
char*		dbGetTime				( void );

void		dbSyncMask				( DWORD dwMask );
void		dbSyncDisableQuad		( void );
void		dbSyncEnableQuad		( void );
void		dbSyncRenderQuad		( void );
