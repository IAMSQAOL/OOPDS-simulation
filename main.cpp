#include "OUTPUT.H"
#include <iostream>
#include <cstdlib>
#include<ctime>
#include "SIMULATION.H"

int main(){
   

     try {
        openF("output.txt");

        mof << "Program started" << std::endl;

        mof << "Processing..." << std::endl;
        mof << std::endl;
        srand(time(0));
        Simulation sim;

        close();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}