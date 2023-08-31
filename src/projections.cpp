#include <array>
#include <vector>
#include "TH1I.h"
#include <sstream>
#include "TCanvas.h"
#include "../header/projections.h"
#include <iostream>

void projections(std::vector<std::array<float, 4>> projectionProfile, int h)
{

	std::vector<float> projectionsAngle;

	const double PI = 3.14159265358979323846;
	double deltaYt = (13.5 / 8);
	double deltaX = 100;
	double tang = (deltaYt / deltaX);
	double deltaTheta = atan(tang);
	int totalRun = 9;

	int u = 0;
	for (int i = -4; i < 4; i++)
	{
		for (int k = 0; k < totalRun; k++)
		{
			projectionsAngle.push_back(((k * 20 * PI) / 180) + (i * deltaTheta));
			u++;
		}
	}

	TCanvas c3("c3", "c3");

	TH1F *myProfile[72] = {};

	int projectionProfileSize = projectionProfile.size();
	// for (int z = 0; z < u; z++)
	// {
	// 	std::ostringstream backprojectionNameStream;
	// 	backprojectionNameStream << "projection" << h << "angle" << z << ".png";
	// 	TH1F *myProfile = new TH1F(backprojectionNameStream.str().c_str(), backprojectionNameStream.str().c_str(), 8, 0, 8);
	// 	for (int k = 0; k < projectionProfileSize; k++)
	// 	{
	// 		if (projectionsAngle[z] - 0.01 < projectionProfile[k][1] < projectionsAngle[z] + 0.01)
	// 		{
	// 			int bin = int(projectionProfile[k][0] / 3.375) + 4;
	// 			myProfile->AddBinContent(bin, projectionProfile[k][3]);
	// 		}
	// 	}

	// 	myProfile->Draw();
	// 	c3.SaveAs(backprojectionNameStream.str().c_str());
	// }
}