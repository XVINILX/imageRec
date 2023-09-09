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

    TH2F *myBackProjection = new TH2F(backprojectionNameStream.str().c_str(), backprojectionNameStream.str().c_str(), 8, -11.76, +11.76 + offset, 8, -11.76, +11.76 + offset);

    std::vector<std::array<float, 4>> projectionsValues;
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
    std::vector<float> possiblePositions;
    /* Simple Back Projection
     */

    // for (int i = 0; i < (columnN); i++)
    // {
    //     possiblePositions.push_back(((i - (columnN / 2)) * pitch) + offset);
    // }

    // for (int x = 0; x < columnN; x++)
    // {
    //     for (int y = 0; y < columnN; y++)
    //     {
    //         for (int i = 0; i < projectionSize; i++)
    //         {
    //             float s = (projections[i][0]);
    //             float theta = projections[i][1];
    //             float r = (possiblePositions[x] * cos(theta) + possiblePositions[y] * sin(theta));
    //             if ((s < (r + 0.1)) && (s > (r - 0.1)))
    //             {
    //                 N++;
    //                 positions[0] = possiblePositions[x];
    //                 positions[1] = possiblePositions[y];
    //                 positions[2] = projections[i][2];
    //                 positions[3] = 0;
    //                 projectionsValues.push_back(positions);
    //                 myBackProjection->Fill(possiblePositions[x], possiblePositions[y]);
    //             }
    //         }
    //     }
    // }

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

    return projectionVector;
}