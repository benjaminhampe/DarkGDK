// thc_skybox.cpp

#include "stdafx.h"

#include "thc_skybox.h"
#include "DarkGDK.h"

#include "thc_image.h"
#include "thc_string.h"
#include "thc_delete.h"
#include "thc_free.h"
#include "thc_is.h"

namespace thc
{

THC_Skybox::THC_Skybox(){}
THC_Skybox::~THC_Skybox(){	terminate();	}

void THC_Skybox::create(float rad_xz, float rad_y,	
						const char * nx, const char * ny, const char * nz, 
						const char * px, const char * py, const char * pz, 
						float ny_ang_x, float ny_ang_y, 
						float py_ang_x, float py_ang_y)
{
	terminate();

	_tex.resize(6);
	_tex_file.resize(6);
	_rad_xz=rad_xz;
	_rad_y=rad_y;
	_ny_ang_x=ny_ang_x;
	_ny_ang_y=ny_ang_y;
	_py_ang_x=py_ang_x;
	_py_ang_y=py_ang_y;

	stringstream s;
	int i,img=0;
	for (i=0; i<6; i++)
	{
		s.str("");
		if (i==0) s<<nx;
		if (i==1) s<<ny;
		if (i==2) s<<nz;
		if (i==3) s<<px;
		if (i==4) s<<py;
		if (i==5) s<<pz;
		
		img=ImageLoad(s.str().c_str(),1);
		if (img==0)
			_tex_file[i]="";
		else				
			_tex_file[i]=s.str();
		_tex[i]=img;
	}
	createObject();
}
void THC_Skybox::create(float rad_xz, float rad_y, int nx, int ny, int nz, int px, int py, int pz, 
						float ny_ang_x, float ny_ang_y, 
						float py_ang_x, float py_ang_y)
{

	terminate();

	_tex.resize(6);
	_tex_file.resize(6);
	_rad_xz=rad_xz;
	_rad_y=rad_y;
	_ny_ang_x=ny_ang_x;
	_ny_ang_y=ny_ang_y;
	_py_ang_x=py_ang_x;
	_py_ang_y=py_ang_y;

	int img=0;
	stringstream s;
	for (int i=0; i<6; i++)
	{
		if (i==0) img=nx;
		if (i==1) img=ny;
		if (i==2) img=nz;
		if (i==3) img=px;
		if (i==4) img=py;
		if (i==5) img=pz;
		
		if(IsImage(img)==false)	
		{	
			_tex[i]=0;
			_tex_file[i]="";
		}
		else					
		{
			s.str("");
			s<<"Texture"<<i<<".png";
			_tex[i]=img;
			_tex_file[i]=s.str();				
		}
		
	}
	createObject();

}
void THC_Skybox::createObject()
{
	// Object
	int obj;
	int mesh;

	// Root
	_obj=FreeObject();
	dbMakeObjectPlain(_obj,2.0f*_rad_xz,2.0f*_rad_y);
	dbOffsetLimb(_obj,0,_rad_xz,0.0f,0.0f);
	dbRotateLimb(_obj,0,0.0f,270.0f,0.0f);

	// Neg Y
	obj=FreeObject();	dbMakeObjectPlain(obj,2*_rad_xz,2*_rad_xz);	dbRotateObject(obj,270.0f,0.0f,0.0f);
	mesh=FreeMesh();	dbMakeMeshFromObject(mesh,obj);				dbDeleteObject(obj);
	dbAddLimb(_obj,1,mesh);	dbOffsetLimb(_obj,1,0.0f,-_rad_y,0.0f);	dbRotateLimb(_obj,1,0.0f,0.0f,0.0f);

	// Neg Z
	obj=FreeObject();	dbMakeObjectPlain(obj,2*_rad_xz,2*_rad_y);	dbRotateObject(obj,0.0f,180.0f,0.0f);
	mesh=FreeMesh();	dbMakeMeshFromObject(mesh,obj);				dbDeleteObject(obj);
	dbAddLimb(_obj,2,mesh);	dbOffsetLimb(_obj,2,0.0f,0.0f,_rad_xz);	dbRotateLimb(_obj,2,0.0f,0.0f,0.0f);

	// Pos X
	obj=FreeObject();	dbMakeObjectPlain(obj,2*_rad_xz,2*_rad_y);	dbRotateObject(obj,0.0f,90.0f,0.0f);
	mesh=FreeMesh();	dbMakeMeshFromObject(mesh,obj);				dbDeleteObject(obj);
	dbAddLimb(_obj,3,mesh);	dbOffsetLimb(_obj,3,-_rad_xz,0.0f,0.0f);	dbRotateLimb(_obj,3,0.0f,0.0f,0.0f);

	// Pos Y
	obj=FreeObject();	dbMakeObjectPlain(obj,2*_rad_xz,2*_rad_xz);	dbRotateObject(obj,90.0f,0.0f,0.0f);
	mesh=FreeMesh();	dbMakeMeshFromObject(mesh,obj);				dbDeleteObject(obj);
	dbAddLimb(_obj,4,mesh);	dbOffsetLimb(_obj,4,0.0f,_rad_y,0.0f);	dbRotateLimb(_obj,4,0.0f,0.0f,0.0f);

	// Pos Z
	obj=FreeObject();	dbMakeObjectPlain(obj,2*_rad_xz,2*_rad_y);	dbRotateObject(obj,0.0f,0.0f,0.0f);
	mesh=FreeMesh();	dbMakeMeshFromObject(mesh,obj);				dbDeleteObject(obj);
	dbAddLimb(_obj,5,mesh);	dbOffsetLimb(_obj,5,0.0f,0.0f,-_rad_xz);	dbRotateLimb(_obj,5,0.0f,0.0f,0.0f);

	// Texture Skybox Limbs
	for (int j=0; j<6; j++)
	{
		dbTextureLimb(_obj,j,_tex[j]);
	}

	dbSetObject(_obj,1,0,0,2,0,0,0);
	dbSetObjectTexture(_obj,2,0);
}

void THC_Skybox::load(const char* pIniFile)
{
	string file=pIniFile;
	string path=STRING_GETPATH(file);

	// Abbruchbedingung
	if (IsFile(file.c_str())==0)
	{
		stringstream err("Die Inidatei existiert nicht : ");	err << file;
		MessageBox(NULL,err.str().c_str(),"Fehler in Skybox::load",0);
		return;
	}

	// Abbruchbedingung
	if (dbPathExist((char*)path.c_str())==0)
	{
		stringstream err("Der Pfad existiert nicht : ");		err << path;
		MessageBox(NULL,err.str().c_str(),"Fehler in Skybox::load",0);
		return;
	}

	// Locale Variablen
	int i;
	float r_xz, r_y, ny_x, ny_y, py_x, py_y;
	char buffer[256];
	vector<string> f(6);
	stringstream s;

	// Open File
	ifstream in(file.c_str());
	//ofstream out("_error_log_skybox.thc");

	// Read File
	for (i=0; i<12; ++i)
	{
//		//Lese Zeile in std::string buffer
//		if (getline(in,buffer))
//		{
		in>>buffer;
			if (i==0)	r_xz=(float)atof(buffer);
			if (i==1)	r_y	=(float)atof(buffer);
			if (i==2)	{s.str(""); s<<path<<"\\"<<buffer; f[0]=s.str();}
			if (i==3)	{s.str(""); s<<path<<"\\"<<buffer; f[1]=s.str();}
			if (i==4)	{s.str(""); s<<path<<"\\"<<buffer; f[2]=s.str();}
			if (i==5)	{s.str(""); s<<path<<"\\"<<buffer; f[3]=s.str();}
			if (i==6)	{s.str(""); s<<path<<"\\"<<buffer; f[4]=s.str();}
			if (i==7)	{s.str(""); s<<path<<"\\"<<buffer; f[5]=s.str();}
			if (i==8)	ny_x=(float)atof(buffer);
			if (i==9)	ny_y=(float)atof(buffer);
			if (i==10)	py_x=(float)atof(buffer);
			if (i==11)	py_y=(float)atof(buffer);
	//	 out << buffer << endl;	
	//	 if (i==2) out<<f[0]<<endl;
	//	 if (i==3) out<<f[1]<<endl;
	//	 if (i==4) out<<f[2]<<endl;
	//	 if (i==5) out<<f[3]<<endl;
	//	 if (i==6) out<<f[4]<<endl;
	//	 if (i==7) out<<f[5]<<endl;

//		}
	}
	in.close();

	create(r_xz,r_y,f[0].c_str(),f[1].c_str(),f[2].c_str(),f[3].c_str(),f[4].c_str(),f[5].c_str(),ny_x,ny_y,py_x,py_y);


}
void THC_Skybox::save(const char* pIniFile)
{
}
void THC_Skybox::terminate()
{
	// Texturen
	if (!_tex.empty())
	{
		for (int i=0; i<(int)_tex.size(); i++)
			if (IsImage(_tex[i]))
				ImageDelete(_tex[i]);
	}
	// Objekt
	if (IsObject(_obj))		ObjectDelete(_obj);

}


}