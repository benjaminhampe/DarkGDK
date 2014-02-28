// thc_free.h

#ifndef __THC_FREE_H_INCLUDED__
#define __THC_FREE_H_INCLUDED__

namespace thc
{
	int FreeImage( void );
	int FreeObject( void );
	int FreeMemblock( void );	
	int FreeMesh( void )	;
	int FreeLimb( int iID );
	int FreeMatrix( void );
	int FreeSound( void );
	int FreeSprite( void );
}

#endif