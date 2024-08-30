/*accelerometer.hpp*/

#ifndef ACCELEROMETER_HPP
#define ACCELEROMETER_HPP

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// SPI
extern const int LIS3DH_SCLK;
extern const int LIS3DH_MISO;
extern const int LIS3DH_MOSI;
extern const int LIS3DH_CS;

// I2C
extern const int SDA_PIN;
extern const int SCL_PIN;

extern Adafruit_LIS3DH lis;

void accStart();
void measure();

#endif // ACCELEROMETER_HPP