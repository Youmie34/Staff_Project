/*states.hpp*/

#ifndef STATES_HPP
#define STATES_HPP

#include <Arduino.h>

enum system_state
{
    INIT,
    IDLE,
    ACTIVE,
    ERROR
};

enum task_state
{
    NOT_STARTED,
    RUNNING,
    COMPLETED,
    PROBLEM
};

struct flags_t
{
    volatile bool motionDetected = false;
    volatile bool distanceDetected = false;
};

struct tasks_t
{
    char taskName[20];
    TaskHandle_t taskHandle;
    task_state state;
};

extern volatile system_state currentState;
extern flags_t systemFlags;

#endif // STATES_HPP