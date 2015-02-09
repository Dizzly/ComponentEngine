#include "Screen.h"
#include "Vec4.h"
#include <gl/glut.h>
Screen::Screen()
{
    m_screenLoc=0;
	m_isOpenGL=false;
}

bool Screen::InFrustrum(Matrix m,Vec3f pos)
{
	Vec4f clipper(pos,1);
	m.Multiply(clipper);
	return abs((int)clipper.x) < clipper.w &&
		abs((int)clipper.y) < clipper.w&&
		0<clipper.z &&
		clipper.z < clipper.w;
}
void Screen::SetPerspective()
{
gluPerspective(60.0f,m_screenWidth/m_screenHeight,1.0f,75.0f);
}

bool Screen::Init(int w, int h, unsigned int flag)
{
	if(flag==SDL_OPENGL)
	{
	m_isOpenGL=true;
	SDL_SetVideoMode(w,h,0,flag);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f,w/h,1.0,1000.0);
	}
	else
	{
    m_screenLoc=SDL_SetVideoMode(w,h,0,flag);
	}
    SDL_WM_SetCaption("Window",NULL);
    m_screenWidth=w;
    m_screenHeight=h;
    m_flag=flag;
    return (m_screenLoc!=0);
}


void Screen::Clear()
{
	if(m_isOpenGL)
	{
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	}
	else
	{
    SDL_FillRect( SDL_GetVideoSurface(), NULL, 0 );
	}
}

SDL_Surface*Screen::GetScreen() const
{
    return m_screenLoc;
}

void Screen::Flip()
{
	if(m_isOpenGL)
	{
		SDL_GL_SwapBuffers();
	}
	else
	{
		SDL_Flip(m_screenLoc);
	}
}

Vec2<int> Screen::ScreenBounds()
{
    Vec2<int> temp(m_screenWidth,m_screenHeight);
    return temp;
}

