#include "Board.h"
#include <stdexcept>
bool Board::fitsOnBoard(Coordinate start, int lengh, Direction direction) const {
    if (!start.IsInside() || lengh < 1 || lengh > 4) {
        return false;
    }
    Coordinate end(start);

    if (direction == Direction::Horizontal) {
        end.col += lengh - 1;
    }
    else {
        end.row += lengh - 1;
    }
    return end.IsInside();
}
CellState Board::cellAt(Coordinate cell) const {
    if (!cell.IsInside()) {
        throw std::out_of_range("Клетка находится за пределами поля.");
    }
    return grid_[cell.row][cell.col];
}
Coordinate Board::deckAt(Coordinate start, int length, Direction direction) {
    if (direction == Direction::Horizontal) {
        start.col += length;
    }
    else {
        start.row += length;
    }
    return start;
}
bool Board::canPlaceShip(Coordinate start, int length, Direction direction) const {
    if (!fitsOnBoard(start, length, direction)) {
        return false;
    }
    for (int i = 0; i < length; ++i) {
        const Coordinate deck = deckAt(start, i, direction);
        for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    const Coordinate cell{deck.row+dr, deck.col+dc};
                    if (cell.IsInside() && cellAt(cell) == CellState::Ship) {
                        return false;
                    }
                }
        }
    }
    return true;
}

bool Board::placeShip(Coordinate start, int length, Direction direction) {
    if (!canPlaceShip(start, length, direction)) {
        return false;
    }
    std::vector<Coordinate> cells;
    for (int i = 0; i < length; ++i) {
        cells.push_back(deckAt(start, i, direction));
    }
    ships_.emplace_back(cells);
    for (const Coordinate cell : cells) {
        grid_[cell.row][cell.col] = CellState::Ship;
    }
    return true;
}

ShotResult Board::recieveShot(Coordinate target) {
    const CellState state = cellAt(target);
    if (state == CellState::Miss ||
        state == CellState::Hit ||
        state == CellState::Sunk) {
        throw std::invalid_argument("В эту клетку уже стреляли.");
    }
    if (state == CellState::Empty) {
        grid_[target.row][target.col] = CellState::Miss;
        return {ShotOutcome::Miss, {}};
    }
    for (Ship& ship : ships_) {
        if (!ship.hit(target)) {
            continue;
        }
        if (!ship.isSunk()) {
            grid_[target.row][target.col] = CellState::Hit;
            return {ShotOutcome::Hit, {}};
        }
        const auto& decks = ship.cells();
        for (const Coordinate cell : decks) {
            grid_[cell.row][cell.col] = CellState::Sunk;
        }
        return {ShotOutcome::Sunk, decks};
    }
    throw std::logic_error("В клетке отмечена палуба, но корабль не найден.");
}

bool Board::allShipsSunk() const {
    if (ships_.empty()) {
        return false;
    }
    for (const Ship& ship : ships_) {
        if (!ship.isSunk()) {
            return false;
        }
    }
    return true;
}