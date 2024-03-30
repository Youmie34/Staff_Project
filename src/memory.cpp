#include "memory.hpp"

// custom pins for the SPI communication
int sck = 18;
int miso = 19;
int mosi = 23;
int cs = 2;

const char *healP = "/heal.mp3";
const char *attackP = "/attack.mp3";

AudioGeneratorMP3 *mp3;
AudioFileSourceSD *sdFile;
AudioOutputI2S *out;

void setupMemory()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(10);
  }

  SPI.begin(sck, miso, mosi, cs);

  if (!SD.begin())
  {
    Serial.println("Card Mount Failed");
    return;
  }

  if (!SPIFFS.begin())
  {
    Serial.println("SPIFFS konnte nicht initialisiert werden.");
    return;
  }

  Serial.printf("Sample MP3 playback begins...\n");

  sdFile = new AudioFileSourceSD("/heal.mp3"); // Öffnen der Audiodatei auf der SD
  out = new AudioOutputI2S();                  // Initialisierung des Audioausgangs
  mp3 = new AudioGeneratorMP3();
  mp3->begin(sdFile, out);

  mp3Loop();
}

void mp3Loop()
{
  while (mp3->isRunning())
  {
    if (!mp3->loop())
    {
      mp3->stop();   // Wenn die Wiedergabe abgeschlossen ist, stoppen Sie die Wiedergabe
      delete mp3;    // Freigabe des Speicherbereichs für mp3
      delete sdFile; // Freigabe des Speicherbereichs für sdFile
      delete out;    // Freigabe des Speicherbereichs für out
      Serial.println("mp3 Wiedergabe abgeschlossen");
    }
    else
    {
      Serial.println("Running");
    }
  }
  Serial.println("END");
}