#ifndef EVENT_HANDLER_INCLUDED_H
#define EVENT_HANDLER_INCLUDED_H
#include <SDL.h>

class EventHandler
{
public:
    virtual ~EventHandler()=0{};
    void HandleEvent(const SDL_Event& event);
    virtual void OnKeyboardEvent(const SDL_KeyboardEvent&){};
    virtual void OnMouseMotionEvent(const SDL_MouseMotionEvent&){};
    virtual void OnMouseButtonEvent(const SDL_MouseButtonEvent&){};
    virtual void OnJoyAxisEvent(const SDL_JoyAxisEvent&){};
    virtual void OnJoyButtonEvent(const SDL_JoyButtonEvent&){};
};
#endif