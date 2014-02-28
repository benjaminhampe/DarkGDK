/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BASIC 3D COMMANDS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <d3dx9.h>
#include <windows.h>
#include <DBO Format/dbodata.h>
#include <stack>
#include <vector>

void		dbLoadObject							( char* szFilename, int iID );
void		dbLoadObject							( char* szFilename, int iID, int iDBProMode );
void		dbSaveObject							( char* szFilename, int iID );
void		dbDeleteObject							( int iID );
void		dbSetObject								( int iID, bool bWireframe, bool bTransparency, bool bCull );
void		dbSetObject								( int iID, bool bWireframe, bool bTransparency, bool bCull, int iFilter );
void		dbSetObject								( int iID, bool bWireframe, bool bTransparency, bool bCull, int iFilter, bool bLight );
void		dbSetObject								( int iID, bool bWireframe, bool bTransparency, bool bCull, int iFilter, bool bLight, bool bFog );
void		dbSetObject								( int iID, bool bWireframe, bool bTransparency, bool bCull, int iFilter, bool bLight, bool bFog, bool bAmbient );
void		dbSetObjectWireframe					( int iID, bool bFlag    );
void		dbSetObjectTransparency					( int iID, int iFlag    );
void		dbSetObjectCull							( int iID, bool bCull    );
void		dbSetObjectFilter						( int iID, int  iFilter  );
void		dbSetObjectFilterStage					( int iID, int iStage, int iFilter );
void		dbSetObjectLight						( int iID, bool bLight   );
void		dbSetObjectFog							( int iID, bool bFog     );
void		dbSetAmbient							( int iID, bool bAmbient );
void		dbSetObjectAmbient						( int iID, bool bAmbient );
void		dbMakeObject							( int iID, int iMeshID, int iTextureID );
void		dbMakeObjectSphere						( int iID, float fRadius, int iRings, int iSegments );
void		dbCloneObject							( int iDestinationID, int iSourceID, int iCloneSharedData );
void		dbCloneObject							( int iDestinationID, int iSourceID );
void		dbInstanceObject						( int iDestinationID, int iSourceID );
void		dbMakeObjectSphere						( int iID, float fRadius );
void		dbMakeObjectCube						( int iID, float iSize );
void		dbMakeObjectBox							( int iID, float fWidth, float fHeight, float fDepth );
void		dbMakeObjectPyramid						( int iID, float fSize );
void		dbMakeObjectCylinder					( int iID, float fSize );
void		dbMakeObjectCone						( int iID, float fSize );
void		dbMakeObjectPlane						( int iID, float fWidth, float fHeight );
void		dbMakeObjectTriangle					( int iID, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3 );
void		dbAppendObject							( char* pString, int iID, int iFrame );
void		dbPlayObject							( int iID );
void		dbPlayObject 							( int iID, int iStart );
void		dbPlayObject							( int iID, int iStart, int iEnd );
void		dbLoopObject							( int iID );
void		dbLoopObject							( int iID, int iStart );
void		dbLoopObject							( int iID, int iStart, int iEnd );
void		dbStopObject							( int iID );
void		dbHideObject							( int iID );
void		dbShowObject							( int iID );
void		dbColorObject							( int iID, DWORD dwRGB );
void		dbSetObjectFrame						( int iID, int iFrame );
void		dbSetObjectFrame						( int iID, float fFrame );
void		dbSetObjectFrame						( int iID, float fFrame, int iRecalculateBounds );
void		dbSetObjectSpeed						( int iID, int iSpeed );
void		dbSetObjectInterpolation				( int iID, int iJump );
void		dbSetObjectRotationXYZ					( int iID );
void		dbSetObjectRotationZYX					( int iID );
void		dbGhostObjectOn							( int iID );
void		dbGhostObjectOn							( int iID, int iFlag );
void		dbGhostObjectOff						( int iID );
void		dbFadeObject							( int iID, float iPercentage );
void		dbGlueObjectToLimb						( int iSource, int iTarget, int iLimb );
void		dbGlueObjectToLimb						( int iSource, int iTarget, int iLimb, int iMode );
void		dbUnGlueObject							( int iID );
void		dbLockObjectOn							( int iID );
void		dbLockObjectOff							( int iID );
void		dbDisableObjectZDepth					( int iID );
void		dbEnableObjectZDepth					( int iID );
void		dbDisableObjectZRead					( int iID );
void		dbEnableObjectZRead						( int iID );
void		dbDisableObjectZWrite					( int iID );
void		dbEnableObjectZWrite					( int iID );
void		dbSetObjectFOV							( int iID, float fRadius );
void		dbDeleteObjects							( int iFrom, int iTo );
void		dbClearObjectsOfTextureRef				( LPDIRECT3DTEXTURE9 pTextureRef );
void		dbDisableObjectBias						( int iID );
void		dbEnableObjectZBias						( int iID, float fSlopeScale, float fDepth );

