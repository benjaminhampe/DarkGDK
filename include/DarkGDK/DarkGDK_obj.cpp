#include "DarkGDK_obj.h"

#include "DarkGDK_struct.h"
#include "DarkGDK_math.h"
#include "DarkGDK_img.h"

#include <geometry.h>
#include <imageTool.h>
namespace irr
{

// DarkGDK :: Basic3D

///@brief Calculate the normale of 3 vertices and store the normale in these vertices again
void dbNormalize( video::S3DVertex &a, video::S3DVertex &b, video::S3DVertex &c)
{
	b.Normal.X = b.Pos.X-a.Pos.X; b.Normal.Y = b.Pos.Y-a.Pos.Y; b.Normal.Z = b.Pos.Z-a.Pos.Z;
	c.Normal.X = c.Pos.X-a.Pos.X; c.Normal.Y = c.Pos.Y-a.Pos.Y; c.Normal.Z = c.Pos.Z-a.Pos.Z;
	a.Normal.X = b.Normal.Y*c.Normal.Z - b.Normal.Z*c.Normal.Y;
	a.Normal.Y = b.Normal.Z*c.Normal.X - b.Normal.X*c.Normal.Z;
	a.Normal.Z = b.Normal.X*c.Normal.Y - b.Normal.Y*c.Normal.X;
	float r = 1.0f/sqrt(a.Normal.X*a.Normal.X + a.Normal.Y*a.Normal.Y + a.Normal.Z*a.Normal.Z);
	a.Normal.X*=r; a.Normal.Y*=r; a.Normal.Z*=r;
	b.Normal.X*=r; b.Normal.Y*=r; b.Normal.Z*=r;
	c.Normal.X*=r; c.Normal.Y*=r; c.Normal.Z*=r;
}

///@brief Add Vertex to mesh
void dbAddVertex( u32 meshID, const video::S3DVertex &v )
{

}

///@brief Add Triangle to mesh
void dbAddVertexTriangle( u32 meshID, const video::S3DVertex &v )
{

}

/// DarkGDK :: Meshes

u32 dbFreeMesh()
{
	return 0;
}

/// DarkGDK :: Objects

///@brief Get number of managed 3d objects ( IAnimatedMeshSceneNode / CAutoMeshSceneNode )
u32 dbGetObjectCount()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	return app.Objects.size();
}


///@brief Get Pointer to Object
scene::IMeshSceneNode* dbGetObject( u32 objID )
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	if (objID == 0)
		return 0;

	u32 count = app.Objects.size();

	bool found = false;

	u32 i = 0;
	while (!found && i<count)
	{
		if (app.Objects[i].ID == objID)
			found = true;
		else
			i++;
	}

	if (found)
		return app.Objects[i].Node;
	else
		return 0;
}


///@brief Return internal array-index for ObjectID
u32 dbGetObjectArrayIndex(u32 objID)
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	const u32 count = app.Objects.size();

	if (objID == 0)
		return count;

	bool found = false;
	u32 i = 0;
	while (!found && i<count)
	{
		if (app.Objects[i].ID == objID)
			found = true;
		else
			i++;
	}

	if (found)
		return i;
	else
		return count;
}

///@brief Returns 'true' if the Object exists, otherwise 'false'
bool dbObjectExist( u32 objID )
{
	if ( dbGetObject( objID ) )
		return true;
	else
		return false;
}

///@brief Returns a valid (>0), unused (free) ObjectID
u32 dbFreeObject()
{
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	return app.Objects.size()+1;
}

///@brief Delete the camera given by its ID
bool dbDeleteObject(u32 objID)
{
	if (!dbObjectExist(objID))
	{
		#ifdef _DEBUG
		dbERROR( "dbDeleteCamera() :: Could not find camera with ID %d\n", camID);
		#endif // _DEBUG
		return false;
	}

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	const u32 count = app.Objects.size();
	const u32 index = dbGetObjectArrayIndex(objID);

	/// penibel check
	if ( index >= count )
	{
		#ifdef _DEBUG
		dbERROR( "dbDeleteCamera() :: Could not find camera with ID %d\n", camID);
		#endif // _DEBUG
		return false;
	}

	/// get pointer and call its remove() function
	scene::ISceneNode* node = app.Objects[index].Node;
	if (node)
	{
		node->remove();
	}

	/// delete SCamera element from array
	app.Objects.erase(index);

	/// return status
	if (count != app.Objects.size())
		return true;
	else
		return false;
}

