#ifndef __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_OBJECTS_H__
#define __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_OBJECTS_H__

#include <irrlicht.h>

namespace irr
{

// DarkGDK :: Basic3D

///@brief Calculate the normale of 3 vertices and store the normale in these vertices again
void dbNormalize( video::S3DVertex &a, video::S3DVertex &b, video::S3DVertex &c);

///@brief Add Vertex to mesh
void dbAddVertex( u32 meshID, const video::S3DVertex &v );

///@brief Add Triangle to mesh
void dbAddVertexTriangle( u32 meshID, const video::S3DVertex &v );

// DarkGDK :: Meshes

///@brief
u32 dbFreeMesh();

// DarkGDK :: Objects

///@brief Returns 'true' if the Object exists, otherwise 'false'
bool dbObjectExist( u32 objID );

///@brief Returns a valid (>0), unused (free) ObjectID
u32 dbFreeObject();

///@brief Delete the camera given by its ID
bool dbDeleteObject(u32 objID);

///@brief Get number of managed 3d objects ( IAnimatedMeshSceneNode / CAutoMeshSceneNode )
u32 dbGetObjectCount();

///@brief Return internal array-index for ObjectID
u32 dbGetObjectArrayIndex(u32 objID);

///@brief Get Pointer to Object
scene::IMeshSceneNode* dbGetObject( u32 objID );

///@brief Load an (animated) object from a file
void dbLoadObject( u32 objID, const io::path& filename );

///@brief Load an (animated) object from a file
void dbLoadObjectPK3( u32 objID, const io::path& pk3_name, const io::path& bsp_name );

///@brief dbObjectSize / dbGetObjectSize
core::vector3df dbGetObjectSize( u32 objID );

///@brief
f32 dbGetObjectSizeX( u32 objID );

///@brief
f32 dbGetObjectSizeY( u32 objID );

///@brief
f32 dbGetObjectSizeZ( u32 objID );

///@brief
core::vector3df dbObjectSize( u32 objID );

///@brief
f32 dbObjectSizeX( u32 objID );

///@brief
f32 dbObjectSizeY( u32 objID );

///@brief
f32 dbObjectSizeZ( u32 objID );

///@brief
void dbPositionObject( u32 objID, f32 x, f32 y, f32 z);

///@brief
void dbRotateObject( u32 objID, f32 x, f32 y, f32 z);

///@brief
void dbPointObject( u32 objID, f32 x, f32 y, f32 z);

///@brief
void dbScaleObject( u32 objID, f32 x, f32 y, f32 z);

///@brief
void dbCenterObject(u32 objID, const core::vector3df& centerTo);

///@brief
void dbSetObjectVisible( u32 objID, bool bVisible);

///@brief
void dbSetObject( u32 objID, bool bWireframe, bool bTransparent,	bool bBackfaceCull, bool bLighting,	s32 iTexFilter,	bool bFog, bool bAmbient, bool bFrontfaceCull);

///@brief
void dbSetObjectWireframe( u32 objID, bool bWireframe);

///@brief
void dbSetObjectTransparent( u32 objID, bool bTransparent);

///@brief
void dbSetObjectBackCull( u32 objID, bool bBackfaceCulling);

///@brief
void dbSetObjectFrontCull( u32 objID, bool bFrontfaceCulling);

///@brief
void dbSetObjectLight( u32 objID, bool bLight );

///@brief
void dbSetObjectFilter( u32 objID, s32 iTexFilter);

///@brief
void dbSetObjectFog( u32 objID, bool bFog);

///@brief
void dbSetObjectAmbient( u32 objID, bool bAmbient);

void dbTextureObject( u32 objID, u32 texID, u32 texStage = 0);

void dbSetObjectTexture( u32 objID, s32 iTexRepeatMode);

//scene::IMesh* dbMakeMesh(	scene::IMeshBuffer* pMeshBuffer)

//scene::IMeshSceneNode* dbMakeObject(
//	scene::ISceneManager* pManager,
//	scene::ISceneNode* pParent,
//	s32 id,
//	scene::IMesh* pMesh);

void dbMakeDefaultImage( u32 objID, u32 wh );

void dbMakeObjectFromMesh( u32 objID, scene::IMesh* mesh, bool dropMesh = true );

///@brief dbMakeObjectBox()
void dbMakeObjectBox( u32 objID, f32 a, f32 b, f32 c);

///@brief dbMakeObjectTriangle()
void dbMakeObjectTriangle( u32 objID, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, f32 x3, f32 y3, f32 z3, const video::SColor& color = 0xffffffff, bool XZPlane = true );

///@brief dbMakeObjectPlain()
void dbMakeObjectPlain( u32 objID, f32 w, f32 h, const video::SColor& color = 0xffffffff, bool XZPlane = true );

///@brief dbMakeObjectHexagon()
void dbMakeObjectHexagon( u32 objID, f32 d, const video::SColor& color, bool XZPlane = true );

void dbMakeObjectDisc( u32 objID, f32 radius, u32 segments);

void dbMakeObjectSphere( u32 objID, f32 radius, u32 segments);

u32 dbMakeObjectCylinder( u32 id, f32 radius, u32 segments);

u32 dbMakeObjectCube( u32 id, f32 size);

u32 dbMakeObjectCone( u32 id, f32 size);

u32 dbMakeObjectTorus( u32 id, f32 size);

u32 dbMakeObjectTeapot( u32 id, f32 size);

u32 dbMakeObjectBunny( u32 id, f32 size);


} // end namespace irr

#endif // __DARKGDK_DARK_GAME_DEVELOPMENT_KIT_H__
