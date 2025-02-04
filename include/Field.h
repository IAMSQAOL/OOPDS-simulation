#ifndef FIELD_H
#define FIELD_H
#include <iostream>
#include <fstream>
using namespace std;

class Ship;
class Field{
    public:
        int width, height, rowCount, col;
        bool start_readFile;
        string ignore_line;
        string field[10][10];
        string backupfield[10][10];
        Field();
        void initialize(const string& filename, ofstream& mof);
        void printField(ofstream& mof);
        void printBackField(ofstream& mof);
        void updateField(Ship* shipPtr, int y, int x);
        void FieldBack(int y,int x);
        string checkCell(int y, int x);

};

#endif