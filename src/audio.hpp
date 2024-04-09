/*audio.hpp*/

#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "memory.hpp"
#include "I2S.h"

// MP3 files on SD-Card
extern AudioFileSourceSD *sdFileHeal;
// AudioFileSourceSD *sdFileAttack;

// MP3 files on flash-memory
extern File flashFileHeal;

// Audio pointer auf MP3 files on flash-memory
extern AudioFileSourceSPIFFS *flashSource;

// extern int DACPin;
extern AudioOutputI2S *i2s_audio;
extern AudioGeneratorMP3 *mp3;

void startMusic();
void mp3Decode();
void playMusic();
void freeFlash();

#endif // AUDIO_HPP