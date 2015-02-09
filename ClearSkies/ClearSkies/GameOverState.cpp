#include "GameOverState.h"
#include <EventPoller.h>
#include "Menu.h"
#include "LoadState.h"
#include "ScoreManager.h"
#include <Screen.h>
#include <Game.h>
#include "UIManager.h"
#include "CameraManager.h"
#include <Skybox.h>

bool GameOverState::getName_=false;
std::string GameOverState::name_;
bool GameOverState::allUpperCase_=true;
int GameOverState::maxNameLength_=3;
GameOverState::GameOverState()
{}

void GameOverState::Update()
{
	
}

void GameOverState::Draw()
{
	glClearColor(0,0,0,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	TheScreen::Instance()->SetPerspective();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	TheCameraManager::Instance()->CurrentCam()->UseCameraZeroed();
	TheSkybox::Instance()->Draw();
	glLoadIdentity();
	TheCameraManager::Instance()->CurrentCam()->UseCamera();
	std::string printName=name_;
	if(name_.size()<maxNameLength_)
	{
	printName.push_back('_');
	}
	TheFontManager::Instance()->GetBitUIFont("MenuFont")->DynamicDraw(printName,Vec2f(-0.5,0),Vec2f(0.5,0.2));
	TheFontManager::Instance()->GetBitUIFont("MenuFont")->DynamicDraw("Submit your score!",Vec2f(-0.7,0.3),Vec2f(0.7,0.5));
	
	glColor3f(1,1,1);
	TheGame::Instance()->DrawGameObjects();
	TheMenu::Instance()->Draw();
}

void GameOverState::OnActive()
{
	TheEventPoller::Instance()->AddEventHandler(this);
	getName_=true;
	TheMenu::Instance()->Load("GameOverMenu",TheLoadState::Instance()->LoadMenu);
	TheMenu::Instance()->AddCall(1,SubmitName);
	TheMenu::Instance()->AddCall(2,Replay);
	TheMenu::Instance()->SetActive(true);
}

void GameOverState::OnInactive()
{
	TheEventPoller::Instance()->RemoveEventHandler(this);
	TheMenu::Instance()->SetActive(false);
}

void GameOverState::OnKeyboardEvent(const SDL_KeyboardEvent& eve)
{
	if(eve.state==SDL_PRESSED)
	{
		if(eve.keysym.sym==SDLK_BACKSPACE)
		{
		if(name_.size()>0)
		{
		name_.pop_back();
		}
		return;
		}
		char inputChar=*SDL_GetKeyName(eve.keysym.sym);	
		if(allUpperCase_)
		{
			inputChar=toupper(inputChar);
		}
		if(name_.size()<maxNameLength_&&getName_)
		{
			name_.push_back(inputChar);		
		}
	}
}

void GameOverState::OnMouseButtonEvent(const SDL_MouseButtonEvent& event)
{
	if(event.state==SDL_RELEASED&&event.button==SDL_BUTTON_LEFT)
	{
		Vec2i scr = TheScreen::Instance()->ScreenBounds();
		TheMenu::Instance()->ClickAt(Vec2f(
			(event.x-scr.x*0.5)/(scr.x*0.5),
			(((event.y*-1)+scr.y)-scr.y*0.5)/(scr.y*0.5)));
	}
}

void GameOverState::OnMouseMotionEvent(const SDL_MouseMotionEvent& event)
{
	Vec2i scr = TheScreen::Instance()->ScreenBounds();
	TheMenu::Instance()->MouseMove(Vec2f(
		((float)event.x-(float)scr.x*0.5)/((float)scr.x*0.5),
		((((float)event.y*-1)+(float)scr.y)-(float)scr.y*0.5)/((float)scr.y*0.5)));
}

 void GameOverState::SubmitName()
{
	if(name_.size()==maxNameLength_)
	{
	getName_=false;
	TheScoreManager::Instance()->SaveScore(name_);
	TheScoreManager::Instance()->WriteScores();
	name_.clear();
	}
}

 void GameOverState::Replay()
 {
	if(getName_==false)
	{
		TheGame::Instance()->SetState(TheLoadState::Instance());
	}
	else
	{
		name_="Bot";
	}
 }