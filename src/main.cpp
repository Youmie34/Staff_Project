/*main.cpp*/

#include <Arduino.h>
#include "distance.hpp"
#include "states.hpp"
#include "app.hpp"

void setup()
{
  Serial.begin(115200);

  while (!Serial)
  {
    delay(10);
  }
  app_init();
}

void loop()
{

  if ((systemFlags.audioInitialized && systemFlags.sensorsInitialized) == true)
  {
    xTaskCreate(neopixelPlayHealing.taskFunction, neopixelPlayHealing.taskName, 8192, NULL, 8, NULL);
    audioPlayHealing.taskFunction(NULL);
    app_main_function();
  }

  else
  {
    Serial.println("System not initialized yet.");
  }
}