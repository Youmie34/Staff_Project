/*distance.cpp*/

#include <Arduino.h>
#include "distance.hpp"

void ultrasonic()
{
    long duration = 0; // Dauer zum Berechnen der Reichweite
    long distance = 0.0;
    Serial.begin(115200);     // Im Serialmonitor die Baudrate auf 9600 einstellen
    pinMode(trigPin, OUTPUT); // Pins werden deklariert
    pinMode(echoPin, INPUT);
    pinMode(LEDPin, OUTPUT);

    while (1)
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
        Serial.print("Duration: ");
        Serial.println(duration);
        Serial.print("Distanz: ");
        Serial.println(distance);

        if (distance > 0 && distance <= minimumRange)
        {
            // Signalisiert "außer Reichweite" indem -1 an den Computer ausgegeben wird und die LED aufleuchtet
            digitalWrite(LEDPin, HIGH);
        }

        else
        {
            // Turn off the LED when distance is greater than minimumRange
            digitalWrite(LEDPin, LOW);
        }
    }
}