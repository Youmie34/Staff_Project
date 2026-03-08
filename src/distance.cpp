/*distance.cpp*/

#include <Arduino.h>
#include "distance.hpp"
#include "neopixel.hpp"

// Define global variables for duration and distance
volatile long duration = 0; // Dauer zum Berechnen der Reichweite
volatile long distance = 0; // Entfernung in cm

volatile bool distanceDetected = false;

void ultrasonicSetup()
{
    pinMode(trigPin, OUTPUT); // Pins werden deklariert
    pinMode(echoPin, INPUT);
    pinMode(LEDPin, OUTPUT);
}

void ultrasonicMeasure()
{
    // TrigPin/echoPin Zyklus zum Berechnen der Entfernung
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(10);
    duration = pulseIn(echoPin, HIGH);

    // Formel zum Berechnen der Entfernung basierend auf der Schallgeschwindigkeit
    distance = duration / 58.2;

    if (distance > 0 && distance <= minimumRange)
    {
        // Signalisiert "außer Reichweite" indem -1 an den Computer ausgegeben wird und die LED aufleuchtet
        distanceDetected = true;
        // digitalWrite(LEDPin, HIGH);
        // neopixelStart();
        // delay(5000);
    }

    else
    {
        // default_LED();
        //  Turn off the LED when distance is greater than minimumRange
        //  digitalWrite(LEDPin, LOW);
    }
}