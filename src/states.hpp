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
    volatile bool sensorsInitialized = false;
    volatile bool audioInitialized = false;
    volatile bool motionDetected = false;
    volatile bool distanceDetected = false;
    volatile bool neoHealing = false;
    volatile bool neoAttack = false;
    volatile bool audioHealing = false;
    volatile bool audioAttack = false;
};

struct tasks_t
{
    const char *taskName;
    void (*taskFunction)(void *); // Function pointer for task execution
    task_state state;
    TaskHandle_t pxCreatedTask;
};

extern volatile system_state currentState; // Correctly declare as extern
extern flags_t systemFlags;

#endif // STATES_HPP