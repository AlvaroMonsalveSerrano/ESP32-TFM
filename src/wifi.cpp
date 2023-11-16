#include <Arduino.h>
#include <WiFi.h>
#include "config_wifi.h"

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