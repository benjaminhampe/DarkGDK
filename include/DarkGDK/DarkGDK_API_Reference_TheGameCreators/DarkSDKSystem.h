/////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEXT COMMANDS ////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void	ConstructorSystem		( void );
void	DestructorSystem		( void );
void	SetErrorHandlerSystem	( LPVOID pErrorHandlerPtr );
void	PassCoreDataSystem		( LPVOID pGlobPtr );
void	RefreshD3DSystem		( int iMode );

int		dbSystemTMEMAvailable	( void );
int		dbSystemDMEMAvailable	( void );
int		dbSystemSMEMAvailable	( void );

void	dbDisableEscapeKey		( void );
void	dbEnableEscapeKey		( void );
void	dbDisableSystemKeys		( void );
void	dbEnableSystemKeys		( void );
void	dbExitPrompt			( char* pString, char* pString2 );

void	dbEmptyChecklist		( void );
int		dbChecklistQuantity		( void );
int		dbChecklistValueA		( int iIndex );
int		dbChecklistValueB		( int iIndex );
int		dbChecklistValueC		( int iIndex );
int		dbChecklistValueD		( int iIndex );
float	dbChecklistFValueA		( int iIndex );
float	dbChecklistFValueB		( int iIndex );
float	dbChecklistFValueC		( int iIndex );
float	dbChecklistFValueD		( int iIndex );
char*	dbChecklistString		( int iIndex );

void	dbDLLLoad				( char* pDLLFile, int dllid );
void	dbDLLDelete				( int dllid );
int		dbDLLExist				( int dllid );
int		dbDLLCallExist			( int dllid, char* pDLLFunction );
DWORD	dbCallDLL				( int dllid, char* pDLLFunction);
DWORD	dbCallDLL				( int dllid, char* pDLLFunction, DWORD P1);
DWORD	dbCallDLL				( int dllid, char* pDLLFunction, DWORD P1,DWORD P2);
DWORD	dbCallDLL				( int dllid, char* pDLLFunction, DWORD P1,DWORD P2,DWORD P3);
DWORD	dbCallDLL				( int dllid, char* pDLLFunction, DWORD P1,DWORD P2,DWORD P3,DWORD P4);
DWORD	dbCallDLL				( int dllid, char* pDLLFunction, DWORD P1,DWORD P2,DWORD P3,DWORD P4,DWORD P5);
DWORD	dbCallDLL				( int dllid, char* pDLLFunction, DWORD P1,DWORD P2,DWORD P3,DWORD P4,DWORD P5,DWORD P6);
DWORD	dbCallDLL				( int dllid, char* pDLLFunction, DWORD P1,DWORD P2,DWORD P3,DWORD P4,DWORD P5,DWORD P6,DWORD P7);
DWORD	dbCallDLL				( int dllid, char* pDLLFunction, DWORD P1,DWORD P2,DWORD P3,DWORD P4,DWORD P5,DWORD P6,DWORD P7,DWORD P8);
DWORD	dbCallDLL				( int dllid, char* pDLLFunction, DWORD P1,DWORD P2,DWORD P3,DWORD P4,DWORD P5,DWORD P6,DWORD P7,DWORD P8,DWORD P9 );
DWORD	dbCallDLL				( int dllid, char* pDLLFunction, DWORD P1,DWORD P2,DWORD P3,DWORD P4,DWORD P5,DWORD P6,DWORD P7,DWORD P8,DWORD P9,DWORD P10 );
DWORD	dbCallDLLX				( int dllid, char* pDLLFunction, DWORD pDataPtr, DWORD dwNumberOfDWORDS );
void*	dbGetGlobalStructure	( void );

void	dbLoadDLL				( char* pDLLFile, int dllid );
void	dbDeleteDLL				( int dllid );
int		dbExistDLL				( int dllid );
int		dbDLLCallExist			( int dllid, char* pDLLFunction );
int		dbSystemTmemAvailable	( void );
int		dbSystemDmemAvailable	( void );
int		dbSystemSmemAvailable	( void );
void	dbDisableEscapekey		( void );
void	dbEnableEscapekey		( void );

