/*memory.hpp*/

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "AudioFileSourceSD.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"
#include "SPIFFS.h"                //Zugriff auf esp32 Flash-Speicher
#include "AudioFileSourceSPIFFS.h" //Zugriff auf audio-file in esp32 flash-speicher
#include "SPI.h"

// SPI
extern int sck;
extern int miso;
extern int mosi;
extern int cs;

// void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
// void readFile(fs::FS &fs, const char *path);
void setupMemory();
// void mp3Loop();
//  free memory
void free();

#endif // MEMORY_HPP