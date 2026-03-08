/*app.c*/

#include "app.hpp"

void app_main_function()
{
    switch (currentState)
    {
    case INIT:
        Serial.println("System is changing to IDLE state.");
        change_state(IDLE);
        break;
    case IDLE:
        Serial.println("System is idle.");

        if (distanceDetected || motionDetected)
        {
            change_state(ACTIVE);
        }

        else
        {
            change_state(IDLE);
            xTaskCreate(distMeasure.taskFunction, distMeasure.taskName, configMINIMAL_STACK_SIZE * 5, NULL, 6, NULL);
            // xTaskCreate(accMeasure.taskFunction, accMeasure.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
        }
        break;
    case ACTIVE:
        Serial.println("System is active.");

        if (distanceDetected)
        {
            xTaskCreate(audioPlayHealing.taskFunction, audioPlayHealing.taskName, 4095, NULL, 9, NULL);
            xTaskCreate(neopixelPlayHealing.taskFunction, neopixelPlayHealing.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 9, NULL);
            change_state(IDLE);
        }
        else
        {
        }

        if (motionDetected)
        {
            xTaskCreate(audioPlayAttack.taskFunction, audioPlayAttack.taskName, 4095, NULL, 9, NULL);
            xTaskCreate(neopixelPlayAttack.taskFunction, neopixelPlayAttack.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 9, NULL);
            change_state(IDLE);
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

    // vTaskStartScheduler();
}

bool app_init()
{
    Serial.println(uxTaskGetStackHighWaterMark(NULL));
    BaseType_t result = xTaskCreate(sensorsInit.taskFunction, sensorsInit.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 9, NULL);
    BaseType_t result1 = xTaskCreate(spiffsInit.taskFunction, spiffsInit.taskName, 8192, NULL, 10, NULL);

    /*
    if (result1 == pdPASS)
    {
        Serial.println("Task created successfully.");
        Serial.print("Stack high-water mark: ");
        Serial.println(uxTaskGetStackHighWaterMark(NULL));
    }
*/
    // xTaskCreate(sdInit.taskFunction, sdInit.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
    return true;
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