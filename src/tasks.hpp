#ifndef TASKS_HPP
#define TASKS_HPP

#include "accelerometer.hpp"
#include "distance.hpp"
#include "neopixel.hpp"
#include "memory.hpp"
#include "audio.hpp"
#include "states.hpp"

// init tasks
extern tasks_t sensorsInit;
extern tasks_t sdInit;
extern tasks_t spiffsInit;
// idle tasks
extern tasks_t distMeasure;
extern tasks_t accMeasure;
// active tasks
extern tasks_t audioPlay;
extern tasks_t neopixelPlay;
// error tasks
extern tasks_t errorHandler;

void sens_init(void *parameter);
void sd_init(void *parameter);
void spiffs_init(void *parameter);
void dist_measure(void *parameter);
void acc_measure(void *parameter);
void audio_play(void *parameter);
void neopixel_play(void *parameter);
void error_handler(void *parameter);

#endif // TASKS_HPP