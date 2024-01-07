#include "StateMachine.h"

#define STOPPED  0
#define STARTING 1
#define RUNNING  2
#define STOPPING 3

StateMachine::StateMachine() {}

void StateMachine::addState(int _state, int _trigger, int _trueDestination, int _trueActions, int _falseDestination, int _falseActions)
{
  triggers[_state] = _trigger;
  trueActions[_state] = _trueActions;
  falseActions[_state] = _falseActions;
  trueDestinations[_state] = _trueDestination;
  falseDestinations[_state] = _falseDestination;
}

void StateMachine::onStart(int _startActions)
{
  startActions = _startActions;
}

void StateMachine::onStop(int _stopActions)
{
  stopActions = _stopActions;
}

int StateMachine::createEventHandle()
{
  eventCount ++;
  return bit(eventCount - 1);
}

int StateMachine::createActionHandle()
{
  actionCount ++;
  return bit(actionCount - 1);
}

void StateMachine::logEvent(int _event, bool _status)
{
  if (_status) currentEvents = currentEvents | _event;
}

void StateMachine::evaluate()
{
  switch(status)
  {
    case STARTING:
      Serial.println("Starting");
      currentActions = startActions;
      currentState = 0;
      status=RUNNING;
      break;
    case RUNNING:
      Serial.println(currentState);
      if ((triggers[currentState] & currentEvents) > 0)
      {
        currentActions = trueActions[currentState];
        currentState = trueDestinations[currentState];
      }
      else
      {
        currentActions = falseActions[currentState];
        currentState = falseDestinations[currentState];
      }
      break;
    case STOPPING:
      Serial.println("Stopping");
      status = STOPPED;
      currentActions = stopActions;
      currentState = 0;
      status=STOPPED;
      break;
    case STOPPED:
      // Serial.println("Stopped");
      currentActions = 0;
      currentState = 0;
      break;
  }
  currentEvents = 0;
}

void StateMachine::start()
{
  Serial.println("Told to start.");
  status = STARTING;
}

void StateMachine::stop()
{
  Serial.println("Told to stop.");
  status = STOPPING;
}

int StateMachine::getState()
{
  return currentState;
}

bool StateMachine::requests(int _action)
{
  return (currentActions & _action) > 0;
}