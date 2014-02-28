#ifndef __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_AUDIO_H__
#define __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_AUDIO_H__

#include "DarkGDK_struct.h"
#include "DarkGDK_math.h"

namespace irr
{

/// DarkGDK :: Audio/Sound/Music/FFT/MIDI Player/Recorder/FFT-Resampler/Synthesizer Module

///@brief Get Pointer to AudioEngine
inline void* dbGetSoundBuffer( u32 soundID );
{
	SGlobalStruct& app = SGlobalStruct::getInstance();

	if (soundID == 0)
		return 0;

	u32 count = app.Sounds.size();

	bool found = false;

	u32 i = 0;
	while (!found && i<count)
	{
		if (app.Sounds[i].ID == camID)
			found = true;
		else
			i++;
	}

	if (found)
		return app.Sounds[i].Node;
	else
		return 0;
}

///@brief Get Pointer to Sound
inline u32 dbGetSoundInternalIndex(u32 camID)
{
	SGlobalStruct& app = SGlobalStruct::getInstance();

	const u32 count = app.Sounds.size();

	if (camID == 0)
		return count;

	bool found = false;
	u32 i = 0;
	while (!found && i<count)
	{
		if (app.Sounds[i].ID == camID)
			found = true;
		else
			i++;
	}

	if (found)
		return i;
	else
		return count;
}

///@brief Returns 'true' if the Sound exists, otherwise 'false'
inline bool dbSoundExist(u32 id)
{
	if (dbGetSoundPointer(id))
		return true;
	else
		return false;
}

///@brief Returns a valid (>0), unused (free) Sound-ID
inline u32 dbGetFreeSoundID()
{
	SGlobalStruct& app = SGlobalStruct::getInstance();

	u32 id = 1;

	while ( !dbSoundExist(id) )
	{
		id++;
	}
	id++;

	return id;
}

///@brief Delete the my_snd given by its ID
inline bool dbDeleteSound(u32 camID)
{
	if (!dbSoundExist(camID))
	{
		#ifdef _DEBUG
		printf( "dbDeleteSound() :: Could not find my_snd with ID %d\n", camID);
		#endif // _DEBUG
		return false;
	}

	SGlobalStruct& app = SGlobalStruct::getInstance();
	const u32 count = app.Sounds.size();
	const u32 index = dbGetSoundInternalIndex(camID);

	/// penibel check
	if ( index >= count )
	{
		#ifdef _DEBUG
		printf( "dbDeleteSound() :: Could not find my_snd with ID %d\n", camID);
		#endif // _DEBUG
		return false;
	}

	/// get pointer and call its remove() function
	scene::ISoundsceneNode* node = app.Sounds[index].Node;
	if (node)
	{
		node->remove();
	}

	/// delete SSound element from array
	app.Sounds.erase(index);

	/// return status
	if (count != app.Sounds.size())
		return true;
	else
		return false;
}

inline void dbMakeSound(u32 camID)
{
	if (dbSoundExist( camID ) )
	{
		#ifdef _DEBUG
		printf( "dbMakeSound() :: Sound with id %d already exist.\n", camID);
		#endif // _DEBUG
		return;
	}

	SGlobalStruct& app = SGlobalStruct::getInstance();
	if (!app.Device)
		return;

	scene::ISceneManager* smgr = app.Device->getSceneManager();
	if (!smgr)
		return;

//	SKeyMap KeyMapArray[6];
//	KeyMapArray[0].Action = EKA_MOVE_FORWARD;
//	KeyMapArray[1].Action = EKA_MOVE_BACKWARD;
//	KeyMapArray[2].Action = EKA_STRAFE_LEFT;
//	KeyMapArray[3].Action = EKA_STRAFE_RIGHT;
//	KeyMapArray[4].Action = EKA_CROUCH;
//	KeyMapArray[5].Action = EKA_JUMP_UP;
//	KeyMapArray[0].KeyCode = KEY_KEY_W;
//	KeyMapArray[1].KeyCode = KEY_KEY_S;
//	KeyMapArray[2].KeyCode = KEY_KEY_A;
//	KeyMapArray[3].KeyCode = KEY_KEY_D;
//	KeyMapArray[4].KeyCode = KEY_KEY_C;
//	KeyMapArray[5].KeyCode = KEY_SPACE;

	scene::ISoundsceneNode* cam = smgr->addSoundsceneNode(smgr->getRootSceneNode());
	if (!cam)
		return;

	cam->setNearValue( 0.01f );
	cam->setFarValue( 10000.0f );
	cam->setPosition( core::vector3df( 0,0,0) );
	cam->setTarget( core::vector3df(0,0,100) );

	SSound tmp;
	tmp.ID = camID;
	tmp.Node = cam;
	app.Sounds.push_back( tmp );
}

//	void dbPositionSound(u32 id, f32 x, f32 y, f32 z);
//	f32 dbSoundPositionX(u32 id);
//	f32 dbSoundPositionY(u32 id);
//	f32 dbSoundPositionZ(u32 id);



inline void dbPositionSound(u32 id, f32 x, f32 y, f32 z)
{
	scene::ISoundsceneNode* my_snd = dbGetSoundPointer(id);
	if (!my_snd) return;
	my_snd->setPosition(core::vector3df(x,y,z));
}

inline f32 dbSoundPositionX(u32 id)
{
	scene::ISoundsceneNode* my_snd = dbGetSoundPointer(id);
	if (!my_snd) return 0.0f;
	return my_snd->getPosition().X;
}

inline f32 dbSoundPositionY(u32 id)
{
	scene::ISoundsceneNode* my_snd = dbGetSoundPointer(id);
	if (!my_snd) return 0.0f;
	return my_snd->getPosition().Y;
}

inline f32 dbSoundPositionZ(u32 id)
{
	scene::ISoundsceneNode* my_snd = dbGetSoundPointer(id);
	if (!my_snd) return 0.0f;
	return my_snd->getPosition().Z;
}



//	void dbRotateSound(u32 id, f32 x, f32 y, f32 z);
//	void dbXRotateSound(u32 id, f32 x);
//	void dbYRotateSound(u32 id, f32 y);
//	void dbZRotateSound(u32 id, f32 z);
//	f32 dbSoundAngleX(u32 id);
//	f32 dbSoundAngleY(u32 id);
//	f32 dbSoundAngleZ(u32 id);

inline void dbRotateSound(u32 id, f32 x, f32 y, f32 z)
{
	scene::ISoundsceneNode* my_snd = dbGetSoundPointer(id);
	if (!my_snd) return;
	my_snd->setRotation(core::vector3df(x,y,z));
}

inline void dbXRotateSound(u32 id, f32 x)
{
	scene::ISoundsceneNode* my_snd = dbGetSoundPointer(id);
	if (!my_snd) return;
	const core::vector3df& rot = my_snd->getRotation();
	my_snd->setRotation(core::vector3df(x,rot.Y,rot.Z));
}

inline void dbYRotateSound(u32 id, f32 y)
{
	scene::ISoundsceneNode* my_snd = dbGetSoundPointer(id);
	if (!my_snd) return;
	const core::vector3df& rot = my_snd->getRotation();
	my_snd->setRotation(core::vector3df(rot.X,y,rot.Z));
}

inline void dbZRotateSound(u32 id, f32 z)
{
	scene::ISoundsceneNode* my_snd = dbGetSoundPointer(id);
	if (!my_snd) return;
	const core::vector3df& rot = my_snd->getRotation();
	my_snd->setRotation(core::vector3df(rot.X,rot.Y,z));
}

inline f32 dbSoundAngleX(u32 id)
{
	scene::ISoundsceneNode* my_snd = dbGetSoundPointer(id);
	if (!my_snd) return 0.0f;
	return my_snd->getRotation().X;
}

inline f32 dbSoundAngleY(u32 id)
{
	scene::ISoundsceneNode* my_snd = dbGetSoundPointer(id);
	if (!my_snd) return 0.0f;
	return my_snd->getRotation().Y;
}

inline f32 dbSoundAngleZ(u32 id)
{
	scene::ISoundsceneNode* my_snd = dbGetSoundPointer(id);
	if (!my_snd) return 0.0f;
	return my_snd->getRotation().Z;
}


//	void dbPointSound( u32 id, f32 x, f32 y, f32 z);

inline void dbPointSound( u32 id, f32 x, f32 y, f32 z)
{
	scene::ISoundsceneNode* my_snd = dbGetSoundPointer(id);
	if (!my_snd) return;
	my_snd->setTarget(core::vector3df(x,y,z));
}

//	void dbMoveSound(u32 id, f32 speed);
//	void dbMoveSoundUp(u32 id, f32 speed);
//	void dbMoveSoundXZ(u32 id, f32 speed);
//	void dbStrafeSound(u32 id, f32 speed);

//
//  static core::vector3df getPickVector( scene::ISoundsceneNode* my_snd, s32 mouse_x, s32 mouse_y );
//  static scene::ISceneNode* pickObject( scene::ISoundsceneNode* my_snd, s32 mouse_x, s32 mouse_y );
//	core::position2di getScreenPos( scene::ISceneManager* smgr );




inline void dbMoveSound(u32 id, f32 speed)
{
	scene::ISoundsceneNode* my_snd = dbGetSoundPointer(id);
	if (!my_snd) return;
	core::vector3df pos = my_snd->getPosition();
	core::vector3df eye = my_snd->getTarget();
	core::vector3df mov = (eye-pos).normalize()*speed;
	pos += mov;
	my_snd->setPosition(pos);
	eye += mov;
	my_snd->setTarget(eye);
}

inline void dbMoveSoundUp(u32 id, f32 speed)
{
	scene::ISoundsceneNode* my_snd = dbGetSoundPointer(id);
	if (!my_snd) return;
	core::vector3df pos = my_snd->getPosition();
	core::vector3df upv = my_snd->getUpVector();
	pos += (upv).normalize()*speed;
	my_snd->setPosition(pos);
}

inline void dbMoveSoundXZ(u32 id, f32 speed)
{
	scene::ISoundsceneNode* my_snd = dbGetSoundPointer(id);
	if (!my_snd) return;
	core::vector3df pos = my_snd->getPosition();
	core::vector3df eye = my_snd->getTarget();
	pos += (eye-pos).normalize()*speed;
	my_snd->setPosition(pos);
}
//
//bool setActiveSound( scene::ISceneManager* smgr, scene::ISoundsceneNode* newActive )
//{
//	if (!smgr)
//		return false;
//
//	scene::ISoundsceneNode* active = smgr->getActiveSound();
//	if (active)
//        active->setInputReceiverEnabled(false);
//
//    if (newActive)
//        newActive->setInputReceiverEnabled(true);
//
//	smgr->setActiveSound(newActive);
//	return true;
//}

///// others
//f32 getObjectDistance( scene::ISoundsceneNode* my_snd, scene::ISceneNode* node )
//{
//    return 0.0f;
//}
//
//bool setToFollow( scene::ISoundsceneNode* my_snd, scene::ISceneNode* node, f32 dXZ, f32 dY )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}

//
///// position
//core::vector3df getPosition( scene::ISoundsceneNode* my_snd )
//{
//    return core::vector3df(0,0,0);
//}
//
//bool setPosition( scene::ISoundsceneNode* my_snd, const core::vector3df& pos )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
//bool setPosition( scene::ISoundsceneNode* my_snd, f32 x, f32 y, f32 z )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
///// move
//bool moveSound( scene::ISoundsceneNode* my_snd, f32 value )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
//bool moveSoundXZ( scene::ISoundsceneNode* my_snd, f32 value )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
//bool moveSoundY( scene::ISoundsceneNode* my_snd, f32 value )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
///// rotation degrees
//core::vector3df getRotation( scene::ISoundsceneNode* my_snd )
//{
//	return core::vector3df(0,0,0);
//}
//
//bool setRotation( scene::ISoundsceneNode* my_snd, const core::vector3df& pos )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
//bool setRotation( scene::ISoundsceneNode* my_snd, f32 x, f32 y, f32 z )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
////bool rotate( scene::ISoundsceneNode* my_snd, const core::vector3df& pos )
////{
////    if (!my_snd)
////        return false;
////
////    /// do something ...
////
////    return true;
////}
////
////bool rotate( scene::ISoundsceneNode* my_snd, f32 x, f32 y, f32 z )
////{
////    if (!my_snd)
////        return false;
////
////    /// do something ...
////
////    return true;
////}
//
//bool rotateX( scene::ISoundsceneNode* my_snd, f32 x )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
//bool rotateY( scene::ISoundsceneNode* my_snd, f32 y )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
//bool rotateZ( scene::ISoundsceneNode* my_snd, f32 z )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
///// target / eye
//core::vector3df getTarget( scene::ISoundsceneNode* my_snd )
//{
//    return core::vector3df(0,0,0);
//}
//
//bool setTarget( scene::ISoundsceneNode* my_snd, const core::vector3df& pos )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
//bool setTarget( scene::ISoundsceneNode* my_snd, f32 x, f32 y, f32 z )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
//
//bool targetObject( scene::ISoundsceneNode* my_snd, scene::ISceneNode* node )
//{
//    if (!node)
//        return false;
//
//    if (!my_snd)
//        return false;
//
//    core::vector3df eye = node->getTransformedBoundingBox().getCenter();
//
//    my_snd->setTarget( eye );
//    return true;
//}
//

//core::vector3df getPickVector( scene::ISoundsceneNode* my_snd, s32 mouse_x, s32 mouse_y )
//{
//    return core::vector3df(0,0,0);
//}
//
//scene::ISceneNode* pickObject( scene::ISoundsceneNode* my_snd, s32 mouse_x, s32 mouse_y )
//{
//    return 0;
//}
//
///// others
//bool strafeSound( scene::ISoundsceneNode* my_snd, f32 value )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
//bool turnSound( scene::ISoundsceneNode* my_snd, f32 value )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
//bool tiltSound( scene::ISoundsceneNode* my_snd, f32 value )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
//bool pitchSound( scene::ISoundsceneNode* my_snd, f32 value )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
//bool rollSound( scene::ISoundsceneNode* my_snd, f32 value )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
//bool yawSound( scene::ISoundsceneNode* my_snd, f32 value )
//{
//    if (!my_snd)
//        return false;
//
//    /// do something ...
//
//    return true;
//}
//
//bool viewOrtho( scene::ISoundsceneNode* my_snd )
//{
//	if (!my_snd)
//		return false;
//
//	my_snd->setPosition( core::vector3df( 0,100,0) );
//	my_snd->setTarget( core::vector3df(0,0,100) );
//	return true;
//}
//
//bool viewIsometric( scene::ISoundsceneNode* my_snd )
//{
//	if (!my_snd)
//		return false;
//
//	my_snd->setPosition( core::vector3df( 0,100,0) );
//	my_snd->setTarget( core::vector3df(0,0,100) );
//	return true;
//}
//
//bool viewDimetric( scene::ISoundsceneNode* my_snd )
//{
//	if (!my_snd)
//		return false;
//
//	my_snd->setPosition( core::vector3df( 0,100,0) );
//	my_snd->setTarget( core::vector3df(0,0,100) );
//	return true;
//}
//
//bool viewPosX( scene::ISoundsceneNode* my_snd )
//{
//	if (!my_snd)
//		return false;
//
//	my_snd->setPosition( core::vector3df( 0,100,0) );
//	my_snd->setTarget( core::vector3df(0,0,100) );
//	return true;
//}
//
//bool viewPosY( scene::ISoundsceneNode* my_snd )
//{
//	if (!my_snd)
//		return false;
//
//	my_snd->setPosition( core::vector3df( 0,100,0) );
//	my_snd->setTarget( core::vector3df(0,0,100) );
//	return true;
//}
//
//bool viewPosZ( scene::ISoundsceneNode* my_snd )
//{
//	if (!my_snd)
//		return false;
//
//	my_snd->setPosition( core::vector3df( 0,100,0) );
//	my_snd->setTarget( core::vector3df(0,0,100) );
//	return true;
//}
//
//bool viewNegX( scene::ISoundsceneNode* my_snd )
//{
//	if (!my_snd)
//		return false;
//
//	my_snd->setPosition( core::vector3df( 0,100,0) );
//	my_snd->setTarget( core::vector3df(0,0,100) );
//	return true;
//}
//
//bool viewNegY( scene::ISoundsceneNode* my_snd )
//{
//	if (!my_snd)
//		return false;
//
//	my_snd->setPosition( core::vector3df( 0,100,0) );
//	my_snd->setTarget( core::vector3df(0,0,100) );
//	return true;
//}
//
//bool viewNegZ( scene::ISoundsceneNode* my_snd )
//{
//	if (!my_snd)
//		return false;
//
//	my_snd->setPosition( core::vector3df( 0,100,0) );
//	my_snd->setTarget( core::vector3df(0,0,100) );
//	return true;
//}
//
////
////
////
//
//
//

//
//
//bool dbPointSound( irr::u32 cam_id, irr::f32 x, irr::f32 y, irr::f32 z)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//bool dbSetSoundNear( irr::u32 cam_id, irr::f32 nearValue )
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//bool dbSetSoundFar( irr::u32 cam_id, irr::f32 farValue )
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//bool dbSetSoundFov( irr::u32 cam_id, irr::f32 fovValue )
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbSetSoundFog( irr::u32 cam_id, bool bEnabled, irr::video::E_FOG_TYPE fogType, const irr::video::SColor& fogColor )
//{
//
//    return true;
//}
//
//bool dbSetSoundFogDistance( irr::u32 cam_id, irr::f32 fogNear, irr::f32 fogFar )
//{
//
//}
//
//irr::video::IImage* dbGetSoundImage( irr::u32 cam_id )
//{
//
//}
//
//bool dbSetCurrentSound( irr::u32 cam_id )
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbPositionSound( irr::u32 cam_id, irr::f32 x, irr::f32 y, irr::f32 z)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbRotateSound( irr::u32 cam_id, irr::f32 x, irr::f32 y, irr::f32 z)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbRotateSoundX( irr::u32 cam_id, irr::f32 x)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbRotateSoundY( irr::u32 cam_id, irr::f32 y)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbRotateSoundZ( irr::u32 cam_id, irr::f32 z)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//
//
//
//irr::f32 dbSoundPositionX( irr::u32 cam_id )
//{
//	return false;
//}
//
//irr::f32 dbSoundPositionY( irr::u32 cam_id )
//{
//	return false;
//}
//
//irr::f32 dbSoundPositionZ( irr::u32 cam_id )
//{
//	return false;
//}
//
//irr::f32 dbSoundRotationX( irr::u32 cam_id )
//{
//	return false;
//}
//
//irr::f32 dbSoundRotationY( irr::u32 cam_id )
//{
//	return false;
//}
//
//irr::f32 dbSoundRotationZ( irr::u32 cam_id )
//{
//	return false;
//}
//
//irr::f32 dbSoundAngleX( irr::u32 cam_id )
//{
//	return false;
//}
//
//irr::f32 dbSoundAngleY( irr::u32 cam_id )
//{
//	return false;
//}
//
//irr::f32 dbSoundAngleZ( irr::u32 cam_id )
//{
//	return false;
//}
//
//
//bool dbMoveSound( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbMoveSoundUp( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbMoveSoundX( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbMoveSoundY( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbMoveSoundZ( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbPitchSoundUp( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("dbSetSoundNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbPitchSoundDown( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("pitch my_snd down()", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbRollSoundLeft( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("roll my_snd left()", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbRollSoundRight( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("roll my_snd right()", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbStrafeSoundLeft( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("strafe my_snd left()", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbStrafeSoundRight( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("strafe my_snd right()", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbYawSoundLeft( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("yaw my_snd left()", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbYawSoundRight( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ISoundsceneNode* my_snd = dbGetSoundByIndex( cam_id );
//	if (!my_snd)
//	{
//		irr::os::Printer::log("yaw my_snd right()", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}


//
//
//SoundManager::SoundManager( scene::ISceneManager* smgr,
//    gui::IGUIEnvironment* env, gui::IGUIElement* parent, s32 id, const core::recti& rectangle )
//: gui::IGUIElement( gui::EGUIET_ELEMENT, env, parent, id, rectangle), SceneManager(smgr), CurrentSound(0)
//{
//    const s32 x1 = rectangle.UpperLeftCorner.X;
//    const s32 y1 = rectangle.UpperLeftCorner.Y;
//    const s32 w = rectangle.getWidth();
//    // const s32 h = rectangle.getHeight();
//
//    // gui::IGUIEnvironment* env = env;
//    s32 t = 64;
//    s32 x = x1;
//    s32 y = y1;
//    s32 dx = 2*t;
//    s32 dy = 21;
//    env->addCheckBox( true, core::recti(x,y,x+dx-1,y+dy-1), this, -1, L"AutoUpdate"); x += dx;
//    env->addButton( core::recti(x,y,x+dx-1,y+dy-1), this, -1, L"Update Dialog"); x += dx;
//    env->addButton( core::recti(x,y,x+dx-1,y+dy-1), this, -1, L"Update SoundUtil"); x += dx;
//    y += dy;
//
//    /// index
//    x = x1;
//    dx = t/2;
//    env->addStaticText( L"Nr", core::recti(x,y,x+dx-1,y+dy-1), true, false, this, -1, true); x += dx;
//    dx = t/2;
//    env->addEditBox( L"1", core::recti(x,y,x+dx-1,y+dy-1), true, this, -1); x += dx;
//    dx = t/3;
//    env->addStaticText( L"/", core::recti(x,y,x+dx-1,y+dy-1), true, false, this, -1, true); x += dx;
//    dx = t/2;
//    env->addEditBox( L"1", core::recti(x,y,x+dx-1,y+dy-1), true, this, -1); x += dx;
//    dx = t/3;
//    env->addButton( core::recti(x,y,x+dx-1,y+dy-1), this, -1, L"<"); x += dx;
//    dx = t/3;
//    env->addButton( core::recti(x,y,x+dx-1,y+dy-1), this, -1, L">"); x += dx;
//    dx = 2*t;
//    env->addEditBox( L"SoundUtil Name", core::recti(x,y,x+dx-1,y+dy-1), true, this, -1); x += dx;
//    dx = 2*t;
//    env->addCheckBox( true, core::recti(x,y,x+dx-1,y+dy-1), this, -1, L"Enable"); x += dx;
//    y += dy;
//
//
//    /// position
//    x = x1;
//    new CGUIVector3d<f32>( env, this, -1, core::recti(x,y,x+w-1,y+dy-1), L"Position" );
//    y += dy;
//
//    /// position
//    x = x1;
//    new CGUIVector3d<f32>( env, this, -1, core::recti(x,y,x+w-1,y+dy-1), L"Rotation" );
//    y += dy;
//
//    /// target / eye-vector
//    x = x1;
//    new CGUIVector3d<f32>( env, this, -1, core::recti(x,y,x+w-1,y+dy-1),  L"Target" );
//    y += dy;
//
////    x = x1;
////    dx = t;
////    env->addStaticText( L"Position", core::recti(x,y,x+dx-1,y+dy-1), true, false, this, -1, true); x += dx;
////    dx = dy;
////    env->addStaticText( L"X", core::recti(x,y,x+dx-1,y+dy-1), true, false, this, -1, true); x += dx;
////    dx = dy;
////    env->addCheckBox( true, core::recti(x,y,x+dx-1,y+dy-1), this, -1, L""); x += dx;
////    dx = t;
////    env->addSpinBox( L"0", core::recti(x,y,x+dx-1,y+dy-1), true, this, -1); x += dx;
////    dx = dy;
////    env->addStaticText( L"Y", core::recti(x,y,x+dx-1,y+dy-1), true, false, this, -1, true); x += dx;
////    dx = dy;
////    env->addCheckBox( true, core::recti(x,y,x+dx-1,y+dy-1), this, -1, L""); x += dx;
////    dx = t;
////    env->addSpinBox( L"0", core::recti(x,y,x+dx-1,y+dy-1), true, this, -1); x += dx;
////    dx = dy;
////    env->addStaticText( L"Z", core::recti(x,y,x+dx-1,y+dy-1), true, false, this, -1, true); x += dx;
////    dx = dy;
////    env->addCheckBox( true, core::recti(x,y,x+dx-1,y+dy-1), this, -1, L""); x += dx;
////    dx = t;
////    env->addSpinBox( L"0", core::recti(x,y,x+dx-1,y+dy-1), true, this, -1); x += dx;
////    dx = t;
////    env->addButton( core::recti(x,y,x+dx-1,y+dy-1), this, -1, L"Set");
////    y += dy;
////
////    /// rotation
////    x = x1;
////    dx = t/2;
////    env->addCheckBox( true, core::recti(x,y,x+dx-1,y+dy-1), this, -1, L"X"); x += dx;
////    dx = t;
////    env->addSpinBox( L"0", core::recti(x,y,x+dx-1,y+dy-1), true, this, -1); x += dx;
////    dx = t/2;
////    env->addCheckBox( true, core::recti(x,y,x+dx-1,y+dy-1), this, -1, L"Y"); x += dx;
////    dx = t;
////    env->addSpinBox( L"0", core::recti(x,y,x+dx-1,y+dy-1), true, this, -1); x += dx;
////    dx = t/2;
////    env->addCheckBox( true, core::recti(x,y,x+dx-1,y+dy-1), this, -1, L"Z"); x += dx;
////    dx = t;
////    env->addSpinBox( L"0", core::recti(x,y,x+dx-1,y+dy-1), true, this, -1); x += dx;
////    dx = t/2;
////    env->addButton( core::recti(x,y,x+dx-1,y+dy-1), this, -1, L"Set");
////    y += dy;
//
////        Sounds.reallocate( 32 );
////        Sounds.set_used( 0 );
////        SoundNames.reallocate( 32 );
////        SoundNames.set_used( 0 );
////
////        for ( u32 i = 0; i < 32; i++ )
////        {
////            Sounds.push_back(0);
////            SoundNames.push_back(L"");
////        }
////
////        Sounds.set_used( 0 );
////        SoundNames.set_used( 0 );
////
//        clear();
//
////        addSoundPosZ();
//
////        createFPS( 0.1, 100.0f );
//}
//
//SoundManager::~SoundManager()
//{
//
//}
//
////! called if an event happened.
//bool SoundManager::OnEvent(const SEvent& event)
//{
//	return IGUIElement::OnEvent(event);
//}
////! draws the element and its children
//void SoundManager::draw()
//{
//	IGUIElement::draw();
//}
//
//bool SoundManager::clear()
//{
//    Sounds.reallocate( 32 );
//    Sounds.set_used( 0 );
//    SoundNames.reallocate( 32 );
//    SoundNames.set_used( 0 );
//
//    for ( u32 i = 0; i < 32; i++ )
//    {
//        Sounds.push_back(0);
//        SoundNames.push_back(L"");
//    }
//
//    Sounds.set_used( 0 );
//    SoundNames.set_used( 0 );
//    return true;
//}
//
//u32 SoundManager::getSoundCount() const
//{
//    return Sounds.size();
//}
//
//scene::ISoundsceneNode* SoundManager::getCurrentSound( )
//{
//    return CurrentSound;
//}
//
//bool SoundManager::setCurrentSound( u32 index )
//{
//    CurrentSound = getSound( index );
//    return true;
//}
//
//scene::ISoundsceneNode*
//SoundManager::getSound( u32 index )
//{
//    if (index-1<Sounds.size())
//    {
//        return Sounds[index-1];
//    }
//    else
//    {
//        return 0;
//    }
//}
//
//scene::ISoundsceneNode*
//SoundManager::getSoundByName( const core::stringw& _compare_name )
//{
//    return 0;
//}
//
//
//
//bool SoundManager::removeSound( u32 index )
//{
//    return true;
//}
//
//bool SoundManager::setSoundName( u32 index, const core::stringw& name )
//{
//    return true;
//}
//
//core::stringw SoundManager::getSoundName( u32 index ) const
//{
//    return L"";
//}





} // end namespace irr

#endif // __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_CAMERA_H__
