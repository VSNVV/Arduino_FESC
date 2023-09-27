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

#define pinPrimerLed 3
#define pinUltimoLed 6

//Instancias básicas
NewPing sonar(pinTrigger, pinEcho, distanciaMaxima); //Instancia para usar el sensor ultrasonido
TM1637Display display(CLK, DIO); //Instancia para usar el display

void setup() {
  display.setBrightness(brillo);
  //Indicamos que los pines de los leds son salidas
  for (int i = pinPrimerLed; i <= pinUltimoLed; i++){
    pinMode(i, OUTPUT);
  }
}

void loop() {
  long distancia = sonar.pingCm(distanciaMaxima);
  imprimeResultado(distancia); //Imprimimos el resultado en el display
  //Una vez que la distancia es visible, encenderemos los leds en funcion de la distancia que dé


}

//Función para mostrar el resultado en el display
void imprimeResultado(long dist){
  const uint8_t SEG_DIST[] = {
    display.encodeDigit(0); //Como el maximo es 200, este digito no nos hará falta
    display.encodeDigit((int dist % 100) / 10), //Centenas
    display.encodeDigit((int dist) / 10), //Decenas
    display.encodeDigit((int dist) % 10) //Unidades
  };
  display.setSegments(SEG_DIST);
}

//Función para encender los leds segun la distancia
void enciendeLeds(long dist){
  int ledsApagados = 0;
  if((int dist) < 20){
    //Se encienden los 4 leds
    ledsApagados = 0;
  }
  else if(20 < (int dist) < 30){
    //Se encienden 3 leds
    ledsApagados = 1;
  }
  else if(30 < (int dist) < 40){
    //Se encienden 2 leds
    ledsApagados = 2;
  }
  else{
    //Se enciende 1 led
    ledsApagados = 3;
  }
  //Encendemos los leds correspondientes
  for(int i = pinPrimerLed; i <= pinUltimoLed - ledsApagados; i++){
      digitalWrite(i, HIGH);
  }
  //Apagamos los demás
  for(int i = pinPrimerLed + ledsApagados; i <= pinUltimoLed; i++){
    digitalWrite(i, LOW);
  }
}
