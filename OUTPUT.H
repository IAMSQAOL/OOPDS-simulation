#ifndef OUTPUT_H
#define OUTPUT_H

#include <fstream>

extern std::ofstream mof;  // Declaration
void openF(const std::string& filename);
void close();

#endif 