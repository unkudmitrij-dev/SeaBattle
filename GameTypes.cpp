#include "GameTypes.h"
#include <stdexcept>

Coordinate parseCoordinate(const std::string& text) {
    if (text.size() < 2 || text.size() > 4) {
        throw std::invalid_argument("Введите координату в формете A1");
    }
    char letter = text[0];
    if (letter >= 'a' && letter <= 'j') {
        letter = 'A' + (letter - 'a');
    }
    if (letter < 'A' || letter > 'J') {
        throw std::invalid_argument("Столбец должен быть буквой от A до J.");
    }

    int row;
    if (text.size() == 2 && text[1] > '0' && text[1] <= '9') {
        row = text[1] - '1';
    }
    else if (text.size() == 3 && text[1] == '1' && text[2] == '0') {
        row = 9;
    }
    else {
        throw std::invalid_argument("Номер строки должен быть от 1 до 10.");
    }
    return Coordinate(row, letter - 'A');
}
