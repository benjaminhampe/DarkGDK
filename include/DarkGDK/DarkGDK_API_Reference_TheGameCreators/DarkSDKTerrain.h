/////////////////////////////////////////////////////////////////////////////////////////////////////////
// TERRAIN COMMANDS /////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void  dbSetupTerrain				( void );

void  dbLoadTerrain					( char* dwFilename, int iID );
void  dbSaveTerrain					( char* dwFilename, int iID );

void  dbMakeObjectTerrain			( int iID );
void  dbBuildTerrain				( int iID );

void  dbSetTerrainScale				( int iID, float fXScale, float fYScale, float fZScale );
void  dbSetTerrainSplit				( int iID, int iSplit );
void  dbSetTerrainTiling			( int iID, int iTile );
void  dbSetTerrainHeightMap			( int iID, char* dwHeightMap );
void  dbSetTerrainTexture			( int iID, int iBase, int iDetail );
void  dbSetTerrainLight				( int iID, float fX, float fY, float fZ, float fRed, float fGreen, float fBlue, float fScale );

float dbGetTerrainGroundHeight		( int iID, float fX, float fZ );
float dbGetTerrainXSize				( int iID );
float dbGetTerrainZSize				( int iID );

void  dbUpdateTerrain				( void );

void  dbSetTerrainHeightmap			( int iID, char* dwHeightMap );

