#include <SD.h>
#include <SPI.h>
#include <NewPing.h>

File fichero;
int ultimaPosicion = 0;

#define CS 4
#define SCK 13
#define MOSI 11
#define MISO 12

#define distanciaMaxima 200
#define triggerPin 8
#define echoPin 9

int led1 = 2;
int led2 = 3;
int led3 = 5;
int led4 = 6;

int delayTime = 1000;

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
    fichero = SD.open("test.txt", FILE_WRITE);
    long dist = sonar.ping_cm(); //Medimos la distancia del ultrasonido en cm
    enciendeLeds(dist);
    if(fichero){
      Serial.print("Escribiendo en SD... -> ");
      fichero.println(dist);
      fichero.close();
      Serial.println(dist);
    }
    else{
      Serial.println("Error escribiendo");
    }
    delay(delayTime);
  }

  //Una vez que hemos escrito, leemos el contenido
  fichero = SD.open("test.txt"); //Abrimos el archivo Leds.txt

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