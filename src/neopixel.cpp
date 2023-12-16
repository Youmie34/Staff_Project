/*neopixel.cpp*/

#include <Arduino.h>
#include "neopixel.hpp"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void neopixelStart()
{
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    strip.setBrightness(0);

    while (1)
    {
        // healing();
        /*
                // Some example procedures showing how to display to the pixels:
                colorWipe(strip.Color(0, 255, 0), 50);   // Green
                colorWipe(strip.Color(255, 0, 0), 50);   // Red
                colorWipe(strip.Color(0, 0, 255), 50);   // Blue
                colorWipe(strip.Color(194, 30, 86), 50); // Rose Red
                //  Send a theater pixel chase in...
                theaterChase(strip.Color(216, 96, 27), 50);   // Pink
                theaterChase(strip.Color(35, 26, 126), 100);  // Indigo
        */
        healing();
        /*
        attack();
        default_LED();
        */
    }
}

void healing()
{
    increaseBrightness(0);
    decreaseBrightness(250);
}

void attack()
{
}

void default_LED()
{
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait)
{
    for (uint16_t i = 0; i < strip.numPixels(); i++)
    {
        strip.setPixelColor(i, c);
        strip.show();
        delay(wait);
    }
}

void rainbow(uint8_t wait)
{
    uint16_t i, j;

    for (j = 0; j < 256; j++)
    {
        for (i = 0; i < strip.numPixels(); i++)
        {
            strip.setPixelColor(i, Wheel((i + j) & 255));
        }
        strip.show();
        delay(wait);
    }
}

void reverseRainbow(uint8_t wait)
{
    uint16_t i, j;

    for (int j = 255; j >= 0; j--)
    { // Count down from 255 to 0
        for (int i = 0; i < strip.numPixels(); i++)
        {
            strip.setPixelColor(i, Wheel((i + j) & 255));
        }
        strip.show();
        delay(wait);
    }
}

// Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait)
{
    for (int j = 0; j < 10; j++)
    { // do 10 cycles of chasing
        for (int q = 0; q < 3; q++)
        {
            for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
            {
                strip.setPixelColor(i + q, c); // turn every third pixel on
            }
            strip.show();

            delay(wait);

            for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
            {
                strip.setPixelColor(i + q, 0); // turn every third pixel off
            }
        }
    }
}

void increaseBrightness(uint8_t brightness)
{
    while (brightness < 250)
    {
        strip.setBrightness(brightness);
        rainbow(5);
        brightness += 10;
        printf("Increase: %d\n", brightness);
    }
}

void decreaseBrightness(uint8_t brightness)
{
    while (brightness > 0)
    {
        strip.setBrightness(brightness);
        reverseRainbow(5);
        brightness-=10;
        printf("Decrease: %d\n", brightness);
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170)
    {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}