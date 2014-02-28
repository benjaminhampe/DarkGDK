// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXTENSION_QUICK_IO_HELPER_H__
#define __IRR_EXTENSION_QUICK_IO_HELPER_H__

#include <cstdlib>
#include <cstdio>

#include <irrlicht.h>

namespace irr
{

//! @return array of strings ( each string is exactly one line of the read file )

bool writeContainer( const core::array<core::stringc>& container, FILE* file_handle );

bool writeContainer( const core::array<core::stringc>& container, const core::stringc& file_name );

bool writeFile( const core::stringc& src_file_name, FILE* dst_file_handle );

bool readFile( core::array<core::stringc>& container, FILE* file_handle );

bool readFile( core::array<core::stringc>& container, const core::stringc& file_name );

} // end namespace irr

#endif // __IRR_EXTENSION_QUICK_IO_HELPER_H__
