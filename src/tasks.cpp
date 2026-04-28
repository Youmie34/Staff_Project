/*tasks.cpp*/

#include "tasks.hpp"

// init tasks
tasks_t sensorsInit =
    {
        "SensorsInit",
        sens_init,
        NOT_STARTED,
};

tasks_t sdInit =
    {
        "SDInit",
        sd_init,
        NOT_STARTED};

tasks_t spiffsInit =
    {
        "SPIFFSInit",
        spiffs_init,
        NOT_STARTED};

// idle tasks
tasks_t distMeasure =
    {
        "DistMeasure",
        dist_measure,
        NOT_STARTED};

tasks_t accMeasure =
    {
        "AccMeasure",
        acc_measure,
        NOT_STARTED};

// active tasks
tasks_t audioPlayHealing =
    {
        "AudioPlayHealing",
        audio_play_healing,
        NOT_STARTED};

tasks_t audioPlayAttack =
    {
        "AudioPlayAttack",
        audio_play_attack,
        NOT_STARTED};

tasks_t neopixelPlayHealing =
    {
        "NeopixelPlay",
        neopixel_play_healing,
        NOT_STARTED};

tasks_t neopixelPlayAttack =
    {
        "NeopixelPlay",
        neopixel_play_attack,
        NOT_STARTED};

// error tasks
tasks_t errorHandler =
    {
        "ErrorHandler",
        error_handler,
        NOT_STARTED};

void sens_init(void *parameter)
{
    sensorsInit.state = RUNNING;

    ultrasonicSetup();
    neoSetup();

    sensorsInit.state = COMPLETED;
    systemFlags.sensorsInitialized = true;

    vTaskDelete(NULL);
}

void sd_init(void *parameter)
{
    sdInit.state = RUNNING;
    setupMemory();
    sdInit.state = COMPLETED;
    vTaskDelete(NULL);
}

void spiffs_init(void *parameter)
{
    spiffsInit.state = RUNNING;
    setupMemory();
    // saveInSPIFFS("/heal.mp3");
    // saveInSPIFFS("/attack.mp3");
    // listSPIFFSFiles();
    setupflashSourceSelect();
    Serial.println("File saving complete");
    spiffsInit.state = COMPLETED;

    // init lis3dh
    pinMode(ENFeatherPin, OUTPUT);
    digitalWrite(ENFeatherPin, HIGH);

    setupAcc();

    systemFlags.audioInitialized = true;
    vTaskDelete(NULL);
}

void dist_measure(void *parameter)
{
    // Serial.println("Distance task started");
    distMeasure.state = RUNNING;
    ultrasonicMeasure();
    distMeasure.state = COMPLETED;
    vTaskDelete(distMeasure.pxCreatedTask);
}

void acc_measure(void *parameter)
{
    // Serial.println("Acceleration task started");
    accMeasure.state = RUNNING;
    // Runs in interrupt, so no implementation here
    accMeasure.state = COMPLETED;
    vTaskDelete(accMeasure.pxCreatedTask);
}

void audio_play_healing(void *parameter)
{
    audioPlayHealing.state = RUNNING;
    Serial.println("Starting healing music");
    startMusic(flashSourceHeal, filenameHeal);
    audioPlayHealing.state = COMPLETED;
    vTaskDelete(audioPlayHealing.pxCreatedTask);
}

void audio_play_attack(void *parameter)
{
    audioPlayAttack.state = RUNNING;
    Serial.println("Starting attack music");
    startMusic(flashSourceAttack, filenameAttack);
    audioPlayAttack.state = COMPLETED;
    vTaskDelete(audioPlayAttack.pxCreatedTask);
}

void neopixel_play_healing(void *parameter)
{
    neopixelPlayHealing.state = RUNNING;
    healing();
    neopixelPlayHealing.state = COMPLETED;
    vTaskDelete(neopixelPlayHealing.pxCreatedTask);
}

void neopixel_play_attack(void *parameter)
{
    neopixelPlayAttack.state = RUNNING;
    attack();
    neopixelPlayAttack.state = COMPLETED;
    vTaskDelete(neopixelPlayAttack.pxCreatedTask);
}

void error_handler(void *parameter)
{
    errorHandler.state = RUNNING;
    // Restart system
    // esp_restart(); // Perform system restart
    vTaskDelete(errorHandler.pxCreatedTask);
}

void clear_attack()
{
    audioPlayAttack.state = NOT_STARTED;
    neopixelPlayAttack.state = NOT_STARTED;
}

void clear_healing()
{
    audioPlayHealing.state = NOT_STARTED;
    neopixelPlayHealing.state = NOT_STARTED;
}