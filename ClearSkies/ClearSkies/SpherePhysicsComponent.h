#ifndef PHYSICSCOMPONENT_H_INCLUDED
#define PHYSICSCOMPONENT_H_INCLUDED
#include "GOComponent.h"
#include "FloorCollisionEvent.h"
class SpherePhysicsComponentLO:public GOComponentLO
{
public:
	~SpherePhysicsComponentLO();
	SpherePhysicsComponentLO();
	const char* GetTypeName()const override;
public:
	static const char* TYPENAME;
public:
	bool loadVelocity;
	Vec3f velocity;

	bool loadGravity;
	Vec3f gravity;

	bool loadGlobalGravity;
	Vec3f globalGravity;

	bool loadRestitution;
	float restitution;

	bool loadFriction;
	float friction;

	bool loadRotation;
	Vec3f rotation;

};

class SpherePhysicsComponent: public GOComponent
{
public:
	~SpherePhysicsComponent();
	void Update()override;
	void Draw()const override;
	void Destroy() override;
	bool Load(File& file) override;
	bool Load(GOComponentLO* loadComp) override;
	const char* GetTypeName()const override;
	void PassEvent(EventPtrList* eve)override;
	void PostInit();
public:
	static const char* TYPENAME;
private:
	Vec3f velocity_;
	Vec3f gravity_;
	static Vec3f globalGravity_;
	float restitution_;
	float friction_;
	Vec3f rotation_;
	
	Transform* parentTransform_;
};


#endif