#include "Timer.h"

Timer::Timer(int _duration) 
{
  duration = _duration;
}

void Timer::reset()
{
  targetTime = millis() + duration;    
}

bool Timer::isAlarming()
{
  return millis() >= targetTime;
}