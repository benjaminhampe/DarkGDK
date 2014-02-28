// thc_is.h

#ifndef __THC_IS_H_INCLUDED__
#define __THC_IS_H_INCLUDED__

namespace thc
{
	bool IsImage(int iID);
	bool IsMemblock( int iID );
	bool IsMesh(int iID);
	bool IsObject( int iID );

	bool IsFile(const char * szFile );
	bool IsImageFile( const char* szFile);
}
#endif