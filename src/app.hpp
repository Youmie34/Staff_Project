/*app.h*/

#ifndef APP_H
#define APP_H

#include "tasks.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void createTasks();
void app_main();
void app_init();
void change_state(system_state newState);

#endif // APP_H