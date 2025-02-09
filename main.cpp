/**********|**********|**********|
Program: main.cpp
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: YEE SI SHUN , GOH CHUN YONG , CHEAH CHUN YONG , LOKE KAR HEI
ID: 241UC24157 , 241UC24158 , 241UC2417G , 241UC24168
Lecture Section: TC1L
Tutorial Section: TT4L
Email: yee.si.shun@gstudent.mmu.edu.my , goh.chun.yong@student.mmu.edu.my , cheach.chun.yong@student.mmu.edu.my , loke.kar.hei@student.mmu.edu.my
Phone: 011-63303212 , 011-10758049 , 011-59252689 , 017-2900377
**********|**********|**********/

#include "include/OUTPUT.H"
#include <iostream>
#include <cstdlib>
#include<ctime>
#include "include/SIMULATION.H"

int main(){
     try {
        //Create file output.txt
        openF("output.txt");

        mof << "Program started" << std::endl;
        mof << "Processing..." << std::endl;
        mof << std::endl;

        std::cout << "Program started" << std::endl;
        std::cout << "Processing..." << std::endl;
        std::cout << std::endl;

        //Using Device time to generate Random Numbers for Simulation
        srand(time(0));
        Simulation sim;
        //Close output.txt file
        close();

    } catch (const std::exception& e) {
        //Print Error line if unable to create output.txt
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}