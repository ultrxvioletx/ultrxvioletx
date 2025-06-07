long tiempo, distancia, d; //DECLARAR VARIABLES DE TIEMPO Y DISTANCIA
int trigger = 13, echo = 12; //VARIABLES GUÍA DE TRIGGER Y ECHO

void setup() {
  Serial.begin(9600);

  //ULTRASONIC SENSOR
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

  //MOTORES
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

  //LEDS
  pinMode(A0, OUTPUT); //verde
  pinMode(A1, OUTPUT); //blanco
  pinMode(A2, OUTPUT); //rojo
}

void izq1() { //FUNCIÓN PARA GIRAR EL MOTOR 1 A LA IZQUIERDA
  digitalWrite(9, 1);
  digitalWrite(11, 0);
  digitalWrite(10, 1);
}
void izq2() { //FUNCIÓN PARA GIRAR EL MOTOR 2 A LA IZQUIERDA
  digitalWrite(6, 1);
  digitalWrite(5, 0);
  digitalWrite(4, 1);
}
void der1() { //FUNCIÓN PARA GIRAR EL MOTOR 1 A LA DERECHA
  digitalWrite(9, 1);
  digitalWrite(11, 1);
  digitalWrite(10, 0);
}
void der2() { //FUNCIÓN PARA GIRAR EL MOTOR 2 A LA DERECHA
  digitalWrite(6, 1);
  digitalWrite(5, 1);
  digitalWrite(4, 0);
}
void loop() {
  digitalWrite(trigger, HIGH); //TRIGGER LANZA LOS PULSOS
  delayMicroseconds(10); //ESPERAMOS 10 MICROSEGUNDOS
  digitalWrite(trigger, LOW); //APAGAR TRIGGER

  tiempo = pulseIn(echo, HIGH); //TIEMPO DE IDA Y REGRESO DEL PULSO
  d = tiempo / 59; //TIEMPO A DISTANCIA
  distancia = d / 3; //DIVIDIMOS PARA CONTEMPLAR EL ERROR

  if (distancia < 50) { //OBJETO CERCANO, MENOR A 50CM
    izq1(); izq2();
    digitalWrite(A0, HIGH);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
  }
  else if (distancia <= 100 && distancia >= 50) { //OBJETO ENTRE 50 Y 100CM
    der1(); der2();
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);
  }
  else if (distancia > 100) { //OBJETO LEJANO, MAYOR A 100CM
    der1(); izq2();
    digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);
  }

  Serial.print("Distancia: "); //IMPRIMIR EN PANTALLA LA DISTANCIA
  Serial.print(distancia);
  Serial.println("cm");
  delay(100);
}

