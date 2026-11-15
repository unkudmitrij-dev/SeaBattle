#pragma once
#include "Ship.h"
#include "GameTypes.h"

#include <vector>

class Board {
public:
    bool fitsOnBoard(Coordinate start, int lengh, Direction direction) const;
    CellState cellAt(Coordinate cell) const;
    bool canPlaceShip(Coordinate start, int length, Direction direction) const;
    bool placeShip(Coordinate start, int length, Direction direction);
    ShotResult recieveShot(Coordinate target);
    bool allShipsSunk() const;
private:
    CellState grid_[BOARD_SIZE][BOARD_SIZE]{};
    std::vector<Ship> ships_;
    static Coordinate deckAt(Coordinate start, int length, Direction direction);
};
