/* Header guard to prevent multiple inclusion */
#ifndef _ESP01_H_

/* Define header guard macro */
#define _ESP01_H_

/* Function declaration to connect ESP01 module to Wi-Fi access point */
void esp01_connectAP(void);

/* Function declaration to send temperature and humidity data to ThingSpeak */
void esp01_sendToThingspeak1(float,float);

/* Function declaration to send humidity data to ThingSpeak */
void esp01_sendToThingspeak2(float);

/* Function declaration to send motor status data to ThingSpeak */
void esp01_sendToThingspeak3(float);

/* End of header guard */
#endif
