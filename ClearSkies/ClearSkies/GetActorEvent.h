#ifndef GETACTOREVENT_H_INCLUDED
#define GETACTOREVENT_H_INCLUDED
#include "Event.h"
#include "Actor.h"
#include "string"
#include "vector"
#include <SmartPointer.h>

class GetActorEvent: public Event
{
private:
	typedef std::vector<std::string> Tags;
public:
	GetActorEvent();
	int GetTargetID()const override;
	void SetTargetID(int id) override;
	const char* GetEventType()const override;
public:
	static const char* TYPENAME;
	Tags tags;
	int ownerID;
	Actor* collectedActor;
private:
	int targetID_;
};
typedef SmartPointer<GetActorEvent> GetActorEventPtr;
#endif