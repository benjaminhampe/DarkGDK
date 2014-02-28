/////////////////////////////////////////////////////////////////////////////////////////////////////////
// DARKGDK HEADER ///////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

// Added to supress Windows.h define
#define NOMINMAX

// Supress some warnings
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif

// Extra datatype define
#if _MSC_VER < 1300
#include <wtypes.h>
#ifndef ADDRESS_TAG_BIT
typedef DWORD *DWORD_PTR;
#endif
#endif

// Includes
#include "DarkSDKCore.h"
#include "DarkSDKText.h"
#include "DarkSDKDisplay.h"
#include "DarkSDKInput.h"
#include "DarkSDKFile.h"
#include "DarkSDKBasic2D.h"
#include "DarkSDKBitmap.h"
#include "DarkSDKSound.h"
#include "DarkSDKMusic.h"
#include "DarkSDKSprites.h"
#include "DarkSDKImage.h"
#include "DarkSDKAnimation.h"
#include "DarkSDKLight.h"
#include "DarkSDKCamera.h"
#include "DarkSDKBasic3D.h"
#include "DarkSDKMatrix.h"
#include "DarkSDKWorld.h"
#include "DarkSDKParticles.h"
#include "DarkSDK3DMaths.h"
#include "DarkSDKFTP.h"
#include "DarkSDKMemblocks.h"
#include "DarkSDKMultiplayer.h"
#include "DarkSDKSystem.h"
#include "DarkSDKTerrain.h"

// Required Libraries
#pragma comment ( lib, "darksdk.lib"     )
#pragma comment ( lib, "core.lib"        )
#pragma comment ( lib, "text.lib"        )
#pragma comment ( lib, "display.lib"     )
#pragma comment ( lib, "input.lib"       )
#pragma comment ( lib, "file.lib"        )
#pragma comment ( lib, "basic2D.lib"     )
#pragma comment ( lib, "bitmap.lib"      )
#pragma comment ( lib, "sound.lib"       )
#pragma comment ( lib, "music.lib"       )
#pragma comment ( lib, "sprites.lib"     )
#pragma comment ( lib, "image.lib"       )
#pragma comment ( lib, "animation.lib"   )
#pragma comment ( lib, "light.lib"       )
#pragma comment ( lib, "camera.lib"      )
#pragma comment ( lib, "basic3D.lib"     )
#pragma comment ( lib, "matrix.lib"      )
#pragma comment ( lib, "world.lib"       )
#pragma comment ( lib, "particles.lib"   )
#pragma comment ( lib, "3dmaths.lib"     )
#pragma comment ( lib, "ftp.lib"         )
#pragma comment ( lib, "memblocks.lib"   )
#pragma comment ( lib, "multiplayer.lib" )
#pragma comment ( lib, "system.lib"      )
#pragma comment ( lib, "convx.lib"       )
#pragma comment ( lib, "conv3ds.lib"     )
#pragma comment ( lib, "convmd2.lib"     )
#pragma comment ( lib, "convmd3.lib"     )
#pragma comment ( lib, "convmdl.lib"     )
#pragma comment ( lib, "terrain.lib"     )
#pragma comment ( lib, "shell32.lib"     )

// Controls escapekey detection
extern int g_iDarkGameSDKQuit;

// Prototypes
void DarkGDK ( void );
bool LoopGDK ( void );
