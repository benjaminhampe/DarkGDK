#include "CClassBuilder.h"

namespace irr{
namespace core{

/// ////////////////////////////////////////////////
/// @brief SystemCall to stringc
/// ////////////////////////////////////////////////

bool trimLine( stringc& line, u32 loop_count, const c8* char_list, const u32 char_count )
{
	u32 k_max = 3;
	bool result = false;

	/// find from start
	u32 k = 0;
	s32 pos = line.findFirstChar(char_list, char_count);
	if ( pos != -1 )
	{
		result = true;
		while ( (pos != -1) && (k<k_max) )
		{
			line.erase( k ); // more hackisch
			pos = line.findFirstChar(char_list, char_count);
			k++;
		}
	}

	/// find from back
	k = 0;
	pos = line.findLastChar(char_list, char_count);
	if ( pos != -1 )
	{
		result = true;
		while ( (pos != -1) && (k<k_max) )
		{
			line.erase( line.size()-1 ); // more hackisch
			pos = line.findLastChar(char_list, char_count);
			k++;
		}
	}
	return result;
}


/// @brief List all files of given extension-list
u32 FindFiles( Container& out, const stringc& rootDir, const Container& fileTypes )
{
	if (rootDir.size()==0)
		return 0;

	if (fileTypes.size()==0)
		return 0;

	const u32 old_size = out.size();

	for (u32 i=0; i<fileTypes.size(); i++)
	{
		core::stringc command;
		command = "find ";
		command += rootDir;
		command += " -iname '*.";
		command += fileTypes[i];
		command += "' | sort";
		AddLines( out, command );
	}
	return out.size() - old_size; // return Number of added lines(stringc) to container 'out'.
}

/// @brief Print all lines
void Print( const Container& out )
{
	if (out.size()==0)
		return;

	for (u32 i=0; i<out.size(); i++)
	{
		printf("%s\n", out[i].c_str() );
	}
}
/// @brief SystemCall to stringc
stringc SingleSysCall( const stringc& command, const u32 LENGTH )
{
    /// open pipe to shell command result
	FILE *f = popen( command.c_str(), "r");
	if (!f) { printf ( "Could not open temporary file as bash script.\n" );	return stringc(""); }

	/// create linebuffer
	c8* buffer = new c8[LENGTH];
	if (!buffer) { printf ( "Sorry, but you are out of memory.\n" ); return stringc(""); }

	u32 lineCount = 0;

	stringc s = "";

	while (fgets(buffer, LENGTH, f))
	{
		/* ... */
		lineCount++;
		s += stringc(buffer);
	}

	delete buffer;

	pclose(f);

	return s;
}

/// @brief SystemCall to Container ( multiline )
Container MultiSysCall( const stringc& command, const u32 LENGTH )
{
	stringc s = SingleSysCall( command, LENGTH );
	Container out;
	s.split( out, "\n",1 );
	return out;
}

/// ////////////////////////////////////////////////////////////////////////////
/// @brief SystemCall to Container ( multiline )
/// ////////////////////////////////////////////////////////////////////////////

bool AddLines( Container& out, const stringc& command, const u32 LENGTH)
{
	Container tmp = MultiSysCall( command, LENGTH );
	for (u32 i=0; i<tmp.size(); i++)
		out.push_back( tmp[i] );
	return true;
}


/// container io

/// ////////////////////////////////////////////////////////////////////////////
/// @brief Container to TextFile ( store ram to hdd )
/// ////////////////////////////////////////////////////////////////////////////

bool LoadLines( Container& container, const stringc& filename, const u32 LENGTH )
{
    /// open file
	FILE *f = fopen( filename.c_str(), "r");
	if (!f)	{ printf ( "Could not open file.\n" ); return false; }

	/// create buffer
	c8* b = new c8[LENGTH];
	if (!b) { printf ( "Sorry, but you are out of memory.\n" ); return false; }

	/// read line-count
	u32 lineCount = 0;
	while (fgets(b, LENGTH, f)) { lineCount++; }

	/// process line-count
	printf ( "Loaded file has %d container.\n", lineCount );
	if (lineCount == 0) { fclose(f); return false; }

	/// reallocate container
	container.reallocate( lineCount );
	container.set_used( 0 );

	/// rewind
	fseek( f, 0L, SEEK_SET );

	/// fill container
	while (fgets(b, LENGTH, f)) { container.push_back( stringc(b) ); }

	/// end
	fclose(f);
	if (b) delete b;
	return true;
}

/// ////////////////////////////////////////////////////////////////////////////
/// @brief Container to TextFile ( store ram to hdd )
/// ////////////////////////////////////////////////////////////////////////////

bool StoreLines( const Container& container, const stringc& filename )
{
    /// open file
	FILE *f = fopen( filename.c_str(), "w");
	if (!f)
	{
		printf ( "Could not open temporary write-file.\n" );
		return false;
	}

	u32 i = 0;
	while (f && i<container.size())
	{
		fputs( container[i].c_str(), f );
		// if ( container[i].size() > fputs( container[i].c_str(), f ) )
		// {
		//		printf ( "Maybe some error while reading [%d].\n", i );
		// }
		fputs( "\n", f );
		i++;
	}

	fclose( f );
	f = 0;

	return true;
}
/// ////////////////////////////////////////////////////////////////////////////
/// @brief SystemCall to text-file
/// ////////////////////////////////////////////////////////////////////////////

bool StoreCall( const stringc& command, const stringc& filename, const u32 LENGTH )
{
    /// open shell-pipe
	FILE *_shell = popen( command.c_str(), "r");
	if (!_shell) { printf ( "%s > %s\n", command.c_str(), filename.c_str() ); return false; }

	/// open write-file
	FILE *_file = fopen( filename.c_str(), "w");
	if (!_file)	{ printf ( "Could not open write-file %s.\n", filename.c_str() ); return false; }

	printf ( "%s > %s OK\n", command.c_str(), filename.c_str() );

	/// create linebuffer
	c8* _buffer = new c8[LENGTH];
	if (!_buffer) { printf ( "Sorry, but you are out of memory.\n" ); return false; }

	u32 lineCount = 0;

	while (fgets(_buffer, LENGTH, _shell))
	{
		fputs(_buffer, _file);
		lineCount++;
	}

	delete _buffer;

	pclose(_shell);
	fclose(_file);

	return true;
}


//stringc create_bash_script()
//{
//	stringc c_filename = "/var/tmp/superbuild.sh";
//
//	printf ( "Created temporary file %s\n", c_filename.c_str() );
//	FILE *f = fopen ( c_filename.c_str(), "w" );
//	if (!f)
//	{
//		printf ( "Could not open temporary file.\n" );
//		exit ( -1 );
//	}
//
//	///	[1] Create bash script
//	fprintf ( f, "#!/bin/bash\n" );
//	fprintf ( f, "# Created temporary bash script.\n" );
//	fprintf ( f, "echo \"Hello BashScript!\"\n" );
//	fprintf ( f, "echo \"Hello BashScript!\"\n" );
//	fprintf ( f, "echo \"Hello BashScript!\"\n" );
//	fprintf ( f, "echo \"Hello BashScript!\"\n" );
//	fprintf ( f, "du -sh /Pfad/ordner/\n" );
//	fprintf ( f, "chmod 755 %s\n", c_filename.c_str() );
//	fclose( f );
//	f = 0;
//
//	return c_filename;
//}

/// class CClass -----------------------------------------------------------------------------

///@brief constructor
CClass::CClass(
	const stringc& name,
	const CClass::Attributes& attribs,
	const CClass::Variables& vars,
	const CClass::Functions& funs )

: m_Name(name)
, m_Attributes(attribs)
, m_Variables(vars)
, m_Functions(funs)

{

}

///@brief destructor
CClass::~CClass()
{

}

/// class CClassBuilder -----------------------------------------------------------------------------

///@brief constructor
CClassBuilder :: CClassBuilder( s32 argc, c8** argv )
	: Argc(argc)
	, Argv(argv)
{
	const c8* c_program_name = "ClassBuilder";
	const c8* c_tmp_filename = "cbuilder.tmp";
//	const c8* c_out_filename = "cbuilder.out";
	core::stringc base_dir = "./";
//	const u32 LENGTH = 1024;

	fprintf( stdout, " ***\t\t %s\t\t\t\t*** \n", c_program_name );

	/// add lines to container
	Container filetypes;
	filetypes.push_back( "c" );
	filetypes.push_back( "cc" );
	filetypes.push_back( "cpp" );
	filetypes.push_back( "c++" );
	filetypes.push_back( "h" );
	filetypes.push_back( "hh" );
	filetypes.push_back( "hpp" );
	filetypes.push_back( "h++" );

	Container container;

	fprintf( stdout, " ***\t\t ParameterCount = %d\t\t\t\t*** \n", Argc );

	if (Argc>0)
	{
		for (s32 i=0; i<Argc; i++)
		{
			fprintf( stdout, "Argv[%d] = %s\n", i, Argv[i] );
		}

		if (Argc>=1)
		{
			FindFiles( container, Argv[1], filetypes );
		}
		else
		{
			FindFiles( container, "./", filetypes );
		}

		/// print and save container to file
		Print( container );
		StoreLines( container, c_tmp_filename );
	}

}

///@brief destructor
CClassBuilder::~CClassBuilder()
{

}

/// END OF MODULE -----------------------------------------------------------------------------

} // end namespace core
} // end namespace irr
