#ifndef FIELD_H
#define FIELD_H
#include <iostream>
#include "SHIP.H"

class Field{
    public:
        int width, height, rowCount, col;
        bool start_readFile;
        std::string ignore_line;
        std::string field[10][10];
        std::string backupfield[10][10];
        Field();

        void initialize(const std::string& filename);

        void printField();

        void printBackField();

        void updateField(Ship* shipPtr, int y, int x);

        void FieldBack(int y,int x);
        std::string checkCell(int y, int x);

};

#endif