/**
 * SopaLetras.java clase que implementa un juego de Sopa de Letras en interfaz de consola,
 * se ilustra uso de excepciones para trabajar con índices de arreglos anidados (matrices)
 * y se utilizan como herramienta para la lógica del programa.
 * El programa agrega las palabras establecidas en la sopa de forma aleatoria
 * (vertical, horizontal, diagonal, al derecho y revés) y posteriormente las busca,
 * indicando su posición y dirección en que se encuentra.
 * 
 * @author Andrea Fernanda Rodríguez Rojas.
 * @version Diciembre 2023.
*/

public class SopaLetras{
	public static void main(String[] args) {
		UsoSopa us = new UsoSopa();

		String[] palabras = {"EDUCACION", "LIBERTAD", "ESCUELA", "LIBROS", "BALANCE"};
		Sopa sopa = new Sopa(palabras, 10);
		System.out.println(sopa.toString());
		us.comprobarSopa(sopa);
	}
}