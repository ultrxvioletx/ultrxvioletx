#include <LiquidCrystal.h>

const int rs = 7, e = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //PINES DE LIQUID CRYSTAL
LiquidCrystal lcd(rs, e, d4, d5, d6, d7); //DECLARAMOS PINES

int sen1, sen2, sen3; //VARIABLES DE VALORES SENSORES
String mensaje; //VARIABLE DEL MENSAJE QUE SE MOSTRARÁ

void setup() {
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
}

char color(int valor) { //FUNCIÓN PARA DEFINIR EL COLOR
  if (valor <= 700) { //COLOR NEGRO
    return 'n';
  } else if (700 < valor) { //COLOR BLANCO
    return 'b';
  }
}
void avanzar(){
  //MOTOR 1
  digitalWrite(11, 1); //ACTIVAR MOTOR1
  digitalWrite(13, 1); //DERECHA
  digitalWrite(12, 0);
  //MOTOR 2
  digitalWrite(10, 1); //ACTIVAR MOTOR2
  digitalWrite(9, 1); //DERECHA
  digitalWrite(8, 0);
}
void detener(){
  //MOTOR 1
  digitalWrite(11, 0); //DESACTIVAR MOTOR1
  //MOTOR 2
  digitalWrite(10, 0); //DESACTIVAR MOTOR2
}
void giroD(){
  //MOTOR 1
  digitalWrite(11, 1); //ACTIVAR MOTOR1
  digitalWrite(13, 1); //DERECHA
  digitalWrite(12, 0);
  //MOTOR 2
  digitalWrite(10, 1); //ACTIVAR MOTOR2
  digitalWrite(9, 0);
  digitalWrite(8, 1); //IZQUIERDA
}
void giroI(){
  //MOTOR 1
  digitalWrite(11, 1); //ACTIVAR MOTOR1
  digitalWrite(13, 0);
  digitalWrite(12, 1); //IZQUIERDA
  //MOTOR 2
  digitalWrite(10, 1); //ACTIVAR MOTOR2
  digitalWrite(9, 1); //DERECHA
  digitalWrite(8, 0);
}
void loop() {
  //DEFINIR LOS VALORES RECIBIDOS DE LOS SENSORES
  sen1 = analogRead(A0);
  sen2 = analogRead(A1);
  sen3 = analogRead(A2);

  lcd.clear(); //LIMPIAR LCD

  if (color(sen1) == 'n' && color(sen2) == 'n' && color(sen3) == 'n'){ //NEGRO NEGRO NEGRO
    detener();
    mensaje = "Detenido";
  }
  else if (color(sen1) == 'n' && color(sen2) == 'b' && color(sen3) == 'n'){ //NEGRO BLANCO NEGRO
    avanzar();
    mensaje = "Avanza";
  }
  else if (color(sen1) == 'n' && color(sen2) == 'n' && color(sen3) == 'b'){ //NEGRO NEGRO BLANCO
    giroD();
    mensaje = "Derecha";
  }
  else if (color(sen1) == 'b' && color(sen2) == 'n' && color(sen3) == 'n'){ //BLANCO NEGRO NEGRO
    giroI();
    mensaje = "Izquierda";
  }
  else if ((color(sen1) == 'n' && color(sen2) == 'b' && color(sen3) == 'b') //NEGRO BLANCO BLANCO
  || (color(sen1) == 'n' && color(sen2) == 'b' && color(sen3) == 'b') //NEGRO BLANCO BLANCO
  || (color(sen1) == 'b' && color(sen2) == 'n' && color(sen3) == 'b') //BLANCO NEGRO BLANCO
  || (color(sen1) == 'b' && color(sen2) == 'b' && color(sen3) == 'n') //BLANCO BLANCO NEGRO
  || (color(sen1) == 'b' && color(sen2) == 'b' && color(sen3) == 'b')){ //BLANCO BLANCO BLANCO
    detener();
    mensaje = "No aplica";
  }

  lcd.setCursor(0,0); //COLOCAR CURSOR FILA 0, COLUMNA 0
  lcd.print(mensaje); //PINTAR MENSAJE EN LCD
  delay(200); //ESPERAR
}

