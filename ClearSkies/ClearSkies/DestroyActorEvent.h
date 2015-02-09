#ifndef DESTROYACTOREVENT_H_INCLUDED
#define DESTROYACTOREVENT_H_INCLUDED
#include "Event.h"
#include <SmartPointer.h>
class DestroyActorEvent: public Event
{
public:
	DestroyActorEvent();
	~DestroyActorEvent();
	int GetTargetID()const override;
	void SetTargetID(int id) override;
	const char* GetEventType()const;
public:
	static const char* TYPENAME;
public:
	int destroyActorID_;
private:
	int ID_;
	int targetID_;
	
};
typedef SmartPointer<DestroyActorEvent> DestroyActorEventPtr;

#endif