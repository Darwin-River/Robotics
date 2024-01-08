#include "StateEngine.h"

#define STOPPED  0
#define STARTING 1
#define RUNNING  2
#define STOPPING 3

StateEngine::StateEngine() 
{

}

void StateEngine::addState(int _machine, int _state, int _trigger, int _trueDestination, int _trueActions, int _falseDestination, int _falseActions)
{
  if(_machine > machineCount) machineCount = _machine;
  triggers[_machine][_state] = _trigger;
  trueActions[_machine][_state] = _trueActions;
  falseActions[_machine][_state] = _falseActions;
  trueDestinations[_machine][_state] = _trueDestination;
  falseDestinations[_machine][_state] = _falseDestination;
}

void StateEngine::onStart(int _machine, int _startActions)
{
  startActions[_machine] = _startActions;
}

void StateEngine::onStop(int _machine, int _stopActions)
{
  stopActions[_machine] = _stopActions;
}

int StateEngine::createEventHandle()
{
  eventCount ++;
  return bit(eventCount - 1);
}

int StateEngine::createActionHandle()
{
  actionCount ++;
  return bit(actionCount - 1);
}

void StateEngine::logEvent(int _event, bool _status)
{
  if (_status) currentEvents = currentEvents | _event;
}

void StateEngine::evaluate()
{
  int machine = 0;
  currentActions = 0;
  do
  {
    if(debugOn[machine]) 
    {
      Serial.print("SM ");
      Serial.print(machine);
    }
    switch(status[machine])
    {
      case STARTING:
        if(debugOn[machine])
        {
          Serial.print(" is starting at state ");
          Serial.println(currentState[machine]);
        }
        currentActions = currentActions & startActions[machine];
        currentState[machine] = 0;
        status[machine] = RUNNING;
        break;
      case RUNNING:
        if(debugOn[machine])
        {
          Serial.print(" is running at state ");
          Serial.println(currentState[machine]);
        }
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
        if(debugOn[machine])
        {
          Serial.print(" is stopping at state ");
          Serial.println(currentState[machine]);
        }
        status[machine] = STOPPED;
        currentActions = currentActions & stopActions[machine];
        currentState[machine] = 0;
        status[machine] = STOPPED;
        break;
      case STOPPED:
        if(debugOn[machine]) Serial.println(" is stopped.");
        currentState[machine] = 0;
        break;
    }
    machine ++;
  } while (machine < machineCount);
  currentEvents = 0;
} 

void StateEngine::start(int _machine)
{
  Serial.println("Told to start.");
  status[_machine] = STARTING;
}

void StateEngine::stop(int _machine)
{
  Serial.println("Told to stop.");
  status[_machine] = STOPPING;
}

int StateEngine::getState(int _machine)
{
  return currentState[_machine];
}

bool StateEngine::requests(int _action)
{
  return (currentActions & _action) > 0;
}

void StateEngine::debug(int _machine, bool _debugOn)
{
  debugOn[_machine] = _debugOn;
}