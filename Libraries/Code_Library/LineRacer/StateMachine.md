## Overview
This C++ class is capable of creating and managing a number of Mealy state machines that run in paralell to guide the robot's response to internal and external events. 

Each state machine consists of multiple interconnected states. Each of these states has a single Boolean event that determines if and how it will transition to another state. Depending on whether the trigger event is true or false, the machine will perform some actions and pass control to another state.

Although the rules for the state machines are quite simple, states can be linked via different user-defined triggers and actions.  Additionally different state machines can work in parallel monitor and respond to different events, allowing the StateEngine class to encode complex sets of environment-driven actions.

When using the StateEngine class in your robot code,  you first need to create a StateEngine object by invocing the constructor fungion: `engine = StateEngine();`

Next, you need to create a series of event and action handles via the `createEventHandle()` and `createActionHandle()` functions.  These functions do not take any arguments.  However they return an integer number that needs to be assigned to a constant and used to reference the events and actions in your code.

```C++
// Create event handles
const int TRU = engine.createEventHandle(); // Always true event
const int STA = engine.createEventHandle(); // Short timer alarm
const int LTA = engine.createEventHandle(); // Long timer alarm

// Create action handles
const int NUL = engine.createActionHandle(); // Do nothing
const int STS = engine.createActionHandle(); // Set short timer
const int LTS = engine.createActionHandle(); // Set long timer
const int LFT = engine.createActionHandle(); // Turn left
const int RGT = engine.createActionHandle(); // Turn right
const int STP = engine.createActionHandle(); // Stop motors
```

## Files
The StateEngine class is encoded by [StateEngine.h](StateEngine.h) and [StateMachine.ino](StateEngine.ino), which need to be included in the Arduino build library.
