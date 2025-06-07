int a, b, c; //variables para determinar el valor recibido de los sensores

bool motor1, motor2; //determina el estado del motor
bool der1 = 0, der2 = 0, izq1 = 0, izq2 = 0; //veriables para determinar el giro

void setup() {
  Serial.begin(9600);
  //ENTRADAS
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  //MOTORES
  for (int i = 8; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
}

char Color(int mm) { //función que facilita determinar el color de acuerdo a los mm de separación
  if (0 <= mm && mm <= 305) {
    return 'n'; //si 7<mm<10 devuelve negro
  }
  else if (970 <= mm && mm <= 1000) {
    return 'b'; //si 0<mm<2 devuelve blanco
  }
  else return NULL; //en cualquier otro caso no devuelve nada
}

void loop() {
  a = analogRead(A0);
  b = analogRead(A1);
  c = analogRead(A2);

  if (Color(a) == 'n' && Color(b) == 'b' && Color(c) == 'n') { //negro blanco negro
    motor1 = 1; motor2 = 1; //motores encendidos
    der1 = 1; izq1 = 0; //derecha
    der2 = 1; izq2 = 0; //derecha
  }
  else if (Color(a) == 'b' && Color(b) == 'n' && Color(c) == 'n') { //blanco negro negro
    motor1 = 1; motor2 = 1; //motores encendidos
    der1 = 1; izq1 = 0; //derecha
    der2 = 0; izq2 = 1; //izquierda
  }
  else if (Color(a) == 'n' && Color(b) == 'n' && Color(c) == 'b') { //negro negro blanco
    motor1 = 1; motor2 = 1; //motores encendidos
    der1 = 0; izq1 = 1; //izquierda
    der2 = 1; izq2 = 0; //derecha
  }
  else if (Color(a) == 'b' && Color(b) == 'b' && Color(c) == 'b') { //blanco blanco blanco
    motor1 = 1; motor2 = 1; //motores encendidos
    der1 = 0; izq1 = 1; //izquierda
    der2 = 0; izq2 = 1; //izquierda
  }
  else { //cualquier otro caso
    motor1 = 0; motor2 = 0; //motores apagados
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

