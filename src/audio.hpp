/*audio.hpp*/

#ifndef AUDIO_HPP
#define AUDIO_HPP

#if defined(ARDUINO_ARCH_RP2040)
    #define WIFI_OFF
    class __x { public: __x() {}; void mode() {}; };
    __x WiFi;
#elif defined(ESP32)
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif

#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"
#include "AudioOutputMixer.h"

// VIOLA sample taken from https://ccrma.stanford.edu/~jos/pasp/Sound_Examples.html
#include "viola.h"

extern AudioGeneratorWAV *wav[2];
extern AudioFileSourcePROGMEM *file[2];
extern AudioOutputI2S *out;
extern AudioOutputMixer *mixer;
extern AudioOutputMixerStub *stub[2];

void audioStart();
void playSound();

#endif // AUDIO_HPP