#ifndef LIFETIMECOMPONENT_H_INCLUDED
#define LIFETIMECOMPONENT_H_INCLUDED
#include "GOComponent.h"

class LifetimeComponentLO:public GOComponentLO
{
public:
	~LifetimeComponentLO();
	LifetimeComponentLO();
	const char* GetTypeName()const override;
public:
	static const char* TYPENAME;
public:
	bool engageTimer;
	bool loadMaxTime;
	float maxTime;
};

class LifetimeComponent:public GOComponent
{
public:
	LifetimeComponent();
	void Draw()const override;
	void Update()override;
	void Destroy()override;
	void PassEvent(EventPtrList* eve)override;
	bool Load(File& file)override;
	bool Load(GOComponentLO* compLoad)override;
	const char* GetTypeName()const override;
	void PostInit();
public:
	static const char* TYPENAME;
private:
	bool isTimeing_;
	int parentID_;
	float timer_;
	float maxTime_;
};

#endif