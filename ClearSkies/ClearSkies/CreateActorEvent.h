#ifndef CREATEACTOREVENT_H_INCLUDED
#define CREATEACTOREVENT_H_INCLUDED
#include "Event.h"
#include <SmartPointer.h>
#include "Actor.h"
class CreateActorEvent: public Event
{
public:
	CreateActorEvent();
	~CreateActorEvent();
	int GetTargetID()const override;
	void SetTargetID(int id) override;
	const char* GetEventType()const override;
public:
	static const char* TYPENAME;
public:
	Actor* createdActor;
	int targetId_;
};
typedef SmartPointer<CreateActorEvent> CreateActorEventPtr;

#endif