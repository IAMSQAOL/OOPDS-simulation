#include "Field.h"
#include <iostream>

Field::Field() : sfield(false), rowCount(0) {}

void Field::printField() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << field[i][j] << " ";
        }
        std::cout << std::endl;
    }
}