/*audio.hpp*/

#ifndef AUDIO_HPP
#define AUDIO_HPP

#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "memory.hpp"

// MP3 files on SD-Card
extern AudioFileSourceSD *sdFileHeal;
// AudioFileSourceSD *sdFileAttack;

// MP3 files on flash-memory
extern File flashFileHeal;

// Audio pointer auf MP3 files on flash-memory
extern AudioFileSourceSPIFFS *flashSource;

extern AudioOutputI2S *i2s;
extern AudioGeneratorMP3 *mp3;

void startMusic();
void mp3Loop();
void freeFlash();

#endif // AUDIO_HPP