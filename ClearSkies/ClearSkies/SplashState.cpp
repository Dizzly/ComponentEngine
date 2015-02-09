#include "SplashState.h"
#include <gl\glut.h>
#include <AngleConvert.h>
#include <Screen.h>
#include "MainMenuState.h"
#include <Game.h>
#include <EventPoller.h>
#include "FontManager.h"
#include "MeshManager.h"
#include <Skybox.h>
#include "GraphicsOptions.h"
SplashState::~SplashState()
{
}

SplashState::SplashState()
{

}

void SplashState::Update()
{}

void SplashState::Draw()
{
	static float aX;
	static float aZ;
	static float add=0.5;
	static float x=0;

	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	TheScreen::Instance()->SetPerspective();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	x+=add;
	aX=cos(DegToRad(x))*4;
	aZ=sin(DegToRad(x))*4;
	glColor3f(1,1,1);

	gluLookAt(aX,-0.7,aZ,
		0,0,0,
		0,1,0);
	TheSkybox::Instance()->Draw();
	glPushMatrix();
	{
		if(GraphicsOptions::WIREFRAME_MODELS)
		{
			glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
			glColor3f(0,1,0);
		}
		ObjMesh* m=TheMeshManager::Instance()->GetMesh(planeMeshTag_);
		glScaled(0.01,0.01,0.01);
		m->Draw();
		if(GraphicsOptions::WIREFRAME_MODELS)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
			glColor3f(1,1,1);
		}
	}
	glPopMatrix();

	glPushMatrix();
	{
		BitmapFontUI* andes=TheFontManager::Instance()->GetBitUIFont(splashFontTag_);
		andes->DynamicDraw("Tonks",Vec2f(-0.6,0.3),Vec2f(0.5,0));
		andes->DynamicDraw("Press any key to continue...",Vec2f(-0.7,-0.3),Vec2f (0.7,-0.4));
	}
	glPopMatrix();
}

void SplashState::OnActive()
{
	planeMeshTag_="TankMesh";
	splashFontTag_="MenuFont";
	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LIGHT0);
	TheEventPoller::Instance()->AddEventHandler(this);
}

void SplashState::OnInactive()
{
	TheEventPoller::Instance()->RemoveEventHandler(this);
}

void SplashState::OnKeyboardEvent(const SDL_KeyboardEvent& event){

	if(event.state==SDL_RELEASED)
	{
		TheGame::Instance()->SetState(TheMainMenuState::Instance());
	}
}

void SplashState::OnMouseButtonEvent(const SDL_MouseButtonEvent& event)
{
	if(event.state==SDL_RELEASED)
	{
		TheGame::Instance()->SetState(TheMainMenuState::Instance());
	}
}