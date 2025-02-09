/**********|**********|**********|
Program: SIMULATION.CPP
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: YEE SI SHUN , GOH CHUN YONG , CHEAH CHUN YONG , LOKE KAR HEI
ID: 241UC24157 , 241UC24158 , 241UC2417G , 241UC24168
Lecture Section: TC1L
Tutorial Section: TT4L
Email: yee.si.shun@gstudent.mmu.edu.my , goh.chun.yong@student.mmu.edu.my , cheach.chun.yong@student.mmu.edu.my , loke.kar.hei@student.mmu.edu.my
Phone: 011-63303212 , 011-10758049 , 011-59252689 , 017-2900377
**********|**********|**********/

#include "../include/SIMULATION.H"
#include "../include/OUTPUT.H"
#include "../include/SHIP.H"
#include <fstream>
#include <iostream>

        Simulation::Simulation(){
            std::string gamefile;
            while (true) {
                //Read input ".txt" file into gamefile
                std::cout << "Please enter the filename(example: game2.txt): ";
                std::cin >> gamefile;
                //Test if the gamefile is found
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
                std::cout << "File not found" << std::endl;
                exit(1);
            }
            //Read file's line into attributes
            file >> ignore_line >> iterations;
            file >> ignore_line >> field.width;
            file >> ignore_line >> field.height;
            //Call class Field to read gamefile
            field.initialize(gamefile);
            //If the first character of the line is not 0 , read Ships details into attributes
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
            file.close();
            StartGame();
        }

        void Simulation::StartGame(){
                bool upgrade=false;
                mof << "Initialize:" << std::endl;
                std::cout << "Initialize:" << std::endl;
                field.printField();
                for(int x=1;x<=iterations;x++){
                    mof << "Turn " << x << std::endl;
                    std::cout << "Turn " << x << std::endl;
                    //For each turn , only 2 destroyed ships is allow to spawn back to battlefield
                    for(int j=0;j<2;j++){
                        DESships.dequeue(field,ships); 
                    }
                    mof<<std::endl;
                    std::cout<<std::endl;
                    Node* temp = ships.head;
                    while(temp != nullptr){
                        temp -> shipPtr -> actions(field,ships,DESships,uS);
                        //When a ship's upgrade is available,push it's pointer to Stack
                        if(temp->shipPtr->Ship_upgrade==true){
                            uS2.push(temp->shipPtr);
                            upgrade=true;
        
                        }
                        temp = temp -> next;
                    }
                    
                    //After the turn is finish,begin upgrade of the ship
                    if(upgrade==true){
                        for(int x=0;x<5;x++){
                            if(!uS2.isEmpty()){
                                //get the pointer of the before upgrade ship and delete it
                                Ship* deleteShip = uS2.pop(); 
                                ships.deleteNode(deleteShip);
                                }
                            if(!uS.isEmpty()){
                                //get the pointer of the after upgrade ship and add it into LinkedLisst
                                Ship* addShip = uS.pop();
                                ships.append(addShip);
                            }
                        }
                        upgrade=false;
                    }
                    field.printField();
                    
                    //When there is not ship with Team A or Team B remain inside Queue and LinkedList,
                    //stop simulation and announce the winner.
                    if((ships.remainTeam('A')==false && DESships.WaitTeam('A') == false)|| (DESships.WaitTeam('B') == false && ships.remainTeam('B')==false)){
                        if(ships.remainTeam('A')==false){
                            mof<<std::endl;
                            mof<<"Team B win as Team A annihilated!" << std::endl;
                            std::cout<<std::endl;
                            std::cout<<"Team B win as Team A annihilated!" << std::endl;
                        }else if(ships.remainTeam('B')==false){
                            mof<<std::endl;
                            mof<<"Team A win as Team B annihilated!" << std::endl;
                            std::cout<<std::endl;
                            std::cout<<"Team A win as Team B annihilated!" << std::endl;
                        }
                        break;
                    }
                    
                    //When x became same as iterations , stop the simulation.
                    if(x==iterations){
                    mof<<"Simulation end with time up." << std::endl;
                    std::cout<<"Simulation end with time up." << std::endl;
                    break;
                    }
                }
                mof<<std::endl;
                std::cout<<std::endl;
        }

        //Clear data inside LinkedList to free memory
        Simulation::~Simulation() {
            ships.clear();
        }