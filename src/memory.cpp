/*memory.cpp*/

#include "memory.hpp"

// custom pins for the SPI communication
int sck = 18;
int miso = 19;
int mosi = 23;
int cs = 2;

// init global variables
AudioFileSourceSD *sdFile = nullptr;
File flashFile;
AudioFileSourceSPIFFS *flashSource = nullptr;

void setupMemory()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(10);
  }

  SPI.begin(sck, miso, mosi, cs);

  // start connection to sd-card
  if (!SD.begin(cs))
  {
    Serial.println("Card Mount Failed");
    return;
  }

  initSPIFFS();

  // SD-Karte initialisieren
  if (!SD.begin(cs))
  {
    Serial.println("Fehler: SD-Karte konnte nicht initialisiert werden!");
    return;
  }
  Serial.println("SD-Karte erfolgreich initialisiert!");

  saveInSPIFFS(filenameHeal);
  saveInSPIFFS(filenameAttack);

  listSPIFFSFiles();
}

void saveInSPIFFS(const char *filename)
{
  // SD_card
  sdFile = new AudioFileSourceSD(filename);

  if (!sdFile->isOpen())
  {
    Serial.println("Fehler beim Öffnen der Datei auf der SD-Karte");
    // sdFile->close();
    delete sdFile; // Speicher freigeben
    return;
  }
  Serial.println("MP3-Datei auf der SD-Karte geöffnet");

  // flash-speicher
  flashFile = SPIFFS.open(filename, "w"); // Öffnen der Datei im SPIFFS zum Schreiben

  if (!flashFile)
  {
    Serial.println("Fehler beim Öffnen der Datei im SPIFFS zum Schreiben");
    delete sdFile; // Speicher freigeben
    return;
  }

  Serial.println("Datei im SPIFFS zum Schreiben geöffnet");

  // Lesen von Daten von der SD-Karte und Schreiben in die Datei im SPIFFS
  // Kopieren der MP3-Datei von der SD-Karte ins SPIFFS
  byte buffer[512];
  while (int bytesRead = sdFile->read(buffer, sizeof(buffer)))
  {
    if (bytesRead > 0)
    {
      flashFile.write(buffer, bytesRead);
    }
    else
    {
      // Serial.println("finished!\n");
      break;
    }
  }

  // Dateien schließen
  sdFile->close();
  delete sdFile; // Speicher freigeben
  flashFile.close();

  Serial.println("MP3-Datei erfolgreich von der SD-Karte ins SPIFFS kopiert");
}

void listSPIFFSFiles()
{
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while (file)
  {
    Serial.print("Datei: ");
    Serial.println(file.name());
    file = root.openNextFile();
  }
}

void initSPIFFS()
{
  // start connection to esp32 flash-memory
  if (!SPIFFS.begin(true))
  {
    Serial.println("SPIFFS konnte nicht initialisiert werden.");
    return;
  }
  Serial.println("SPIFFS erfolgreich gemountet!");
}