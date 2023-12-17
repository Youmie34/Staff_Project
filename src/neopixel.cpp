/*neopixel.cpp*/

#include <Arduino.h>
#include "neopixel.hpp"

uint8_t minValue = 1;
uint8_t maxValue = 250;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void neopixelStart()
{
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    strip.setBrightness(70);

    while (1)
    {
        /*
        // Some example procedures showing how to display to the pixels:
        colorWipe(strip.Color(255, 0, 200), 50); // pink
        colorWipe(strip.Color(255, 0, 0), 50);   // red
        colorWipe(strip.Color(255, 220, 0), 50); // yellow
        */

        healing();
        // attack();
        // default_LED();
    }
}

void healing()
{
    increaseBrightness(minValue);
    decreaseBrightness(maxValue);
}

void attack()
{
}

void default_LED()
{
}

void increaseBrightness(uint8_t brightness)
{
    while (brightness < 250)
    {
        strip.setBrightness(brightness);

        colorTransition(255, 0, 255, 255, 0, 0, 1000); // Transition from Pink to Red
        delay(500);                                    // Delay for visibility (adjust as needed)
        brightness += 10;
        printf("Increase: %d\n", brightness);
        if (brightness >= 250)
        {
            break; // Exit the loop when brightness reaches the desired value
        }
        colorTransition(255, 0, 0, 255, 255, 0, 1000); // Transition from Red to Yellow
        delay(500);                                    // Delay for visibility (adjust as needed)
        brightness += 10;
        printf("Increase: %d\n", brightness);

        if (brightness >= 250)
        {
            break; // Exit the loop when brightness reaches the desired value
        }
    }
    printf("Ende Schleife: %d\n", brightness); // YAAAAASSSSSSS
}

void decreaseBrightness(uint8_t brightness)
{
    while (brightness > 0)
    {
        strip.setBrightness(brightness);

        colorTransition(255, 255, 0, 255, 0, 0, 1000); // Transition from Yellow to Red
        delay(500);                                    // Delay for visibility (adjust as needed)
        brightness -= 10;
        printf("Decrease: %d\n", brightness);

        if (brightness <= 0)
        {
            break; // Exit the loop when brightness reaches the desired value
        }

        colorTransition(255, 0, 255, 255, 0, 0, 1000); // Transition from Red to Pink
        delay(500);                                    // Delay for visibility (adjust as needed)
        brightness -= 10;
        printf("Decrease: %d\n", brightness);

        if (brightness <= 0)
        {
            break; // Exit the loop when brightness reaches the desired value
        }
    }
    printf("Ende Schleife: %d\n", brightness);
}

void colorTransition(int startR, int startG, int startB, int endR, int endG, int endB, int duration)
{
    int steps = 100; // Number of steps in the transition
    int delayTime = duration / steps;

    for (int i = 0; i <= steps; i++)
    {
        int currentR = map(i, 0, steps, startR, endR);
        int currentG = map(i, 0, steps, startG, endG);
        int currentB = map(i, 0, steps, startB, endB);

        for (int j = 0; j < strip.numPixels(); j++)
        {
            strip.setPixelColor(j, strip.Color(currentR, currentG, currentB));
        }

        strip.show();
        delay(delayTime);
    }
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

/*
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
*/

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