/*main.cpp*/

#include <Arduino.h>
#include "distance.hpp"
#include "states.hpp"
#include "app.hpp"

const int ledPin = 27;

void led_test()
{
  digitalWrite(ledPin, LOW);
  delay(1000);
  digitalWrite(ledPin, HIGH);
  delay(1000);
}

void setup()
{
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  Serial.begin(115200);
  while (!Serial)
  {
    delay(10);
  }
  app_init();
}

void loop()
{
  led_test();

  if ((systemFlags.audioInitialized && systemFlags.sensorsInitialized) == true)
  {
    app_main_function();
  }

  else
  {
    Serial.println("System not initialized yet.");
  }
}