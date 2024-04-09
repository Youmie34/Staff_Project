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
  // put your setup code here, to run once:
  // accStart();
  // ultrasonic();
  // neopixelStart();
  setupMemory();
  startMusic();
}

void loop()
{
  // put your main code here, to run repeatedly:
}
