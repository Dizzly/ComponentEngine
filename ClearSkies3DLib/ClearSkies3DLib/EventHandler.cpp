#include "EventHandler.h"

void EventHandler::HandleEvent(const SDL_Event& event)
{
    switch(event.type)
    {
    case SDL_KEYDOWN:
    case SDL_KEYUP:
        OnKeyboardEvent(event.key);
        break;

    case SDL_MOUSEMOTION:
        OnMouseMotionEvent(event.motion);
        break;

    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        OnMouseButtonEvent(event.button);
        break;

    case SDL_JOYAXISMOTION:
        OnJoyAxisEvent(event.jaxis);
        break;

    case SDL_JOYBUTTONDOWN:
    case SDL_JOYBUTTONUP:
        OnJoyButtonEvent(event.jbutton);
        break;

    }
}