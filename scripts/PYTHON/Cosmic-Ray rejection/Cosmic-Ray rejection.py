import astropy.io.fits as fits
import numpy as np
import scipy.ndimage as ndimage

"""
Cosmic-Ray rejection.py programa que, dada una imagen/fotografía estelar identifica rayos cósmicos, diferenciando de estrellas y otros cuerpos.
Es un algoritmo aplicado de acuerdo al paper: Cosmic-Ray Rejection by Laplacian Edge Detection, Pieter G. van Dokkum1 (California Institute of Technology).

@author Andrea Fernanda Rodríguez Rojas.
@version Novimebre 2023.
"""


# Función que convierte la imagen dada a su resolución original dado un factor=2
# ndarray -> ndarray
def original_resolution(img):
    size_x = img.shape[1] * 2
    size_y = img.shape[0] * 2
    new_img = np.zeros(shape = (size_y, size_x))
    for i in np.arange(size_x):
        for j in np.arange(size_y):
            k = int(i/2)
            l = int(j/2)
            new_img[j,i] = img[int(l),int(k)]
    for i in np.arange(1, size_x, 2):
        for j in np.arange(1, size_y, 2):
            new_img[j,i] = (new_img[j-1, i-1] + new_img[j-1, i] + new_img[j, i-1] + new_img[j,i]) / 4
    return(new_img)

# Función que aplica una convolución a una imagen dado un kernel nxn, donde n es impar>=3
# ndarray, ndarray = ndarray
def apply_convolution(img, f):
    size = img.shape
    n = int((f.shape[0]-1)/2)
    f = np.flip(np.flip(f, 0), 1)
    
    #se aplica borde externo de grosor (n-1)/2
    col0, colN = img[:, 0], img[:, size[0]-1]
    col0.shape, colN.shape = (size[0], 1), (size[0], 1)
    for i in np.arange(n):
        img = np.hstack((col0, img))
        img = np.hstack((img, colN))

    row0, rowN = img[0, :], img[size[1]-1, :]
    for i in np.arange(n):
        img = np.vstack((row0, img))
        img = np.vstack((img, rowN))
    
    #se aplica convolución
    conv = np.zeros(shape = (size[0], size[1]))
    for i in np.arange(n, size[1]-n): #eje x
        for j in np.arange(n, size[0]-n): #eje y
            img_piece = img[j-n:j+n+1, i-n:i+n+1]
            mult = np.matrix(f * img_piece)
            suma = mult.sum()
            conv[j,i] = suma if suma >= 0 else 0
    return conv

def main():
    img = fits.open('glob_cluster_cr.fits', uint=True)[0].data
    
    #SUBSAMPLING FACTOR=2
    subs_img = img[0::2, 0::2]

    #CONVOLUTION WITH KERNEL
    #Se aplica la convolución de dos formas distintas (una hecha a mano y otra con scipy)
    f = np.array([[0, -1, 0], [-1, 4, -1], [0, -1, 0]]) * (1/4)
    laplacian = apply_convolution(subs_img, f)
    laplacian2 = ndimage.convolve(subs_img, f)

    #RESAMPLING
    laplacian = original_resolution(laplacian)
    laplacian2 = original_resolution(laplacian2)

    #FINE-STRUCTURE IMAGE
    #se omite el segundo término porque salen valores raros
    fstructure = ndimage.median_filter(img, size=(3,3)) #- (ndimage.median_filter(ndimage.median_filter(img, size=(3,3)), size=(7,7)))

    #DEVIATION
    min_contrast = 2
    cosmic_rays, cosmic_rays2 = 0, 0
    S = np.zeros(shape=(img.shape[0],img.shape[1]))
    S2 = np.zeros(shape=(img.shape[0],img.shape[1]))
    for i in range(img.shape[1]):
        for j in range(img.shape[0]):
            S[j,i] = laplacian[j,i] / fstructure[j,i] if fstructure[j,i] != 0 else 0
            S2[j,i] = laplacian2[j,i] / fstructure[j,i] if fstructure[j,i] != 0 else 0
            if S[j,i] > min_contrast: cosmic_rays+=1
            if S2[j,i] > min_contrast: cosmic_rays2+=1

    print("Cosmic rays = " + str(cosmic_rays)) #164
    print("Cosmic rays = " + str(cosmic_rays2)) #151

    
    #CREATE FITS FILES
    hdu = fits.PrimaryHDU(S)
    hdul = fits.HDUList([hdu])
    hdul.writeto('cosmicrays.fits')


if __name__ == "__main__":
    main()