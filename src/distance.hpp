/*distance.hpp*/

#ifndef DISTANCE_H
#define DISTANCE_H

#include "states.hpp"

const int echoPin = 16; // Echo Pin
const int trigPin = 17; // Trigger Pin
const int LEDPin = 5;   // Pin der LED

const int minimumRange = 12; // Minimale Reichweite

extern volatile long duration; // Dauer zum Berechnen der Reichweite
extern volatile long distance; // Berechnete Entfernung
extern volatile bool distanceDetected;

void ultrasonicSetup();
void ultrasonicMeasure();

#endif // DISTANCE_H