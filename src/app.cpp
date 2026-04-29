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
        xTaskCreatePinnedToCore(distMeasure.taskFunction, distMeasure.taskName, configMINIMAL_STACK_SIZE * 5, NULL, 8, NULL, 0);
        break;
    case ACTIVE:
        Serial.println("System is active.");

        if (systemFlags.distanceDetected)
        {
            xTaskCreatePinnedToCore(audioPlayHealing.taskFunction, audioPlayHealing.taskName, 8192, NULL, 9, NULL, 1);
            xTaskCreatePinnedToCore(neopixelPlayHealing.taskFunction, neopixelPlayHealing.taskName, 8192, NULL, 8, NULL, 0);

            if (audioPlayHealing.state == COMPLETED && neopixelPlayHealing.state == COMPLETED)
            {
                systemFlags.distanceDetected = false;
                clear_healing();
                change_state(IDLE);
            }
        }
        else
        {
        }

        if (systemFlags.motionDetected)
        {
            xTaskCreatePinnedToCore(audioPlayAttack.taskFunction, audioPlayAttack.taskName, 8192, NULL, 9, NULL, 1);
            xTaskCreatePinnedToCore(neopixelPlayAttack.taskFunction, neopixelPlayAttack.taskName, 8192, NULL, 8, NULL, 0);

            if ((audioPlayAttack.state == COMPLETED) && (neopixelPlayAttack.state == COMPLETED))
            {
                systemFlags.motionDetected = false;
                clear_attack();
                change_state(IDLE);
            }
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
    BaseType_t result = xTaskCreatePinnedToCore(
        sensorsInit.taskFunction, sensorsInit.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 9, NULL, 0);
}

void change_state(system_state newState)
{
    currentState = newState;

    switch (currentState)
    {
    case INIT:
        break;
    case IDLE:
        enableLIS3DHInterrupt();
        break;
    case ACTIVE:
        vTaskDelete(distMeasure.pxCreatedTask);
        disableLIS3DHInterrupt();
        break;
    case ERROR:
        vTaskDelete(distMeasure.pxCreatedTask);
        vTaskDelete(audioPlayHealing.pxCreatedTask);
        vTaskDelete(audioPlayAttack.pxCreatedTask);
        vTaskDelete(neopixelPlayHealing.pxCreatedTask);
        vTaskDelete(neopixelPlayAttack.pxCreatedTask);
        disableLIS3DHInterrupt();
        break;
    default:
        vTaskDelete(distMeasure.pxCreatedTask);
        vTaskDelete(audioPlayHealing.pxCreatedTask);
        vTaskDelete(audioPlayAttack.pxCreatedTask);
        vTaskDelete(neopixelPlayHealing.pxCreatedTask);
        vTaskDelete(neopixelPlayAttack.pxCreatedTask);
        disableLIS3DHInterrupt();
        break;
    }
}