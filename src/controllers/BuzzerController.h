/*
  Yarrboard

  Author: Zach Hoeken <hoeken@gmail.com>
  Website: https://github.com/hoeken/yarrboard
  License: GPLv3
*/

#ifndef YARR_BUZZER_H
#define YARR_BUZZER_H

#include "YarrboardConfig.h"
#include "controllers/BaseController.h"
#include "driver/ledc.h"
#include <ArduinoJson.h>

struct Note {
    uint16_t freqHz;
    uint16_t ms;
};

struct Melody {
    const char* name;
    const Note* seq;
    size_t len;
};

#define YB_MAX_MELODY_LENGTH 100
#define LEDC_RES_BITS        10
#define BUZZER_DUTY          512
#define MELODY_ENTRY(x)      {#x, x, sizeof(x) / sizeof(Note)}

class YarrboardApp;
class ConfigManager;

// Forward declaration
void BuzzerTask(void* pv);

class BuzzerController : public BaseController
{
  public:
    BuzzerController(YarrboardApp& app);

    bool setup() override;
    void generateConfigHook(JsonVariant output) override;

    bool playMelodyByName(const char* melody);
    void generateMelodyJSON(JsonVariant output);

    void handlePlaySound(JsonVariantConst input, JsonVariant output);

    // Make the task a friend so it can access private static members
    friend void BuzzerTask(void* pv);

    byte buzzerPin = 0;
    bool isActive = false;

  private:
    void playMelody(const Note* seq, size_t len);
    void buzzerMute();
    void buzzerTone(uint16_t freqHz);
};

#endif /* !YARR_BUZZER_H */