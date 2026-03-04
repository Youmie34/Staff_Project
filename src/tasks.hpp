#ifndef TASKS_HPP
#define TASKS_HPP

#include <Arduino.h>

enum task_state
{
    NOT_STARTED,
    RUNNING,
    COMPLETED,
    ERROR
};

TaskHandle_t sensorInitTaskHandler;
TaskHandle_t audioInitTaskHandler;
TaskHandle_t sensorTaskHandler;
TaskHandle_t outputTaskHandler;

volatile task_state sensorInitState;
volatile task_state audioInitState;
volatile task_state sensorState;
volatile task_state outputState;

#endif // TASKS_HPP