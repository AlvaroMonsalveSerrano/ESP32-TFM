

#include <Arduino.h>


void publishStringDataToMqtt(String data);

void initMqtt();

void connectMqtt();

void handleMqtt();

void suscribeMqtt();

void onMqttReceived(char* topic, byte* payload, unsigned int length);


