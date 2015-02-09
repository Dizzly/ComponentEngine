#include "CollisionController.h"
#include "SphereCollider.h"
#include <LineSegment.h>
#include <assert.h>


bool SphereRayCollision(const Collider* obj, const LineSegment* ray)
{
	const SphereCollider* sphere =dynamic_cast<const SphereCollider*>(obj);

	assert(sphere);
	if(sphere)
	{
		float dist=ray->SqrdDistance(sphere->GetPos());
		if(dist < (sphere->GetRad()*sphere->GetRad()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

static bool superSneaky= TheCollisionController::Instance()->AddRayCastCheck(
	SphereRayCollision,std::string(SphereCollider::TYPENAME));