void 		dbPositionObject  						( int iID, float fX, float fY, float fZ );
void		dbScaleObject     						( int iID, float fX, float fY, float fZ );
void 		dbRotateObject    						( int iID, float fX, float fY, float fZ );
void 		dbMoveObject      						( int iID, float fStep );
void 		dbPointObject     						( int iID, float fX, float fY, float fZ );
void 		dbMoveObjectDown  						( int iID, float fStep );
void 		dbMoveObjectLeft  						( int iID, float fStep );
void 		dbMoveObjectRight 						( int iID, float fStep );
void 		dbMoveObjectUp    						( int iID, float fStep );
void 		dbXRotateObject   						( int iID, float fX );
void 		dbYRotateObject   						( int iID, float fY );
void 		dbZRotateObject   						( int iID, float fZ );
void 		dbTurnObjectLeft  						( int iID, float fAngle );
void 		dbTurnObjectRight 						( int iID, float fAngle );
void 		dbPitchObjectUp   						( int iID, float fAngle );
void 		dbPitchObjectDown 						( int iID, float fAngle );
void 		dbRollObjectLeft  						( int iID, float fAngle );
void 		dbRollObjectRight 						( int iID, float fAngle );

float 		dbObjectPositionX 						( int iID );
float 		dbObjectPositionY 						( int iID );
float 		dbObjectPositionZ						( int iID );
float		dbObjectSize							( int iID );
float		dbObjectSizeX							( int iID );
float		dbObjectSizeY							( int iID );
float		dbObjectSizeZ							( int iID );
float 		dbObjectAngleX 							( int iID );
float 		dbObjectAngleY 							( int iID );
float 		dbObjectAngleZ 							( int iID );

void		dbSetObjectDiffuse						( int iID, DWORD dwRGB );
void		dbSetObjectAmbience						( int iID, DWORD dwRGB );
void		dbSetObjectSpecular						( int iID, DWORD dwRGB );
void		dbSetObjectSpecularPower				( int iID, float fPower );
void		dbSetObjectEmissive						( int iID, DWORD dwRGB );

void		dbFixObjectPivot						( int iID );
void		dbSetObjectToObjectOrientation			( int iID, int iWhichID );
void		dbSetObjectToObjectOrientation			( int iID, int iWhichID, int iWhichLimbID );
void		dbSetObjectToCameraOrientation			( int iID );

void		dbTextureObject							( int iID, int iImage );
void		dbTextureObject							( int iID, int iStage, int iImage );
void		dbScrollObjectTexture					( int iID, float fU, float fV );
void		dbScaleObjectTexture					( int iID, float fU, float fV );
void		dbScaleObjectTexture					( int iID, int iStage, float fU, float fV );
void		dbSetObjectSmoothing					( int iID, float fAngle );
void		dbSetObjectNormals						( int iID );
void		dbSetObjectTexture						( int iID, int iMode, int iMipGeneration );
void		dbSetObjectTexture						( int iID, int iStage, int iMode, int iMipGeneration );
void		dbSetLightMappingOn						( int iID, int iImage );
void		dbSetSphereMappingOn					( int iID, int iSphereImage );
void		dbSetCubeMappingOn						( int iID, int i1, int i2, int i3, int i4, int i5, int i6 );
void		dbSetDetailMappingOn					( int iID, int iImage );
void		dbSetBlendMappingOn						( int iID, int iImage, int iMode );
void		dbSetBlendMappingOn						( int iID, int iStage, int iImage, int iTexCoordMode, int iMode );
void		dbSetTextureMD3							( int iID, int iH0, int iH1, int iL0, int iL1, int iL2, int iU0 );

