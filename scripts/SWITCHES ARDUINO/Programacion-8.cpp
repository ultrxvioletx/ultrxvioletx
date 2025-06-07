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

void izquierda(){ //FUNCIÓN PARA GIRAR LOS MOTORES A LA IZQUIERDA
  //MOTOR1
  digitalWrite(9, 1);
  digitalWrite(11, 0);
  digitalWrite(10, 1);
  //MOTOR2
  digitalWrite(6, 1);
  digitalWrite(5, 0);
  digitalWrite(4, 1);
}
void derecha(){ //FUNCIÓN PARA GIRAR LOS MOTORES A LA DERECHA
  //MOTOR1
  digitalWrite(9, 1);
  digitalWrite(11, 1);
  digitalWrite(10, 0);
  //MOTOR2
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

  if (distancia <= 20){ //OBJETO CERCANO, MENOR O IGUAL A 20CM
    izquierda();
    digitalWrite(A0, LOW);
    digitalWrite(A2, HIGH);
  }
  else{ //ALG+UN OTRO CASO
    derecha();
    digitalWrite(A0, HIGH);
    digitalWrite(A2, LOW);
  }

  Serial.print("Distancia: "); //IMPRIMIR EN PANTALLA LA DISTANCIA
  Serial.print(distancia);
  Serial.println("cm");
  delay(100);
}

