int LED1 = 13;
int LED2 = 12;
int LED3 = 11;
int LED4 = 10;
int LED5 = 9;
int LED6 = 8;
int LED7 = 7;
int LED8 = 6;

int tiempo = 60;

int a, num;

void setup() {
  pinMode(A5, INPUT);
  for (int j = 6; j <= 13; j++) {
    pinMode(j, OUTPUT);
  }
  Serial.begin(9600); //recibir información de entrada
}

void loop() {
  a = digitalRead(A5);

  if (Serial.available() > 0) { //SENTENCIA PARA SABER SI SE INGRESA UN VALOR
    num = Serial.read() - '0'; //SE ACTUALIZA LA NUEVA ENTRADA EN LA VARIABLE
    //APAGAR TODOS LOS LEDS
    for (int i = 6; i <= 13; i++) {
      digitalWrite(i, LOW);
    }
  }

  if (a == 0) {
    switch (num) {
      case 0:
        //APAGAR TODOS LOS LEDS
        for (int i = 6; i <= 13; i++) {
          digitalWrite(i, LOW);
        }
        break;
      case 1:
        //ENCENDER LED 1
        digitalWrite(LED1, HIGH);
        break;
      case 2:
        //ENCENDER LED 2
        digitalWrite(LED2, HIGH);
        break;
      case 3:
        //ENCENDER LED 3
        digitalWrite(LED3, HIGH);
        break;
      case 4:
        //ENCENDER LED 4
        digitalWrite(LED4, HIGH);
        break;
      case 5:
        //ENCENDER LED 5
        digitalWrite(LED5, HIGH);
        break;
      case 6:
        //ENCENDER LED 6
        digitalWrite(LED6, HIGH);
        break;
      case 7:
        //ENCENDER LED 7
        digitalWrite(LED7, HIGH);
        break;
      case 8:
        //ENCENDER LED 8
        digitalWrite(LED8, HIGH);
        break;
      case 9:
        //ENCENDER TODOS LOS LEDS
        for (int i = 6; i <= 13; i++) {
          digitalWrite(i, HIGH);
        }
        break;
    }
  } else {
    switch (num) {
      case 0:
        //APAGAR TODOS LOS LEDS
        for (int i = 6; i <= 13; i++) {
          digitalWrite(i, LOW);
        }
        break;
      case 1:
        //AUTO INCREIBLE
        for (int i = 13; i >= 6; i--) {
          digitalWrite(i, HIGH);
          delay(tiempo);
          digitalWrite(i, LOW);
        }
        for (int i = 6; i <= 13; i++) {
          digitalWrite(i, HIGH);
          delay(tiempo);
          digitalWrite(i, LOW);
        }
        break;
      case 2:
        //ENCENDER LEDS
        for (int i = 6; i <= 13; i++) {
          digitalWrite(i, HIGH);
        }
        delay(2000); //ESPERAR
        
        //APAGAR LEDS
        for (int i = 6; i <= 13; i++) {
          digitalWrite(i, LOW);
        }
        delay(1000); //ESPERAR
        break;
      case 3:
        //ENDENDER IMPARES
        for (int i = 13; i > 6; i = i - 2) {
          digitalWrite(i, HIGH);
        }
        break;
      case 4:
        //ENCENDER PARES
        for (int i = 12; i >= 6; i = i - 2) {
          digitalWrite(i, HIGH);
        }
        break;
      case 5:
        //ENDENDER IMPARES
        for (int i = 13; i > 6; i = i - 2) {
          digitalWrite(i, HIGH);
        }
        delay(1000); //ESPERAR
        //APAGAR IMPARES
        for (int i = 13; i > 6; i = i - 2) {
          digitalWrite(i, LOW);
        }
        //ENCENDER PARES
        for (int i = 12; i >= 6; i = i - 2) {
          digitalWrite(i, HIGH);
        }
        delay(1000); //ESPERAR
        //APAGAR PARES
        for (int i = 12; i >= 6; i = i - 2) {
          digitalWrite(i, LOW);
        }
        break;
    }
  }
}

