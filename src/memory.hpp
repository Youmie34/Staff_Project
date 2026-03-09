/*memory.hpp*/

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "AudioFileSourceSD.h"
#include "SPIFFS.h"                //Zugriff auf esp32 Flash-Speicher
#include "AudioFileSourceSPIFFS.h" //Zugriff auf audio-file in esp32 flash-speicher
#include "SPI.h"
#include "audio.hpp"
#include <string.h>

// SPI
extern int sck;
extern int miso;
extern int mosi;
extern int cs;

// MP3 files on SD-Card
extern AudioFileSourceSD *sdFile;

// MP3 files on flash-memory
extern File flashFile;

// Audio pointer auf MP3 files on flash-memory
extern AudioFileSourceSPIFFS *flashSource;

extern AudioOutputI2S *i2s_audio;
extern AudioGeneratorMP3 *mp3;

void setupMemory();
void saveInSPIFFS(String filename);
void checkSPIFFSStorage();
void listSPIFFSFiles();
void formatSPIFFS();

#endif // MEMORY_HPP