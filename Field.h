#ifndef FIELD_H
#define FIELD_H

#include <iostream>

class Field {
public:
    int iterations, width, height, rowCount, col;
    bool sfield;
    std::string field[10][10];

    Field();
    void setCell(int x, int y, std::string name);
    std::string getCell(int x, int y);
    int getWidth();
    int getHeight();
    void printField();
};

#endif // FIELD_H