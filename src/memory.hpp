/*memory.hpp*/

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "AudioFileSourceSD.h"
#include "SPIFFS.h"                //Zugriff auf esp32 Flash-Speicher
#include "AudioFileSourceSPIFFS.h" //Zugriff auf audio-file in esp32 flash-speicher
#include "SPI.h"
#include "audio.hpp"

// SPI
extern int sck;
extern int miso;
extern int mosi;
extern int cs;

// MP3 files on SD-Card
extern AudioFileSourceSD *sdFileHeal;
// AudioFileSourceSD *sdFileAttack;

// MP3 files on flash-memory
extern File flashFileHeal;

// Audio pointer auf MP3 files on flash-memory
extern AudioFileSourceSPIFFS *flashSource;

extern AudioOutputI2S *i2s;
extern AudioGeneratorMP3 *mp3;

void setupMemory();

#endif // MEMORY_HPP