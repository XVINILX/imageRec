#pragma once
#include <array>
#include <cmath>
#include <complex>
#include <vector>
#include <iostream>

/*https://jakevdp.github.io/blog/2013/08/28/understanding-the-fft/ */
/*https://en.wikipedia.org/wiki/Discrete_Fourier_transform#:~:text=In%20mathematics%2C%20the%20discrete%20Fourier,complex%2Dvalued%20function%20of%20frequency.*/
/*Escrever em termo de cos*/

void dft(std::vector<std::array<float, 4>> projectionProfile, int h);