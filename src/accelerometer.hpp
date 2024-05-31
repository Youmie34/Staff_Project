#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// I2C
extern const int SDA_PIN;
extern const int SCL_PIN;
extern const int INTERRUPT_PIN;

extern Adafruit_LIS3DH lis;
extern sensors_event_t event;

void accStart();
void measure();
void interruptHandler();
void measureWithEvent();