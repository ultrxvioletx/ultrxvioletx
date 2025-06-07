#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

//CONSTANTES
const byte row = 4;
const byte col = 4;
//DEFINICIÓN DE BOTONES
char teclado[row][col] = {
  {'7', '8', '9', '/'},
  {'4', '5', '6', '*'},
  {'1', '2', '3', '-'},
  {'C', '0', '=', '+'}
};
//DEFINICIÓN DE PINES
byte rowPin[row] = {A0, A1, A2, A3};
byte colPin[col] = {7, 6, 5, 4};

//DEFINICIÓN DE COMPONENTES
Keypad myKpad = Keypad( makeKeymap(teclado), rowPin, colPin, row, col);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//VARIABLES
int vel1, vel2;
bool der1, der2;
String porcentaje, direccion1, direccion2;
char key;

void setup() {
  lcd.begin(20, 4);

  //MOTORES
  for (int i = 8; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  key = myKpad.getKey();

  if (key != NO_KEY) {
    lcd.clear();
    Serial.println(key);

    switch (key) {
      case 'C':
        vel1 = 25; vel2 = 25;
        der1 = 1; der2 = 0;
        porcentaje = "10%";
        break;
      case '0':
        vel1 = 0; vel2 = 0;
        porcentaje = "0%";
        break;
      case '1':
        vel1 = 51; vel2 = 51;
        porcentaje = "20%";
        break;
      case '2':
        vel1 = 76; vel2 = 76;
        porcentaje = "30%";
        break;
      case '3':
        vel1 = 102; vel2 = 102;
        porcentaje = "40%";
        break;
      case '4':
        vel1 = 127; vel2 = 127;
        porcentaje = "50%";
        break;
      case '5':
        vel1 = 153; vel2 = 153;
        porcentaje = "60%";
        break;
      case '6':
        vel1 = 178; vel2 = 178;
        porcentaje = "70%";
        break;
      case '7':
        vel1 = 204; vel2 = 204;
        porcentaje = "80%";
        break;
      case '8':
        vel1 = 229; vel2 = 229;
        porcentaje = "90%";
        break;
      case '9':
        vel1 = 225; vel2 = 225;
        porcentaje = "100%";
        break;
      case '/':
        der1 = !der1;
        break;
      case '*':
        der2 = !der2;
        break;
      case '+':
        der1 = 1; der2 = 1;
        break;
      case '-':
        der1 = 0; der2 = 0;
        break;
      case '=':
        vel1 = 225; vel2 = 225;
        der1 = 1; der2 = 0;
        porcentaje = "100%";
        break;
    }

    
    direccion1 = (der1 == 1) ? "Derecha" : "Izquierda";
    direccion2 = (der2 == 1) ? "Derecha" : "Izquierda";

    lcd.setCursor(0, 0);
    lcd.print(porcentaje);
    lcd.setCursor(0, 1);
    lcd.print(direccion1);

    lcd.setCursor(0, 2);
    lcd.print(porcentaje);
    lcd.setCursor(0, 3);
    lcd.print(direccion2);
  }

  //MOTOR1
  analogWrite(11, vel1); //SE HABILITA MEDIANTE PWM
  digitalWrite(13, der1);
  digitalWrite(12, !der1);
  //MOTOR2
  analogWrite(10, vel2); //SE HABILITA MEDIANTE PWM
  digitalWrite(9, der2);
  digitalWrite(8, !der2);
}

