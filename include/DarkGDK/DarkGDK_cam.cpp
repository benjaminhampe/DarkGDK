#include "DarkGDK_cam.h"

#include "DarkGDK_struct.h"
#include "DarkGDK_math.h"

#include <../../source/Irrlicht/CSceneNodeAnimatorCameraFPS.h>

namespace irr
{

/// DarkGDK :: Camera

///@brief Get Pointer to Camera
scene::ICameraSceneNode* dbGetCamera( u32 camID )
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	if (camID == 0)
		return 0;

	u32 count = app.Cameras.size();

	bool found = false;

	u32 i = 0;
	while (!found && i<count)
	{
		if (app.Cameras[i].ID == camID)
		{
			found = true;
			// break;
		}
		i++;
	}

	if (found)
	{
		return app.Cameras[i-1].Node;
	}
	else
	{
		// printf("Did not found Camera with ID %d\n", camID );
		return 0;
	}

}


///@brief Get camera's internal array-index by given ID
u32 dbGetCameraArrayIndex(u32 camID)
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	const u32 count = app.Cameras.size();

	if (camID == 0)
		return count;

	bool found = false;
	u32 i = 0;
	while (!found && i<count)
	{
		if (app.Cameras[i].ID == camID)
			found = true;
		else
			i++;
	}

	if (found)
		return i;
	else
		return count;
}

///@brief Returns 'true' if the camera exists, otherwise 'false'
bool dbCameraExist(u32 id)
{
	if (dbGetCamera(id))
		return true;
	else
		return false;
}

///@brief Returns a valid (>0) unused (free) camera id.
u32 dbGetFreeCameraID()
{
//	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	u32 id = 1;

	while ( !dbCameraExist(id) )
	{
		id++;
	}
	id++;

	return id;
}



void dbMakeCamera(u32 camID)
{
	if (dbCameraExist( camID ) )
	{
		// #ifdef _DEBUG
		printf( "dbMakeCamera() :: Camera with id %d already exist.\n", camID);
		// #endif // _DEBUG
		return;
	}

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return;

	scene::ISceneManager* smgr = app.Device->getSceneManager();
	if (!smgr)
		return;

	SKeyMap keyArray[6];
	keyArray[0].Action = EKA_MOVE_FORWARD;
	keyArray[1].Action = EKA_MOVE_BACKWARD;
	keyArray[2].Action = EKA_STRAFE_LEFT;
	keyArray[3].Action = EKA_STRAFE_RIGHT;
	keyArray[4].Action = EKA_CROUCH;
	keyArray[5].Action = EKA_JUMP_UP;
	keyArray[0].KeyCode = KEY_KEY_W;
	keyArray[1].KeyCode = KEY_KEY_S;
	keyArray[2].KeyCode = KEY_KEY_A;
	keyArray[3].KeyCode = KEY_KEY_D;
	keyArray[4].KeyCode = KEY_KEY_C;
	keyArray[5].KeyCode = KEY_SPACE;

	scene::ICameraSceneNode* cam = smgr->addCameraSceneNodeFPS(smgr->getRootSceneNode(), 100, 0.5f, -1, &keyArray[0], 6, false, 0.f, false, true );
	//scene::ICameraSceneNode* cam = smgr->addCameraSceneNode(smgr->getRootSceneNode());
	if (!cam)
		return;

	cam->setNearValue( 1.f );
	cam->setFarValue( 10000.0f );
	cam->setPosition( core::vector3df( 0,0,0) );
	cam->setTarget( core::vector3df(0,0,100) );

	DarkGDK_SCamera tmp;
	tmp.ID = camID;
	tmp.Node = cam;
	app.Cameras.push_back( tmp );
}



///@brief Delete the camera given by its ID
bool dbDeleteCamera(u32 camID)
{
	if (!dbCameraExist(camID))
	{
		#ifdef _DEBUG
		printf( "dbDeleteCamera() :: Could not find camera with ID %d\n", camID);
		#endif // _DEBUG
		return false;
	}

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	const u32 count = app.Cameras.size();
	const u32 index = dbGetCameraArrayIndex(camID);

	/// penibel check
	if ( index >= count )
	{
		#ifdef _DEBUG
		printf( "dbDeleteCamera() :: Could not find camera with ID %d\n", camID);
		#endif // _DEBUG
		return false;
	}

	/// get pointer and call its remove() function
	scene::ICameraSceneNode* node = app.Cameras[index].Node;
	if (node)
	{
		node->remove();
	}

	/// delete SCamera element from array
	app.Cameras.erase(index);

	/// return status
	if (count != app.Cameras.size())
		return true;
	else
		return false;
}

