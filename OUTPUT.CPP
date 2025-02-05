#include "OUTPUT.H"

std::ofstream mof; 

void openF(const std::string& filename) {
    mof.open(filename, std::ios::out | std::ios::trunc);
    if (!mof) {
        throw std::runtime_error("Failed to open log file.");
    }
}

void close() {
    if (mof.is_open()) {
        mof.close();
    }
}