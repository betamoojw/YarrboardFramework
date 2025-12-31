## v2.0

* guest/admin login doesnt work when on the #logout page -> wont redirect
* move stuff from YB.start to onStart callbacks where it makes sense.

* addMessageHandler -> onMessage (homogenize)
* onMessage -> messageHandler (homogenize)
* rename control to home

## Long Term

* other app.* callbacks to register various things?

* bug with reconnecting (eg ESP.restart not going down the hello path)

* currently we have a chance of collisions if http api + websockets requests happen simulataneously.
  * best to solve this as a mutex (but is this really needed?)

* allow turning off http server (mqtt / serial only)
* allow turning off wifi (serial only)

* add support for revived ESPAsyncWebServer:
  * https://github.com/ESP32Async/ESPAsyncWebServer