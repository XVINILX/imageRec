#include <vector>
#include <iostream>
#include <array>
#include "../header/gateHeaders.h"
#include <sstream>
#include "../header/reconstruction3d.h"
#include <math.h>

int reconstruction3d(std::vector<std::vector<std::array<float, 4>>> profile3d)
{
    double PI = 3.14159265358979323846;
    TCanvas c3("c3", "c3");
    int Column_n = 8;
    double pitch = 26.88 / 8;

    double offset = pitch / 2;

    std::cout << "Reconstru��o 3d" << std::endl;
    std::ostringstream reconstructiona3dNameStream;
    reconstructiona3dNameStream << "./images/3drec"
                                << ".png";

    TH3F *my3dRec = new TH3F(reconstructiona3dNameStream.str().c_str(), reconstructiona3dNameStream.str().c_str(), 8, -11.76, +11.76 + offset, 8, -11.76, +11.76 + offset, (2 * Column_n - 1), -11.76, +11.76 + offset);

    std::vector<std::vector<std::array<float, 3>>> profileValues;

    const int projectionSize = profile3d.size();
    auto N = 0.0;
    for (int i = 0; i < projectionSize; i++)
    {
        const int sliceSize = profile3d[i].size();
        for (int k = 0; k < sliceSize; k++)
        {
            my3dRec->Fill(profile3d[i][k][0], profile3d[i][k][1], profile3d[i][k][2]);
        };
    };

    c3.SetCanvasSize(600, 600);
    c3.SetWindowSize(700, 700);

    my3dRec->GetYaxis()->SetTitle("Eixo Y");
    my3dRec->GetXaxis()->SetTitle("Eixo X");
    my3dRec->GetZaxis()->SetTitle("Eixo Z");
    my3dRec->SetStats(kTRUE);
    my3dRec->Draw("LEGO2");

    c3.SaveAs(reconstructiona3dNameStream.str().c_str());

    return 0;
}