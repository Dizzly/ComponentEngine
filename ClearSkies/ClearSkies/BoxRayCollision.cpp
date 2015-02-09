#include "CollisionController.h"
#include "BoxCollider.h"
#include <LineSegment.h>
#include <assert.h>
bool BoxRayCollision(const Collider* obj, const LineSegment* ray)
{
	const BoxCollider* box =dynamic_cast<const BoxCollider*>(obj);
	assert(box);
	if(box)
	{
		Vec3f point=ray->ClosestPoint(box->GetCenter());
		Vec2f xVals=box->XValues();
		Vec2f yVals=box->YValues();
		Vec2f zVals=box->ZValues();
		return (xVals.x<point.x&&
			point.x<xVals.y&&
			yVals.x<point.y&&
			point.y<yVals.y&&
			zVals.x<point.z&&
			point.z<zVals.y);
	}
	return false;
}

static const bool sneakyRay =TheCollisionController::Instance()->AddRayCastCheck(
	BoxRayCollision,std::string(BoxCollider::TYPENAME));