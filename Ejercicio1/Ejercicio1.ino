//--------=[DECLARACION DE VARIABLES]=--------
int pinPuls = 12;   //El pin que se conecta al pulsador es el 12
int pinLed1 = 2;    //El pin que se conecta al LED1 es el 2
int pinLed2 = 3;    //El pin que se conecta al LED2 es el 3
int pinLed3 = 4;    //El pin que se conecta al LED3 es el 4
int pinLed4 = 5;    //El pin que se conecta al LED4 es el 5
int pinLed5 = 6;    //El pin que se conecta al LED5 es el 6

int leds[] = {pinLed1, pinLed2, pinLed3, pinLed4, pinLed5};  //Creamos una lista con todos los pines de los LEDs
int longitud = sizeof(leds) / sizeof(leds[0]);

int puls = 0;       //Almacena si el pulsador está activo o no

int delayTime = 1000;

void setup() {
  pinMode(pinLed1, OUTPUT);   //Configuramos el pinLed1 como salida para poder alimentarlo
  pinMode(pinLed2, OUTPUT);   //Configuramos el pinLed2 como salida para poder alimentarlo
  pinMode(pinLed3, OUTPUT);   //Configuramos el pinLed3 como salida para poder alimentarlo
  pinMode(pinLed4, OUTPUT);   //Configuramos el pinLed4 como salida para poder alimentarlo
  pinMode(pinLed5, OUTPUT);   //Configuramos el pinLed5 como salida para poder alimentarlo
   
  pinMode(pinPuls, INPUT);    //Configuramos pinPuls como una entrada, para leer el estado del pulsador

}

void loop() {
  puls = digitalRead(pinPuls); //Cogemos el estado del pulsador

  if (puls == HIGH){
    //Verificamos que el pulsador no está activo, por tanto, apagaremos los LEDs
    digitalWrite(pinLed1, LOW); //Apagamos el LED1
    digitalWrite(pinLed2, LOW); //Apagamos el LED2
    digitalWrite(pinLed3, LOW); //Apagamos el LED3
    digitalWrite(pinLed4, LOW); //Apagamos el LED4
    digitalWrite(pinLed5, LOW); //Apagamos el LED5
  }
  else{
    
    //Enciende LEDs
    for (int led = 2; (led <= 6) && (puls == LOW); led++){
      digitalWrite(led, HIGH);
      delay(delayTime);
      puls = digitalRead(pinPuls);
    }
    //Apaga LEDs
    for (int led = 6; (led >= 2) && (puls == LOW); led--){
      digitalWrite(led, LOW);
      delay(delayTime);
      puls = digitalRead(pinPuls);
    }
  }
}