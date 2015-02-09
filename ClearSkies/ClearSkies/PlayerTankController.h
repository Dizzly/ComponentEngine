#ifndef PLAYERTANKCONTROLLER_H_INCLUDED
#define PLAYERTANKCONTROLLER_H_INCLUDED
#include <EventHandler.h>
#include "GOComponent.h"
#include <map>
#include <string>
//SDL based inputs, checking against the keybinds that its loaded in.
// there are 3 states, down, up and no change. No change is necessary because when you read an event it sets its  value to it
class PlayerTankController: public GOComponent, public EventHandler
{
public:
	enum PLAYERKEY {KEY_UP=0,KEY_DOWN};
	~PlayerTankController();
	PlayerTankController();
	bool Load(File& file)override;
		bool Load(GOComponentLO* loadObj)override;
	void Update()override;
	void Draw()const override;
	void OnKeyboardEvent(const SDL_KeyboardEvent&)override;
	void OnMouseMotionEvent(const SDL_MouseMotionEvent&) override;
	void OnMouseButtonEvent(const SDL_MouseButtonEvent&) override;
	const char* GetTypeName()const;
	void Destroy()override;
	void PassEvent(EventPtrList*)override;
	void SetKeybind(std::string bind, SDLKey key);
public:
	static const char* TYPENAME;
private:
	typedef std::map<SDLKey,std::string> KeyBindingMap;
	KeyBindingMap keyBinds_;

};
#endif