///@brief Load an (animated) object from a file
void dbLoadObject( u32 objID, const io::path& filename )
{
	if (dbObjectExist(objID))
	{
		dbERROR("dbLoadObject() :: There already is an object with id = %d, abort function.\n", objID);
		return;
	}

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	if (!app.Device)
		return;

	scene::ISceneManager* smgr = app.Device->getSceneManager();
	if (!smgr)
		return;

	scene::IMesh* mesh = smgr->getMesh( filename );
	if (!mesh)
	{
		dbERROR("dbLoadObject() :: Could not load model-file %s.\n", core::stringc( filename ).c_str() );
		return;
	}

	scene::CAutoMeshSceneNode* node = new scene::CAutoMeshSceneNode(
		mesh, smgr, smgr->getRootSceneNode(), -1, scene::EPT_TRIANGLES);

	mesh->drop();

	DarkGDK_SObject obj;
	obj.ID = objID;
	obj.Node = node;

	app.Objects.push_back( obj );
}



///@brief Load an (animated) object from a file
void dbLoadObjectPK3( u32 objID, const io::path& pk3_name, const io::path& bsp_name )
{
	if (dbObjectExist(objID))
	{
		dbERROR("dbLoadObjectPK3() :: There already is an object with id = %d, abort function.\n", objID);
		return;
	}

	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();

	if (!app.Device)
		return;

	scene::ISceneManager* smgr = app.Device->getSceneManager();
	io::IFileSystem* fileSys = app.Device->getFileSystem();

	fileSys->addFileArchive( pk3_name );
	scene::IAnimatedMesh* mesh = smgr->getMesh( bsp_name );

	scene::ISceneNode* node = 0;
	if (mesh)
	{
		node = smgr->addOctreeSceneNode( mesh->getMesh(0), 0, -1, 1024);
		// node = smgr->addMeshSceneNode(mesh->getMesh(0));
	}

	if (node)
	{
		node->setPosition(core::vector3df(-1300,-144,-1249));
	}

	if (mesh)
	{
		mesh->drop();
	}

	if (node)
	{
		DarkGDK_SObject obj;
		obj.ID = objID;
		obj.Node = reinterpret_cast<scene::CAutoMeshSceneNode*>(node);

		app.Objects.push_back( obj );
		dbERROR("dbLoadObjectPK3() :: Created object with ID = %d.\n", objID);
	}
	else
	{
		dbERROR("dbLoadObjectPK3() :: Could not create object with ID = %d.\n", objID);
	}
}


/// /////////////////////////////////////////////////////////////////

/// dbObjectSize / dbGetObjectSize

/// /////////////////////////////////////////////////////////////////

core::vector3df dbObjectSize( u32 objID )
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
	{
		dbERROR( "dbObjectSize( u32 objID = %d ) :: Invalid SceneNode Pointer.\n", objID );
		return core::vector3df(0,0,0);
	}

	return node->getBoundingBox().getExtent();
}

f32 dbObjectSizeX( u32 objID )
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
	{
		dbERROR( "dbObjectSizeX( u32 objID = %d ) :: Invalid SceneNode Pointer.\n", objID );
		return 0.f;
	}

	return node->getBoundingBox().getExtent().X;
}

f32 dbObjectSizeY( u32 objID )
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
	{
		dbERROR( "dbObjectSizeY( u32 objID = %d ) :: Invalid SceneNode Pointer.\n", objID );
		return 0.f;
	}

	return node->getBoundingBox().getExtent().Y;
}

f32 dbObjectSizeZ( u32 objID )
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
	{
		dbERROR( "dbObjectSizeZ( u32 objID = %d ) :: Invalid SceneNode Pointer.\n", objID );
		return 0.f;
	}

	return node->getBoundingBox().getExtent().Z;
}


core::vector3df dbGetObjectSize( u32 objID )
{
	return dbObjectSize( objID );
}

f32 dbGetObjectSizeX( u32 objID )
{
	return dbObjectSizeX( objID );
}

f32 dbGetObjectSizeY( u32 objID )
{
	return dbObjectSizeY( objID );
}

f32 dbGetObjectSizeZ( u32 objID )
{
	return dbObjectSizeZ( objID );
}

/// /////////////////////////////////////////////////////////////////

/// dbPositionObject

/// /////////////////////////////////////////////////////////////////

void dbPositionObject( u32 objID, f32 x, f32 y, f32 z)
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
		return;

	node->setPosition( core::vector3df(x,y,z) );
}

void dbRotateObject( u32 objID, f32 x, f32 y, f32 z)
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
		return;

	node->setRotation( core::vector3df(x,y,z) );
}


void dbPointObject( u32 objID, f32 x, f32 y, f32 z)
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
		return;

	const core::vector3df targetToRot( core::vector3df(x,y,z) - node->getAbsolutePosition());
	const core::vector3df searchedRot = targetToRot.getHorizontalAngle();
	node->setRotation( searchedRot );
}

void dbScaleObject( u32 objID, f32 x, f32 y, f32 z)
{
	scene::IMeshSceneNode* node = dbGetObject( objID );
	if (!node)
		return;

	node->setScale( core::vector3df(x,y,z) );
}

