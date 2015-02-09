#include "Light.h"
#include <gl/glut.h>

Light::Light()
{
number_=0;
position_.resize(4);
position_[3]=1;
ambient_.resize(4);
ambient_[3]=1;
diffuse_.resize(4);
diffuse_[3]=1;
specular_.resize(4);
specular_[3]=1;

linearAt_=0;
constantAt_=1;
quadAt_=0;
}
void Light::Draw()
{
	glLightfv(GL_LIGHT0+number_,GL_POSITION,position_.data());
	glLightfv(GL_LIGHT0+number_,GL_AMBIENT,ambient_.data());
	glLightfv(GL_LIGHT0+number_,GL_DIFFUSE,diffuse_.data());
	glLightfv(GL_LIGHT0+number_,GL_SPECULAR,specular_.data());

	glLightf(GL_LIGHT0+number_,GL_CONSTANT_ATTENUATION,constantAt_);
	glLightf(GL_LIGHT0+number_,GL_LINEAR_ATTENUATION,linearAt_);
	glLightf(GL_LIGHT0+number_,GL_QUADRATIC_ATTENUATION,quadAt_);

}

void Light::SetConAt(float value)
{
	constantAt_=value;
}

void Light::SetLinAt(float value)
{
	linearAt_=value;
}

void Light::SetQuadAt(float value)
{
	quadAt_=value;
}

void Light::Update()
{}

Vec3f Light::GetPos()const
{
return Vec3f(position_[0],position_[1],position_[2]);
}


void Light::SetPos(Vec3f p)
{
	position_[0]=p.x;
	position_[1]=p.y;
	position_[2]=p.z;
}

void Light::SetNumber(int num)
{
number_=num;
}

void Light::SetAmbient(Vec3f am)
{
	ambient_[0]=am.x;
	ambient_[1]=am.y;
	ambient_[2]=am.z;
}

void Light::SetDiffuse(Vec3f di)
{
	diffuse_[0]=di.x;
	diffuse_[1]=di.y;
	diffuse_[2]=di.z;
}

void Light::SetSpecular(Vec3f sp)
{
	specular_[0]=sp.x;
	specular_[1]=sp.y;
	specular_[2]=sp.z;
}