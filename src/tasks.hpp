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
extern tasks_t memoryInit;
// idle tasks
extern tasks_t distMeasure;
extern tasks_t accMeasure;
// active tasks
extern tasks_t audioPlay;
extern tasks_t neopixelPlay;
// error tasks
extern tasks_t errorHandler;

extern TaskHandle_t SensorsInitHandle;
extern TaskHandle_t SDInitHandle;
extern TaskHandle_t SPIFFSInitHandle;
extern TaskHandle_t DistMeasureHandle;
extern TaskHandle_t AccMeasureHandle;
extern TaskHandle_t AudioPlayHandle;
extern TaskHandle_t NeopixelPlayHandle;
extern TaskHandle_t ErrorHandle;

#endif // TASKS_HPP