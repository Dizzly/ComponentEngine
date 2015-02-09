#ifndef EVENT_POLLER_H_INCLUDED
#define EVENT_POLLER_H_INCLUDED
#include <set>
#include "NonCopyable.h"
#include "Singleton.h"

class EventHandler;

class EventPoller;
typedef Singleton<EventPoller> TheEventPoller;

class EventPoller: public NonCopyable
{
public:
    void Update();
    void AddEventHandler(EventHandler*);
    void RemoveEventHandler(EventHandler*);

private:
    EventPoller(){};
    typedef std::set<EventHandler*> Handlers;
    Handlers m_handlers;
    friend TheEventPoller;
};


#endif