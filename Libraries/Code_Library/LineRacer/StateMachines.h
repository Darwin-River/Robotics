#pragma once

#define MAX_MACHINES 5
#define MAX_STATES 20

class StateMachines
{
  private:

    int currentEvents;
  	int currentActions;
    int eventCount;
    int actionCount;
    int machineCount;

    int status[MAX_MACHINES];
  	int currentState[MAX_MACHINES];
    int startActions[MAX_MACHINES];
    int stopActions[MAX_MACHINES];

    int triggers[MAX_MACHINES][MAX_STATES];
    int trueActions[MAX_MACHINES][MAX_STATES];
    int falseActions[MAX_MACHINES][MAX_STATES];
    int trueDestinations[MAX_MACHINES][MAX_STATES];
    int falseDestinations[MAX_MACHINES][MAX_STATES];
 
  public:
  	StateMachines();
    void addState(int _SM, int _state, int _trigger, int _trueDestination, int _trueActions, int _falseDestination,  int _falseActions);
    void onStart(int _SM, int _startActions);
    void onStop(int _SM, int _stopActions);
    int createEventHandle();
    int createActionHandle(); 
    void logEvent(int _event, bool _status);
    void evaluate();
    void start(int _SM);
    void stop(int _SM);
    int getState(int _SM);
    bool request(int _action);
};