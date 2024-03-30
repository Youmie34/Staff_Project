#include "memory.hpp"

// custom pins for the SPI communication
int sck = 18;
int miso = 19;
int mosi = 23;
int cs = 2;

const char *heal = "/heal.mp3";
const char *attack = "/attack.mp3";

// MP3 files on SD-Card
AudioFileSourceSD *sdFileHeal;
// AudioFileSourceSD *sdFileAttack;

// MP3 files on flash-memory
File flashFileHeal;

AudioOutputI2S *i2s;
AudioGeneratorMP3 *mp3;

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
  sdFileHeal = new AudioFileSourceSD(heal);
  if (!sdFileHeal->isOpen())
  {
    Serial.println("Fehler beim Öffnen der Datei auf der SD-Karte");
    return;
  }
  Serial.println("MP3-Datei auf der SD-Karte geöffnet");

  // flash-speicher
  flashFileHeal = SPIFFS.open(heal, "w"); // Öffnen der Datei im SPIFFS zum Schreiben
  if (!flashFileHeal)
  {
    Serial.println("Fehler beim Öffnen der Datei im SPIFFS zum Schreiben");
    return;
  }
  Serial.println("Datei im SPIFFS zum Schreiben geöffnet");

  // Lesen von Daten von der SD-Karte und Schreiben in die Datei im SPIFFS
  // Kopieren der MP3-Datei von der SD-Karte ins SPIFFS
  byte buffer[512];
  while (int bytesRead = sdFileHeal->read(buffer, sizeof(buffer)))
  {
    if (bytesRead > 0)
    {
      flashFileHeal.write(buffer, bytesRead);
    }
    else
    {
      break;
    }
  }

  // Schließen der Dateien
  sdFileHeal->close();
  flashFileHeal.close();

  Serial.println("MP3-Datei erfolgreich von der SD-Karte ins SPIFFS kopiert");

  i2s = new AudioOutputI2S(); // Initialisierung des Audioausgangs
  mp3 = new AudioGeneratorMP3();
  // mp3->begin(sdFileHeal, i2s);

  // mp3Loop();

  free();
}

void mp3Loop()
{
  while (mp3->isRunning())
  {

    if (!mp3->loop())
    {
      mp3->stop(); // Wenn die Wiedergabe abgeschlossen ist, stoppen Sie die Wiedergabe
      free();
      Serial.println("mp3 Wiedergabe abgeschlossen");
    }
    else
    {
      Serial.println("Running");
    }
  }
}

void free()
{
  delete mp3;
  delete sdFileHeal;
  delete i2s;
}