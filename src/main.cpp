/*main.cpp*/

#include <Arduino.h>
#include "accelerometer.hpp"
#include "distance.hpp"
#include "neopixel.hpp"
#include "memory.hpp"
#include "audio.hpp"
#include "states.hpp"
#include "app.hpp"

const int ledPin = 27;

void setup()
{
  app_init();
}

void loop()
{
  if (systemFlags.motionDetected)
  {
  }
  else
  {
    Serial.println("No motion detected.");
    digitalWrite(ledPin, LOW);
  }
  delay(1000);
}