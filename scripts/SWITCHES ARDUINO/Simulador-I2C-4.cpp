#include <LiquidCrystal_I2C.h> //cargamos librería

LiquidCrystal_I2C lcd1(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LiquidCrystal_I2C lcd2(0x26, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int pot[4];

void setup() {
  //PINES DE ENTRADA POTENCIOMETROS
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  //INICIALIZAMOS LCDS
  lcd1.begin(16, 2);
  lcd2.begin(16, 2);

  //COLOCAMOS ETIQUETAS DE POTENCIOMETROS
  lcd1.setCursor(0, 0);
  lcd1.print("POT1: ");
  lcd1.setCursor(0, 1);
  lcd1.print("POT2: ");

  lcd2.setCursor(0, 0);
  lcd2.print("POT3: ");
  lcd2.setCursor(0, 1);
  lcd2.print("POT4: ");
}

void loop() {
  //GUARDAMOS VALORES DE POTENCIOMETROS EN UN ARREGLO
  pot[0] = analogRead(A0);
  pot[1] = analogRead(A1);
  pot[2] = analogRead(A2);
  pot[3] = analogRead(A3);

  //MOSTRAMOS EN PANTALLA LOS VALORES GUARDADOS EN EL ARREGLO
  lcd1.setCursor(7, 0);
  lcd1.print(pot[0]);
  lcd1.setCursor(7, 1);
  lcd1.print(pot[1]);

  lcd2.setCursor(7, 0);
  lcd2.print(pot[2]);
  lcd2.setCursor(7, 1);
  lcd2.print(pot[3]);
}

