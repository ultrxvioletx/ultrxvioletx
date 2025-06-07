import numpy as np
import matplotlib.pyplot as plt
import scipy.interpolate as interpolate

"""
Full width at half maximum.py programa que mide la "Anchura a media altura" de una función gaussiana
dada por una colección de puntos coordenados, leidos a través de un archivo .txt
Grafica y muestra tanto la gráfica original como el FWHM.

@author Andrea Fernanda Rodríguez Rojas.
@version Octubre 2023.
"""


precision = 0.1 #presición del intervalo x
error = 0.01    #error en el eje y

# FUNCIÓN QUE DEVUELVE EL ÍNDICE DEL ELEMENTO MÁAS CERCANO A UN VALOR,
# DADO UN ARREGLO Y UN VALOR
# list, float -> int
def index_nearest(array, val):
    index = (np.abs(array - val)).argmin()
    return index

# FUNCIÓN QUE DEVUELVE EL VALOR CORRESPONDIENTE A LA X
# DEL VALOR MEDIO VERTICAL AL APLICARLE LA FUNCIÓN F
# function, list, list, float, tinyint(bool) -> float
def encontrar_x(f, x, y, mitad, creciente):
    paso = precision / 10
    x_i = []
    mas_cercano = index_nearest(y, mitad)
    dx = x
    dy = y
    # se ejecuta el while hasta encontrar un valor de y que no exceda el error
    # para esto, tomamos los x,f(x) que rodean a la altura media para crear un intervalo
    # y avanzar sobre él con una presición mayor; en caso de seguir superando el error,
    # se repite el proceso con nuevos valores de x(f) y se refina la precisión.
    # Básicamente, se genera un intervalo [mitad-h, mitad+k] cada vez más pequeño
    while(len(x_i) == 0):
        # en caso de ser creciente, tomamos el f(x) menor inmediato de la altura media y x como inicio del intervalo
        # si es decreciente, tomamos el f(x) mayor inmediato a la altura media, y su x como inicio del intervalo
        menor_yi = mas_cercano if (dy[mas_cercano] < mitad) else mas_cercano + ((-1)**(creciente))
        dx = np.arange(dx[menor_yi], dx[menor_yi + 1], paso) if (creciente) else np.arange(dx[menor_yi - 1], dx[menor_yi], paso)
        dy = f(dx)
        # guardamos el indice de la f(x) que cumpla |mitad - f(x)| < error
        x_i = np.where(np.abs(dy - mitad) < error)[0]

        # refinamos valores en caso de reiniciarse el loop
        paso = paso / 10
        mas_cercano = index_nearest(dy, mitad)
    return dx[x_i][0]

# MAIN
def main():
    xdata, ydata = [], []
    # se abre el archivo datos_halfa.txt y se guardan los valores de x,y en listas correspondientes
    with open("FWHM_data.txt") as archivo:
        for linea in archivo:
            data = []
            data = linea.split()
            xdata.append(int(data[0]))
            ydata.append(int(data[1]))

    # se define la función interpolante f, y se guardan valores de x,f(x) dada la presición elegida
    f = interpolate.interp1d(xdata, ydata, kind='quadratic')
    x = np.arange(min(xdata), max(xdata), precision)
    y = f(x)

    horizontal = min(y) #definimos donde queremos la horizontal
    ymax = max(y)  #valor maximo en y
    ymax_i = np.where(y == ymax)[0] #indice del valor maximo en y
    xmax = x[ymax_i]   #valor en x de la f(x) maxima
    ymitad = (ymax - horizontal) / 2 + horizontal #mitad de la longitud desde la horizontal hasta el maximo
    print("Half Maximum: " + str(ymitad))


    # Definimos el punto x al que corresponde f(x) de la mitad
    ## INTERVALO IZQUIERDO
    x_izq = x[0:ymax_i[0]]
    y_izq = y[0:ymax_i[0]]
    x1 = encontrar_x(f, x_izq, y_izq, ymitad, 1)

    ## INTERVALO DERECHO
    x_der = x[ymax_i[0]:len(x)-1]
    y_der = y[ymax_i[0]:len(y)-1]
    x2 = encontrar_x(f, x_der, y_der, ymitad, 0)


    # Distancia entre x1 y x2, es decir,
    # la anchura a media altura (Full Width at Half Maximum)
    fwhm = np.abs(x2 - x1)
    print("Full Width at Half Maximum: " + str(fwhm))

    # GRÁFICAS
    plt.plot(xdata, ydata, 'o', color="lightseagreen") #puntos de la data
    plt.plot(x, y, '-', color="palevioletred") #función interpolante
    plt.vlines(x=xmax, ymin=horizontal, ymax=ymax, color='gray', linestyle='--', linewidth=1) #altura máxima
    plt.axhline(y=horizontal, color='gray', linestyle='--', linewidth=1) #horizontal del mínimo
    plt.hlines(y=ymitad, xmin=x1, xmax=x2, color="indigo", linewidth=3) #anchura a media altura
    plt.show()

if __name__ == "__main__":
    main()