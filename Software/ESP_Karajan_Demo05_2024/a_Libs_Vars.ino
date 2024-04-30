//*** Include Own Configuration files ***
#include "Credentials.h"
#include "Config.h"

// *** libraries***  (including with <> takes by priority global files, including with "" takes local files).
#include <Wire.h>
#include <ArduinoOTA.h>
#include "time.h"  // built-in
//#include <FS.h>
#include <EEPROM.h>
#include "InterpolationLib.h"

#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>
#endif
#if defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#ifndef LED_BUILTIN
#define LED_BUILTIN 5       //no built-in LED on an ESP32, using GPIO5 (Wemos ESP32).
#endif
//#include <WebServer.h>
#include <HTTPClient.h>
//using SDClass = fs::SDFS;
#endif

//#include <AutoConnectCredential.h>
#ifdef SCREEN_IS_64x48
#include <SSD1306.h>                              // from https://github.com/ThingPulse/esp8266-oled-ssd1306/
SSD1306 display(0x3c, SDA, SCL, GEOMETRY_64_48);  // WEMOS OLED 64*48 shield
#endif

#ifdef SCREEN_IS_128x64
#include <SSD1306.h>                               // from https://github.com/ThingPulse/esp8266-oled-ssd1306/
SSD1306 display(0x3c, SDA, SCL, GEOMETRY_128_64);  //OLED 128*64 soldered
#endif

#ifdef SCREEN_IS_HW364A                           // This module has SCL on D5 (GPIO12) and SDA on D6 (GPIO14) !
#define SDA 14
#define SCL 12
#define RST 16
#include <SSD1306.h>
SSD1306 display(0x3c, 14, 12); //, GEOMETRY_128_64, 16);
#endif

#ifdef SCREEN_IS_WEMOS32
#define SDA 5
#define SCL 4
#define RST 16
#include <SSD1306.h>
SSD1306 display(0x3c);
#endif

#ifdef SCREEN_IS_HELTEC
#define SDA 4
#define SCL 15
#define RST 16
#include <SSD1306.h>
SSD1306 display(0x3c);  //cut: , SDA, SCL, GEOMETRY_128_64, RST)
#endif

#ifdef SCREEN_IS_TTGO
#include <TFT_eSPI.h>
#include <SPI.h>
#include <MoToButtons.h>    // from Library (MoBaTools).
TFT_eSPI tft = TFT_eSPI();  // Invoke custom library
#define TOUCH_CS            21
#define SCL                 22  // GPIO5 for I2C (Wire) System Clock
#define SDA                 21  // GPIO4 for I2C (Wire) System Data
#define RST                 16  //    GPIO0
#define TFT_BL               4        // Display backlight control pin
#define A0                  36
#define BUTTON_UP           35
#define BUTTON_DOWN          0
#define ROTARY_ENCODER_A_PIN 25       // Rotary Encoder A
#define ROTARY_ENCODER_B_PIN 26       // Rotary Encoder B
#define ROTARY_ENCODER_BUTTON_PIN 33  // Rotary Encoder Switch
#define ROTARY_ENCODER_STEPS 4        // Rotary Encoder Delta (Steps) not an input!
#define TFT_GREY        0x5AEB               // better Grey
#define TFT_VERMILON    0xFA60           // better Orange
#endif


//*** Buffers ***
static char charbuff[120];  //Char buffer for many functions

#ifdef WEATHER_SOURCE_IS_OWM
#include <ArduinoJson.h>  // Libs for Webscraping
#define OPEN_WEATHER_MAP_URL "http://api.openweathermap.org/data/2.5/weather?id=" OPEN_WEATHER_MAP_LOCATION_ID "&appid=" OPEN_WEATHER_MAP_API_KEY "&units=" OPEN_WEATHER_MAP_UNITS "&lang=" OPEN_WEATHER_MAP_LANGUAGE
WiFiClient WifiClient;
#endif

#ifdef WEATHER_SOURCE_IS_BME680  // Local Temperature / Pressure / Humidity sensor
#include "Adafruit_Sensor.h"
#include "Adafruit_BME680.h"
Adafruit_BME680 bme;  ///< Create an instance of the BME280 class
#endif

#if defined(DASHBRD_IS_THINGER)
#if defined(ARDUINO_ARCH_ESP8266)
#include "ThingerESP8266.h"
ThingerESP8266 thing(THINGER_USERNAME, DEVICE_NAME, DEVICE_CREDENTIALS);
#else
#include "ThingerESP32.h"
ThingerESP32 thing(THINGER_USERNAME,  DEVICE_NAME, DEVICE_CREDENTIALS);
#endif
#endif

