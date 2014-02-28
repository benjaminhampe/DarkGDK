/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FILE COMMANDS ////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void	ConstructorFile					( void );
void	DestructorFile					( void );
void	SetErrorHandlerFile				( LPVOID pErrorHandlerPtr );
void	PassCoreDataFile				( LPVOID pGlobPtr );

void	dbSetDir						( char* pString );
void	dbDir							( void );
void	dbDriveList						( void );
void	dbPerformCheckListForFiles		( void );
void	dbPerformCheckListForDrives		( void );
void	dbFindFirst						( void );
void	dbFindNext						( void );
void	dbMakeFile						( char* pFilename );
void	dbDeleteFile					( char* pFilename );
void	dbCopyFile						( char* pFilename, char* pFilename2 );
void	dbRenameFile					( char* pFilename, char* pFilename2 );
void	dbMoveFile						( char* pFilename, char* pFilename2 );
void	dbWriteByteToFile				( char* pFilename, int iPos, int iByte );
int		dbReadByteFromFile				( char* pFilename, int iPos );
void	dbMakeDirectory					( char* pFilename );
void	dbDeleteDirectory				( char* pFilename );
void	dbDeleteDirectory				( char* pFilename, int iFlag );
void	dbExecuteFile					( char* pFilename, char* pFilename2, char* pFilename3 );
void	dbExecuteFile					( char* pFilename, char* pFilename2, char* pFilename3, int iFlag );
DWORD	dbExecuteExecutable				( char* pFilename, char* pFilename2, char* pFilename3 );
DWORD	dbExecuteExecutable				( char* pFilename, char* pFilename2, char* pFilename3, int iPriority );
void	dbStopExecutable				( DWORD hIndiExecuteFileProcess );

void	dbWriteFilemapValue				( char* pFilemapname, DWORD dwValue );
void	dbWriteFilemapString			( char* pFilemapname, char* pString );
DWORD	dbReadFilemapValue				( char* pFilemapname );
char*	dbReadFilemapString				( char* pFilemapname );

void	dbOpenToRead					( int f, char* pFilename );
void	dbOpenToWrite					( int f, char* pFilename );
void	dbCloseFile						( int f );
int		dbReadByte						( int f );
int		dbReadWord						( int f );
int		dbReadFile						( int f );
float	dbReadFloat						( int f );
char*	dbReadString					( int f );
void	dbReadFileBlock					( int f, char* pFilename );
void	dbSkipBytes						( int f, int iSkipValue );
void	dbReadDirBlock					( int f, char* pFilename );
void	dbWriteByte						( int f, int iValue );
void	dbWriteWord						( int f, int iValue );
void	dbWriteLong						( int f, int iValue );
void	dbWriteFloat					( int f, float fValue );
void	dbWriteString					( int f, char* pString );
void	dbWriteFileBlock				( int f, char* pFilename );
void	dbWriteFileBlockEx				( int f, char* pFilename, int iFlag );
void	dbWriteDirBlock					( int f, char* pFilename );

void	dbReadMemblock					( int f, int mbi );
void	dbMakeMemblockFromFile			( int mbi, int f );
void	dbWriteMemblock					( int f, int mbi );
void	dbMakeFileFromMemblock			( int f, int mbi );

char*	dbGetDir						( void );
char*	dbGetFileName					( void );
int		dbGetFileType					( void );
char*	dbGetFileDate					( void );
char*	dbGetFileCreation				( void );
int		dbFileExist						( char* pFilename );
int		dbFileSize						( char* pFilename );
int		dbPathExist						( char* pFilename );
int		dbFileOpen						( int f );
int		dbFileEnd						( int f );

char*	dbAppname						( void );
char*	dbWindir						( void );
int		dbExecutableRunning				( DWORD hIndiExecuteFileProcess );

unsigned char dbReadByte				( int f, unsigned char* pByte );
WORD	dbReadWord						( int f, WORD* pWord );
int		dbReadFile						( int f, int* pInteger );
float	dbReadFloat						( int f, float* pFloat );
char*	dbReadString					( int f, char* pString );
int		dbReadLong						( int f, int* pInteger );
void	dbCD							( char* pPath );
void	dbWriteFile						( int f, int iValue );
