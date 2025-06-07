import java.util.Random;

class Sopa{
    private char[][] sopa;
	private int dimension;
	private String[] palabras;

    public Sopa(String[] palabras){
		this.dimension = 10;
		this.palabras = palabras;
        this.sopa = crearSopa();
    }
	public Sopa(String[] palabras, int dimension){
		this.dimension = dimension;
		this.palabras = palabras;
		this.sopa = crearSopa();
	}

    public char[][] getSopa(){
        return this.sopa;
    }
	public int getDimension(){
		return this.dimension;
	}
    public String[] getPalabras(){
        return this.palabras;
    }

	public char[][] crearSopa(){
        Random random = new Random();
		UsoSopa us = new UsoSopa();

		int dim = this.dimension;
		int cantidadPalabras = this.palabras.length;
        char[][] sopa = new char[dim][dim];
        //INSERTAR PALABRAS
        int numPalabrasInsertadas = random.nextInt(5)+3; //insertaremos de 3 a 7 palabras en la sopa
        for(int i = 0; i < numPalabrasInsertadas; i++){
            int p = random.nextInt(cantidadPalabras); //indice de la palabra a insertar
            int intentos = 0; //número de intentos para insertar una palabra
            while(intentos < 4){
                int row = random.nextInt(dim); //indice de la fila
                int col = random.nextInt(dim); //indice de la columna
                int direccion = random.nextInt(8)+1; //consideramos 8 direcciones de la palabra: arriba, abajo, izq, der y 4 diagonales
                try{
                    char[] temp;
                    switch(direccion){
                        case 1: //arriba
                            temp = us.extraerColumna(sopa,col);
                            temp = us.defineTemp(temp, palabras[p], row);
                            temp = us.volteaArray(temp);
                            for(int l = 0; l < temp.length; l++){
                                sopa[l][col] = temp[l];
                            }
                            break;
                        case 2: //abajo
                            temp = us.extraerColumna(sopa,col);
                            temp = us.defineTemp(temp, palabras[p], row);
                            for(int l = 0; l < temp.length; l++){
                                sopa[l][col] = temp[l];
                            }
                            break;
                        case 3: //izquierda
                            temp = us.extraerFila(sopa,row);
                            temp = us.defineTemp(temp, palabras[p], col);
                            temp = us.volteaArray(temp);
                            for(int l = 0; l < temp.length; l++){
                                sopa[row][l] = temp[l];
                            }
                            break;
                        case 4: //derecha
                            temp = us.extraerFila(sopa,row);
                            temp = us.defineTemp(temp, palabras[p], col);
                            for(int l = 0; l < temp.length; l++){
                                sopa[row][l] = temp[l];
                            }
                            break;
                        case 5: //diagonal arriba-izquierda
                            temp = us.extraerDiagonal(sopa,row,col);
                            temp = us.defineTemp(temp, palabras[p], Math.min(row,col));
                            temp = us.volteaArray(temp);
                            for(int l = 0; l < temp.length; l++){
                                int r = (row>col) ? (row-col)+l : l;
                                int c = (row>col) ? l : (row-col)+l;
                                sopa[r][c] = temp[l];
                            }
                            break;
                        case 6: //diagonal abajo-derecha
                            temp = us.extraerDiagonal(sopa,row,col);
                            temp = us.defineTemp(temp, palabras[p], Math.min(row,col));
                            for(int l = 0; l < temp.length; l++){
                                int r = (row>col) ? (row-col)+l : l;
                                int c = (row>col) ? l : (row-col)+l;
                                sopa[r][c] = temp[l];
                            }
                            break;
                        case 7: //diagonal abajo-izquierda
                            temp = us.extraerDiagonalInversa(sopa,row,col);
                            temp = us.defineTemp(temp, palabras[p], Math.min(9-row,col));
                            temp = us.volteaArray(temp);
                            for(int l = 0; l < temp.length; l++){
                                int r = ((9-row) > col) ? (row+col)-l : 9-l;
                                int c = ((9-row) > col) ? l : col-(9-row)+l;
                                sopa[r][c] = temp[l];
                            }
                            break;
                        case 8: //diagonal arriba-derecha
                            temp = us.extraerDiagonalInversa(sopa,row,col);
                            temp = us.defineTemp(temp, palabras[p], Math.min(9-row,col));
                            for(int l = 0; l < temp.length; l++){
                                int r = ((9-row) > col) ? (row+col)-l : 9-l;
                                int c = ((9-row) > col) ? l : col-(9-row)+l;
                                sopa[r][c] = temp[l];
                            }
                            break;
                    }
                } catch(Exception e){
                    intentos++;
                }
            }
        }
        //INSERTAR LETRAS RANDOM
        String letras = us.extraeLetrasUnicas(this.palabras); //no colocamos todo el abecedario para crear confusión
        for (int i = 0; i < dim; i++){
            for(int j = 0; j < dim; j++){
                if(sopa[i][j] == '\u0000'){
                    int indice = random.nextInt(letras.length());
                    sopa[i][j] = letras.charAt(indice);
                }
            }
        }
        return sopa;
    }

    public String toString(){
		String string = "";
		int dim = this.dimension;
		for(int i = 0; i < 2*dim+1; i++){
			string += "|";
			for(int j = 0; j < dim; j++){
                if (i%2 == 0) { string += "----"; }
				else { string += " " + this.sopa[(i-1)/2][j] + " |"; }
			}
			string += "\n";
		}
		return string;
	}
}