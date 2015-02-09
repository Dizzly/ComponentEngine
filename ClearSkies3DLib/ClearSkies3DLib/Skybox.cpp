#include "Skybox.h"
#include "Vec3.h"
Skybox::Skybox()
{
	size_=0;
}
bool Skybox::Load(const std::string& filename,const std::string& filetype, float size)
{
	texFront_.Load(filename+"f"+filetype);
	texRight_.Load(filename+"r"+filetype);
	texBack_.Load(filename+"b"+filetype);
	texLeft_.Load(filename+"l"+filetype);
	texUp_.Load(filename+"u"+filetype);
	texDown_.Load(filename+"d"+filetype);

	size_=size;
	return true;
}
Skybox::~Skybox()
{

}
void Skybox::Draw()
{
	float s=size_*0.5f;
	Vec3f mmp(-s,-s,s); //-,-,+;
	Vec3f pmp(s,-s,s); //+,-,+
	Vec3f mpp(-s,s,s); //-,+,+
	Vec3f ppp(s,s,s); //+,+,+
	Vec3f mmm(-s,-s,-s); //-,-,-
	Vec3f pmm(s,-s,-s); //+,-,-
	Vec3f mpm(-s,s,-s); //-,+,-
	Vec3f ppm(s,s,-s); //+,+,-
	GLboolean light;
	GLint lineWidth;
	glGetIntegerv(GL_LINE_WIDTH,&lineWidth);
	glGetBooleanv(GL_LIGHTING,&light);
	if(light)
	{
		glDisable(GL_LIGHTING);
	}
	glDepthMask(0);
	glColor3f(1,1,1);
	glLineWidth(0);
	texBack_.Begin();
	glBegin(GL_QUADS);//back face
	{
		glTexCoord2f(1,1);glVertex3f(mmm.x,mmm.y,mmm.z);
		glTexCoord2f(0,1);glVertex3f(mmp.x,mmp.y,mmp.z);
		glTexCoord2f(0,0);glVertex3f(mpp.x,mpp.y,mpp.z);
		glTexCoord2f(1,0);glVertex3f(mpm.x,mpm.y,mpm.z);
	}
	glEnd();

	texDown_.Begin();
	glBegin(GL_QUADS);//down face
	{
		glTexCoord2f(1,1);glVertex3f(mmm.x,mmm.y,mmm.z);
		glTexCoord2f(0,1);glVertex3f(mmp.x,mmp.y,mmp.z);
		glTexCoord2f(1,0);glVertex3f(pmp.x,pmp.y,pmp.z);
		glTexCoord2f(0,0);glVertex3f(pmm.x,pmm.y,pmm.z);
	}
	glEnd();
	texLeft_.Begin();
	glBegin(GL_QUADS);//left face
	{
		glTexCoord2f(1,1);glVertex3f(pmm.x,pmm.y,pmm.z);
		glTexCoord2f(0,1);glVertex3f(mmm.x,mmm.y,mmm.z);
		glTexCoord2f(0,0);glVertex3f(mpm.x,mpm.y,mpm.z);
		glTexCoord2f(1,0);glVertex3f(ppm.x,ppm.y,ppm.z);
	}
	glEnd();
	texFront_.Begin();
	glBegin(GL_QUADS);//front face
	{
		glTexCoord2f(0,1);glVertex3f(pmm.x,pmm.y,pmm.z);
		glTexCoord2f(1,1);glVertex3f(pmp.x,pmp.y,pmp.z);
		glTexCoord2f(1,0);glVertex3f(ppp.x,ppp.y,ppp.z);
		glTexCoord2f(0,0);glVertex3f(ppm.x,ppm.y,ppm.z);
	}
	glEnd();
	texRight_.Begin();
	glBegin(GL_QUADS);//right face
	{
		glTexCoord2f(1,1);glVertex3f(mmp.x,mmp.y,mmp.z);
		glTexCoord2f(1,0);glVertex3f(mpp.x,mpp.y,mpp.z);
		glTexCoord2f(0,0);glVertex3f(ppp.x,ppp.y,ppp.z);
		glTexCoord2f(0,1);glVertex3f(pmp.x,pmp.y,pmp.z);
	}
	glEnd();
	texUp_.Begin();
	glBegin(GL_POLYGON);// up face
	{
		glTexCoord2f(0,1);glVertex3f(ppp.x,ppp.y,ppp.z);
		glTexCoord2f(1,1);glVertex3f(mpp.x,mpp.y,mpp.z);
		glTexCoord2f(1,0);glVertex3f(mpm.x,mpm.y,mpm.z);
		glTexCoord2f(0,0);glVertex3f(ppm.x,ppm.y,ppm.z);
	}
	glEnd();
	texUp_.End();
	if(light)
	{
		glEnable(GL_LIGHTING);
	}
	glDepthMask(1);
	glLineWidth(lineWidth);
}