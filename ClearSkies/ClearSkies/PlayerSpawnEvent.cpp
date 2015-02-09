#include "PlayerSpawnEvent.h"

const char* PlayerSpawnEvent::TYPENAME="PlayerSpawnEvent";

PlayerSpawnEvent::~PlayerSpawnEvent()
{}

void PlayerSpawnEvent::SetTargetID(int id)
{
	targetID_=id;
}

int PlayerSpawnEvent::GetTargetID()const
{
	return targetID_;
}

const char* PlayerSpawnEvent::GetEventType()const
{
	return TYPENAME;
}