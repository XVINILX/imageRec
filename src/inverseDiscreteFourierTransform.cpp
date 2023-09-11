#include <array>
#include <cmath>
#include <complex>
#include <vector>
#include <iostream>
#include <TVirtualFFT.h>
#include "../header/inverseDiscreteFourierTransform.h"

/*https://jakevdp.github.io/blog/2013/08/28/understanding-the-fft/ */
/*https://en.wikipedia.org/wiki/Discrete_Fourier_transform#:~:text=In%20mathematics%2C%20the%20discrete%20Fourier,complex%2Dvalued%20function%20of%20frequency.*/
/*Escrever em termo de cos*/

std::vector<std::array<float, 2>> idft(std::vector<std::array<float, 2>> projectionProfile)
{

	int projectionsProfileSize = projectionProfile.size() * 2;
	float PI = 3.14159265358979323846;

	std::vector<std::array<float, 2>> projectionProfileFourier;
	std::array<float, 2> valuesFourier;
	Double_t xKPoints[projectionsProfileSize];
	Double_t yKPoints[projectionsProfileSize];
	std::cout << "projections profile size" << projectionsProfileSize << std::endl;

	TVirtualFFT *fft = TVirtualFFT::FFT(1, &projectionsProfileSize, "C2R");

	for (int k = 0; k < projectionsProfileSize; k++)
	{
		xKPoints[k] = projectionProfile[k][0];
		yKPoints[k] = projectionProfile[k][1];
		// float sum0 = 0;
		// float sum1 = 0;
		// for (int m = 0; m < projectionsProfileSize; m++)
		// {
		// 	for (int n = 0; n < projectionsProfileSize; n++)
		// 	{
		// 		sum0 = sum0 + projectionProfile[n][0] * (cos(2 * PI * m * n / projectionsProfileSize));
		// 		sum1 = sum1 + projectionProfile[n][0] * (cos(2 * PI * m * n / projectionsProfileSize));
		// 	}
		// }

		// valuesFourier[0] = sum0;
		// valuesFourier[1] = sum1;

		// projectionProfileFourier.push_back(valuesFourier);
	}

	fft->SetPoints(xKPoints);
	fft->Transform();

	Double_t *re_full = new Double_t[projectionsProfileSize];
	Double_t *im_full = new Double_t[projectionsProfileSize];
	fft->GetPoints(re_full);

	for (int k = 0; k < projectionsProfileSize; k++)
	{
		std::cout << re_full[k] << std::endl;
		std::cout << im_full[k] << std::endl;
		valuesFourier[0] = re_full[k];
		valuesFourier[1] = im_full[k];
		projectionProfileFourier.push_back(valuesFourier);
	}
	return projectionProfileFourier;
}