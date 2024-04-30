# ESP_Karajan
"Thing different !" What is ESP-Karajan?  
  
ESP-Karajan is a kind of operating system for ESP 8266 and ESP32 devices, taking away unproductive tasks of   
- initializing the processor,  
- WiFi connection,  
- the displays,  
- online dashboards,  
- measurement chips,  
- communication between ESP devices,  
- connection to a remote PC.    
  
Starting with Karajan is the basement for powerful projects  

Karajan contains a collaborative scheduler written for ease of use and clarity easily accessible to non-programmers without IT gibberish.  
It provides several levels of runtime processing:  
    - Instant data (highest priority, no fixed timing, for asynchronous communication with other devices)  
- Fast data  (runs every 125ms)  
- Menu        (runs every 125ms)  
- Slow data (runs every second)  
- Statistics   (runs every second)   
- Display      (runs every second)  
- Serial reports  (runs every second)  
- Wireless communication  (runs every second)  
The scheduler distributes the tasks running every second evenly over the whole second.
Additionally timing flags are provided:  
- NewMinute  
- Minute Expiring  
- NewHour  
- HourExpiring  
- NewDay  
- DayExpiring  
which allow to process statistics at the right time.  
These timing flags rely on the time given from a NTP server over the WiFi connection.  

But read the doc to discover all the other features of Karajan...  
