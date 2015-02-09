#include "PlayerControllerEvent.h"

const char* PlayerControllerEvent::TYPENAME="PlayerControllerEvent";

PlayerControllerEvent::PlayerControllerEvent()
{
	forwards_=1;
	left_=1;
	right_=1;
	backwards_=1;
	fire_=0;
}

PlayerControllerEvent::~PlayerControllerEvent()
{

}

int PlayerControllerEvent::GetTargetID()const
{
	return targetID_;
}

void PlayerControllerEvent::SetTargetID(int ID)
{
	targetID_=ID;
}

const char* PlayerControllerEvent::GetEventType()const
{
return TYPENAME;
}