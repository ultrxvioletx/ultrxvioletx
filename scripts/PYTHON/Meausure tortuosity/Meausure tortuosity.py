# MAIN
import math
import numpy as np
import matplotlib.pyplot as plt
import scipy.interpolate as interpolate
from scipy.integrate import quad

"""
Measure tortuosity.py programa que aplica las operaciones y cálculos dados por el paper:
Measurement and classification of retinal vascular tortuosity, William E. Hart (International Journal of Medical Informatics)
para medir la turtosidad en las venas oculares y detectar posibles enfermedades.
Data dada por un conjunto de puntos en un archivo .dat
Grafica los datos originale, así como imprime en consola los valores de las funciones de tortuisidad.

@author Andrea Fernanda Rodríguez Rojas.
@version Octubre 2023.
"""


kind = 'linear'

# Newton's difference quotient first-order
def d(f, t, left=False, h=1e-6):
    sign = (-1)**(int(left)) #si se acerca por la derecha sign=1, si es por la izquierda sign=-1
    return sign * (f(t + sign*h) - f(t)) / h
# Newton's difference quotient second-order
def d2(f, t, left=False, h=1e-6):
    sum = 0
    sign = (-1)**(int(left))
    for k in range(0,2):
        sum += ((-1)**(k + 2)) * math.comb(2, k) * f(t + sign*k*h)
    return (1/h**2) * sum

# Arc length s(C)
# function, function, list -> float
def s(x, y, t):
    s = 0
    for ti in t[0:len(t)-1]:
        t = np.arange(ti, ti+1, 0.001)
        ff = np.sqrt(d(x,t)**2 + d(y,t)**2)
        f = interpolate.interp1d(t, ff, kind=kind)
        s += quad(f, ti, ti+1)[0]
    return s
# Chord length chord(C)
# function, function, list -> float
def chord(x, y, t):
    chord = 0
    for ti in t[0:len(t)-1]:
        chord += np.sqrt((x(ti+1) - x(ti))**2 + (y(ti+1) - y(ti))**2)
    return chord
# Curvature k(t)
# function, function, list -> function
def k(x, y, t):
    k = []
    for ti in t:
        is_last = ti == t[len(t)-1]
        num = (d(x,ti,is_last)*d2(y,ti,is_last) - d2(x,ti,is_last)*d(y,ti,is_last))
        den = ((d(y,ti,is_last)**2 + d(x,ti,is_last)**2)**(3/2))
        k.append(num/den)
    f = interpolate.interp1d(t, k, kind=kind)
    return f
# Total curvature tc(C)
# function, list -> float
def tc(k, t):
    tc = 0
    for ti in t[0:len(t)-1]:
        t = np.arange(ti, ti+1, 0.001)
        ff = np.abs(k(t))
        f = interpolate.interp1d(t, ff, kind=kind)
        tc += quad(f, ti, ti+1)[0]
    return tc
# Total squared curvature tsc(C)
# function, list -> float
def tsc(k, t):
    tsc = 0
    for ti in t[0:len(t)-1]:
        t = np.arange(ti, ti+1, 0.001)
        ff = k(t)**2
        f = interpolate.interp1d(t, ff, kind=kind)
        tsc += quad(f, ti, ti+1)[0]
    return tsc

