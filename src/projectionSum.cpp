#include <vector>
#include <array>
#include <iostream>
#include <math.h>
#include "../header/projectionSum.h"


void projectionsSumFunction(std::vector<std::array<float, 3>> projections) {
	std::vector<float> projectionsAngle;
	std::vector<float> projectionsR;
	const double PI = 3.14159265358979323846;
	double deltaYt = (13.5 / 8);
	double deltaX = 100;
	double tang = (deltaYt / deltaX);
	//[0] � o tamanho de r, [1] � theta, [2] � a posi��o z e [3] � a soma
	std::vector<std::array<float, 4>> projectionsSum;
	std::array<float, 4> arrayValues;

	double deltaTheta = atan(tang);
	int totalRun = 9;
	/*const float anguloTest = (totalRun * 20 * PI) / 180 + index*deltaTheta;*/
	int u = 0;
	for (int i = -4; i < 4; i++) {
		for (int k = 0; k < totalRun; k++) {
			projectionsAngle.push_back(((k * 20 * PI) / 180) + (i * deltaTheta));
			u++;
		}
	}

	float deltaY = 13.5 / 4;

	for (int i = -4; i < 4; i++) {
		projectionsR.push_back(i * deltaY);
	}



	const int projectionsNumber = projectionsAngle.size();
	const int projectionsAllDataSize = projections.size();
	const int projectionsRSize = projectionsR.size();
	for (int l = 0; l < projectionsNumber; l++) {
		for (int n = 0; n < projectionsAllDataSize; n++) {
			{
				for (int t = 0; t < projectionsRSize; t++)
					if ((projectionsAngle[l] = projections[n][1]) && (projectionsR[t] = projections[n][0])) {
						int projectionsSumSize = projectionsSum.size();
						for (int k = 0; k < projectionsSumSize; k++) {
							if ((projectionsSum[k][0] = projectionsAngle[l]) && (projectionsSum[k][1] = projectionsAngle[l])) {
								arrayValues[0] = projectionsR[t];
								arrayValues[1] = projectionsAngle[l];
								arrayValues[2] = projections[n][1];
								arrayValues[3] = projectionsSum[k][3]++;
								projectionsSum.push_back(arrayValues);

							}
						}
						arrayValues[0] = projectionsR[t];
						arrayValues[1] = projectionsAngle[l];
						arrayValues[2] = projections[n][1];
						arrayValues[3] = 0;
						projectionsSum.push_back(arrayValues);

					}
			}
		}
	}

	return;


}