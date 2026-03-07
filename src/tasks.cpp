/*tasks.cpp*/

#include "tasks.hpp"

flags_t systemFlags;

// init tasks
tasks_t sensorsInit =
    {
        "SensorsInit",
        sens_init,
        NOT_STARTED,
};

tasks_t sdInit =
    {
        "SDInit",
        sd_init,
        NOT_STARTED};

tasks_t spiffsInit =
    {
        "SPIFFSInit",
        spiffs_init,
        NOT_STARTED};

// idle tasks
tasks_t distMeasure =
    {
        "DistMeasure",
        dist_measure,
        NOT_STARTED};

tasks_t accMeasure =
    {
        "AccMeasure",
        acc_measure,
        NOT_STARTED};

// active tasks
tasks_t audioPlay =
    {
        "AudioPlay",
        audio_play,
        NOT_STARTED};

tasks_t neopixelPlay =
    {
        "NeopixelPlay",
        neopixel_play,
        NOT_STARTED};

// error tasks
tasks_t errorHandler =
    {
        "ErrorHandler",
        error_handler,
        NOT_STARTED};

void sens_init(void *parameter)
{
}

void sd_init(void *parameter)
{
}

void spiffs_init(void *parameter)
{
}

void dist_measure(void *parameter)
{
}

void acc_measure(void *parameter)
{
}

void audio_play(void *parameter)
{
}

void neopixel_play(void *parameter)
{
}

void error_handler(void *parameter)
{
}