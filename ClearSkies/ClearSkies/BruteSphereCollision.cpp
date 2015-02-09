#include "BruteSphereCollision.h"
#include "CollisionController.h"

void BruteSphereCollision::Update(GameObjectMap* gomp)
{
	TheCollisionController::Instance()->CheckCollisions();
}