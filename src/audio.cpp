/* audio.cpp*/

#include "audio.hpp"

// init global variables
AudioOutputI2S *i2s_audio = nullptr;
AudioGeneratorMP3 *mp3 = nullptr;
AudioFileSourceSPIFFS *flashSourceSelect = nullptr;
AudioFileSourceSPIFFS *flashSourceHeal = nullptr;
AudioFileSourceSPIFFS *flashSourceAttack = nullptr;
const char *filenameHeal = "/heal.mp3";
const char *filenameAttack = "/attack.mp3";
volatile bool audioHealing = false;
volatile bool audioAttack = false;

void setupflashSourceSelect()
{
    flashSourceHeal = new AudioFileSourceSPIFFS(filenameHeal);
    flashSourceAttack = new AudioFileSourceSPIFFS(filenameAttack);
}

void selectMusic()
{
    // test
    startMusic(flashSourceHeal, filenameHeal);
    delay(1000);
    startMusic(flashSourceAttack, filenameAttack);
    delay(1000);
}

void startMusic(AudioFileSourceSPIFFS *flashSourceSelect, const char *filename)
{
    flashSourceSelect->open(filename);

    if (!flashSourceSelect->isOpen())
    {
        Serial.println("Datei ist geschlossen.");
        change_state(ERROR);
        return;
    }

    // Initialisierung des Audioausgangs über I2S
    i2s_audio = new AudioOutputI2S(0, 1, 8, -1); // Initialisierung des Audioausgangs
    i2s_audio->SetOutputModeMono(true);
    i2s_audio->SetGain(0.4f);

    mp3 = new AudioGeneratorMP3();

    // Verwenden Sie die gewünschte Bit-Breite für das Audio (z. B. 16 Bit)
    if (!i2s_audio->begin())
    {
        Serial.println("Fehler beim Initialisieren des Audioausgangs über I2S");
        freeFlash();
        change_state(ERROR);
        return;
    }

    mp3->begin(flashSourceSelect, i2s_audio);
    mp3Decode();
    freeResources();
    flashFile.close();
    Serial.println("END");
}

void mp3Decode()
{
    const TickType_t startTick = xTaskGetTickCount();
    TickType_t lastHeartbeat = startTick;
    const TickType_t heartbeatInterval = pdMS_TO_TICKS(3000);
    const TickType_t timeout = pdMS_TO_TICKS(20000);

    while (mp3->isRunning())
    {
        if (!mp3->loop())
        {
            // dekodiere Dateien und schreibe sie ins i2s
            mp3->stop(); // Wenn die Wiedergabe abgeschlossen ist, stoppen Sie die Wiedergabe
            // Serial.println("mp3 Wiedergabe abgeschlossen");
            break;
        }

        const TickType_t now = xTaskGetTickCount();
        if ((now - lastHeartbeat) >= heartbeatInterval)
        {
            const unsigned int elapsedMs = static_cast<unsigned int>((now - startTick) * portTICK_PERIOD_MS);
            Serial.printf("heartbeat=%u ms\n", elapsedMs);
            lastHeartbeat = now;
        }

        if ((now - startTick) >= timeout)
        {
            Serial.println("Audio timeout");
            mp3->stop();
            break;
        }

        vTaskDelay(1);
    }
}

void freeResources()
{
    if (mp3 != nullptr)
    {
        delete mp3;
        mp3 = nullptr;
    }
    if (i2s_audio != nullptr)
    {
        delete i2s_audio;
        i2s_audio = nullptr;
    }
}

void freeFlash()
{
    delete mp3;
    delete i2s_audio;
    delete flashSourceSelect;
    delete flashSourceHeal;
    delete flashSourceAttack;

    // close() frees memory!
    flashFile.close();
    /*
        if ((SPIFFS.remove("/heal.mp3")) && (SPIFFS.remove("/attack.mp3")))
        {
            Serial.println("- files deleted");
        }
        else
        {
            Serial.println("- delete failed");
        }
    */
    SPIFFS.end(); // SPIFFS-Verbindung trennen
}