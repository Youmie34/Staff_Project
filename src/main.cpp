/*main.cpp*/

#include <Arduino.h>
#include "distance.hpp"
#include "states.hpp"
#include "app.hpp"

const int ledPin = 27;

volatile bool systemInitialized = false;

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

  if (!app_init())
  {
    Serial.println("Error initializing app");
    change_state(ERROR);
  }
  else
  {
    Serial.println("App initialized successfully");
    systemInitialized = true;
    change_state(IDLE);
  }
}

void loop()
{
  led_test();

  if (systemInitialized)
  {
    app_main_function();
  }

  else
  {
    Serial.println("System not initialized yet.");
  }
}