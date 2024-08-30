/*accelerometer.hpp*/

#ifndef ACCELEROMETER_HPP
#define ACCELEROMETER_HPP

#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// I2C
// SPI
extern const int LIS3DH_SCLK;
extern const int LIS3DH_MISO;
extern const int LIS3DH_MOSI;
extern const int LIS3DH_CS;

// I2C
extern const int SDA_PIN;
extern const int SCL_PIN;
extern const int INTERRUPT_PIN;

extern Adafruit_LIS3DH lis;
extern sensors_event_t event;

void interruptHandler();
void measureWithEvent();

#endif // ACCELEROMETER_HPP