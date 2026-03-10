/*memory.cpp*/

#include "memory.hpp"
#include "FS.h"

// custom pins for the SPI communication
int sck = 18;
int miso = 19;
int mosi = 23;
int cs = 2;

// init global variables
AudioFileSourceSD *sdFile = nullptr;
File flashFile;
AudioFileSourceSPIFFS *flashSource = nullptr;

void checkSPIFFSStorage()
{
  size_t totalBytes = SPIFFS.totalBytes();
  size_t usedBytes = SPIFFS.usedBytes();

  Serial.println("SPIFFS Storage Info:");
  Serial.printf("Total Bytes: %u\n", totalBytes);
  Serial.printf("Used Bytes: %u\n", usedBytes);
  Serial.printf("Free Bytes: %u\n", totalBytes - usedBytes);
}

void setupMemory()
{

  SPI.begin(sck, miso, mosi, cs);

  // start connection to sd-card
  if (!SD.begin())
  {
    Serial.println("Card Mount Failed");
    change_state(ERROR);
    return;
  }

  // start connection to esp32 flash-memory
  if (!SPIFFS.begin())
  {
    Serial.println("SPIFFS konnte nicht initialisiert werden.");
    change_state(ERROR);
    return;
  }
  listSPIFFSFiles();
  formatSPIFFS();

  // Serial.println("saved heal and attack mp3 in SPIFFS\n");
}

void saveInSPIFFS(String filename)
{ // SD_card
  sdFile = new AudioFileSourceSD(filename.c_str());
  if (!sdFile->isOpen())
  {
    Serial.println("Fehler beim Öffnen der Datei auf der SD-Karte");
    sdFile->close();
    SPIFFS.end(); // SPIFFS-Verbindung trennen
    change_state(ERROR);
    return;
  }
  // Serial.println("MP3-Datei auf der SD-Karte geöffnet");

  // flash-speicher
  flashFile = SPIFFS.open(filename, "w"); // Öffnen der Datei im SPIFFS zum Schreiben
  if (!flashFile)
  {
    Serial.println("Fehler beim Öffnen der Datei im SPIFFS zum Schreiben");
    flashFile.close();
    change_state(ERROR);
    if (SPIFFS.remove(filename))
    {
      Serial.println("- file deleted");
    }
    else
    {
      Serial.println("- delete failed");
      sdFile->close();
      SPIFFS.end(); // SPIFFS-Verbindung trennen
      return;
    }
  }

  // Lesen von Daten von der SD-Karte und Schreiben in die Datei im SPIFFS
  // Kopieren der MP3-Datei von der SD-Karte ins SPIFFS
  byte buffer[512];

  // Serial.print("writing");

  while (int bytesRead = sdFile->read(buffer, sizeof(buffer)))
  {
    if (bytesRead > 0)
    {
      flashFile.write(buffer, bytesRead);
      // Serial.print(".");
    }
    else
    {
      break;
    }
  }

  // files no longer need to be open!
  sdFile->close();
  flashFile.close();
}

void listSPIFFSFiles()
{
  Serial.println("Dateien im SPIFFS:");
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while (file)
  {
    Serial.printf("  %s - %u Bytes\n", file.name(), file.size());
    file = root.openNextFile();
  }
}

void formatSPIFFS()
{
  Serial.println("Formatiere SPIFFS...");
  if (SPIFFS.format())
  {
    Serial.println("SPIFFS erfolgreich formatiert.");
  }
  else
  {
    Serial.println("Fehler beim Formatieren von SPIFFS.");
  }
}