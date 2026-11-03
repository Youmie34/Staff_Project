/* memory.cpp */

#include "memory.hpp"
#include <SPI.h>
#include <SD.h>
#include <SPIFFS.h>

// Your existing SPI pins
int sck = 27;
int miso = 13;
int mosi = 14;
int cs = 4;

bool saveInSPIFFS(const char *filename)
{
  // 1. Check flash first: no SD access if file already exists
  if (SPIFFS.exists(filename))
  {
    Serial.printf("%s already exists in SPIFFS. Skipping copy.\n",
                  filename);
    return true;
  }

  Serial.printf("Copying %s from SD to SPIFFS...\n", filename);

  // 2. Open source file on SD card
  File source = SD.open(filename, FILE_READ);

  if (!source || source.isDirectory())
  {
    Serial.printf("ERROR: Cannot open %s on SD card.\n", filename);
    if (source)
      source.close();
    return false;
  }

  // 3. Open destination file in SPIFFS
  File destination = SPIFFS.open(filename, "w");

  if (!destination)
  {
    Serial.printf("ERROR: Cannot create %s in SPIFFS.\n", filename);
    source.close();
    return false;
  }

  // 4. Copy data in chunks
  uint8_t buffer[512];
  size_t totalWritten = 0;
  bool copyOK = true;

  while (source.available())
  {
    size_t bytesRead = source.read(buffer, sizeof(buffer));

    if (bytesRead == 0)
    {
      copyOK = false;
      break;
    }

    size_t bytesWritten = destination.write(buffer, bytesRead);

    if (bytesWritten != bytesRead)
    {
      copyOK = false;
      break;
    }

    totalWritten += bytesWritten;
  }

  // Close both files before checking the result
  source.close();
  destination.close();

  // 5. Verify that the destination exists and has the expected size
  File check = SPIFFS.open(filename, FILE_READ);
  bool verified = check &&
                  check.size() == totalWritten &&
                  totalWritten > 0;

  if (check)
    check.close();

  if (!copyOK || !verified)
  {
    Serial.printf("ERROR: Copy of %s failed. Removing incomplete file.\n",
                  filename);
    SPIFFS.remove(filename);
    return false;
  }

  Serial.printf("Successfully copied %s (%u bytes).\n",
                filename, (unsigned int)totalWritten);

  return true;
}

void setupMemory()
{
  Serial.begin(115200);

  // 1. Mount SPIFFS
  if (!SPIFFS.begin(true))
  {
    Serial.println("SPIFFS mount failed!");
    return;
  }

  Serial.println("SPIFFS mounted successfully.");

  // 2. Check whether both MP3 files already exist
  bool healExists = SPIFFS.exists("/heal.mp3");
  bool attackExists = SPIFFS.exists("/attack.mp3");

  if (healExists && attackExists)
  {
    Serial.println("Both MP3 files found in SPIFFS.");
    Serial.println("SD card access is not needed.");
    Serial.println("MP3 initialization complete.");
    return; // Exit without initializing or accessing SD
  }

  // 3. Only initialize SD if at least one file is missing
  Serial.println("At least one MP3 is missing. Initializing SD card...");

  SPI.begin(sck, miso, mosi, cs);

  if (!SD.begin(cs, SPI))
  {
    Serial.println("SD card mount failed!");
    return;
  }

  Serial.println("SD card mounted successfully.");

  // 4. Copy only the missing files
  if (!healExists)
    saveInSPIFFS("/heal.mp3");

  if (!attackExists)
    saveInSPIFFS("/attack.mp3");

  Serial.println("MP3 initialization complete.");
}