// thc_free.cpp

#include "thc_free.h"
#include "DarkGDK.h"

namespace thc
{
	int FreeImage( void )
	{
		int index = 1;
		while	(dbImageExist(index)==1)
		{ 
			index++;
		}
		return index;
	}
	int FreeObject( void )
	{
		int index = 1;
		while	(dbObjectExist(index)==1)
		{ 
			index++;
		}
		return index;
	}
	int FreeMemblock( void )
	{	
		int index = 0;
		int found = 0;
		do { index++;	if (dbMemblockExist(index)==0) found=index;}	while ( found==0 );
		return found;
	}
	int FreeMesh( void )
	{
		int index = 0;
		int found = 0;
		do	{ index++;	if (dbMeshExist(index)==0) found=index;	} while ( found==0 );
		return found;
	}
	int FreeLimb( int iID )
	{
		int index = 0;
		int found = 0;
		do	{ index++;  if (dbLimbExist(iID,index)==0) found=index;} while ( found==0 );
		return found;
	}
	int FreeMatrix( void )
	{
		int index = 0;
		int found = 0;
		do	{ index++;  if (dbMatrixExist(index)==0) found=index;	} while ( found==0 );
		return found;
	}
	int FreeSound( void )
	{
		int index = 0;
		int found = 0;
		do	{ index++;  if (dbSoundExist(index)==0) found=index;	} while ( found==0 );
		return found;
	}
	int FreeSprite( void )
	{
		int index = 0;
		int found = 0;
		do	{ index++;  if (dbSpriteExist(index)==0) found=index;	} while ( found==0 );
		return found;
	}
}