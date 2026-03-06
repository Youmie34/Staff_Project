/*tasks.cpp*/

#include "tasks.hpp"

flags_t systemFlags;

// Define specific memory locations for task handles
TaskHandle_t SensorsInitHandle;
TaskHandle_t SDInitHandle;
TaskHandle_t SPIFFSInitHandle;
TaskHandle_t DistMeasureHandle;
TaskHandle_t AccMeasureHandle;
TaskHandle_t AudioPlayHandle;
TaskHandle_t NeopixelPlayHandle;
TaskHandle_t ErrorHandle;

// init tasks
tasks_t sensorsInit =
    {
        "SensorsInit",
        SensorsInitHandle,
        NOT_STARTED};

tasks_t sdInit =
    {
        "SDInit",
        SDInitHandle,
        NOT_STARTED};

tasks_t spiffsInit =
    {
        "SPIFFSInit",
        SPIFFSInitHandle,
        NOT_STARTED};

// idle tasks
tasks_t distMeasure =
    {
        "DistMeasure",
        DistMeasureHandle,
        NOT_STARTED};

tasks_t accMeasure =
    {
        "AccMeasure",
        AccMeasureHandle,
        NOT_STARTED};

// active tasks
tasks_t audioPlay =
    {
        "AudioPlay",
        AudioPlayHandle,
        NOT_STARTED};

tasks_t neopixelPlay =
    {
        "NeopixelPlay",
        NeopixelPlayHandle,
        NOT_STARTED};

// error tasks
tasks_t errorHandler =
    {
        "ErrorHandler",
        ErrorHandle,
        NOT_STARTED};