void		dbSetAlphaMappingOn						( int iID, float fPercentage );

void		dbSetBumpMappingOn						( int iID, int iBumpMap );
void		dbSetCartoonShadingOn					( int iID, int iStandardImage, int iEdgeImage );
void		dbSetRainbowShadingOn					( int iID, int iStandardImage );

void		dbSetEffectOn							( int iID, char* pFilename, int iUseDefaultTextures );
void		dbLoadEffect							( char* pFilename, int iEffectID, int iUseDefaultTextures );
void		dbDeleteEffect							( int iEffectID );
void		dbSetObjectEffect						( int iID, int iEffectID );
void		dbSetLimbEffect							( int iID, int iLimbID, int iEffectID );
void		dbPerformChecklistForEffectValues		( int iEffectID );
void		dbPerformChecklistForEffectErrors		( void );
void		dbPerformChecklistForEffectErrors		( int iEffectID );
void		dbSetEffectTranspose					( int iEffectID, int iTransposeFlag );
void		dbSetEffectConstantBoolean				( int iEffectID, char* pConstantName, int iValue );
void		dbSetEffectConstantInteger				( int iEffectID, char* pConstantName, int iValue );
void		dbSetEffectConstantFloat				( int iEffectID, char* pConstantName, float fValue );
void		dbSetEffectConstantVector				( int iEffectID, char* pConstantName, int iValue );
void		dbSetEffectConstantMatrix				( int iEffectID, char* pConstantName, int iValue );
void		dbSetEffectTechnique					( int iEffectID, char* pTechniqueName );
int			dbEffectExist							( int iEffectID );

void		dbSetShadowShadingOn					( int iID );
void		dbSetShadowClipping						( int iID, float fMin, float fMax );
void		dbSetReflectionShadingOn				( int iID );
void		dbSetGlobalShadowColor					( int iRed, int iGreen, int iBlue, int iAlphaLevel );
void		dbSetGlobalShadowShades					( int iShades );
void		dbSetGlobalReflectionColor				( int iRed, int iGreen, int iBlue, int iAlphaLevel );

void		dbSetShadowShadingOff					( int iID );
void		dbSetShadowPosition						( int iMode, float fX, float fY, float fZ );
void		dbSetShadowShadingOn					( int iID, int iMesh, int iRange, int iUseShader );

void		dbSetVertexShaderOn          			( int iID, int iShader );
void		dbSetVertexShaderOff         			( int iID );
void		dbConvertObjectFVF		       			( int iID, DWORD dwFVF );
void		dbSetVertexShaderStreamCount 			( int iID, int iCount );
void		dbSetVertexShaderStream      			( int iID, int iStreamPos, int iData, int iDataType );
void		dbCreateVertexShaderFromFile 			( int iID, char* szFile );
void		dbSetVertexShaderVector      			( int iID, DWORD dwRegister, int iVector, DWORD dwConstantCount );
void		dbSetVertexShaderMatrix      			( int iID, DWORD dwRegister, int iMatrix, DWORD dwConstantCount );
void		dbDeleteVertexShader					( int iShader );

void		dbSetPixelShaderOn						( int iID, int iShader );
void		dbSetPixelShaderOff						( int iID );
void		dbCreatePixelShaderFromFile				( int iID, char* szFile );
void		dbDeletePixelShader						( int iShader );
void		dbSetPixelShaderTexture					( int iShader, int iSlot, int iTexture );

void		dbSaveObjectAnimation					( int iID, char* pFilename );
void		dbAppendObjectAnimation					( int iID, char* pFilename );
void		dbClearAllObjectKeyFrames				( int iID );
void		dbClearObjectKeyFrame					( int iID, int iFrame );
void		dbSetObjectKeyFrame						( int iID, int iFrame );

