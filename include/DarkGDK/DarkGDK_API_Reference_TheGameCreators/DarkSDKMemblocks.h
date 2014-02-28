/////////////////////////////////////////////////////////////////////////////////////////////////////////
// MEMBLOCK COMMANDS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void	dbReturnMemblockPtrs		( LPVOID* pSizeArray, LPVOID* pDataArray );

LPSTR	dbExtMakeMemblock			( int mbi, DWORD size );
void	dbExtFreeMemblock			( int mbi );
DWORD	dbExtGetMemblockSize		( int mbi );
void	dbExtSetMemblockSize		( int mbi, DWORD size );
LPSTR	dbExtGetMemblockPtr			( int mbi );

void	dbMakeMemblock				( int mbi, int size );
void	dbDeleteMemblock			( int mbi );
int		dbMemblockExist				( int mbi );
DWORD	dbGetMemblockPtr			( int mbi );
int		dbGetMemblockSize			( int mbi );
void	dbCopyMemblock				( int mbiF, int mbiT, int posF, int posT, int size );
void	dbWriteMemblockByte			( int mbi, int pos, int data );
int		dbMemblockByte				( int mbi, int pos );
void	dbWriteMemblockWord			( int mbi, int pos, int data );
int		dbMemblockWord				( int mbi, int pos );
void	dbWriteMemblockDWORD		( int mbi, int pos, DWORD data );
DWORD	dbMemblockDWORD				( int mbi, int pos );
void	dbWriteMemblockFloat		( int mbi, int pos, float data );
float	dbMemblockFloat				( int mbi, int pos );
void	dbMakeMemblockFromBitmap	( int mbi, int bitmapindex );
void	dbMakeBitmapFromMemblock	( int bitmapindex, int mbi );
void	dbMakeMemblockFromMesh		( int mbi, int meshid );
void	dbMakeMeshFromMemblock		( int meshid, int mbi );
void	dbChangeMeshFromMemblock	( int meshid, int mbi );
void	dbMakeMemblockFromSound		( int mbi, int soundindex );
void	dbMakeSoundFromMemblock		( int soundindex, int mbi );
void	dbMakeMemblockFromImage		( int mbi, int imageid );
void	dbMakeImageFromMemblock		( int imageid, int mbi );
void	dbMakeMemblockFromArray		( int mbi, DWORD arrayptr );
void	dbMakeArrayFromMemblock		( DWORD arrayptr, int mbi );

void	ConstructorMemblocks		( void );
void	DestructorMemblocks			( void );
void	SetErrorHandlerMemblocks	( LPVOID pErrorHandlerPtr );
void	PassCoreDataMemblocks		( LPVOID pGlobPtr );
void	RefreshD3DMemblocks			( int iMode );

void	dbWriteMemblockByte			( int mbi, int pos, unsigned char data );
void	dbWriteMemblockWord			( int mbi, int pos, WORD data );
void	dbWriteMemblockDword		( int mbi, int pos, DWORD data );
DWORD	dbMemblockDword				( int mbi, int pos );
