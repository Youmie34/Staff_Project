/*main.cpp*/

#include <Arduino.h>
#include "distance.hpp"
#include "states.hpp"
#include "app.hpp"

const int ledPin = 27;

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
  }

  Serial.println("Setup complete. Entering loop...");
}

void loop()
{
  while (1)
  {
    digitalWrite(ledPin, LOW);
    delay(1000);
    Serial.println("LED ON");
    digitalWrite(ledPin, HIGH);
    delay(1000);
    Serial.println("LED OFF");
  }
  // app_main();
}