## Long Term

* find a way to provide html/css/js/etc files as part of library framework included.
  * modify the gulp.js script to pull from the framework lib directory?
  * project specific gulp rules to pull in custom stuff logo, css, js, etc.
      * html/index.html -> overrides framework html
      * html/logo.png -> overrides framework.html
      * html/css/* -> gets added to the framework css includes
      * html/js/* -> gets added to the framework js includes
  * create a better gulped file format that includes data, hash, and length in one struct

* we need to add an order field to controllers that determines how they loop.
  * sort on add.
  * mqtt needs to be last

* global brightness
  * rgb controller -> setMaxBrightness()
  * onBrightness -> max * brightness

* login, hello, logout are special commands.  would be nice to have them use the same command registry
  * problem is we need certain context specific things (mode, connection id, and role)
  * currently we have a chance of collisions if http api + websockets requests happen simulataneously.
  * implementing a queue similar to websockets for all other commands would be best way.
    * then protocol controller handles all the requests in its own loop, single entry point.
  * we will need this to implement protocol over mqtt
  * current command entry flow:
    * SERIAL: ProtocolController::loop -> serial -> handleReceivedJSON
    * WEBSOCKET: HTTPController::loop -> handleWebsocketMessageLoop -> handleReceivedJSON
    * HTTP API: esp-idf HTTP thread -> handleWebServerRequest -> handleReceivedJSON
    * MQTT: not implemented

* add support for revived ESPAsyncWebServer:
  * https://github.com/ESP32Async/ESPAsyncWebServer