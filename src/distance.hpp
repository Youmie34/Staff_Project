/*distance.hpp*/

#ifndef DISTANCE_H
#define DISTANCE_H

#include "app.hpp"
#include "pins.hpp"
#include "HardwareSerial.h"

const int minimumRange = 20; // Minimale Reichweite

void ultrasonicSetup();
void ultrasonicMeasure();

#endif // DISTANCE_H