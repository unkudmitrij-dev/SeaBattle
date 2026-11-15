#include "Ship.h"

Ship::Ship(const std::vector<Coordinate> &cells) : cells_(cells), hits_(cells.size(), false) {}

int Ship::length() const {
    return static_cast<int>(cells_.size());
}

bool Ship::contains(Coordinate cell) const {
    for (const Coordinate& deck : cells_) {
        if (deck.row == cell.row && deck.col == cell.col) {
            return true;
        }
    }
    return false;
}

bool Ship::hit(Coordinate cell) {
    for (int i = 0; i < length(); ++i) {
        if (cells_[i].row == cell.row && cells_[i].col == cell.col) {
            if (hits_[i]) {
                return false;
            }
            hits_[i] = true;
            return true;
        }
    }
    return false;
}

bool Ship::isSunk() const {
    if (cells_.empty()) {
        return false;
    }
    for (bool wasHit : hits_) {
        if (!wasHit) {
            return false;
        }
    }
    return true;
}

const std::vector<Coordinate>& Ship::cells() const {
    return cells_;
}
