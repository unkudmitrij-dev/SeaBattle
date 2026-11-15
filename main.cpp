#include "Board.h"
#include "GameTypes.h"

#include <iostream>
#include <stdexcept>
#include <string>

// Длину (от 1 до 4) задаёт вызывающий код. Игрок выбирает место на поле.
bool placeShipManually(Board& board, int length) {
    while (true) {
        std::cout << "Начальная клетка: ";
        std::string coordinateText;
        if (!std::getline(std::cin, coordinateText)) {
            return false;
        }

        Coordinate start{};
        try {
            start = parseCoordinate(coordinateText);
        } catch (const std::invalid_argument& error) {
            std::cout << error.what() << '\n';
            continue;
        }

        Direction direction = Direction::Horizontal;
        if (length > 1) {
            std::cout << "Направление (H — вправо, V — вниз): ";
            std::string directionText;
            if (!std::getline(std::cin, directionText)) {
                return false;
            }

            if (directionText == "V" || directionText == "v") {
                direction = Direction::Vertical;
            } else if (directionText != "H" && directionText != "h") {
                std::cout << "Допустимы H и V. Введи корабль ещё раз.\n";
                continue;
            }
        }

        if (board.placeShip(start, length, direction)) {
            return true;
        }
        std::cout << "Корабль выходит за поле, пересекает другой или касается его.\n";
    }
}

int main() {
    Board board;
    constexpr int shipCount = 10;
    constexpr int lengths[shipCount] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};

    for (int i = 0; i < shipCount; ++i) {
        std::cout << "Корабль " << i + 1 << " из " << shipCount
                  << ". Длина: " << lengths[i] << '\n';
        if (!placeShipManually(board, lengths[i])) {
            std::cout << "\nВвод завершён.\n";
            return 0;
        }
    }

    int deckCount = 0;
    std::cout << "Занятые клетки:";
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board.cellAt({row, col}) == CellState::Ship) {
                ++deckCount;
                const char letter = static_cast<char>('A' + col);
                std::cout << ' ' << letter << row + 1;
            }
        }
    }
    std::cout << '\n';
    std::cout << "Палуб на поле: " << deckCount << '\n';
    return 0;
}



