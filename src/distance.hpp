/*distance.hpp*/

#ifndef DISTANCE_H
#define DISTANCE_H

#include "HardwareSerial.h"

const int echoPin = 16; // Echo Pin RX (green)
const int trigPin = 17; // Trigger Pin TX (yellow)
const int LEDPin = 27;  // Pin der LED

const int minimumRange = 20; // Minimale Reichweite

void ultrasonic();

#endif // DISTANCE_H