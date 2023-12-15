#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include <Adafruit_NeoPixel.h>

// Declare the NeoPixel object globally
extern Adafruit_NeoPixel strip;
const int PIN = 15;

void neopixelStart();
void colorWipe(uint32_t c, uint8_t wait);
void rainbow(uint8_t wait);
void rainbowCycle(uint8_t wait);
void theaterChase(uint32_t c, uint8_t wait);
void theaterChaseRainbow(uint8_t wait);
uint32_t Wheel(byte WheelPos);

#endif // NEOPIXEL_H
