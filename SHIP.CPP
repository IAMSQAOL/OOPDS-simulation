#include "SHIP.H"
#include <iostream>
#include "SHIP_TYPE.H"

Ship::Ship(){}
Ship::~Ship(){}

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