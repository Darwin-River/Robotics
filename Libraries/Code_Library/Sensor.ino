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