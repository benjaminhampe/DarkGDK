/////////////////////////////////////////////////////////////////////////////////////////////////////////
// DISPLAY COMMANDS /////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <d3d9.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

int   				dbCheckDisplayMode					( int iWidth, int iHeight, int iDepth );
char* 				dbCurrentGraphicsCard				( void );
int   				dbEmulationMode 					( void );
void  				dbPerformChecklistForDisplayModes	( void );
void  				dbPerformChecklistForGraphicsCards	( void );
int   				dbScreenType	   					( void );
int   				dbScreenWidth  						( void );
int   				dbScreenHeight 						( void );
int   				dbScreenDepth  						( void );
int   				dbScreenFPS    						( void );
int   				dbScreenInvalid						( void );
void  				dbSetGamma		  					( int   iR, int   iG, int   iB );
void  				dbSetDisplayMode 					( int iWidth, int iHeight, int iDepth );
void  				dbSetEmulationOn   					( void );
void  				dbSetEmulationOff   				( void );
void  				dbSetGraphicsCard 					( char* szCardname );

void  				dbSetWindowOn						( void );
void  				dbSetWindowOff						( void );
void  				dbSetWindowLayout					( int iStyle, int iCaption, int iIcon );
void 				dbSetWindowPosition					( int posx, int posy );
void  				dbSetWindowSize						( int sizex, int sizey );
void  				dbHideWindow						( void );
void				dbShowWindow						( void );
void  				dbMinimiseWindow					( void );
void  				dbMaximiseWindow					( void );
void  				dbRestoreWindow						( void );
void  				dbSetWindowTitle					( char* pTitleString );
int   				dbWindowExist						( char* pTitleString );
void  				dbWindowToBack						( void );
void  				dbWindowToFront						( void );
void  				dbWindowToFront						( char* pTitleString );
void  				dbWindowToBack						( char* pTitleString );

void  				dbLockBackbuffer					( void );
void  				dbUnlockBackbuffer					( void );
DWORD 				dbGetBackbufferPtr					( void );
int   				dbGetBackbufferWidth				( void );
int   				dbGetBackbufferHeight				( void );
int   				dbGetBackbufferDepth				( void );
int   				dbGetBackbufferPitch				( void );

IDirect3D9*			dbGetDirect3D						( void );
IDirect3DDevice9*	dbGetDirect3DDevice					( void );

bool 				ConstructorDisplay					( void );
void 				DestructorDisplay					( void );
void 				SetErrorHandlerDisplay				( LPVOID pErrorHandlerPtr );
void 				PassCoreDataDisplay					( LPVOID pGlobPtr, int iStage );

void				dbBegin								( void );
void				dbEnd								( void );
void				dbRender							( void );
void 				dbOverrideHWND						( HWND hWnd );

bool 				dbSetDisplayDebugMode				( void );
bool 				dbSetDisplayModeEx					( int iWidth, int iHeight );
bool 				dbSetDisplayModeEx					( int iWidth, int iHeight, int iDepth );
bool 				dbSetDisplayModeEx					( int iWidth, int iHeight, int iDepth, int iMode );
bool 				dbSetDisplayModeEx					( int iWidth, int iHeight, int iDepth, int iMode, int iVertexProcessing );
bool 				dbSetDisplayModeEx					( int iWidth, int iHeight, int iDepth, int iMode, int iVertexProcessing, int iLockable );
void 				dbRestoreDisplayMode  				( void );
void 				dbRestoreLostDevice	 				( void );

void 				dbClear    							( int   iR, int   iG, int   iB );
void 				dbGetGamma 							( int* piR, int* piG, int* piB );

bool 				dbGetWindowedMode					( void );
int  				dbGetNumberOfDisplayModes			( void );
void 				dbGetDisplayMode					( int iID, char* szMode );
int  				dbGetNumberOfDisplayDevices			( void );
void 				dbSetDisplayDevice					( int iID );

void 				dbSetDitherMode   					( int iMode );
void 				dbSetShadeMode    					( int iMode );
void 				dbSetLightMode    					( int iMode );
void 				dbSetCullMode     					( int iMode );
void 				dbSetSpecularMode 					( int iMode );
void 				dbSetRenderState  					( int iState, int iValue );

void  				dbMinimizeWindow					( void );
void  				dbMaximizeWindow					( void );
int					dbDesktopWidth						( void );
int					dbDesktopHeight						( void );
bool				dbSetDisplayModeVSync				( int iWidth, int iHeight, int iDepth, int iVSyncOn );
bool				dbSetDisplayModeAntialias			( int iWidth, int iHeight, int iDepth, int iVSyncOn, int iMultisamplingFactor, int iMultimonitorMode );
