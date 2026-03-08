/*app.h*/

#ifndef APP_H
#define APP_H

#include "tasks.hpp"

void app_main_function();
bool app_init();
void change_state(system_state newState);

#endif // APP_H