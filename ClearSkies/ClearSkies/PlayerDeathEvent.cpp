#include "PlayerDeathEvent.h"

const char* PlayerDeathEvent::TYPENAME="PlayerDeathEvent";

PlayerDeathEvent::~PlayerDeathEvent()
{}
void PlayerDeathEvent::SetTargetID(int id)
{
	targetID_=id;
}

int PlayerDeathEvent::GetTargetID()const
{
	return targetID_;
}

const char* PlayerDeathEvent::GetEventType()const
{
	return TYPENAME;
}