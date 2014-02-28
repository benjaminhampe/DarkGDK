// Copyright (C) 2002-2013 Benjamin Hampe
// This file is part of the "irrlicht-engine"
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __IRR_EXT_C_CLASS_BUILDER_MANAGER_H__
#define __IRR_EXT_C_CLASS_BUILDER_MANAGER_H__

//#include <sys/stat.h>
//#include <sys/io.h>
//#include <sys/ioctl.h>
//#include <sys/user.h>
//#include <sys/soundcard.h>
//#include <sys/termios.h>

//#include <cstdlib>
//#include <cstdio>
//#include <cmath>
//#include <cstring>
//#include <cstdarg>

#include <irrlicht.h>

#include <cstdio>
#include <stdio.h>


namespace irr{
namespace core{

/// @brief Container == array of stringc
typedef array<stringc> Container;

/// @brief SystemCall to stringc
bool trimLine( stringc& line, u32 loop_count = 3, const c8* char_list = ":./", const u32 char_count = 3 );

/// @brief SystemCall to stringc
stringc SingleSysCall( const stringc& command, const u32 LENGTH = 1024 );

/// @brief SystemCall to Container ( multiline )
Container MultiSysCall( const stringc& command, const u32 LENGTH = 1024 );

/// @brief SystemCall to TextFile ( store shell result to text-file )
bool StoreCall( const stringc& command, const stringc& filename = "./tmp.txt", const u32 LENGTH = 1024 );

/// @brief add output of SystemCall to Container ( ram )
bool AddLines( Container& container, const stringc& command, const u32 LENGTH = 1024 );

/// @brief Container to TextFile ( store ram to hdd )
bool LoadLines( Container& container, const stringc& filename = "./tmp.txt", const u32 LENGTH = 1024 );

/// @brief Container to TextFile ( store ram to hdd )
bool StoreLines( const Container& container, const stringc& filename = "./tmp.txt" );

/// @brief List all files of given extension-list
u32 FindFiles( Container& out, const stringc& rootDir, const Container& fileTypes );

/// @brief Print all lines
void Print( const Container& out );

/// @brief GetDir
stringc GetDir();

/// @brief SetDir
void SetDir( const stringc& new_dir );

enum E_ATTRIBUTES
{
	EAOF_NONE = 0,
	EAOF_UNKNOWN = 1,
	EAOF_PUBLIC = 1<<1,
	EAOF_PROTECTED = 1<<2,
	EAOF_PRIVATE = 1<<3,
	EAOF_STATIC = 1<<4,
	EAOF_CONST = 1<<5,
	EAOF_VIRTUAL = 1<<6,
	EAOF_INLINE = 1<<7
//		EAOF_LVALUE = 1<<8
//		EAOF_REFERENCE = 1<<9
//		EAOF_POINTER = 1<<10
//		EAOF_RValue = 1<<11
//		EAOF_VARIABLE_DEF = 1<<11
//		EAOF_VARIABLE_DECL = 1<<11
//		EAOF_FUNCTION_DEF = 1<<11
//		EAOF_FUNCTION_DECL = 1<<11
//		EAOF_MACRO_DEF = 1<<11
//		EAOF_CLASS = 1<<11
//		EAOF_STRUCT = 1<<11
//		EAOF_INTERFACE = 1<<11
//		EAOF_INTERFACE = 1<<11
};

class CClassAttributes
{
	public:
	u32 Attributes;

	//C++:
	//Bit setzen: var |= 1<<Bitnummer; /* Bitnr ab 0 */
	//Bit loeschen: var &= ~(1<<Bitnummer);

	///@brief Default constructor
	CClassAttributes()
	{
		Attributes = (u32)EAOF_NONE;
		Attributes |= (u32)EAOF_PUBLIC;
		Attributes |= (u32)EAOF_INLINE;
		Attributes |= (u32)EAOF_VIRTUAL;
	}

	///@brief Default constructor
	virtual ~CClassAttributes()
	{
	}

	///@brief Clear All Flags
	virtual CClassAttributes& clear()
	{
		Attributes = (u32)EAOF_NONE;
		return *this;
	}

	///@brief Set public
	virtual CClassAttributes& setUnknown()
	{
		Attributes |= (u32)EAOF_UNKNOWN;
		return *this;
	}

	///@brief Set public
	virtual CClassAttributes& setPublic()
	{
		Attributes |= (u32)EAOF_PUBLIC;
		Attributes &= ~((u32)EAOF_PRIVATE + (u32)EAOF_PROTECTED + (u32)EAOF_STATIC );
		return *this;
	}

	///@brief Set protected
	virtual CClassAttributes& setProtected()
	{
		Attributes |= (u32)EAOF_PROTECTED;
		Attributes &= ~((u32)EAOF_PUBLIC + (u32)EAOF_PRIVATE + (u32)EAOF_STATIC );
		return *this;
	}

	///@brief Set private
	virtual CClassAttributes& setPrivate()
	{
		Attributes |= EAOF_PRIVATE;
		Attributes &= ~((u32)EAOF_PUBLIC + (u32)EAOF_PROTECTED + (u32)EAOF_STATIC );
		return *this;
	}

	///@brief Set static
	virtual CClassAttributes& setStatic()
	{
		Attributes |= ((u32)EAOF_PUBLIC + (u32)EAOF_STATIC);
		Attributes &= ~((u32)EAOF_PROTECTED + (u32)EAOF_PRIVATE );
		return *this;
	}

	///@brief Set virtual
	virtual CClassAttributes& setVirtual()
	{
		Attributes |= (u32)EAOF_VIRTUAL;
		return *this;
	}

