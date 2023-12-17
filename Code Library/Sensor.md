This is a general purpose class that allows the robot to monitor digital signals from different Arduino sensors like the IR Sensor and Sound Sensor used in the Line Racer robot.

## Sensor.h
```C++
#pragma once

class Sensor
{
  private:
    byte myPin;
  	int mySamplePeriod;
  	int mySampleThreshold;
  	int countEvents();
    
  public:
    Sensor(byte _pin, int _samplePeriod, int _sampleThreshold);  
    bool alarm();   
};
```

## Sensor.ino
```C++
#include "Sensor.h"
  
int Sensor::countEvents()
{
  int eventCount = 0;
  unsigned long timeMarker = millis();
  while(millis()-timeMarker < mySamplePeriod) {
    if (digitalRead(myPin) == LOW) 
    {
      eventCount ++;
    }
  }
  return eventCount;
}

Sensor::Sensor(byte _pin, int _samplePeriod, int _sampleThreshold) 
{
  myPin = _pin;
  mySamplePeriod = _samplePeriod;
  mySampleThreshold = _sampleThreshold;
  
  pinMode(myPin, INPUT);
}

bool Sensor::alarm()
{
  return countEvents() >= mySampleThreshold;
}
```
