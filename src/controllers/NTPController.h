/*
 * Yarrboard Framework
 *
 * Copyright (c) 2025 Zach Hoeken <hoeken@gmail.com>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef YARR_NTP_H
#define YARR_NTP_H

#include "controllers/BaseController.h"
#include "esp_sntp.h"
#include "time.h"
#include <Arduino.h>

class YarrboardApp;
class ConfigManager;

class NTPController : public BaseController
{
  public:
    NTPController(YarrboardApp& app);

    bool setup() override;
    bool isReady() { return ntp_is_ready; }
    int64_t getTime();
    void printLocalTime();

  private:
    const char* ntpServer1 = "pool.ntp.org";
    const char* ntpServer2 = "time.nist.gov";
    const long gmtOffset_sec = 0;
    const int daylightOffset_sec = 0;
    bool ntp_is_ready = false;

    // --- THE CALLBACK TRAP ---
    // Libraries expecting C-style function pointers cannot take normal member functions.
    // We use a static instance pointer and static methods to bridge the gap.
    static NTPController* _instance;
    static void _timeAvailableCallbackStatic(struct timeval* t);
    void timeAvailableCallback(struct timeval* t);
};

#endif /* !YARR_NTP_H */