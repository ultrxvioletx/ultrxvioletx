#include <LiquidCrystal.h> //librería pantalla liquid
#include <Keypad.h> //librería teclado keypad

//CONSTANTES
const byte row = 4;
const byte col = 6;
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

//DEFINICIÓN DE BOTONES
char teclado[row][col] = {
  {'C', '7', '8', '9', '*', '/'},
  {'P', '4', '5', '6', '-', 'D'},
  {'%', '1', '2', '3', '+', 'm'},
  {'S', '0', '.', '=', '+', 'M'}
};
//DEFINICIÓN DE PINES
byte rowPin[row] = {13, 12, 11, 10};
byte colPin[col] = {A5, A4, A3, A2, A1, A0};

//DEFINICIÓN DE COMPONENTES
Keypad kpad = Keypad( makeKeymap(teclado), rowPin, colPin, row, col);
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//VARIABLES
float num1, num2, num;
char key, action;
bool result = false;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void KeyButton(); //función que determina las acciones de acuerdo a las teclas oprimidas
void Calculate(); //función que realiza las operaciones

void loop() {
  key = kpad.getKey(); //guarda el valor de la tecla seleccionada

  if (key != NO_KEY) { //realiza el proceso cuando se oprime una tecla
    KeyButton();
    Serial.println(key); //imprime en consola

    if (result == true) {
      Calculate();
    }
  }
  delay(10); //espera poquito
}

void KeyButton() {
  if (key == 'C') { //limpia los valores y la pantalla
    lcd.clear();
    num = num1 = num2 = 0;
    result = false;
  }
  else if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == '7' || key == '8' || key == '9' || key == '0') {
    lcd.print(key); //muestra los números ingresados
    (num == 0) ? (num = key - '0') : (num = (num * 10) + (key - '0')); //nos permite operar con números mayores que 9,
                                                                      //ubicando su valor en decenas, centenas, etc.
    Serial.println(num); //vemos en consola los números ingresados
  }
  else if (key == '+' || key == '-' || key == '/' || key == '*' || key == '+' || key == '%' || key == 'S') {
    if (key == 'S') { //cuando se oprime el botón de raíz
      lcd.print(" raiz");
      result = true; //activamos la variable "result" para evitar ingresar un segundo valor
    } else {
      lcd.print(key);
    }
    num1 = num; //guardamos en un variable el valor del primer operando
    num = 0; //reseteamos la variable temporal

    action = key;
  }
  else if (key == '=') { //cuando se oprime el botón de igual
    num2 = num; //guardamos en una variable el valor del segundo operando
    result = true; //activamos la variable "result" para relizar los cálculos e imprimirlos
  }
}
void Calculate() {
  switch (action) {
    case '+': //SUMA
      num = num1 + num2;
      break;
    case '-': //RESTA
      num = num1 - num2;
      break;
    case '*': //MULTIPLICACIÓN
      num = num1 * num2;
      break;
    case '/': //DIVISIÓN
      num = num1 / num2;
      break;
    case '%': //PORCENTAJE
      num = num1 * (num2 / 100);
      break;
    case 'S': //RAÍZ
      num = sqrt(num1);
      break;
    default:
      break;
  }

  lcd.clear(); //limpiamos pantalla
  lcd.setCursor(0, 0);
  lcd.print(num1);
  if (action == 'S') { //en caso de ser una raíz, solo se imprime el primer operando
    lcd.print(" raiz");
  } else {
    lcd.print(action); //caso contrario, se imprime el operador
    lcd.print(num2); //y el segundo operando
  }

  if (result == true) {
    lcd.setCursor(0, 1);
    lcd.print("=");
    lcd.print(num); //se imprime el resultado de la operación

    num1 = num; //se guarda el resultado de la operación para volver a operarlo si se desea
    result = false; //desactivamos la variable "result" para evitar que opere infinitamente
  }
}


