#include "MainMenuState.h"
#include <EventPoller.h>
#include "Menu.h"
#include "LoadState.h"
#include <Game.h>
#include <Screen.h>
#include "PlayState.h"

MainMenuState::MainMenuState()
{}

void MainMenuState::Update()
{

}

void MainMenuState::Draw()
{
	TheMenu::Instance()->Draw();
}

void MainMenuState::OnActive()
{
	TheEventPoller::Instance()->AddEventHandler(this);
	TheMenu::Instance()->Load("MainMenu",TheLoadState::Instance()->LoadMenu);
	TheMenu::Instance()->AddCall(1,Quit);
	TheMenu::Instance()->AddCall(2,Play);
	TheMenu::Instance()->SetActive(true);
}

void MainMenuState::OnInactive()
{
	TheEventPoller::Instance()->RemoveEventHandler(this);
	TheMenu::Instance()->SetActive(false);
}

void MainMenuState::OnMouseMotionEvent(const SDL_MouseMotionEvent& event)
{
	Vec2i scr = TheScreen::Instance()->ScreenBounds();
	TheMenu::Instance()->MouseMove(Vec2f(
		((float)event.x-(float)scr.x*0.5)/((float)scr.x*0.5),
		((((float)event.y*-1)+(float)scr.y)-(float)scr.y*0.5)/((float)scr.y*0.5)));
}

void MainMenuState::OnMouseButtonEvent(const SDL_MouseButtonEvent& event)
{
	if(event.state==SDL_RELEASED&&event.button==SDL_BUTTON_LEFT)
	{
		Vec2i scr = TheScreen::Instance()->ScreenBounds();
		TheMenu::Instance()->ClickAt(Vec2f(
			(event.x-scr.x*0.5)/(scr.x*0.5),
			(((event.y*-1)+scr.y)-scr.y*0.5)/(scr.y*0.5)));
	}
}

void MainMenuState::Quit()
{
	exit(0);
}

void MainMenuState::Play()
{
	TheGame::Instance()->SetState(ThePlayState::Instance());
}