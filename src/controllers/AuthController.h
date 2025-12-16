/*
  Yarrboard

  Author: Zach Hoeken <hoeken@gmail.com>
  Website: https://github.com/hoeken/yarrboard
  License: GPLv3
*/

#ifndef YARR_AUTH_H
#define YARR_AUTH_H

#include "YarrboardConfig.h"
#include "controllers/BaseController.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <etl/vector.h>

class YarrboardApp;
class ConfigManager;

typedef enum {
  NOBODY,
  GUEST,
  ADMIN
} UserRole;

typedef struct {
    int socket;
    UserRole role;
} AuthenticatedClient;

class AuthController : public BaseController
{
  public:
    AuthController(YarrboardApp& app);

    etl::vector<AuthenticatedClient, YB_CLIENT_LIMIT> authenticatedClients;

    bool setup() override;

    UserRole getUserRole(JsonVariantConst input, byte mode, int socket);
    bool logClientIn(int socket, UserRole role);
    bool isLoggedIn(JsonVariantConst input, byte mode, int socket);
    void removeClientFromAuthList(int socket);
    bool isApiClientLoggedIn(JsonVariantConst doc);

  private:
    bool addClientToAuthList(int socket, UserRole role);
    bool isWebsocketClientLoggedIn(JsonVariantConst input, int socket);
    bool isSerialClientLoggedIn(JsonVariantConst input);
    bool checkLoginCredentials(JsonVariantConst doc, UserRole& role);
    UserRole getWebsocketRole(JsonVariantConst doc, int socket);
};

#endif /* !YARR_AUTH_H */