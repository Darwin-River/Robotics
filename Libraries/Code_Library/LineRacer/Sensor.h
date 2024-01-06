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