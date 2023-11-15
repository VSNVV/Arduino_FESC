//Ejercicio 5

//Librerias necesarias
#include <NewPing.h> //Libreria del sensor de ultrasonido
#include <TM1637Display.h> //Libreria del display

//Variables globales
#define pinEcho 11
#define pinTrigger 12
#define distanciaMaxima 200

#define CLK 7
#define DIO 8
#define brillo 0x0f

int led1 = 3;
int led2 = 4;
int led3 = 5;
int led4 = 6;

int delayTime = 500;

//Instancias básicas
NewPing sonar(pinTrigger, pinEcho, distanciaMaxima); //Instancia para usar el sensor ultrasonido
TM1637Display display(CLK, DIO); //Instancia para usar el display

void setup() {
  display.setBrightness(brillo);
  Serial.begin(9600);
  //Indicamos que los pines de los leds son salidas
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  long distancia = sonar.ping_cm(distanciaMaxima);
  Serial.println(distancia);
  imprimeResultado(distancia); //Imprimimos el resultado en el display
  //Una vez que la distancia es visible, encenderemos los leds en funcion de la distancia que dé
  enciendeLeds(distancia);

}

//Función para mostrar el resultado en el display
void imprimeResultado(long dist){
  const uint8_t SEG_DIST[] = {
    display.encodeDigit(0), //Como el maximo es 200, este digito no nos hará falta
    display.encodeDigit((dist / 100)), //Centenas
    display.encodeDigit((dist) / 10), //Decenas
    display.encodeDigit((dist) % 10) //Unidades
  };
  display.setSegments(SEG_DIST);
}

//Función para encender los leds segun la distancia
void enciendeLeds(long dist){
  if(dist < 20){
    //Se encienden los 4 leds
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
    digitalWrite(led4, HIGH);
  }
  else if(dist < 30){
    //Se encienden 3 leds
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }
  else if(dist < 40){
    //Se encienden 2 leds
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }
  else{
    //Se enciende 1 led
    digitalWrite(led1, HIGH);
  }
  delay(delayTime);
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);
  digitalWrite(led4,LOW);
  
}
