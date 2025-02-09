/**********|**********|**********|
Program: FIELD.CPP
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: YEE SI SHUN , GOH CHUN YONG , CHEAH CHUN YONG , LOKE KAR HEI
ID: 241UC24157 , 241UC24158 , 241UC2417G , 241UC24168
Lecture Section: TC1L
Tutorial Section: TT4L
Email: yee.si.shun@gstudent.mmu.edu.my , goh.chun.yong@student.mmu.edu.my , cheach.chun.yong@student.mmu.edu.my , loke.kar.hei@student.mmu.edu.my
Phone: 011-63303212 , 011-10758049 , 011-59252689 , 017-2900377
**********|**********|**********/

#include "../include/FIELD.H"
#include "../include/OUTPUT.H"
#include <iostream>
#include <fstream>

Field::Field(){}

void Field::initialize(const std::string& filename) {
            std::ifstream file(filename);
            if (!file) {
                mof << "File not found" << std::endl;
                std::cout<< "File not found" << std::endl;
                exit(1);
            }

            while (getline(file, ignore_line)) {
                if (!start_readFile) {
                    //If the first character of the line is '0',set start_readFile to true so if statement below can activate
                    if (ignore_line[0] == '0') {
                        start_readFile = true;
                    } else {
                        continue;
                    }
                }

                if (start_readFile && rowCount < height) {
                    col = 0;
                    for (char c : ignore_line) {
                        if (c == '0' || c == '1') {
                            field[rowCount][col] = c;
                            backupfield[rowCount][col++] = c; 
                            if (col >= width) break;
                        }
                    }
                    rowCount++;
                }
            }
            file.close();
        }

void Field::printField() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            mof << field[i][j];
            std::cout<< field[i][j];
            //If the length of the value inside array is 1 : print one space 
            //else print 2 space
            if (field[i][j].length() == 1) {
                mof << "  "; 
                std::cout<< "  "; 
            } else {
                mof << " ";
                std::cout<< " ";
            }
        }
        mof << std::endl;
        std::cout<< std::endl;
    }
}

//Print backup BattleField(unuse in any other files)
void Field::printBackField() {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            mof << backupfield[i][j];
            std::cout<< backupfield[i][j];
            if (backupfield[i][j].length() == 1) {
                mof << "  "; 
                std::cout<< "  "; 
            } else {
                mof << " "; 
                std::cout<< " "; 
            }
        }
        mof << std::endl;
        std::cout << std::endl;
    }
}

//Enabling Ship to change the value of the Battlefield array
void Field::updateField(Ship* shipPtr, int y, int x) {
        field[y][x] = shipPtr->Ship_name;
}

//Restore the original value inside Battlefield with Backup
void Field::FieldBack(int y,int x){
    if(backupfield[y][x]=="0"){
        field[y][x] = '0';
    }else if(backupfield[y][x]=="1"){
            field[y][x] = '1';
    }
}

std::string Field::checkCell(int y, int x) {
    return field[y][x];
}