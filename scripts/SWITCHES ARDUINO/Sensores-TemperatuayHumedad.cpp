//CARGAMOS LIBRERÍAS
#include <DHT.h>
#include <Wire.h>

DHT dht(A0, DHT11); //DEFINIMOS SENSOR HUMEDAD

//LEDS COLORES
int calentador = 2, amarillo = 3, verde = 4;

void setup() {
  //SENSOR DE HUMEDAD (Y TEMPERATURA)
  dht.begin();

  //SENSOR DE TEMPERATURA
  Wire.begin();
  Wire.beginTransmission(0x48);
  Wire.write(0xAC);
  Wire.write(0x02);
  Wire.beginTransmission(0x48);
  Wire.write(0xEE);
  Wire.endTransmission();

  //MOTORES
  for (int i = 8; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  //LEDS
  for (int i = 2; i <= 4; i++) {
    pinMode(i,  OUTPUT);
  }
}

/**************FUNCIONES*************/
void bomba(bool on) {
  digitalWrite(11, on);
  digitalWrite(13, 1);
  digitalWrite(12, 0);
}
void ventilador(bool on) {
  digitalWrite(10, on);
  digitalWrite(9, 1);
  digitalWrite(8, 0);
}
void temperatura(int temp) {
  bool v, c;
  if (temp < 23) {
    v = 0; c = 1;
  }
  else if (temp > 25) {
    v = 1; c = 0;
  }
  else {
    v = 0; c = 0;
  }

  ventilador(v);//Encender/apagar motor de ventilador
  digitalWrite(calentador, c); //Encender/apagar led rojo
}
void humedad(int hum) {
  bool b, v, a;
  if (hum > 70) {
    b = 0; v = 0; a = 1;
  }
  else if (hum < 70) {
    b = 1; v = 0; a = 0;
  }
  else if (hum = 70) {
    b = 0; v = 1; a = 0;
  }

  bomba(b); //Encender/apagar motor de bomba
  digitalWrite(verde, v); //Encender/apagar led verde
  digitalWrite(amarillo, a); //Encender/apagar led amarillo
}
/************************************/

void loop() {
  //COMENZAMOS TRANSMISION
  Wire.beginTransmission(0x48);
  Wire.write(0xAA);
  Wire.endTransmission();
  Wire.requestFrom(0x48, 1);

  //GUARDAMOS VALORES DE TEMP Y HUMEDAD EN VARIABLES
  int temp = Wire.read();
  int hum = dht.readHumidity();

  //FUNCIONES QUE ESTABLECEN LAS CONDICIONES
  temperatura(temp);
  humedad(hum);

  delay(500);
}

