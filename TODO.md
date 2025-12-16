## v1.0.0 Release

* modify the gulp.js script to pull from the framework lib directory
* project specific gulp rules to pull in custom stuff logo, css, js, etc.
    * html/index.html -> overrides framework html
    * html/logo.png -> overrides framework.html
    * html/css/* -> gets added to the framework css includes
    * html/js/* -> gets added to the framework js includes

* protocol hooks
  * registerCommand(role, "command", callback);
  * onGenerateUpdate(callback) - generate update json
  * onGenerateFastUpdate(callback) - generate fast update json
  * onGenerateStats(callback) - generate stats json
  * onMessage() - gets called for every single message

* copy the ChannelRegistry style from JS and port to c++
  * might make more sense to implement it as ChannelController
  * move channel headers/classes to a channels/ folder
  * rename foo_channel.cpp to FooChannel.cpp to match class names
  * create callbacks:
      * onSetup() - main.cpp
      * onLoop() - main.cpp
      * onInit() - prefs.cpp
    * might be best at channel controller level?
      * onGenerateConfig() - prefs.cpp
      * onLoadConfig() - prefs.cpp
      * onMQTTUpdate() - mqtt.cpp
      * onHADiscovery() - mqtt.cpp
    * for looping only stuff it would be best to do something like this:
        * yba.registerChannels(channels);
        * yba.registerMQTTChannels(channels);
        * yba.registerHAChannels(channels);
* figure out how to manage BaseChannel mqtt calls -> really dont want to have to pass config + app details to them.
* figure out how to properly handle USB_CDC mode to avoid double prints.
* firmware_manifest_url needs to be configurable and passed to the UI as part of the config.