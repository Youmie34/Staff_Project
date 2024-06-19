/*neopixel.cpp*/

#include <Arduino.h>
#include "neopixel.hpp"

uint8_t minValue = 0;
uint8_t maxValue = 253;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

// IMPORTANT: To reduce NeoPixel burnout risk, add 1000 uF capacitor across
// pixel power leads, add 300 - 500 Ohm resistor on first pixel's data input
// and minimize distance between Arduino and first pixel.  Avoid connecting
// on a live circuit...if you must, connect GND first.

void neopixelStart()
{
    strip.begin();
    strip.setBrightness(90);
    strip.show(); // Initialize all pixels to 'off'

    while (1)
    {

        // Some example procedures showing how to display to the pixels:
        // colorWipe(strip.Color(255, 0, 200), 100); // pink
        // theaterChase(strip.Color(255, 109, 84), 120); // White
        // theaterChase(strip.Color(255, 100, 00), 120); // yellow
        // colorWipe(strip.Color(255, 0, 0), 120);   // red
        // colorWipe(strip.Color(255, 220, 0), 50); // yellow

        healing();
        // attack();
        //   default_LED();
    }
}

void healing()
{
    printf("healing");
    strip.Color(255, 0, 200);
    glowUp(minValue);
    quadIncreaseBrightness(minValue);
    quadDecreaseBrightness(maxValue);
}

void attack()
{
    printf("attack");
    theaterChase(strip.Color(200, 0, 255), 120); // violet
    theaterChase(strip.Color(255, 0, 40), 120);  // pink
    theaterChase(strip.Color(255, 0, 0), 120);   // red
    theaterChase(strip.Color(200, 0, 255), 120); // violet
    theaterChase(strip.Color(200, 0, 255), 120); // violet
}

void default_LED()
{
}

void glowUp(uint8_t brightness)
{
    // Gradual increase in brightness
    if (brightness < 250)
    {
        long in_Min = 0;
        long in_Max = 250;
        long out_Min = 1;
        long out_Max = 250;

        // Adjust the rate of increase based on the current brightness level
        uint8_t increment = map(brightness, 0, 255, 1, 100);

        brightness += increment;

        // Set the brightness for the NeoPixels
        strip.setBrightness(brightness);

        // Update NeoPixels
        strip.show();
        printf("%d", brightness);
        // Add a delay to control the speed of the increase
        delay(50);
    }

    // Reset brightness to 0 after reaching maximum (optional)
    if (brightness >= 255)
    {
        brightness = 0;
    }
}

void quadIncreaseBrightness(uint8_t brightness)
{
    printf("Beginn Increase\n");
    int x = 0;

    while (brightness < 250)
    {
        strip.setBrightness(brightness);
        colorTransition(255, 255, 0, 0, 255, 255, 1000); // Transition from Yellow to Teal, letzte Aktion bevor break!
        delay(500);
        // Delay for visibility (adjust as needed)
        brightness = brightness + uint8_t(pow(2, x));
        x++;
        printf("Increase1: %d\n", brightness);

        if (brightness > 250)
        {
            break; // Exit the loop when brightness reaches the desired value
        }

        strip.setBrightness(brightness);
        colorTransition(0, 255, 255, 255, 0, 255, 1000); // Transition from Teal to Pink
        delay(500);
        // Delay for visibility (adjust as needed)
        // TODO: currentbrightness zu newbrightness per for-loop
        brightness = brightness + uint8_t(pow(2, x));
        printf("Increase2: %d\n", brightness);

        if (brightness > 250)
        {
            break; // Exit the loop when brightness reaches the desired value
        }

        strip.setBrightness(brightness);
        colorTransition(255, 0, 255, 0, 255, 255, 1000); // Transition from Pink to Teal
        delay(500);
        // Delay for visibility (adjust as needed)
        brightness = brightness + uint8_t(pow(2, x));
        x++;
        printf("Increase3: %d\n", brightness);

        if (brightness > 250)
        {
            break; // Exit the loop when brightness reaches the desired value
        }

        strip.setBrightness(brightness);
        colorTransition(0, 255, 255, 255, 255, 0, 1000); // Transition from Teal to Yellow
        delay(500);
        // Delay for visibility (adjust as needed)
        brightness = brightness + uint8_t(pow(2, x));
        printf("Increase4: %d\n", brightness);

        if (brightness > 250)
        {
            break; // Exit the loop when brightness reaches the desired value
        }
    }
    printf("Ende Schleife: %d\n", brightness);
}

void quadDecreaseBrightness(uint8_t brightness)
{
    printf("Beginn Decrease\n");
    int x = 6;

    while (brightness >= 1)
    {
        strip.setBrightness(brightness);
        colorTransition(0, 255, 255, 255, 0, 255, 1000); // Transition from Teal to Pink
        delay(500);
        // Delay for visibility (adjust as needed)
        brightness = brightness - uint8_t(pow(2, x));
        printf("Decrease1: %d\n", brightness);

        if (brightness == 1)
        {
            break; // Exit the loop when brightness reaches the desired value
        }

        strip.setBrightness(brightness);
        colorTransition(255, 0, 255, 0, 255, 255, 1000); // Transition from Pink to Teal
        delay(500);
        // Delay for visibility (adjust as needed)
        brightness = brightness - uint8_t(pow(2, x));
        x--;
        printf("Decrease2: %d\n", brightness);

        if (brightness == 1)
        {
            break; // Exit the loop when brightness reaches the desired value
        }

        strip.setBrightness(brightness);
        colorTransition(0, 255, 255, 255, 255, 0, 1000); // Transition from Teal to Yellow
        delay(500);
        // Delay for visibility (adjust as needed)
        brightness = brightness - uint8_t(pow(2, x));
        printf("Decrease3: %d\n", brightness);

        if (brightness == 1)
        {
            break; // Exit the loop when brightness reaches the desired value
        }

        strip.setBrightness(brightness);
        colorTransition(255, 255, 0, 0, 255, 255, 1000); // Transition from Yellow to Teal
        delay(500);
        // Delay for visibility (adjust as needed)
        brightness = brightness - uint8_t(pow(2, x));
        x--;
        if (brightness == 1)
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