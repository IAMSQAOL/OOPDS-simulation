#include "Field.h"
#include <iostream>
#include <fstream>

Field::Field() : sfield(false), rowCount(0) {
    std::ifstream file("game.txt");
    if (!file) {
        std::cout << "Error: Couldn't open game.txt" << std::endl;
        return;
    }

    std::string line;
    while (getline(file, line)) {
        if (!sfield) {
            if (line[0] == '0') {
                sfield = true;
            } else {
                continue;
            }
        }
        if (sfield && rowCount < height) {
            int col = 0;
            for (char c : line) {
                if (c == '0' || c == '1') {
                    field[rowCount][col++] = c;
                    if (col >= width) break;
                }
            }
            rowCount++;
        }
    }
}

void Field::printField() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::cout << field[i][j];
            if (field[i][j].length() == 1) {
                std::cout << "  "; // Two spaces for single-character strings
            } else {
                std::cout << " "; // One space for multi-character strings
            }
        }
        std::cout << std::endl;
    }
}

void Field::setCell(int x, int y, std::string name) {
    field[x][y] = name;
};

std::string Field::getCell(int x, int y) {
    return field[x][y];
};

int Field::getWidth() {
    return width;
};

int Field::getHeight() {
    return height;
};