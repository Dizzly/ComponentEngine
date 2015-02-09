#ifndef FLOORCOLLISIONEVENT_H_INCLUDED
#define FLOORCOLLISIONEVENT_H_INCLUDED
#include "Event.h"
#include <SmartPointer.h>
class FloorCollisionEvent: public Event
{
public:
	~FloorCollisionEvent();
	int GetTargetID()const override;
	void SetTargetID(int id)override;
	const char* GetEventType()const override;
public:
	static const char* TYPENAME;
public:
	float floorHeight;
private:
	int targetID_;
};
typedef SmartPointer<FloorCollisionEvent> FloorCollisionEventPtr;


#endif