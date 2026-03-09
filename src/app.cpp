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

        if ((systemFlags.distanceDetected) || (systemFlags.motionDetected))
        {
            change_state(ACTIVE);
        }

        else
        {
            change_state(IDLE);
            xTaskCreate(distMeasure.taskFunction, distMeasure.taskName, configMINIMAL_STACK_SIZE * 5, NULL, 6, distMeasure.pxCreatedTask);
            // xTaskCreate(accMeasure.taskFunction, accMeasure.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
        }
        break;
    case ACTIVE:
        Serial.println("System is active.");

        if (systemFlags.distanceDetected)
        {
            vTaskDelete(distMeasure.pxCreatedTask);
            xTaskCreate(audioPlayHealing.taskFunction, audioPlayHealing.taskName, 8192, NULL, 9, NULL);
            xTaskCreate(neopixelPlayHealing.taskFunction, neopixelPlayHealing.taskName, 8192, NULL, 8, NULL);

            change_state(IDLE);
        }
        else
        {
        }

        if (systemFlags.motionDetected)
        {
            xTaskCreate(audioPlayAttack.taskFunction, audioPlayAttack.taskName, 8192, NULL, 9, NULL);
            xTaskCreate(neopixelPlayAttack.taskFunction, neopixelPlayAttack.taskName, 8192, NULL, 8, NULL);

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

void app_init()
{
    BaseType_t result = xTaskCreate(sensorsInit.taskFunction, sensorsInit.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 9, NULL);
    BaseType_t result1 = xTaskCreate(spiffsInit.taskFunction, spiffsInit.taskName, 8192, NULL, 10, NULL);
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
        enableLIS3DHInterrupt();
        break;
    case ACTIVE:
        Serial.println("System is active.");
        vTaskDelete(distMeasure.pxCreatedTask);
        disableLIS3DHInterrupt();
        break;
    case ERROR:
        Serial.println("System error occurred!");
        vTaskDelete(distMeasure.pxCreatedTask);
        vTaskDelete(audioPlayHealing.pxCreatedTask);
        vTaskDelete(audioPlayAttack.pxCreatedTask);
        vTaskDelete(neopixelPlayHealing.pxCreatedTask);
        vTaskDelete(neopixelPlayAttack.pxCreatedTask);
        disableLIS3DHInterrupt();
        break;
    default:
        Serial.println("Unknown system state!");
        vTaskDelete(distMeasure.pxCreatedTask);
        vTaskDelete(audioPlayHealing.pxCreatedTask);
        vTaskDelete(audioPlayAttack.pxCreatedTask);
        vTaskDelete(neopixelPlayHealing.pxCreatedTask);
        vTaskDelete(neopixelPlayAttack.pxCreatedTask);
        disableLIS3DHInterrupt();
        break;
    }
}