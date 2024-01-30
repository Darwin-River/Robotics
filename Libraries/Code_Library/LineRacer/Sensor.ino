#include "Sensor.h"

 /**
  * Creates an object that connects to an external sensor such as a microphone or IR sensor
  * and monitors the input as a series of countable micro events.
  * When these events excede a threshold number of hits per sample period 
  * an alarm will register as true.
  * @param _pin The pin to which the sensor is connected.
  * @param _samplePeriod The interval in milliseconds over which the events are counted.
  * @param _sampleThreshold The minimum number of events that need to be counted during 
  * the sample period for the alarm to trigger.
  * */ 
Sensor::Sensor(byte _pin, int _samplePeriod, int _sampleThreshold) 
{
  myPin = _pin;
  mySamplePeriod = _samplePeriod;
  mySampleThreshold = _sampleThreshold;
  
  pinMode(myPin, INPUT);
}

/**
 * Counts the number events that accumulate over a sample period.
*/
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

/**
 * Returns a true value if the number of events counted during a sample period
 * exceed the sample threshold.
*/
bool Sensor::alarm()
{
  return countEvents() >= mySampleThreshold;
}