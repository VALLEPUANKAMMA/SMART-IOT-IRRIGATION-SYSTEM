/*
 Function declaration for DHT11 display function

 This function reads temperature and humidity
 data from the DHT11 sensor and displays the
 values on the LCD screen.

 It may also send the sensor data to
 ThingSpeak cloud using ESP01 Wi-Fi module.
*/
void dht11_display(void);


/*
 Function declaration for RTC initialization function

 This function initializes the Real Time Clock (RTC)
 registers of LPC2148.

 It sets initial values for:
 - Hours
 - Minutes
 - Seconds

 Used for time-based operations in the project.
*/
void rtc_init(void);


/*
 Function declaration for compare temperature
 and humidity function

 This function compares current sensor readings
 with user-defined threshold values.

 Based on comparison results:
 - Motor ON/OFF decision is taken
 - Irrigation timing is selected
 - Motor status is updated to ThingSpeak
*/
void compare_temp_hum(void);
