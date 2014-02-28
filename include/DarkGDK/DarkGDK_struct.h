#ifndef DARKGDK_GLOB_STRUCT_H
#define DARKGDK_GLOB_STRUCT_H

/// uses StdC++
#include <cstdlib>
#include <cstdio>
#include <cstdarg>
#include <cmath>
#include <ctime>

/// my print macros
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
	#define ERROR_ON_NULL_POINTER(x,args...) if (!(x)) { \
		fprintf( stdout, args ); \
		fprintf( stderr, args ); \
		return -1; \
		}
#else
	#define dbPRINT( args... )
	#define dbERROR( args... ) \
	{ \
		fprintf( stderr, args ); \
	}
	#define ERROR_NULL_POINTER(x, args... ) { if ( !(x) ) \
	{ \
		fprintf( stdout, args ); \
		fprintf( stderr, args ); \
		return -1; \
		} \
	}
#endif

/// uses irrlicht-engine
#include <irrlicht.h>
#include <CAutoMeshSceneNode.h>
#include "driverChoice.h"

#ifndef SAVE_DROP
	#define SAVE_DROP(x) {if((x)){(x)->drop();(x)=0;}}
#endif

#ifndef SAVE_DELETE
	#define SAVE_DELETE(x) {if((x)){delete (x); (x)=0;}}
#endif

/// uses SFML-2.1 Audio API
#include <SFML/Audio.hpp>

// uses SDL-mixer
// #include <SDL/SDL_mixer.h>

namespace irr
{

enum E_DARKGDK_RESSOURCE_TYPE
{
	EDRT_IMAGE = 0,
	EDRT_MESH,
	EDRT_TEXTURE,
	EDRT_SPRITE,
	EDRT_OBJECT,
	EDRT_XMLTREE,
	EDRT_SOUND,
	EDRT_MUSIC,
	EDRT_COUNT,
	EDRT_UNKNOWN
};

typedef core::array<core::stringc> StringArray;

///@brief SMemblock
struct DarkGDK_SMemblock : public IReferenceCounted
{
	u32 ID;
	u32 Type; /// 0=generic,1=image, 2=mesh, 3=sound, 4=music, 5=file, 6=xml/html, 7=video
	u32 ByteSize;
	void* DataPtr;
};

///@brief SImage
struct DarkGDK_SImage : public IReferenceCounted
{
	u32 ID;
	//u32 Type; ///( 0==Texture, 1==Image)
	video::IImage* Image;
	video::ITexture* Texture;

	explicit DarkGDK_SImage( video::IImage* img = 0, video::ITexture* tex = 0) : Image(img), Texture(tex) {}

	~DarkGDK_SImage()
	{
		if (Image)
			Image->drop();
	}
};

///@brief SText
struct DarkGDK_SText2d : public IReferenceCounted
{
	gui::IGUIFont* Font;
	core::stringw Text;
	core::recti Position;
	video::SColor FGColor;
	video::SColor BGColor;
};

///@brief SObject
struct DarkGDK_SObject : public IReferenceCounted
{
	u32 ID;
	scene::IMeshSceneNode* Node;
};

///@brief SCamera
struct DarkGDK_SCamera : public IReferenceCounted
{
	u32 ID;
	scene::ICameraSceneNode* Node;
};

///@brief SCamera
struct DarkGDK_SViewPort : public IReferenceCounted
{
	u32 ID;
	u32 CameraID;
	core::recti ViewPort;
};


///@brief SManagedWindow
struct DarkGDK_SManagedWindow : public IReferenceCounted
{
	gui::IGUIWindow* Window;
	gui::IGUIButton* ToggleButton;
};

///@brief DarkGDK_Application
class DarkGDK_SGlobalStruct : public IEventReceiver
{
public:
	/// Meyer's Singleton access to one and only class instance
	static DarkGDK_SGlobalStruct& getInstance()
	{
		static DarkGDK_SGlobalStruct my_singleton;
		return my_singleton;
	}

public:
	/// global application ( Meyers Singleton ) :: member variable fields
	s32 Argc;
	c8** Argv;
	core::stringc Title;
	SIrrlichtCreationParameters NullParam;
	SIrrlichtCreationParameters Param;
	IrrlichtDevice* NullDevice;
	IrrlichtDevice* Device;
	scene::ICameraSceneNode* CurrentCamera;
	core::dimension2du DesktopSize;
	core::dimension2du ScreenSize;
	core::recti ScreenRect;
	gui::IGUIFont* Font;
	core::position2di CursorPos;
	core::position2di CursorAlign;
	video::SColor ClearColor;
	video::SColor TextForeColor;
	video::SColor TextBackColor;
	u32 FrameCount;
	u32 FPS_Count;
	s32 FPS_Now;
	s32 FPS_Min;
	s32 FPS_Max;
	s32 FPS_Avg;
	u32 SyncRate;
	u32 SyncWait;
	u32 Time_Now;
	u32 Time_Start;
	u32 Time_Last;
	u32 Time_Wait_Window_Title_Update;
	u32 Time_Last_Window_Title_Update;

