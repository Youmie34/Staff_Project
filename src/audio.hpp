/*audio.hpp*/

#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "memory.hpp"
#include "I2S.h"
#include <string.h>

const int DACPin = 26; // Pin für den DAC-Ausgang
const int PWRPin = 15;
extern const char *filenameHeal;
extern const char *filenameAttack;

// MP3 files on SD-Card
extern AudioFileSourceSD *sdFile;

// MP3 files on flash-memory
extern File flashFile;

// Audio pointer auf MP3 files on flash-memory
extern AudioFileSourceSPIFFS *flashSourceSelect;
extern AudioFileSourceSPIFFS *flashSourceHeal;
extern AudioFileSourceSPIFFS *flashSourceAttack;

// extern int DACPin;
extern AudioOutputI2S *i2s_audio;
extern AudioGeneratorMP3 *mp3;

void startMusic(AudioFileSourceSPIFFS *flashSourceSelect, const char *filename);
void mp3Decode();
void playMusic();
void freeFlash();
void selectMusic();
void setupflashSourceSelect();
void freeResources();

#endif // AUDIO_HPP