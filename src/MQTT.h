#include <utils.h>

WiFiClient espClient;
PubSubClient mqttClient(espClient);

String payload = "";
String content = "";



/**
 * Función suscribeMqtt que realiza la suscripción de a un topic.
 * 
 */
void suscribeMqtt(){
  mqttClient.subscribe(TOPIC_ESP32_OXIGEN_BINOMIO1);
  Serial.println("Subscrito al topic: esp32/binomio1/oxigeno");

  mqttClient.subscribe(TOPIC_BRIDGE_BINOMIO1_ACCION1);
  Serial.println("Subscrito al topic: bridge/binomio1/accion1");
}

/**
 * Función publishLongDataToMqtt que realiza la publicación de un mensaje.
 * Parámetros:
 *  data: unsigned long .- Dato del mensaje a enviar al topic.
 * 
 */
void publishLongDataToMqtt(unsigned long data){
  payload = String(data);
  mqttClient.publish(TOPIC_ESP32_OXIGEN_BINOMIO1, (char*)payload.c_str());
  Serial.print("Publicado...");
  Serial.println(payload);
}

void publishStringDataToMqtt(String data){
  mqttClient.publish(TOPIC_ESP32_OXIGEN_BINOMIO1, (char*)data.c_str());
  // Serial.print("Publicado...");
  // Serial.println(data);
}



/**
 * Función charToString transformadora de byte a String.
 * 
 */
String charMsgToString(byte* payload, unsigned int length){
  String content = "";
  for (size_t i = 0; i < length; i++) {
    content.concat((char)payload[i]);
  }

  return content;    
}


void doEsp32OxigenBinomio(String value){
  Serial.print(value);
  Serial.println();
}

void doBridgeAccion1(String value){
  Serial.print("Recibido Acción 1: ");
  Serial.print(value);
  Serial.println("");  
}


/**
 * Función OnMqttReceived que realiza la recepción de un mensaje desde 
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
    content = charMsgToString(payload, length);
    doBridgeAccion1(content);

  }


}


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
 * 
 */
void handleMqtt(){
  if (!mqttClient.connected()){
    connectMqtt();
  }
  mqttClient.loop();

}  


