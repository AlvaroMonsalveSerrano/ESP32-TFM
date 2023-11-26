#include <Arduino.h>


#define ALARM1 "ON1"
#define ALARM2 "ON2"
#define ALARM3 "ON3"

#define RED 17
#define YELLOW 16
#define GREEN 18

/**
 * La función setUpPinEAR define la configuración de los pin para 
 * el semáforo instalado en la placa controlador.
 */
void setUpPinEAR(){
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
}

void onSemaphore(){
  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW); 
}

/**
 * La función  doEsp32OxigenBinomio realiza la funcionalidad asociada a la acción 
 * del envío de uan señal de oxígeno.
 */
void doEsp32OxigenBinomio(String value){
  Serial.print(value);
  Serial.println();
}


/**
 * La función doBridgeAccion1 realiza la funcionalidad asociada a la acción del evento 
 * asociado a la alarma de tipo 1.
 */
void doBridgeAccion1(String value){
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
