/*memory.cpp*/

#include "memory.hpp"

// custom pins for the SPI communication
int sck = 18;
int miso = 19;
int mosi = 23;
int cs = 2;

// init global variables
AudioFileSourceSD *sdFileHeal = nullptr;
File flashFileHeal;
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
  if (!SD.begin())
  {
    Serial.println("Card Mount Failed");
    return;
  }

  // start connection to esp32 flash-memory
  if (!SPIFFS.begin())
  {
    Serial.println("SPIFFS konnte nicht initialisiert werden.");
    return;
  }

  Serial.printf("Sample MP3 playback begins...\n");

  // SD_card
  sdFileHeal = new AudioFileSourceSD("/heal.mp3");
  if (!sdFileHeal->isOpen())
  {
    Serial.println("Fehler beim Öffnen der Datei auf der SD-Karte");
    sdFileHeal->close();
    SPIFFS.end(); // SPIFFS-Verbindung trennen
    return;
  }
  Serial.println("MP3-Datei auf der SD-Karte geöffnet");

  // flash-speicher
  flashFileHeal = SPIFFS.open("/heal.mp3", "w"); // Öffnen der Datei im SPIFFS zum Schreiben
  if (!flashFileHeal)
  {
    Serial.println("Fehler beim Öffnen der Datei im SPIFFS zum Schreiben");
    flashFileHeal.close();
    if (SPIFFS.remove("/heal.mp3"))
    {
      Serial.println("- file deleted");
    }
    else
    {
      Serial.println("- delete failed");
      sdFileHeal->close();
      SPIFFS.end(); // SPIFFS-Verbindung trennen
      return;
    }
  }
  Serial.println("Datei im SPIFFS zum Schreiben geöffnet");

  // Lesen von Daten von der SD-Karte und Schreiben in die Datei im SPIFFS
  // Kopieren der MP3-Datei von der SD-Karte ins SPIFFS
  byte buffer[512];

  Serial.print("writing");

  while (int bytesRead = sdFileHeal->read(buffer, sizeof(buffer)))
  {
    if (bytesRead > 0)
    {
      flashFileHeal.write(buffer, bytesRead);
      Serial.print(".");
    }
    else
    {
      Serial.println("finished!");
      break;
    }
  }

  // files no longer need to be open!
  sdFileHeal->close();
  flashFileHeal.close();

  Serial.println("MP3-Datei erfolgreich von der SD-Karte ins SPIFFS kopiert");
}