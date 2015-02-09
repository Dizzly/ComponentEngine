#include "MoveActorEvent.h"

const char* MoveActorEvent::TYPENAME="MoveActorEvent";

void MoveActorEvent::SetTargetID(int id)
{
targetID_=id;
}

int MoveActorEvent::GetTargetID()const
{
return targetID_;
}

const char*  MoveActorEvent::GetEventType()const
{
	return TYPENAME;
}