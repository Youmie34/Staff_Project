/*accelerometer.cpp*/

#include <Arduino.h>
#include "accelerometer.hpp"

// I2C
const int SDA_PIN = 21; // Custom SDA pin
const int SCL_PIN = 22; // Custom SCL pin
const int INT_PIN = 13; // Interrupt pin

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

  lis.setRange(LIS3DH_RANGE_2_G); // 2, 4, 8 or 16 G!

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

  writeRegister(0x20, 0x57); // CTRL_REG1: 100Hz data rate, all axes enabled
  // High-pass filter for INT1 (AOI) so gravity/tilt doesn't constantly trigger.
  // CTRL_REG2: enable HP for interrupt 1 (HPIS1=1) and set a modest cutoff (HPCF=01).
  writeRegister(0x21, 0x11);
  writeRegister(0x30, 0b00001000); // INT1_CFG (Y high)
  writeRegister(0x32, 12);         // INT1_THS
  writeRegister(0x33, 1);          // INT1_DURATION
  writeRegister(0x24, 0x08);       // latch interrupt
  writeRegister(0x22, 0x40);       // CTRL3 -> INT1 enable

  // If INT1 is configured/open-drain or the line is long, a pullup prevents a floating input.
  pinMode(INT_PIN, INPUT_PULLUP);

  // Clear any pending/latched interrupt before enabling the ESP32 GPIO interrupt.
  clearInterrupt();
  attachInterrupt(digitalPinToInterrupt(INT_PIN), motionISR, RISING);
}

void clearInterrupt()
{
  Wire.beginTransmission(0x18);
  Wire.write(0x31); // INT1_SRC
  Wire.endTransmission();
  Wire.requestFrom(0x18, 1);
  Wire.read();
}

void IRAM_ATTR motionISR()
{
  systemFlags.motionDetected = true;
}

void test_SRC()
{
  uint8_t src;

  Wire.beginTransmission(0x18);
  Wire.write(0x31);
  Wire.endTransmission();
  Wire.requestFrom(0x18, 1);
  src = Wire.read();

  Serial.println(src, BIN);
}

void enableLIS3DHInterrupt()
{
  clearInterrupt();
  attachInterrupt(digitalPinToInterrupt(INT_PIN), motionISR, RISING); // GPIO-Interrupt aktivieren
  // Serial.println("LIS3DH Interrupt aktiviert");
}

void disableLIS3DHInterrupt()
{
  detachInterrupt(INT_PIN); // GPIO-Interrupt deaktivieren
  // Serial.println("LIS3DH Interrupt deaktiviert");
}