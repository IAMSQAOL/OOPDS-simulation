#include "SIMULATION.H"
#include "OUTPUT.H"
#include "SHIP.H"
#include <fstream>
#include <iostream>

        //Simulation::Simulation(){}
        Simulation::Simulation(){
            std::string gamefile;
            while (true) {
                std::cout << "Please enter the filename(example: game2.txt): ";
                std::cin >> gamefile;

                std::ifstream tfile(gamefile);
                if (tfile) {
                    tfile.close();
                    break;
                } else {
                    std::cout << "File not found. Please re-enter the filename." << std::endl;
                }
            }

            std::ifstream file(gamefile);
            if (!file) {
                mof << "File not found" << std::endl;
                exit(1);
            }
            file >> ignore_line >> iterations;
            file >> ignore_line >> field.width;
            file >> ignore_line >> field.height;
            field.initialize("game.txt");
            while (ignore_line[0] != '0') {
                file >> ignore_line >> Team_Name >> ships_count_in_Team;
                for (int i = 0; i < ships_count_in_Team; ++i) {
                    file >> Ship_Type >> Ship_symbol >> ship_num;
                    for (int j = 0; j < ship_num; ++j) {
                        Ship* ship = Ship::createShip(Team_Name, Ship_Type, Ship_Name = Ship_symbol + std::to_string(j + 1),field,ships,DESships,uS);
                        if (ship) {
                            ships.append(ship);
                        }
                    }
                }
            }
            //Ship* amphibious1 = Ship::createShip ('B', "Amphibious", ";1", field, ships, DESships,uS);
            //Ship* amphibious2 =  Ship::createShip('B', "Amphibious", ";2",  field, ships, DESships,uS);
            //Ship* Sniper =  Ship::createShip('A', "SniperShip", "~S",  field, ships, DESships,uS);
            //ships.append(amphibious1);
            //ships.append(amphibious2);
            //ships.append(Sniper);
            file.close();
            StartGame();
        }

        void Simulation::StartGame(){
                bool upgrade=false;
                mof << "Initialize:" << std::endl;
                field.printField();
                for(int x=1;x<=iterations;x++){
                    mof << "Turn " << x << std::endl;
                    for(int j=0;j<2;j++){
                        DESships.dequeue(field,ships); 
                    }
                    mof<<std::endl;
                    Node* temp = ships.head;
                    Node* temp2;
                    while(temp != nullptr){
                        temp -> shipPtr -> actions(field,ships,DESships,uS);
                        if(temp->shipPtr->Ship_upgrade==true){
                            uS2.push(temp->shipPtr);
    
                            //ships.deleteNode(temp->shipPtr);
                            upgrade=true;
        
                        }
                        temp = temp -> next;
                    }

                    if(upgrade==true){
                        for(int x=0;x<5;x++){
                            if(!uS2.isEmpty()){
                                Ship* deleteShip = uS2.pop(); //fucker this is so weird i need to create a pointer and the function will work
                                ships.deleteNode(deleteShip);
                                }
                            if(!uS.isEmpty()){
                                Ship* addShip = uS.pop();
                                ships.append(addShip);
                            }
                        }
                        upgrade=false;
                    }
                    field.printField();
                    
                    if((ships.remainTeam('A')==false && DESships.WaitTeam('A') == false)|| (DESships.WaitTeam('B') == false && ships.remainTeam('B')==false)){
                        if(ships.remainTeam('A')==false){
                            mof<<std::endl;
                    
                            mof<<"Team B win as Team A annihilated!" << std::endl;
                

                        }else if(ships.remainTeam('B')==false){
                            mof<<std::endl;
                        
                            mof<<"Team A win as Team B annihilated!" << std::endl;
            
                        }
                        break;
                    }
                    if(x==iterations){
                    mof<<"Simulation end with time up." << std::endl;
                    break;
                    }
                }
                mof<<std::endl;
        }

        Simulation::~Simulation() {
            ships.clear();
        }