/*audio.hpp*/

#ifndef AUDIO_HPP
#define AUDIO_HPP

#include <Arduino.h>
#if defined(ARDUINO_ARCH_RP2040)

#else
#if defined(ESP32)
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif
#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SNoDAC.h"

#ifndef STASSID
#define STASSID "Pixel"
#define STAPSK  "CaroNet4"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

// Randomly picked URL
const char *URL="http://kvbstreams.dyndns.org:8000/wkvi-am";

extern AudioGeneratorMP3 *mp3;
extern AudioFileSourceICYStream *file;
extern AudioFileSourceBuffer *buff;
extern AudioOutputI2SNoDAC *out;

void audioStart();
void playSound();
void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string);
void StatusCallback(void *cbData, int code, const char *string);

#endif // AUDIO_HPP