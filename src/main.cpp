/*main.cpp*/

#include <Arduino.h>
#include "accelerometer.hpp"
#include "distance.hpp"
#include "neopixel.hpp"
#include "memory.hpp"
#include "audio.hpp"
#include "states.hpp"

const int ledPin = 27;

void test_SRC()
{
  uint8_t src;

  Wire.beginTransmission(0x18);
  Wire.write(0x31);
  Wire.endTransmission();
  Wire.requestFrom(0x18, 1);
  src = Wire.read();

  Serial.println(src, BIN);
}

void setup()
{
  volatile system_state currentState = INIT;

  pinMode(ENFeatherPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ENFeatherPin, LOW);
  digitalWrite(ledPin, HIGH);
  digitalWrite(ENFeatherPin, HIGH);

  setupMemory();
  setupflashSourceSelect();
  neoSetup();
  setupAcc();
  ultrasonicSetup();
  // neopixelStart();
}

void loop()
{
  if (systemFlags.motionDetected)
  {
    Serial.println("Motion detected!");
    digitalWrite(ledPin, HIGH);
    // Reading INT1_SRC clears the (latched) interrupt on INT1.
    // Only read it when we're handling an interrupt; reading it all the time can
    // create repeated re-triggers.
    test_SRC();
  }
  else
  {
    Serial.println("No motion detected.");
    digitalWrite(ledPin, LOW);
  }
  delay(1000);
}