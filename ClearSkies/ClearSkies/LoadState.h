#ifndef LOADSTATE_H_INCLUDED
#define LOADSTATE_H_INCLUDED
#include <Singleton.h>
#include <GameState.h>
#include "FontManager.h"
#include <vector>
#include <map>
#include "Menu.h"
#include <AudioManager.h>

class LoadState;
typedef Singleton<LoadState> TheLoadState;
class LoadState:public GameState
{
public:
	~LoadState();
	virtual void Update()override;
	virtual void Draw()override;
	virtual void OnActive()override;
	virtual void OnInactive()override;
	static bool LoadMenu(const std::string&, Menu&);
public:
	std::map<std::string,Mix_Chunk*> soundsMap;
private:
	LoadState();
	friend TheLoadState;
private:
	typedef std::vector<Button*> ButtonPVec;
	typedef std::map<std::string,ButtonPVec> ButtonVecMap;
	static ButtonVecMap buttonMap_;
	bool shouldRestart_;
};

#endif