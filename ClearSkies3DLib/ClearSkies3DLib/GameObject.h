#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED
#include <string> 
#include <map>
#include "File.h"
#include "Transform.h"

#define GameObject Actor
class GameObject
{
public:
	GameObject(){};
	virtual ~GameObject()=0{};
	virtual void Update()=0{};
	virtual void Draw()const=0{};
	virtual bool Load(File*)=0{};
	virtual void SetID(int id){ID_=id;}
	virtual const int GetID()const{return ID_;}
	virtual const char* GetTypeName()const=0;
	virtual bool HasTag(std::string& str)=0{return false;};
	virtual bool IsActive()const{return isActive_;}
	virtual void Destroy()=0{};
	Transform* GetTransform(){return &transform_;}
	const Transform* GetCTransform()const{return &transform_;}
protected:
	bool isActive_;
	Transform transform_;
	int ID_;

};
typedef std::map<int, GameObject*> GameObjectMap;
#endif