/**********|**********|**********|
Program: SHIP_CPP
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: YEE SI SHUN , GOH CHUN YONG , CHEAH CHUN YONG , LOKE KAR HEI
ID: 241UC24157 , 241UC24158 , 241UC2417G , 241UC24168
Lecture Section: TC1L
Tutorial Section: TT4L
Email: yee.si.shun@gstudent.mmu.edu.my , goh.chun.yong@student.mmu.edu.my , cheach.chun.yong@student.mmu.edu.my , loke.kar.hei@student.mmu.edu.my
Phone: 011-63303212 , 011-10758049 , 011-59252689 , 017-2900377
**********|**********|**********/

#include "../include/SHIP.H"
#include <iostream>
#include "../include/SHIP_TYPE.H"

Ship::Ship(){}
Ship::~Ship(){}

//Create new Ship object referecing object from Field,LinkedList,Queue and Stack 
Ship* Ship::createShip(const char& Team_name,const std::string& Ship_Type,const std::string& Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
           if(Ship_Type=="Battleship"){
                return new Battleship(Team_name,Ship_name,field,ships,DESships,uS);
            }else if(Ship_Type=="Cruiser"){
                return new Cruiser(Team_name,Ship_name,field,ships,DESships,uS);
            }else if(Ship_Type=="Frigate"){
                return new Frigate(Team_name,Ship_name,field,ships,DESships,uS);
            }else if(Ship_Type=="Amphibious"){
                return new Amphibious(Team_name,Ship_name,field,ships,DESships,uS);
            }else if(Ship_Type=="SniperShip"){
                return new SniperShip(Team_name,Ship_name,field,ships,DESships,uS);
            }else{
                return nullptr;
            }
        }

//upgrade the Ship by create new Ship object with old ship's position X and Y 
Ship* Ship::updateShip(const char& Team_name,const std::string& Ship_Type,const std::string& Ship_name,const int& posX,const int& posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
           if(Ship_Type=="Destroyer"){
                return new Destroyer(Team_name,Ship_name,posX,posY,field,ships,DESships,uS);
            }else if(Ship_Type=="Corvette"){
                return new Corvette(Team_name,Ship_name,posX,posY,field,ships,DESships,uS);
            }else if(Ship_Type=="SuperShip"){
                return new SuperShip(Team_name,Ship_name,posX,posY,field,ships,DESships,uS);
            }else{
                return nullptr;
            }
        }