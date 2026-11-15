#pragma once
#include <string>
#include <vector>

//константа размера поля
constexpr int BOARD_SIZE = 10;

struct Coordinate {
    int row;
    int col;
    bool IsInside() const {
        return row >= 0 && row < BOARD_SIZE
        && col >= 0 && col < BOARD_SIZE;
    }
};

enum class Direction {
    Horizontal,
    Vertical,
};

enum class CellState {
    Empty,
    Ship,
    Miss,
    Hit,
    Sunk
};

enum class ShotOutcome {
    Miss,
    Hit,
    Sunk
};
struct ShotResult {
    ShotOutcome outcome;
    std::vector<Coordinate> sunkCells;
};

struct ShipPlacement {
    Coordinate start;
    int length;
    Direction direction;
};

Coordinate parseCoordinate(const std::string& text);