#include "GetActorEvent.h"

const char* GetActorEvent::TYPENAME="GetActorEvent";


GetActorEvent::GetActorEvent()
{
targetID_=0;
}
int GetActorEvent::GetTargetID()const
{
	return targetID_;
}

void GetActorEvent::SetTargetID(int ID)
{
	targetID_=ID;
}

const char* GetActorEvent::GetEventType()const 
{
return TYPENAME;
}
