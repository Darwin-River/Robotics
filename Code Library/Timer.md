Use this class to set up timers that run for set periods of time before triggering an alarm event for the robot to respond to.

## Timer.h
```C++
#pragma once

class Timer
{
  private:
    int targetTime;
    int duration;
  public:
    Timer(int _duration);
    void reset();
    bool isAlarming();
};
```

## Timer.ino
```C++
#include "Timer.h"

Timer::Timer(int _duration) 
{
  duration = _duration;
}

void Timer::reset()
{
  targetTime = millis() + duration;
  Serial.print("Setting timer for ");
  Serial.print(duration);
  Serial.println(" ms");     
}

bool Timer::isAlarming()
{
  return millis() >= targetTime;
}
```
