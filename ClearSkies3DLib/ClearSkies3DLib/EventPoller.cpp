#include "EventPoller.h"
#include "EventHandler.h"
void EventPoller::Update()
{
    Handlers copy = m_handlers;
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type == SDL_QUIT||event.key.keysym.sym==SDLK_ESCAPE&&event.key.state==SDL_PRESSED)
        {
            exit(0);
        }
        for (Handlers::iterator it= copy.begin(); 
            it!=copy.end();
            ++it)
        {
            (*it)->HandleEvent(event);
        }
    }
}

void EventPoller::AddEventHandler(EventHandler* eh)
{
    m_handlers.insert(eh);
}

void EventPoller::RemoveEventHandler(EventHandler* eh)
{
    m_handlers.erase(eh);
}