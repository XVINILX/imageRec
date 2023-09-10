#include <array>
#include <vector>
#include "TH1I.h"
#include <sstream>
#include "TCanvas.h"
#include "../header/projections.h"
#include "../header/discreteFourierTransform.h"
#include "../header/inverseDiscreteFourierTransform.h"
#include <iostream>
/**
 * Define uma projection.
 */

void Projection::projectionFunction(std::array<float, 4> event)
{

	projection.push_back(event);
};

void Projection::fourierProjection()
{
	std::array<float, 2> intermediateArray;

	std::vector<std::array<float, 4>> fourierTransform;
	fourierTransform = dft(projection);

	int fourierTransformSize = fourierTransform.size();
	for (int k = 0; k < fourierTransformSize; k++)
	{
		intermediateArray[0] = fourierTransform[k][0] * cos(angle);
		intermediateArray[1] = fourierTransform[k][0] * sin(angle);
		fourierTransform2d.push_back(intermediateArray);
	};
}

void Projection::inverseFourierProjection()
{
	inverseFourier = idft(fourierTransform2d);
}