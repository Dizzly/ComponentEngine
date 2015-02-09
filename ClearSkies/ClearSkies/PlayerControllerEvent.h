#ifndef PLAYERCONTROLLEREVENT_H_INCLUDED
#define PLAYERCONTROLLEREVENT_H_INCLUDED
#include <Vec3.h>
#include "Event.h"
class PlayerControllerEvent:public Event
{
public:
	PlayerControllerEvent();
	~PlayerControllerEvent();
	int GetTargetID()const override;
	void SetTargetID(int ID)override;
	const char* GetEventType()const override;
public:
	int forwards_;
	int left_;
	int  right_;
	int backwards_;
	int fire_;
	static const char* TYPENAME;
private:
	int ID_;
	int targetID_;
};
typedef SmartPointer<PlayerControllerEvent> PlayerControllerEventPtr;
#endif