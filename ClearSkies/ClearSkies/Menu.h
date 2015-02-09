#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "Button.h"
#include <vector>
#include <map>
#include <Singleton.h>
#include <NonCopyable.h>
class Menu;
typedef Singleton<Menu> TheMenu;
class Menu :public NonCopyable
{
private:
	typedef void (*Callback)();
	typedef bool (*LoadFunction)(const std::string&,Menu&);
public:
	bool Load(std::string load,LoadFunction);
	bool AddButton(Button* button);
	bool AddCall(int tag, Callback c);
	void ClickAt(Vec2f click);
	void MouseMove(Vec2f move);
	void Draw();
	void SetActive(bool b);
	void ClearButtons();
private:
	Menu();
	friend TheMenu;
	typedef std::map<int,Callback> CallTagMap;
	typedef std::vector<Button*> ButtonVec;
	bool isActive_;
	CallTagMap tagMap_;
	ButtonVec buttons_;
	std::string menuName_;
};


#endif