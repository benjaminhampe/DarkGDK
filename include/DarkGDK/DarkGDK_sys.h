#ifndef __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_SYSTEM_H__
#define __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_SYSTEM_H__

#include <irrlicht.h>

#include "DarkGDK_struct.h"
#include "DarkGDK_math.h"
#include "DarkGDK_obj.h"
#include "DarkGDK_cam.h"

namespace irr
{

/// macro - dbPRINT & dbERROR
#if defined(_DEBUG) || defined(DEBUG)
	#define dbPRINT( args...) \
	{ \
		printf( args ); \
	}
	#define dbERROR( args... ) \
	{ \
		printf( stderr, args ); \
		fprintf( stdout, args ); \
	}
#else
	#define dbPRINT( args... )
	#define dbERROR( args... ) \
	{ \
		fprintf( stderr, args ); \
	}
#endif

///@brief
void dbDarkGDK(s32 argc, c8** argv);

///@brief
bool dbLoopGDK();

/// handle Keyboard
bool OnKeyEvent(const SEvent::SKeyInput& key_event );


///@brief handle MainWindow
bool dbSetDisplayMode( u32 w, u32 h, u32 bpp, bool fullscreen = false, bool vSync = false, bool antiAlias = true, bool anisotropFilter = true );

///@brief
void dbPositionWindow( u32 id, s32 x, s32 y);

///@brief
void dbSetWindowTitle(const wchar_t* title);

///@brief
void dbSetWindowOn();

///@brief
void dbSetWindowOff();

///@brief
void dbMaximizeWindow();

///@brief
void dbMinimizeWindow();

///@brief
s32 dbWindowPositionX( u32 id );

///@brief
s32 dbWindowPositionY( u32 id );

///@brief
u32 dbWindowWidth( u32 id );

///@brief
u32 dbWindowHeight( u32 id );

///@brief update Screen
void dbSync();

///@brief set Refresh-Rate of MainWindow / FrontBuffer
void dbSyncOn();

///@brief
void dbSyncOff();

///@brief
void dbSyncRate(u32 rate);

///@brief sleep
void dbYield();

void dbWait( u32 seconds );


///@brief get Size of Desktop
u32 dbDesktopWidth();

///@brief
u32 dbDesktopHeight();

///@brief
u32 dbDesktopDepth();

///@brief get Size of MainWindow
u32 dbScreenWidth();

///@brief
u32 dbScreenHeight();

///@brief
u32 dbScreenDepth();

///@brief get current render-target size
u32 dbGetRTTWidth();

///@brief
u32 dbGetRTTHeight();

///@brief get maximum render-target size
u32 dbGetRTTWidthMax();

///@brief
u32 dbGetRTTHeightMax();

///@brief get version
core::stringc dbGetVersion();

///@brief get vendor
core::stringc dbGetVendor();

///@brief get driver-type as string
core::stringc dbGetDriverString();

///@brief
u32 dbTimer();

///@brief
u32 dbPerfTimer();

///@brief get FPS
u32 dbScreenFPS();

///@brief set polygon-count ( for current scenemanager )
u32 dbGetPolygonCount();

///@brief
u32 dbGetFrameCount();

///@brief
u32 dbGetFPS();

///@brief
u32 dbGetFPSMin();

///@brief
u32 dbGetFPSMax();

///@brief
u32 dbGetFPSAverage();

///@brief get current directory
io::path dbGetDir();

///@brief get current directory
void dbSetDir( const io::path& newDir = _IRR_TEXT("./") );

///@brief set clear-color ( for current renderTarget )
void dbCls( const video::SColor& color );

///@brief set text-color ( for current font )
void dbInk( const video::SColor& fgcolor, const video::SColor& bgcolor = 0x00000000 );

///@brief Set Mouse
void dbPositionMouse(s32 x, s32 y);

///@brief handle cursor
void dbPositionCursor(s32 x, s32 y, s32 hAlign = -1, s32 vAlign = -1 );

/// handle Keyboard
bool dbKbHit();

/// handle Keyboard
EKEY_CODE dbKbKey();

/// handle Keyboard
bool isPressed(EKEY_CODE keyCode);

/// handle Keyboard
core::stringw dbInkey();

/// handle Keyboard
s32 dbKeyState(EKEY_CODE key);






///@brief print container of strings at cursor pos
void dbPrint( const core::stringc& line_txt );

///@brief
void dbPrint( const core::stringw& line_txt );

///@brief
void dbPrint( const StringArray& container );

///@brief
StringArray dbGetFiles( const io::path& filename );

///@brief Get Text Dimension ( from current font )
core::dimension2du dbGetTextDimension( const core::stringw& txt );


///@brief Get Mouse
s32 dbMouseClick();

///@brief Get Mouse
s32 dbMouseX();

///@brief Get Mouse
s32 dbMouseY();

///@brief Get Mouse
f32 dbMouseZ();

///@brief Get Mouse
s32 dbMouseMoveX();

///@brief Get Mouse
s32 dbMouseMoveY();

///@brief Get Mouse
f32 dbMouseMoveZ();

///@brief Get Mouse
bool dbMouseOver(s32 x1, s32 y1, s32 x2, s32 y2);

///@brief Get Mouse
bool dbMouseOver(const core::rect<s32>& box);



///@brief  Text
void dbSetTextFont(const io::path& file);

void dbSetTextSize(u32 height);

void dbGetTextSize();

///@brief draw text on screen ( with current font )
void dbText( const StringArray& lines, s32 x, s32 y, s32 hAlign = -1, s32 vAlign = -1 );

///@brief
void dbCenterText( const core::stringw& txt, s32 x, s32 y );



/// handle Keyboard
u8 dbUpKey();

/// handle Keyboard
u8 dbDownKey();

/// handle Keyboard
u8 dbLeftKey();

/// handle Keyboard
u8 dbRightKey();

/// handle Keyboard
u8 dbEscapeKey();

/// handle Keyboard
u8 dbReturnKey();

/// handle Keyboard
u8 dbShiftKey();

/// handle Keyboard
u8 dbControlKey();

} // end namespace irr

#endif // __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_H__
