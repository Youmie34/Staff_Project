/*tasks.cpp*/

#include "tasks.hpp"

flags_t systemFlags;

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
    Serial.println("sens_init: Starting initialization");
    Serial.print("sens_init: Current state before assignment: ");
    Serial.println(sensorsInit.state);

    sensorsInit.state = RUNNING;

    Serial.println("sens_init: Setting pin mode");
    pinMode(ENFeatherPin, OUTPUT);
    // digitalWrite(ENFeatherPin, LOW);
    digitalWrite(ENFeatherPin, HIGH);

    // Uncomment these lines if needed
    Serial.println("sens_init: Setting up ultrasonic sensor");
    ultrasonicSetup();
    //  neoSetup();
    //   setupAcc();

    Serial.println("sens_init: Initialization complete");
    Serial.print("sens_init: Current state after assignment: ");
    Serial.println(sensorsInit.state);

    Serial.print("sens_init: Task function pointer: ");
    Serial.println((unsigned long)sensorsInit.taskFunction, HEX);

    sensorsInit.state = COMPLETED;
    Serial.println("sens_init: Deleting task");
    vTaskDelete(NULL);
}

void sd_init(void *parameter)
{
    sdInit.state = RUNNING;
    setupMemory();
    sdInit.state = COMPLETED;
}

void spiffs_init(void *parameter)
{
    spiffsInit.state = RUNNING;
    saveInSPIFFS("/heal.mp3");
    saveInSPIFFS("/attack.mp3");
    setupflashSourceSelect();
    spiffsInit.state = COMPLETED;
}

void dist_measure(void *parameter)
{
    distMeasure.state = RUNNING;
    // Implementation for distance measurement
    ultrasonicMeasure();
    distMeasure.state = COMPLETED;
}

void acc_measure(void *parameter)
{
    accMeasure.state = RUNNING;
    // Runs in interrupt, so no implementation here
    accMeasure.state = COMPLETED;
}

void audio_play_healing(void *parameter)
{
    audioPlayHealing.state = RUNNING;
    startMusic(flashSourceHeal, filenameHeal);
    audioPlayHealing.state = COMPLETED;
}

void audio_play_attack(void *parameter)
{
    audioPlayAttack.state = RUNNING;
    startMusic(flashSourceAttack, filenameAttack);
    audioPlayAttack.state = COMPLETED;
}

void neopixel_play_healing(void *parameter)
{
    neopixelPlayHealing.state = RUNNING;
    healing();
    neopixelPlayHealing.state = COMPLETED;
}

void neopixel_play_attack(void *parameter)
{
    neopixelPlayAttack.state = RUNNING;
    attack();
    neopixelPlayAttack.state = COMPLETED;
}

void error_handler(void *parameter)
{
    errorHandler.state = RUNNING;
    // Restart system
    // esp_restart(); // Perform system restart
}