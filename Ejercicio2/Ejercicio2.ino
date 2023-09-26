//Ejercicio 2

#include <TM1637Display.h>  //Importamos la libreria del display

#define CLK 2  //Definimos que la señal de reloj está conectada al pin 2 del arduino
#define DIO 3  //Definimos que la señal de intercambio de datos está conectada al pin 3 del arduino
#define PULS_JUGADOR_1 5 //Definimos que el pulsador del jugador 1 está conectado al pin 5 del arduino
#define PULS_JUGADOR_2 6 //Definimos que el pulsador del jugador 2 está conectado al pin 6 del arduino

int puntosJugador1 = 0; //Variable entera que almacena los puntos del jugador 1
int puntosJugador2 = 0; //Variable entera que almacena los puntos del jugador 2
int timeDelay = 100;    //Variable entera que controla el timepo (en ms) entre pulsada y pulsada

bool antirebote = false;  //Variable entera que controla que no se pulse dos veces el pulsador evitando el rebote

TM1637Display display(CLK, DIO); //Creamos la instancia del display

const uint8_t CERO[] = {
  display.encodeDigit(0),
  display.encodeDigit(0),
  display.encodeDigit(0),
  display.encodeDigit(0)
};

void setup() {
  pinMode(PULS_JUGADOR_1, INPUT); //Configuramos el pulsador del jugador 1 como entrada
  pinMode(PULS_JUGADOR_2, INPUT); //Configuramos el pulsador del jugador 2 como entrada
  Serial.begin(9600); //Inicializamos el monitor serie
  displayInicial(); //Inicializamos el display
  delay(2000); //2 segundos de cooldown
  display.setSegments(CERO); //Imprimimos todo ceros en el display
}

void loop() {
  if (antirebote) {
    delay(timeDelay);
    antirebote = false;
  }
  while (digitalRead(PULS_JUGADOR_1) == LOW && digitalRead(PULS_JUGADOR_2) == LOW); //Generamos una espera activa hasta que pulsemos alguno de los dos pulsadores

  if (digitalRead(PULS_JUGADOR_1) == HIGH) {
    //Verificamos que el pulsador del jugador 1 está pulsado
    puntosJugador1++; //Incrementamos en 1 los puntos del jugador 1
  }
  if (digitalRead(PULS_JUGADOR_2) == HIGH) {
    //Verificamos que el pulsador del jugador 2 está pulsado
    puntosJugador2++; //Incrementamos en 1 los puntos del jugador 2
  }

  while (digitalRead(PULS_JUGADOR_1) == HIGH || digitalRead(PULS_JUGADOR_2) == HIGH);  //Si mantiene presionado despues del puntuaje no sumará, ya que se quedará aqui haciendo espera activa

  displayScores(); //Una vez todo correcto, mostramos la puntuación en el display

  antirebote = true; //Activamos el antirebote para que tenga lugar un breve delay antes de pulsar el pulsador
}

//Función para poner una "pantalla de inicio"
void displayInicial() {
  display.setBrightness(0x0f);
  imprimePuntuaciones();
  const uint8_t SEG_J1J2[] = {
    SEG_B | SEG_C | SEG_D,                  // J
    display.encodeDigit(1),                 // 1
    SEG_B | SEG_C | SEG_D,                  // J
    display.encodeDigit(2)                  // 2
  };

  display.setSegments(SEG_J1J2);            //Aplicamos los segmentos anteriores al display
}

//Funcion para mostrar la puntuacion de cada jugador en el display
void displayScores() {
  printScores();
  const uint8_t SEG_PUNTOS[] = {
    display.encodeDigit(puntosJugador1 / 10),
    display.encodeDigit(puntosJugador1 % 10),
    display.encodeDigit(puntosJugador2 / 10),
    display.encodeDigit(puntosJugador2 % 10)
  };
  display.setSegments(SEG_PUNTOS);          //MAplicamos los segmentos anteriores al display, que, al ser numeros, usando la funcion encodeDigit pone automáticamente los segmentos
}

//Funcion para imprimir la puntuacion de cada jugador en el monitor serie de arduino
void imrpimePuntuaciones() {
  Serial.print("\n");
  Serial.print("Jugador 1: " + puntosJugador1);
  Serial.print(puntosJugador1);
  Serial.print("\n");
  Serial.print("Jugador 2: ");
  Serial.print(puntosJugador2);
  Serial.print("\n");
}