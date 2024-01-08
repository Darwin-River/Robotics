#include "StateMachines.h"

#define STOPPED  0
#define STARTING 1
#define RUNNING  2
#define STOPPING 3

StateMachines::StateMachines() {}

void StateMachines::addState(int _machine, int _state, int _trigger, int _trueDestination, int _trueActions, int _falseDestination, int _falseActions)
{
  if(_machine > machineCount) machineCount = _machine;
  triggers[_machine][_state] = _trigger;
  trueActions[_machine][_state] = _trueActions;
  falseActions[_machine][_state] = _falseActions;
  trueDestinations[_machine][_state] = _trueDestination;
  falseDestinations[_machine][_state] = _falseDestination;
}

void StateMachines::onStart(int _machine, int _startActions)
{
  startActions[_machine] = _startActions;
}

void StateMachines::onStop(int _machine, int _stopActions)
{
  stopActions[_machine] = _stopActions;
}

int StateMachines::createEventHandle()
{
  eventCount ++;
  return bit(eventCount - 1);
}

int StateMachines::createActionHandle()
{
  actionCount ++;
  return bit(actionCount - 1);
}

void StateMachines::logEvent(int _event, bool _status)
{
  if (_status) currentEvents = currentEvents | _event;
}

void StateMachines::evaluate()
{
  int machine = 0;
  currentActions = 0;
  do
  {
    switch(status[machine])
    {
      case STARTING:
        Serial.println("Starting");
        currentActions = currentActions & startActions[machine];
        currentState[machine] = 0;
        status[machine] = RUNNING;
        break;
      case RUNNING:
        Serial.println(currentState[machine]);
        if ((triggers[machine][currentState[machine]] & currentEvents) > 0)
        {
          currentActions = currentActions & trueActions[machine][currentState[machine]];
          currentState[machine] = trueDestinations[machine][currentState[machine]];
        }
        else
        {
          currentActions = currentActions & falseActions[machine][currentState[machine]];
          currentState[machine] = falseDestinations[machine][currentState[machine]];
        }
        break;
      case STOPPING:
        Serial.println("Stopping");
        status[machine] = STOPPED;
        currentActions = currentActions & stopActions[machine];
        currentState[machine] = 0;
        status[machine] = STOPPED;
        break;
      case STOPPED:
        // Serial.println("Stopped");
        currentState[machine] = 0;
        break;
    }
    machine ++;
  } while (machine < machineCount);
  currentEvents = 0;
} 

void StateMachines::start(int _machine)
{
  Serial.println("Told to start.");
  status[_machine] = STARTING;
}

void StateMachines::stop(int _machine)
{
  Serial.println("Told to stop.");
  status[_machine] = STOPPING;
}

int StateMachines::getState(int _machine)
{
  return currentState[_machine];
}

bool StateMachines::request(int _action)
{
  return (currentActions & _action) > 0;
}