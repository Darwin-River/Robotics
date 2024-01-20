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
## Degining the individual state machines
The StateEngine is capable of managaging multiple state machines that are running in parallel to make use of the previously defined events and actions.  

Each state machine has it's own start and stop actions which are defined using the `onStart()` and `onStop()` functions.  Each of these functions accepts an integer ID for the affected state machine and an integer sum of all the actions that are performned byt the state machnine when it receives a start or stop command.

Additionally, you need to use the `addState()` function to define each of the states in the state machine, starting with state 0. The state machine expects the following parameters in the order that they're listed here:
- State Machine ID (int)
- Trigger Event Handle (int).  This is the handle for the binary event that the state will monitor to guide the program's transition to another state.
- True Destintation (int).  This is the state that the state machine will progres to if the event is true.
- True Actions (int).  This is the sum of the action handles that the state machine will invoke as it passes to the new state.
- False Destintation (int).  This is the state that the state machine will progres to if the event is false.
- False Actions (int).  This is the sum of the action handles that the state machine will invoke as it passes to the new state.

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


## Files
The StateEngine class is encoded by [StateEngine.h](StateEngine.h) and [StateMachine.ino](StateEngine.ino), which need to be included in the Arduino build library.
