#include <Keypad.h>

//VARIABLES
int array1[3][3], array2[3][3], res[3][3], det; //variables para las matrices a operar y el resultado

void setup() {
  Serial.begin(9600); //Iniciamos la terminal
}

/* FUNCIONES */
int IntroducirArray(int arr[3][3]) {  //Función para guardar valores en un array
  for (int i = 0; i < 3; i++) {       //Recorre las filas de la matriz
    for (int j = 0; j < 3; j++) {     //Recorre las columnas de la matriz
      while (Serial.available() <= 0) //While de espera para la recepción de datos
        delay(50);
      int val = Serial.read() - '0';  //Variable temporal para valor introducido
      arr[i][j] = val;                //Introdicimos valor en el lugar de la matriz correspondiente
      Serial.print(val);              //Imprimir valor para visualizar la matriz
      Serial.print(" ");
    }
    Serial.println("");
  }
  return arr;                         //Array que devuelve la función
}
/*******************/

void loop() {
  Serial.println("Introduzca la matriz");
  IntroducirArray(array1);            //Llamamos a la funcion para introducir matrices

  Serial.println("Suma +");
  Serial.println("Resta -");
  Serial.println("Multiplicacion *");
  Serial.println("Determinante d");
  Serial.println("");

  while (Serial.available() <= 0)     //While de espera para la recepción de datos
    delay(50);
  char key = Serial.read();           //Variable para guardar key ingresada
  Serial.println(key);                //Imprimir key nomás para verificar
  
  if (key == 'd') {
    det = (array1[0][0] * (array1[1][1] * array1[2][2] - array1[1][2] * array1[2][1]))
          - (array1[0][1] * (array1[1][0] * array1[2][2] - array1[1][2] * array1[2][0]))
          + (array1[0][2] * (array1[1][0] * array1[2][1] - array1[1][1] * array1[2][0]));
          //Formula para calcular la determinante de una matriz

    Serial.print("El determinante es: ");
    Serial.println(det);              //Imprimimos resultado
    Serial.println("");
  }
  else if (key == '*' || key == '-' || key == '+') {
    Serial.println("Introduzca otra matriz");

    IntroducirArray(array2);          //Si es suma, resta o multiplicación se pide otra matriz

    switch (key) {
      case '+':
        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            res[i][j] = array1[i][j] + array2[i][j]; //Se suma entrada por entrada
          }
        }
        break;
      case '-':
        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            res[i][j] = array1[i][j] - array2[i][j]; //Se resta entrada por entrada
          }
        }
        break;
      case '*':
        for (int a = 0; a < 3; a++) {   //Recorre las columnas de la segunda matriz
          for (int i = 0; i < 3; i++) { //Recorre las filas de la primera matriz
            int suma = 0;               //Variable auxiliar para guardar la suma
            for (int j = 0; j < 3; j++) { //Recorre las columnas de la primera matriz
              suma += array1[i][j] * array2[j][a]; //Se multiplican las entradas fila x columna
                                                   //y se van sumando (producto punto)
            }
            res[i][a] = suma; //Se guarda el valor en la entrada correspondiente de la matriz resultante
          }
        }
        break;
    }

    Serial.println("El resultado es:");
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        Serial.print(res[i][j]); //Imprimimos las entradas de la matriz resultante
        Serial.print(" ");
      }
      Serial.println("");
    }
    Serial.println("");
  }
  else {
    //Evita introducir caracter que no sea para las operaciones establecidas.
    Serial.println("Entrada no valida. Se reinicia programa.");
    Serial.println("");
  }
}

