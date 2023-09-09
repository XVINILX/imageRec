#pragma once
#include <vector>
#include <array>
#include "../header/projections.h"

std::vector<Projection> backprojection(std::vector<std::array<float, 4>> projections, int h);
