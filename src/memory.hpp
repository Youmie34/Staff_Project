/*memory.hpp*/

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "AudioFileSourceSD.h"
#include "SPIFFS.h" //Zugriff auf esp32 Flash-Speicher
#include "SPI.h"
#include "audio.hpp"

// SPI
extern int sck;
extern int miso;
extern int mosi;
extern int cs;

// MP3 files on SD-Card
AudioFileSourceSD *sdFileHeal;
// AudioFileSourceSD *sdFileAttack;

// MP3 files on flash-memory
File flashFileHeal;

// Audio pointer auf MP3 files on flash-memory
AudioFileSourceSPIFFS *flashSource;

void setupMemory();

#endif // MEMORY_HPP