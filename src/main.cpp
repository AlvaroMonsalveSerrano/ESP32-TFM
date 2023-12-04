#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

#include "MQTT.h"
#include "EAR.h"
#include "wifi.h"

#define OXIGEN_LIMIT 100

int value; 

void setup() {

  value = OXIGEN_LIMIT;

  serialConfiguration();
  connectToWiFi();
  initMqtt();
  setUpPinEAR();
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
  
  if(value > 0){
    publishStringDataToMqtt(String(value));
    Serial.print("Oxigeno: ");
    Serial.print(value);
    Serial.println();
    setLevelSemaphore(value);
    value = value - 1;

  }else{
    Serial.println("## Botella vacía,proceso de llenado...");    
    delay(10000);
    value = OXIGEN_LIMIT; 
    setGreenEar();   

  }

  delay(1000);

}
