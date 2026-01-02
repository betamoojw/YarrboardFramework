/*
  Yarrboard Framework Example

  This example code is in the Public Domain (or CC0 licensed, at your option.)

  Unless required by applicable law or agreed to in writing, this
  software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
  CONDITIONS OF ANY KIND, either express or implied.
*/

#include <Arduino.h>
#include <ArduinoJson.h>
#include <YarrboardFramework.h>

// generated at build by running "gulp" in the firmware directory.
#include "gulp/gulped.h"

YarrboardApp yba;

// setup for our buzzer / piezo (if present)
// is_active:  true = monotone, false = pwm tones
#include <controllers/BuzzerController.h>
#define YB_BUZZER_PIN       39
#define YB_BUZZER_IS_ACTIVE false
BuzzerController buzzer(yba);

// setup for our indicator LED (if present)
#include <controllers/RGBController.h>
#define YB_STATUS_RGB_PIN   38
#define YB_STATUS_RGB_ORDER GRB
#define YB_STATUS_RGB_COUNT 1
RGBController<WS2812B, YB_STATUS_RGB_PIN, YB_STATUS_RGB_ORDER> rgb(yba, YB_STATUS_RGB_COUNT);

void setup()
{
  yba.http.registerGulpedFiles(gulpedFiles, gulpedFilesCount);

  yba.board_name = "Framework Test";
  yba.default_hostname = "yarrboard";
  yba.firmware_version = "1.2.3";
  yba.hardware_version = "REV_A_B_C";
  yba.manufacturer = "Test Manufacturer";
  yba.hardware_url = "http://example.com/my-hardware-page";
  yba.project_name = "Yarrboard Framework";
  yba.project_url = "https://github.com/hoeken/YarrboardFramework";

  // OTA updates configuration.  Firmware can poll the url and download its own OTA updates.
  yba.ota.firmware_manifest_url = "https://raw.githubusercontent.com/hoeken/YarrboardFramework/main/releases/ota_manifest.json";

  // firmware signing is optional, but recommended
  // generate your public key like so:
  // openssl genrsa -out priv_key.pem 4096
  // openssl rsa -in priv_key.pem -pubout > rsa_key.pub
  // replace yba.ota.public_key with the contents of rsa_key.pub
  // keep priv_key.pem somewhere safe.
  // update releases/config.json to point to the private key for
  // firmware signing when you make a new release.
  yba.ota.public_key = R"PUBLIC_KEY(
-----BEGIN PUBLIC KEY-----
MIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAjsPaBVvAoSlNEdxLnKl5
71m+8nEbI6jTenIau884++X+tzjRM/4vctpkfM+b6yPEER6hLKLU5Sr/sVbNAu3s
Ih9UHsgbyzQ4r+NMzM8ohvPov1j5+NgzoIRPn9IQR40p/Mr3T31MXoeSh/WXw7yJ
BjVH2KhTD14e8Yc9CiEUvzYhFVjs8Doy1q2+jffiutcR8z+zGBSGHI3klTK8mNau
r9weglTUCObkUfbgrUWXOkDN50Q97OOv99+p8NPkcThZYbaqjbrOCO9vnMFB9Mxj
5yDruS9QF/qhJ5mC7AuHLhAGdkPu+3OXRDlIJN1j7y8SorvQj9F17B8wnhNBfDPN
QbJc4isLIIBGECfmamCONi5tt6fcZC/xZTxCiEURG+JVgUKjw+mIBrv+iVn9NKYK
UF8shPfl0CGKzOvsXBf91pqF5rHs6TpVw985u1VFbRrUL6nmsCELFxBz/+y83uhj
jsROITwP34vi7qMuHm8UzTnfxH0dSuI6PfWESIM8aq6bidBgUWlnoN/zQ/pwLVsz
0Gh5tAoFCyJ+FZiKS+2spkJ5mJBMY0Ti3dHinp6E2YNxY7IMV/4E9oK+MzvX1m5s
rgu4zp1Wfh2Q5QMX6bTrDCTn52KdyJ6z2WTnafaA08zeKOP+uVAPT0HLShF/ITEX
+Cd7GvvuZMs80QvqoXi+k8UCAwEAAQ==
-----END PUBLIC KEY-----
)PUBLIC_KEY";

  // register the "test" command that requires GUEST or higher permissions
  yba.protocol.registerCommand(GUEST, "test", [](JsonVariantConst input, JsonVariant output, ProtocolContext context) {
    // check our input.
    String foo = input["foo"] | "Unknown";

    // log to console / webconsole
    YBP.printf("Test Command: %s\n", foo);

    // generate our message back to the client
    output["msg"] = "test";
    output["bar"] = foo;
  });

  // add our rgb controller in.
  yba.registerController(rgb);

  // add our buzzer controller in.
  buzzer.buzzerPin = YB_BUZZER_PIN;
  buzzer.isActive = YB_BUZZER_IS_ACTIVE;
  yba.registerController(buzzer);

  // finally call the app setup to start the party.
  yba.setup();
}

// loop is very basic.
// each controller has its own loop function that gets called by the app
void loop()
{
  yba.loop();
}