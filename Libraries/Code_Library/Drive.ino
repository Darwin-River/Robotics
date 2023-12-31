#include "Drive.h"
#include <Servo.h>

#define SERVO_SPEED 90
#define SERVO_STOP 91


Drive::Drive() {}

void Drive::attach(int _leftPin, int _rightPin)
{
  rightServo.attach(_rightPin);
  leftServo.attach(_leftPin);
}
void Drive::forward(float _speed)
{
  if (_speed > 1.0) _speed = 1.0;

  int rightServoFwd = SERVO_STOP - SERVO_SPEED * _speed;
  int leftServoFwd = SERVO_STOP + SERVO_SPEED * _speed;

  rightServo.write(rightServoFwd);
  leftServo.write(leftServoFwd);
}

void Drive::reverse(float _speed)
{
  if (_speed > 1.0) _speed = 1.0;

  int rightServoRev = SERVO_STOP + SERVO_SPEED ;
  int leftServoRev = SERVO_STOP - SERVO_SPEED ;

  rightServo.write(rightServoRev);
  leftServo.write(leftServoRev);
}

void Drive::left(float _speed)
{
  if (_speed > 1.0) _speed = 1.0;
  if (_speed < 0.0) _speed = 0.0;

  rightServo.write(SERVO_STOP - SERVO_SPEED * _speed);
  leftServo.write(SERVO_STOP - SERVO_SPEED * _speed);
}

void Drive::right(float _speed)
{
  if (_speed > 1.0) _speed = 1.0;

  int rightServoRev = SERVO_STOP + SERVO_SPEED ;
  int leftServoFwd = SERVO_STOP + SERVO_SPEED ;

  rightServo.write(rightServoRev);
  leftServo.write(leftServoFwd);
}

void Drive::stop()
{
  rightServo.write(SERVO_STOP);
  leftServo.write(SERVO_STOP);
}

