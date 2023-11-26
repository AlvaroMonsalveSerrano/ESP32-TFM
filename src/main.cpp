#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "MQTT.h"
#include "EAR.h"
#include "wifi.h"


#define LIMITE_OXIGENO 100


int value; 


void setup() {

  serialConfiguration();

  connectToWiFi();

  initMqtt();

  setUpPinEAR();

  value = LIMITE_OXIGENO;

}

void loop() {

  handleMqtt();

  value = value - 1;
  if(value > 0){
    publishStringDataToMqtt(String(value));
    Serial.print("Oxígeno: ");
    Serial.print(value);
    Serial.println();

    if(value <= 80){
      // digitalWrite(LED, HIGH);
    }

  }else{
    Serial.println("BOTELLA VACÍA");
  }

  // onSemaphore();

  delay(1000);

}
