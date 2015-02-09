#ifndef MAINMENUSTATE_H_INCLUDED
#define MAINMENUSTATE_H_INCLUDED
#include <Singleton.h>
#include <GameState.h>
#include "Menu.h"
class MainMenuState;
typedef Singleton<MainMenuState> TheMainMenuState;
class MainMenuState:public GameState
{
public:
	virtual void Update()override;
	virtual void Draw()override;
	virtual void OnActive()override;
	virtual void OnInactive()override;
	virtual void OnMouseMotionEvent(const SDL_MouseMotionEvent&);
	virtual void OnMouseButtonEvent(const SDL_MouseButtonEvent&);
	static void Quit();
	static void Play();
private:
	MainMenuState();
	friend TheMainMenuState;
private:
	bool isPaused_;
};



#endif