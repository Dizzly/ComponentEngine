#include "EventStore.h"
#include <ReportError.h>
#include <sstream>
#ifdef _DEBUG
#include <iostream>
#endif
EventStore::EventStore()
{}

void EventStore::RemoveID(int id)
{
	eventMap_.erase(id);
	eventQueueMap_.erase(id);
}

bool EventStore::AnnounceEvent(EventPtr eve)
{
	for(EventMap::iterator it=eventQueueMap_.begin();
		it!=eventQueueMap_.end();
		++it)
	{
		it->second.push_back(eve);
	}

/*#ifdef _DEBUG
	std::cout<<"Announce "<<eve->GetEventType()<<"\n";
#endif*/

	return true;
}

bool EventStore::AddID(int id)
{
	EventMap::iterator it=eventMap_.find(id);
	if(it!=eventMap_.end())
	{
		return false;
	}
	else
	{
		eventMap_[id];
		eventQueueMap_[id];
		return true;
	}
}

bool EventStore::AddEvent(EventPtr eve)
{
	EventMap::iterator it= eventQueueMap_.find(eve->GetTargetID());
	if(it==eventQueueMap_.end())
	{
		std::stringstream ss;
		ss<<"Event for ID ";
		ss<<eve->GetTargetID();
		ss<<" with type ";
		ss<<eve->GetEventType();
		ss<<" cannot be found in event map";
		ReportError(ss.str());
		return false;
	}
	else
	{
		it->second.push_back(eve);

/*#ifdef _DEBUG
		std::cout<<eve->GetEventType()<<"\n";
#endif*/
	}
	return true;
}

EventPtrList* EventStore::GetEvents(int id)
{
	EventMap::iterator it=eventQueueMap_.find(id);
	if(it!=eventQueueMap_.end())
	{
		eventMap_[id].insert(eventMap_[id].end(),eventQueueMap_[id].begin(),eventQueueMap_[id].end());
		eventQueueMap_[id].clear();
		return &eventMap_[id];
	}
	else
	{
		std::stringstream ss;
		ss<<"ID ";
		ss<<id;
		ss<<" is not found";
		ReportError(ss.str());
	}
}
