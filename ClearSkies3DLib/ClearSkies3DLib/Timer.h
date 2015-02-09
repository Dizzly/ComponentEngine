#ifndef TIMER_H
#define TIMER_H
#include "Singleton.h"
class Timer;
typedef Singleton<Timer> TheTimer;

class Timer : public NonCopyable
{
public:

    void Update();
    float GetDt() const;
private:
    Timer();
    float m_deltaTime;
    float m_lastTime;
    friend TheTimer;

};


#endif