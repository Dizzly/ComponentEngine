#ifndef UIMANAGER_H_INCLUDED
#define UIMANAGER_H_INCLUDED
#include "GOComponent.h"
#include <set>
#include <Singleton.h>
#include <NonCopyable.h>
class UIManager;
typedef Singleton<UIManager> TheUIManager;
class UIManager :public NonCopyable
{
public:
	void AddUIElement(const GOComponent* g);
	void RemoveUIElement(const GOComponent* g);
	void DrawUIElements()const;
private:
	friend TheUIManager;
private:
	UIManager();
	typedef std::set<const GOComponent*> UIElements;
	UIElements uis_;
};

#endif