/* audio.cpp*/

#include "audio.hpp"

// init global variables
AudioOutputI2S *i2s_audio = nullptr;
AudioGeneratorMP3 *mp3 = nullptr;

void startMusic()
{
    flashSource = new AudioFileSourceSPIFFS("/heal.mp3"); // test

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
    i2s_audio = new AudioOutputI2S(0, 1, 8, -1); // Initialisierung des Audioausgangs
    i2s_audio->SetOutputModeMono(true);

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
    playMusic();

    freeFlash();

    Serial.println("END");
}

void mp3Decode()
{
    while (mp3->isRunning())
    {
        if (!mp3->loop())
        {
            // dekodiere Dateien und schreibe sie ins i2s
            mp3->stop(); // Wenn die Wiedergabe abgeschlossen ist, stoppen Sie die Wiedergabe
            Serial.println("mp3 Wiedergabe abgeschlossen");
        }
        else
        {
            Serial.print("Running");
        }
    }
}

void playMusic()
{
    Serial.println("playMusic");
    int16_t sample[2];

    while (mp3->isRunning())
    {
        if (!mp3->loop())
        {
            mp3->stop();
            Serial.println("mp3 Wiedergabe abgeschlossen");
            break;
        }

        // Lesen der Audiodaten vom I2S
        if (!i2s_audio->ConsumeSample(sample))
        {
            Serial.println("FEHLER beim Lesen von Samples vom MP3-Decodierer");
            continue;
        }

        // Konvertiere int16_t in uint8_t für den DAC
        uint8_t sample_byte = static_cast<uint8_t>((sample[0] >> 8) & 0xFF); // Linker Kanal

        // Schreiben der Audiodaten auf den DAC-Pin
        dacWrite(DACPin, sample_byte);
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