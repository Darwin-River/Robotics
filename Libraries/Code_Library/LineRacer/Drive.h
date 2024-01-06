#pragma once
#include <Servo.h>

class Drive
{
  private:
    Servo rightServo;
    Servo leftServo;

  public:
    Drive();
    void attach(int _leftPin, int _rightPin);
    void forward(float _speed);
    void reverse(float _speed);
    void left(float _speed);
    void right(float _speed);
    void stop();
};
