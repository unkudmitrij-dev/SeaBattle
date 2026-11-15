#pragma once
#include "GameTypes.h"
#include <vector>


class Ship {
public:
    explicit Ship(const std::vector<Coordinate>& coordinates);
    int length() const;
    //содержит ли корабль выбранную клетку
    bool contains(Coordinate cell) const;
    bool hit(Coordinate cell);
    bool isSunk() const;
    const std::vector<Coordinate>& cells() const;
private:
    std::vector<Coordinate> cells_;
    std::vector<bool> hits_;
};