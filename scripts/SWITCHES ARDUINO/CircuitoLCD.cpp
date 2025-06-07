#include <LiquidCrystal.h>

const int rs = 7, e = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //PINES DE LIQUID CRYSTAL
LiquidCrystal lcd(rs, e, d4, d5, d6, d7); //DECLARAMOS PINES

char car; //VARIABLE DEL CARACTER INGRESADO
float vel1, vel2; //VELOCIDADES DE LOS MOTORES
bool der, izq; //DIRECCION DE LOS MOTORES
String direccion, motor1, motor2; //CADENAS DE IMPRESION EN LCD

void setup() {
  Serial.begin(9600);

  //LIQUID CRYSTAL
  lcd.begin(16, 2);

  //SENSORES
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  //MOTORES
  for (int i = 8; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }

  //INICIAR EN MOTORES DETENIDOS Y A LA DERECHA
  vel1 = 0; vel2 = 0;
  der = 1; izq = 0;
  direccion = 'D';
}
void loop() {
  if (Serial.available() > 0) { //SENTENCIA PARA SABER SI SE INGRESA UN VALOR
    car = Serial.read(); //SE ACTUALIZA LA NUEVA ENTRADA EN LA VARIABLE

    switch (car) {
      case '1':
        if (vel1 <= 229.5) { //NOS ASEGURAMOS QUE LA VELOCIDAD NO SEA MENOR QUE 0
          vel1 = vel1 + (25.5); //AUMENTAMOS EL 10%
        }
        break;
      case '2':
        if (vel2 <= 229.5) { //NOS ASEGURAMOS QUE LA VELOCIDAD NO SEA MENOR QUE 0
          vel2 = vel2 + (25.5); //AUMENTAMOS EL 10%
        }
        break;
      case '3':
        if (vel1 >= 25.5) { //NOS ASEGURAMOS QUE LA VELOCIDAD NO SEA MAYOR QUE 225
          vel1 = vel1 - (25.5); //QUITAMOS EL 10%
        }
        break;
      case '4':
        if (vel2 >= 25.5) { //NOS ASEGURAMOS QUE LA VELOCIDAD NO SEA MAYOR QUE 225
          vel2 = vel2 - (25.5); //QUITAMOS EL 10%
        }
        break;
    }
  }

  if (car == 'd' || car == 'i') { //CAMBIO DE DIRECCION
    der = (car == 'd') ? 1 : 0; //OPERADOR TERNARIO
    izq = (car == 'd') ? 0 : 1; 

    direccion = (car == 'd') ? 'D' : 'I';
  }
  if (car == 's' || car == 'f') { //VELOCIDAD MÁXIMA O MÍNIMA
    vel1 = (car == 'f') ? 255 : 0;
    vel2 = (car == 'f') ? 255 : 0;
  }

  //MOTOR 1
  analogWrite(11, vel1);
  digitalWrite(13, der);
  digitalWrite(12, izq);
  //MOTOR 2
  analogWrite(10, vel2);
  digitalWrite(9, der);
  digitalWrite(8, izq);
  
  motor1 = (String)(int)(vel1 / 2.55) + "%" + direccion; //CADENA DEL PORCENTAJE MOTOR1
  motor2 = (String)(int)(vel2 / 2.55) + "%" + direccion; //CADENA DEL PORCENTAJE MOTOR2

  lcd.clear(); //LIMPIAR LCD
  
  lcd.setCursor(0, 0); //FILA 0, COLUMNA 0
  lcd.print("Motor1");
  lcd.setCursor(0, 1); //FILA 1, COLUMNA 0
  lcd.print(motor1);

  lcd.setCursor(8, 0); //FILA 0, COLUMNA 8
  lcd.print("Motor2");
  lcd.setCursor(8, 1); //FILA 1, COLUMNA 8
  lcd.print(motor2);

  delay(200); //ESPERAR
}

