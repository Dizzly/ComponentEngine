#ifndef SPLASHSTATE_H_INCLUDED
#define SPLASHSTATE_H_INCLUDED
#include <Singleton.h>
#include <GameState.h>
#include <ObjMesh.h>
class SplashState;
typedef Singleton<SplashState> TheSplashState;
class SplashState: public GameState
{
public:
	~SplashState();
	void Update()override;
	void Draw()override;
	void OnActive()override;
	void OnInactive()override;
	void OnKeyboardEvent(const SDL_KeyboardEvent&)override;
	void OnMouseButtonEvent(const SDL_MouseButtonEvent&)override;
private:
	std::string splashFontTag_;
	std::string planeMeshTag_;
	SplashState();
	friend TheSplashState;
};


#endif