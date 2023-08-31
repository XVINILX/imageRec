#include <iostream>
#include <array>
#include <vector>
#include <filesystem>
#include "../header/gateHeaders.h"
#include <sstream>
#include "../header/backprojection.h"
#include "../header/lorCrystalId.h"
#include "../header/reconstruction3d.h"
#include "../header/projectionSum.h"
#include "../header/projections.h"

int main(int argc, char *argv[])
{

    double PI = 3.14159265358979323846;

    std::cout << "programa iniciando" << std::endl;

    std::string currentPath = std::filesystem::current_path().string();
    TFile MyFile(argv[1]);
    if (MyFile.IsZombie())
    {
        std::cout << "Error opening file" << std::endl;
        exit(-1);
    }

    std::vector<std::array<float, 2>> backprojectionValues;

    std::vector<std::vector<std::array<float, 4>>> allProjections;
    std::vector<std::vector<std::array<float, 4>>> positions3d;
    std::vector<std::array<float, 3>> projection;
    std::array<float, 4> line;

    std::array<float, 3> theta_and_s_crystal_id;
    std::cout << "Programa Iniciando" << std::endl;

    int crystals_number = 8;

    allProjections.resize(crystals_number * 2 - 1);
    std::string coincidencesString = "Coincidences;1";
    const char *coincidences = coincidencesString.c_str();

    double deltaYt = (13.5 / 8);
    double deltaX = 100;
    double tang = (deltaYt / deltaX);
    double minEnergy = 0.498;
    double maxEnergy = 0.550;

    double deltaTheta = atan(tang);
    std::unique_ptr<TTree> tTreeCoincidences(MyFile.Get<TTree>("Coincidences;1"));
    int entries = tTreeCoincidences->GetEntries();
    float en1, en2, posX1, posX2, posZ1, posZ2;
    int crystalID1, crystalID2, run, rsectorID1, rsectorID2;
    tTreeCoincidences->SetBranchAddress("energy1", &en1);
    tTreeCoincidences->SetBranchAddress("energy2", &en2);
    tTreeCoincidences->SetBranchAddress("crystalID2", &crystalID2);
    tTreeCoincidences->SetBranchAddress("crystalID1", &crystalID1);
    tTreeCoincidences->SetBranchAddress("rsectorID1", &rsectorID1);
    tTreeCoincidences->SetBranchAddress("rsectorID2", &rsectorID2);
    tTreeCoincidences->SetBranchAddress("runID", &run);

    for (int i = 0; i < entries; i++)
    {
        tTreeCoincidences->GetEntry(i);
        if (((minEnergy < en1) && (maxEnergy > en1)) && ((minEnergy < en2) && (maxEnergy > en2)))
        {
            int C_crystal1 = int(crystalID1 / crystals_number);
            int C_crystal2 = int(crystalID2 / crystals_number);
            int slice = (C_crystal1 + C_crystal2);
            theta_and_s_crystal_id = theta_s_crystal(crystalID1, crystalID2, run, crystals_number, deltaTheta, rsectorID1);
            int allProjectionsSliceSize = (allProjections[slice]).size();
            // for (int k = 0; k < allProjectionsSliceSize; k++)
            // {
            //     if ((allProjections[slice][k][0] == theta_and_s_crystal_id[0]) && (allProjections[slice][k][1] == theta_and_s_crystal_id[1]))
            //     {
            //         allProjections[slice][k][3] = allProjections[slice][k][3] + 1;
            //         break;
            //     }
            // }
            line[0] = theta_and_s_crystal_id[0];
            line[1] = theta_and_s_crystal_id[1];
            line[2] = theta_and_s_crystal_id[2];
            line[3] = 0;

            allProjections[slice].push_back(line);
        }
    }

    TCanvas c1("c", "c");

    TH2F *myHistos[15] = {};
    int delta = (PI / deltaTheta);

    for (int h = 0; h < crystals_number * 2 - 1; h++)
    {
        std::ostringstream histogramNameStream;
        histogramNameStream << "./images/Sinogram" << h << ".png";

        myHistos[h] = new TH2F(histogramNameStream.str().c_str(), "", 8, -11.76, +11.76, 120, 0, 180);

        positions3d.push_back(backprojection(allProjections[h], h));
        projections(allProjections[h], h);

        int sino_size = allProjections[h].size();

        for (int g = 0; g < sino_size; g++)
        {
            myHistos[h]->Fill(allProjections[h][g][0], allProjections[h][g][1] * 180 / PI);
        }

        c1.SetCanvasSize(450, 450);
        c1.SetWindowSize(500, 500);
        c1.GetFrame()->SetLineColor(0);
        c1.SetFrameFillColor(1);

        // myHistos[h]->SetStats(0);
        // myHistos[h]->GetXaxis()->SetLabelSize(0);
        // myHistos[h]->GetYaxis()->SetLabelSize(0);
        myHistos[h]->Draw("COLZ");

        c1.SaveAs(histogramNameStream.str().c_str());
        c1.Update();
    }

    reconstruction3d(positions3d);

    return 0;
}