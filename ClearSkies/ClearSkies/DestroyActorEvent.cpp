#include "DestroyActorEvent.h"

const char* DestroyActorEvent::TYPENAME="DestroyActorEvent";

DestroyActorEvent::DestroyActorEvent()
{}

DestroyActorEvent::~DestroyActorEvent()
{

}

int DestroyActorEvent::GetTargetID()const
{
	return targetID_;
}

void DestroyActorEvent::SetTargetID(int id)
{
	targetID_=id;
}

const char* DestroyActorEvent::GetEventType()const
{
return TYPENAME;
}