//Ejercicio 3

//Librerias necesarias
#include <dht11.h>          //Librería del sensor de temperatura y humedad
#include <TM1637Display.h>  //Librería del display

//Variables globales
#define pinDHT11 2
#define CLK 3
#define DIO 4
#define brilloDisplay 0x0f
#define pinLedRojo 5
#define pinLedVerde 6

dht11 DHT11; //Creamos la instancia del sensor de temperatura y humedad

TM1637Display display(CLK, DIO); //Creamos la instancia del display

void setup() {
  display.setBrightness(brilloDisplay); //Indicamos el nivel del brillo al display
  DHT11.attach(pinDHT11); //Indicamos que el sensor está conectado al pin 2 del arudino
  Serial.begin(9600); //Inicializamos el monitor serie
  displayInicial(); //Inicializampos el display

}

void loop() {
  //Lo primero que haremos es leer el sensor DHT11 y almacenar los datos
  int temperatura = DHT11.readTemperature(); //Leemos la temperatura del sensor
  int humedad = DHT11.readHumidity(); //Leemos la humedad del sensor

  //Ahora imprimiremos los resultados en el monitor serie
  Serial.print("Temperatura --> " + temperatura + "\nHumedad --> " + humedad + "\n");

  //Una vez hemos leido ambas magnitudes, imprimos los valores en el displayl
  imprimeResultados(temperatura, humedad);
  //Una vez que los reusltados son visibles en ambos lados, encenderemos el led en función del resultado de la temperatura
  enciendeLed(temperatura);
  //Le metemos un delay de 2 segundos para que no se vuelva loco el DHT11 ni el display
  delay(2000);
}

//Función para poner una "pantalla de inicio"
void displayInicial() {
  /*
  ºC --> Tempratura
  HU --> Humedad
  */
  display.setBrightness(brilloDisplay);
  const uint8_t SEG_J1J2[] = {
    SEG_A | SEG_B | SEG_F | SEG_G,                 // º
    SEG_A | SEG_F | SEG_E | SEG_D,                 // C
    SEG_F | SEG_B | SEG_E | SEG_C | SEG_G,         // H
    SEG_F | SEG_E | SEG_D | SEG_C | SEG_B          // U
  };
}

//Función para mostrar los resultados en el display
void imprimeResultados(int temp, int hum){
  //Imprime los resultados de la lectura del sensor en en display
  const uint8_t SEG_PUNTOS[] = {
    display.encodeDigit(temp / 10),
    display.encodeDigit(temp % 10),
    display.encodeDigit(hum / 10),
    display.encodeDigit(hum % 10)
  };
  display.setSegments(SEG_PUNTOS);
}

//Función para encender un led segun la temperatura
void enciendeLed(int temp){
  if(temp > 22){
    digitalWrite(pinLedRojo, HIGH); //Encendemos el led rojo
    digitalWrite(pinLedVerde, LOW); //En consecuencia, apagamos el led verde
  }
  else{
    digitalWrite(pinLedVerde, HIGH); //Encendemos el led verde
    digitalWrite(pinLedRojo, LOW); //En consecuencia apagamos el led rojo en caso de que esté encendido
  }
}