#ifndef FIELD_H
#define FIELD_H

#include <string>

class Field {
public:
    int iterations, width, height, rowCount, col;
    bool sfield;
    std::string field[10][10];

    Field();
    void printField();
};

#endif // FIELD_H