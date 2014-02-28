/////////////////////////////////////////////////////////////////////////////////////////////////////////
// SPRITE COMMANDS //////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <d3d9.h>
#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTION LISTINGS ////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void	dbSetSprite						( int iID, int iBacksave, int iTransparent );
void	dbSprite						( int iID, int iX, int iY, int iImage );
void	dbPasteSprite					( int iID, int iX, int iY );	
void	dbSizeSprite					( int iID, int iXSize, int iYSize );
void	dbScaleSprite					( int iID, float fScale );			
void	dbStretchSprite					( int iID, int iXStretch, int iYStretch );
void	dbMirrorSprite					( int iID );							
void	dbFlipSprite					( int iID );							
void	dbOffsetSprite					( int iID, int iXOffset, int iYOffset );	
void	dbHideSprite					( int iID );						
void	dbShowSprite					( int iID );						
void	dbHideAllSprites				( void );							
void	dbShowAllSprites				( void );							
void	dbDeleteSprite					( int iID );						

void	dbMoveSprite					( int iID, float velocity );					
void	dbRotateSprite					( int iID, float fRotate );				
void	dbSetSpriteImage				( int iID, int iImage );					
void	dbSetSpriteAlpha				( int iID, int iValue );				
void	dbSetSpriteDiffuse 				( int iID, int iR, int iG, int iB );	
void	dbPlaySprite					( int iID, int iStart, int iEnd, int iDelay );			
void	dbSetSpriteFrame				( int iID, int iFrame );									
void	dbSetSpriteTextureCoordinates	( int iID, int iVertex, float tu, float tv );			
void	dbCreateAnimatedSprite			( int iID, char* szImage, int iWidth, int iHeight, int iImageID );
void	dbCloneSprite					( int iID, int iDestinationID );			
void	dbSetSpritePriority				( int iID, int iPriority );

int		dbSpriteExist					( int iID );
int		dbSpriteX         				( int iID );
int		dbSpriteY         				( int iID );
int		dbSpriteImage     				( int iID );
int		dbSpriteWidth     				( int iID );
int		dbSpriteHeight    				( int iID );
int		dbSpriteScaleX    				( int iID );
int		dbSpriteScaleY    				( int iID );
int		dbSpriteMirrored  				( int iID );
int		dbSpriteFlipped   				( int iID );
int		dbSpriteOffsetX   				( int iID );
int		dbSpriteOffsetY   				( int iID );
int		dbSpriteHit       				( int iID, int iTarget );
int		dbSpriteCollision 				( int iID, int iTarget );

float	dbSpriteAngle	  				( int iID );
int		dbSpriteAlpha     				( int iID );
int		dbSpriteRed       				( int iID );
int		dbSpriteGreen     				( int iID );
int		dbSpriteBlue      				( int iID );
int		dbSpriteFrame     				( int iID );
int		dbSpriteVisible   				( int iID );

void	ConstructorSprites				( HINSTANCE hSetup, HINSTANCE hImage );
void	DestructorSprites				( void );
void	SetErrorHandlerSprites			( LPVOID pErrorHandlerPtr );
void	PassCoreDataSprites				( LPVOID pGlobPtr );
void	RefreshD3DSprites				( int iMode );
void	UpdateSprites					( void );
void	UpdateAllSpritesSprites			( void );

void	dbPasteImage					( int iImageID, int iX, int iY, float fU, float fV );
void	dbPasteImageEx					( int iImageID, int iX, int iY, float fU, float fV, int iTransparent );
void	dbPasteTextureToRect			( LPDIRECT3DTEXTURE9 pTexture, float fU, float fV, RECT Rect );

void	dbSaveSpriteBack				( void );
void	dbRestoreSpriteBack				( void );

void	dbScaleSprite					( int iID, int iScale );			
void	dbSetSpriteTextureCoord			( int iID, int iVertex, float tu, float tv );			
