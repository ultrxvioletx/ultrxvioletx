long tiempo, distancia, d; //DECLARAR VARIABLES DE TIEMPO Y DISTANCIA
int trigger = 13, echo = 12; //VARIABLES GUÍA DE TRIGGER Y ECHO
String mensaje; //VARIABLE VELOCIDAD DEL MOTOR

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

void izq1(int velocidad) { //FUNCIÓN PARA GIRAR EL MOTOR 1 A LA IZQUIERDA
  analogWrite(9, velocidad); //SE HABILITA MEDIANTE PWM
  digitalWrite(11, 0);
  digitalWrite(10, 1);
}
void izq2(int velocidad) { //FUNCIÓN PARA GIRAR EL MOTOR 2 A LA IZQUIERDA
  analogWrite(6, velocidad); //SE HABILITA MEDIANTE PWM
  digitalWrite(5, 0);
  digitalWrite(4, 1);
}
void der1(int velocidad) { //FUNCIÓN PARA GIRAR EL MOTOR 1 A LA DERECHA
  analogWrite(9, velocidad); //SE HABILITA MEDIANTE PWM
  digitalWrite(11, 1);
  digitalWrite(10, 0);
}
void der2(int velocidad) { //FUNCIÓN PARA GIRAR EL MOTOR 2 A LA DERECHA
  analogWrite(6, velocidad); //SE HABILITA MEDIANTE PWM
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

  if (distancia > 300 && distancia <= 430) { //OBJETO LEJANO, ENTRE 300 Y 430CM
    izq1(45); der2(45);
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    mensaje = "Nada detectado";
  }
  else if (distancia > 200 && distancia <= 300) { //OBJETO ENTRE 200 y 300CM
    der1(67); der2(67);
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);
    mensaje = "Objeto detectado a: " + String(distancia) + "cm";
  }
  else if (distancia > 100 && distancia <= 200) { //OBJETO ENTRE 100 y 200CM
    der1(135); der2(135);
    digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    mensaje = "Objeto cerca a: " + String(distancia) + "cm";
  }
  else if (distancia > 4 && distancia <= 100) { //OBJETO ENTRE 4 y 100CM
    der1(225); der2(225);
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    mensaje = "Objeto muy cerca a: " + String(distancia) + "cm";
  }
  else if (distancia <= 4) { //OBJETO MUY CERCANO A MENOS DE 4CM
    izq1(112); izq2(112);
    digitalWrite(A0, LOW);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);
    mensaje = "Objeto encontrado";
  }

  Serial.println(mensaje); //IMPRIMIR EN PANTALLA EL MENSAJE CORRESPONDIENTE
  delay(100);
}

