/*main.cpp*/

#include <Arduino.h>
#include "accelerometer.hpp"
#include "distance.hpp"
#include "neopixel.hpp"
#include "memory.hpp"
#include "audio.hpp"

enum system_state
{
  INIT,
  IDLE,
  ACTIVE,
  ERROR
};

const int ledPin = 5;

void setup()
{
  volatile system_state currentState = INIT;
  pinMode(ENFeatherPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ENFeatherPin, LOW);
  digitalWrite(ledPin, LOW);
  // digitalWrite(ENFeatherPin, HIGH);
  //   neoSetup();
  setupAcc();
  //   ultrasonic();
  //   neopixelStart();

  // setupMemory();
  // setupflashSourceSelect();
}

void loop()
{
  if (motionDetected)
  {
    motionDetected = false;

    Serial.println("Motion detected!");
    digitalWrite(ledPin, HIGH);
    clearInterrupt();
  }
  Serial.println(digitalRead(INT_PIN));
  digitalWrite(ledPin, LOW);
  delay(1000);
}
