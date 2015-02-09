#include "HomebrewShapes.h"
#include "AngleConvert.h"
#include <gl/glut.h>
void DrawCircle(Vec2f pos,float radius)
{
	glBegin(GL_LINE_LOOP);
	{
		for(int i=0;i<360;++i)
		{
			float angle=i*DegToRad(1);
			glVertex3f((cos(angle)*radius)+pos.x,
				0,(sin(angle)*radius)+pos.y);
		}
	}
	glEnd();
}