#ifndef GAMEOVERSTATE_H_INCLUDED
#define GAMEOVERSTATE_H_INCLUDED
#include <GameState.h>
#include <Singleton.h>
#include <string>
class GameOverState;
typedef Singleton<GameOverState> TheGameOverState;
class GameOverState:public GameState
{
public:
	void Update()override;
	void Draw()override;
	void OnActive()override;
	void OnInactive()override;
	void OnKeyboardEvent(const SDL_KeyboardEvent& eve)override;
	void OnMouseButtonEvent(const SDL_MouseButtonEvent& mutton)override;
	void OnMouseMotionEvent(const SDL_MouseMotionEvent& moustion)override;
	static void SubmitName();
	static void Replay();

private:
	friend TheGameOverState;
	GameOverState();
private:
	float fadeTime_;
	float controlFreezeTime_;
	static bool getName_;
	static int maxNameLength_;
	static bool allUpperCase_;
	static std::string name_;
};


#endif