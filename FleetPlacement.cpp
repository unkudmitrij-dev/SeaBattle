#include "FleetPlacement.h"
#include <vector>

bool FleetPlacement::hasStandartComposition(const std::vector<ShipPlacement>& fleet) {
    int oneDeckCount = 0;
    int twoDeckCount = 0;
    int threeDeckCount = 0;
    int fourDeckCount = 0;

    for (const ShipPlacement& placement : fleet) {
        switch (placement.length) {
            case 1:
                ++oneDeckCount;
                break;
            case 2:
                ++twoDeckCount;
                break;
            case 3:
                ++threeDeckCount;
                break;
            case 4:
                ++fourDeckCount;
                break;
            default:
                return false;
        }
    }
    return oneDeckCount == 4
        && twoDeckCount == 3
        && threeDeckCount == 2
        && fourDeckCount == 1;
}