void dbCenterObject(u32 objID, const core::vector3df& centerTo)
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
		return;
}

//	void dbSetObjectVisible( u32 id, bool bVisible);
//	void dbSetObjectWireframe( u32 id, bool bWireframe);
//	void dbSetObjectTransparent( u32 id, bool bTransparent);
//	void dbSetObjectBackCull( u32 id, bool bBackfaceCulling);
//	void dbSetObjectLighting( scene::ISceneNode* pNode, bool bLighting);
//	void dbSetObjectFilter( u32 id, s32 iTexFilter);
//	void dbSetObjectFog( scene::ISceneNode* pNode, bool bFog);
//	void dbSetObjectAmbient( u32 id, bool bAmbient);
//	void dbSetObjectFrontCull( u32 id, bool bFrontfaceCulling);


// void dbSetObjectTexture( scene::ISceneNode* pNode, s32 iTexRepeatMode);
void dbTextureObject( u32 objID, u32 texID, u32 texStage)
{
	dbERROR("dbTextureObject()\n");

	scene::ISceneNode* node = dbGetObject( objID );

	/// error
	if (!node)
	{
		dbERROR( "Could not get object with id %d\n", objID );
		return;
	}

	video::ITexture* tex = dbGetTexture( texID );

	/// error
	if (!tex)
	{
		dbERROR( "Could not get image with id %d\n", texID );
		return;
	}

	node->setMaterialTexture( texStage, tex );
	return;
}


void dbSetObjectTexture( u32 objID, s32 iTexRepeatMode)
{

}

void dbSetObjectVisible( u32 objID, bool bVisible)
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
		return;

	node->setVisible( bVisible );
}

void dbSetObjectWireframe( u32 objID, bool bWireframe)
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
		return;

	node->setMaterialFlag( video::EMF_WIREFRAME, bWireframe );
}

void dbSetObjectTransparent( u32 objID, bool bTransparent)
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
		return;

	// node->setMaterialFlag( video::EMF_WIREFRAME, bWireframe );
}

void dbSetObjectBackCull( u32 objID, bool bBackfaceCulling)
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
		return;

	node->setMaterialFlag( video::EMF_BACK_FACE_CULLING, bBackfaceCulling );
}

void dbSetObjectFrontCull( u32 objID, bool bFrontfaceCulling)
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
		return;

	node->setMaterialFlag( video::EMF_FRONT_FACE_CULLING, bFrontfaceCulling );
}

void dbSetObjectLight( u32 objID, bool bLight )
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
		return;

	node->setMaterialFlag( video::EMF_LIGHTING, bLight );
}

void dbSetObjectFilter( u32 objID, s32 iTexFilter)
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
		return;

	node->setMaterialFlag( video::EMF_BILINEAR_FILTER, (iTexFilter > 0) );
	node->setMaterialFlag( video::EMF_TRILINEAR_FILTER, (iTexFilter > 1) );
	node->setMaterialFlag( video::EMF_ANISOTROPIC_FILTER, (iTexFilter > 2) );
}

void dbSetObjectFog( u32 objID, bool bFog)
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
		return;

	node->setMaterialFlag( video::EMF_FOG_ENABLE, bFog );
}

void dbSetObjectAmbient( u32 objID, bool bAmbient)
{
	scene::ISceneNode* node = dbGetObject( objID );
	if (!node)
		return;

	// node->setMaterialFlag( EMF_LIGHTING, bLight );
}

