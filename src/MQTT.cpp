
#include <Arduino.h>

#include <WiFi.h>
#include <PubSubClient.h>

#include "utils.h"
#include "EAR.h"

#include "config_mqtt.h"

WiFiClient espClient;
PubSubClient mqttClient(espClient);

String payload = "";
String accion = "";


/**
 * La función suscribeMqtt realiza la suscripción de a un topic.
 * 
 */
void suscribeMqtt(){
  mqttClient.subscribe(TOPIC_ESP32_OXIGEN_BINOMIO1);
  Serial.println("Subscrito al topic: esp32/binomio1/oxigeno");

  mqttClient.subscribe(TOPIC_BRIDGE_BINOMIO1_ACCION1);
  Serial.println("Subscrito al topic: app/binomio1/alarm1");

  mqttClient.subscribe(TOPIC_BRIDGE_BINOMIO1_ACCION2);
  Serial.println("Subscrito al topic: app/binomio1/alarm2");

  mqttClient.subscribe(TOPIC_BRIDGE_BINOMIO1_ACCION3);
  Serial.println("Subscrito al topic: app/binomio1/alarm3");  
}


/**
 * Función publishStringDataToMqtt realiza la publicación de un mensaje.
 * Parámetros:
 *  topic: const char* .- Nombre del topic del broker MQTT. 
 *  data: unsigned long .- Dato del mensaje a enviar al topic.
 * 
 */
void publishStringDataToMqtt(String data){
  mqttClient.publish(TOPIC_ESP32_OXIGEN_BINOMIO1, (char*)data.c_str());
}



/**
 * Función OnMqttReceived  realiza la recepción de un mensaje desde 
 * el broker MQTT.
 * 
 */
void onMqttReceived(char* topic, byte* payload, unsigned int length){

  String topicName = String(topic);



  if(topicName == TOPIC_ESP32_OXIGEN_BINOMIO1){
    // No hacemos nada...
    // content = charMsgToString(payload, length);
    // doEsp32OxigenBinomio(content);

  } else if(topicName == TOPIC_BRIDGE_BINOMIO1_ACCION1){

    Serial.print("Topic: ");
    Serial.println(topicName);

    accion = charMsgToString(payload, length);
    Serial.println("Entramos en Accion1...");
    Serial.println(accion);
    doBridgeAccion1("ON1");

  } else if(topicName == TOPIC_BRIDGE_BINOMIO1_ACCION2){

    Serial.print("Topic: ");
    Serial.println(topicName);

    accion = charMsgToString(payload, length);
    Serial.println("Entramos en Accion2...");
    Serial.println(accion);
    doBridgeAccion1("ON2");

  } else if(topicName == TOPIC_BRIDGE_BINOMIO1_ACCION3){

    Serial.print("Topic: ");
    Serial.println(topicName);

    accion = charMsgToString(payload, length);
    Serial.println("Entramos en Accion3...");
    Serial.println(accion);
    doBridgeAccion1("ON3");
  }

}


/**
 * La función initMqtt realiza la configuración de la conexión al broker
 * MQTT.
 */
void initMqtt(){
  Serial.println("Iniciamos MQTT....");
  mqttClient.setServer(MQTT_BROKER_ADRESS, MQTT_PORT);
  Serial.println("Set server asignado....");
  Serial.println(MQTT_BROKER_ADRESS);
  Serial.println(MQTT_PORT);

  suscribeMqtt();
  mqttClient.setCallback(onMqttReceived);

  Serial.println("Conectado a MQTT Mosquitto.");
}


/**
 * La función connectMqtt realiza la definición de la conexión al broker
 * MQTT.
 */
void connectMqtt(){
  while (!mqttClient.connected()){
    Serial.print("Iniciada conexión MQTT...");
    if (mqttClient.connect(MQTT_CLIENT_NAME)){
      suscribeMqtt();
    } else {
      Serial.print("Fallo conexión MQTT, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" reconectando en 5 segundos");

      delay(5000);
    }
  }
}

/**
 * La función handleMqtt es aquella función de utilidad para definir
 * las operaciones con el broker MQTT
 */
void handleMqtt(){
  if (!mqttClient.connected()){
    connectMqtt();
  }
  mqttClient.loop();

}  

// A borrar
void doEARAccion1(String value){
    doBridgeAccion1(value);
}  