	bool KeyIsDown[KEY_KEY_CODES_COUNT];
	core::array<EKEY_CODE> KeyBuffer; // kbhit und getKey()
	s32 MouseClick;
	s32 MousePosX;
	s32 MousePosY;
	f32 MousePosZ;
	s32 MousePosXold;
	s32 MousePosYold;
	f32 MousePosZold;
	s32 MouseMoveX;
	s32 MouseMoveY;
	f32 MouseMoveZ;
	f32 MouseWheel;
	core::array<DarkGDK_SMemblock> Memblocks; // managed generic memblock list
	core::array<DarkGDK_SViewPort> ViewPorts; // references only cameras
	core::array<DarkGDK_SCamera> Cameras; // managed camera library
	core::array<DarkGDK_SImage> Images; // managed images/textures
	core::array<DarkGDK_SObject> Objects; // managed 3d objects
	core::array<DarkGDK_SText2d> Texts; // managed 2d text list
	core::array<DarkGDK_SManagedWindow> Windows; // managed gui windows
	gui::IGUIWindow* EscapeWindow;

private:

	/// forbidden call to default constructor
	DarkGDK_SGlobalStruct() : Argc(0), Argv(0), NullDevice(0), Device(0), CurrentCamera(0), Font(0)
	, FrameCount(0), FPS_Count(0), FPS_Now(-1), FPS_Min(1024), FPS_Max(-1), FPS_Avg(-1)
	, Time_Now(0), Time_Start(0), Time_Last(0), CursorPos(0,0), CursorAlign(-1,-1)
	//, Time_Wait_Window_Title_Update(0), Time_Last_Window_Title_Update(0)
	{

	}

	/// forbidden call to copy constructor
	DarkGDK_SGlobalStruct(const DarkGDK_SGlobalStruct&) {}

	/// forbidden to copy
	DarkGDK_SGlobalStruct& operator=(const DarkGDK_SGlobalStruct&) { return *this; }

	~DarkGDK_SGlobalStruct()
	{
		if ( Device )
		{
//			while( Device->run() )
//			{
//				Device->closeDevice();
//			}
			Device->drop();
			Device = 0;
		}

		if ( NullDevice )
		{
//			while( NullDevice->run() )
//			{
//				NullDevice->closeDevice();
//			}
			NullDevice->drop();
			NullDevice = 0;
		}
	}

public:

	///@brief updateWindowStack
	virtual void updateWindowStack()
	{
		const s32 h = 32;
		const u32 windowCount = Windows.size();
		if (windowCount==0)
		{
			return;
		}
		const s32 windowMax = core::s32_max( ScreenRect.getWidth(), ScreenRect.getHeight() );
		const s32 windowSize = core::round32( windowMax / (s32)windowCount );

		for (u32 i=0; i<windowCount; i++)
		{
			gui::IGUIButton* btn = Windows[i].ToggleButton;
			if (btn)
			{
				btn->setRelativePosition( core::recti( i*windowSize, ScreenRect.LowerRightCorner.Y-h, (i+1)*windowSize,ScreenRect.LowerRightCorner.Y-1) );
			}
		}
	}

	///@brief clear AppData
	void clear()
	{
		Memblocks.clear();
		ViewPorts.clear();
		Cameras.clear();
		Images.clear();
		Objects.clear();
		Texts.clear();
		Windows.clear();
	}

	///@brief window shown when EscapeKey pressed
	gui::IGUIWindow* createEscapeWindow( )
	{
		if (!Device)
			return 0;

		gui::IGUIEnvironment* env = Device->getGUIEnvironment();

		video::IVideoDriver* driver = Device->getVideoDriver();

		EscapeWindow = env->addWindow( core::recti( core::position2di(0,0), driver->getScreenSize() ), false, L"", env->getRootGUIElement(), -1 );
		const core::recti& cr = EscapeWindow->getClientRect();
		const s32 w = cr.getWidth();
		const s32 h = cr.getHeight();
		const s32 bw =  48;
		const s32 bh = 48;
		const s32 grid_rows = 8;
		const s32 grid_cols = 8;
		const s32 grid_cell_w = core::round32( (f32)w / (f32)grid_cols );
		const s32 grid_cell_h = core::round32( (f32)h / (f32)grid_rows );
		s32 bx = 0;
		s32 by = core::round32( (f32)(grid_rows-1)*(f32)grid_cell_h );

		env->addButton( core::recti( bx,h-bh,bx+w/2,h-1), EscapeWindow, -1, L"Exit ?", L"Wollen Sie das Program beenden?" );
	}

	///@brief return internal boolean key-states
	virtual bool getKeyState( EKEY_CODE keyCode ) const
	{
		return KeyIsDown[keyCode];
	}

