#ifndef PLAYERSPAWNEVENT_H_INCLUDED
#define PLAYERSPAWNEVENT_H_INCLUDED
#include "Event.h"
#include <SmartPointer.h>
class PlayerSpawnEvent:public Event
{
public:
	~PlayerSpawnEvent();
	int GetTargetID()const override;
	void SetTargetID(int id)override;
	const char* GetEventType()const override;
public:
	int spawnID_;
	int livesLeft_;
	static const char* TYPENAME;
private:
	int targetID_;
};
typedef SmartPointer<PlayerSpawnEvent> PlayerSpawnEventPtr;
#endif