/*audio.hpp*/

#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "AudioFileSourceSPIFFS.h" //Zugriff auf audio-file in esp32 flash-speicher
#include "memory.hpp"

AudioOutputI2S *i2s;
AudioGeneratorMP3 *mp3;

void startMusic();
void mp3Loop();
void freeFlash();

#endif // AUDIO_HPP