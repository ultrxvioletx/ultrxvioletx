/**
 * ExtraerMayorSubcadena.java clase que, dadas dos cadenas, extrae la mayor subcadena contenida en la otra,
 * se limita únicamente al uso de ciclos y sentencias condicionales,
 * así como métodos length() y charAt() de la clase String y métodos públicos.
 * 
 * @author Andrea Fernanda Rodríguez Rojas.
 * @version Septiembre 2023.
*/

class ExtraerMayorSubcadena {
    public static void main() {
        String A = "Esto es una cadena muy larga";
        String B = "Esto tambien es una cadena";
        
        String salida = "";
        String salida_aux = "";
        
        for (int i = 0; i < A.length(); i++){
            for (int j = 0; j < B.length(); j++){
                salida_aux = salida;
                salida = "";
                int l = j;
                int k = i;
                while (A.charAt(k)==B.charAt(l)){
                    salida += B.charAt(l);
                    l++;
                    k++;
                    
                    if (l==B.length() || k==A.length()) break;
                };
                salida = (salida.length() > salida_aux.length()) ? salida : salida_aux;
            }
        }
        System.out.println(salida);
    }
}