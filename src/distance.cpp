#include <Arduino.h>
#include "neopixel.cpp"

#define echoPin 16 // Echo Pin
#define trigPin 17 // Trigger Pin
#define LEDPin 5   // Pin der LED

int minimumRange = 4;    // Minimale Reichweite
long duration, distance; // Dauer zum Berechnen der Reichweite

void ultrasonic()
{
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
        duration = pulseIn(echoPin, HIGH);

        // Formel zum Berechnen der Entfernung basierend auf der Schallgeschwindigkeit
        distance = duration / 58.2;

        if (distance <= minimumRange)
        {
            // Signalisiert "außer Reichweite" indem -1 an den Computer ausgegeben wird und die LED aufleuchtet
            Serial.println("ich leuchte :D");
            digitalWrite(LEDPin, HIGH);
        }
    }
}