#include <LiquidCrystal_I2C.h> //CARGAMOS LIBRERIA

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  lcd.begin(16, 2); //INICIALIZAMOS LCD CON I2C
}

void loop() {
  //LEEMOS VALORES DE ENTRADA
  float lm35 = analogRead(A0);
  //ESTABLECEMOS UNA RELACIÓN
  int temp = lm35 * 0.49;

  //PINTAMOS EN LA PANTALLA LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura: ");
  lcd.setCursor(0, 1);
  lcd.print(temp);

  delay(100);
}

