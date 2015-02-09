#ifndef COLLISIONEVENT_H_INCLUDED
#define COLLISIONEVENT_H_INCLUDED
#include "Event.h"
#include "Collider.h"
#include <SmartPointer.h>
class CollisionEvent: public Event
{
public:
	CollisionEvent();
	~CollisionEvent();
	int GetTargetID()const override;
	void SetTargetID(int id)override;
	const char* GetEventType()const override;
public:
	Collider* collider;
	std::string coltype;
public:
	static const char* TYPENAME;
private:
	int ID_;
	int targetID_;
};
typedef SmartPointer<CollisionEvent> CollisionEventPtr;


#endif