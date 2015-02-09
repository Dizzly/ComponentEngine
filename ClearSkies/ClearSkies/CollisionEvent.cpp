#include "CollisionEvent.h"

const char* CollisionEvent::TYPENAME="CollisionEvent";

CollisionEvent::CollisionEvent()
{
	collider=NULL;
}

CollisionEvent::~CollisionEvent()
{

}

int CollisionEvent::GetTargetID()const
{
	return targetID_;
}

void CollisionEvent::SetTargetID(int id)
{
	targetID_=id;
}

const char* CollisionEvent::GetEventType()const 
{
	return TYPENAME;
}
