
#pragma comment ( lib, "shaderdata.lib" )

void dbShaderDataStart( );	//must be called before any other commands

void dbReloadShaderDisplayPointer( );	//must be called after any "set display mode" calls

void dbMakeDynamicCubeMap( int iID, int size );	//creates a cube map of the specified resolution, valid ID = 1-10
void dbMakeDynamicCubeMap( int iID, int size, int mipmapped );	//creates a cube map of the specified resolution, with mipmap parameter
void dbDeleteDynamicCubeMap( int iID );	//deletes a cubemap
void dbRenderDynamicCubeMap( int iID, int camera, float x, float y, float z );	//renders a cube map with a camera (-1 for temp camera) at a position
void dbApplyCubeMapToObject( int objID, int stage, int iID, int shader );	//applies a cube map to an object stage, use shader=1 if using an object shader
void dbApplyCubeMapToObject( int objID, int stage, int iID );	//applies a cube map to an object stage, shader=1
int dbDynamicCubeMapExist( int iID ); //returns 1 if cube map exists

void dbLoadCameraEffect( char* filename, int effectID, int loadTex );	//Loads a camera effect into an ID, separate from object effect IDs
void dbDeleteCameraEffect( int effectID );	//delete a camera effect
int dbCameraEffectExist( int effectID );	//returns 1 if effect exists
void dbSetCameraEffectConstantFloat( int effectID, char* varName, float value );	//set a float variable in a camera effect
void dbSetCameraEffectConstantInt( int effectID, char* varName, int value );	//set an integer variable in a camera effect
void dbSetCameraEffectConstantVector( int effectID, char* varName, int vector );	//set a float vector variable in a camera effect, uses dbvector4
void dbSetCameraEffect( int camera, int effect, int image );	//set an effect to a camera, and output to an image, this command will also take control of image 65499
void dbRemoveCameraEffect( int camera );	//remove an effect from an image
void dbSyncCamera( int camera );	//render a camera containing a camera effect, no other cameras synced, only output is to the image from SetCameraEffect