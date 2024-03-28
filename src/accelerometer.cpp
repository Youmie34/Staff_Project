#include <Arduino.h>
#include "accelerometer.hpp"

// I2C
const int SDA_PIN = 21;      // Custom SDA pin
const int SCL_PIN = 22;      // Custom SCL pin
const int INTERRUPT_PIN = 9; // Interrupt pin

Adafruit_LIS3DH lis;

void accStart()
{
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN, 400000);

  // I2C
  lis = Adafruit_LIS3DH();

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

  lis.setRange(LIS3DH_RANGE_2_G); // 2, 4, 8 or 16 G!

  lis.setDataRate(LIS3DH_DATARATE_10_HZ);
  measure();
}

void interruptHandler()
{
  // This function will be called when a motion interrupt is detected
  Serial.println("Motion detected!");
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
    /*  sensors_event_t event;
       lis.getEvent(&event);

       /* Display the results (acceleration is measured in m/s^2) */
    /*   Serial.print("\t\tX: ");
      Serial.print(event.acceleration.x);
      Serial.print(" \tY: ");
      Serial.print(event.acceleration.y);
      Serial.print(" \tZ: ");
      Serial.print(event.acceleration.z);
      Serial.println(" m/s^2 ");
  */
    Serial.println();

    delay(200);
  }
}