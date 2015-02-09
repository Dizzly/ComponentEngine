#ifndef MOVEACTOREVENT_H_INCLUDED
#define MOVEACTOREVENT_H_INCLUDED
#include "Event.h"
#include <Transform.h>

class MoveActorEvent:public Event
{
public:
	int GetTargetID()const override;
	void SetTargetID(int id) override;
	const char* GetEventType()const override;
public:
	static const char* TYPENAME;
public:
	Vec3f pos_;
private:
	int targetID_;
};
typedef SmartPointer<MoveActorEvent> MoveActorEventPtr;


#endif