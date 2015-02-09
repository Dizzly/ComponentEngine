#ifndef BRUTESPHERECOLLISION_H_INCLUDED
#define BRUTESPHERECOLLISION_H_INCLUDED
#include <CollisionSystem.h>
//to override the collision system in Game. 
class BruteSphereCollision: public CollisionSystem
{
public:
	void Update(GameObjectMap* gomp)override;
};

#endif