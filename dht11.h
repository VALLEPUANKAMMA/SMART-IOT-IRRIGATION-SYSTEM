/* Header guard to prevent multiple inclusion */
#ifndef _DHT11_H_

/* Define header guard macro */
#define _DHT11_H_

/* Function declaration to send start request signal to DHT11 sensor */
void dht11_request(void);

/* Function declaration to receive response from DHT11 sensor */
void dht11_response(void);

/* Function declaration to read one byte of data from DHT11 sensor */
unsigned char dht11_data(void);

/* End of header guard */
#endif
