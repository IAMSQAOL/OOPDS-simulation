/**********|**********|**********|
Program: OUTPUT.CPP
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: YEE SI SHUN , GOH CHUN YONG , CHEAH CHUN YONG , LOKE KAR HEI
ID: 241UC24157 , 241UC24158 , 241UC2417G , 241UC24168
Lecture Section: TC1L
Tutorial Section: TT4L
Email: yee.si.shun@gstudent.mmu.edu.my , goh.chun.yong@student.mmu.edu.my , cheach.chun.yong@student.mmu.edu.my , loke.kar.hei@student.mmu.edu.my
Phone: 011-63303212 , 011-10758049 , 011-59252689 , 017-2900377
**********|**********|**********/

#include "../include/OUTPUT.H"
//mof declare as name of output file that every files can use
std::ofstream mof; 

void openF(const std::string& filename) {
    //When create the file clear the content inside it first.
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