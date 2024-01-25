#include "StateEngine.h"
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
StateEngine engine;
Timer shortTimer(500);
Timer longTimer(4000);
Sensor mic(MIC_PIN, MIC_SAMPLE_PERIOD, MIC_THRESHOLD);
Sensor leftIR(LEFT_IR_PIN, IR_SAMPLE_PERIOD, IR_SAMPLE_THRESHOLD);
Sensor rightIR(RIGHT_IR_PIN, IR_SAMPLE_PERIOD, IR_SAMPLE_THRESHOLD);
Drive myDrive;

// Create machine handles
const int LISTEN_SM = engine.createMachineHandle();
const int FOLLOW_SM = engine.createMachineHandle();

// Create action handles
const int NUL = engine.createActionHandle(); // Do nothing
const int SFL = engine.createActionHandle(); // Start Follow State Machine
const int PST = engine.createActionHandle(); // Print current state
const int STS = engine.createActionHandle(); // Set short timer
const int LTS = engine.createActionHandle(); // Set long timer
const int LFT = engine.createActionHandle(); // Turn left
const int RGT = engine.createActionHandle(); // Turn right
const int STP = engine.createActionHandle(); // Stop motors

const int XFL = engine.createActionHandle(); // Stop Follow State Machine

// Create event handles
const int TRU = engine.createEventHandle(); // Always true event
const int STA = engine.createEventHandle(); // Short timer alarm
const int LTA = engine.createEventHandle(); // Long timer alarm
const int LIR = engine.createEventHandle(); // Left IR sensor
const int RIR = engine.createEventHandle(); // Right IR sensor
const int MIC = engine.createEventHandle(); // MIC Alarm

void setup() {
  Serial.begin(9600);

  myDrive.attach(LEFT_SERVO_PIN, RIGHT_SERVO_PIN);

  // Construct Listen State Machine
  engine.onStart(LISTEN_SM, LTS+SFL);
  engine.onStop(LISTEN_SM, NUL);
  engine.addState(LISTEN_SM, 0, LTA, 1, XFL, 0, NUL);
  engine.addState(LISTEN_SM, 1, TRU, 1, NUL, 1, NUL);

  // Construct Follow State Machine
  engine.onStart(FOLLOW_SM, STS + RGT);
  engine.onStop(FOLLOW_SM, STP);
  engine.addState(FOLLOW_SM, 0, STA, 1, STS + LFT, 0, NUL);
  engine.addState(FOLLOW_SM, 1, STA, 0, STS + RGT, 1, NUL);

  // Start the Listen State Machine
  engine.start(LISTEN_SM);
  //engine.start(FOLLOW_SM);

  engine.debug(LISTEN_SM, true);
  engine.debug(FOLLOW_SM, true);
}

void loop() {
  // Log events
  engine.logEvent(MIC, mic.alarm());
  engine.logEvent(LTA, longTimer.isAlarming());

  engine.logEvent(TRU, true);
  engine.logEvent(STA, shortTimer.isAlarming());
 
  engine.logEvent(LIR, ! leftIR.alarm());
  engine.logEvent(RIR, ! rightIR.alarm());
  
  // Evaluate state machines
  engine.evaluate();
  
  // Perform requested actions
  if(engine.requests(SFL)) engine.start(FOLLOW_SM);
  if(engine.requests(XFL)) engine.stop(FOLLOW_SM);
  if(engine.requests(STS)) shortTimer.reset();
  if(engine.requests(LTS)) longTimer.reset();
  if(engine.requests(LFT)) myDrive.left(0.1);
  if(engine.requests(RGT)) myDrive.right(0.1);
  if(engine.requests(STP)) myDrive.stop();
}