void		dbSetStaticUniverse						( float fX, float fY, float fZ );
void		dbMakeStaticObject						( int iID, int iType, int iArbitaryValue, int iCastShadow, int iPortalBlocker );
void		dbMakeStaticLimb						( int iID, int iLimb, int iType, int iArbitaryValue, int iCastShadow, int iPortalBlocker );
void		dbDeleteStaticObject					( int iID );
void		dbDeleteStaticObjects					( void );
void		dbSetStaticObjectsWireframeOn			( void );
void		dbSetStaticObjectsWireframeOff			( void );
void		dbMakeStaticCollisionBox				( float fX1, float fY1, float fZ1, float fX2, float fY2, float fZ2 );
void		dbSetSetStaticObjectsTexture			( int iMode );
void		dbDisableStaticOcclusion				( void );
void		dbEnableStaticOcclusion					( void );
void		dbSaveStaticObjects						( char* pFilename );
void		dbLoadStaticObjects						( char* pFilename, int iDivideTextureSize );
void		dbAttachObjectToStatic					( int iID );
void		dbDetachObjectFromStatic				( int iID );
void		dbSetStaticPortalsOn       				( void );
void		dbSetStaticPortalsOff					( void );
void		dbBuildStaticPortals					( void );
void		dbSetStaticScorch						( int iImageID, int iWidth, int iHeight );
void		dbAddStaticScorch						( float fSize, int iType );
void		dbAddStaticLight						( int iLightIndex, float fX, float fY, float fZ, float fRange );

void		dbPeformCSGUnion						( int iObjectA, int iObjectB );
void		dbPeformCSGDifference					( int iObjectA, int iObjectB );
void		dbPeformCSGIntersection					( int iObjectA, int iObjectB );
void		dbPeformCSGClip							( int iObjectA, int iObjectB );
int			dbObjectBlocking						( int iID, float X1, float Y1, float Z1, float X2, float Y2, float Z2 );

void		dbAddObjectToLightMapPool				( int iID );
void		dbAddLimbToLightMapPool					( int iID, int iLimb );
void		dbAddStaticObjectsToLightMapPool		( void );
void		dbAddLightMapLight						( float fX, float fY, float fZ, float fRadius, float fRed, float fGreen, float fBlue, float fBrightness, bool bCastShadow );
void		dbDeleteLightMapLights					( void );
void		dbCreateLightMaps						( int iLMSize, int iLMQuality, char* dwPathForLightMaps );

void		dbSetGlobalShadowsOn					( void );
void		dbSetGlobalShadowsOff					( void );

void		dbSetObjectCollisionOn					( int iID );
void		dbSetObjectCollisionOff					( int iID );
void		dbMakeObjectCollisionBox				( int iID, float iX1, float iY1, float iZ1, float iX2, float iY2, float iZ2, int iRotatedBoxFlag );
void		dbDeleteObjectCollisionBox				( int iID );
void		dbSetObjectCollisionToSpheres			( int iID );
void		dbSetObjectCollisionToBoxes				( int iID );
void		dbSetObjectCollisionToPolygons			( int iID );
void		dbSetGlobalCollisionOn					( void );
void		dbSetGlobalCollisionOff					( void );
void		dbSetObjectRadius						( int iID, float fRadius );
float		dbIntersectObject						( int iObjectID, float fX, float fY, float fZ, float fNewX, float fNewY, float fNewZ );
void		dbAutomaticObjectCollision				( int iObjectID, float fRadius, int iResponse );
void		dbAutomaticCameraCollision				( int iCameraID, float fRadius, int iResponse );
void		dbCalculateAutomaticCollision			( void );
void		dbHideObjectBounds						( int iID );
void		dbShowObjectBounds						( int iID, int iBoxOnly );
void		dbShowObjectBounds						( int iID );
void		dbShowObjectLimbBounds					( int iID, int iLimb );

