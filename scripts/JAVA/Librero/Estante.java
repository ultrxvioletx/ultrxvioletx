import java.util.Scanner;

public class Estante {
    Libro[] estante = new Libro[10];
    Scanner scString = new Scanner(System.in);
    Scanner scInt = new Scanner(System.in);

    //METODO AUXILIAR
    public Libro[] bubbleSort(Libro[] array, int n){
        if (n == 1) { return array; }
        for (int i = 0; i < n-1; i++){
            if (array[i] != null && array[i + 1] != null){
                if (array[i].getTitulo().charAt(0) > array[i + 1].getTitulo().charAt(0)){
                    Libro temp = array[i];
                    array[i] = array[i + 1];
                    array[i + 1] = temp;
                }
            }
        }
        return bubbleSort(array, n-1);
    }

    //AGREGAR UN LIBRO
    public void agregarLibro(){
        //Validacion de que haya espacio disponible
        boolean hayEspacio = false;
        for (int i=0; i<estante.length; i++){
            if(estante[i] == null){
                hayEspacio = true;
                break;
            }
        }
        if (!hayEspacio){ System.out.println("\nEstante lleno, no se puede agregar otro libro.\n"); }
        else {
            //DATOS DEL LIBRO
            System.out.println("\nDatos del libro");
            System.out.print("ISBN: ");
            String id = scString.nextLine();

            //Valida que no se haga agregado el mismo ISBN
            boolean esUnico = true;
            for (int i=0; i<estante.length; i++){
                if (estante[i] != null){
                    if (estante[i].getId().equals(id)){
                        esUnico = false;
                        break;
                    }
                }
            }

            if (!esUnico){ System.out.println("Ya se ha agregado un libro con ese ISBN."); }
            else{
                //Creacion del objeto
                Libro libro = new LibroInfantil(id);

                System.out.print("Titulo: ");
                String titulo = scString.nextLine();
                libro.setTitulo(titulo);

                System.out.print("Editorial: ");
                String editorial = scString.nextLine();
                libro.setEditorial(editorial);

                System.out.print("Genero: ");
                String genero = scString.nextLine();
                libro.setGenero(genero);
                boolean esInfantil = (genero.equals("infantil") || genero.equals("Infantil"));
                if (!esInfantil) { libro = (Libro) libro; }

                System.out.print("A\u00F1o: ");
                int anio = scInt.nextInt();
                libro.setAnio(anio);

                boolean esValido;
                do{
                    System.out.print("Páginas: ");
                    int paginas = scInt.nextInt();
                    esValido = libro.setNumPaginas(paginas, esInfantil);
                } while(!esValido);
                
                //Valida que la entrada [s/n] de ilustraciones sea correcta en caso de no ser infantil
                if (!esInfantil){
                    do{
                        System.out.print("Tiene ilustraciones? [s/n]: ");
                        String ilustraciones = scString.nextLine();
                        esValido = libro.setIlustraciones(ilustraciones);
                    } while (!esValido);
                    if (!libro.getIlustraciones()) libro.setNumIlustraciones(0);
                } else {
                    libro.setIlustraciones("s");
                    //Se ingresa el numero de ilustraciones es caso de ser infantil
                    System.out.print("Número de ilustraciones: ");
                    int numIlustraciones = scInt.nextInt();
                    libro.setNumIlustraciones(numIlustraciones);
                }

                //DATOS DEL AUTOR
                Autor autor = new Autor();
                System.out.println("Datos del autor.");
                System.out.print("Nombre(s): ");
                String nombre = scString.nextLine();
                autor.setNombre(nombre);

                System.out.print("Apellido paterno: ");
                String paterno = scString.nextLine();
                autor.setPaterno(paterno);

                System.out.print("Apellido materno: ");
                String materno = scString.nextLine();
                autor.setMaterno(materno);

                System.out.print("Nacionalidad: ");
                String nacionalidad = scString.nextLine();
                autor.setNacionalidad(nacionalidad);

                libro.setAutor(autor);
                
                for (int i = 0; i < estante.length; i++){
                    if (estante[i] == null){
                        estante[i] = libro;
                        break;
                    }
                }

                System.out.println("\nLibro agregado\n");
            }
        }
    }
    //MODIFICAR UN LIBRO
    public void modificarLibro(String id){
        int opcion = 0, k = -1;

        for (int i = 0; i < estante.length; i++){
            if (estante[i] != null){
                if (estante[i].getId().equals(id)){
                    k = i;
                    break;
                }
            }
        }
        if (k == -1){ System.out.println("\nNo se encontró un libro con ese ISBN.\n"); }
        else {
            while(opcion != 11){
                boolean esInfantil = (estante[k].getGenero().equals("infantil") || estante[k].getGenero().equals("Infantil"));

                System.out.println("Elige la opción que deseas modificar:");
                System.out.println("1. Título del libro");
                System.out.println("2. Editorial");
                System.out.println("3. Género");
                System.out.println("4. A\u00F1o");
                System.out.println("5. Número de páginas");
                if(!esInfantil) System.out.println("6. Ilustraciones");
                if(esInfantil) System.out.println("6. Número de ilustraciones");

                System.out.println("\n7. Nombre del autor");
                System.out.println("8. Apellido paterno del autor");
                System.out.println("9. Apellido materno del autor");
                System.out.println("10. Nacionalidad del autor");

                System.out.println("\n11. Salir");
                opcion = scInt.nextInt();

                switch(opcion){
                    case 1: //titulo del libro
                        System.out.print("Nuevo valor: ");
                        String titulo = scString.nextLine();
                        estante[k].setTitulo(titulo);
                        break;
                    case 2: //editorial
                        System.out.print("Nuevo valor: ");
                        String editorial = scString.nextLine();
                        estante[k].setEditorial(editorial);
                        break;
                    case 3: //genero
                        System.out.print("Nuevo valor: ");
                        String genero = scString.nextLine();
                        estante[k].setGenero(genero);
                        break;
                    case 4: //anio
                        System.out.print("Nuevo valor: ");
                        int anio = scInt.nextInt();
                        estante[k].setAnio(anio);
                        break;
                    case 5: //numero de paginas
                        System.out.print("Nuevo valor: ");
                        int numPags = scInt.nextInt();
                        estante[k].setNumPaginas(numPags, (estante[k] instanceof LibroInfantil));
                        break;
                    case 6: //ilustraciones o num ilustraciones
                        if (!esInfantil){
                            boolean esValido;
                            do{
                                System.out.print("Nuevo valor [s/n]: ");
                                String ilustraciones = scString.nextLine();
                                esValido = estante[k].setIlustraciones(ilustraciones);
                            } while (!esValido);
                            if (!estante[k].getIlustraciones()) estante[k].setNumIlustraciones(0);
                        } else {
                            System.out.print("Nuevo valor: ");
                            int numIlustraciones = scInt.nextInt();
                            estante[k].setNumIlustraciones(numIlustraciones);
                        }
                        break;
                    case 7: //nombre del autor
                        System.out.print("Nuevo valor: ");
                        String nombre = scString.nextLine();
                        estante[k].getAutor().setNombre(nombre);
                        break;
                    case 8: //apellido paterno del autor
                        System.out.print("Nuevo valor: ");
                        String paterno = scString.nextLine();
                        estante[k].getAutor().setPaterno(paterno);
                        break;
                    case 9: //apellido materno del autor
                        System.out.print("Nuevo valor: ");
                        String materno = scString.nextLine();
                        estante[k].getAutor().setMaterno(materno);
                        break;
                    case 10: //nacionalidad del autor
                        System.out.print("Nuevo valor: ");
                        String nacionalidad = scString.nextLine();
                        estante[k].getAutor().setNacionalidad(nacionalidad);
                        break;
                    case 11:
                        break;
                }

                System.out.println("\nLibro modificado con éxito.\n");
            }
        }
    }
    //BORRAR UN LIBRO
    public void borrarLibro(String id){
        boolean existe = false;
        for (int i = 0; i < estante.length; i++){
            if (estante[i] != null){
                if (estante[i].getId().equals(id)){
                    estante[i] = null;
                    existe = true;
                    break;
                }
            }
        }

        if (existe) System.out.println("\nLibro eliminado con éxito.\n");
        else System.out.println("\nNo se encontró un libro con ese ISBN.\n");
    }
    //IMPRIMIR ESTANTE
    public void imprimirEstante(){
        boolean existe = false;
        for (int i = 0; i < estante.length; i++){
            if (estante[i] != null){
                System.out.print("\n" + estante[i].toString() + "\n");
                existe = true;
            }
        }

        if (!existe) { System.out.println("\nNo hay libros en el estante.\n"); }
    }
    //HACER UNA BUSQUEDA
    public void hacerBusqueda(String palabra){
        boolean existe = false;
        Libro[] busqueda = new Libro[estante.length];
        int j = 0;
        for (int i = 0; i < estante.length; i++){
            if (estante[i] != null){
                if (estante[i].getAutor().getNombre().equals(palabra)
                    || estante[i].getAutor().getPaterno().equals(palabra)
                    || estante[i].getAutor().getMaterno().equals(palabra)
                    || estante[i].getTitulo().equals(palabra)
                    || estante[i].getGenero().equals(palabra)
                ){
                    busqueda[j] = estante[i];
                    j++;
                    existe = true;
                }
            }
        }
        if (existe){
            for (int i = 0; i < busqueda.length; i++){
                if (busqueda[i] != null) { System.out.println("\n" +busqueda[i].toString()+ "\n"); }
            }
        } else { System.out.println("\nNo hay libros que coincidan con tu búsqueda.\n"); }
        
    }
    //ORDERNAR ESTANTE
    public void ordenarEstante(){
        boolean existe = false;
        Libro[] temp = new Libro[estante.length];
        int j = 0;
        for (int i = 0; i < estante.length; i++){
            if (estante[i] != null){
                temp[j] = estante[i];
                j++;
                existe = true;
            }
        }
        if (existe){
            estante = bubbleSort(temp, temp.length);
            System.out.println("\nEstante ordenado con éxito.\n");
        } else System.out.println("\nNo hay libros en el estante.\n");
        
    }
    //BORRAR ESTANTE
    public void borrarEstante(){
        for (int i = 0; i < estante.length; i++){
            estante[i] = null;
        }

        System.out.println("\nEl estante ahora está vacío.\n");
    }
}