#include "pins.hpp"

const int SDA_PIN = 23;
const int SCL_PIN = 22;
const int INT_PIN = 19;
const int DACPin = 25;       // Pin für den DAC-Ausgang
const int ENFeatherPin = 18; // Pin zum Aktivieren des Feather Audio Boards
const int echoPin = 16;      // Echo Pin RX (green)
const int trigPin = 17;      // Trigger Pin TX (yellow)

const int PIN = 21; // Pin on ESP32

const int sck = 27;
const int miso = 13;
const int mosi = 14;
const int cs = 4;

void init_gpios()
{

    pinMode(trigPin, OUTPUT); // Pins werden deklariert
    pinMode(echoPin, INPUT);

    pinMode(DACPin, OUTPUT);
    pinMode(ENFeatherPin, OUTPUT);
    pinMode(PIN, OUTPUT);

    pinMode(INT_PIN, INPUT_PULLUP);

    setup_interrupts();

    Serial.println("GPIOs initialized");
}

void setup_interrupts()
{
    attachInterrupt(digitalPinToInterrupt(INT_PIN), motionISR, RISING);
}