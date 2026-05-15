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
        // Serial.println("System is idle.");

        if ((systemFlags.distanceDetected) || (systemFlags.motionDetected))
        {
            change_state(ACTIVE);
        }

        else
        {
            if (currentState != IDLE)
            {
                change_state(IDLE);
            }
            // xTaskCreate(distMeasure.taskFunction, distMeasure.taskName, configMINIMAL_STACK_SIZE * 5, NULL, 8, NULL);
            ultrasonicMeasure();
            // xTaskCreate(accMeasure.taskFunction, accMeasure.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
        }
        break;
    case ACTIVE:
        // Serial.println("System is active.");

        if (systemFlags.distanceDetected)
        {
            if (neopixelPlayHealing.state == NOT_STARTED && neopixelPlayHealing.pxCreatedTask == NULL)
            {
                xTaskCreatePinnedToCore(neopixelPlayHealing.taskFunction, neopixelPlayHealing.taskName, 8192, NULL, 9, &neopixelPlayHealing.pxCreatedTask, 0);
                vTaskDelay(50 / portTICK_PERIOD_MS);
            }

            if (audioPlayHealing.state == NOT_STARTED && audioPlayHealing.pxCreatedTask == NULL)
            {
                xTaskCreatePinnedToCore(audioPlayHealing.taskFunction, audioPlayHealing.taskName, 8192, NULL, 7, &audioPlayHealing.pxCreatedTask, 1);
            }

            if (audioPlayHealing.state == COMPLETED && neopixelPlayHealing.state == COMPLETED)
            {
                systemFlags.distanceDetected = false;
                clear_healing();
                change_state(IDLE);
            }
        }
        else if (systemFlags.motionDetected)
        {
            if (neopixelPlayAttack.state == NOT_STARTED && neopixelPlayAttack.pxCreatedTask == NULL)
            {
                xTaskCreatePinnedToCore(neopixelPlayAttack.taskFunction, neopixelPlayAttack.taskName, 8192, NULL, 9, &neopixelPlayAttack.pxCreatedTask, 0);
                vTaskDelay(50 / portTICK_PERIOD_MS);
            }

            if (audioPlayAttack.state == NOT_STARTED && audioPlayAttack.pxCreatedTask == NULL)
            {
                xTaskCreatePinnedToCore(audioPlayAttack.taskFunction, audioPlayAttack.taskName, 8192, NULL, 7, &audioPlayAttack.pxCreatedTask, 1);
            }

            if ((audioPlayAttack.state == COMPLETED) && (neopixelPlayAttack.state == COMPLETED))
            {
                systemFlags.motionDetected = false;
                clear_attack();
                change_state(IDLE);
            }
        }
        break;
    case ERROR:
        Serial.println("System error occurred!");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        xTaskCreate(errorHandler.taskFunction, errorHandler.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 5, &errorHandler.pxCreatedTask);
        break;
    default:
        Serial.println("Unknown system state!");
        break;
    }

    // vTaskStartScheduler();
}

void app_init()
{
    // Sensor-Initialisierung auf Core 0
    BaseType_t result1 = xTaskCreatePinnedToCore(
        spiffsInit.taskFunction, spiffsInit.taskName, 8192, NULL, 10, &spiffsInit.pxCreatedTask, 1);

    BaseType_t result = xTaskCreatePinnedToCore(
        sensorsInit.taskFunction, sensorsInit.taskName, configMINIMAL_STACK_SIZE * 3, NULL, 9, &sensorsInit.pxCreatedTask, 0);
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
        neoForceOff();
        break;
    case ACTIVE:
        disableLIS3DHInterrupt();
        break;
    case ERROR:
        if (distMeasure.pxCreatedTask != NULL)
        {
            vTaskDelete(distMeasure.pxCreatedTask);
            distMeasure.pxCreatedTask = NULL;
        }
        if (audioPlayHealing.pxCreatedTask != NULL)
        {
            vTaskDelete(audioPlayHealing.pxCreatedTask);
            audioPlayHealing.pxCreatedTask = NULL;
        }
        if (audioPlayAttack.pxCreatedTask != NULL)
        {
            vTaskDelete(audioPlayAttack.pxCreatedTask);
            audioPlayAttack.pxCreatedTask = NULL;
        }
        if (neopixelPlayHealing.pxCreatedTask != NULL)
        {
            vTaskDelete(neopixelPlayHealing.pxCreatedTask);
            neopixelPlayHealing.pxCreatedTask = NULL;
        }
        if (neopixelPlayAttack.pxCreatedTask != NULL)
        {
            vTaskDelete(neopixelPlayAttack.pxCreatedTask);
            neopixelPlayAttack.pxCreatedTask = NULL;
        }
        disableLIS3DHInterrupt();
        neoForceOff();
        break;
    default:
        if (distMeasure.pxCreatedTask != NULL)
        {
            vTaskDelete(distMeasure.pxCreatedTask);
            distMeasure.pxCreatedTask = NULL;
        }
        if (audioPlayHealing.pxCreatedTask != NULL)
        {
            vTaskDelete(audioPlayHealing.pxCreatedTask);
            audioPlayHealing.pxCreatedTask = NULL;
        }
        if (audioPlayAttack.pxCreatedTask != NULL)
        {
            vTaskDelete(audioPlayAttack.pxCreatedTask);
            audioPlayAttack.pxCreatedTask = NULL;
        }
        if (neopixelPlayHealing.pxCreatedTask != NULL)
        {
            vTaskDelete(neopixelPlayHealing.pxCreatedTask);
            neopixelPlayHealing.pxCreatedTask = NULL;
        }
        if (neopixelPlayAttack.pxCreatedTask != NULL)
        {
            vTaskDelete(neopixelPlayAttack.pxCreatedTask);
            neopixelPlayAttack.pxCreatedTask = NULL;
        }
        disableLIS3DHInterrupt();
        neoForceOff();
        break;
    }
}