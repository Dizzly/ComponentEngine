#include "Billboard.h"
#include <gl/glut.h>
#include "Vec3.h"
void Billboard::Draw()
{
	glPushMatrix();
	glTranslatef(pos_.x,pos_.y,pos_.z);
	float f[16];
	glGetFloatv(GL_MODELVIEW_MATRIX,f);
	Vec3f right(f[0],f[4],f[8]);
	Vec3f up(f[1],f[5],f[9]);
	right*=sideLength_.x;
	up*=sideLength_.y;
	Vec3f corners[4]=
	{
		right+up,
		right-up,
		-right-up,
		-right+up
	};
	glBegin(GL_QUADS);
	{
		glTexCoord2f(1,0);
		glVertex3f(corners[0].x,corners[0].y,corners[0].z);
		glTexCoord2f(1,1);
		glVertex3f(corners[1].x,corners[1].y,corners[1].z);
		glTexCoord2f(0,1);
		glVertex3f(corners[2].x,corners[2].y,corners[2].z);
		glTexCoord2f(0,0);
		glVertex3f(corners[3].x,corners[3].y,corners[3].z);
	}
	glEnd();
	glPopMatrix();
}

void Billboard::SetPos(Vec3f pos)
{
pos_=pos;
}
void Billboard::SetSideLength(Vec2f vec)
{
sideLength_=vec;
}

Vec2f Billboard::GetSideLength()const
{
return sideLength_;
}