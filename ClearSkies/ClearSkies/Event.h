#ifndef EVENT_H_INCLUDED
#define EVENT_H_INCLUDED
#include <string>
#include <list>
#include <SmartPointer.h>
class Event: public RefCounted
{
public:
	Event(){};
	virtual ~Event(){};
	virtual int GetTargetID()const=0{}
	virtual void SetTargetID(int id)=0;
	virtual const char* GetEventType()const=0{};
private:
};
typedef SmartPointer<Event> EventPtr;
typedef std::list<EventPtr> EventPtrList;
typedef std::list<Event> EventList;

#endif