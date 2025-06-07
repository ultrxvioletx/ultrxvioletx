int tiempo = 60; //declarar variabl de tiempo

void setup() {
  pinMode(13, OUTPUT); //declarar al pin 13 como salida
  pinMode(12, OUTPUT); //declarar al pin 12 como salida
  pinMode(11, OUTPUT); //declarar al pin 11 como salida
  pinMode(10, OUTPUT); //declarar al pin 10 como salida
  pinMode(9, OUTPUT); //declarar al pin 9 como salida
  pinMode(8, OUTPUT); //declarar al pin 8 como salida
}

void loop() {
  for (int i = 13; i >= 8; i = i - 1) { //ciclo for que va desde 13 hasta 8
    digitalWrite(i, HIGH); //encender led
    delay(tiempo); //eperar
    digitalWrite(i, LOW); //apagar led
  }
  for (int i = 8; i <= 13; i = i + 1) { //ciclo for que va desde 8 hasta 13
    digitalWrite(i, HIGH); //encender led
    delay(tiempo); //esperar
    digitalWrite(i, LOW); //apagar led
  }
}
