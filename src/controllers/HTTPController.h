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

#ifndef YARR_SERVER_H
#define YARR_SERVER_H

#include "YarrboardConfig.h"

#include "controllers/AuthController.h"
#include "controllers/BaseController.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <PsychicHttp.h>
#include <PsychicHttpsServer.h>
#include <freertos/queue.h>

typedef struct {
    int socket;
    char* buffer;
    size_t len;
} WebsocketRequest;

class YarrboardApp;
class ConfigManager;

class HTTPController : public BaseController
{
  public:
    HTTPController(YarrboardApp& app);

    bool setup() override;
    void loop() override;

    void sendToAllWebsockets(const char* jsonString, UserRole auth_level);

    uint32_t index_length = 0;
    const char* index_sha;
    const uint8_t* index_data;

    uint32_t logo_length = 0;
    const char* logo_sha;
    const uint8_t* logo_data;

    unsigned int websocketClientCount = 0;
    unsigned int httpClientCount = 0;

  private:
    PsychicHttpServer* server;
    PsychicWebSocketHandler websocketHandler;
    char last_modified[50];
    QueueHandle_t wsRequests;
    SemaphoreHandle_t sendMutex;

    void handleWebsocketMessageLoop(WebsocketRequest* request);
    esp_err_t handleWebServerRequest(JsonVariant input, PsychicRequest* request, PsychicResponse* response);
    void handleWebSocketMessage(PsychicWebSocketRequest* request, uint8_t* data, size_t len);
};

#endif /* !YARR_SERVER_H */