#include <NewPing.h>
#include <AccelStepper.h>
#include <MultiStepper.h>

#define HALFSTEP 8
#define IN1 11 
#define IN2 10
#define IN3 9 
#define IN4 8
#define TRIGGER_PIN 12
#define ECHO_PIN 13

NewPing sonar(TRIGGER_PIN, ECHO_PIN);

int potenciometro1 = A0;
int potenciometro2 = A1;

int valorPotenciometro1 = 0;
int valorPotenciometro2 = 0;

int movimiento = 0;
int velocidad = 0;

AccelStepper stepper1(HALFSTEP, IN1, IN3, IN2, IN4);

void setup() {
  pinMode(potenciometro1, INPUT);
  pinMode(potenciometro2, INPUT);

  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(500.0);
}

void loop() {

  unsigned int dist = sonar.ping_cm();
  valorPotenciometro1 = analogRead(potenciometro1);
  valorPotenciometro2 = analogRead(potenciometro2);

  movimiento = map(valorPotenciometro1, 0, 1023, 0, 1600);
  velocidad = map(valorPotenciometro2, 0, 1023, 0, 1000);

  stepper1.setSpeed(velocidad);
  stepper1.moveTo(posicion);

 while ((stepper1.distanceToGo() != 0)/* && ((tm/ US_ROUNDTRIP_CM)>30)*/) 
  { 
    dist = sonar.ping_cm();
    stepper1.run();
    while((dist) < 30){ //Valor arbitrario para reconocer que hay un obstáculo cerca
      dist = sonar.ping();
    }
  }
}
