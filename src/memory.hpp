/*memory.hpp*/

#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "FS.h"
#include "SD.h"
#include "SPI.h"

// SPI
extern int sck;
extern int miso;
extern int mosi;
extern int cs;

void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
void readFile(fs::FS &fs, const char *path);
void setupMemory();

#endif // MEMORY_HPP