# MAIN
def main():
    # Tortuosity measures functions
    T1 = lambda s,chord: s/(chord-1)
    T2 = lambda tc: tc
    T3 = lambda tsc: tsc
    T4 = lambda tc,s: tc/s
    T5 = lambda tsc,s: tsc/s
    T6 = lambda tc,chord: tc/chord
    T7 = lambda tsc,chord: tsc/chord

    # Open files
    c1data_x, c1data_y = [], []
    with open("c1OjoIzq.dat") as c1File:
        for linea in c1File:
            data = linea.split()
            c1data_x.append(float(data[0]))
            c1data_y.append(float(data[1]))

    c2data_x, c2data_y = [], []
    with open("c2OjoIzq.dat") as c2File:
        for linea in c2File:
            data = linea.split()
            c2data_x.append(float(data[0]))
            c2data_y.append(float(data[1]))
    # Curve 1
    f1 = interpolate.interp1d(c1data_x, c1data_y, kind='linear')
    x1 = np.arange(min(c1data_x), max(c1data_x), 0.1)
    y1 = f1(x1)
    plt.plot(c1data_x, c1data_y, 'o', color="silver")
    plt.plot(x1, y1, '-', color="palevioletred")
    # Curve 2
    f2 = interpolate.interp1d(c2data_x, c2data_y, kind='linear')
    x2 = np.arange(min(c2data_x), max(c2data_x), 0.1)
    y2 = f2(x2)
    plt.plot(c2data_x, c2data_y, 'o', color="silver")
    plt.plot(x2, y2, '-', color="lightseagreen")
    
    plt.show()

    # Graphic position for c1
    t1 = np.arange(0, len(c1data_x))
    fx1 = interpolate.interp1d(t1, c1data_x, kind=kind)
    fy1 = interpolate.interp1d(t1, c1data_y, kind=kind)
    x1_new = fx1(t1)
    y1_new = fy1(t1)
    plt.plot(t1, c1data_x, 'o', color="silver")
    plt.plot(t1, x1_new, '-', color="palevioletred", label="x1(t)")
    plt.plot(t1, c1data_y, 'o', color="silver")
    plt.plot(t1, y1_new, '-', color="orchid", label="y1(t)")
    # Graphic position for c2
    t2 = np.arange(0, len(c2data_x))
    fx2 = interpolate.interp1d(t2, c2data_x, kind=kind)
    fy2 = interpolate.interp1d(t2, c2data_y, kind=kind)
    x2_new = fx2(t2)
    y2_new = fy2(t2)
    plt.plot(t2, c2data_x, 'o', color="silver")
    plt.plot(t2, x2_new, '-', color="mediumaquamarine", label="x2(t)")
    plt.plot(t2, c2data_y, 'o', color="silver")
    plt.plot(t2, y2_new, '-', color="limegreen", label="y2(t)")

    plt.legend()
    plt.show()


    # Definitions for c1
    s1 = s(fx1,fy1,t1) #Arc length
    chord1 = chord(fx1,fy1,t1) #Chord length
    k1 = k(fx1,fy1,t1) #Curvature of a C
    tc1 = tc(k1,t1) #Total curvature
    tsc1 = tsc(k1,t1) #Total squared curvature
    # Definitions for c2
    s2 = s(fx2,fy2,t2) #Arc length
    chord2 = chord(fx2,fy2,t2) #Chord length
    k2 = k(fx2,fy2,t2) #Curvature of a C
    tc2 = tc(k2,t2) #Total curvature
    tsc2 = tsc(k2,t2) #Total squared curvature


    # Tortuosity measures for c1
    T1_1 = T1(s1,chord1)
    T2_1 = T2(tc1)
    T3_1 = T3(tsc1)
    T4_1 = T4(tc1,s1)
    T5_1 = T5(tsc1,s1)
    T6_1 = T6(tc1,chord1)
    T7_1 = T7(tsc1,chord1)
    print("CURVA 1:")
    print("T1: " + str(T1_1))
    print("T2: " + str(T2_1))
    print("T3: " + str(T3_1))
    print("T4: " + str(T4_1))
    print("T5: " + str(T5_1))
    print("T6: " + str(T6_1))
    print("T7: " + str(T7_1))

    # Tortuosity measures for c2
    T1_2 = T1(s2,chord2)
    T2_2 = T2(tc2)
    T3_2 = T3(tsc2)
    T4_2 = T4(tc2,s2)
    T5_2 = T5(tsc2,s2)
    T6_2 = T6(tc2,chord2)
    T7_2 = T7(tsc2,chord2)
    print("CURVA 2:")
    print("T1: " + str(T1_2))
    print("T2: " + str(T2_2))
    print("T3: " + str(T3_2))
    print("T4: " + str(T4_2))
    print("T5: " + str(T5_2))
    print("T6: " + str(T6_2))
    print("T7: " + str(T7_2))



if __name__ == "__main__":
    main()