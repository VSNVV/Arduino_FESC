// Definimos nuestras 7 salidas para el display de 7 segmentos
#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define F 7
#define G 8
// Variable global de cuenta
int count = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); // Inicializar la comunicación serie
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT); 
}

void loop() {
  int trama[7];
  decodifica(count, trama);
  Serial.println(count);
  enviaTrama(trama);
  if(count < 9){
    count++;
  }
  else{
    count = 0;
  }
  delay(1000);
}

void enviaTrama(int trama[]){
  for(int index = 0; index < 7; index++){
    if(trama[index] == 1){
      digitalWrite(index + 2, HIGH);
    }
    else{
      digitalWrite(index + 2, LOW);
    }
  }
}

void decodifica(int numero, int trama[]) {
  switch (numero) {
    case 1:
      trama[0] = 1; trama[1] = 0; trama[2] = 0; trama[3] = 1; trama[4] = 1; trama[5] = 1; trama[6] = 1;
      break;
    case 2:
      trama[0] = 0; trama[1] = 0; trama[2] = 1; trama[3] = 0; trama[4] = 0; trama[5] = 1; trama[6] = 0;
      break;
    case 3:
      trama[0] = 0; trama[1] = 0; trama[2] = 0; trama[3] = 0; trama[4] = 1; trama[5] = 1; trama[6] = 0;
      break;
    case 4:
      trama[0] = 1; trama[1] = 0; trama[2] = 0; trama[3] = 1; trama[4] = 1; trama[5] = 0; trama[6] = 0;
      break;
    case 5:
      trama[0] = 0; trama[1] = 1; trama[2] = 0; trama[3] = 0; trama[4] = 1; trama[5] = 0; trama[6] = 0;
      break;
    case 6:
      trama[0] = 0; trama[1] = 1; trama[2] = 0; trama[3] = 0; trama[4] = 0; trama[5] = 0; trama[6] = 0;
      break;
    case 7:
      trama[0] = 0; trama[1] = 0; trama[2] = 0; trama[3] = 1; trama[4] = 1; trama[5] = 1; trama[6] = 1;
      break;
    case 8:
      trama[0] = 0; trama[1] = 0; trama[2] = 0; trama[3] = 0; trama[4] = 0; trama[5] = 0; trama[6] = 0;
      break;
    case 9:
      trama[0] = 0; trama[1] = 0; trama[2] = 0; trama[3] = 1; trama[4] = 1; trama[5] = 0; trama[6] = 0;
      break;
    case 0:
      trama[0] = 0; trama[1] = 0; trama[2] = 0; trama[3] = 0; trama[4] = 0; trama[5] = 0; trama[6] = 1;
      break;
    default:
      // Para otros números, definir otras tramas aquí
      for (int i = 0; i < 7; i++) {
        trama[i] = 0;
      }
      break;
  }
}
