#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "MQTT.h"
#include "wifi.h"

#define LED 17
#define LIMITE_OXIGENO 100

int value; 



void setup() {

  serialConfiguration();

  connectToWiFi();

  initMqtt();

  value = LIMITE_OXIGENO;

  pinMode(LED, OUTPUT);

}

void loop() {

  handleMqtt();

  // Publicamos un valor.
  // int instante = millis();
  // Serial.printf("Valor a publicar: %e", instante);
  //publishLongDataToMqtt(millis());

  value = value - 1;
  if(value > 0){
    publishStringDataToMqtt(String(value));
    Serial.print("Oxígeno: ");
    Serial.print(value);
    Serial.println();

    if(value <= 80){
      digitalWrite(LED, HIGH);
    }

  }else{
    Serial.println("BOTELLA VACÍA");
  }

  // publishStringDataToMqtt(String(millis()));

  delay(1000);

}