void dbSetObject( u32 objID, bool bWireframe, bool bTransparent, bool bBackfaceCull, bool bLighting, s32 iTexFilter, bool bFog, bool bAmbient, bool bFrontfaceCull)
{

//	for (u32 c=0; c<pNode->getMaterialCount(); c++)
//	{
//		pNode->getMaterial(c).AmbientColor.setAlpha(bAmbient?255:0);
//		pNode->getMaterial(c).AntiAliasing = video::EAAM_OFF;
//		pNode->getMaterial(c).AntiAliasing = video::EAAM_SIMPLE;
//		pNode->getMaterial(c).AntiAliasing = video::EAAM_FULL_BASIC;
//		pNode->getMaterial(c).AntiAliasing = video::EAAM_QUALITY;
//		pNode->getMaterial(c).AntiAliasing = video::EAAM_POINT_SMOOTH;
//		pNode->getMaterial(c).AntiAliasing = video::EAAM_LINE_SMOOTH;
//		pNode->getMaterial(c).AntiAliasing = video::EAAM_ALPHA_TO_COVERAGE;
//		pNode->getMaterial(c).BackfaceCulling = bBackfaceCull;
//		pNode->getMaterial(c).ColorMask = video::ECP_ALL;
//		pNode->getMaterial(c).ColorMaterial = video::ECM_NONE;
//		pNode->getMaterial(c).ColorMaterial = video::ECM_DIFFUSE;
//		pNode->getMaterial(c).ColorMaterial = video::ECM_AMBIENT;
//		pNode->getMaterial(c).ColorMaterial = video::ECM_DIFFUSE_AND_AMBIENT;
//		pNode->getMaterial(c).ColorMaterial = video::ECM_EMISSIVE;
//		pNode->getMaterial(c).ColorMaterial = video::ECM_SPECULAR;
//		pNode->getMaterial(c).DiffuseColor.set(255,255,255,255);
//		pNode->getMaterial(c).EmissiveColor.set(255,255,255,255);
//		pNode->getMaterial(c).FogEnable = bFog;
//		pNode->getMaterial(c).FrontfaceCulling = bFrontfaceCull;
//		pNode->getMaterial(c).GouraudShading = false;
//		pNode->getMaterial(c).Lighting = bLighting;
//		pNode->getMaterial(c).MaterialType = video::EMT_DETAIL_MAP;
//		pNode->getMaterial(c).MaterialType = video::EMT_FORCE_32BIT;
//		pNode->getMaterial(c).MaterialType = video::EMT_LIGHTMAP;
//		pNode->getMaterial(c).MaterialType = video::EMT_LIGHTMAP_ADD;
//		pNode->getMaterial(c).MaterialType = video::EMT_LIGHTMAP_LIGHTING;
//		pNode->getMaterial(c).MaterialType = video::EMT_LIGHTMAP_LIGHTING_M2;
//		pNode->getMaterial(c).MaterialType = video::EMT_LIGHTMAP_LIGHTING_M4;
//		pNode->getMaterial(c).MaterialType = video::EMT_LIGHTMAP_M2;
//		pNode->getMaterial(c).MaterialType = video::EMT_LIGHTMAP_M4;
//		pNode->getMaterial(c).MaterialType = video::EMT_NORMAL_MAP_SOLID;
//		pNode->getMaterial(c).MaterialType = video::EMT_NORMAL_MAP_TRANSPARENT_ADD_COLOR;
//		pNode->getMaterial(c).MaterialType = video::EMT_NORMAL_MAP_TRANSPARENT_VERTEX_ALPHA;
//		pNode->getMaterial(c).MaterialType = video::EMT_ONETEXTURE_BLEND;
//		pNode->getMaterial(c).MaterialType = video::EMT_PARALLAX_MAP_SOLID;
//		pNode->getMaterial(c).MaterialType = video::EMT_PARALLAX_MAP_TRANSPARENT_ADD_COLOR;
//		pNode->getMaterial(c).MaterialType = video::EMT_PARALLAX_MAP_TRANSPARENT_VERTEX_ALPHA;
//		pNode->getMaterial(c).MaterialType = video::EMT_REFLECTION_2_LAYER;
//		pNode->getMaterial(c).MaterialType = video::EMT_SOLID;
//		pNode->getMaterial(c).MaterialType = video::EMT_SOLID_2_LAYER;
//		pNode->getMaterial(c).MaterialType = video::EMT_SPHERE_MAP;
//		pNode->getMaterial(c).MaterialType = video::EMT_TRANSPARENT_ADD_COLOR;
//		pNode->getMaterial(c).MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
//		pNode->getMaterial(c).MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL_REF;
//		pNode->getMaterial(c).MaterialType = video::EMT_TRANSPARENT_REFLECTION_2_LAYER;
//		pNode->getMaterial(c).MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
//		pNode->getMaterial(c).MaterialTypeParam = 0;
//		pNode->getMaterial(c).MaterialTypeParam2 = 0;
//		pNode->getMaterial(c).NormalizeNormals=true;
//		pNode->getMaterial(c).PointCloud=false;
//		pNode->getMaterial(c).Shininess=20.0f; // range [0.5;128]
//		pNode->getMaterial(c).SpecularColor.set(255,255,255,255);
//		pNode->getMaterial(c).Thickness=1.0f;
//		pNode->getMaterial(c).TextureLayer[0].AnisotropicFilter = 0xFF; // default 0
//		pNode->getMaterial(c).TextureLayer[0].BilinearFilter = true;
//		pNode->getMaterial(c).TextureLayer[0].LODBias = 0; //! Bias for the mipmap choosing decision.
////		pNode->getMaterial(c).TextureLayer[0].Texture.getSize();
////		pNode->getMaterial(c).TextureLayer[0].Texture.getOriginalSize();
////		pNode->getMaterial(c).TextureLayer[0].Texture.getColorFormat();
////		pNode->getMaterial(c).TextureLayer[0].Texture.getName();
////		pNode->getMaterial(c).TextureLayer[0].Texture.hasAlpha();
////		pNode->getMaterial(c).TextureLayer[0].Texture.hasMipMaps();
////		pNode->getMaterial(c).TextureLayer[0].Texture.isRenderTarget();
////		pNode->getMaterial(c).TextureLayer[0].getTextureMatrix();
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapU = video::ETC_CLAMP;
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapU = video::ETC_CLAMP_TO_BORDER;
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapU = video::ETC_CLAMP_TO_EDGE;
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapU = video::ETC_MIRROR;
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapU = video::ETC_MIRROR_CLAMP;
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapU = video::ETC_MIRROR_CLAMP_TO_BORDER;
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapU = video::ETC_MIRROR_CLAMP_TO_EDGE;
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapU = video::ETC_REPEAT;
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapV = video::ETC_CLAMP;
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapV = video::ETC_CLAMP_TO_BORDER;
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapV = video::ETC_CLAMP_TO_EDGE;
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapV = video::ETC_MIRROR;
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapV = video::ETC_MIRROR_CLAMP;
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapV = video::ETC_MIRROR_CLAMP_TO_BORDER;
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapV = video::ETC_MIRROR_CLAMP_TO_EDGE;
//		pNode->getMaterial(c).TextureLayer[0].TextureWrapV = video::ETC_REPEAT;
//		pNode->getMaterial(c).TextureLayer[0].TrilinearFilter = true;
//		pNode->getMaterial(c).Wireframe = bWireframe;
//		pNode->getMaterial(c).ZBuffer = true;
//		pNode->getMaterial(c).ZWriteEnable = !bTransparent;
}