void		dbPerformCheckListForObjectLimbs		( int iID );
void		dbHideLimb								( int iID, int iLimbID );
void		dbShowLimb								( int iID, int iLimbID );
void		dbOffsetLimb							( int iID, int iLimbID, float fX, float fY, float fZ );
void		dbOffsetLimb							( int iID, int iLimbID, float fX, float fY, float fZ, int iBoundFlag );
void		dbRotateLimb							( int iID, int iLimbID, float fX, float fY, float fZ );
void		dbRotateLimb							( int iID, int iLimbID, float fX, float fY, float fZ, int iBoundFlag );
void		dbScaleLimb								( int iID, int iLimbID, float fX, float fY, float fZ );
void		dbScaleLimb								( int iID, int iLimbID, float fX, float fY, float fZ, int iBoundFlag );
void		dbAddLimb								( int iID, int iLimbID, int iMeshID );
void		dbRemoveLimb							( int iID, int iLimbID );
void		dbLinkLimb								( int iID, int iParentID, int iLimbID );
void		dbTextureLimb							( int iID, int iLimbID, int iImageID );
void		dbTextureLimb							( int iID, int iLimbID, int iStage, int iImageID );
void		dbColorLimb								( int iID, int iLimbID, DWORD dwColor );
void		dbScrollLimbTexture						( int iID, int iLimbID, float fU, float fV );
void		dbScaleLimbTexture						( int iID, int iLimbID, float fU, float fV );
void		dbSetLimbSmoothing						( int iID, int iLimbID, float fPercentage );
void		dbSetLimbNormals						( int iID, int iLimbID );

void		dbMakeObjectFromLimb					( int iID, int iSrcObj, int iLimbID );

void		dbLoadMesh								( char* pFilename, int iID );
void		dbDeleteMesh							( int iID );
void		dbSaveMesh								( char* pFilename, int iMeshID );
void		dbChangeMesh							( int iObjectID, int iLimbID, int iMeshID );
void		dbMakeMeshFromObject					( int iID, int iObjectID );
void		dbReduceMesh							( int iMeshID, int iBlockMode, int iNearMode, int iGX, int iGY, int iGZ );
void		dbMakeLODFromMesh						( int iMeshID, int iVertNum, int iNewMeshID );

void		dbLockVertexDataForLimb					( int iID, int iLimbID, int iReplaceOrUpdate );
void		dbLockVertexDataForLimb					( int iID, int iLimbID );
void		dbLockVertexDataForMesh					( int iID );
void		dbUnlockVertexData						( void );
void		dbSetVertexDataPosition					( int iVertex, float fX, float fY, float fZ );
void		dbSetVertexDataNormals					( int iVertex, float fNX, float fNY, float fNZ );
void		dbSetVertexDataDiffuse					( int iVertex, DWORD dwDiffuse );
void		dbSetVertexDataUV						( int iVertex, float fU, float fV );
void		dbSetVertexDataSize 					( int iVertex, float fSize );
void		dbSetIndexData							( int iIndex, int iValue );
void		dbSetVertexDataUV						( int iVertex, int iIndex, float fU, float fV );

void		dbAddMeshToVertexData					( int iMeshID );
void		dbDeleteMeshFromVertexData				( int iVertex1, int iVertex2, int iIndex1, int iIndex2 );
void		dbPeformCSGUnionOnVertexData			( int iBrushMeshID );
void		dbPeformCSGDifferenceOnVertexData		( int iBrushMeshID );
void		dbPeformCSGIntersectionOnVertexData		( int iBrushMeshID );
int			dbGetVertexDataVertexCount				( void );
int			dbGetVertexDataIndexCount				( void );
float		dbGetVertexDataPositionX				( int iVertex );
float		dbGetVertexDataPositionY				( int iVertex );
float		dbGetVertexDataPositionZ				( int iVertex );
float		dbGetVertexDataNormalsX					( int iVertex );
float		dbGetVertexDataNormalsY					( int iVertex );
float		dbGetVertexDataNormalsZ					( int iVertex );
DWORD		dbGetVertexDataDiffuse					( int iVertex );
float		dbGetVertexDataU						( int iVertex );
float		dbGetVertexDataV						( int iVertex );
float		dbGetVertexDataU						( int iVertex, int iIndex );
float		dbGetVertexDataV						( int iVertex, int iIndex );
int			dbGetIndexData							( int iIndex );

void		dbSetMipmapMode							( int iMode );
void		dbFlushVideoMemory						( void );
void		dbDisableTNL							( void );
void		dbEnableTNL								( void );
void		dbConvert3DStoX							( char* pFilename1, char* pFilename2 );

