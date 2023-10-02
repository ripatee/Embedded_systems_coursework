#ifndef _MQTTCONNECTION_H_
#define _MQTTCONNECTION_H_
#define IMEI_LEN 15
#define CGSN_RESPONSE_LENGTH (IMEI_LEN + 6 + 1) /* Add 6 for \r\nOK\r\n and 1 for \0 */
#define CLIENT_ID_LEN sizeof("nrf-") + IMEI_LEN

/**@brief Initialize the MQTT client structure
 */
int mqtt_client_init_wrapper(struct mqtt_client *client);

/**@brief Initialize the file descriptor structure used by poll.
 */
int mqtt_fds_init(struct mqtt_client *c, struct pollfd *fds);

/**@brief Function to publish data on the configured topic
 */
int mqtt_data_publish(struct mqtt_client *c, enum mqtt_qos qos,
	uint8_t *data, size_t len);

#endif /* _CONNECTION_H_ */