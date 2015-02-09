#include "CreateActorEvent.h"

const char* CreateActorEvent::TYPENAME="CreateActorEvent";

CreateActorEvent::CreateActorEvent()
{

}

CreateActorEvent::~CreateActorEvent()
{

}

int CreateActorEvent::GetTargetID()const
{
return targetId_;
}

void CreateActorEvent::SetTargetID(int id)
{
targetId_=id;
}

const char* CreateActorEvent::GetEventType()const
{
return TYPENAME;
}