int			dbPickObject							( int iX, int iY, int iObjectStart, int iObjectEnd );
void		dbPickScreen							( int iX, int iY, float fDistance );
float		dbGetPickDistance						( void );
float		dbGetPickVectorX						( void );
float		dbGetPickVectorY						( void );
float		dbGetPickVectorZ						( void );

void		dbMakeEmitter							( int iID, int iSize );
void		dbGetEmitterData  						( int iID, BYTE** ppVertices, DWORD* pdwVertexCount, int** ppiDrawCount );
void		dbUpdateEmitter   						( int iID );

void		dbExcludeObjectOn 						( int iID );
void		dbExcludeObjectOff						( int iID );

int			dbObjectExist  	  						( int iID );
int			dbTotalObjectFrames 					( int iID );
float		dbObjectSize 							( int iID );
float		dbObjectSize							( int iID, int iUseScaling );
float		dbObjectSizeX							( int iID );
float		dbObjectSizeY							( int iID );
float		dbObjectSizeZ							( int iID );
float		dbObjectSizeX							( int iID, int iUseScaling );
float		dbObjectSizeY							( int iID, int iUseScaling );
float		dbObjectSizeZ							( int iID, int iUseScaling );
int			dbObjectVisible    						( int iID );
int			dbObjectPlaying    						( int iID );
int			dbObjectLooping    						( int iID );
float		dbObjectFrame          					( int iID );
float		dbObjectSpeed          					( int iID );
float		dbObjectInterpolation  					( int iID );
int			dbObjectScreenX        					( int iID );
int			dbObjectScreenY        					( int iID );
int			dbObjectInScreen       					( int iID );

float		dbObjectCollisionRadius					( int iID );
float		dbObjectCollisionCenterX 				( int iID );
float		dbObjectCollisionCenterY 				( int iID );
float		dbObjectCollisionCenterZ 				( int iID );

int			dbObjectCollision 						( int iObjectA, int iObjectB );
int			dbObjectHit								( int iObjectA, int iObjectB );
int			dbLimbCollision							( int iObjectA, int iLimbA, int iObjectB, int iLimbB );
int			dbLimbHit								( int iObjectA, int iLimbA, int iObjectB, int iLimbB );
int			dbGetStaticCollisionHit 				( float fOldX1, float fOldY1, float fOldZ1, float fOldX2, float fOldY2, float fOldZ2, float fNX1,   float fNY1,   float fNZ1,   float fNX2,   float fNY2,   float fNZ2   );
int			dbStaticLineOfSight 					( float fSx, float fSy, float fSz, float fDx, float fDy, float fDz, float fWidth, float fAccuracy );
int			dbStaticRayCast 						( float fSx, float fSy, float fSz, float fDx, float fDy, float fDz );
int			dbStaticVolume	 						( float fX, float fY, float fZ, float fNewX, float fNewY, float fNewZ, float fSize );
float		dbGetStaticCollisionX					( void );
float		dbGetStaticCollisionY					( void );
float		dbGetStaticCollisionZ					( void );
int			dbGetStaticCollisionFloor 				( void );
int			dbGetStaticCollisionCount				( void );
int			dbGetStaticCollisionValue				( void );

float		dbStaticLineOfSightX					( void );
float		dbStaticLineOfSightY 					( void );
float		dbStaticLineOfSightZ 					( void );
float		dbGetObjectCollisionX					( void );
float		dbGetObjectCollisionY					( void );
float		dbGetObjectCollisionZ					( void );

int			dbLimbExist 							( int iID, int iLimbID );

float		dbLimbOffsetX    						( int iID, int iLimbID );
float		dbLimbOffsetY    						( int iID, int iLimbID );
float		dbLimbOffsetZ    						( int iID, int iLimbID );
float		dbLimbAngleX     						( int iID, int iLimbID );
float		dbLimbAngleY     						( int iID, int iLimbID );
float		dbLimbAngleZ     						( int iID, int iLimbID );
float		dbLimbPositionX  						( int iID, int iLimbID );
float		dbLimbPositionY  						( int iID, int iLimbID );
float		dbLimbPositionZ							( int iID, int iLimbID );
float		dbLimbDirectionX 						( int iID, int iLimbID );
float		dbLimbDirectionY 						( int iID, int iLimbID );
float		dbLimbDirectionZ 						( int iID, int iLimbID );
int			dbLimbTexture							( int iID, int iLimbID );
int			dbLimbVisible							( int iID, int iLimbID );
int			dbCheckLimbLink 						( int iID, int iLimbID );
char*		dbLimbTextureName						( DWORD pDestStr, int iID, int iLimbID );

