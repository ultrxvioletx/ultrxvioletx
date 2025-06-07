String a, b, c; //valores de los switch
String combinacion; //cadena de numeros

bool motor1, motor2; //determina el estado del motor
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

  //ENTRADAS
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}
void loop() {
  a = digitalRead(A0);
  b = digitalRead(A1);
  c = digitalRead(A2);

  combinacion = a + b + c;

  switch (String(combinacion).toInt()) {
    case 0:
      motor1 = 0; //detenido
      motor2 = 0; //detenido
      break;
    case 1:
      motor1 = 1; //encendido
      motor2 = 1; //encendido

      der1 = 0; izq1 = 1; //giro a la izquierda
      der2 = 1; izq2 = 0; //giro a la derecha
      break;
    case 10:
      motor1 = 1; //encendido
      motor2 = 1; //encendido

      der1 = 1; izq1 = 0; //giro a la derecha
      der2 = 1; izq2 = 0; //giro a la derecha
      break;
    case 11:
      motor1 = 1; //encendido
      motor2 = 1; //encendido

      der1 = 1; izq1 = 0; //giro a la derecha
      der2 = 0; izq2 = 1; //giro a la izquierda
      break;
    case 100:
      motor1 = 1; //encendido
      motor2 = 1; //encendido

      der1 = 0; izq1 = 1; //giro a la izquierda
      der2 = 1; izq2 = 0; //giro a la derecha
      break;
    case 101:
      motor1 = 0; //detenido
      motor2 = 0; //detenido
      break;
    case 110:
      motor1 = 1; //encendido
      motor2 = 1; //encendido

      der1 = 0; izq1 = 1; //giro a la izquierda
      der2 = 1; izq2 = 0; //giro a la derecha
      break;
    case 111:
      motor1 = 1; //encendido
      motor2 = 1; //encendido

      der1 = 0; izq1 = 1; //giro a la izquierda
      der2 = 0; izq2 = 1; //giro a la izquierda
      break;
  }

  //MOTOR1
  digitalWrite(11, motor1); //Se habilita el motor 1
  digitalWrite(13, der1);
  digitalWrite(12, izq1);
  //MOTOR2
  digitalWrite(10, motor2); //Se habilita el motor 2
  digitalWrite(9, der2);
  digitalWrite(8, izq2);
}

