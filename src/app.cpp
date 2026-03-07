/*app.c*/

#include "app.hpp"

void createTasks()
{
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    xTaskCreate(sensorsInit.taskFunction, sensorsInit.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
    xTaskCreate(sdInit.taskFunction, sdInit.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
    xTaskCreate(spiffsInit.taskFunction, spiffsInit.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
    xTaskCreate(distMeasure.taskFunction, distMeasure.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
    xTaskCreate(accMeasure.taskFunction, accMeasure.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
    xTaskCreate(audioPlay.taskFunction, audioPlay.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
    xTaskCreate(neopixelPlay.taskFunction, neopixelPlay.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
    xTaskCreate(errorHandler.taskFunction, errorHandler.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}
