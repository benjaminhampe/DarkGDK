/////////////////////////////////////////////////////////////////////////////////////////////////////////
// TEXT COMMANDS ////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

int			dbAsc						( char* dwSrcStr);
char* 		dbBin						( int iValue );
char* 		dbChr						( int iValue );
char* 		dbHex						( int iValue );
char* 		dbLeft						( char* szText, int iValue );
int			dbLen						( char* dwSrcStr );
char* 		dbLower 					( char* szText );
char* 		dbMid						( char* szText, int iValue );
char* 		dbRight 					( char* szText, int iValue );
char* 		dbStr						( float fValue );
char* 		dbStr						( int iValue );
char* 		dbUpper 					( char* szText );
float 		dbValF						( char* dwSrcStr );
double		dbStrDouble					( double dValue );
LONGLONG	dbValR						( char* dwSrcStr );

void		dbPerformChecklistForFonts	( void );
void		dbText						( int iX, int iY, char* szText );
void 		dbCenterText				( int iX, int iY, char* szText );
void 		dbSetTextFont				( char* szTypeface );
void 		dbSetTextFont		  		( char* szTypeface, int iCharacterSet );	
void 		dbSetTextSize          		( int iSize );							
void 		dbSetTextToNormal      		( void );								
void 		dbSetTextToItalic      		( void );								
void 		dbSetTextToBold        		( void );								
void 		dbSetTextToBoldItalic  		( void );								
void 		dbSetTextToOpaque      		( void );								
void 		dbSetTextToTransparent 		( void );								

int   		dbTextBackgroundType 		( void );
char* 		dbTextFont			 		( void );
int   		dbTextSize           		( void );
int   		dbTextStyle          		( void );
int			dbTextWidth          		( char* szString );
int			dbTextHeight         		( char* szString );

void		dbText3D     				( char* szText );									

char*		dbSpaces					( int iSpaces );

void		dbAppend        			( char* dwA, char* dwB );
void		dbReverse       			( char* dwA );
int			dbFindFirstChar 			( char* dwSource, char* dwChar );
int			dbFindLastChar  			( char* dwSource, char* dwChar );
int			dbFindSubString 			( char* dwSource, char* dwString );
int			dbCompareCase   			( char* dwA, char* dwB );
char*		dbFirstToken    			( char* dwSource, char* dwDelim );
char*		dbNextToken     			( char* dwDelim );

void		ConstructorText				( HINSTANCE );
void		DestructorText				( void );
void		SetErrorHandlerText			( LPVOID pErrorHandlerPtr );
void		PassCoreDataText			( LPVOID pGlobPtr );
void		RefreshD3DText				( int iMode );

void		dbSetTextColor				( int iAlpha, int iRed, int iGreen, int iBlue );
void		dbSetTextFont				( char* szTypeface, int iCharacterSet );
void		dbText						( int iX, int iY, char* szText );
int			dbGetTextWidth				( char* szString );
int			dbGetTextHeight				( char* szString );

void 		dbSetTextOpaque      		( void );								
void 		dbSetTextTransparent 		( void );								
float 		dbVal						( char* dwSrcStr );
