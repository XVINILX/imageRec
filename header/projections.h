#pragma once
#include <array>
#include <vector>
class Projection
{
public:
    float angle;
    std::array<float, 4> event;
    std::vector<std::array<float, 4>> projection;

    // TODO criar função para reproduzir projeções

public:
    Projection(float angle) : angle(angle){};
    void projectionFunction(std::array<float, 4> event);
};