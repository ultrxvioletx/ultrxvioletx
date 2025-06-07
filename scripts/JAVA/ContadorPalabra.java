/**
 * ContadorPalabra.java clase que determina el número de veces que aparece la palabra WALLY
 * en otra cadena dada, aunque esté cortada o separada pero sus letras correspondientes
 * tengan siempre el orden correcto. Este código se puede generalizar a cualquier palabra.
 * Se limita únicamente al uso de ciclos y sentencias condicionales,
 * así como métodos length() y charAt() de la clase String y métodos públicos.
 * 
 * @author Andrea Fernanda Rodríguez Rojas.
 * @version Octubre 2023.
*/

public class ContadorPalabra{
    public static void main(String[] args){
        String cadena = "QWEWRTWERGBNAMMTHNLKLYUHLMXCNMXCNBYWALLYWWALAGGGWALXCBBVLJGDGDKICKKCKY"; //Cadena propuesta
        String palabra = "WALLY"; //Cadena que buscamos
        
        String extracto = ""; //Cadena que va a extraer los caracteres 'W' 'A' 'L' 'Y'
        for (int i = 0; i < cadena.length(); i++){ 
            if (cadena.charAt(i) == 'W'
            || cadena.charAt(i) == 'A'
            || cadena.charAt(i) == 'L'
            || cadena.charAt(i) == 'Y'){
                extracto += cadena.charAt(i);
            }
        }
        // System.out.println(extracto);
        int contador = 0; //Contador que enumera la cantidad de veces que aparece WALLY en la cadena extraída
        for (int i = 0; i < extracto.length(); i++){
            if (extracto.charAt(i) == 'W' && i < extracto.length()-4){
                boolean flag = true; //Bandera que indica si la palabra WALLY apareció de manera ininterrumpida
                for (int j = 0; j < palabra.length(); j++){
                    if(!(palabra.charAt(j) == extracto.charAt(j+i))){ //Si algun caracter falla, la bandera cambia a false
                        flag = false;
                    }
                }
                if (flag) contador++; //Si la bandera no cambió a false, la palabra WALLY apareció y se aumenta el contador en uno
            }
        }
        System.out.println("La palabra WALLY aparece "+contador+" veces en la cadena "+cadena);
    }
}