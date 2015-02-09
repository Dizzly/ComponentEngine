#include "GetComponentEvent.h"

const char* GetComponentEvent::TYPENAME="GetComponentEvent";

GetComponentEvent::GetComponentEvent()
{
targetID_=0;
}

GetComponentEvent::~GetComponentEvent()
{

}

int GetComponentEvent::GetTargetID()const
{
return targetID_;
}

void GetComponentEvent::SetTargetID(int id)
{
targetID_=id;
}

const char* GetComponentEvent::GetEventType()const
{
return TYPENAME;
}