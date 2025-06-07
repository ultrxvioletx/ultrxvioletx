public class Libro {
    private String ISBN;
    private String titulo;
    private Autor autor;
    private String editorial;
    private String genero;
    private int anio;
    private int paginas;
    private boolean ilustraciones; //Dado que no todos los libros con ilustraciones son para niños se hace esta implementación

    public Libro(String id){
        this.ISBN = id;
    }

    //METODOS GET
    public String getId(){
        return this.ISBN;
    }
    public String getTitulo(){
        return this.titulo;
    }
    public Autor getAutor(){
        return this.autor;
    }
    public String getGenero(){
        return this.genero;
    }
    public boolean getIlustraciones(){
        return this.ilustraciones;
    }

    //METODOS SET
    public void setTitulo(String titulo){
        this.titulo = titulo;
    }
    public void setAutor(Autor autor){
        this.autor = autor;
    }
    public void setEditorial(String editorial){
        this.editorial = editorial;
    }
    public void setGenero(String genero){
        this.genero = genero;
    }
    public void setAnio(int anio){
        this.anio = anio;
    }
    public boolean setNumPaginas(int num, boolean esInfantil){
        boolean esValido = true;
        if (num > 30 && esInfantil) {
            System.out.println("Un libro infantil no puede tener más de 30 páginas.");
            esValido = false;
        }
        else { this.paginas = num; }
        return esValido;
    }
    public boolean setIlustraciones(String entrada){
        boolean esValido = true;
        if (!entrada.equals("s") && !entrada.equals("n")){
            System.out.println("Entrada no válida.");
            esValido = false;
        } else {
            this.ilustraciones = (entrada.equals("s")) ? true : false;
        }
        return esValido;
    }
    public void setNumIlustraciones(int num){
        
    }

    public String toString(){
        String i = (ilustraciones ? "Sí" : "No");
        return "[" +ISBN+ "]: " +autor+", (" +anio+ "). " +titulo+ ". " +editorial+ ".\nGénero: " +genero+ "\nPáginas: " +paginas+ "\nIlustraciones: " +i+ "\n";
    }
}