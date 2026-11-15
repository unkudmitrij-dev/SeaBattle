#pragma once
#include "GameTypes.h"
#include <vector>

class FleetPlacement {
public:
    static bool hasStandartComposition(const std::vector<ShipPlacement>& fleet);
};