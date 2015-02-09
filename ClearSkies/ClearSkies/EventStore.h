#ifndef EVENTSTORE_H_INCLUDED
#define EVENTSTORE_H_INCLUDED
#include <Singleton.h>
#include <NonCopyable.h>
#include "Event.h"
#include <map>
class EventStore;
typedef Singleton<EventStore> TheEventStore;
//memory issue, where do I declare the memorys on the heap?
class EventStore:public NonCopyable
{
private:
	typedef std::map<int,EventPtrList> EventMap;
public:
	bool AddID(int id);
	void RemoveID(int id);
	bool AddEvent(EventPtr eve);
	bool AnnounceEvent(EventPtr eve);
	EventPtrList* GetEvents(int id);
	void ClearEvents(int id);
private:
	EventStore();
	friend TheEventStore;
	EventMap eventMap_;
	EventMap eventQueueMap_;

};

#endif