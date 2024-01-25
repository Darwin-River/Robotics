# StateEngine Class
This C++ class is capable of creating and managing a number of Mealy state machines that run in paralell to guide the robot's response to internal and external events. 

Each state machine consists of multiple interconnected states. Each of these states has a single Boolean event that determines if and how it will transition to another state. Depending on whether the trigger event is true or false, the machine will perform some actions and pass control to another state.

Although the rules for the state machines are quite simple, states can be linked via different user-defined triggers and actions.  Additionally different state machines can work in parallel monitor and respond to different events, allowing the StateEngine class to encode complex sets of environment-driven actions.

## Creating a StateEngine object
When using the StateEngine class in your robot code,  you first need to create a StateEngine object by invocing the constructor fungion: `engine = StateEngine();`

## Creating the event and action handles
Next, you need to create a series of event and action handles via the `createEventHandle()` and `createActionHandle()` functions.  These functions do not take any arguments.  However they return an integer number that needs to be assigned to a constant and used to reference the events and actions in your code.

```C++
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
```
## Designing the individual state machines
The StateEngine is capable of managaging multiple state machines that are running in parallel to make use of the previously defined events and actions.  

Each state machine has it's own start and stop actions which are defined using the `onStart()` and `onStop()` functions.  Each of these functions accepts an integer ID for the affected state machine and an integer sum of all the actions that are performned byt the state machnine when it receives a start or stop command.

Additionally, you need to use the `addState()` function to define each of the states in the state machine, starting with state 0. The state machine expects the following parameters in the order that they're listed here:
- __State Machine ID (int).__ This is the ID of the affected state machin.
- __Trigger Event Handle (int).__  This is the handle for the binary event that the state will monitor to guide the program's transition to another state.
- __True Destintation (int).__  This is the state that the state machine will progres to if the event is true.
- __True Actions (int).__  This is the sum of the action handles that the state machine will invoke as it passes to the new state.
- __False Destintation (int).__  This is the state that the state machine will progres to if the event is false.
- __False Actions (int).__  This is the sum of the action handles that the state machine will invoke as it passes to the new state.

Here is an example of how two state engines are set up using the `onStart()`, `onStop()`, and `addState()` functions:
```C++
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
```
After defining each of the state machines in the StateEngine object, you'll need to start at least one of the engines using the `start()` function as follows:

```C++
  engine.start(LISTEN_SM);
```

## Creating a StateEngine loop
The final step in implementing the StateEngine class in an Arduino sketch, is to set up the evaluation loop that the robot will continuouly cycle through while in operation.

There are three parts to the evaluation loop:
1. Log the status of all events by passing a Boolean value to each of the event handles using the `logEvent()` function.
2. Evaluate how each of the state engines responds to the logged events by calling the `evaluate()` function.
3. Implement each of the actions that are invoked by the state engines by using the `requests()` function to identify and respond to each of the actions that are called for by the state engine.

Here's an example of a propperly formatted evaluation loop:
```C++
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
```

## Files
The StateEngine class is encoded by [StateEngine.h](StateEngine.h) and [StateMachine.ino](StateEngine.ino), which need to be included in the Arduino build library.
