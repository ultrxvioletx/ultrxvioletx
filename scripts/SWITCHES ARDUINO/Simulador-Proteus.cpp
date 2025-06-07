int tiempo=500;
void setup() {
  pinMode(A0,INPUT); //definir pin como entrada (no es necesario en este caso)
  pinMode(A1,INPUT); //definir pin como entrada (no es necesario en este caso)
  for(int j=6; j<=13; j++){ //recorrer pines del 6 al 13
    pinMode(j,OUTPUT); //definir pines como salidas
  }
  Serial.begin(9600); //recibir información de entrada
}

void loop() {
  bool a = digitalRead(A0), b = digitalRead(A1); //definir variables de valores de entrada
  if(a==0 && b==0){ //ambos switch abiertos
    for(int i=13; i>=6; i--){ //recorrer pines del 13 a 6
      digitalWrite(i,0); //apagar todos los leds
    }
  }
  if(a==1 && b==0){ //switch a cerrado y b abierto
    for(int i=13; i>=6; i--){ //recorrer pines del 13 a 6
      digitalWrite(i,1); //enceder leds
      delay(tiempo); //esperar
      digitalWrite(i,0); //apagar leds
    }
  }
  if(a==0 && b==1){ //switch a abierto y b cerrado
    for(int i=6; i<=13; i++){ //recorrer pines del 6 al 13
      digitalWrite(i,1); //encender leds
      delay(tiempo); //esperar
      digitalWrite(i,0); //apagar leds
    }
  }
  if(a==1 && b==1){ //ambos switch cerrados
    for(int i=0; i<8; i++){ //recorrer variable i del 0 a 7 (total-1 de pines de salida)
      //se le suma el valor de i al primer pin y se le resta al último
      //para que ambos en las orillas se enciendan al mismo tiempo y recorran hacia adentro
      digitalWrite(6+i,1); 
      digitalWrite(13-i,1);
      delay(tiempo);
      digitalWrite(6+i,0);
      digitalWrite(13-i,0);
    }
  }
}

