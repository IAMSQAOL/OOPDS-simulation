#include "FIELD.H"
#include "OUTPUT.H"
#include <iostream>
#include <fstream>

Field::Field(){}
void Field::initialize(const std::string& filename) {
            std::ifstream file(filename);
            if (!file) {
                mof << "File not found" << std::endl;
                exit(1);
            }

            while (getline(file, ignore_line)) {
                if (!start_readFile) {
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
                            backupfield[rowCount][col++] = c; //backup is ass so i put ++ here
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
                    if (field[i][j].length() == 1) {
                        mof << "  "; // Two spaces for single-character strings
                    } else {
                        mof << " "; // One space for multi-character strings
                    }
                }
                mof << std::endl;
            }
        }

        void Field::printBackField() {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    mof << backupfield[i][j];
                    if (backupfield[i][j].length() == 1) {
                        mof << "  "; // Two spaces for single-character strings
                    } else {
                        mof << " "; // One space for multi-character strings
                    }
                }
                mof << std::endl;
            }
        }

        void Field::updateField(Ship* shipPtr, int y, int x) {
                field[y][x] = shipPtr->Ship_name;
        }

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