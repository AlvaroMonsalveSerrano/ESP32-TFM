

#include <Arduino.h>

// A borrar
void doEARAccion1(String value);

void publishStringDataToMqtt(String data);

// // No tiene sentido aquí.
// void doEsp32OxigenBinomio(String value);

// // No tiene sentido aquí.
// void doBridgeAccion1(String value);

void initMqtt();

void connectMqtt();

void handleMqtt();

void suscribeMqtt();

void onMqttReceived(char* topic, byte* payload, unsigned int length);


