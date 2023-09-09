#include <array>
#include <cmath>
#include <complex>
#include <vector>
#include <iostream>
#include "../header/discreteFourierTransform.h"

/*https://jakevdp.github.io/blog/2013/08/28/understanding-the-fft/ */
/*https://en.wikipedia.org/wiki/Discrete_Fourier_transform#:~:text=In%20mathematics%2C%20the%20discrete%20Fourier,complex%2Dvalued%20function%20of%20frequency.*/
/*Escrever em termo de cos*/

void dft(std::vector<std::array<float, 4>> projectionProfile, int h)
{
	// TODO rever essa dft pra que fique mais rápida
	const int projectionsProfileSize = projectionProfile.size();
	float PI = 3.14159265358979323846;

	std::vector<std::array<float, 4>> projectionProfileFourier;
	std::array<float, 4> valuesFourier;
	int n = 0;

	// TODO adicionar um gráfico para visualização dos dados

	for (int k = 0; k < projectionsProfileSize; k++)
	{
		float sum = 0;
		for (int m = 0; m < projectionsProfileSize; m++)
		{
			for (int n = 0; n < projectionsProfileSize; n++)
			{
				sum = sum + projectionProfile[n][0] * (cos(-2 * PI * m * n / projectionsProfileSize));
			}
		}

		valuesFourier[0] = sum; /*soma de fourier*/
		valuesFourier[1] = projectionProfile[k][1];
		valuesFourier[2] = projectionProfile[k][2];
		valuesFourier[3] = projectionProfile[k][3];
		projectionProfileFourier.push_back(valuesFourier);
	}

	std::cout << "Ended a sum" << std::endl;
}