	///@brief return number of key-elelements in keybuffer
	virtual u32 kbhit( ) const
	{
		return KeyBuffer.size();
	}

///@brief OnKey () Event-Handler
	virtual bool OnKey( const SEvent::SKeyInput& kin )
	{
		//wchar_t kchar = kin.Char;
		EKEY_CODE kkey = kin.Key;
		bool kpressed = kin.PressedDown;
		KeyIsDown[kkey] = kin.PressedDown;

		/// Escape-key ==> exit program
		if(kkey == KEY_ESCAPE)
		{
			if (Device)
				Device->drop();
			exit(0); // we exit
		}

		if (!Device)
			return false;

		/// Space-key ==> toggle camera event-receiver enable/disable
		if (kkey == KEY_SPACE && !kpressed)
		{
			scene::ISceneManager* smgr = Device->getSceneManager();
			if (smgr)
			{
				scene::ICameraSceneNode* camera = smgr->getActiveCamera();
				if (camera)
				{
					camera->setInputReceiverEnabled( !camera->isInputReceiverEnabled() );
				}
			}
			return true;
		}

		/// Print-key ==> create screenshot image] unique name by timer
		if ( (kkey == KEY_PRINT || kkey == KEY_SNAPSHOT) && !kpressed)
		{
			video::IVideoDriver* driver = Device->getVideoDriver();
			video::IImage* screenshot = driver->createScreenShot();
			ITimer* timer = Device->getTimer();
			if (screenshot)
			{
				io::path name = "./screenshot_render_audio_spectrum_";
				name += timer->getRealTime();
				name += ".png";
				driver->writeImageToFile( screenshot, name);
				screenshot->drop();
			}
			return true; /// ??????
		}

		return false;
	}

	///@brief OnEvent () Main Event-Handler
	virtual bool OnMouse (const SEvent::SMouseInput &m)
	{
		//MouseClick = (s32)m.isLeftPressed() + 2 * (s32)m.isRightPressed(); + 3*(s32)m.isMiddlePressed();

		if (MousePosX != m.X)
		{
			MouseMoveX = m.X - MousePosX;
			MousePosX = m.X;
		}
		if (MousePosY != m.Y)
		{
			MouseMoveY = m.Y - MousePosY;
			MousePosY = m.Y;
		}
		if (MousePosZ != m.Wheel)
		{
			MouseMoveZ = m.Wheel - MousePosZ;
			MousePosZ = m.Wheel;
			MouseWheel = m.Wheel;
		}

		return false;
	}

	///@brief OnEvent () Main Event-Handler
	virtual bool OnEvent (const SEvent &event) _IRR_OVERRIDE_
	{

//		/// handle Keyboard
//		// We use this array to store the current state of each key
//		bool KeyIsDown[KEY_KEY_CODES_COUNT];
//		core::array<EKEY_CODE> KeyBuffer; // kbhit und getKey()
//
		/// Keyboard

		if (event.EventType == EET_KEY_INPUT_EVENT)
		{
			return OnKey( event.KeyInput );
		}

		/// Mouse

		if (event.EventType == EET_MOUSE_INPUT_EVENT)
		{
			return OnMouse( event.MouseInput );
		}
		/// GUI

		if (event.EventType == EET_GUI_EVENT)
		{
			if (!Device)
				return false;

			//ITimer* timer = Device->getTimer();
			gui::IGUIEnvironment* env = Device->getGUIEnvironment();
			//video::IVideoDriver* driver = Device->getVideoDriver();
			//scene::ISceneManager* smgr = Device->getSceneManager();

			gui::IGUIElement* caller = event.GUIEvent.Caller;

			/// Event :: WindowClose

			if (event.GUIEvent.EventType==gui::EGET_ELEMENT_CLOSED)
			{
				if (caller->getType() == gui::EGUIET_WINDOW)
				{
					caller->setVisible(false);

					DarkGDK_SManagedWindow managedWindow;
					managedWindow.Window = ((gui::IGUIWindow*)caller);
					managedWindow.ToggleButton = env->addButton( core::recti(0,0,1,1)+ScreenRect.UpperLeftCorner, env->getRootGUIElement(), -1, managedWindow.Window->getText(), L"This is a ToggleButton" );
					Windows.push_back( managedWindow );

					updateWindowStack();

					return true; // catch event by returning true
				}
				return false; // else return false
			}

			/// Event :: ButtonClick

			if (event.GUIEvent.EventType==gui::EGET_BUTTON_CLICKED)
			{
				if (caller)
				{
					u32 c = Windows.size();
					for (u32 i=0; i<c; i++)
					{
						if (caller == Windows[i].ToggleButton )
						{
							gui::IGUIWindow* win = Windows[i].Window;

							if (win)
							{
								win->setVisible(true);
								env->setFocus( win );
							}

							env->getRootGUIElement()->removeChild( caller );
							caller = 0;
							Windows.erase( i );
							updateWindowStack();
							return true;
						}
					}
				}
			}

		}


		// exit function
		return false;
	}

};

} // end namespace irr

#endif // DARKGDK_H
