#include "Timer.h"
#include <SDL.h>

Timer::Timer()
{
    m_deltaTime=0;
    m_lastTime=0;
}



void Timer::Update()
{
    float currentTime = SDL_GetTicks() *0.001f;
    m_deltaTime=currentTime-m_lastTime;
    m_lastTime=currentTime;
    const float MAX_DT =0.1f;
    if(m_deltaTime>MAX_DT)
    {m_deltaTime=MAX_DT;}
}

float Timer::GetDt() const
{
    return m_deltaTime;
}