// move the camera using the arrow keys
void dbControlCameraUsingArrowKeys ( u32 camID, f32 moveSpeed, f32 turnSpeed, f32 jumpSpeed, bool bNoVerticalMovement )
{
//	scene::ICameraSceneNode* node = dbGetCamera( camID );
//	if (!node)
//		return;
//
//	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
//	if (!app.Device)
//		return;
//
//	scene::ISceneManager* smgr = app.Device->getSceneManager();
//	if (!smgr)
//		return;
//
//	const core::list<scene::ISceneNodeAnimator*>& Animators = node->getAnimators();
//	core::list<scene::ISceneNodeAnimator*>::ConstIterator it = Animators.begin();
//
//	bool found = false;
//	scene::CSceneNodeAnimatorCameraFPS* fpsAnimator = 0;
//
//	while (!found && ( it!=Animators.end() ))
//	{
//		if ( (*it)->getType() == scene::ESNAT_CAMERA_FPS )
//		{
//			fpsAnimator = (scene::CSceneNodeAnimatorCameraFPS*)(*it);
//			found = true;
//		}
//		it++;
//	}
//
//	if (!found)
//	{
//		gui::ICursorControl* cursor = app.Device->getCursorControl();
//
//		SKeyMap KeyMapArray[6];
//		KeyMapArray[0].Action = EKA_MOVE_FORWARD;
//		KeyMapArray[1].Action = EKA_MOVE_BACKWARD;
//		KeyMapArray[2].Action = EKA_STRAFE_LEFT;
//		KeyMapArray[3].Action = EKA_STRAFE_RIGHT;
//		KeyMapArray[4].Action = EKA_CROUCH;
//		KeyMapArray[5].Action = EKA_JUMP_UP;
//		KeyMapArray[0].KeyCode = KEY_KEY_W;
//		KeyMapArray[1].KeyCode = KEY_KEY_S;
//		KeyMapArray[2].KeyCode = KEY_KEY_A;
//		KeyMapArray[3].KeyCode = KEY_KEY_D;
//		KeyMapArray[4].KeyCode = KEY_KEY_C;
//		KeyMapArray[5].KeyCode = KEY_SPACE;
//
//		fpsAnimator = new scene::CSceneNodeAnimatorCameraFPS( cursor, turnSpeed, moveSpeed, jumpSpeed, KeyMapArray, 5, bNoVerticalMovement, false);
//		//node->addAnimator( smgr->createSceneNodeAnimator( scene::ESNAT_CAMERA_FPS ) );
//		//fpsAnimator = (*(node->getAnimators().begin())); // dereference iterator
//	}
//
//	if (!fpsAnimator)
//	{
//		printf("dbControlCameraUsingArrowKeys() :: Could not create FPS-Animator\n");
//		return;
//	}
//
//	node->setInputReceiverEnabled( true );
}


void dbPositionCamera( u32 id, f32 x, f32 y, f32 z )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return;
	camera->setPosition(core::vector3df(x,y,z));
}

f32 dbCameraPositionX( u32 id )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return 0.0f;
	return camera->getPosition().X;
}

f32 dbCameraPositionY( u32 id )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return 0.0f;
	return camera->getPosition().Y;
}

f32 dbCameraPositionZ( u32 id )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return 0.0f;
	return camera->getPosition().Z;
}

void dbRotateCamera( u32 id, f32 x, f32 y, f32 z )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return;
	camera->setRotation(core::vector3df(x,y,z));
}

void dbXRotateCamera( u32 id, f32 x )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return;
	const core::vector3df& rot = camera->getRotation();
	camera->setRotation(core::vector3df(x,rot.Y,rot.Z));
}

void dbYRotateCamera( u32 id, f32 y )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return;
	const core::vector3df& rot = camera->getRotation();
	camera->setRotation(core::vector3df(rot.X,y,rot.Z));
}

void dbZRotateCamera( u32 id, f32 z )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return;
	const core::vector3df& rot = camera->getRotation();
	camera->setRotation(core::vector3df(rot.X,rot.Y,z));
}

f32 dbCameraAngleX( u32 id )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return 0.0f;
	return camera->getRotation().X;
}

f32 dbCameraAngleY( u32 id )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return 0.0f;
	return camera->getRotation().Y;
}

f32 dbCameraAngleZ( u32 id )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return 0.0f;
	return camera->getRotation().Z;
}

void dbPointCamera( u32 id, f32 x, f32 y, f32 z )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return;
	camera->setTarget(core::vector3df(x,y,z));
}

void dbMoveCamera( u32 id, f32 speed )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return;
	core::vector3df pos = camera->getPosition();
	core::vector3df eye = camera->getTarget();
	core::vector3df mov = (eye-pos).normalize()*speed;
	pos += mov;
	camera->setPosition(pos);
	eye += mov;
	camera->setTarget(eye);
}

void dbMoveCameraUp( u32 id, f32 speed )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return;
	core::vector3df pos = camera->getPosition();
	core::vector3df upv = camera->getUpVector();
	pos += (upv).normalize()*speed;
	camera->setPosition(pos);
}

void dbMoveCameraXZ( u32 id, f32 speed )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return;
	core::vector3df pos = camera->getPosition();
	core::vector3df eye = camera->getTarget();
	pos += (eye-pos).normalize()*speed;
	camera->setPosition(pos);
}


void dbStrafeCamera( u32 id, f32 speed )
{
	scene::ICameraSceneNode* camera = dbGetCamera(id);
	if (!camera) return;
}

