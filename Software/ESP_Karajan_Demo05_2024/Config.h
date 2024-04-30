// N.B. Compile sketch with following board settings: 
//- for option 8266:           LolinWEMOSD1 (Clone)     
//- for option TTGO:           TTGO T1 
//- for option HELTEC LoRa:    HELTEC WiFi Lora32  (Not V2 !) from HELTEC, not generic
//----------------------- HARDWARE OPTIONS ---------------------------------
#define SCREEN_IS_TTGO   // _NONE , _64x48 , _128x64, _TTGO, _HELTEC, _WEMOS32 _HW364A ; 
#define SCREEN_IS_REVERSED // _IS_NORMAL, _IS_REVERSED To turn the display 180° if required
#define BRIGHTNESS 128     // PWM value for default brightness with TTGO 0=totally dark;255=totally shiny

//----------------------- SOFTWARE OPTIONS ---------------------------------
#define DASHBRD_IS_THINGER    // _NONE , _THINGER          // (Internet Dashboard)
#define TERM_IS_TELNET     // _TELNET, _SERIAL , _SOFTSER, _2SERIAL // defines where do Menus and Reports occur: _SERIAL and D7_IS_VICTRON are mutually exclusive )
#define UDP_IS_NONE        // _NONE , _SEND , _RECEIVE  // (UDP Inter-ESP Communication)
#define ESP_UDP_ADDR       "192.168.188.85"                 // (IP of the receiving ESP having UDP_IS_RECEIVE) 
#define ESP_UDP_PORT       4200  // (Port used to send/receive Values to other ESP)
#define COM_IS_NONE        // _NONE , _HOURLY           // Periodical reports to computer 
#define COM_UDP_ADDR       "192.168.188.96"              // (IP of the receiving computer for night reports) 
#define COM_UDP_PORT       4230                          // (Port used to send/receive Values to other computer) 
#define DEVICE_NAME        "Karajan"                // Name of the device used as Hostname and at Thinger.io 
// #define DEVICE_NAME        WiFi.getHostname()            // Device name is automatic from MAC-Address
#define SERIAL_SWAP                                      

//----------------------- MEASUREMENT AND I/O OPTIONS---------------------------------
#define WEATHER_SOURCE_IS_OWM     // _NONE , _OWM , _BME680       // (Source of weather Information, URL in Credentials.h)
#define A0_IS_DEMO        // _NONE , _INPUT, _DEMO
#define A0_MAX        40  // if A0 is used, define the value of the full range measure
#define A0_HALF       20  // if A0 is used, define the value of the half range measure  (if different from A0_MAX /2 then with offset)
#define D0_IS_NONE        // _NONE , _RELAY1
#define D5_IS_NONE        // _NONE , _RELAY2
#define D6_IS_NONE        // _NONE , _RELAY3
#define D7_IS_NONE        // _NONE , _RELAY4; _SERIAL
#define D8_IS_NONE        // _NONE , _RELAY5; _SERIAL
#define INA_IS_NONE       // _NONE , _226    when measures come from an INA226 power sensor  (Smart shunt scenario)
#define ADS_IS_NONE       // _NONE , _1115   when measures come from an ADS1115 ADC converter (Drok type)

//--------------------------- WiFi Options -------------------------------------
#define WIFI_REPEAT          500      //mS for retries and LED blinking during WiFi initialization
#define WIFI_MAXTRIES        30
#define NTP_DELAY            6000
#define GRACE_PAUSE          //Suspend Network processing for a grace pause, if the remote server takes too long to react, in order to keep being reactive on menues

//---------------------------Options to reduce WiFi power hence the current draw-----------------------------
#ifdef ARDUINO_ARCH_ESP8266
#define WIFI_POWER           7.5   // from 0.5 to 21.5 full power (more current draw)
#else                              // ESP32
#define WIFI_POWER           WIFI_POWER_11dBm
#endif
/*
 Available ESP32 RF power parameters: 
 WIFI_POWER_19_5dBm   // _19dBm, _18_5dBm, _17dBm, _15dBm, _13dBm, _11dBm, _8_5dBm, _7dBm, _5dBm, _2dBm, _MINUS1dBm 
 Available ESP8266 RF power parameters: any value in 0.5 steps from
0 (for lowest RF power output, supply current ~ 70mA  to 20.5 (for highest RF power output, supply current ~ 80mA  
 */

//----------------------DO NOT EDIT until you know what you do -------------
#define SERIAL_SPEED      9600
#define RELAY1            16    // D0  Relay or FET control 1
#define RELAY2            14    // D5  Relay or FET control 2
#define REDLED            15    // D8
#define BLULED            13    // D7 <-- Victron
#define GRNLED            12    // D6
