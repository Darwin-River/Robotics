#include "StateMachines.h"
#include "Timer.h"
#include "Sensor.h"
#include "Drive.h"

// Connections
#define LEFT_SERVO_PIN 10
#define RIGHT_SERVO_PIN 9
#define MIC_PIN A0
#define LEFT_IR_PIN A1
#define RIGHT_IR_PIN A2

// Parameters
#define MIC_SAMPLE_PERIOD 10
#define MIC_THRESHOLD 10
#define IR_SAMPLE_PERIOD 10
#define IR_SAMPLE_THRESHOLD 10

// Create objects
StateMachines listen; 
StateMachines follow;
Timer shortTimer(500);
Timer longTimer(4000);
Sensor mic(MIC_PIN, MIC_SAMPLE_PERIOD, MIC_THRESHOLD);
Sensor leftIR(LEFT_IR_PIN, IR_SAMPLE_PERIOD, IR_SAMPLE_THRESHOLD);
Sensor rightIR(RIGHT_IR_PIN, IR_SAMPLE_PERIOD, IR_SAMPLE_THRESHOLD);
Drive myDrive;

// Create action handles
const int NUL = bit(0); // Do nothing
const int PST = bit(1); // Print current state
const int STS = bit(2); // Set short timer
const int LTS = bit(3); // Set long timer
const int LFT = bit(4); // Turn left
const int RGT = bit(5); // Turn right
const int STP = bit(6); // Stop motors
const int SFL = bit(7); // Start Follow State Machine
const int XFL = bit(8); // Stop Follow State Machine

// Create event handles
const int TRU = bit(0); // Always true event
const int STA = bit(1); // Short timer alarm
const int LTA = bit(2); // Long timer alarm
const int LIR = bit(3); // Left IR sensor
const int RIR = bit(4); // Right IR sensor
const int MIC = bit(5); // MIC Alarm

void setup() {
  Serial.begin(9600);

  myDrive.attach(LEFT_SERVO_PIN, RIGHT_SERVO_PIN);

  // Construct Listen State Machine
  listen.onStart(LTS+SFL);
  listen.onStop(NUL);
  listen.addState(0, LTA, 1, XFL, 0, NUL);
  listen.addState(1, TRU, 1, NUL, 1, NUL);

   
  // Construct Follow State Machine
  follow.onStart(STS + RGT);
  follow.onStop(STP);
  follow.addState(0, STA, 1, STS + LFT, 0, NUL);
  follow.addState(1, STA, 0, STS + RGT, 1, NUL);

  // Start the Listen State Machine
  listen.start();
}

void loop() {
  // Log events
  listen.logEvent(MIC, mic.alarm());
  listen.logEvent(LTA, longTimer.isAlarming());

  follow.logEvent(TRU, true);
  follow.logEvent(STA, shortTimer.isAlarming());
 
  follow.logEvent(LIR, ! leftIR.alarm());
  follow.logEvent(RIR, ! rightIR.alarm());
  
  // Evaluate state machines
  listen.evaluate();
  follow.evaluate();
  
  // Perform requested actions
  if(listen.requests(SFL)) follow.start();
  if(listen.requests(XFL)) follow.stop();
  if(follow.requests(STS)) shortTimer.reset();
  if(follow.requests(LTS)) longTimer.reset();
  if(follow.requests(LFT)) myDrive.left(0.1);
  if(follow.requests(RGT)) myDrive.right(0.1);
  if(follow.requests(STP)) myDrive.stop();
}