///////////////////////////////////////////////////////////////////////////////
// set a perspective frustum with 6 params similar to glFrustum()
// (left, right, bottom, top, near, far)
// Note: this is for row-major notation. OpenGL needs transpose it
///////////////////////////////////////////////////////////////////////////////
//bool setFrustum(float l, float r, float b, float t, float n, float f)
//{
//    matrixProjection.identity();
//    matrixProjection[0]  = 2 * n / (r - l);
//    matrixProjection[2]  = (r + l) / (r - l);
//    matrixProjection[5]  = 2 * n / (t - b);
//    matrixProjection[6]  = (t + b) / (t - b);
//    matrixProjection[10] = -(f + n) / (f - n);
//    matrixProjection[11] = -(2 * f * n) / (f - n);
//    matrixProjection[14] = -1;
//    matrixProjection[15] = 0;
//}
//
///////////////////////////////////////////////////////////////////////////////
// set a orthographic frustum with 6 params similar to glOrtho()
// (left, right, bottom, top, near, far)
// Note: this is for row-major notation. OpenGL needs transpose it
///////////////////////////////////////////////////////////////////////////////
//bool setOrthoFrustum(float l, float r, float b, float t, float n,
//                              float f)
//{
//    matrixProjection.identity();
//    matrixProjection[0]  = 2 / (r - l);
//    matrixProjection[3]  = -(r + l) / (r - l);
//    matrixProjection[5]  = 2 / (t - b);
//    matrixProjection[7]  = -(t + b) / (t - b);
//    matrixProjection[10] = -2 / (f - n);
//    matrixProjection[11] = -(f + n) / (f - n);
//}
//...
//
//// pass projection matrx to OpenGL before draw
//glMatrixMode(GL_PROJECTION);
//glLoadMatrixf(matrixProjection.getTranspose());
//...
//
//bool dbPositionCamera( irr::u32 cam_id, irr::f32 x, irr::f32 y, irr::f32 z)
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("dbSetCameraNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbMoveCamera( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("dbSetCameraNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbMoveCameraUp( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("dbSetCameraNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbMoveCameraX( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("dbSetCameraNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbMoveCameraY( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("dbSetCameraNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbMoveCameraZ( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("dbSetCameraNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbPitchCameraUp( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("dbSetCameraNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbPitchCameraDown( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("pitch camera down()", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbRollCameraLeft( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("roll camera left()", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbRollCameraRight( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("roll camera right()", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbStrafeCameraLeft( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("strafe camera left()", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbStrafeCameraRight( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("strafe camera right()", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbYawCameraLeft( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("yaw camera left()", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbYawCameraRight( irr::u32 cam_id, irr::f32 speed)
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("yaw camera right()", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}




//bool dbSetCurrentCamera( irr::u32 cam_id )
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("dbSetCameraNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//
//bool setActiveCamera( scene::ISceneManager* smgr, scene::ICameraSceneNode* newActive )
//{
//	if (!smgr)
//		return false;
//
//	scene::ICameraSceneNode* active = smgr->getActiveCamera();
//	if (active)
//        active->setInputReceiverEnabled(false);
//
//    if (newActive)
//        newActive->setInputReceiverEnabled(true);
//
//	smgr->setActiveCamera(newActive);
//	return true;
//}

///// others
//f32 getObjectDistance( scene::ICameraSceneNode* camera, scene::ISceneNode* node )
//{
//    return 0.0f;
//}
//
//bool setToFollow( scene::ICameraSceneNode* camera, scene::ISceneNode* node, f32 dXZ, f32 dY )
//{
//    if (!camera)
//        return false;
//
//    /// do something ...
//
//    return true;
//}


//
//bool dbPointCamera( irr::u32 cam_id, irr::f32 x, irr::f32 y, irr::f32 z)
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("dbSetCameraNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//bool dbSetCameraNear( irr::u32 cam_id, irr::f32 nearValue )
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("dbSetCameraNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//bool dbSetCameraFar( irr::u32 cam_id, irr::f32 farValue )
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("dbSetCameraNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//bool dbSetCameraFov( irr::u32 cam_id, irr::f32 fovValue )
//{
//	irr::scene::ICameraSceneNode* camera = dbGetCameraByIndex( cam_id );
//	if (!camera)
//	{
//		irr::os::Printer::log("dbSetCameraNear()::Could not set Near", irr::ELL_ERROR);
//		return false;
//	}
//
//	return true;
//}
//
//bool dbSetCameraFog( irr::u32 cam_id, bool bEnabled, irr::video::E_FOG_TYPE fogType, const irr::video::SColor& fogColor )
//{
//
//    return true;
//}
//
//bool dbSetCameraFogDistance( irr::u32 cam_id, irr::f32 fogNear, irr::f32 fogFar )
//{
//
//}
//
//irr::video::IImage* dbGetCameraImage( irr::u32 cam_id )
//{
//
//}
//

//
//  static core::vector3df getPickVector( scene::ICameraSceneNode* camera, s32 mouse_x, s32 mouse_y );
//  static scene::ISceneNode* pickObject( scene::ICameraSceneNode* camera, s32 mouse_x, s32 mouse_y );
//	core::position2di getScreenPos( scene::ISceneManager* smgr );


} // end namespace irr
