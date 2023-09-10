#include <vector>
#include <iostream>
#include <array>
#include "../header/gateHeaders.h"
#include <sstream>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>

#include "../header/backprojection.h"
#include "../header/projectionSum.h"
#include "../header/projections.h"
#include "../header/discreteFourierTransform.h"

std::vector<Projection> backprojection(std::vector<std::array<float, 4>> projections, int h)
{
    float PI = 3.14159265358979323846;
    TCanvas c2("c2", "c2");
    int columnN = 8;

    float pitch = 26.88 / 8;

    float offset = pitch / 2;

    std::ostringstream backprojectionNameStream;
    backprojectionNameStream << "./images/backProjection" << h << ".png";
    // dft(projections, h);

    TH2F *myBackProjection = new TH2F(backprojectionNameStream.str().c_str(), backprojectionNameStream.str().c_str(), 8, -11.76, +11.76, 8, -11.76, +11.76);

    std::vector<std::array<float, 4>> projectionsValues;
    std::vector<std::array<float, 2>> fourierXandY;
    std::vector<Projection> projectionVector;
    std::array<float, 4>
        positions;
    // TODO preciso rever o acionamento da classe aqui embaixo.

    const int projectionSize = projections.size();
    for (int k = 0; k < projectionSize; k++)
    {
        float angle = projections[k][0];
        const int projectionsVectorSize = projectionVector.size();
        if (projectionsVectorSize == 0)
        {
            Projection projection(angle);
            projection.projectionFunction(projections[k]);
            projectionVector.push_back(projection);
        };
        for (int j = 0; j < projectionsVectorSize; j++)
        {

            if (angle == projectionVector[j].angle)
            {
                projectionVector[j].projectionFunction(projections[k]);
                break;
            }
        }
        Projection projection(angle);
        projection.projectionFunction(projections[k]);

        projectionVector.push_back(projection);
    }
    float N = 0.0;
    std::cout << projectionVector.size() << std::endl;
    int projectionVectorSize = projectionVector.size();
    for (int k = 0; k < projectionVectorSize; k++)
    {

        projectionVector[k].fourierProjection();
        projectionVector[k].inverseFourierProjection();
        int projectionsSize = projectionVector[k].inverseFourier.size();
        for (int m = 0; m < projectionsSize; m++)
        {

            myBackProjection->Fill(projectionVector[k].inverseFourier[m][0], projectionVector[k].inverseFourier[m][1]);
        }
    }

    std::cout << "Ended BackProjection of" << h << std::endl;

    c2.SetCanvasSize(600, 600);
    c2.SetWindowSize(700, 700);
    c2.GetFrame()->SetLineColor(0);
    c2.SetFrameFillColor(1);
    myBackProjection->GetYaxis()->SetTitle("Eixo Y");
    myBackProjection->GetXaxis()->SetTitle("Eixo X");
    myBackProjection->Draw("COLZ");

    c2.SaveAs(backprojectionNameStream.str().c_str());

    return projectionVector;
}