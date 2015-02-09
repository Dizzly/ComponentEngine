#ifndef TANKCOMPONENT_H_INCLUDED
#define TANKCOMPONENT_H_INCLUDED
#include "GOComponent.h"
#include "CollisionEvent.h"
class TankComponent:public GOComponent
{
public:
	void Draw()const override;
	void Update()override;
	void Destroy()override;
	bool Load(File& file)override;
	bool Load(GOComponentLO* loadObj)override;
	const char* GetTypeName()const override;
	void PassEvent(EventPtrList* eve)override;
	void PostInit()override;
public:
	static const char* TYPENAME;
private:
	void HandleCollision(CollisionEvent& eve);
	int lives_;
	bool hit_;
	float hitTimer_;
	float timer_;

	float spawnTime_;
	float spawnTimer_;

	float spawnDistance_;
	Vec3f spawnPosition_;

	std::string deathSound_;
	std::string spawningSound_;
};

#endif