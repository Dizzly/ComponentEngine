#ifndef TANKAICOMPONENT_H_INCLUDED
#define TANKAICOMPONENT_H_INCLUDED
#include "GOComponent.h"
// The main AI component for all enemy tanks, sends movement events to the tank mover.
class TankAIComponent: public GOComponent
{
public:
	TankAIComponent();
	void Draw()const override;
	void Update() override;
	const char* GetTypeName()const override;
	bool Load(File& file);
	bool Load(GOComponentLO* loadObj)override;
	void PassEvent(EventPtrList* eve) override;
	void Destroy() override;
	void PostInit() override;
public:
	static const char* TYPENAME;
private:
	float agroRange_;
	float lockTime_;
	float lockOnTimer_;

	bool sleep_;
	float sleepTime_;
	float sleepTimer_;
	bool aggro_;
	bool lockOn_;

	Vec3f target_;
	const Transform* playerTransform_;
	Transform* parentTransform_;
};


#endif