//scene::IMesh* dbMakeMesh(	scene::IMeshBuffer* pMeshBuffer)
//{
//	if (!pMeshBuffer) return 0;
//
//	video::E_VERTEX_TYPE vtype = lMeshBuffer->getVertexType();
//
//	switch (vtype)
//	{
//		case video::EVT_STANDARD:
//		{
//			return (scene::IMesh*)new scene::SMesh();
//
//		} break;
//
//		case video::EVT_2TCOORDS:
//		{
//			return (scene::IMesh*)new scene::CMesh<video::S3DVertex2TCoords>();
//
//		} break;
//
//		case video::EVT_TANGENTS:
//		{
//			return (scene::IMesh*)new scene::CMesh<video::S3DVertexTangents>();
//		} break;
//
//		default:
//			break;
//	}
//	return 0;
//
//	scene::SMesh* pMesh = new scene::SMesh();
//	if (!pMesh) return 0;
//
//	pMesh->addMeshBuffer(pMeshBuffer);
//
//	return (scene::IMesh*)pMesh;
//}

//scene::IMeshSceneNode* dbMakeObject(
//	scene::ISceneManager* pManager,
//	scene::ISceneNode* pParent,
//	s32 id,
//	scene::IMesh* pMesh)
//{
//	if (!pManager) return 0;
//	if (!pMesh) return 0;
//
//	scene::IMeshSceneNode* pNode = pManager->addMeshSceneNode(pMesh, (pParent)?pParent:pManager->getRootSceneNode(), -1);
//
//	return pNode;
//}
void dbMakeDefaultImage( u32 objID, u32 wh )
{

}

void dbMakeObjectFromMesh( u32 objID, scene::IMesh* mesh, bool dropMesh )
{
	/// check pointer
	if (!mesh)
		return;

	/// get instance
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return;

	/// get pointer
	//video::IVideoDriver* driver = app.Device->getVideoDriver();
	scene::ISceneManager* smgr = app.Device->getSceneManager();

	/// create scenenode
	scene::IMeshSceneNode* node = smgr->addMeshSceneNode( mesh, smgr->getRootSceneNode(), -1 );
	if (node)
	{
		node->setMaterialType( video::EMT_SOLID );
		node->setMaterialFlag( video::EMF_WIREFRAME, false );
		node->setMaterialFlag( video::EMF_LIGHTING, false );
		node->setMaterialFlag( video::EMF_FOG_ENABLE, false );

		DarkGDK_SObject obj;
		obj.ID = objID;
		obj.Node = node;
		app.Objects.push_back( obj );
	}

	if (dropMesh)
	{
		mesh->drop();
	}
}

///@brief dbMakeObjectBox()
/**
*
*	@param objID Unique object-id
*	@param a X-width Dimension
*	@param b Y-height Dimension
*	@param c Z-depth Dimension
*
*/
void dbMakeObjectBox( u32 objID, f32 a, f32 b, f32 c)
{
	/// check id
	if (dbObjectExist(objID))
	{
		dbERROR("dbMakeObjectBox() :: Could not make object because id %d already exist.\n", objID );
		return;
	}

	/// get instance
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return;

	/// get pointer
	const scene::IGeometryCreator* geom = app.Device->getSceneManager()->getGeometryCreator();

	/// create mesh
	scene::IMesh* mesh = geom->createCubeMesh( core::vector3df(a,b,c) );

	/// add mesh to internal manager
	dbMakeObjectFromMesh( objID, mesh);
}


