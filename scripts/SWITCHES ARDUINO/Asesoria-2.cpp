#include <Keypad.h>

//CONSTANTES
const byte row = 4;
const byte col = 3;

//DEFINICIÓN DE BOTONES
char teclado[row][col] = {
  {'7', '8', '9'},
  {'4', '5', '6'},
  {'1', '2', '3'},
  {'C', '0', '='}
};
//DEFINICIÓN DE PINES
byte rowPin[row] = {A0, A1, A2, A3};
byte colPin[col] = {A4, A5, 13};

//DEFINICIÓN DE COMPONENTES
Keypad kpad = Keypad( makeKeymap(teclado), rowPin, colPin, row, col);

//DEFINION DE PINES LED
#define l1 9
#define l2 8
#define l3 7
#define l4 6
#define l5 5
#define l6 4
#define l7 3
#define l8 2


int tiempo = 60;
int a, num;
char key;

void setup() {
  pinMode(10, INPUT);
  for (int i = 2; i <= 9; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600); //recibir información de entrada
}

void leds(int pin, bool val);
void parimpar(int pin, bool val);

void loop() {
  a = digitalRead(10);

  key = kpad.getKey();
  if (key != NO_KEY) { //SENTENCIA PARA SABER SI SE INGRESA UN VALOR
    num = key - '0'; //SE ACTUALIZA LA NUEVA ENTRADA EN LA VARIABLE
    leds(0, 0);

    if (a == 0) {
      switch (num) {
        case 0:
          //APAGAR TODOS LOS LEDS
          leds(0, 0);
          break;
        case 1:
          //ENCENDER LED 1
          leds(l1, 0);
          break;
        case 2:
          //ENCENDER LED 2
          leds(l2, 0);
          break;
        case 3:
          //ENCENDER LED 3
          leds(l3, 0);
          break;
        case 4:
          //ENCENDER LED 4
          leds(l4, 0);
          break;
        case 5:
          //ENCENDER LED 5
          leds(l5, 0);
          break;
        case 6:
          //ENCENDER LED 6
          leds(l6, 0);
          break;
        case 7:
          //ENCENDER LED 7
          leds(l7, 0);
          break;
        case 8:
          //ENCENDER LED 8
          leds(l8, 0);
          break;
        case 9:
          //ENCENDER TODOS LOS LEDS
          leds(0, 1);
          break;
        default:
          break;
      }
    } else {
      switch (num) {
        case 0:
          leds(0, 0);
          break;
        case 1:
          //AUTO INCREIBLE
          for (int i = 9; i >= 2; i--) {
            digitalWrite(i, HIGH);
            delay(tiempo);
            digitalWrite(i, LOW);
          }
          for (int i = 2; i <= 9; i++) {
            digitalWrite(i, HIGH);
            delay(tiempo);
            digitalWrite(i, LOW);
          }
          break;
        case 2:
          //ENCEDER LEDS
          leds(9, 1);
          delay(2000); //ESPERAR

          //APAGAR LEDS
          leds(0, 0);
          delay(1000); //ESPERAR
          break;
        case 3:
          //ENDENDER IMPARES
          parimpar(9, 1);
          break;
        case 4:
          //ENCENDER PARES
          parimpar(8, 1);
          break;
        case 5:
          //ENDENDER IMPARES
          parimpar(9, 1);
          delay(1000); //ESPERAR
          //APAGAR IMPARES
          parimpar(9, 0);
          //ENCENDER PARES
          parimpar(8, 1);
          delay(1000); //ESPERAR
          //APAGAR PARES
          parimpar(8, 0);
          break;
        default:
          break;
      }
    }
  }
}

void leds(int pin, bool val) {
  for (int i = 2; i <= 9; i++) {
    digitalWrite(i, val);
  }
  digitalWrite(pin, 1);
}
void parimpar(int pin, bool val) {
  for (int i = pin; i >= 2; i = i - 2) {
    digitalWrite(i, val);
  }
}

