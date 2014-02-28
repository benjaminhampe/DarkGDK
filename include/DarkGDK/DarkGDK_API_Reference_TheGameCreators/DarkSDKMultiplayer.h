/////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEXT COMMANDS ////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void	dbCreateNetGame							( LPSTR gamename, LPSTR name, int playermax );
void	dbCreateNetGame							( LPSTR gamename, LPSTR name, int playermax, int flagnum );
void	dbJoinNetGame							( int sessionnum, LPSTR name );
void	dbFreeNetGame							( void );

void	dbPerformChecklistForNetConnections		( void );
void	dbSetNetConnections						( int index );
void	dbSetNetConnections						( int index, LPSTR ipaddress );
void	dbPerformChecklistForNetSessions		( void );
void	dbPerformChecklistForNetPlayers			( void );

void	dbCreateNetPlayer						( LPSTR playername );
int		dbCreateNetPlayerEx						( LPSTR playername );
void	dbDestroyNetPlayer						( int playerid );

void	dbSendNetMessageInteger					( int playerid, int MessageData );
void	dbSendNetMessageFloat					( int playerid, float MessageData );
void	dbSendNetMessageString					( int playerid, LPSTR pMessageData );

void	dbSendNetMessageMemblock				( int playerid, int mbi );
void	dbSendNetMessageMemblock				( int playerid, int mbi, int gua );
void	dbSendNetMessageImage					( int playerid, int imageindex, int gua );
void	dbSendNetMessageBitmap					( int playerid, int bitmapindex, int gua );
void	dbSendNetMessageSound					( int playerid, int soundindex, int gua );
void	dbSendNetMessageMesh					( int playerid, int meshindex, int gua );

void	dbGetNetMessage							( void );
int		dbNetMessageInteger						( void );
float	dbNetMessageFloat						( void );
char*	dbNetMessageString						( void );

void	dbNetMessageMemblock					( int mbi );
void	dbNetMessageImage						( int imageindex );
void	dbNetMessageBitmap						( int bitmapindex );
void	dbNetMessageSound						( int soundindex );
void	dbNetMessageMesh						( int meshindex );

int		dbNetMessageExists						( void );
int		dbNetMessageType						( void );
int		dbNetMessagePlayerFrom					( void );
int		dbNetMessagePlayerTo					( void );
int		dbNetSessionExists						( void );
int		dbNetSessionLost						( void );
int		dbNetPlayerCreated						( void );
int		dbNetPlayerDestroyed					( void );
int		dbNetGameNowHosting						( void );

int		dbDefaultNetGame						( char* lpGameName, char* lpPlayerName, int PlayerMax, int FlagNum );
int		dbNetBufferSize							( void );

void	ConstructorMultiplayer					( void );
void	DestructorMultiplayer					( void );
void	SetErrorHandlerMultiplayer				( LPVOID pErrorHandlerPtr );
void	PassCoreDataMultiplayer					( LPVOID pGlobPtr );
void	RefreshD3DMultiplayer					( int iMode );

void	dbFreeNetPlayer							( int playerid );
void	dbSetNetConnection						( int index );
void	dbSetNetConnection						( int index, LPSTR ipaddress );
int		dbNetGameExists							( void );
int		dbNetGameLost							( void );
