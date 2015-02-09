#include "FloorCollisionEvent.h"

const char* FloorCollisionEvent::TYPENAME="FloorCollisionEvent";

FloorCollisionEvent::~FloorCollisionEvent()
{
	floorHeight=0;
}

void FloorCollisionEvent::SetTargetID(int id)
{
	targetID_=id;
}

int FloorCollisionEvent::GetTargetID()const
{
	return targetID_;
}

const char* FloorCollisionEvent::GetEventType()const
{
	return TYPENAME;
}