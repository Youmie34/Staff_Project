/*accelerometer.cpp*/

#include <Arduino.h>
#include "accelerometer.hpp"

// I2C
const int SDA_PIN = 21; // Custom SDA pin
const int SCL_PIN = 22; // Custom SCL pin
const int INT_PIN = 13; // Interrupt pin

volatile bool motionDetected = false;

Adafruit_LIS3DH lis;

void setupAcc()
{
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN, 400000);

  // I2C
  lis = Adafruit_LIS3DH();

  if (!lis.begin(0x18))
  { // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
  }

  else
  {
    Serial.println("LIS3DH found!");
  }

  lis.setRange(LIS3DH_RANGE_4_G); // 2, 4, 8 or 16 G!

  lis.setDataRate(LIS3DH_DATARATE_100_HZ);

  setMotionInterrupt();
}

void writeRegister(uint8_t reg, uint8_t value)
{
  Wire.beginTransmission(0x18);
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

void setMotionInterrupt()
{
  lis.enableDRDY(false, 1);

  writeRegister(0x30, 0b00001100); // INT1_CFG (Y high + low)
  writeRegister(0x32, 32);         // INT1_THS
  writeRegister(0x33, 1);          // INT1_DURATION
  writeRegister(0x22, 0x40);       // CTRL3 -> INT1 enable
  writeRegister(0x24, 0x08);       // latch interrupt

  pinMode(INT_PIN, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(INT_PIN), motionISR, RISING);
}

void clearInterrupt()
{
  motionDetected = false;

  Wire.beginTransmission(0x18);
  Wire.write(0x31); // INT1_SRC
  Wire.endTransmission();

  Wire.requestFrom(0x18, 1);
  Wire.read();
}

void motionISR()
{
  motionDetected = true;
}
