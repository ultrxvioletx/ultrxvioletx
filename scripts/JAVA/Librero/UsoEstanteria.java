import java.util.Scanner;

/**
 * UsoEstanteria.java clase que implementa una administración muy básica de un estante de libros,
 * se ilustra el uso del CRUD así como un método de ordenamiento y uno de búsqueda básicos.
 * Se limita al uso primitivo de administración de una db (almacena 10 objetos)
 * con el único objetivo de ejemplificar el uso de arreglos y crud en java.
 * 
 * @author Andrea Fernanda Rodríguez Rojas.
 * @version Octubre 2023.
*/

public class UsoEstanteria{
    public static void main(String[] args) {

        Scanner sc = new Scanner(System.in);
        Estante estante = new Estante();

        int opcion = 0;
        while(opcion != 8){
            System.out.println("1. Agregar un nuevo libro");
            System.out.println("2. Modificar los datos de un libro");
            System.out.println("3. Borrar un libro");
            System.out.println("4. Mostrar todos los libros");
            System.out.println("5. Hacer una búsqueda");
            System.out.println("6. Ordenar los libros por titulo");
            System.out.println("7. Limpiar estante (borrar todos los libros)");
            System.out.println("8. Salir");
            opcion = sc.nextInt();

            switch(opcion){
                case 1: //agregar libro
                    estante.agregarLibro();
                    break;
                case 2: //modificar libro
                    System.out.print("Ingresa el ISBN del libro:  ");
                    String id = sc.next();
                    estante.modificarLibro(id);
                    break;
                case 3: //borrar libro
                    System.out.print("Ingresa el ISBN del libro:  ");
                    id = sc.next();
                    estante.borrarLibro(id);
                    break;
                case 4: //imprimir estante
                    estante.imprimirEstante();
                    break;
                case 5: //hacer busqueda
                    System.out.print("Buscar palabra: ");
                    String busqueda = sc.next();
                    estante.hacerBusqueda(busqueda);
                    break;
                case 6: //ordenar libros por titulo
                    estante.ordenarEstante();
                    break;
                case 7: //borrar estante
                    System.out.print("Está seguro que desea borrar todos los libros? [s/n]: ");
                    String confirmacion = sc.next();
                    if (confirmacion.equals("s")) { estante.borrarEstante(); }
                    else if (!confirmacion.equals("n")) { System.out.println("Entrada no válida"); }
                    break;
                case 8:
                    break;
            }
        }
    }
}