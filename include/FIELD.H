/**********|**********|**********|
Program: FIELD.H
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: YEE SI SHUN , GOH CHUN YONG , CHEAH CHUN YONG , LOKE KAR HEI
ID: 241UC24157 , 241UC24158 , 241UC2417G , 241UC24168
Lecture Section: TC1L
Tutorial Section: TT4L
Email: yee.si.shun@gstudent.mmu.edu.my , goh.chun.yong@student.mmu.edu.my , cheach.chun.yong@student.mmu.edu.my , loke.kar.hei@student.mmu.edu.my
Phone: 011-63303212 , 011-10758049 , 011-59252689 , 017-2900377
**********|**********|**********/

#ifndef FIELD_H
#define FIELD_H
#include <iostream>
#include "../include/SHIP.H"

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