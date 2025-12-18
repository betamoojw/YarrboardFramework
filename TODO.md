## v1.0.0 Release

* test that dns and stuff works after improv

* fix our CI hookss
* copy the release.yml from psychic
* setup module on arduino
* setup module on platformio

## Long Term

* global brightness
  * rgb controller -> setMaxBrightness()
  * onBrightness -> max * brightness

* modify the gulp.js script to pull from the framework lib directory
  * it should also write the files to the framework lib directory for inclusion
  * project specific gulp rules to pull in custom stuff logo, css, js, etc.
      * html/index.html -> overrides framework html
      * html/logo.png -> overrides framework.html
      * html/css/* -> gets added to the framework css includes
      * html/js/* -> gets added to the framework js includes

* login, hello, logout are special commands.  can we modify this?
  * probably too much work for now.  implementing a queue similar to websockets would be the best way.
  * i guess there's a chance of collisions if there are http requests and websockets happening together.
  * command entry flow:
    * SERIAL: ProtocolController::loop -> serial -> handleReceivedJSON
    * WEBSOCKET: HTTPController::loop -> handleWebsocketMessageLoop -> handleReceivedJSON
    * HTTP API: esp-idf HTTP thread -> handleWebServerRequest -> handleReceivedJSON
    * MQTT: not implemented
