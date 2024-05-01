
/*
Software from https://github.com/rin67630/Victron_VE_on_Steroids

Target Hardware modules: 
- Witty ESP8266 or WEMOS D1,  Board Setting: WEMOS D1 Mini (Clone), or ESP8266 Bare
- ESP32 TTGO (with Color Display), Board Setting: 
- ESP32 HELTEC LoRa V1 Board setting, Board Setting: Heltec WiFi LoRa 32 (not V2) 
- ESP32 with or without I2C OLED display. Board Setting: LoLin Wemos32 

Arduino IDE Preferences for above type of boards settings: http://arduino.esp8266.com/stable/package_esp8266com_index.json
https://github.com/HELTEC-Aaron-Lee/WiFi_Kit_series/releases/download/1.0.0/package_HELTEC_esp32_index.json
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json


Libraries:
Thanks to the respective owners of all libraries used:
-ESP8266 and ESP32 OLED driver for SSD1306 displays by ThingPulse, Fabrice Weinberg
-MobaTools by MicroBahner from which I took the Motobuttons.h lib
-Arduinojson by Benoit Blanchon <blog.benoitblanchon.fr>
-ThingerCore32 and Thinger.io by Alvaro Luis Bustamante
-TelnetStream by Juraj Andrassy
-INA226 by Rob Tillaart
-InterpolationLib by Luis Llamas


The other libraries are the standard libs from Arduino, Espressif, Adafruit...

Software provide free under Creative Commons CC BY 3.0 license
https://creativecommons.org/licenses/by/3.0/
*/
