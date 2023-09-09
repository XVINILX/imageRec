#include <array>
#include <vector>
#include "TH1I.h"
#include <sstream>
#include "TCanvas.h"
#include "../header/projections.h"
#include <iostream>
/**
 * Define uma projection.
 */

void Projection::projectionFunction(std::array<float, 4> event)
{

	projection.push_back(event);
};