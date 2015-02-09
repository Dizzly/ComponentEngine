#include "UI.h"
#include <gl/glut.h>
#include <SDL_image.h>
void UI::Init()
{
	SDL_Surface* s=IMG_Load("PicFrame.png");
	tex.Load32Pixes(s);
}
void UI::Draw()
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT_MODEL_TWO_SIDE);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1,1,1);
	tex.Begin();
	glBegin(GL_QUADS);
	{
		glTexCoord2f(0,0);
		glVertex3f(-1,-1,0);
		glTexCoord2f(1,0);
		glVertex3f(-0.5,-1,0);
		glTexCoord2f(1,1);
		glVertex3f(-0.5,-0.5,0);
		glTexCoord2f(0,1);
		glVertex3f(-1,-0.5,0);

	}
	glEnd();
	tex.End();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT_MODEL_TWO_SIDE);

}