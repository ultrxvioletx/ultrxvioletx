#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//DEFINICION DE VARIABLES
int index = 0, row = 20;
String mensaje = "Ya lo ves, la vida es asi. Tu te vas y yo me quedo aqui, llovera y ya no sere tuya, sere la gata bajo la lluvia y maullare por ti.";

void setup() {
  lcd.begin(20, 4); //INICIA LIQUID CRYSTAL
}

void loop() {
  for (int j = 0; j < 4; j++) { //CICLO FOR QUE CUENTA RENGLONES DEL 0 AL 3
    lcd.setCursor(0, j); //SITÚA EN LOS RENGLONES CORRESPONDIENTES

    char arr[21]; //INICIALIZAMOS ARRAY DONDE SE GUARDARÁN CARACTERES
    //CORTAMOS TEXTO EN PARTES DE CIERTO NUMERO DE CARACTERES, EN ESTE CASO, 20
    String msj = mensaje.substring(index * row, index * row + row + 1);
    msj.toCharArray(arr, 21); //CONVERTIMOS TEXTO EN ARRAY

    for (int i = 0; i < row; i++) { //CICLO FOR QUE ITERA CARACTERES POR RENGLÓN
      lcd.print(arr[i]); //IMPRIMIMOS EN PANTALLA LCD
      if (arr[i] == ' ') delay(400); //CADA QUE ENCUENTRE UN ESPACIO, ESPERA UN MOMENTO
                                      //PARA DAR ILUSIÓN QUE COLOCA PALABRA POR PALABRA
    }
    index++;
  }
  lcd.clear(); //LIMPIA PANTALLA CUANDO ESTÁ LLENA
  //CUANDO YA SE IMPRIMIÓ TODO EL TEXTO, INICIA DE NUEVO EL CONTADOR INDEX
  index = (index * row) >= mensaje.length() ? 0 : index;
}

