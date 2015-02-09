#include "SphereCollider.h"
#include "BoxCollider.h"
#include "CollisionController.h"
#include <assert.h>

bool SphereBoxCollision(const Collider* obj1, const Collider* obj2)
{
	const SphereCollider* sphere = dynamic_cast<const SphereCollider*>(obj1);
	const BoxCollider* box =dynamic_cast<const BoxCollider*>(obj2);
	if(!sphere||!box)
	{
		sphere = dynamic_cast<const SphereCollider*>(obj2);
		box =dynamic_cast<const BoxCollider*>(obj1);
	}
	assert(sphere&&box);
	if(sphere&&box)
	{
		Vec2f xVals=box->XValues();
		Vec2f yVals=box->YValues();
		Vec2f zVals=box->ZValues();
		float radius =sphere->GetRad();
		xVals.x-=radius;
		yVals.x-=radius;
		zVals.x-=radius;

		xVals.y+=radius;
		yVals.y+=radius;
		zVals.y+=radius;

		Vec3f point =sphere->GetPos();
		return (xVals.x<point.x&&
			point.x<xVals.y&&
			yVals.x<point.y&&
			point.y<yVals.y&&
			zVals.x<point.z&&
			point.z<zVals.y);

	}

	return false;

}

static const bool sneakyTank =TheCollisionController::Instance()->AddCollisionCheck(
	SphereBoxCollision,CollisionController::TypePair(SphereCollider::TYPENAME,BoxCollider::TYPENAME));