int			dbMeshExist								( int iID );
int			dbAlphaBlendingAvailable				( void );
int			dbFilteringAvailable					( void );
int			dbFogAvailable							( void );
int			dbGet3DBLITAvailable					( void );
int			dbStatistic								( int iCode );
int			dbGetTNLAvailable						( void );

char*		dbLimbName						  		( DWORD pDestStr, int iID, int iLimbID );
int			dbLimbCount					    		( int iID );
float		dbLimbScaleX				    		( int iID, int iLimbID );
float		dbLimbScaleY				    		( int iID, int iLimbID );
float		dbLimbScaleZ				    		( int iID, int iLimbID );

bool		dbVertexShaderExist						( int iShader );
bool		dbPixelShaderExist						( int iShader );

int			dbGetDeviceType							( void );
bool		dbCalibrateGammaAvailable          		( void );
bool		dbRenderWindowedAvailable          		( void );
bool		dbFullScreenGammaAvailable         		( void );
bool		dbBlitSysOntoLocalAvailable        		( void );
bool		dbRenderAfterFlipAvailable         		( void );
bool		dbTNLAvailable			           		( void );
bool		dbGetHWTransformAndLight        		( void );
bool		dbSeparateTextureMemoriesAvailable 		( void );
bool		dbTextureSystemMemoryAvailable			( void );
bool		dbTextureVideoMemoryAvailable      		( void );
bool		dbNonLocalVideoMemoryAvailable	 		( void );
bool		dbTLVertexSystemMemoryAvailable    		( void );
bool		dbTLVertexVideoMemoryAvailable     		( void );
bool		dbClipAndScalePointsAvailable      		( void );
bool		dbClipTLVertsAvailable            		( void );
bool		dbColorWriteEnableAvailable        		( void );
bool		dbCullCCWAvailable                 		( void );
bool		dbCullCWAvailable                  		( void );
bool		dbAnisotropicFilteringAvailable    		( void );
bool		dbAntiAliasAvailable             		( void );
bool		dbColorPerspectiveAvailable        		( void );
bool		dbDitherAvailable                 		( void );
bool		dbFogRangeAvailable                		( void );
bool		dbFogTableAvailable                		( void );
bool		dbFogVertexAvailable               		( void );
bool		dbMipMapLODBiasAvailable           		( void );
bool		dbWBufferAvailable                 		( void );
bool		dbWFogAvailable                    		( void );
bool		dbZFogAvailable                    		( void );
bool		dbAlphaAvailable                   		( void );
bool		dbCubeMapAvailable                 		( void );
bool		dbMipCubeMapAvailable              		( void );
bool		dbMipMapAvailable                  		( void );
bool		dbMipMapVolumeAvailable            		( void );
bool		dbNonPowTexturesAvailable        		( void );
bool		dbPerspectiveTexturesAvailable     		( void );
bool		dbProjectedTexturesAvailable       		( void );
bool		dbOnlySquareTexturesAvailable      		( void );
bool		dbVolumeMapAvailable              		( void );
bool		dbAlphaComparisionAvailable       		( void );
bool		dbTextureAvailable              		( void );
bool		dbZBufferAvailable                 		( void );
int			dbGetMaximumTextureWidth           		( void );
int			dbGetMaximumTextureHeight          		( void );
int			dbGetMaximumVolumeExtent           		( void );
float		dbGetMaximumVertexShaderVersion    		( void );
float		dbGetMaximumPixelShaderVersion     		( void );
int			dbGetMaximumVertexShaderConstants  		( void );
float		dbGetMaximumPixelShaderValue       		( void );
int			dbGetMaximumLights                 		( void );

