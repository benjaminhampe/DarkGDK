
#include "gl.h"

#include <GL/gl.h>
#include <GL/glu.h>

#include "irrTypes.h"
#include "irrMath.h"
using namespace irr;

namespace hampe
{

void glCurve(f64 x[], f64 y[], s32 count, f32 linewidth, u16 pattern, f32 * color)
{
	if (x && y)
	{
		glEnable(GL_LINE_STIPPLE);
		glLineStipple(1, pattern);
		GLfloat oldLineWidth;
		glGetFloatv(GL_LINE_WIDTH,&oldLineWidth);
		glLineWidth(linewidth);
		glBegin(GL_LINES);

		for (s32 c=0; c<count-1; ++c)
		{
			glColor4fv(color);	glVertex3d(x[c],y[c],0);
			glColor4fv(color);	glVertex3d(x[c+1],y[c+1],0);
		}
		glEnd();
		glLineWidth(oldLineWidth);
		glDisable(GL_LINE_STIPPLE);
	}
}
}
