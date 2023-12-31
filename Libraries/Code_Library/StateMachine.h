#pragma once

#define MAX_STATES 20

class StateMachine
{
  private:
    int status = 0;

    int triggers[MAX_STATES];
    int trueActions[MAX_STATES];
    int falseActions[MAX_STATES];
    int trueDestinations[MAX_STATES];
    int falseDestinations[MAX_STATES];

  	int currentState;
    int currentEvents;
  	int currentActions;
    int startActions;
    int stopActions;

    int eventCount;
    int actionCount;
  
  public:
  	StateMachine();
    void addState(int _state, int _trigger, int _trueDestination, int _trueActions, int _falseDestination,  int _falseActions);
    void onStart(int _startActions);
    void onStop(int _stopActions);
    int createEventHandle();
    int createActionHandle(); 
    void logEvent(int _event, bool _status);
    void evaluate();
    void start();
    void stop();
    int getState();
    bool requests(int _action);
};