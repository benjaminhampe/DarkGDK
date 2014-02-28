/////////////////////////////////////////////////////////////////////////////////////////////////////////
// INPUT COMMANDS ///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void 			dbClearEntryBuffer 					( void );
char* 			dbGetEntry 							( void );

int 			dbUpKey      						( void );
int 			dbDownKey    						( void );
int 			dbLeftKey   						( void );
int 			dbRightKey   						( void );
int 			dbControlKey 						( void );
int 			dbShiftKey   						( void );
int 			dbSpaceKey   						( void );
int 			dbEscapeKey  						( void );
int 			dbReturnKey  						( void );
int 			dbKeyState   						( int iKey );
int 			dbScanCode   						( void );

void 			dbWriteToClipboard					( char* pString );
void 			dbWriteToRegistry					( char* a, char* b, int c );
char*			dbGetClipboard						( void );
int 			dbGetRegistry						( LPSTR, LPSTR );
void 			dbWriteToRegistryS					( LPSTR pfolder, LPSTR valuekey, char* pString );
char* 			dbGetRegistryS						( LPSTR pfolder, LPSTR valuekey );

void 			dbHideMouse     					( void );
void 			dbShowMouse     					( void );
void 			dbPositionMouse 					( int, int );
void 			dbChangeMouse   					( int );
int  			dbMouseX     						( void );
int  			dbMouseY     						( void );
int  			dbMouseZ     						( void );
int  			dbMouseClick 						( void );
int  			dbMouseMoveX 						( void );
int  			dbMouseMoveY 						( void );
int  			dbMouseMoveZ 						( void );

int 			dbJoystickUp 						( void );
int 			dbJoystickDown 						( void );
int 			dbJoystickLeft 						( void );
int 			dbJoystickRight 					( void );
int 			dbJoystickX 						( void );
int 			dbJoystickY 						( void );
int 			dbJoystickZ 						( void );
int 			dbJoystickFireA 					( void );
int 			dbJoystickFireB 					( void );
int 			dbJoystickFireC 					( void );
int 			dbJoystickFireD 					( void );
int 			dbJoystickFireXL 					( int iButton );
int 			dbJoystickSliderA 					( void );
int 			dbJoystickSliderB 					( void );
int 			dbJoystickSliderC 					( void );
int 			dbJoystickSliderD 					( void );
int 			dbJoystickTwistX 					( void );
int 			dbJoystickTwistY 					( void );
int 			dbJoystickTwistZ 					( void );
int 			dbJoystickHatAngle 					( int iHatID );

void 			dbForceUp 							( int iMagnitude );
void 			dbForceDown							( int iMagnitude );
void 			dbForceLeft 						( int iMagnitude );
void 			dbForceRight 						( int iMagnitude );
void 			dbForceAngle						( int iMagnitude, int iAngle, int iDuration );
void 			dbForceChainsaw						( int iMagnitude, int iDuration );
void 			dbForceShoot						( int iMagnitude, int iDuration );
void 			dbForceImpact						( int iMagnitude, int iDuration );
void 			dbForceNoEffect						( void );
void 			dbForceWaterEffect					( int iMagnitude, int iDuration );
void 			dbForceAutoCenterOn					( void );
void 			dbForceAutoCenterOff				( void );

void 			dbPerformChecklistControlDevices	( void );
void 			dbSetControlDevice					( char* pName );
char* 			dbGetControlDevice 					( void );
int 			dbControlDeviceX					( void );
int 			dbControlDeviceY					( void );
int 			dbControlDeviceZ					( void );

void			ConstructorInput 					( HINSTANCE );
void 			DestructorInput  					( void );
void 			SetErrorHandlerInput				( LPVOID pErrorHandlerPtr );
void 			PassCoreDataInput					( LPVOID pGlobPtr );
void 			RefreshD3DInput 					( int iMode );
void			dbClearDataInput 					( void );

char* 			dbEntry 							( void );
void 			dbWriteStringToRegistry				( LPSTR pfolder, LPSTR valuekey, DWORD pString );
char* 			dbGetRegistryString					( LPSTR pfolder, LPSTR valuekey );
int 			dbJoystickFireX 					( int iButton );
