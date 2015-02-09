#ifndef PLAYSTATE_H_INCLUDED
#define PLAYSTATE_H_INCLUDED
#include <GameState.h>
#include <Singleton.h>
#include <vector>
#include <GameObject.h>
class PlayState;
typedef Singleton<PlayState> ThePlayState;
class PlayState: public GameState
{
public:
	virtual void Update()override;
	virtual void Draw()override;
	virtual void OnActive()override;
	virtual void OnInactive()override;
	void GameOver();
	void OnKeyboardEvent(const SDL_KeyboardEvent& eve)override;
private:
	PlayState(); 
	friend ThePlayState;
private:
	bool isPaused_;
};

#endif