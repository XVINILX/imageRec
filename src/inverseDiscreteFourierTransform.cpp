#include <array>
#include <cmath>
#include <complex>
#include <vector>
#include <iostream>
#include "../header/inverseDiscreteFourierTransform.h"

/*https://jakevdp.github.io/blog/2013/08/28/understanding-the-fft/ */
/*https://en.wikipedia.org/wiki/Discrete_Fourier_transform#:~:text=In%20mathematics%2C%20the%20discrete%20Fourier,complex%2Dvalued%20function%20of%20frequency.*/
/*Escrever em termo de cos*/

std::vector<std::array<float, 2>> idft(std::vector<std::array<float, 2>> projectionProfile)
{
	// TODO ERRO NA INVERSE DISCRETE
	const int projectionsProfileSize = projectionProfile.size();
	float PI = 3.14159265358979323846;

	std::vector<std::array<float, 2>> projectionProfileFourier;
	std::array<float, 2> valuesFourier;
	int n = 0;

	for (int k = 0; k < projectionsProfileSize; k++)
	{
		float sum = 0;
		valuesFourier[0] = 0;
		valuesFourier[1] = 0;
		for (int m = 0; m < projectionsProfileSize; m++)
		{
			for (int n = 0; n < projectionsProfileSize; n++)
			{
				valuesFourier[0] = valuesFourier[0] + projectionProfile[n][0] * (cos(2 * PI * m * n / projectionsProfileSize));
				valuesFourier[1] = valuesFourier[1] + projectionProfile[n][1] * (cos(2 * PI * m * n / projectionsProfileSize));
			}
		}

		projectionProfileFourier.push_back(valuesFourier);
	}

	std::cout << "Ended a sum" << std::endl;
	return projectionProfileFourier;
}