#include "BoxCollider.h"
#include "CollisionController.h"
#include <assert.h>

bool BoxBoxCollision(const Collider* obj1, const Collider* obj2)
{
	const BoxCollider* box1= dynamic_cast<const BoxCollider*>(obj1);
	const BoxCollider* box2= dynamic_cast<const BoxCollider*>(obj2);

	assert(box1&&box2);

	Vec2f box1X=box1->XValues();
	Vec2f box2X=box2->XValues();
	if(box1X.x<box2X.y&&
		box1X.y>box2X.x)
	{
		Vec2f box1Y=box1->YValues();
		Vec2f box2Y=box2->YValues();

		if(box1Y.x<box2Y.y&&
			box1Y.y>box2Y.x)
		{
			Vec2f box1Z=box1->ZValues();
			Vec2f box2Z=box2->ZValues();
			return (box1Z.x<box2Z.y&&
				box1Z.y>box2Z.x);

		}

	}
	return false;

}

static const bool BOXCOLLISIONFUNCTION=TheCollisionController::Instance()->AddCollisionCheck(
	BoxBoxCollision,CollisionController::TypePair(BoxCollider::TYPENAME,BoxCollider::TYPENAME));