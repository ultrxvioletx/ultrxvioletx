import java.util.Random;

class UsoSopa{
    //Extrae la fila indice-ésima de una matriz
    //matrix, int -> array
    public char[] extraerFila(char[][] matriz, int indice){
        int dim = matriz.length;
		char[] fila = new char[dim];
		for(int i = 0; i < dim; i++){
			fila[i] = matriz[indice][i];
		}
		return fila;
	}
    //Extrae la columna indice-ésima de una matriz
    //matrix, int -> array
	public char[] extraerColumna(char[][] matriz, int indice){
        int dim = matriz.length;
		char[] columna = new char[dim];
		for(int i = 0; i < dim; i++){
			columna[i] = matriz[i][indice];
		}
		return columna;
	}
    //Extrae la diagonal de una matriz dada una casilla
    //matrix, int, int -> array
    public char[] extraerDiagonal(char[][] matriz, int row, int col){
        int dim = matriz.length;
        char[] diagonal = new char[dim-Math.abs(row-col)];
        for(int i = 0; i < diagonal.length; i++){
            if(row > col){
                diagonal[i] = matriz[(row-col)+i][i];
            }else{
                diagonal[i] = matriz[i][Math.abs(row-col)+i];
            }
        }
        return diagonal;
    }
    //Extrae la diagonal inversa de una matriz dada una casilla
    //matrix, int, int -> array
    public char[] extraerDiagonalInversa(char[][] matriz, int row, int col){
        int dim = matriz.length;
        int length = (dim-row-1 >= col) ? row+col+1 : (dim-col)+(dim-row-1);
        char[] diagonal = new char[length];
        for(int i = 0; i < diagonal.length; i++){
            if((dim-row-1) >= col){
                diagonal[i] = matriz[(row+col)-i][i];
            }else{
                diagonal[i] = matriz[dim-1-i][col-(dim-1-row)+i];
            }
        }
        return diagonal;
    }
    //Voltea un string para poder buscar la palabra al revés
    //string -> string
    public String volteaString(String palabra){
        String volteado = "";
        for(int i = 0; i < palabra.length(); i++){
            volteado += palabra.charAt(palabra.length()-1-i) + "";
        }
        return volteado;
    }
    //Voltea un array para poder insertar la palabra al revés
    //array -> array
    public char[] volteaArray(char[] array){
        char[] volteado = new char[array.length];
        for(int i = 0; i < array.length; i++){
            volteado[i] = array[array.length-1-i];
        }
        return volteado;
    }
    //Asigna valores al array temporal que ayudará a insertar las palabras en la sopa en distintas direcciones
    //array, string, int -> array
    public char[] defineTemp(char[] temp, String palabra, int indice){
        for(int i = 0; i < palabra.length(); i++){
            if(temp[indice+i] == '\u0000' || temp[indice+i] == palabra.charAt(i)){
                temp[indice+i] = palabra.charAt(i);
            }else{
                temp[temp.length + 1] = 'a'; //ocasionamos una excepción a propósito, pues la casilla ya está ocupada
            }
        }
        return temp;
    }
    //Personaliza el mensaje de salida de las palabras encontradas
    //string, string, int, int -> string
    public String crearMensaje(String direccion, String palabra, int row, int col){
        String sentido = "";
        if(row < 0) {
            sentido = " (al revés)";
            row = row*-1;
        }
        if(col < 0){
            sentido = " (al revés)";
            col = col*-1;
        }
        return palabra + ": ["+row+","+col+"] " + direccion + sentido;
    }
    //Valida que un arreglo tenga las palabras buscadas y devuelve un array con el índice donde la encuentra
    //array -> array
    public int[] contienePalabras(char[] array, String[] palabras){
        String linea = "";
        for(int i = 0; i < array.length; i++){
            linea += array[i] + "";
        }
        int[] indexlist = new int[palabras.length];
        for(int i = 0; i < palabras.length; i++){
            int index = 0; //valor default, si no está contenido
            String lineaR = volteaString(linea);
            if(linea.contains(palabras[i])){
                //si está contenida al derecho, devuelve el indice+1 positivo
                indexlist[i] = linea.indexOf(palabras[i]) + 1;
            }
            else if(lineaR.contains(palabras[i])){
                //si está contenido al revés, devuelve el indice+1 negativo
                indexlist[i] = (array.length - lineaR.indexOf(palabras[i]))*-1;
            }
        }
        return indexlist;
    }
    //Extrae las letras únicas de una palabra en un arreglo de palabras
    //array -> string
    public String extraeLetrasUnicas(String[] palabras){
        String unicas = "";
        for(int i = 0; i < palabras.length; i++){
            String palabra = palabras[i];
            for(int j = 0; j < palabra.length(); j++){
                if(!unicas.contains(palabra.charAt(j)+"")){
                    unicas += palabra.charAt(j) + "";
                }
            }
        }
        return unicas;
    }
    //Realiza la búsqueda de palabras en la sopa
    //Sopa -> null
    public void comprobarSopa(Sopa sopaLetras){
        char[][] sopa = sopaLetras.getSopa();
        int dim = sopaLetras.getDimension();
        String[] palabras = sopaLetras.getPalabras();

        boolean hayPalabras = false;
        String[] encuentros = new String[8];
        int e = 0;

        for(int i = 0; i < dim; i++){
            //FILAS, COLUMNAS O DIAGONALES DE LA SOPA
            char fila[] = extraerFila(sopa,i);
            char columna[] = extraerColumna(sopa,i);
            char diagonal1[] = extraerDiagonal(sopa,i,0); //matriz triangular inferior
            char diagonal2[] = extraerDiagonal(sopa,i,dim-1); //matriz triangular superior
            char diagonalInversa1[] = extraerDiagonalInversa(sopa,i,0); //anti-matriz triangular superior
            char diagonalInversa2[] = extraerDiagonalInversa(sopa,i,dim-1); //anti-matriz triangular inferior
            //INDICES DE POSICION DE LAS PALABRAS
            int[] filaIndices = contienePalabras(fila,palabras);
            int[] columnaIndices = contienePalabras(columna,palabras);
            int[] diagonalIndices1 = contienePalabras(diagonal1,palabras);
            int[] diagonalIndices2 = contienePalabras(diagonal2,palabras);
            int[] diagonalInversaIndices1 = contienePalabras(diagonalInversa1,palabras);
            int[] diagonalInversaIndices2 = contienePalabras(diagonalInversa2,palabras);
            //CREACIÓN DE MENSAJES
            for(int k = 0; k < palabras.length; k++){
                if(filaIndices[k] != 0){
                    hayPalabras = true;
                    encuentros[e] = crearMensaje("horizontal", palabras[k], i+1, filaIndices[k]);
                    e++;
                }
                if(columnaIndices[k] != 0){
                    hayPalabras = true;
                    encuentros[e] = crearMensaje("vertical", palabras[k], columnaIndices[k], i+1);
                    e++;
                }
                if(diagonalIndices1[k] != 0){
                    hayPalabras = true;
                    int r = (diagonalIndices1[k]<0) ? 0 : i;
                    int c = (diagonalIndices1[k]<0) ? i : 0;
                    encuentros[e] = crearMensaje("diagonal", palabras[k], r+diagonalIndices1[k], c+diagonalIndices1[k]);
                    e++;
                }
                if(diagonalIndices2[k] != 0){
                    hayPalabras = true;
                    int r = (diagonalIndices2[k]<0) ? 0 : i;
                    int c = (diagonalIndices2[k]<0) ? i : 0;
                    encuentros[e] = crearMensaje("diagonal", palabras[k], r+diagonalIndices2[k], c+diagonalIndices2[k]);
                    e++;
                }
                if(diagonalInversaIndices1[k] != 0){
                    hayPalabras = true;
                    int r = (diagonalInversaIndices1[k]<0) ? (i+1)+(diagonalInversaIndices1[k]+1) : (i+1)-(diagonalInversaIndices1[k]-1);
                    encuentros[e] = crearMensaje("anti-diagonal", palabras[k], r, diagonalInversaIndices1[k]);
                    e++;
                }
                if(diagonalInversaIndices2[k] != 0 && i != 0){
                    hayPalabras = true;
                    int r = (diagonalInversaIndices2[k]<0) ? (dim+1)+diagonalInversaIndices2[k] : (dim+1)-diagonalInversaIndices2[k];
                    encuentros[e] = crearMensaje("anti-diagonal", palabras[k], r, i+Math.abs(diagonalInversaIndices2[k]));
                    e++;
                }
            }
        }
        if (!hayPalabras) System.out.println("La sopa no contiene ninguna de las palabras.");
        else {
            System.out.println("Se encontraron las palabras en los siguientes lugares:");
            for(int i = 0; i < encuentros.length; i++){
                if(encuentros[i] != null) System.out.println(encuentros[i]);
            }
        }
    }
}