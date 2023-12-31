#include <math.h>
#include <iostream>
#include <vector>
#include <array>
#include "../header/gateHeaders.h"
#include "../header/lorCrystalId.h"
#include <cmath>

std::array<float, 2> rotationMatrix(float x, float y, float theta)
{

    // obs: rotação é horária

    std::array<float, 2> arrayRotated = {(x * cos(theta) + y * sin(theta)), (-x * sin(theta) + y * cos(theta))};

    return arrayRotated;
}

std::array<float, 3> theta_s_crystal(int crystalID1, int crystalID2, int run, int Column_n, float delta_theta, int rsectorID1)

{
    float PI = 3.14159265358979323846;
    std::array<float, 3> theta_s;
    std::array<float, 2> rotation;
    float s;
    float angulo;
    float radius = 100;
    float deltaY = 26.88 / 8;
    float X_1, X_2, Y_1, Y_2;

    float pitch = 26.88 / 8;

    float offset = pitch / 2;

    int C_1 = int(crystalID1 / Column_n);
    int L_1 = (crystalID1 - C_1 * Column_n);

    int C_2 = int(crystalID2 / Column_n);
    int L_2 = (crystalID2 - C_2 * Column_n);

    float VectorX = 2 * radius;
    float rSectorY_1 = ((L_1 - (Column_n / 2)) * pitch) + offset;
    float rSectorY_2 = ((L_2 - (Column_n / 2)) * pitch) + offset;
    // esse if abaixo define a posição inicial dos rsector
    // Nesse caso, o rsector 0 está na posição inicial x = - radius.
    // Se o rsector ID1 for referente ao primeiro rsector, essa é a configuração inicial em X.
    // Caso contrário, rsectorID1 é referente ao segundo rsector, que iniciou em +radius

    if (rsectorID1 == 0)
    {
        X_1 = -radius;
        X_2 = -X_1;
        Y_1 = rSectorY_1;
        Y_2 = -rSectorY_2;
    }
    else
    {
        X_2 = -radius;
        X_1 = -X_2;
        Y_1 = -rSectorY_1;
        Y_2 = rSectorY_2;
    }

    rotation = rotationMatrix(X_1, Y_1, run * 20 * PI / 180);
    X_1 = rotation[0];
    Y_1 = rotation[1];

    rotation = rotationMatrix(X_2, Y_2, run * 20 * PI / 180);
    X_2 = rotation[0];
    Y_2 = rotation[1];

    // TODO adiionar as linhas que indicam o valor da equação paramétrica:
    // https://www.youtube.com/watch?v=NXazSzbK6n8;
    // https://www.youtube.com/watch?v=0lG53-ogF2k
    // Vetor Direção(YFinal - YInicial)
    float tX = X_1 - X_2;
    float tY = Y_1 - Y_2;
    // aqui é sim necessário definir dois detectores para saber se y2 é de -radius ou + radius.
    // Definimos os pontos inicias da reta paramétrica

    float Y_0 = Y_2;
    float X_0 = X_2;

    // Aqui é o ponto de referência (centro, onde temos interesse em descobrir a distância)
    float centerX = 0;
    float centerY = 0;

    float t = -(((tX * X_0) + (tY * Y_0)) / ((tY * tY) + (tX * tX)));

    float xPoint = X_0 + t * tX;
    float yPoint = Y_0 + t * tY;
    // TODO pensar numa lógica para retornar o valor de s positivo ou negativo
    // se possível, essa lógica também não pode dar angulo nan...

    // Calculando por meio da eq. geral da reta:
    // https://lirte.pesquisa.ufabc.edu.br/matreematica/a-matematica-do-cotidiano/ramos/geometria/geometria-analitica/equacao-da-reta/
    float a = Y_1 - Y_2;
    float b = X_2 - X_1;
    float c = X_1 * Y_2 - X_2 * Y_1;
    s = (c / sqrt(a * a + b * b));

    angulo = acos(xPoint / s);
    if (s == 0)
    {
        angulo = atan2(tY, tX);
        if (cos(angulo) < 0)
        {
            angulo = angulo - PI / 2;
        }
        else
            angulo = angulo + PI / 2;
    }

    float zPoint = (((C_1 + C_2) - (int(Column_n * 2 - 1) / 2)) * pitch);

    theta_s[0] = s;
    theta_s[1] = angulo;
    theta_s[2] = zPoint;

    return theta_s;
}