void		dbObjectSetDisableTransform 			( int iID, bool bTransform );
void		dbCreateMeshForObject					( int iID, DWORD dwFVF, DWORD dwVertexCount, DWORD dwIndexCount );
void		dbSetObjectWorldMatrix 					( int iID, D3DXMATRIX* pMatrix );
void		dbGetObjectWorldMatrix 					( int iID, int iLimb, D3DXMATRIX* pMatrix );
D3DXVECTOR3	dbGetObjectCameraLook					( void );
D3DXVECTOR3	dbGetObjectCameraPosition				( void );
D3DXVECTOR3	dbGetObjectCameraUp						( void );
D3DXVECTOR3	dbGetObjectCameraRight					( void );
D3DXMATRIX	dbGetObjectCameraMatrix					( void );
sObject*	dbGetObject								( int iID );

//	@@@ PSJM - Added to provide exports for plugins originally written for DarkBASIC Professional
bool		GetFVFOffsetMap			( sMesh* pMesh, sOffsetMap* psOffsetMap );
bool		CalculateMeshBounds		( sMesh* pMesh );
bool		CalcObjectWorld			( sObject* pObject );
bool		MakeMeshFromOtherMesh	( bool bCreateNew, sMesh* pMesh, sMesh* pOtherMesh, D3DXMATRIX* pmatWorld );
void		GetUniverseMeshList		( std::vector<sMesh*> *pMeshList );
bool		GetFVFValueOffsetMap	( unsigned long lFVF, sOffsetMap *pOffsetMap );
void		ConvertLocalMeshToVertsOnly( sMesh *pMesh );
void		ConvertToSharedVerts	( sMesh *pMesh, float fThreshold );
bool		ConvertLocalMeshToTriList( sMesh *pMesh );
bool		CalculateAllBounds		( sObject *pObject, bool bFlag );
bool		CalculateMeshBounds		( sMesh *pMesh );
//	@@@

void		ConstructorBasic3D			( HINSTANCE hSetup, HINSTANCE hImage, HINSTANCE hTypes, HINSTANCE hCamera );
void		SetErrorHandlerBasic3D		( LPVOID pErrorHandlerPtr );
void		PassCoreDataBasic3D		( LPVOID pGlobPtr );
void		RefreshD3DBasic3D			( int iMode );
void		DestructorBasic3D			( void );

void		dbUpdateBasic3D			( void );
void		dbUpdateOnce				( void );
void		dbUpdateGhostLayer			( void );

void		dbUpdateNoZDepth			( void );
void		dbStencilRenderStart		( void );
void		dbStencilRenderEnd			( void );
void		dbAutomaticStart			( void );
void		dbAutomaticEnd				( void );

void		dbGetMeshData				( int iMeshID, DWORD* pdwFVF, DWORD* pdwFVFSize, DWORD* pdwVertMax, LPSTR* pData, DWORD* dwDataSize, bool bLockData );
void		dbSetMeshData				( int iMeshID, DWORD dwFVF, DWORD dwFVFSize, LPSTR pMeshData, DWORD dwVertMax );

void		dbSetGlobalObjectCreationMode ( int iMode );
void*		dbObjectGetInternalData ( int iID );
void		dbSetObjectMipMapLODBias				( int iID, float fBias );
void		dbSetObjectMipMapLODBias				( int iID, int iLimb, float fBias );

void		dbMakeObjectPlain						( int iID, float fWidth, float fHeight );
void		dbFadeObject							( int iID, int iPercentage );
void		dbSetObjectSmoothing					( int iID, int iPercentage );
void		dbSetObjectAmbient						( int iID, bool bAmbient );
void		dbUnglueObject							( int iID );
void		dbSetAlphaMappingOn						( int iID, int iPercentage );
void		dbSetLimbSmoothing						( int iID, int iLimbID, int iPercentage );
bool		dbAnistropicfilteringAvailable    		( void );
bool		dbBlitSysToLocalAvailable        		( void );
char*		dbLimbTextureName						( int iID, int iLimbID );

void		dbPerformChecklistForObjectLimbs		( int iID );
char*		dbLimbName						  		( int iID, int iLimbID );

void		dbTextureScreen 						( int iStageIndex, int iImageID );
void		dbSetScreenEffect						( int iEffectID );
int			dbRenderQuad 							( int iMode );
