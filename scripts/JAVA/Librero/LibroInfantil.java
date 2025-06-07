public class LibroInfantil extends Libro{
    private int numIlustraciones;
    
    public LibroInfantil(String id){
        super(id);
    }

    //METODOS SET
    public void setNumIlustraciones(int num){
        this.numIlustraciones = num;
    }

    public String toString(){
        return super.toString() + "Número de ilustraciones: " +numIlustraciones;
    }
}