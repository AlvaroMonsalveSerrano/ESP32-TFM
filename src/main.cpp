#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include <config.h>
#include <MQTT.h>
#include <utils.h>

const int LIMITE_OXIGENO = 100;
int value; 

// -----------------------
//
// DEFINICIÓN DE FUNCIONES
//
// -----------------------

// Función para configurar el puerto Serie.
void serialConfiguration();

// Función para realizar una conexión a una WiFi.
void connectToWiFi();



// ----------------------------
//
// IMPLEMENTACIÓN DE FUNCIONES
//
// ----------------------------

void setup() {

  serialConfiguration();

  // Conexión a una red WiFi.
  connectToWiFi();

  initMqtt();

  value = LIMITE_OXIGENO;

}

void loop() {

  // Handler del protocolo MQTT
  handleMqtt();

  // Publicamos un valor.
  // int instante = millis();
  // Serial.printf("Valor a publicar: %e", instante);
  //publishLongDataToMqtt(millis());

  value = value - 1;
  if(value > 0){
    publishStringDataToMqtt(String(value));

  }else{
    Serial.println("BOTELLA VACÍA");
  }

  // publishStringDataToMqtt(String(millis()));

  delay(1000);

}


void serialConfiguration(){
  Serial.begin(115200);
  while(!Serial){
    delay(100);
  }
}

void connectToWiFi(){
  WiFi.begin(SSID, PASSWORD);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }

  Serial.println("WiFi connected");
}