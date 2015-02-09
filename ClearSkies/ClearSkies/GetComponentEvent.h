#ifndef GETCOMPONENTEVENT_H_INCLUDED
#define GETCOMPONENTEVENT_H_INCLUDED
#include "Event.h"
#include "GOComponent.h"
class GetComponentEvent: public Event
{
public:
	GetComponentEvent();
	~GetComponentEvent();
	int GetTargetID()const override;
	void SetTargetID(int id)override;
	const char* GetEventType()const override;
public:
	static const char* TYPENAME;
	std::string componentType_;
	GOComponent* returnAdress_;
private:
	int targetID_;

};
typedef SmartPointer<GetComponentEvent> GetComponentEventPtr;
#endif