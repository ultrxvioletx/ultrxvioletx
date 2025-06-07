import numpy as np
import scipy.interpolate as interpolate
import matplotlib.pyplot as plt

def gauss_seidel(A, b, cf, iterations=100, e=1e-8):
    n = len(b)
    x = np.zeros(n)
    for i in np.arange(iterations):
        x_aux = np.zeros(n)
        for j in np.arange(n):
            L = np.dot(A[j,:j], x[:j])
            U = np.dot(A[j,j+1:], x[j+1:])
            x_aux[j] = (b[j] - cf[j] - L - U) / A[j,j]
        if (np.allclose(x, x_aux, rtol=e)): break
        x = x_aux
    return x

def main():
    # Diferencias finitas
    # ay'' + by' + cy = f(t)
    alpha = 1
    beta = 2
    gamma = -3
    f = lambda t: t
    # condiciones de frontera
    t0, y0 = 0, 2
    tn, yn = 3, 3
    # step
    h = 0.1
    # definición de matrices
    # cf + A*x = b
    t = np.arange(t0+h, tn, h)
    n = len(t)
    A = np.zeros(shape = (n,n))
    cf = np.zeros(n)
    b = h**2 * f(t)

    for i in np.arange(n):
        for j in np.arange(n):
            if (i == j): A[i,j] = gamma*h**2 - 2*alpha #xi
            elif (j == i+1): A[i,j] = alpha + (beta/2)*h #xi+1
            elif (j == i-1): A[i,j] = alpha - (beta/2)*h #xi-1
        if (i == 0): cf[i] = (alpha - (beta/2)*h) * y0
        elif (i == n-1): cf[i] = (alpha + (beta/2)*h) * yn
    # print(A)
    # print(cf)

    # Cálculo de solución
    y = gauss_seidel(A,b,cf)
    for i in np.arange(n):
        print("t = " + str(round(t[i], 1)) + ", y = " + str(y[i]))

    # Plot
    t = np.insert(t,0,t0)
    t = np.append(t,tn)
    y = np.insert(y,0,y0)
    y = np.append(y,yn)

    g = interpolate.interp1d(t, y)
    t = np.arange(t0,tn,1e-4)
    plt.plot(t, g(t))
    plt.show()



if __name__ == "__main__":
    main()