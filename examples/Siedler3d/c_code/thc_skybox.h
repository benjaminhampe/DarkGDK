// thc_skybox.h

#ifndef __THC_SKYBOX_H_INCLUDED__
#define __THC_SKYBOX_H_INCLUDED__

#include "stdafx.h"

namespace thc
{
	class THC_Skybox
	{
	public:
		THC_Skybox();
		~THC_Skybox();

		void create(float rad_xz, float rad_y,	
					const char * nx, const char * ny, const char * nz, 
					const char * px, const char * py, const char * pz, 
					float ny_ang_x, float ny_ang_y, 
					float py_ang_x, float py_ang_y);

		void create(float rad_xz, float rad_y, int nx, int ny, int nz, int px, int py, int pz, 
					float ny_ang_x, float ny_ang_y, 
					float py_ang_x, float py_ang_y);
		
		void load(const char* pIniFile);
		void save(const char* pIniFile);
		void terminate();

	private:
		void createObject();

		int    _obj;				// Object Nummer
		float  _rad_xz;			// Radius der Grundfläche -> Quadratisch
		float  _rad_y;				// Radius der Höhe
		vector<string>	_tex_file;	// 0=nx, 1=ny, 2=nz, 3=px, 4=py, 5=pz
		vector<int>		_tex;		// 0=nx, 1=ny, 2=nz, 3=px, 4=py, 5=pz
		float  _ny_ang_x;	// Winkel
		float  _ny_ang_y;	// Winkel
		float  _py_ang_x;	// Winkel
		float  _py_ang_y;	// Winkel
		float  _x,_y,_z;     // Position
		

	};
}

#endif



/*
		void create(float rad_xz=1000.0f, 
					float rad_y=1000.0f, 
					const char * nx="", const char * ny="", const char * nz="", 
					const char * px="", const char * py="", const char * pz="", 
					float ny_ang_x=0.0f, float ny_ang_y=0.0f, 
					float py_ang_x=0.0f, float py_ang_y=0.0f);

		void create(float rad_xz=1000.0f, 
					float rad_y=1000.0f, 
					int nx=0, int ny=0, int nz=0, 
					int px=0, int py=0, int pz=0, 
					float ny_ang_x=0.0f, float ny_ang_y=0.0f, 
					float py_ang_x=0.0f, float py_ang_y=0.0f);
					*/