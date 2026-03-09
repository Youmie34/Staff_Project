/*main.cpp*/

#include <Arduino.h>
#include "accelerometer.hpp"
#include "accelerometer.hpp"
#include "distance.hpp"
#include "neopixel.hpp"
#include "memory.hpp"
#include "audio.hpp"

void setup()
{
  // neoSetup();
  // accStart();
  // ultrasonic();
  // neopixelStart();
  pinMode(DACPin, OUTPUT);
  setupMemory();
  setupflashSourceSelect();
  selectMusic();
}

void loop()
{
  // put your main code here, to run repeatedly:
}
