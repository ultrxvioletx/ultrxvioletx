import java.util.Scanner;
import java.util.Random;

/**
 * ElAhorcado.java clase que implementa juego de El Ahorcado en interfaz de consola,
 * se ilustra uso del Switch y While para crear un menú de opciones
 * y se limita únicamente al uso de ciclos y sentencias condicionales,
 * así como métodos length() y charAt() de la clase String y métodos públicos.
 * 
 * @author Andrea Fernanda Rodríguez Rojas.
 * @version Septiembre 2023.
*/

public class Hangman {
    // METODOS AUXILIARES

    // Revisa si una letra es válida o no de acuerdo a un estandar de mayusculas,
    // de no serlo devuelve false
    public static boolean LetraValida(char letra){
        String letras_validas = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        boolean valida = false;
        for (int i = 0; i < letras_validas.length(); i++){
            char letra_i = letras_validas.charAt(i);
            if (letra == letra_i){
                valida = true;
                break;
            }
        }
        return valida;
    }
    // Devuelve los caracteres unicos de una cadena, sin contar espacios
    public static int LetrasUnicas(String pelicula){
        String letras_unicas = "";
        letras_unicas = letras_unicas + pelicula.charAt(0);
        for (int i = 0; i < pelicula.length(); i++){
            char pelicula_i = pelicula.charAt(i);
            boolean is_contenida = false;
            int j = 0;

            while(!is_contenida && j < letras_unicas.length()){
                char letra_j = letras_unicas.charAt(j);
                if (pelicula_i == letra_j) is_contenida = true;
                j++;
            }
            if (!is_contenida && pelicula_i != ' ') letras_unicas = letras_unicas + pelicula_i;
        }
        return letras_unicas.length();
    }
    // Crea rayas y espacios de acuerdo al nombre de la pelicula
    public static String OcultarPelicula(String pelicula){
        String rayitas = "";
        for (int i = 0; i < pelicula.length(); i++){
            char pelicula_i = pelicula.charAt(i);
            if (pelicula_i == ' ') rayitas = rayitas + "  ";
            else rayitas = rayitas + "_ ";
        }
        return rayitas;
    }
    
    // MAIN
    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);
        Random rand = new Random();
        String nombre = "";
        int opcion;
        int victorias = 0, derrotas = 0; // contadores para estadísticas

        // Ingresa nombre del jugador
        System.out.print("Ingresa tu nombre: ");
        nombre = scanner.nextLine();
        System.out.println("\nBienvenido, " + nombre);

        // Menú principal
        do{
            System.out.println();
            System.out.println("1. Jugar El Ahorcado");
            System.out.println("2. Ver estadisticas");
            System.out.println("3. Salir");

            System.out.print("Seleccione una opción: ");
            opcion = scanner.nextInt();

            switch(opcion){
                case 1: // 1. Jugar El Ahorcado
                    int rand_int = rand.nextInt(9);
                    int errores = 0, aciertos = 0; // contadores para ganar o perder
                    String pelicula = "", partida = "", ahorcado = ""; // variables de impresión en pantalla

                    switch(rand_int){ // Repertorio nombres de películas
                        case 0:
                            pelicula = "STAR WARS";
                            break;
                        case 1:
                            pelicula = "BLADE RUNNER";
                            break;
                        case 2:
                            pelicula = "AFTERSUN";
                            break;
                        case 3:
                            pelicula = "GHOST IN THE SHELL";
                            break;
                        case 4:
                            pelicula = "LALALAND";
                            break;
                        case 5:
                            pelicula = "FALLEN ANGELS";
                            break;
                        case 6:
                            pelicula = "CHUNGKING EXPRESS";
                            break;
                        case 7:
                            pelicula = "THE GRAND BUDAPEST HOTEL";
                            break;
                        case 8:
                            pelicula = "ASTEROID CITY";
                            break;
                        case 9:
                            pelicula = "THE LIGHTHOUSE";
                            break;
                    }
                    partida = OcultarPelicula(pelicula);

                    do{ // Inicia el juego
                        System.out.println(ahorcado);
                        System.out.println();
                        System.out.println(partida);
                        System.out.print("Ingresa una letra: ");

                        char letra = scanner.next().charAt(0); // lectura de letra del jugador

                        if (LetraValida(letra)) { // se revisa que la letra sea válida
                            String partida_aux = "";
                            boolean correcta = false;

                            for (int i = 0; i < pelicula.length(); i++){ // recorre el nombre de la pelicula
                                char pelicula_i = pelicula.charAt(i);
                                char partida_i = partida.charAt(i*2);
                                
                                if (LetraValida(partida_i) || partida_i == ' ') // si ya se había colocado antes o es un espacio, sólo lo escribe
                                    partida_aux += partida_i + " ";
                                else if (letra == pelicula_i){                // si coincide, la escribe y activa bandera en true
                                    partida_aux += letra + " ";
                                    correcta = true;
                                } else                                        // si no coincide, escribe raya y no cambia bandera en false
                                    partida_aux += "_ ";
                            }
                            partida = partida_aux;

                            if (correcta){
                                System.out.println("Correcto! \n");
                                aciertos++; // aumenta contador de aciertos
                            } else {
                                System.out.println("Incorrecto :( \n");
                                errores++; // aumenta contador de errores
                            };

                            switch(errores){ // Numero de errores, se construye el ahorcado
                                case 0:
                                    ahorcado = "";
                                    break;
                                case 1:
                                    ahorcado = "  O";
                                    break;
                                case 2:
                                    ahorcado = "  O \n  |";
                                    break;
                                case 3:
                                    ahorcado = "  O \n/ |";
                                    break;
                                case 4:
                                    ahorcado = "  O \n/ | \\";
                                    break;
                                case 5:
                                    ahorcado = "  O \n/ | \\ \n /";
                                    break;
                                case 6: // 6 errores alcanzados, pierde la partida y muestra el nombre correcto
                                    ahorcado = "  O \n/ | \\ \n / \\ ";
                                    System.out.println(ahorcado);
                                    System.out.println();
                                    System.out.println(partida);
                                    System.out.println("Has perdido. Respuesta correcta:    " + pelicula);
                                    derrotas++; // aumenta contador de partidas perdidas
                                    break;
                            }
                        } else System.out.println("Letra no valida, intenta de nuevo ingresando solo letras mayusculas.");

                        if (aciertos == LetrasUnicas(pelicula)){ // todas las letras adivinadas
                            System.out.println(ahorcado);
                            System.out.println();
                            System.out.println(partida);
                            System.out.println("Felicidades! Has ganado. :)\n");
                            victorias++; // aumenta contador de partidas ganadas
                            break;
                        }
                    } while(errores < 6);
                    break;
                case 2: // 2. Ver estadísticas
                    System.out.println();
                    System.out.println("Total de juegos: " + (victorias + derrotas));
                    System.out.println("Victorias de " +nombre+ ": " + victorias);
                    System.out.println("Victorias de la computadora: " + derrotas);
                    System.out.println();
                    break;
                case 3: // 3. Salir
                    System.out.println("Hasta luego!");
                    break;
                default: // Control de errores
                    System.out.println("Entrada no valida, intente de nuevo con valores del 1 al 3.");
                    break;
            }
        } while(opcion != 3);
    }
}