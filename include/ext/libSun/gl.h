#ifndef HAMPE_OPENGL_H
#define HAMPE_OPENGL_H

#include <irrlicht.h>
using namespace irr;

#include "math.h"
#include "mathe/rect2.h"
#include <GL/gl.h>
#include <GL/glu.h>


namespace hampe
{
// Konstanten fuer DIN Seitenverhaeltnisse
static f32 DIN_A0 = 841.0/1189.0;
static f32 DIN_A1 =  594.0/841.0;
static f32 DIN_A2 =  420.0/594.0;
static f32 DIN_A3 =  297.0/420.0;
static f32 DIN_A4 =  210.0/297.0;
static f32 DIN_A5 =  148.0/210.0;
static f32 DIN_A6 =  105.0/148.0;
static f32 DIN_A7 =   74.0/105.0;
static f32 DIN_A8 =    52.0/74.0;

// Konstanten f�r OpenGl Farben RGBA
static f32 white[4] = { 1, 1, 1, 1 };
static f32 grey[4] = { 0.5, 0.5, 0.5f, 1 };
static f32 black[4] = { 0, 0, 0, 1 };
static f32 red[4] = { 1, 0, 0, 1 };
static f32 green[4] = { 0, 1, 0, 1 };
static f32 blue[4] = { 0, 0, 1, 1 };
static f32 orange[4] = { 1, 0.5, 0, 1 };
static f32 yellow[4] = { 1, 1, 0, 1 };

static f32 light_red[4] = { 1, 0.5, 0.5, 1 };
static f32 light_green[4] = { 0.5, 1, 0.5, 1 };
static f32 light_blue[4] = { 0.5, 0.5, 1, 1 };
static f32 light_yellow[4] = { 1, 1, 0.5, 1 };
static f32 light_grey[4] = { 0.75, 0.75, 0.75, 1 };

static f32 dark_grey[4] = { 0.25, 0.25, 0.25, 1 };
static f32 dark_green[4] = { 0, 0.25, 0, 1 };
static f32 dark_blue[4] = { 0, 0, 0.25, 1 };

static f32 very_light_red[4] = { 1, 0.9, 0.9, 1 };
static f32 very_light_green[4] = { 0.9, 1, 0.9, 1 };
static f32 very_light_blue[4] = { 0.9, 0.9, 1, 1 };
static f32 very_light_yellow[4] = { 1, 1, 0.8, 1 };
static f32 very_light_grey[4] = { 0.9, 0.9, 0.9, 1 };


inline void glRect(f32 x1, f32 y1, f32 x2, f32 y2, f32 *cLT, f32 *cRT, f32 *cRB, f32 *cLB)
{
	glBegin(GL_LINE_LOOP);
        glColor4fv(cLT); glVertex3f(x1,y1,0);
        glColor4fv(cRT); glVertex3f(x2,y1,0);
        glColor4fv(cRB); glVertex3f(x2,y2,0);
        glColor4fv(cLB); glVertex3f(x1,y2,0);
	glEnd();
}

inline void glLine(f32 x1, f32 y1, f32 x2, f32 y2, f32* c1, f32* c2)
{
    glBegin(GL_LINES);
        glColor4fv(c1); glVertex3f((f32)x1,(f32)y1,0);
        glColor4fv(c2); glVertex3f((f32)x2,(f32)y2,0);
    glEnd();
}

inline void glLine(f32 x1, f32 y1, f32 z1, f32 x2, f32 y2, f32 z2, f32 * c1, f32* c2)
{
    glBegin(GL_LINES);
        glColor4fv(c1); glVertex3f(x1,y1,z1);
        glColor4fv(c2); glVertex3f(x2,y2,z2);
    glEnd();
}

inline void glLine(f32 x1, f32 y1, f32 x2, f32 y2, s32 faktor, f32 linewidth, u16 pattern, f32* color)
{
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(faktor, pattern);
    f32 oldLineWidth;
    glGetFloatv(GL_LINE_WIDTH,&oldLineWidth);
    glLineWidth(linewidth);
    glBegin(GL_LINES);
        glColor4fv(color); glVertex3f(x1,y1,0);
        glColor4fv(color); glVertex3f(x2,y2,0);
    glEnd();
    glLineWidth(oldLineWidth);
    glDisable(GL_LINE_STIPPLE);
}

/*
template <class T>
inline void glCurve(const matrix<T>& daten, const Rect2<T>& zoom, s32 w, s32 h, s32 faktor, f32 linewidth, u16 pattern, f32* color)
{
    if (daten.rows()<2) return;
    if (daten.cols()<2) return;
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(faktor, pattern);
	f32 oldLineWidth;
	glGetFloatv(GL_LINE_WIDTH,&oldLineWidth);
	glLineWidth(linewidth);
	glBegin(GL_LINES);
        glColor4fv(color);

	T ww = (T)w;
	T hh = (T)h;

	for (s32 c=0; c<daten.cols()-1; ++c)
	{
        T d1 = daten.get(0,c);
        T d2 = daten.get(1,c);
        T d3 = daten.get(0,c+1);
        T d4 = daten.get(1,c+1);
        f32 x1 = (f32)(ww * (d1-zoom.x1)/zoom.width());
        f32 y1 = (f32)(hh * (d2-zoom.y1)/zoom.height());
        f32 x2 = (f32)(ww * (d3-zoom.x1)/zoom.width());
        f32 y2 = (f32)(hh * (d4-zoom.y1)/zoom.height());

        glVertex3f(x1,y1,0);
        glVertex3f(x2,y2,0);
    }
	glEnd();
	glLineWidth(oldLineWidth);
    glDisable(GL_LINE_STIPPLE);
}
*/

/*
template <class T>
inline void glGrid(const Rect2<T>& zoom, s32 w, s32 h, T stepX, T stepY, s32 faktor, f32 linewidth, GLushort pattern, f32* color)
{
    // Berechne Ursprung
    T ur[2];
	ur[0] = projectToScreenOrtho<T>(T(0),zoom.x1,zoom.x2,w);
	ur[1] = projectToScreenOrtho<T>(T(0),zoom.y1,zoom.y2,h);

	// Berechne Anzahl Netzlinien in den 4 Quadranten
	s32 n[4];
	n[0] = (s32)floor(fabs(zoom.x2-ur[0])/stepX); // [+]
	n[1] = (s32)floor(fabs(zoom.y2-ur[1])/stepY); // [+]
	n[2] = (s32)floor(fabs(ur[0]-zoom.x1)/stepX); // [-]
	n[3] = (s32)floor(fabs(ur[1]-zoom.y1)/stepY); // [-]

    f32 x1(0);
    f32 y1(0);
    f32 x2 = (f32)w;
    f32 y2 = (f32)h;

    // save old state
	f32 oldLineWidth;
	glGetFloatv(GL_LINE_WIDTH,&oldLineWidth);

    // set new state
    glLineWidth(linewidth);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(faktor, pattern);
	glBegin(GL_LINES);


    // 1. Quadrant in X-Richtung
	for (s32 i=0; i<=n[0]; ++i)
	{
        f32 d = (f32)(ur[0]+projectToScreenOrtho<T>(stepX*(T)i, zoom.x1, zoom.x2, w));
        glColor4fv(color);
        glVertex3f(d,y1,0);
        glVertex3f(d,y2,0);
	}

	// 1. Quadrant in Y-Richtung
	for (s32 i=0; i<=n[1]; ++i)
	{
        f32 d = (f32)(ur[1]+projectToScreenOrtho<T>(stepY*(T)i, zoom.y1, zoom.y2, h));
        glColor4fv(color);
        glVertex3f(x1,d,0);
        glVertex3f(x2,d,0);
	}

	// 3. Quadrant in X-Richtung (neg)
	for (s32 i=0; i<=n[2]; ++i)
	{
        f32 d = (f32)(ur[0]+projectToScreenOrtho<T>(-stepX*(T)i, zoom.x1, zoom.x2, w));
        glColor4fv(color);
        glVertex3f(d,y1,0);
        glVertex3f(d,y2,0);
	}

	// 3. Quadrant in Y-Richtung (neg)
	for (s32 i=0; i<=n[3]; ++i)
	{
        f32 d = (f32)(ur[1]+projectToScreenOrtho<T>(-stepY*(T)i, zoom.y1, zoom.y2, h));
        glColor4fv(color);
        glVertex3f(x1,d,0);
        glVertex3f(x2,d,0);
	}

	glEnd();
	glLineWidth(oldLineWidth);
	glDisable(GL_LINE_STIPPLE);
}
*/

void glQuad(f32 x1, f32 y1, f32 z1,
			f32 x2, f32 y2, f32 z2,
			f32 x3, f32 y3, f32 z3,
			f32 x4, f32 y4, f32 z4,
			f32 *rgb1, f32 *rgb2, f32 *rgb3, f32 *rgb4);

//void glCircle(f32 x, f32 y, f32 radius, GLint segments, f32 color[4]);
//
//void glRect(f32 x1, f32 y1, f32 x2, f32 y2, f32 colorLT[4], f32 colorRT[4], f32 colorRB[4], f32 colorLB[4]);
//void glRect(f32 x1, f32 y1, f32 x2, f32 y2, f32 color[4]);
//void glFilledCircle(f32 radius, GLint segments, f32 colorCenter[4], f32 colorOutline[4]);
//void glFilledCircle(f32 radius, GLint segments, f32 color[4]);
//void glFilledRect(f32 x1, f32 y1, f32 x2, f32 y2, f32 colorLT[4], f32 colorRT[4], f32 colorRB[4], f32 colorLB[4]);
//void glFilledRect(f32 x1, f32 y1, f32 x2, f32 y2, f32 color[4]);
//void glGrid(f32 x1, f32 y1, f32 x2, f32 y2, f32 stepX, f32 stepY, f32 linewidth, GLint factor, GLushort pattern, f32 color[4]);
void glCurve(f64 x[], f64 y[], s32 count, f32 linewidth, u16 pattern, f32 * color);
//void glCoordsystem(f32 x1, f32 x2, f32 y1, f32 y2, f32 stepX, f32 stepY, GLint width, GLint height, GLint marksize, f32 color[4]);
//
//void glDrawSphere(f32 radius, GLint polyCountX, GLint polyCountY);
//GLuint dlDrawSphere(f32 radius, GLint polyCountX, GLint polyCountY);
//
//GLuint dlCircle(f32 x, f32 y, f32 radius, GLint segments, f32 color[4]);
//GLuint dlRect(f32 x1, f32 y1, f32 x2, f32 y2, f32 colorLT[4], f32 colorRT[4], f32 colorRB[4], f32 colorLB[4]);
//GLuint dlRect(f32 x1, f32 y1, f32 x2, f32 y2, f32 color[4]);
//GLuint dlFilledCircle(f32 radius, GLint segments, f32 colorCenter[4], f32 colorOutline[4]);
//GLuint dlFilledCircle(f32 radius, GLint segments, f32 color[4]);
//GLuint dlFilledRect(f32 x1, f32 y1, f32 x2, f32 y2, f32 colorLT[4], f32 colorRT[4], f32 colorRB[4], f32 colorLB[4]);
//GLuint dlFilledRect(f32 x1, f32 y1, f32 x2, f32 y2, f32 color[4]);
//GLuint dlGrid(f32 x1, f32 y1, f32 x2, f32 y2, f32 stepX, f32 stepY, f32 linewidth, GLint factor, GLushort pattern, f32 color[4]);
//GLuint dlCurve(f32 x[], f32 y[], GLuint count, f32 linewidth, GLushort pattern, f32 color[4]);
//GLuint dlCoordsystem(f32 x1, f32 x2, f32 y1, f32 y2, f32 stepX, f32 stepY, GLint width, GLint height, GLint marksize, f32 color[4]);
//
//template <class f32>
//class vertex3
//{
//	public:
//		vertex3(f32 xPos = (f32)0, f32 yPos = (f32)0, f32 zPos = (f32)0,
//				f32 xNormal = (f32)0, f32 yNormal = (f32)1, f32 zNormal = (f32)0,
//				f32 Color[4] = white, f32 texUCoord = (f32)0, f32 texVCoord = (f32)0)
//			:	x(xPos), y(yPos), z(zPos), nx(xNormal), ny(yNormal), nz(zNormal), color(Color), u(texUCoord), v(texVCoord)
//		{}
//
//		~vertex3()
//		{}
//
//	f32 x,y,z,nx,ny,nz,u,v;
//	f32 color[4];
//
//	vertex3<f32>&	operator= (const vertex3<f32> &other)
//	//===========================================
//	{
//		if (&other==this) return *this;
//		x = other.x;
//		y = other.y;
//		z = other.z;
//		nx = other.nx;
//		ny = other.ny;
//		nz = other.nz;
//		u = other.u;
//		v = other.v;
//		return *this;
//	}
//};
//
//template <class f32>
//class quad3
//{
//	public:
//		quad3(vertex3<f32> A = vertex3<f32>(), vertex3<f32> B = vertex3<f32>(), vertex3<f32> C = vertex3<f32>(), vertex3<f32> D = vertex3<f32>())
//			:	a(A), b(B), c(C), d(D)
//		{}
//
//		~quad3()
//		{}
//
//	vertex3<f32> a,b,c,d;
//
//	quad3<f32>& operator= (const quad3<f32> &other)
//	//===========================================
//	{
//		if (&other==this) return *this;
//		a = other.a;
//		b = other.b;
//		c = other.c;
//		d = other.d;
//		return *this;
//	}
//
//};



} // END NAMESPACE
#endif
