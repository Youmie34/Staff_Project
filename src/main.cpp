/*main.cpp*/

#include <Arduino.h>
#include "accelerometer.hpp"
#include "accelerometer.hpp"
#include "distance.hpp"
#include "neopixel.hpp"

enum system_state
{
  INIT,
  IDLE,
  ACTIVE,
  ERROR
};

void setup()
{
<<<<<<< HEAD
  volatile system_state currentState = INIT;
  pinMode(ENFeatherPin, OUTPUT);
  digitalWrite(ENFeatherPin, LOW);
  // neoSetup();
  //  accStart();
  //   ultrasonic();
  //   neopixelStart();

  setupMemory();
  digitalWrite(ENFeatherPin, HIGH);
  setupflashSourceSelect();
=======
  neoSetup();
  // accStart();
  // ultrasonic();
  neopixelStart();
  // setupMemory();
  // startMusic();
>>>>>>> neopixel
}

void loop()
{
  // put your main code here, to run repeatedly:
  selectMusic();
}
