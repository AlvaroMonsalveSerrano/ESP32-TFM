#include <Arduino.h>

#include <utils.h>

// Semáforo alarmas
#define RED 17
#define YELLOW 16
#define GREEN 18

// Semáforo de nivel EAR
#define RED_EAR 0
#define YELLOW_EAR 2
#define GREEN_EAR 15


/**
 * La función setUpPinEAR define la configuración de los pin para 
 * el semáforo instalado en la placa controlador.
 */
void setUpPinEAR(){
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  pinMode(RED_EAR, OUTPUT);
  pinMode(YELLOW_EAR, OUTPUT);
  pinMode(GREEN_EAR, OUTPUT);  
}

/**
 * La función doBridgeAccion1 realiza la funcionalidad asociada a la acción de 
 * recepcionar eventos.
 */
void doBridgeAccion(String value){

  Serial.print("Recibido Acción : ");
  Serial.print(value);
  Serial.println(""); 

  if(value == ALARM1){
    Serial.println("Alarma 1"); 
    digitalWrite(RED, HIGH);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, LOW);

  } else if(value == ALARM2){
    Serial.println("Alarma 2"); 
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, LOW);

  } else if(value == ALARM3){
    Serial.println("Alarma 3"); 
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, HIGH);

  }else{
    Serial.println("Alarma error"); 
    digitalWrite(RED, HIGH);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(GREEN, HIGH);

  }
 
}

/**
 * La función setRedEar activa lus roja del semáforo de nivel.
 * 
 */
void setRedEar(){
    digitalWrite(RED_EAR, HIGH);
    digitalWrite(YELLOW_EAR, LOW);
    digitalWrite(GREEN_EAR, LOW);
}

/**
 * La función setYellowEar activa lus roja del semáforo de nivel.
 * 
 */
void setYellowEar(){
    digitalWrite(RED_EAR, LOW);
    digitalWrite(YELLOW_EAR, HIGH);
    digitalWrite(GREEN_EAR, LOW);
}

/**
 * La función setGreenEar activa luz roja del semáforo de nivel.
 * 
 */
void setGreenEar(){
    digitalWrite(RED_EAR, LOW);
    digitalWrite(YELLOW_EAR, LOW);
    digitalWrite(GREEN_EAR, HIGH);
}

/**
 * La función setAllLedEar activa todas las luces del semáforo de nivel.
 * 
 */
void setAllLedEar(){
    digitalWrite(RED_EAR, HIGH);
    digitalWrite(YELLOW_EAR, HIGH);
    digitalWrite(GREEN_EAR, HIGH);  
}

