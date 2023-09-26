//Ejercicio 4

#define pinLed 3 //Primer pin analógico con
#define pinPotenciometro A4 //Pin analógico dle potenciometro

int voltaje = 0; //voltaje leido del pin analogico, 0-1023
int voltajeLed = 0; //Voltaje de salida al led

void setup() {
	Serial.begin(9600); //Inicializamos el monitor serie
}

void loop() {
	voltaje = analogRead(pinPotenciometro); //Leemos el valor del potenciometro
  Serial.println("Voltaje leido: " + voltaje); //Imprimimos el voltaje leido del potenciometro en el monitor serie
  voltajeLed = map(voltage, 0, 1023, 0, 255); //Voltaje del led mapeado 0-1023 -> 0-255
  Serial.print("Voltaje mapeado: " + voltajeLed); //Imprimimos el voltaje mapeado en el monitor serie
	analogWrite(pinLed, voltajeLed); //Aplicamos el voltaje mapeado al led mediante la salida analógica
  delay(100); //Añadimos un pequeño delay para que el programa no se vuelva muy loco
}
