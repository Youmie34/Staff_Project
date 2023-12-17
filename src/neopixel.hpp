#ifndef NEOPIXEL_H
#define NEOPIXEL_H

#include <Adafruit_NeoPixel.h>
#include <cmath>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Global variables
extern uint8_t minValue;
extern uint8_t maxValue;

// Define main colours

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
void quadIncreaseBrightness(uint8_t brightness);
void quadDecreaseBrightness(uint8_t brightness);

void colorTransition(int startR, int startG, int startB, int endR, int endG, int endB, int duration);
void colorTransitionReverse(int startR, int startG, int startB, int endR, int endG, int endB, int duration);

#endif // NEOPIXEL_H
