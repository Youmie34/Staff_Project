/*distance.hpp*/

#ifndef DISTANCE_H
#define DISTANCE_H

const int echoPin = 16; // Echo Pin (green)
const int trigPin = 17; // Trigger Pin (yellow)
const int LEDPin = 5;   // Pin der LED

const int minimumRange = 8; // Minimale Reichweite

void ultrasonic();

#endif // DISTANCE_H