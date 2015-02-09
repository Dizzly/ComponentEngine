#ifndef PLAYERDEATHEVENT_H_INCLUDED
#define PLAYERDEATHEVENT_H_INCLUDED
#include "Event.h"
#include <SmartPointer.h>
class PlayerDeathEvent:public Event
{
public:
	~PlayerDeathEvent();
	int GetTargetID()const override;
	void SetTargetID(int id)override;
	const char* GetEventType()const override;
public:
	int deathID_;
	static const char* TYPENAME;
private:
	int targetID_;
};
typedef SmartPointer<PlayerDeathEvent> PlayerDeathEventPtr;
#endif