#if defined(DASHBRD_IS_INFLUX)   //not yet fully implemented
#include <InfluxDBClient.h>
#include <InfluxDbCloud.h>
#endif

#if defined(TERM_IS_SOFTSER)
#include <SoftwareSerial.h>
#define Console1 SoftwareSerial
#endif

#if defined(TERM_IS_SERIAL)
#define Console1 Serial
#endif

#if defined(TERM_IS_TELNET)
#include <TelnetStream.h>
#define Console1 TelnetStream
#endif

// Parameters for MoToButtons
#ifdef SCREEN_IS_TTGO
#define MAX8BUTTONS  // This saves ressources if you don't need more than 8 buttons
const byte buttonPins[] = { BUTTON_UP, BUTTON_DOWN, ROTARY_ENCODER_BUTTON_PIN };
enum : byte { UP,
              DOWN,
              ROT
            };
const byte buttonCount = sizeof(buttonPins);
MoToButtons Buttons(buttonPins, buttonCount, 130, 5000);  //  130ms debounce. 5 s to distinguish short/long
#endif

//***Variables for Time***
tm* timeinfo;  //localtime returns a pointer to a tm struct static int by Second;
tm* offsettedTimeinfo;
time_t now;
time_t offsettedNow;
time_t Epoch;
byte Second;
long SecondOfDay;
long MillisMem;
long MillisMem2;
byte Minute;
byte Hour;
byte Day;
byte Month;
unsigned int Year;
byte Weekday;
// Optional if you want to use names 
//char DayName[16];
//char MonthName[16];
//char Time[16];
//char Date[16];
static IPAddress ip;

//*** Variables for the scheduler ***
byte slice;
boolean NewMinute;
boolean MinuteExpiring;
boolean NewHour;
boolean HourExpiring;
boolean NewDay;
boolean DayExpiring;
boolean TrigEvent;
unsigned int RunMillis[28];  // keep trace of consumed time

byte serialReceived;

//*** Variables for User Commands ***
byte  serialPage;
byte  displayPage;
byte  displaySubPage;
byte  wirelessPage;
//bool  resetCoulomb;
//bool  restart;
//bool  freezePsonUpdate;

// ***Weather***
float temperature;
float humidity;
float pressure;
float wind_speed;
int   wind_direction;
int   cloudiness;
String weather_summary;

// ***Data structures that can be transmitted between ESP devices***
struct payload {
  //***Operating Values from Victron/SmartShunt***
  float BatV;   // V   Battery voltage, V
  float BatI;   // I   Battery current, A
  float BatW;   // W BatV*BatI

  float PanV;  // VPV Panel voltage,   V
  float PanI;  // PanW/PanV
  float PanW;  // PPV Panel power,     W

  float LodI;  // IL  Load Current     A
  float LodW;  //  BatI*BatV
  float IOhm;  //  dV / dI

  int ChSt;       // CS  Charge state (not POC), 0 to 9
  int Err;        // ERR Error code, 0 to 119
  boolean LodOn;  // LOAD ON Load output state, ON/OFF
} payload;

struct setpoints {
  //***Operating Values from Victron/SmartShunt***
  float BatV;   // V   Battery voltage, V
  float BatI;   // I   Battery current, A
  float PanV;  // VPV Panel voltage,   V
} setpoints;

struct targets {
  //***Operating Values from Victron/SmartShunt***
  float BatV;   // V   Battery voltage, V
  float BatI;   // I   Battery current, A
  float PanV;   // VPV Panel voltage,   V
} targets;

//***Define Char Array ans String for Transmission between ESP modules***
unsigned char UDPCharPayload[sizeof(payload) + 2]; //  Array of characters as image of the structure for UDP xmit/rcv
String JSONpayload;


//*** Hourly integrated Values
float BatAh[36];    //  Ah statistics
//float BatWh[36];  //  Wh statistics
float BatVavg[36];  //  Avg Statistics
float currentInt;   //  Averaging bucket for hourly stats
long nCurrent;      //  Counter for averaging

// ***Power Integrations and mean values***
float dBatI;  // delta_voltage
float dBatV;  // delta_current


#ifndef INA_IS_NONE
byte devicesFound = 0;
float ina1_voltage;
float ina1_current;
float ina1_shunt;
float ina1_power;
#endif
