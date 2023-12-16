#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Declare the NeoPixel object globally
extern Adafruit_NeoPixel strip;
const int PIN = 4; // Pin on ESP32
uint32_t Wheel(byte WheelPos);

//start
void neopixelStart();

//functions for animation start
void healing(); // if input from distance
void attack(); // if input from accelerometer
void default_LED(); // default

//animations
void colorWipe(uint32_t c, uint8_t wait);
void rainbow(uint8_t wait);
void reverseRainbow(uint8_t wait);
void theaterChase(uint32_t c, uint8_t wait);
void increaseBrightness(uint8_t brightness);
void decreaseBrightness(uint8_t brightness);

#endif // NEOPIXEL_H
