
// PubSubClient mqttClient(espClient);

#include <Arduino.h>

void suscribeMqtt();

void publishLongDataToMqtt(unsigned long data);

void publishStringDataToMqtt(String data);

String charMsgToString(byte* payload, unsigned int length);

void doEsp32OxigenBinomio(String value);

void doBridgeAccion1(String value);

void onMqttReceived(char* topic, byte* payload, unsigned int length);


void initMqtt();

void connectMqtt();

void handleMqtt();


