import numpy as np
def DFT_slow(x):
    """Compute the discrete Fourier Transform of the 1D array x"""
    x = np.asarray(x, dtype=float)
    N = x.shape[0]
    n = np.arange(N)
    print(n)
    k = n.reshape((N, 1))
    print(k)
    print(k*n)
    M = np.exp(-2j * np.pi * k * n / N)
    print(M)
    return np.dot(M, x)


x = np.random.random(1024)
print(DFT_slow(x).shape)


