public class Autor {
    private String nombre;
    private String paterno;
    private String materno;
    private String nacionalidad;

    public Autor(){

    }

    public Autor(String nombre, String paterno, String materno, String nacionalidad){
        materno = (materno == null) ? "" : materno;
        
        this.nombre = nombre;
        this.paterno = paterno;
        this.materno = materno;
        this.nacionalidad = nacionalidad;
    }

    //METODOS GET
    public String getNombre(){
        return this.nombre;
    }
    public String getPaterno(){
        return this.paterno;
    }
    public String getMaterno(){
        return this.materno;
    }


    //METODOS SET
    public void setNombre(String nombre){
        this.nombre = nombre;
    }
    public void setPaterno(String paterno){
        this.paterno = paterno;
    }
    public void setMaterno(String materno){
        this.materno = materno;
    }
    public void setNacionalidad(String nacionalidad){
        this.nacionalidad = nacionalidad;
    }

    public String toString(){
        return paterno+ " " +materno+ ", " +nombre;
    }
}