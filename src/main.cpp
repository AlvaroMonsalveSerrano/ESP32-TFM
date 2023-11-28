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
  setGreenEar();

}

void setLevelSemaphore(int value){

  if((100 >= value) & (value > 80)){
    setGreenEar();

  }else if( (80 >= value) & (value > 30)){
    setYellowEar();

  }else if((30 >= value) & (value > 0)){
    setRedEar();

  }else{
    setAllLedEar();

  }

}

void loop() {

  handleMqtt();

  value = value - 1;
  if(value > 0){
    publishStringDataToMqtt(String(value));
    Serial.print("Oxigeno: ");
    Serial.print(value);
    Serial.println();

    setLevelSemaphore(value);

  }else{
    Serial.println("BOTELLA VACÍA");    
    delay(10000);
    value = LIMITE_OXIGENO; 
    setGreenEar();   

  }

  delay(1000);

}
