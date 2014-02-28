// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#include "readFile.h"

namespace irr
{

bool readFile( core::array<core::stringc>& container, const core::stringc& file_name )
{
	FILE* file_handle = fopen( file_name.c_str(), "r");
	if (!file_handle)
	{
		return false;
	}

	const u32 buffer_size = 1024;

	c8* line_buffer = new c8[buffer_size];
	if (!line_buffer)
	{
		fclose( file_handle );
		return false;
	}

	u32 line_count = 0;

	while( fgets( line_buffer, buffer_size, file_handle) )
	{
		line_count++;
	}

	if (line_count == 0)
	{
		fclose( file_handle );
		return false;
	}

	container.reallocate( line_count );
	container.set_used( 0 );

	rewind( file_handle );

	while( fgets( line_buffer, buffer_size, file_handle) )
	{
		container.push_back( core::stringc( line_buffer ) );
	}

	fclose( file_handle );

	return true;
}

bool writeFile( const core::stringc& src_file_name, FILE* dst_file_handle )
{
	if (!dst_file_handle)
		return false;

	/// create a temporary buffer of chars

	const u32 buffer_size = 1024;
	c8* line_buffer = new c8[buffer_size];

	if (!line_buffer)
		return false;

	/// open file

	FILE* src_file_handle = fopen( src_file_name.c_str(), "r");

	if (!src_file_handle)
		return false;


	/// copy lines from loaded hdd file to dst_file_handle ( i.e. stdout )

	while( fgets( line_buffer, buffer_size, src_file_handle) )
	{
		fputs( line_buffer, dst_file_handle );
	}

//		if (ferror(file))
//		{
//			/* deal with error */
//		}

	fclose( src_file_handle );

	return true;
}

} // end namespace irr
