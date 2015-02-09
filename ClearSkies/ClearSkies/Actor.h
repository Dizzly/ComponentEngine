#ifndef TANK_H_INCLUDED
#define TANK_H_INCLUDED
#include <Vec3.h>
#include <set>
#include "EventStore.h"
#include <GameObject.h>
#include "GOCompOwner.h"
class Actor:public GameObject, public GOCompOwner
{
public:
	Actor();
	~Actor();
	void Update()override;
	void Draw()const override;
	bool Load(File*)override;
	const char* GetTypeName()const override;
	void SetID(int id) override;
	void SetName(std::string& str);
	bool HasTag(std::string& str) override;
	void AddTag(std::string& str);
	void SetParentID(int id);
	int GetParentID();
	void Destroy() override;
private:
	void PollEvents();
	std::string name_;
	int parentID_;
	typedef std::set<std::string> TagSet;
	TagSet tags_;
	bool isDestro_;
};


#endif