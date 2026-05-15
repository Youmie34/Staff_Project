/*tasks.cpp*/

#include "tasks.hpp"

// init tasks
tasks_t sensorsInit =
    {
        "SensorsInit",
        sens_init,
        NOT_STARTED,
        NULL,
};

tasks_t sdInit =
    {
        "SDInit",
        sd_init,
        NOT_STARTED,
        NULL};

tasks_t spiffsInit =
    {
        "SPIFFSInit",
        spiffs_init,
        NOT_STARTED,
        NULL};

// idle tasks
tasks_t distMeasure =
    {
        "DistMeasure",
        dist_measure,
        NOT_STARTED,
        NULL};

tasks_t accMeasure =
    {
        "AccMeasure",
        acc_measure,
        NOT_STARTED,
        NULL};

// active tasks
tasks_t audioPlayHealing =
    {
        "AudioPlayHealing",
        audio_play_healing,
        NOT_STARTED,
        NULL};

tasks_t audioPlayAttack =
    {
        "AudioPlayAttack",
        audio_play_attack,
        NOT_STARTED,
        NULL};

tasks_t neopixelPlayHealing =
    {
        "NeopixelPlay",
        neopixel_play_healing,
        NOT_STARTED,
        NULL};

tasks_t neopixelPlayAttack =
    {
        "NeopixelPlay",
        neopixel_play_attack,
        NOT_STARTED,
        NULL};

// error tasks
tasks_t errorHandler =
    {
        "ErrorHandler",
        error_handler,
        NOT_STARTED,
        NULL};

void sens_init(void *parameter)
{
    sensorsInit.state = RUNNING;

    ultrasonicSetup();
    neoSetup();

    // init lis3dh
    pinMode(ENFeatherPin, OUTPUT);
    digitalWrite(ENFeatherPin, HIGH);

    setupAcc();

    sensorsInit.state = COMPLETED;
    systemFlags.sensorsInitialized = true;
    sensorsInit.pxCreatedTask = NULL;
    vTaskDelete(NULL);
}

void sd_init(void *parameter)
{
    sdInit.state = RUNNING;
    setupMemory();
    sdInit.state = COMPLETED;
    sdInit.pxCreatedTask = NULL;
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

    systemFlags.audioInitialized = true;
    spiffsInit.pxCreatedTask = NULL;
    vTaskDelete(NULL);
}

void dist_measure(void *parameter)
{
    // Serial.println("Distance task started");
    distMeasure.state = RUNNING;
    ultrasonicMeasure();
    distMeasure.state = COMPLETED;
    distMeasure.pxCreatedTask = NULL;
    vTaskDelete(NULL);
}

void acc_measure(void *parameter)
{
    // Serial.println("Acceleration task started");
    accMeasure.state = RUNNING;
    // Runs in interrupt, so no implementation here
    accMeasure.state = COMPLETED;
    accMeasure.pxCreatedTask = NULL;
    vTaskDelete(NULL);
}

void audio_play_healing(void *parameter)
{
    audioPlayHealing.state = RUNNING;
    systemFlags.audioHealing = true;
    Serial.println("Starting healing music");
    startMusic(flashSourceHeal, filenameHeal);
    systemFlags.audioHealing = false;
    audioPlayHealing.state = COMPLETED;
    audioPlayHealing.pxCreatedTask = NULL;
    vTaskDelete(NULL);
}

void audio_play_attack(void *parameter)
{
    audioPlayAttack.state = RUNNING;
    systemFlags.audioAttack = true;
    Serial.println("Starting attack music");
    startMusic(flashSourceAttack, filenameAttack);
    systemFlags.audioAttack = false;
    audioPlayAttack.state = COMPLETED;
    audioPlayAttack.pxCreatedTask = NULL;
    vTaskDelete(NULL);
}

void neopixel_play_healing(void *parameter)
{
    neopixelPlayHealing.state = RUNNING;
    Serial.println("Starting healing animation");
    neoSetBrightnessForPower(systemFlags.audioHealing || systemFlags.audioAttack);
    healing();
    neopixelPlayHealing.state = COMPLETED;
    neopixelPlayHealing.pxCreatedTask = NULL;
    vTaskDelete(NULL);
}

void neopixel_play_attack(void *parameter)
{
    neopixelPlayAttack.state = RUNNING;
    Serial.println("Starting attack animation");
    neoSetBrightnessForPower(systemFlags.audioHealing || systemFlags.audioAttack);
    attack();
    neopixelPlayAttack.state = COMPLETED;
    neopixelPlayAttack.pxCreatedTask = NULL;
    vTaskDelete(NULL);
}

void error_handler(void *parameter)
{
    errorHandler.state = RUNNING;
    // Restart system
    // esp_restart(); // Perform system restart
    errorHandler.pxCreatedTask = NULL;
    vTaskDelete(NULL);
}

void clear_attack()
{
    audioPlayAttack.state = NOT_STARTED;
    neopixelPlayAttack.state = NOT_STARTED;
    systemFlags.audioAttack = false;
    neoForceOff();
}

void clear_healing()
{
    audioPlayHealing.state = NOT_STARTED;
    neopixelPlayHealing.state = NOT_STARTED;
    systemFlags.audioHealing = false;
    neoForceOff();
}