/*app.c*/

#include "app.hpp"

void app_main()
{
    createTasks();

    switch (currentState)
    {
    case INIT:
        Serial.println("System is changing to IDLE state.");
        change_state(IDLE);
        break;
    case IDLE:
        Serial.println("System is idle.");
        xTaskCreate(distMeasure.taskFunction, distMeasure.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
        xTaskCreate(accMeasure.taskFunction, accMeasure.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
        break;
    case ACTIVE:
        Serial.println("System is active.");

        if (distanceDetected)
        {
            xTaskCreate(audioPlayHealing.taskFunction, audioPlayHealing.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
            xTaskCreate(neopixelPlayHealing.taskFunction, neopixelPlayHealing.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
        }
        else
        {
        }

        if (motionDetected)
        {
            xTaskCreate(audioPlayAttack.taskFunction, audioPlayAttack.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
            xTaskCreate(neopixelPlayAttack.taskFunction, neopixelPlayAttack.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
        }
        else
        {
        }
        break;
    case ERROR:
        Serial.println("System error occurred!");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        xTaskCreate(errorHandler.taskFunction, errorHandler.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
        break;
    default:
        Serial.println("Unknown system state!");
        break;
    }

    vTaskStartScheduler();
}

void app_init()
{
    xTaskCreate(sensorsInit.taskFunction, sensorsInit.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
    xTaskCreate(sdInit.taskFunction, sdInit.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
    xTaskCreate(spiffsInit.taskFunction, spiffsInit.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}

void change_state(system_state newState)
{
    currentState = newState;

    switch (currentState)
    {
    case INIT:
        Serial.println("System is initializing...");
        break;
    case IDLE:
        Serial.println("System is idle.");
        break;
    case ACTIVE:
        Serial.println("System is active.");
        break;
    case ERROR:
        Serial.println("System error occurred!");
        break;
    default:
        Serial.println("Unknown system state!");
        break;
    }
}