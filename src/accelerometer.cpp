/*accelerometer.cpp*/

#include <Arduino.h>
#include "accelerometer.hpp"

// I2C
const int SDA_PIN = 21;       // Custom SDA pin
const int SCL_PIN = 22;       // Custom SCL pin
const int INTERRUPT_PIN = 13; // Interrupt pin

Adafruit_LIS3DH lis;
sensors_event_t event;

void scanAdresse()
{
  Wire.begin(SDA_PIN, SCL_PIN, 400000);
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  Serial.begin(115200);
  while (!Serial)
    ;
  Serial.println("\nI2C Scanner");
  for (byte address = 1; address < 127; ++address)
  {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0)
    {
      Serial.print("Found I2C device at address 0x");
      Serial.println(address, HEX);
    }
  }
  Serial.println("nopes\n");
}

void accStart()
{
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN, 400000);

  // I2C
  lis = Adafruit_LIS3DH();

  while (!Serial)
    delay(10);

  Serial.println("LIS3DH test!");

  if (!lis.begin(0x18))
  { // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
  }

  Serial.println("LIS3DH found!");

  lis.setRange(LIS3DH_RANGE_2_G); // 2, 4, 8 or 16 G!

  lis.setDataRate(LIS3DH_DATARATE_10_HZ);
  // measureWithEvent();
  //  measure();
  lis.setClick(1, 100);
}

void getTapEvent()
{
  if (lis.getClick())
  {
    Serial.println("Tap erkannt!");
    Serial.println(".");
  }
}

void interruptHandler()
{
  // This function will be called when a motion interrupt is detected
  Serial.println("Motion detected!");
}

void measure()
{
  lis.read(); // get X Y and Z data at once
              // Then print out the raw data
  Serial.print("X:  ");
  Serial.print(lis.x);
  Serial.print("  \tY:  ");
  Serial.print(lis.y);
  Serial.print("  \tZ:  ");
  Serial.print(lis.z);
  Serial.println();

  delay(1000);
}