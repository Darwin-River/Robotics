#include "Drive.h"
#include <Servo.h>

#define SERVO_SPEED 90
#define SERVO_STOP 91

/**
 * Creates a new object to manuever the robot by controling a pair of servos 
 * on either side of the robot.
*/
Drive::Drive() {}

/**
 * Specifies how the servos are attached to the Arduino controller.
 * @param _leftPin The pin number that connects to the left servo.
 * @param _rightPin The pin number that connects to the right servo.
*/
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

/**
 * Robot starts movin in reverse.
 * @param _speed Sets the speeds of the motors.
*/
void Drive::reverse(float _speed)
{
  if (_speed > 1.0) _speed = 1.0;

  int rightServoRev = SERVO_STOP + SERVO_SPEED ;
  int leftServoRev = SERVO_STOP - SERVO_SPEED ;

  rightServo.write(rightServoRev);
  leftServo.write(leftServoRev);
}

/**
 * Robot starts pivoting to the left.
 * @param _speed Sets the speeds of the motors.
*/
void Drive::left(float _speed)
{
  if (_speed > 1.0) _speed = 1.0;
  if (_speed < 0.0) _speed = 0.0;

  rightServo.write(SERVO_STOP - SERVO_SPEED * _speed);
  leftServo.write(SERVO_STOP - SERVO_SPEED * _speed);
}

/**
 * Robot starts pivoting to the right.
 * @param _speed Sets the speeds of the motors.
*/
void Drive::right(float _speed)
{
  if (_speed > 1.0) _speed = 1.0;

  int rightServoRev = SERVO_STOP + SERVO_SPEED ;
  int leftServoFwd = SERVO_STOP + SERVO_SPEED ;

  rightServo.write(rightServoRev);
  leftServo.write(leftServoFwd);
}

/**
 * Stops the motors.
*/
void Drive::stop()
{
  rightServo.write(SERVO_STOP);
  leftServo.write(SERVO_STOP);
}

