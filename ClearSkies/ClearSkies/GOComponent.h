#ifndef GOCOMPONENT_H_INCLUDED
#define GOCOMPONENT_H_INCLUDED
#include "EventStore.h"
#include <GameObject.h>
#include "File.h"
#include "SmartPointer.h"
// the base load object class. This is used to load objects at runtime
class GOComponentLO
{
public:
	virtual ~GOComponentLO()=0{};
	virtual const char* GetTypeName()const=0{};
};
// the base component class, nice and abstract. 
// two load functions for both file loading and the load object
// Destroy is to wrap up the class, mostly removing it from other managers
class GOComponent
{
public:
	virtual void Draw()const=0{};
	virtual void Update()=0{};
	virtual const char* GetTypeName()const=0{}
	virtual bool Load(File& file)=0{}
	virtual bool Load(GOComponentLO* loadObject)=0{}
	virtual void Destroy()=0{};
	virtual void PassEvent(EventPtrList* eve)=0{}
public:
	virtual void SetID(int id){ID_=id;}
	void SetParentID(GameObject* g){parent_=g;}
	int GetParentID(){return parent_->GetID();}
	virtual void PostInit(){};
	virtual const int GetID()const{return ID_;}

	virtual bool IsActive()const{return isActive_;}
	virtual bool ShouldDraw()const{return shouldDraw_;}
	virtual bool ShouldUpdate()const{return shouldUpdate_;}
	
	GOComponent(){isActive_=true;
	shouldDraw_=true;
	shouldUpdate_=true;
	}
	virtual ~GOComponent(){}
protected:
	int ID_;
	GameObject* parent_;
	bool isActive_;
	bool shouldDraw_;
	bool shouldUpdate_;
};
typedef SmartPointer<GOComponent> GOComponentPtr;


#endif