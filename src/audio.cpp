/* audio.cpp*/

#include "audio.hpp"

void startMusic()
{
    i2s = new AudioOutputI2S();                           // Initialisierung des Audioausgangs
    mp3 = new AudioGeneratorMP3();

    mp3->begin(flashSource, i2s);
    mp3Loop();

    freeFlash();

    Serial.println("END");
}

void mp3Loop()
{
    while (mp3->isRunning())
    {

        if (!mp3->loop())
        {
            mp3->stop(); // Wenn die Wiedergabe abgeschlossen ist, stoppen Sie die Wiedergabe
            Serial.println("mp3 Wiedergabe abgeschlossen");
        }
        else
        {
            Serial.println("Running");
        }
    }
}

void freeFlash()
{
    delete mp3;
    delete i2s;
    delete flashSource;

    // close() frees memory!
    flashFileHeal.close();
    SPIFFS.end(); // SPIFFS-Verbindung trennen
}