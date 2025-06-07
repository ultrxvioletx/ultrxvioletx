void setup() {
  //MOTOR1
  pinMode(13, OUTPUT); //IN1
  pinMode(12, OUTPUT); //IN2
  pinMode(11, OUTPUT); //EN1

  //MOTOR2
  pinMode(10, OUTPUT); //EN2
  pinMode(9, OUTPUT); //IN3
  pinMode(8, OUTPUT); //IN4
}

void Avanzar(){
  //MOTOR1
  digitalWrite(11,1); //Se habilita el motor 1
  digitalWrite(13,1); //Dirección levógira
  digitalWrite(12,0);
  //MOTOR2
  digitalWrite(10,1); //Se habilita el motor 2
  digitalWrite(9,1); //Dirección levógira
  digitalWrite(8,0);
}

void Retroceder(){
  //MOTOR1
  digitalWrite(11,1); //Se habilita el motor 1
  digitalWrite(13,0);
  digitalWrite(12,1); //Dirección dextrógira
  //MOTOR2
  digitalWrite(10,1); //Se habilita el motor 2
  digitalWrite(9,0);
  digitalWrite(8,1); //Dirección dextrógira
}

void GiroDerecha(){
  //MOTOR1
  digitalWrite(11,1); //Se habilita el motor 1
  digitalWrite(13,1); //Dirección levógira
  digitalWrite(12,0);
  //MOTOR2
  digitalWrite(10,1); //Se habilita el motor 2
  digitalWrite(9,0);
  digitalWrite(8,1); //Dirección dextrógira
}

void GiroIzquierda(){
  //MOTOR1
  digitalWrite(11,1); //Se habilita el motor 1
  digitalWrite(13,0);
  digitalWrite(12,1); //Dirección dextrógira
  //MOTOR2
  digitalWrite(10,1); //Se habilita el motor 2
  digitalWrite(9,1); //Dirección levógira
  digitalWrite(8,0);
}
void loop() {
  Avanzar();
  delay(3000);

  Retroceder();
  delay(3000);

  GiroDerecha();
  delay(3000);

  GiroIzquierda();
  delay(3000);
}

