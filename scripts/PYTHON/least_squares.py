import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from scipy.linalg import solve
from scipy.interpolate import interp1d


# float -> float
def f(x, c, fN, N):
    suma = c[0]
    for k in range(1, N+1):
        suma += c[2*k - 1]*fN[1](k, x) + c[2*k]*fN[0](k, x)
    return suma

def least_square(x, y, N):
    cos_k = lambda k, x: np.cos(k * np.pi * x)
    sin_k = lambda k, x: np.sin(k * np.pi * x)
    fN = [sin_k, cos_k]

    A = np.zeros(shape = (2*N + 1, 2*N + 1))
    b = []
    for i in range(2*N + 1):
        k = int((i+1)/2)
        f1 = fN[i%2](k, x) if (i!=0) else np.ones(len(x))
        for j in range(i, 2*N + 1):
            k = int((j+1)/2)
            f2 = fN[j%2](k, x) if (j!=0) else np.ones(len(x))
            dot = np.dot(f1, f2)
            A[i,j] = dot
            A[j,i] = dot
        b.append(np.dot(f1,y))
    c = solve(A, b)
    ff = f(x, c, fN, N)
    F = interp1d(x, ff)

    #RMS
    r = [np.abs(y[i] - ff[i]) for i in range(168)]
    SE = np.dot(r, r)
    RMSE = np.sqrt(SE/168)

    return F, RMSE




data = pd.read_csv("datos_temperatura.csv")
t = np.linspace(0, 7, 168)
x = data["fecha"]
y = data["temperatura"]


#RMSE cuando N=90
ls = least_square(t, y, 90)
F,e = ls[0], ls[1]
print("N = 90, RMSE =", e)

plt.plot(t, y, 'o', color="silver")
plt.plot(t, F(t), '-', color="palevioletred")
plt.show()

#N minimo para que RMSE<0.01
N = 86
e = least_square(t, y, N)[1]
print("N =",N,", RMSE =",e)

N = 87
e = least_square(t, y, N)[1]
print("N =",N,", RMSE =",e)