	///@brief Set inline
	virtual CClassAttributes& setInline()
	{
		Attributes |= (u32)EAOF_INLINE;
		Attributes &= ~((u32)EAOF_STATIC);
		return *this;
	}

	///@brief Get value member-variable.
	virtual bool isPublic() const
	{
		if ( Attributes & (u32)EAOF_PUBLIC )
			return true;
		else
			return false;
	}

	///@brief Get value member-variable.
	virtual bool isProtected() const
	{
		if ( Attributes & (u32)EAOF_PROTECTED )
			return true;
		else
			return false;
	}

	///@brief Get value member-variable.
	virtual bool isPrivate() const
	{
		if ( Attributes & (u32)EAOF_PRIVATE )
			return true;
		else
			return false;
	}

	///@brief Get value member-variable.
	virtual bool isStatic() const
	{
		if ( Attributes & (u32)EAOF_STATIC )
			return true;
		else
			return false;
	}

	///@brief Get value member-variable.
	virtual bool isVirtual() const
	{
		if ( Attributes & (u32)EAOF_VIRTUAL )
			return true;
		else
			return false;
	}

	///@brief Get value member-variable.
	virtual bool isInline() const
	{
		if ( Attributes & (u32)EAOF_INLINE )
			return true;
		else
			return false;
	}
};

class CBaseVariable : IReferenceCounted
{
	stringc Name;
	stringc Type;
	stringc InitValue;
	CClassAttributes Attributes;
public:
	CBaseVariable(
		const stringc& name = stringc("Variable_"),
		const stringc& type = stringc("u32"),
		const stringc& init = stringc("0"),
		const CClassAttributes& attribs = CClassAttributes())
	: Name(name), Type(type), InitValue(init), Attributes(attribs)
	{
	}
};

class CBaseFunction : IReferenceCounted
{

	stringc Name;
	stringc ReturnType;
	stringc Visibility;	// public, protected, private
	CClassAttributes Attributes;

	typedef array<CBaseVariable> SParameterList;

	SParameterList ParamList;

public:
	CBaseFunction(
		const stringc& name = stringc("NumberingSomething"), // class IUnknown
		const stringc& returntype = stringc("u32"), // types: struct:"struct S", class:"class C", int[erface]:"class I"
		const CClassAttributes& attributes = CClassAttributes())
	: Name(name)
	, ReturnType(returntype)
	, Attributes(attributes)
	{

	}

	~CBaseFunction()
	{
		ParamList.clear();
	}

	virtual void addParam(
		const stringc& name = stringc("Variable_"),
		const stringc& type = stringc("u32"),
		const stringc& init = stringc("0"),
		const CClassAttributes& attribs = CClassAttributes()	)
	{
		ParamList.push_back( CBaseVariable(name, type, init, attribs ) );
	}
};



struct CClassVariable : CBaseVariable
{
	bool HasGetter;
	bool HasConstGetter;
	bool HasSetter;

	CClassVariable(
		const stringc& name = stringc("NumberOfSomething"),
		const stringc& type = stringc("u32"),
		const stringc& init = stringc("0"),
		const CClassAttributes& attribs = CClassAttributes().setVirtual().setInline(),
		bool hasGetter = true,
		bool hasConstGetter = true,
		bool hasSetter = true )
	: CBaseVariable( name, type, init, attribs)
	, HasGetter(hasGetter), HasConstGetter(hasConstGetter), HasSetter(hasSetter)
	{

	}
};

class CClassFunction : public CBaseFunction
{

};

class CClass
{
	typedef array<CClassAttributes> Attributes;
	typedef array<stringc> Lines;
	typedef array<CClassVariable> Variables;
	typedef array<CClassFunction> Functions;

	stringc m_Name;
	Attributes m_Attributes;
	Lines m_Comments;
	Variables m_Variables;
	Functions m_Functions;

public:
	CClass(
		const stringc& name,
		const CClass::Attributes& attribs,
		const CClass::Variables& vars,
		const CClass::Functions& funs );

	virtual ~CClass();

	virtual void addVariable( const CClassVariable& v )
	{
		m_Variables.push_back( v );
	}

	virtual void addFunction( const CClassFunction& f )
	{
		m_Functions.push_back( f );
	}

	virtual void addComment( const stringc& comment = "")
	{
		m_Comments.push_back( comment );
	}

	virtual void addBlock( const stringc& block_name, bool isFolded = false )
	{
		// m_Functions.push_back( my_fun );
	}

	virtual void addMarkDown( const stringc& md_file_or_txt )
	{
		// m_Functions.push_back( my_fun );
	}
};


class CClassBuilder : public IReferenceCounted
{
	s32 Argc;
	c8** Argv;
	array<CClass> Classes;

public:
	CClassBuilder ( s32 argc = 0, c8** argv = 0L );

	~CClassBuilder ();

	///@brief get Pointer to single class.
	///@param index Index of class-array.
	///@return Pointer to single class.
	virtual u32 getClassCount() const
	{
		return Classes.size();
	}

	///@brief get Pointer to single clas.
	///@param index Index of class-array.
	///@return Pointer to single class.
	virtual core::CClass& getClass( u32 index = 0 )
	{
		_IRR_DEBUG_BREAK_IF( index >= getClassCount() )
		return Classes[index];
	}

	///@brief add Class
	///@param id Unique identifier of this text-shape
	///@param name Name of the ISceneNode
	///@return true on success
	virtual bool addClass( const core::CClass& other)
	{
		u32 old_size = Classes.size();
		Classes.push_back( other );
		return (Classes.size()-old_size>0)?true:false;
	}
};


} // end namespace core
} // end namespace irr

#endif // __IRR_EXT_CLASS_BUILDER_H__
