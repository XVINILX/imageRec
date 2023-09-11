#include <array>
#include <cmath>
#include <complex>
#include <vector>
#include <iostream>
#include "../header/discreteFourierTransform.h"
#include "TVirtualFFT.h"
#include "TMath.h"

/*https://jakevdp.github.io/blog/2013/08/28/understanding-the-fft/ */
/*https://en.wikipedia.org/wiki/Discrete_Fourier_transform#:~:text=In%20mathematics%2C%20the%20discrete%20Fourier,complex%2Dvalued%20function%20of%20frequency.*/
/*Escrever em termo de cos*/

std::vector<std::array<float, 2>> dft(std::vector<std::array<float, 4>> projectionProfile)
{
	// TODO rever essa dft pra que fique mais rápida
	Int_t projectionsProfileSize = projectionProfile.size();

	float PI = 3.14159265358979323846;

	std::vector<std::array<float, 2>> projectionProfileFourier;
	std::array<float, 2> valuesFourier;

	// TODO adicionar um gráfico para visualização dos dados
	Double_t array[projectionsProfileSize];

	TVirtualFFT *fft = TVirtualFFT::FFT(1, &projectionsProfileSize, "R2C M K");

	for (int k = 0; k < projectionsProfileSize; k++)
	{
		array[k] = projectionProfile[k][0];
		// float sum = 0;
		// for (int m = 0; m < projectionsProfileSize; m++)
		// {
		// 	for (int n = 0; n < projectionsProfileSize; n++)
		// 	{
		// 		sum = sum + projectionProfile[n][0] * (cos(-2 * PI * m * n / projectionsProfileSize));
		// 	}
		// }

		// // TODO confirmar o que é esse Kr(?) -> abs(num) seria o ramp filter?

		// valuesFourier[0] = sum * (1 / projectionsProfileSize) * abs(sum);
		// valuesFourier[1] = projectionProfile[k][1];
		// valuesFourier[2] = projectionProfile[k][2];
		// valuesFourier[3] = projectionProfile[k][3];
		// projectionProfileFourier.push_back(valuesFourier);
	}

	fft->SetPoints(array);
	fft->Transform();

	Double_t *re_full = new Double_t[projectionsProfileSize];
	Double_t *im_full = new Double_t[projectionsProfileSize];
	fft->GetPointsComplex(re_full, im_full);

	for (int k = 0; k < projectionsProfileSize; k++)
	{
		valuesFourier[0] = re_full[k];
		valuesFourier[1] = im_full[k];
		projectionProfileFourier.push_back(valuesFourier);
	}
	return projectionProfileFourier;
}