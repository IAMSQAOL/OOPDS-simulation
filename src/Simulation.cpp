#include "../include/Simulation.h"
using namespace std;

Simulation::Simulation() : mof("out1put1.txt") {
            ifstream file("game.txt");
            if (!file) {
                mof << "File not found" << endl;
                return;
            }
            file >> ignore_line >> iterations;
            file >> ignore_line >> field.width;
            file >> ignore_line >> field.height;
            field.initialize("game.txt", mof);
            while (ignore_line[0] != '0') {
                file >> ignore_line >> Team_Name >> ships_count_in_Team;
                for (int i = 0; i < ships_count_in_Team; ++i) {
                    file >> Ship_Type >> Ship_symbol >> ship_num;
                    for (int j = 0; j < ship_num; ++j) {
                        Ship* ship = Ship::createShip(Team_Name, Ship_Type, Ship_Name = Ship_symbol + to_string(j + 1),field,ships,DESships,uS, mof);
                        if (ship) {
                            ships.append(ship);
                        }
                    }
                }
            }
            Ship* amphibious1 = Ship::createShip ('B', "Amphibious", ";1", field, ships, DESships,uS, mof);
            Ship* amphibious2 =  Ship::createShip('B', "Amphibious", ";2",  field, ships, DESships,uS, mof);
            Ship* Sniper =  Ship::createShip('A', "SniperShip", "~S",  field, ships, DESships,uS, mof);
            ships.append(amphibious1);
            ships.append(amphibious2);
            ships.append(Sniper);
            file.close();
            StartGame();
        }

        void Simulation::StartGame(){
                bool upgrade=false;
                mof << "Initialize:" << endl;
                field.printField(mof);
                for(int x=1;x<=iterations;x++){
                    mof << "Turn " << x << endl;
                    for(int j=0;j<2;j++){
                        DESships.dequeue(field,ships, mof); 
                    }
                    mof<<endl;
                    Node* temp = ships.head;
                    Node* temp2;
                    while(temp != nullptr){
                        temp -> shipPtr -> actions(field,ships,DESships,uS, mof);
                        if(temp->shipPtr->Ship_upgrade==true){
                            uS2.push(temp->shipPtr, mof);
    
                            //ships.deleteNode(temp->shipPtr);
                            upgrade=true;
        
                        }
                        temp = temp -> next;
                    }

                    if(upgrade==true){
                        for(int x=0;x<5;x++){
                            if(!uS2.isEmpty()){
                                Ship* deleteShip = uS2.pop(mof); //fucker this is so weird i need to create a pointer and the function will work
                                ships.deleteNode(deleteShip);
                                }
                            if(!uS.isEmpty()){
                                Ship* addShip = uS.pop(mof);
                                ships.append(addShip);
                            }
                        }
                        upgrade=false;
                    }
                    field.printField(mof);
                    
                    if((ships.remainTeam('A')==false && DESships.WaitTeam('A') == false)|| (DESships.WaitTeam('B') == false && ships.remainTeam('B')==false)){
                        if(ships.remainTeam('A')==false){
                            mof<<endl;
                            mof<<"Team B win as Team A annihilated!" << endl;


                        }else if(ships.remainTeam('B')==false){
                            mof<<endl;
                            mof<<"Team A win as Team B annihilated!" << endl;
                        }
                        break;
                    }
                    if(x==iterations){
                    mof<<"Simulation end with time up." << endl;
                    
                    break;
                    }
                }
                mof<<endl;
        }

        Simulation::~Simulation() {
            ships.clear();
        }