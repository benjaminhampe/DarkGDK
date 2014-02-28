#ifndef __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_CAMERA_H__
#define __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_CAMERA_H__

#include "DarkGDK_struct.h"

namespace irr
{

/// DarkGDK :: Camera

///@brief Get Pointer to Camera
scene::ICameraSceneNode* dbGetCamera( u32 camID );

///@brief Get camera's internal array-index by given ID
u32 dbGetCameraArrayIndex(u32 camID);

///@brief Returns 'true' if the camera exists, otherwise 'false'
bool dbCameraExist(u32 id);

///@brief Returns a valid (>0) unused (free) camera id.
u32 dbGetFreeCameraID();

///@brief
void dbMakeCamera(u32 camID);

///@brief Delete the camera given by its ID
bool dbDeleteCamera(u32 camID);

///@brief Move the camera using the arrow keys
void dbControlCameraUsingArrowKeys ( u32 camID, f32 moveSpeed = 0.1f, f32 turnSpeed = 100.f, f32 jumpSpeed = 0.f, bool bNoVerticalMovement = false );

///@brief
void dbPositionCamera( u32 id, f32 x, f32 y, f32 z );

///@brief
f32 dbCameraPositionX( u32 id );

///@brief
f32 dbCameraPositionY( u32 id );

///@brief
f32 dbCameraPositionZ( u32 id );

///@brief
void dbRotateCamera( u32 id, f32 x, f32 y, f32 z );

void dbXRotateCamera( u32 id, f32 x );

void dbYRotateCamera( u32 id, f32 y );

void dbZRotateCamera( u32 id, f32 z );

f32 dbCameraAngleX( u32 id );

f32 dbCameraAngleY( u32 id );

f32 dbCameraAngleZ( u32 id );

void dbPointCamera( u32 id, f32 x, f32 y, f32 z );

void dbMoveCamera( u32 id, f32 speed );

void dbMoveCameraUp( u32 id, f32 speed );

void dbMoveCameraXZ( u32 id, f32 speed );

void dbStrafeCamera( u32 id, f32 speed );

//bool setFrustum(float l, float r, float b, float t, float n, float f)

//bool setOrthoFrustum(float l, float r, float b, float t, float n, float f)

//bool dbPositionCamera( irr::u32 cam_id, irr::f32 x, irr::f32 y, irr::f32 z)
//
//bool dbMoveCamera( irr::u32 cam_id, irr::f32 speed)
//
//bool dbMoveCameraUp( irr::u32 cam_id, irr::f32 speed)
//
//bool dbMoveCameraX( irr::u32 cam_id, irr::f32 speed)
//
//bool dbMoveCameraY( irr::u32 cam_id, irr::f32 speed)
//
//bool dbMoveCameraZ( irr::u32 cam_id, irr::f32 speed)
//
//bool dbPitchCameraUp( irr::u32 cam_id, irr::f32 speed)
//
//bool dbPitchCameraDown( irr::u32 cam_id, irr::f32 speed)
//
//bool dbRollCameraLeft( irr::u32 cam_id, irr::f32 speed)
//
//bool dbRollCameraRight( irr::u32 cam_id, irr::f32 speed)
//
//bool dbStrafeCameraLeft( irr::u32 cam_id, irr::f32 speed)
//
//bool dbStrafeCameraRight( irr::u32 cam_id, irr::f32 speed)
//
//bool dbYawCameraLeft( irr::u32 cam_id, irr::f32 speed)
//
//bool dbYawCameraRight( irr::u32 cam_id, irr::f32 speed)
//
//bool dbSetCurrentCamera( irr::u32 cam_id )
//
//bool setActiveCamera( scene::ISceneManager* smgr, scene::ICameraSceneNode* newActive )
//
//f32 getObjectDistance( scene::ICameraSceneNode* camera, scene::ISceneNode* node )
//
//bool setToFollow( scene::ICameraSceneNode* camera, scene::ISceneNode* node, f32 dXZ, f32 dY )
//
//bool dbPointCamera( irr::u32 cam_id, irr::f32 x, irr::f32 y, irr::f32 z)
//
//bool dbSetCameraNear( irr::u32 cam_id, irr::f32 nearValue )

//bool dbSetCameraFar( irr::u32 cam_id, irr::f32 farValue )

//bool dbSetCameraFov( irr::u32 cam_id, irr::f32 fovValue )

//bool dbSetCameraFog( irr::u32 cam_id, bool bEnabled, irr::video::E_FOG_TYPE fogType, const irr::video::SColor& fogColor )

//bool dbSetCameraFogDistance( irr::u32 cam_id, irr::f32 fogNear, irr::f32 fogFar )

//irr::video::IImage* dbGetCameraImage( irr::u32 cam_id )

//core::vector3df getPickVector( scene::ICameraSceneNode* camera, s32 mouse_x, s32 mouse_y );

//scene::ISceneNode* pickObject( scene::ICameraSceneNode* camera, s32 mouse_x, s32 mouse_y );

//core::position2di getScreenPos( scene::ISceneManager* smgr );

} // end namespace irr

#endif // __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_CAMERA_H__
