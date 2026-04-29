/*main.cpp*/

#include <Arduino.h>
#include "distance.hpp"
#include "states.hpp"
#include "app.hpp"

void setup()
{
  ultrasonicSetup();

  // app_init();
}

void loop()
{
  ultrasonicMeasure();
  // app_main_function();
}