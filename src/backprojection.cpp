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

std::vector<std::array<float, 4>> backprojection(std::vector<std::array<float, 4>> projections, int h)
{
    double PI = 3.14159265358979323846;
    TCanvas c2("c2", "c2");
    float deltaY = 13.5 / 4;
    int columnN = 8;

    double pitch = 26.88 / 8;

    double offset = pitch / 2;

    std::ostringstream backprojectionNameStream;
    backprojectionNameStream << "./images/backProjection" << h << ".png";

    TH2F *myBackProjection = new TH2F(backprojectionNameStream.str().c_str(), backprojectionNameStream.str().c_str(), 8, -11.76, +11.76 + offset, 8, -11.76, +11.76 + offset);

    std::vector<std::array<float, 4>> projectionsValues;
    std::array<float, 4> positions;
    /* Determinar extremidades da image e determinar os pontos*/

    const int projectionSize = projections.size();
    double N = 0.0;

    std::vector<double> possiblePositions;

    for (int i = 0; i < (columnN); i++)
    {
        possiblePositions.push_back(((i - (columnN / 2)) * pitch) + offset);
    }

    for (int x = 0; x < columnN; x++)
    {
        for (int y = 0; y < columnN; y++)
        {
            for (int i = 0; i < projectionSize; i++)
            {
                double s = (projections[i][0]);
                float theta = projections[i][1];
                double r = (possiblePositions[x] * cos(theta) + possiblePositions[y] * sin(theta));
                if ((s < (r + 0.1)) && (s > (r - 0.1)))
                {
                    N++;
                    positions[0] = possiblePositions[x];
                    positions[1] = possiblePositions[y];
                    positions[2] = projections[i][2];
                    positions[3] = 0;
                    projectionsValues.push_back(positions);
                    myBackProjection->Fill(possiblePositions[x], possiblePositions[y]);
                }
            }
        }
    }

    c2.SetCanvasSize(600, 600);
    c2.SetWindowSize(700, 700);
    c2.GetFrame()->SetLineColor(0);
    c2.SetFrameFillColor(1);
    myBackProjection->GetXaxis()->SetLabelSize(0);
    myBackProjection->GetYaxis()->SetLabelSize(0);
    myBackProjection->GetYaxis()->SetTitle("Eixo Y");
    myBackProjection->GetXaxis()->SetTitle("Eixo X");
    myBackProjection->Scale(1 / N);
    myBackProjection->Draw("COLZ");

    c2.SaveAs(backprojectionNameStream.str().c_str());

    return projectionsValues;
}