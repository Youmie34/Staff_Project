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

    flashSource = new AudioFileSourceSPIFFS("/heal.mp3");

    // Öffnen der MP3-Datei im Flash-Speicher
    if (!flashSource->isOpen())
    {
        Serial.println("Fehler beim Öffnen der Datei im SPIFFS");

        delete flashSource;
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
    mp3Decode();

    freeFlash();

    Serial.println("END");
}

void mp3Decode()
{
    while (mp3->isRunning())
    {
        if (!mp3->loop())
        {
            mp3->stop(); // Wenn die Wiedergabe abgeschlossen ist, stoppen Sie die Wiedergabe
            Serial.println("mp3 Wiedergabe abgeschlossen");
            freeFlash();
            break;
        }
        else
        {
            // Lesen Sie die Audiodaten vom I2S und schreiben Sie sie auf den DAC-Pin
            int16_t sample[2];
            if (!i2s_audio->ConsumeSample(sample))
            {
                // Fehler beim Lesen der Samples
                Serial.println("FEHLER beim Lesen von Samples vom MP3-Decodierer");
                freeFlash();
                break;
            }

            // Konvertiere int16_t in uint8_t
            uint8_t sample_byte = static_cast<uint8_t>((sample[0] >> 8) & 0xFF); // Beispiel für einen 8-Bit-Sample aus dem linken Kanal

            // Schreiben Sie die Audiodaten auf den DAC-Pin
            dacWrite(DACPin, sample_byte);
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