/*distance.cpp*/

#include <Arduino.h>
#include "distance.hpp"
#include "neopixel.hpp"

long duration;
long distance;

void ultrasonicSetup()
{
    // UART-Instanz auswählen (z. B. UART2)
    HardwareSerial mySerial(2);

    long duration = 0; // Dauer zum Berechnen der Reichweite
    long distance = 0.0;

    mySerial.begin(115200, SERIAL_8N1, echoPin, trigPin);

    pinMode(trigPin, OUTPUT); // Pins werden deklariert
    pinMode(echoPin, INPUT);
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
    Serial.print("Distanz: ");
    Serial.println(distance);

    if (distance > 0 && distance <= minimumRange)
    {
        // Signalisiert "außer Reichweite" indem -1 an den Computer ausgegeben wird und die LED aufleuchtet
        systemFlags.distanceDetected = true;
        // neopixelStart();
    }

    else
    {
        // default_LED();
        //  Turn off the LED when distance is greater than minimumRange
        // systemFlags.distanceDetected = false;
    }
}