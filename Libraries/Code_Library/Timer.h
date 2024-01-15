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