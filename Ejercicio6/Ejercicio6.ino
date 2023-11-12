#include <SD.h>
#include <SPI.h>
#include <NewPing.h>

File fichero;
int ultimaPosicion = 0;
#define timeDelay 1000

#define CS 4
#define SCK 13
#define MOSI 7
#define MISO 12

#define distanciaMaxima 200
#define triggerPin 8
#define echoPin 7

NewPing sonar(triggerPin, echoPin, distanciaMaxima);

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  Serial.print("Iniciando tarjeta SD...");
  if (!SD.begin(CS)) {
    Serial.println("Error al inicializar");
    return;
  }
  Serial.println("Inicializacion completada");
}

void loop() {
  for(int i = 0; i < 10; i++){
    fichero = SD.open("Leds.txt", FILE_WRITE);
    long dist = sonar.ping_cm(); //Medimos la distancia del ultrasonido en cm
    enciendeLeds(dist);
    if(fichero){
      Serial.print("Escribiendo...");
      Serial.print("Escribiendo en SD...");
      fichero.println(dist);
      fichero.close();
      Serial.println(dist);
    }
    else{
      Serial.println("Error escribiendo");
    }
    delay(timeDelay);
  }

  //Una vez que hemos escrito, leemos el contenido
  fichero = SD.open("Leds.txt"); //Abrimos el archivo Leds.txt

 int bytesTotales = fichero.size();
  String cadena = "";
  if (fichero) {
    if (ultimaPosicion >= bytesTotales);
      ultimaPosicion = 0;
    fichero.seek(ultimaPosicion);
    //--Leemos una línea de la hoja de texto
    while (fichero.available()) {
      char caracter = fichero.read();
      cadena = cadena + caracter;
      ultimaPosicion = fichero.position();
      if (caracter == 10){
        break;
      }
    }
    fichero.close();
    Serial.print("Cadena Leida:");
    Serial.print(cadena);
  } else {
    Serial.println("Error al abrir el archivo");
  }
}

void enciendeLeds(long dist){
  int ledsApagados = 0;
  if((dist) < 20){
    //Se encienden los 4 leds
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(5, HIGH);
    digitalWrite(6, HIGH);
  }
  else if(20 < (dist) < 30){
    //Se encienden 3 leds
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(5, HIGH);
  }
  else if(30 < (dist) < 40){
    //Se encienden 2 leds
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
  }
  else{
    //Se enciende 1 led
    digitalWrite(2, HIGH);
  }
}
