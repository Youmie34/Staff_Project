#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

extern const int SDA_PIN;
extern const int SCL_PIN;

extern Adafruit_LIS3DH lis;

void accStart();