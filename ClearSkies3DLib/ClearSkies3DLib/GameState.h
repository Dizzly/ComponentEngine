#ifndef GAMESTATE_H_INCLUDED
#define GAMESTATE_H_INCLUDED
#include "EventHandler.h"
#include "NonCopyable.h"
class GameState: public EventHandler,public NonCopyable
{
public:
    virtual ~GameState(){};
    virtual void Update()=0;
    virtual void Draw()=0;
    virtual void OnActive()=0;
    virtual void OnInactive()=0;

};

#endif