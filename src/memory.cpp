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

  Serial.printf("Sample MP3 playback can begin\n");

  // saveInSPIFFS("/heal.mp3");
  // saveInSPIFFS("/attack.mp3");

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
  // Serial.println("Datei im SPIFFS zum Schreiben geöffnet");

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
      // Serial.println("finished!\n");
      break;
    }
  }

  // files no longer need to be open!
  sdFile->close();
  // flashFile.close();

  // Serial.println("MP3-Datei erfolgreich von der SD-Karte ins SPIFFS kopiert");
}