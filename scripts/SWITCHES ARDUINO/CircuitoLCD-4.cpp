#include <LiquidCrystal.h>

const int rs = 7, e = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, e, d4, d5, d6, d7);

String mensaje = "Este es un mensaje largo de mas de 16 caracteres.";
int velocidad = 100;

void setup() {
  lcd.begin(16, 2);
}

void loop() {
  int a = mensaje.length();
  a = a * (-1) + 16;
  for (int i = 15; i >= a; i--) {
    lcd.clear();
    lcd.setCursor(i, 0);
    lcd.print(mensaje);

    delay(velocidad);
  }
}

