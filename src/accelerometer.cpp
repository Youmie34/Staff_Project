/*accelerometer.cpp*/

#include <Arduino.h>
#include "accelerometer.hpp"

// SPI
const int LIS3DH_SCLK = 18;
const int LIS3DH_MISO = 19;
const int LIS3DH_MOSI = 23;
const int LIS3DH_CS = 2;

// I2C
const int SDA_PIN = 21; // Custom SDA pin
const int SCL_PIN = 22; // Custom SCL pin

Adafruit_LIS3DH lis;

void accStart()
{
  Serial.begin(115200);
  SPI.begin(LIS3DH_SCLK, LIS3DH_MISO, LIS3DH_MOSI, LIS3DH_CS);
  // Example settings (1 MHz, MSB first, SPI mode 0)
  //SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  // Wire.begin(SDA_PIN, SCL_PIN, 400000);

  // SPI
  Adafruit_LIS3DH lis = Adafruit_LIS3DH();

  // I2C
  // Adafruit_LIS3DH lis = Adafruit_LIS3DH();

  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("LIS3DH test!");

  if (!lis.begin(0x18))
  { // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1)
      yield();
  }
  Serial.println("LIS3DH found!");

  // sensitivity
  lis.setRange(LIS3DH_RANGE_4_G); // 2, 4, 8 or 16 G!

  Serial.print("Range = ");
  Serial.print(2 << lis.getRange());
  Serial.println("G");

  // lis.setDataRate(LIS3DH_DATARATE_50_HZ);
  Serial.print("Data rate set to: ");
  switch (lis.getDataRate())
  {
  case LIS3DH_DATARATE_1_HZ:
    Serial.println("1 Hz");
    break;
  case LIS3DH_DATARATE_10_HZ:
    Serial.println("10 Hz");
    break;
  case LIS3DH_DATARATE_25_HZ:
    Serial.println("25 Hz");
    break;
  case LIS3DH_DATARATE_50_HZ:
    Serial.println("50 Hz");
    break;
  case LIS3DH_DATARATE_100_HZ:
    Serial.println("100 Hz");
    break;
  case LIS3DH_DATARATE_200_HZ:
    Serial.println("200 Hz");
    break;
  case LIS3DH_DATARATE_400_HZ:
    Serial.println("400 Hz");
    break;

  case LIS3DH_DATARATE_POWERDOWN:
    Serial.println("Powered Down");
    break;
  case LIS3DH_DATARATE_LOWPOWER_5KHZ:
    Serial.println("5 Khz Low Power");
    break;
  case LIS3DH_DATARATE_LOWPOWER_1K6HZ:
    Serial.println("16 Khz Low Power");
    break;
  }
  measure();
}

void measure()
{

  while (1)
  {
    lis.read(); // get X Y and Z data at once
    // Then print out the raw data
    Serial.print("X:  ");
    Serial.print(lis.x);
    Serial.print("  \tY:  ");
    Serial.print(lis.y);
    Serial.print("  \tZ:  ");
    Serial.print(lis.z);

    /* Or....get a new sensor event, normalized */
    sensors_event_t event;
    lis.getEvent(&event);

    /* Display the results (acceleration is measured in m/s^2) */
    Serial.print("\t\tX: ");
    Serial.print(event.acceleration.x);
    Serial.print(" \tY: ");
    Serial.print(event.acceleration.y);
    Serial.print(" \tZ: ");
    Serial.print(event.acceleration.z);
    Serial.println(" m/s^2 ");

    Serial.println();

    delay(200);
  }
}