#include "CollisionController.h"
#include "SphereCollider.h"
#include <assert.h>


bool SphereSphereCollision(const Collider* obj1, const Collider* obj2)
{
	const SphereCollider* sphere1 = dynamic_cast<const SphereCollider*>(obj1);
	const SphereCollider* sphere2 = dynamic_cast<const SphereCollider*>(obj2);
	
	assert(sphere1&&sphere2);
	if(sphere1&&sphere2)
	{
		Vec3f vec=sphere1->GetPos()-sphere2->GetPos();
		float sqrRadSum=((sphere1->GetRad()+sphere2->GetRad())*(sphere1->GetRad()+sphere2->GetRad()));
		return sqrRadSum>=vec.SqrLength();
	}
	return false;
}

static bool sneaky =TheCollisionController::Instance()->AddCollisionCheck(
	SphereSphereCollision,CollisionController::TypePair(SphereCollider::TYPENAME,SphereCollider::TYPENAME));
