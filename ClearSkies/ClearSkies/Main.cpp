#include <stdlib.h>
#include <Game.h>
#include <SDL.h>
#include <Screen.h>
#include <AudioManager.h>

#include "LoadState.h"


int main(int, char**)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TheScreen::Instance()->Init(1280,720,SDL_OPENGL);
	TheAudioManager::Instance()->Init();
	TheGame::Instance()->SetState(TheLoadState::Instance());
	TheGame::Instance()->Run();
	SDL_Quit();
	return 0;
}