/* audio.cpp*/

#include "audio.hpp"

// init global variables
int DACPin = 26;
AudioOutputI2S *i2s_audio = nullptr;
AudioGeneratorMP3 *mp3 = nullptr;

void startMusic()
{
    // Initialisierung des DAC-Pins
    dacWrite(DACPin, 0); // Setzen Sie den DAC-Pin auf einen Startwert

    // Öffnen der MP3-Datei im Flash-Speicher
    if (!flashSource->isOpen())
    {
        Serial.println("Fehler beim Öffnen der Datei im SPIFFS");
        delete flashSource;

        // close() frees memory!
        flashFileHeal.close();
        if (SPIFFS.remove("/heal.mp3"))
        {
            Serial.println("- file deleted");
        }
        else
        {
            Serial.println("- delete failed");
        }
        SPIFFS.end(); // SPIFFS-Verbindung trennen
        return;
    }

    // Initialisierung des Audioausgangs über I2S
    i2s_audio = new AudioOutputI2S(); // Initialisierung des Audioausgangs
    mp3 = new AudioGeneratorMP3();

    // Verwenden Sie die gewünschte Bit-Breite für das Audio (z. B. 16 Bit)
    if (!i2s_audio->begin())
    {
        Serial.println("Fehler beim Initialisieren des Audioausgangs über I2S");
        freeFlash();
        return;
    }

    mp3->begin(flashSource, i2s_audio);
    // mp3Loop();

    freeFlash();

    Serial.println("END");
}

void startPlayback()
{
    // Wiedergabe der Audiodaten
    while (true)
    {
        int16_t sample[2];
        if (i2s_audio->ConsumeSample(sample))
        {
            // Schreiben Sie die Audiodaten auf den I2S-Ausgang
            i2s_audio->write(sample);
        }
        else
        {
            // Wenn keine Audiodaten mehr verfügbar sind, beenden Sie die Wiedergabe
            Serial.println("Wiedergabe abgeschlossen");
            break;
        }
    }
}

void mp3Loop()
{
    while (mp3->isRunning())
    {

        if (!mp3->loop())
        {
            mp3->stop(); // Wenn die Wiedergabe abgeschlossen ist, stoppen Sie die Wiedergabe
            Serial.println("mp3 Wiedergabe abgeschlossen");
            break;
        }
        else
        {
            // Lesen Sie die Audiodaten vom I2S und schreiben Sie sie auf den DAC-Pin
            // size_t *bytes_read;
            const size_t bufferSize = 1024; // Zum Beispiel 1024 Bytes
            int sample = i2s_audio->read(NULL, bufferSize);
            if (sample == 0)
            {
                Serial.println("FEHLER beim Lesen von Audiodaten vom I2S");
                freeFlash(); // Fehlerbehandlung und Aufräumen
                break;       // Beenden Sie die Schleife bei einem Fehler
            }

            // Schreiben Sie die Audiodaten auf den DAC-Pin
            dacWrite(DACPin, sample);
        }
    }
}

void freeFlash()
{
    delete mp3;
    delete i2s_audio;
    delete flashSource;

    // close() frees memory!
    flashFileHeal.close();
    if (SPIFFS.remove("/heal.mp3"))
    {
        Serial.println("- file deleted");
    }
    else
    {
        Serial.println("- delete failed");
    }
    SPIFFS.end(); // SPIFFS-Verbindung trennen
}