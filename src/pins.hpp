#ifndef PINS_HPP
#define PINS_HPP

#include <Arduino.h>
#include "accelerometer.hpp"
#include "audio.hpp"

// I2C
extern const int SDA_PIN;
extern const int SCL_PIN;
extern const int INT_PIN;

extern const int DACPin;       // Pin für den DAC-Ausgang
extern const int ENFeatherPin; // Pin zum Aktivieren des Feather Audio Boards

// UART
extern const int echoPin; // Echo Pin RX (green)
extern const int trigPin; // Trigger Pin TX (yellow)

// SPI
extern const int sck;
extern const int miso;
extern const int mosi;
extern const int cs;

// Neopixel
extern const int PIN; // Pin on ESP32

void init_gpios();
void setup_interrupts();

#endif // PINS_HPP