/////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEXT COMMANDS ////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void	dbFTPConnect		( char* szString, char* szString2, char* szString3, int iUseWindow );
void	dbFTPConnect		( char* szString, char* szString2, char* szString3 );
void	dbFTPDisconnect		( void );
void	dbFTPDisconnect		( int iFlag );

void	dbFTPSetDir			( char* dwString );
void	dbFTPPutFile		( char* dwString );
void	dbFTPGetFile		( char* dwString, char* dwString2 );
void	dbFTPGetFile		( char* dwString, char* dwString2, int iFlag );
void	dbFTPDeleteFile		( char* dwString );
void	dbFTPFindFirst		( void );
void	dbFTPFindNext		( void );
void	dbFTPTerminate		( void );
void	dbFTPProceed		( void );

char*	dbGetFTPError		( void );
char*	dbGetFTPDir			( void );
char*	dbGetFTPFileName	( void );
int		dbGetFTPFileType	( void );
int		dbGetFTPFileSize	( void );
int		dbGetFTPProgress	( void );
int		dbGetFTPStatus		( void );
int		dbGetFTPFailure		( void );

void	ConstructorFTP		( void );
void	DestructorFTP		( void );
void	SetErrorHandlerFTP	( LPVOID pErrorHandlerPtr );
void	PassCoreDataFTP		( LPVOID pGlobPtr );
