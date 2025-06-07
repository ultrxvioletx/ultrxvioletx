char ent; //variable de entrada de datos
int velocidad1, velocidad2; //velocidades de los motores
bool der1 = 0, der2 = 0, izq1 = 0, izq2 = 0; //veriables para determinar el giro


void setup() {
  //MOTOR1
  pinMode(13, OUTPUT); //IN1
  pinMode(12, OUTPUT); //IN2
  pinMode(11, OUTPUT); //EN1

  //MOTOR2
  pinMode(10, OUTPUT); //EN2
  pinMode(9, OUTPUT); //IN3
  pinMode(8, OUTPUT); //IN4

  Serial.begin(9600); //recibir información de entrada
}
void loop() {
  if (Serial.available() > 0) { //Sentencia para saber si se ingresa un valor
    ent = Serial.read(); //Se actualiza la variable
  }
  switch (ent) {
    case 's':
      velocidad1 = 0; //detenido
      velocidad2 = 0; //detenido
      break;
    case 'd':
      velocidad1 = 0; //detenido
      velocidad2 = 127; //velocidad al 50%

      der2 = 1; izq2 = 0; //giro a la derecha
      break;
    case 'a':
      velocidad1 = 225; //velocidad al 100%
      velocidad2 = 225; //velocidad al 100%

      der1 = 1; izq1 = 0; //giro a la derecha
      der2 = 1; izq2 = 0; //giro a la derecha
      break;
    case 'e':
      velocidad1 = 127; //velocidad al 50%
      velocidad2 = 191; //velocidad al 75%

      der1 = 1; izq1 = 0; //giro a la derecha
      der2 = 0; izq2 = 1; //giro a la izquierda
      break;
    case 'i':
      velocidad1 = 127; //velocidad al 50%
      velocidad2 = 0; //detenido

      der1 = 0; izq1 = 1; //giro a la izquierda
      break;
    case '1':
      velocidad1 = 25; //velocidad al 10%
      velocidad2 = 25; //velocidad al 10%

      der1 = 1; izq1 = 0; //giro a la derecha
      der2 = 1; izq2 = 0; //giro a la derecha
      break;
    case '2':
      velocidad1 = 127; //velocidad al 50%
      velocidad2 = 127; //velocidad al 50%

      der1 = 1; izq1 = 0; //giro a la derecha
      der2 = 1; izq2 = 0; //giro a la derecha
      break;
    case '3':
      velocidad1 = 216; //velocidad al 85%
      velocidad2 = 216; //velocidad al 85%

      der1 = 1; izq1 = 0; //giro a la derecha
      der2 = 1; izq2 = 0; //giro a la izquierda
      break;
  }
  //MOTOR1
  analogWrite(11, velocidad1); //Se habilita el motor 1 mediante PWM
  digitalWrite(13, der1);
  digitalWrite(12, izq1);
  //MOTOR2
  analogWrite(10, velocidad2); //Se habilita el motor 2 mediante PWM
  digitalWrite(9, der2);
  digitalWrite(8, izq2);
}

