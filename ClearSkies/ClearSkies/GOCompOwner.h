#ifndef GOCOMPOWNER_H_INCLUDED
#define GOCOMPOWNER_H_INCLUDED
#include "GOComponent.h"
#include <GameObject.h>
#include <map>
#include <string>
class GOCompOwner
{
public:
	GOCompOwner(GameObject* parent);
	~GOCompOwner();
	void AddGOComponent(GOComponent& go);
	void DeleteGOComponent(int id);
	GOComponent* GetGOComponent(const std::string& type);
	GOComponent* GetColliderComponent();
	void UpdateComps();
	void DrawComps()const;
protected:
	typedef std::map<int,GOComponent*> CompMap;
	CompMap compMap_;
	GameObject* parent_;
};

#endif