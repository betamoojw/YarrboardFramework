## v2.0

  * convert other pages to onPageOpen()
    * control
    * stats
    * config
    * settings
    * system
    * login
    * logout
* onPageOpen()
  * pass in our page object
  * overwrites previous page with that name.
* add onStart(callback) to YB.App, better hook than dom onready.

## Long Term

* other app.* callbacks to register various things?
  * addMessageHandler -> onMessage (homogenize)
  * onMessage -> messageHandler (homogenize)

* bug with reconnecting (eg ESP.restart not going down the hello path)

* currently we have a chance of collisions if http api + websockets requests happen simulataneously.
  * best to solve this as a mutex (but is this really needed?)

* allow turning off http server (mqtt / serial only)
* allow turning off wifi (serial only)

* add support for revived ESPAsyncWebServer:
  * https://github.com/ESP32Async/ESPAsyncWebServer