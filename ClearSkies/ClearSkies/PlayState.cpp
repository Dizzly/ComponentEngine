#include "PlayState.h"
#include <GameObjectFactory.h>
#include "EventStore.h"
#include <Screen.h>
#include <gl\glut.h>
#include <Skybox.h>
#include "MeshManager.h"
#include <EventPoller.h>
#include "CameraManager.h"
#include "CollisionController.h"
#include "UIManager.h"
#include <Game.h>
#include "ScoreManager.h"
#include "GameOverState.h"
PlayState::PlayState()
{
isPaused_=false;
}

void PlayState::Draw()
{
	glClearColor(0,1,1,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	TheScreen::Instance()->SetPerspective();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	TheCameraManager::Instance()->CurrentCam()->UseCameraZeroed();
	TheSkybox::Instance()->Draw();
	glLoadIdentity();
	TheCameraManager::Instance()->CurrentCam()->UseCamera();
	
	
	glColor3f(1,1,1);
	TheGame::Instance()->DrawGameObjects();
	TheUIManager::Instance()->DrawUIElements();
}

void PlayState::Update()
{
	if(!isPaused_)
	{
	TheGame::Instance()->UpdateGameObjects();
	TheCollisionController::Instance()->CheckCollisions();
	}
}
void PlayState::OnActive()
{
	TheEventPoller::Instance()->AddEventHandler(this);
}

void PlayState::OnInactive()
{
	TheEventPoller::Instance()->RemoveEventHandler(this);
}

void PlayState::OnKeyboardEvent(const SDL_KeyboardEvent& eve)
{
	if(eve.state==SDL_PRESSED)
	{
		if(eve.keysym.sym == SDLK_p)
		{
			isPaused_=!isPaused_;
		}
	}
}

void PlayState::GameOver()
{
	isPaused_=false;
	TheGame::Instance()->SetState(TheGameOverState::Instance());
}