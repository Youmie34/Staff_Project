/*accelerometer.hpp*/

#ifndef ACCELEROMETER_HPP
#define ACCELEROMETER_HPP

#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "states.hpp"
#include "pins.hpp"

extern Adafruit_LIS3DH lis;
extern sensors_event_t event;

void setupAcc();
void motionISR();
void setMotionInterrupt();
void clearInterrupt();
void writeRegister(uint8_t reg, uint8_t value);
void test_SRC();
void enableLIS3DHInterrupt();
void disableLIS3DHInterrupt();

#endif // ACCELEROMETER_HPP