///@brief dbMakeObjectTriangle()
/**
*
*	@param objID Unique object-id
*	@param a X-width Dimension
*	@param b Y-height Dimension
*	@param c Z-depth Dimension
*
*/
void dbMakeObjectTriangle( u32 objID, f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, f32 x3, f32 y3, f32 z3, const video::SColor& color, bool XZPlane )
{
	/// check id
	if (dbObjectExist(objID))
	{
		dbERROR("dbMakeObjectHexagon() :: Could not make object because id %d already exist.\n", objID );
		return;
	}

	/// get instance
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return;

	/// create mesh
	scene::SMesh* mesh = new scene::SMesh();
	if (!mesh)
		return;

	/// create meshbuffer
	scene::SMeshBuffer* buffer = new scene::SMeshBuffer();
	if (buffer)
	{
		// material
		if (color.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		// vertices
		buffer->Vertices.reallocate(3);
		buffer->Vertices.set_used(0);
		video::S3DVertex A( x1, y1, z1, 0,0,-1, color, 0,   0.75f);
		video::S3DVertex B( x2, y2, z2, 0,0,-1, color, 0,   0.25f);
		video::S3DVertex C( x3, y3, z3, 0,0,-1, color, 0.5f,0    );
		buffer->Vertices.push_back( A );
		buffer->Vertices.push_back( B );
		buffer->Vertices.push_back( C );


		// indices
		buffer->Indices.reallocate(3);
		buffer->Indices.set_used(0);
		buffer->Indices.push_back( 0 );
		buffer->Indices.push_back( 1 );
		buffer->Indices.push_back( 2 ); // ABD

		buffer->recalculateBoundingBox();
		mesh->addMeshBuffer(buffer);
		mesh->BoundingBox = buffer->getBoundingBox();
		buffer->drop();
	}

	mesh->setHardwareMappingHint(scene::EHM_STATIC);

	/// add mesh to internal manager
	dbMakeObjectFromMesh( objID, mesh);
}




///@brief dbMakeObjectPlain()
/**
*
*	@param objID Unique object-id
*	@param a X-width Dimension
*	@param b Y-height Dimension
*	@param c Z-depth Dimension
*
*/
void dbMakeObjectPlain( u32 objID, f32 w, f32 h, const video::SColor& color, bool XZPlane )
{
	/// check id
	if (dbObjectExist(objID))
	{
		dbERROR("dbMakeObjectHexagon() :: Could not make object because id %d already exist.\n", objID );
		return;
	}

	/// get instance
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return;

	/// create mesh
	scene::SMesh* mesh = new scene::SMesh();
	if (!mesh)
		return;

	/// create meshbuffer
	scene::SMeshBuffer* buffer = new scene::SMeshBuffer();
	if (buffer)
	{
		// material
		if (color.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		// vertices
		buffer->Vertices.reallocate(4);
		buffer->Vertices.set_used(0);
		if (XZPlane)
		{
		buffer->Vertices.push_back( video::S3DVertex( -0.5f*w, 0.0f,-0.5f*h, 0,1,0, color, 0, 1) );
		buffer->Vertices.push_back( video::S3DVertex( -0.5f*w, 0.0f, 0.5f*h, 0,1,0, color, 0, 0) );
		buffer->Vertices.push_back( video::S3DVertex(  0.5f*w, 0.0f, 0.5f*h, 0,1,0, color, 1, 0) );
		buffer->Vertices.push_back( video::S3DVertex(  0.5f*w, 0.0f,-0.5f*h, 0,1,0, color, 1, 1) );
		}
		else
		{
		buffer->Vertices.push_back( video::S3DVertex( -0.5f*w,-0.5f*h, 0.0f, 0,0,-1, color, 0, 1) );
		buffer->Vertices.push_back( video::S3DVertex( -0.5f*w, 0.5f*h, 0.0f, 0,0,-1, color, 0, 0) );
		buffer->Vertices.push_back( video::S3DVertex(  0.5f*w, 0.5f*h, 0.0f, 0,0,-1, color, 1, 0) );
		buffer->Vertices.push_back( video::S3DVertex(  0.5f*w,-0.5f*h, 0.0f, 0,0,-1, color, 1, 1) );
		}
		// indices
		buffer->Indices.reallocate(6);
		buffer->Indices.set_used(0);
		buffer->Indices.push_back( 0 );
		buffer->Indices.push_back( 1 );
		buffer->Indices.push_back( 2 ); // ABC
		buffer->Indices.push_back( 0 );
		buffer->Indices.push_back( 2 );
		buffer->Indices.push_back( 3 ); // ACD

		buffer->recalculateBoundingBox();
		// add to mesh
		mesh->addMeshBuffer(buffer);
		mesh->BoundingBox = buffer->getBoundingBox();
		buffer->drop();
	}

	mesh->setHardwareMappingHint(scene::EHM_STATIC);

	/// add mesh to internal manager
	dbMakeObjectFromMesh( objID, mesh);
}

///@brief dbMakeObjectHexagon()
/**
*
*	@param objID Unique object-id
*	@param a X-width Dimension
*	@param b Y-height Dimension
*	@param c Z-depth Dimension
*
*/
void dbMakeObjectHexagon( u32 objID, f32 d, const video::SColor& color, bool XZPlane )
{
	/// check id
	if (dbObjectExist(objID))
	{
		dbERROR("dbMakeObjectHexagon() :: Could not make object because id %d already exist.\n", objID );
		return;
	}

	/// get instance
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return;

	/// create mesh
	scene::SMesh* mesh = new scene::SMesh();
	if (!mesh)
		return;

	/// create meshbuffer
	scene::SMeshBuffer* buffer = new scene::SMeshBuffer();
	if (buffer)
	{
		// bbox
		if (XZPlane)
			buffer->setBoundingBox( core::aabbox3df( -.5f*d, 0.f, -.5f*d, .5f*d, 0.f, .5f*d ) );
		else
			buffer->setBoundingBox( core::aabbox3df( -.5f*d,-.5f*d, 0.f, .5f*d, .5f*d, 0.f ) );

		// material
		if (color.getAlpha()<255)
			buffer->Material.MaterialType = video::EMT_TRANSPARENT_VERTEX_ALPHA;
		else
			buffer->Material.MaterialType = video::EMT_SOLID;

		// vertices
		buffer->Vertices.reallocate(6);
		buffer->Vertices.set_used(0);
		if (XZPlane)
		{
		buffer->Vertices.push_back( video::S3DVertex( -0.5f*d, 0, -0.25f*d, 0,0,-1, color, 0,   0.75f) );
		buffer->Vertices.push_back( video::S3DVertex( -0.5f*d, 0,  0.25f*d, 0,0,-1, color, 0,   0.25f) );
		buffer->Vertices.push_back( video::S3DVertex(  0, 0, 0.5f *d, 0,0,-1, color, 0.5f,0    ) );
		buffer->Vertices.push_back( video::S3DVertex(  0.5f*d, 0,  0.25f*d, 0,0,-1, color, 1.0f,0.25f) );
		buffer->Vertices.push_back( video::S3DVertex(  0.5f*d, 0, -0.25f*d, 0,0,-1, color, 1.0f,0.75f) );
		buffer->Vertices.push_back( video::S3DVertex(  0, 0, -0.5f *d, 0,0,-1, color, 0.5f,1    ) );
		}
		else
		{
		buffer->Vertices.push_back( video::S3DVertex( -0.5f*d, -0.25f*d, 0, 0,0,-1, color, 0,   0.75f) );
		buffer->Vertices.push_back( video::S3DVertex( -0.5f*d,  0.25f*d, 0, 0,0,-1, color, 0,   0.25f) );
		buffer->Vertices.push_back( video::S3DVertex(  0, 0.5f *d, 0, 0,0,-1, color, 0.5f,0    ) );
		buffer->Vertices.push_back( video::S3DVertex(  0.5f*d,  0.25f*d, 0, 0,0,-1, color, 1.0f,0.25f) );
		buffer->Vertices.push_back( video::S3DVertex(  0.5f*d, -0.25f*d, 0, 0,0,-1, color, 1.0f,0.75f) );
		buffer->Vertices.push_back( video::S3DVertex(  0, -0.5f *d, 0, 0,0,-1, color, 0.5f,1    ) );
		}
		// indices
		buffer->Indices.reallocate(12);
		buffer->Indices.set_used(0);
		buffer->Indices.push_back( 0 );
		buffer->Indices.push_back( 1 );
		buffer->Indices.push_back( 3 ); // ABD
		buffer->Indices.push_back( 0 );
		buffer->Indices.push_back( 3 );
		buffer->Indices.push_back( 4 ); // ADE
		buffer->Indices.push_back( 1 );
		buffer->Indices.push_back( 2 );
		buffer->Indices.push_back( 3 ); // BCD
		buffer->Indices.push_back( 0 );
		buffer->Indices.push_back( 4 );
		buffer->Indices.push_back( 5 ); // AEF

		// add to mesh
		mesh->addMeshBuffer(buffer);
		mesh->BoundingBox = buffer->getBoundingBox();
		buffer->drop();
	}

	mesh->setHardwareMappingHint( scene::EHM_STATIC);

	/// add mesh to internal manager
	dbMakeObjectFromMesh( objID, mesh);
}

void dbMakeObjectDisc( u32 objID, f32 radius, u32 segments)
{
/// check id
	if (dbObjectExist(objID))
	{
		dbERROR("dbMakeObjectHexagon() :: Could not make object because id %d already exist.\n", objID );
		return;
	}

	/// get instance
	DarkGDK_SGlobalStruct& app = DarkGDK_SGlobalStruct::getInstance();
	if (!app.Device)
		return;

	/// create mesh
	scene::SMesh* mesh = new scene::SMesh();
	if (!mesh)
		return;

	// allocate memory for meshbuffer struct
	scene::SMeshBuffer* buffer = new scene::SMeshBuffer();
	if(!buffer)
		return;


	// create sin/cos table
	if (segments<3) segments=3;
	if (segments>1000) segments=1000;
	dbSinCosTablef scTable(segments);

	// allocate memory for vertices and indices
	buffer->Vertices.reallocate(segments+1);
	buffer->Indices.reallocate(3*segments);

	// general settings
	buffer->BoundingBox.reset(core::vector3df(0,0,0));
	buffer->Material.MaterialType = video::EMT_SOLID;
	buffer->Material.Lighting = false;
	buffer->Material.Wireframe = true;
	buffer->Material.Thickness = 1.0f;
	buffer->Material.DiffuseColor.set(255,255,255,255);
	buffer->Material.BackfaceCulling = false;
	buffer->Material.FrontfaceCulling = false;

	// write center vertex
	const video::SColor clr(255,255,255,255);
	buffer->Vertices[0] = video::S3DVertex(0, 0, 0, 0,0,-1,clr,.5f,.5f);

	for (u32 i=1; i<segments+1; i++)
	{
		video::S3DVertex vertex;
		vertex.Pos.X = -radius*scTable[i].Sin;			// x
		vertex.Pos.Y = radius*scTable[i].Cos;			// y
		vertex.Pos.Z = 0.0f;						// z
		vertex.Normal.X = .0f;						// nx -> will be calculated correctly afterwards
		vertex.Normal.Y = .0f;						// ny -> will be calculated correctly afterwards
		vertex.Normal.Z = -1.0f;					// nz -> will be calculated correctly afterwards
		vertex.Color = clr;							// diffuse color
		vertex.TCoords.X = .5f - .5f*scTable[i].Sin; 	// u
		vertex.TCoords.Y = .5f - .5f*scTable[i].Cos; 	// v
		buffer->Vertices[i] = vertex;
		buffer->BoundingBox.addInternalPoint(vertex.Pos);
	}

	// write indices (segments * triangles clockwise)
	u16* index = buffer->Indices.pointer();
	for (u32 i=0; i<segments; i++)
	{
		if (i==segments-1)
		{
			*index=0; 		 index++;
			*index=segments; index++;
			*index=1; 		 index++;
		}
		else
		{
			*index=0; 	index++;
			*index=i+1; index++;
			*index=i+2; index++;
		}
	}

	/// set mesh
	mesh->addMeshBuffer(buffer);
	mesh->BoundingBox = buffer->getBoundingBox();
	mesh->setHardwareMappingHint(scene::EHM_STATIC);
	buffer->drop();

	/// add mesh to internal manager
	dbMakeObjectFromMesh( objID, mesh);
}


void dbMakeObjectSphere( u32 objID, f32 radius, u32 segments)
{

	return;
}



u32 dbMakeObjectCylinder( u32 id, f32 radius, u32 segments)
{
	return 0;
}


u32 dbMakeObjectCube( u32 id, f32 size)
{
	return 0;
}

u32 dbMakeObjectCone( u32 id, f32 size)
{
	return 0;
}

u32 dbMakeObjectTorus( u32 id, f32 size)
{
	return 0;
}

u32 dbMakeObjectTeapot( u32 id, f32 size)
{
	return 0;
}

u32 dbMakeObjectBunny( u32 id, f32 size)
{
	return 0;
}


//-----------------------------------------------------------------------------
//	dbMakePlainMeshBuffer
//-----------------------------------------------------------------------------

//	buffer->Material.AmbientColor.set(50,255,255,255);
//	buffer->Material.DiffuseColor.set(255,255,255,255);
//	buffer->Material.AntiAliasing = video::EAAM_QUALITY;
//	buffer->Material.ColorMaterial = false;
//	buffer->Material.BackfaceCulling = false;
//	buffer->Material.EmissiveColor.set(255,100,255,100);
//	buffer->Material.SpecularColor.set(255,255,255,255);
//	buffer->Material.FogEnable = true;
//	buffer->Material.FrontfaceCulling = false;
//	buffer->Material.GouraudShading = false;
//	buffer->Material.Lighting = true;
//	buffer->Material.MaterialType = video::EMT_TRANSPARENT_ALPHA_CHANNEL;
//	buffer->Material.NormalizeNormals = false;
//	buffer->Material.PointCloud = false;
//	buffer->Material.Shininess = 20.5f;
//	buffer->Material.Thickness = 1.0f;
//	buffer->Material.Wireframe = true;
//	buffer->Material.ZBuffer = true;
//	buffer->Material.ZWriteEnable =true;

} // end namespace irr
