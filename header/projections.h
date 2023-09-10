#pragma once
#include <array>
#include <vector>
class Projection
{
public:
    float angle;
    std::array<float, 4> event;
    std::vector<std::array<float, 4>> projection;
    std::vector<std::array<float, 2>> fourierTransform2d;
    std::vector<std::array<float, 2>> inverseFourier;

public:
    Projection(float angle) : angle(angle){};
    void projectionFunction(std::array<float, 4> event);
    void fourierProjection();
    void inverseFourierProjection();
};