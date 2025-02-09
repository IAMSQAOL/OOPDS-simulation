/**********|**********|**********|
Program: SHIP_TYPE.CPP
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
#include "../include/SHIP_TYPE.H"
#include <iostream>
#include "../include/FIELD.H"
#include "../include/OUTPUT.H"
#include "../include/LINKEDLIST.H"
#include "../include/STACK.H"
#include "../include/QUEUE.H"

//BattleShip Start--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Battleship::Battleship(char Team_name,std::string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
            this->Team_name = Team_name;
            this->Ship_name = Ship_name;
            this->Ship_type = "Battleship";
            //Keep setting position X and Y of the ship until it find a valid position inside Battlefield
            while(true){
                this->posX = rand()%10;
                this->posY = rand()%10;
                if(field.checkCell(posY,posX)=="0"){
                    field.updateField(this,posY,posX);
                    break;
                }
            }
        }

    void Battleship::look(Field& field,LinkedList& ships){
        int startingX=0,endingX=0,startingY=0,endingY=0;
        int NewP=0;
        //When a ship's position will cause value outside Battlefield array , initialize:
        if( this->posX-1<0 || this->posY-1<0 || this->posX+2>9 || this->posY+2>9){
            if(this->posX-1<0 && this->posY-1<0){ //top left
                startingX=this->posX;
                startingY=this->posY;
                endingX=this->posX+2;
                endingY=this->posY+2;
            }else if(this->posX+2>9 && this->posY-1<0){ //top right
                startingX=this->posX-1;
                startingY=this->posY;
                endingX=this->posX+1;
                endingY=this->posY+2; 
            }else if(this->posX-1<0 && this->posY+2>9){ //Bottom Left
                startingX=this->posX;
                startingY=this->posY-1;
                endingX=this->posX+2;
                endingY=this->posY+1;    
            }else if(this->posX+2>9 && posY+2>9){  //Bottom Right
                startingX=this->posX-1;
                startingY=this->posY-1;
                endingX=this->posX+1;
                endingY=this->posY+1;  
            }else if(this->posX-1<0){ //Left
                startingX=this->posX;
                startingY=this->posY-1;
                endingX=this->posX+2;
                endingY=this->posY+2;  
            }else if(this->posY-1<0){ //Up
                startingX=this->posX-1;
                startingY=this->posY;
                endingX=this->posX+2;
                endingY=this->posY+2;  
            }else if(this->posX+2>9){ //Right
                startingX=this->posX-1;
                startingY=this->posY-1;
                endingX=this->posX+1;
                endingY=this->posY+2;  
            }else if(this->posY+2>9){ //Down
                startingX=this->posX-1;
                startingY=this->posY-1;
                endingX=this->posX+1;
                endingY=this->posY+1;  
            }
        }else{ //middle
            startingX = (this->posX)-1;
            endingX = (this->posX)+2;
            startingY = (this->posY)-1;
            endingY = (this->posY+2);
        }

        //Using initialized starting and ending Position , look for information arround the ship
        for(int row=startingY;row<endingY;row++){
            for(int column=startingX;column<endingX;column++){
                if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)!=this->Team_name){
                    std::cout<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<")" << std::endl;
                    mof<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<")" << std::endl;
                }else if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)==this->Team_name){
                    std::cout<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
                    mof<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
                }
                if(field.checkCell(row,column)=="0"){
                    if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                        //Add NewP when a place is found that are free to move : Up down left Right
                        ++NewP;
                    }
                }
            }
        }

        if(NewP!=0){  
            CanMove = true;
            //Using value of NewP , random generate the position should move to.
            int decide = (rand() % NewP)+1;
            int reaching=0;
            for(int row=startingY;row<endingY;row++){
                for(int column=startingX;column<endingX;column++){
                    if(field.checkCell(row,column)=="0"){
                        if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                            if(reaching!=decide){
                                reaching++;
                                if(reaching==decide){
                                    this->nextX=column;
                                    this->nextY=row;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }else if(NewP==0){
            CanMove=false;
        }
    }

    void Battleship::move(Field& field,LinkedList& ships){
        //Using the move decide during look() , change position of the ship to the desire position 
        if(CanMove){
            mof<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            std::cout<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            field.updateField(this,this->nextY,this->nextX);
            field.FieldBack(this->posY,this->posX);
            this->posX=this->nextX;
            this->posY=this->nextY;
            this->nextX=-1;
            this->nextY=-1;
            CanMove=false;
        }else{
            mof<<this->Ship_name<<" currently can't move." << std::endl;;
            std::cout<<this->Ship_name<<" currently can't move." << std::endl;;
        }
    }

    void Battleship::shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
        int x=0,y=0;
        int shots=2;
        int max_range = 5;
        int calXY;
        for(int i=0;i<shots;i++){
            x = (rand() % 11)-5;
            y = (rand() % 11)-5;
            //Range of shoot should not be larger than 5 , use absolute number to calculate valid shooting position. 
            calXY = abs(x) + abs(y); 
            //If shooting position unvalid , re-generate shooting position of X and Y
            while(calXY>max_range || this->posX+x>9 || this->posX+x<0 || this->posY+y>9 || this->posY+y<0 || x==0 || y==0 || ships.findShipTeam(posX+x,posY+y)==this->Team_name){ //if not less than 5
            x = (rand() % 11)-5;
            y = (rand() % 11)-5;
            calXY = abs(x) + abs(y);
            }
            //If shoot at position that contain another ship that is not the same team:
            if(ships.findShipTeam(posX+x,posY+y)!=this->Team_name || field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1"){
                if(field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1" ){
                    mof << this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<std::endl;
                    std::cout<< this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<std::endl;
                }
                if(field.checkCell(posY+y,posX+x)==ships.findShipname(posX+x,posY+y)){
                    mof << this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<std::endl;
                    std::cout<< this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<std::endl;
                    if(ships.findShipPtr(posX+x,posY+y)->Ship_lives>1){
                    ships.findShipPtr(posX+x,posY+y)->Ship_lives--;
                    this->Ship_kill_count++;
                    mof<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<std::endl;
                    std::cout<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<std::endl;
                    //If the turn already state the destroyed ship will upgrade , don't add the destroyed ship to Queue
                    if(ships.findShipPtr(posX+x,posY+y)->Ship_upgrade==false){
                    DESships.enqueue(ships.findShipPtr(posX+x,posY+y));
                    }
                    //Delete the destroyed ship at LinkedList
                    ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                    //Restore the original value at the position of the destroyed ship
                    field.FieldBack(posY+y,posX+x);
                        //When the Ship's kill count meet the requirement :
                        if(this->Ship_kill_count==4){
                            mof << this->Ship_name << " upgrade to Destroyer!" << std::endl;
                            std::cout<< this->Ship_name << " upgrade to Destroyer!" << std::endl;
                            Ship* ship=updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                            this->Ship_upgrade=true;
                            //Push upgraded Ship pointer to Stack
                            uS.push(ship);
                            break;
                        }
                    }else if(ships.findShipPtr(posX+x,posY+y)->Ship_lives==1 && ships.findShipPtr(posX+x,posY+y)->Ship_die==false){
                        ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die=true;
                        mof << this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<std::endl;
                        std::cout<<this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<std::endl;
                        ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                        field.FieldBack(posY+y,posX+x);
                        if(this->Ship_kill_count==4){
                            mof << this->Ship_name << " upgrade to Destroyer!" << std::endl;
                            std::cout<< this->Ship_name << " upgrade to Destroyer!" << std::endl;
                            Ship* ship=updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                            this->Ship_upgrade=true;
                            uS.push(ship);
                            break;
                        }  
                    }
                }
            }  
        }
    }


//Call all Ship's functions to start working.
void Battleship::actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
    mof<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< std::endl;
    std::cout<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< std::endl;
    look(field,ships);
    move(field,ships);  
    shoot(field,ships,DESships,uS);
    mof<<std::endl;
    std::cout<<std::endl;
}

//BattleShip End--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Cruiser Start--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Cruiser::Cruiser(char Team_name,std::string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
    this->Team_name = Team_name;
    this->Ship_name = Ship_name;
    this->Ship_type = "Cruiser";
    while(true){
        this->posX = rand()%10;
        this->posY = rand()%10;
        if(field.checkCell(posY,posX)=="0"){
            field.updateField(this,posY,posX);
            break;
        }
    }
}

void Cruiser::look(Field& field,LinkedList& ships){
    int startingX=0,endingX=0,startingY=0,endingY=0;
    int NewP=0;
    if( this->posX-1<0 || this->posY-1<0 || this->posX+2>9 || this->posY+2>9){
        if(this->posX-1<0 && this->posY-1<0){ 
            startingX=this->posX;
            startingY=this->posY;
            endingX=this->posX+2;
            endingY=this->posY+2;
        }else if(this->posX+2>9 && this->posY-1<0){ 
            startingX=this->posX-1;
            startingY=this->posY;
            endingX=this->posX+1;
            endingY=this->posY+2; 
        }else if(this->posX-1<0 && this->posY+2>9){
            startingX=this->posX;
            startingY=this->posY-1;
            endingX=this->posX+2;
            endingY=this->posY+1;    
        }else if(this->posX+2>9 && posY+2>9){
            startingX=this->posX-1;
            startingY=this->posY-1;
            endingX=this->posX+1;
            endingY=this->posY+1;  
        }else if(this->posX-1<0){
            startingX=this->posX;
            startingY=this->posY-1;
            endingX=this->posX+2;
            endingY=this->posY+2;  
        }else if(this->posY-1<0){
            startingX=this->posX-1;
            startingY=this->posY;
            endingX=this->posX+2;
            endingY=this->posY+2;  
        }else if(this->posX+2>9){
            startingX=this->posX-1;
            startingY=this->posY-1;
            endingX=this->posX+1;
            endingY=this->posY+2;  
        }else if(this->posY+2>9){
            startingX=this->posX-1;
            startingY=this->posY-1;
            endingX=this->posX+1;
            endingY=this->posY+1;  
        }
    }else{
        startingX = (this->posX)-1;
        endingX = (this->posX)+2;
        startingY = (this->posY)-1;
        endingY = (this->posY+2);
    }
    
    //If enemy ship found on the valid moving position for the ship,set the next moving position to the enemy ship.
    //NewP can be increment even friendly ship is near the ship.
    for(int row=startingY;row<endingY;row++){
        for(int column=startingX;column<endingX;column++){
            if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)!=this->Team_name){
                mof<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
                std::cout<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
                if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                this->nextX=column;
                this->nextY=row;
                NewP=0;
                break;
                }
            }else if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)==this->Team_name){
                mof<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
                std::cout<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
            }
            if(field.checkCell(row,column)=="0" || (field.checkCell(row,column)!=this->Ship_name && ships.findShipTeam(column,row)==this->Team_name)){
                if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                    ++NewP;
                }
            }
        }
    }
    if(NewP!=0){  
        CanMove = true;
        int decide = (rand() % NewP)+1;
        int reaching=0;
        for(int row=startingY;row<endingY;row++){
            for(int column=startingX;column<endingX;column++){
                if(field.checkCell(row,column)!="1"){
                    if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                        if(reaching!=decide){
                            reaching++;
                            if(reaching==decide){
                                this->nextX=column;
                                this->nextY=row;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }else if(NewP==0){
        CanMove=true;
    }
}

//Cruiser can step on friendly ship
void Cruiser::step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
    if(CanMove){
        if(ships.findShipTeam(this->nextX,this->nextY)==this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
            mof<<this->Ship_name<<" step on fristd::endly ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            std::cout<<this->Ship_name<<" step on fristd::endly ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                mof<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<std::endl;
                std::cout<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<std::endl;
                if(ships.findShipPtr(this->nextX,this->nextY)->Ship_upgrade==false){
                DESships.enqueue(ships.findShipPtr(this->nextX,this->nextY));
                }
                ships.deleteNode(ships.findShipPtr(this->nextX,this->nextY));
                field.updateField(this,this->nextY,this->nextX);
                field.FieldBack(this->posY,this->posX);
                this->posX=this->nextX;
                this->posY=this->nextY;
                this->nextX=-1;
                this->nextY=-1;
                CanMove=false;
                this->Ship_kill_count++;
                    if(this->Ship_kill_count==3){
                        mof << this->Ship_name << " upgrade to Destroyer!" << std::endl;
                        std::cout << this->Ship_name << " upgrade to Destroyer!" << std::endl;
                        Ship* ship=updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                        this->Ship_upgrade=true;
                        uS.push(ship);
                        return;
                    }
            }else if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives==1 && ships.findShipPtr(this->nextX,this->nextY)->Ship_die==false){
                ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                mof << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << std::endl;
                std::cout<< this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << std::endl;
                ships.deleteNode(ships.findShipPtr(this->nextX,this->nextY));
                field.updateField(this,this->nextY,this->nextX);
                field.FieldBack(this->posY,this->posX);
                this->posX=this->nextX;
                this->posY=this->nextY;
                this->nextX=-1;
                this->nextY=-1;
                CanMove=false;
                this->Ship_kill_count++;
                if(this->Ship_kill_count==3){
                    mof << this->Ship_name << " upgrade to Destroyer!" << std::endl;
                    std::cout<< this->Ship_name << " upgrade to Destroyer!" << std::endl;
                    Ship* ship=updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                    this->Ship_upgrade=true;
                    uS.push(ship);
                    return;
                }
            }
        }else if(ships.findShipTeam(this->nextX,this->nextY)!=this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
            mof<<this->Ship_name<<" step on enemy ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            std::cout<<this->Ship_name<<" step on enemy ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                mof<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<std::endl;
                std::cout<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<std::endl;
                if(ships.findShipPtr(this->nextX,this->nextY)->Ship_upgrade==false){
                DESships.enqueue(ships.findShipPtr(this->nextX,this->nextY));
                }
                ships.deleteNode(ships.findShipPtr(this->nextX,this->nextY));
                field.updateField(this,this->nextY,this->nextX);
                field.FieldBack(this->posY,this->posX);
                this->posX=this->nextX;
                this->posY=this->nextY;
                this->nextX=-1;
                this->nextY=-1;
                CanMove=false;
                this->Ship_kill_count++;
                    if(this->Ship_kill_count==3){
                        mof << this->Ship_name << " upgrade to Destroyer!" << std::endl;
                        std::cout<< this->Ship_name << " upgrade to Destroyer!" << std::endl;
                        Ship* ship=updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                        this->Ship_upgrade=true;
                        uS.push(ship);
                        return;
                    }
            }else if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives==1 && ships.findShipPtr(this->nextX,this->nextY)->Ship_die==false){
                ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                mof << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << std::endl;
                std::cout<< this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << std::endl;
                ships.deleteNode(ships.findShipPtr(this->nextX,this->nextY));
                field.updateField(this,this->nextY,this->nextX);
                field.FieldBack(this->posY,this->posX);
                this->posX=this->nextX;
                this->posY=this->nextY;
                this->nextX=-1;
                this->nextY=-1;
                CanMove=false;
                this->Ship_kill_count++;
                if(this->Ship_kill_count==3){
                    mof << this->Ship_name << " upgrade to Destroyer!" << std::endl;
                    std::cout<< this->Ship_name << " upgrade to Destroyer!" << std::endl;
                    Ship* ship = updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                    this->Ship_upgrade=true;
                    uS.push(ship);
                    return;
                }
            }
        }else if(field.checkCell(this->nextY,this->nextX)=="0"){
            mof<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            std::cout<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            field.updateField(this,this->nextY,this->nextX);
            field.FieldBack(this->posY,this->posX);
            this->posX=this->nextX;
            this->posY=this->nextY;
            this->nextX=-1;
            this->nextY=-1;
            CanMove=false;
        }
    }else{
        mof<<this->Ship_type<<" is bugging" << std::endl;
        std::cout<<this->Ship_type<<" is bugging" << std::endl;
    }
}
void Cruiser::actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) {
    mof<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< std::endl;
    std::cout<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< std::endl;
    look(field,ships);
    step(field,ships,DESships,uS);
    mof<<std::endl;
    std::cout<<std::endl;
}

//Cruiser End--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//The rest of the class ship's functions is the same except value changed...

//Destoyer Start--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Destroyer::Destroyer(char Team_name,std::string Ship_name,int posX,int posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
    this->Ship_lives=3;
    this->Team_name = Team_name;
    this->Ship_name = Ship_name;
    this->Ship_type = "Destroyer";
    this->posX = posX;
    this->posY = posY;
}
void Destroyer::updateF(Field& field){
    field.updateField(this,this->posY,this->posX);
}

void Destroyer::look(Field& field,LinkedList& ships) {
    int startingX=0,endingX=0,startingY=0,endingY=0;
    int NewP=0;
    if( this->posX-1<0 || this->posY-1<0 || this->posX+2>9 || this->posY+2>9){
        if(this->posX-1<0 && this->posY-1<0){ 
            startingX=this->posX;
            startingY=this->posY;
            endingX=this->posX+2;
            endingY=this->posY+2;
        }else if(this->posX+2>9 && this->posY-1<0){ 
            startingX=this->posX-1;
            startingY=this->posY;
            endingX=this->posX+1;
            endingY=this->posY+2; 
        }else if(this->posX-1<0 && this->posY+2>9){
            startingX=this->posX;
            startingY=this->posY-1;
            endingX=this->posX+2;
            endingY=this->posY+1;    
        }else if(this->posX+2>9 && posY+2>9){
            startingX=this->posX-1;
            startingY=this->posY-1;
            endingX=this->posX+1;
            endingY=this->posY+1;  
        }else if(this->posX-1<0){
            startingX=this->posX;
            startingY=this->posY-1;
            endingX=this->posX+2;
            endingY=this->posY+2;  
        }else if(this->posY-1<0){
            startingX=this->posX-1;
            startingY=this->posY;
            endingX=this->posX+2;
            endingY=this->posY+2;  
        }else if(this->posX+2>9){
            startingX=this->posX-1;
            startingY=this->posY-1;
            endingX=this->posX+1;
            endingY=this->posY+2;  
        }else if(this->posY+2>9){
            startingX=this->posX-1;
            startingY=this->posY-1;
            endingX=this->posX+1;
            endingY=this->posY+1;  
        }
    }else{
        startingX = (this->posX)-1;
        endingX = (this->posX)+2;
        startingY = (this->posY)-1;
        endingY = (this->posY+2);
    }

    for(int row=startingY;row<endingY;row++){
        for(int column=startingX;column<endingX;column++){
            if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)!=this->Team_name){
                mof<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
                std::cout <<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
                if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                this->nextX=column;
                this->nextY=row;
                NewP=0;
                break;
                }
            }else if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)==this->Team_name){
                mof<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
                std::cout<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
            }
            if(field.checkCell(row,column)=="0" || (field.checkCell(row,column)!=this->Ship_name && ships.findShipTeam(column,row)==this->Team_name)){
                if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                    ++NewP;
                }
            }
        }
    }
    if(NewP!=0){  
        CanMove = true;
        int decide = (rand() % NewP)+1;
        int reaching=0;
        for(int row=startingY;row<endingY;row++){
            for(int column=startingX;column<endingX;column++){
                if(field.checkCell(row,column)!="1"){
                    if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                        if(reaching!=decide){
                            reaching++;
                            if(reaching==decide){
                                this->nextX=column;
                                this->nextY=row;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }else if(NewP==0){
        CanMove=true;
    }
}
void Destroyer::step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
    if(CanMove){
        if(ships.findShipTeam(this->nextX,this->nextY)==this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
            mof<<this->Ship_name<<" step on fristd::endly ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            std::cout<<this->Ship_name<<" step on fristd::endly ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                mof<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<std::endl;
                std::cout<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<std::endl;
                if(ships.findShipPtr(this->nextX,this->nextY)->Ship_upgrade==false){
                DESships.enqueue(ships.findShipPtr(this->nextX,this->nextY));
                }
                ships.deleteNode(ships.findShipPtr(this->nextX,this->nextY));
                field.updateField(this,this->nextY,this->nextX);
                field.FieldBack(this->posY,this->posX);
                this->posX=this->nextX;
                this->posY=this->nextY;
                this->nextX=-1;
                this->nextY=-1;
                CanMove=false;
                this->Ship_kill_count++;
                    if(this->Ship_kill_count==3){
                        mof << this->Ship_name << " upgrade to SuperShip!" << std::endl;
                        std::cout<< this->Ship_name << " upgrade to SuperShip!" << std::endl;
                        Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                        this->Ship_upgrade=true;
                        uS.push(ship);
                        return;
                    }
            }else if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives==1 && ships.findShipPtr(this->nextX,this->nextY)->Ship_die==false){
                ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                mof << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << std::endl;
                std::cout<< this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << std::endl;
                ships.deleteNode(ships.findShipPtr(this->nextX,this->nextY));
                field.updateField(this,this->nextY,this->nextX);
                field.FieldBack(this->posY,this->posX);
                this->posX=this->nextX;
                this->posY=this->nextY;
                this->nextX=-1;
                this->nextY=-1;
                CanMove=false;
                this->Ship_kill_count++;
                if(this->Ship_kill_count==3){
                    mof << this->Ship_name << " upgrade to SuperShip!" << std::endl;
                    std::cout<< this->Ship_name << " upgrade to SuperShip!" << std::endl;
                    Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                    this->Ship_upgrade=true;
                    uS.push(ship);
                    return;
                }
            }
        }else if(ships.findShipTeam(this->nextX,this->nextY)!=this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
            mof<<this->Ship_name<<" step on enemy ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            std::cout<<this->Ship_name<<" step on enemy ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                mof<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<std::endl;
                std::cout<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<std::endl;
                if(ships.findShipPtr(this->nextX,this->nextY)->Ship_upgrade==false){
                DESships.enqueue(ships.findShipPtr(this->nextX,this->nextY));
                }
                ships.deleteNode(ships.findShipPtr(this->nextX,this->nextY));
                field.updateField(this,this->nextY,this->nextX);
                field.FieldBack(this->posY,this->posX);
                this->posX=this->nextX;
                this->posY=this->nextY;
                this->nextX=-1;
                this->nextY=-1;
                CanMove=false;
                this->Ship_kill_count++;
                    if(this->Ship_kill_count==3){
                        mof << this->Ship_name << " upgrade to SuperShip!" << std::endl;
                        std::cout<< this->Ship_name << " upgrade to SuperShip!" << std::endl;
                        Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                        this->Ship_upgrade=true;
                        uS.push(ship);
                        return;
                    }
            }else if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives==1 && ships.findShipPtr(this->nextX,this->nextY)->Ship_die==false){
                ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                mof << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << std::endl;
                std::cout<< this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << std::endl;
                ships.deleteNode(ships.findShipPtr(this->nextX,this->nextY));
                field.updateField(this,this->nextY,this->nextX);
                field.FieldBack(this->posY,this->posX);
                this->posX=this->nextX;
                this->posY=this->nextY;
                this->nextX=-1;
                this->nextY=-1;
                CanMove=false;
                this->Ship_kill_count++;
                if(this->Ship_kill_count==3){
                    mof << this->Ship_name << " upgrade to SuperShip!" << std::endl;
                    std::cout<< this->Ship_name << " upgrade to SuperShip!" << std::endl;
                    Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                    this->Ship_upgrade=true;
                    uS.push(ship);
                    return;
                }
            }
        }else if(field.checkCell(this->nextY,this->nextX)=="0"){
            mof<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            std::cout<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            field.updateField(this,this->nextY,this->nextX);
            field.FieldBack(this->posY,this->posX);
            this->posX=this->nextX;
            this->posY=this->nextY;
            this->nextX=-1;
            this->nextY=-1;
            CanMove=false;
        }
    }else{
        mof<<this->Ship_type<<" is bugging" << std::endl;
        std::cout<<this->Ship_type<<" is bugging" << std::endl;
    } 
}
void Destroyer::shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
    int x=0,y=0;
    int shots=2;
    int max_range = 5;
    int calXY;
    for(int i=0;i<shots;i++){
        x = (rand() % 11)-5;
        y = (rand() % 11)-5;
        calXY = abs(x) + abs(y);
        while(calXY>max_range || this->posX+x>9 || this->posX+x<0 || this->posY+y>9 || this->posY+y<0 || x==0 || y==0 || ships.findShipTeam(posX+x,posY+y)==this->Team_name){ //if not less than 5
        x = (rand() % 11)-5;
        y = (rand() % 11)-5;
        calXY = abs(x) + abs(y);
        }
        if(ships.findShipTeam(posX+x,posY+y)!=this->Team_name || field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1"){
            if(field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1" ){
                mof << this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<std::endl;
                std::cout<< this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<std::endl;
            }else if(field.checkCell(posY+y,posX+x)==ships.findShipname(posX+x,posY+y)){
                mof << this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<std::endl;
                std::cout<< this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<std::endl;
                if(ships.findShipPtr(posX+x,posY+y)->Ship_lives>1){
                    ships.findShipPtr(posX+x,posY+y)->Ship_lives--;
                    this->Ship_kill_count++;
                    mof<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<std::endl;;
                    std::cout<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<std::endl;;
                    if(ships.findShipPtr(posX+x,posY+y)->Ship_upgrade==false){
                    DESships.enqueue(ships.findShipPtr(posX+x,posY+y));
                    }
                    ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                    field.FieldBack(posY+y,posX+x);
                    if(this->Ship_kill_count==3){
                        mof << this->Ship_name << " upgrade to SuperShip!" << std::endl;
                        std::cout<< this->Ship_name << " upgrade to SuperShip!" << std::endl;
                        Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                        this->Ship_upgrade=true;
                        uS.push(ship);
                        break;
                    }
                }else if(ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives==1 && ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==false){
                    ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==true;
                    mof << this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<std::endl;
                    std::cout<< this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<std::endl;
                    ships.deleteNode(ships.findShipPtr(this->posX+x,this->posY+y));
                    field.FieldBack(this->posY+y,this->posX+x);
                        if(this->Ship_kill_count==3){
                        mof << this->Ship_name << " upgrade to SuperShip!" << std::endl;
                        std::cout<< this->Ship_name << " upgrade to SuperShip!" << std::endl;
                        Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                        this->Ship_upgrade=true;
                        uS.push(ship);
                        break;
                        }  
                }
            }
        }  
    }
}
void Destroyer::actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
    if(!this->ShootPosition){
        updateF(field);
        this->ShootPosition=true;
    }
    mof<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< std::endl;
    std::cout<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< std::endl;
    look(field,ships);
    step(field,ships,DESships,uS);
    if(this->Ship_upgrade){
        return;
    }
    shoot(field,ships,DESships,uS);
    mof<<std::endl;
    std::cout<<std::endl;
}
//Destroyer End--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//Frigate--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Frigate::Frigate(char Team_name,std::string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
    this->Team_name = Team_name;
    this->Ship_name = Ship_name;
    this->Ship_type = "Frigate";
    while(true){
        this->posX = rand()%10;
        this->posY = rand()%10;
        if(field.checkCell(posY,posX)=="0"){
            field.updateField(this,posY,posX);
            break;
        }
    }
}

void Frigate::shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) { 
    //Record need to be always smaller than 7 else set to 0 to use value inside directions[][]
    if(this->record>7){
        this->record=0;
    }
        int directions[8][2] = {
        {0, -1},  // Up
        {1, -1},  // Up-Right
        {1, 0},   // Right
        {1, 1},   // Down-Right
        {0, 1},   // Down
        {-1, 1},  // Down-Left
        {-1, 0},  // Left
        {-1, -1}  // Up-Left
        };

    if(!this->ShootPosition){
        for (int i = 0; i < 8; i++) {
            if( this->posX + directions[i][0]>=0 && this->posY + directions[i][1]>=0 && this->posX + directions[i][0]<10 && this->posY + directions[i][1]<10){
                this->targetX = this->posX + directions[i][0];
                this->targetY = this->posY + directions[i][1];
                this->record = i;
                this->ShootPosition=true;
                break;
            }
        }
    }

    if(this->ShootPosition){
            std::string targetName = ships.findShipname(this->targetX, this->targetY);
            if (targetName != "nothing" && ships.findShipTeam(this->targetX, this->targetY) != this->Team_name) {
                mof << this->Ship_name << " shoots at (" << targetX << "," << targetY << ") and hits enemy ship: " << targetName << "!" << std::endl;
                std::cout<< this->Ship_name << " shoots at (" << targetX << "," << targetY << ") and hits enemy ship: " << targetName << "!" << std::endl;
                Ship* targetShip = ships.findShipPtr(targetX, targetY);
                targetShip->Ship_lives--;
                if(targetShip->Ship_lives>1){
                mof<<targetShip->Ship_name<<" remain "<<targetShip->Ship_lives << " lives." << std::endl;
                std::cout<<targetShip->Ship_name<<" remain "<<targetShip->Ship_lives << " lives." << std::endl;
                if(targetShip->Ship_upgrade==false){
                DESships.enqueue(targetShip);
                }
                ships.deleteNode(targetShip);
                field.FieldBack(this->targetY, this->targetX);
                this->Ship_kill_count++;
                    if(this->Ship_kill_count==3){
                        mof << this->Ship_name << " upgrade to Corvette!" << std::endl;
                        std::cout<< this->Ship_name << " upgrade to Corvette!" << std::endl;
                        Ship* ship=updateShip(this->Team_name,"Corvette",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                        this->Ship_upgrade=true;
                        uS.push(ship);
                        return;
                    }
                }else if (targetShip->Ship_lives == 1 && targetShip->Ship_die==false) {
                    targetShip->Ship_die=true;
                    mof << targetName << " is eliminated by "<<this->Ship_name<< "!" << std::endl;
                    std::cout<< targetName << " is eliminated by "<<this->Ship_name<< "!" << std::endl;
                    ships.deleteNode(targetShip);
                    field.FieldBack(targetY, targetX);
                    this->Ship_kill_count++;
                    if(this->Ship_kill_count==3){
                        mof << this->Ship_name << " upgrade to Corvette!" << std::endl;
                        std::cout << this->Ship_name << " upgrade to Corvette!" << std::endl;
                        Ship* ship=updateShip(this->Team_name,"Corvette",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                        uS.push(ship);
                        return;
                    }
                }
            }else {
                mof << this->Ship_name << " shoots at (" << targetX << "," << targetY << ") and missed the shot.." << std::endl;
                std::cout<< this->Ship_name << " shoots at (" << targetX << "," << targetY << ") and missed the shot.." << std::endl;
            }
            //Increment reocrd to make Frigate shoot the next postion clock wise
            record++;
            this->targetX = this->posX + directions[this->record][0];
            this->targetY = this->posY + directions[this->record][1];
            //If the shooting position is outside battlefield , reset to first position clockwise
            if(targetX<0||targetY<0||targetX>9||targetY>9){
                this->ShootPosition=false;
            }
        }
    }

void Frigate::actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
    mof << this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << std::endl;
    std::cout<< this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << std::endl;
    shoot(field, ships, DESships,uS);
    mof<<std::endl;
    std::cout<<std::endl;
}

//Frigate--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Corvette--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Corvette::Corvette(char Team_name,std::string Ship_name,int posX,int posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
        this->Team_name = Team_name;
        this->Ship_name = Ship_name;
        this->Ship_type = "Corvette";
        this->Ship_lives=3;
        this->posX = posX;
        this->posY = posY;
}

void Corvette::updateF(Field& field){
    field.updateField(this,this->posY,this->posX);
    }

void Corvette::shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
        int x=0,y=0;
        int shots=2;
        int max_X = 1;
        int max_Y = 1;
        int CalX,CalY;
        for(int i=0;i<shots;i++){
            x = (rand() % 3)-1;
            y = (rand() % 3)-1;
            while(x>max_X || y>max_Y || this->posX+x>9 || this->posX+x<0 || this->posY+y>9 || this->posY+y<0 || x==0 || y==0 || ships.findShipTeam(posX+x,posY+y)==this->Team_name){ 
                x = (rand() % 3)-1;
                y = (rand() % 3)-1;
                CalX=abs(x);
                CalY=abs(y);
            }
            if(ships.findShipTeam(posX+x,posY+y)!=this->Team_name || field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1"){
                if(field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1" ){
                    mof << this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<std::endl;
                    std::cout<< this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<std::endl;
                }
                if(field.checkCell(this->posY+y,this->posX+x)==ships.findShipname(this->posX+x,this->posY+y)){
                    mof << this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<std::endl;
                    std::cout<< this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<std::endl;
                    if(ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives>1){
                    ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives--;
                    this->Ship_kill_count++;
                    mof<<ships.findShipname(this->posX+x,this->posY+y)<<" remain "<<ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives <<" lives."<<std::endl;;
                    std::cout<<ships.findShipname(this->posX+x,this->posY+y)<<" remain "<<ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives <<" lives."<<std::endl;;
                    if(ships.findShipPtr(this->posX+x,this->posY+y)->Ship_upgrade==false){
                        DESships.enqueue(ships.findShipPtr(this->posX+x,this->posY+y));
                    }
                    ships.deleteNode(ships.findShipPtr(this->posX+x,this->posY+y));
                    field.FieldBack(this->posY+y,this->posX+x);
                    }else if(ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives==1 && ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==false){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                        mof << this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<std::endl;
                        std::cout<< this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<std::endl;
                        ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                        field.FieldBack(posY+y,posX+x);
                    }
                }
            }  
        }
}
void Corvette::actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
    if(!this->ShootPosition){
            updateF(field);
            this->ShootPosition=true;
        }
    mof << this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << std::endl;
    std::cout<< this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << std::endl;
    shoot(field, ships, DESships,uS);
}
//Corvette--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//Amphibious--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Amphibious::Amphibious(char Team_name,std::string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
        this->Team_name = Team_name;
        this->Ship_name = Ship_name;
        this->Ship_type = "Amphibious";
        while(true){
            this->posX = rand()%10;
            this->posY = rand()%10;
            if(field.checkCell(posY,posX)=="0"){
                field.updateField(this,posY,posX);
                break;
            }
        }
}
void Amphibious::look(Field& field,LinkedList& ships) {
    int startingX=0,endingX=0,startingY=0,endingY=0;
        int NewP=0;
        if( this->posX-1<0 || this->posY-1<0 || this->posX+2>9 || this->posY+2>9){
            if(this->posX-1<0 && this->posY-1<0){ 
                startingX=this->posX;
                startingY=this->posY;
                endingX=this->posX+2;
                endingY=this->posY+2;
            }else if(this->posX+2>9 && this->posY-1<0){ 
                startingX=this->posX-1;
                startingY=this->posY;
                endingX=this->posX+1;
                endingY=this->posY+2; 
            }else if(this->posX-1<0 && this->posY+2>9){
                startingX=this->posX;
                startingY=this->posY-1;
                endingX=this->posX+2;
                endingY=this->posY+1;    
            }else if(this->posX+2>9 && posY+2>9){
                startingX=this->posX-1;
                startingY=this->posY-1;
                endingX=this->posX+1;
                endingY=this->posY+1;  
            }else if(this->posX-1<0){
                startingX=this->posX;
                startingY=this->posY-1;
                endingX=this->posX+2;
                endingY=this->posY+2;  
            }else if(this->posY-1<0){
                startingX=this->posX-1;
                startingY=this->posY;
                endingX=this->posX+2;
                endingY=this->posY+2;  
            }else if(this->posX+2>9){
                startingX=this->posX-1;
                startingY=this->posY-1;
                endingX=this->posX+1;
                endingY=this->posY+2;  
            }else if(this->posY+2>9){
                startingX=this->posX-1;
                startingY=this->posY-1;
                endingX=this->posX+1;
                endingY=this->posY+1;  
            }
        }else{
            startingX = (this->posX)-1;
            endingX = (this->posX)+2;
            startingY = (this->posY)-1;
            endingY = (this->posY+2);
        }

        for(int row=startingY;row<endingY;row++){
            for(int column=startingX;column<endingX;column++){
                if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)!=this->Team_name){
                    mof<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<")" << std::endl;
                    std::cout<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<")" << std::endl;
                }else if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)==this->Team_name){
                    mof<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
                    std::cout<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
                }
                if(field.checkCell(row,column)=="0" ||field.checkCell(row,column)=="1"){
                    if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                        ++NewP;
                    }
                }
            }
        }
        if(NewP!=0){  
            CanMove = true;
            int decide = (rand() % NewP)+1;
            int reaching=0;
            for(int row=startingY;row<endingY;row++){
                for(int column=startingX;column<endingX;column++){
                    if(field.checkCell(row,column)=="0" || field.checkCell(row,column)=="1"){
                        if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                            if(reaching!=decide){
                                reaching++;
                                if(reaching==decide){
                                    this->nextX=column;
                                    this->nextY=row;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }else if(NewP==0){
            CanMove=false;
        }
}
void Amphibious:: move(Field& field,LinkedList& ships){
    if(CanMove){
            mof<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            std::cout<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< std::endl; 
            field.updateField(this,this->nextY,this->nextX);
            field.FieldBack(this->posY,this->posX);
            this->posX=this->nextX;
            this->posY=this->nextY;
            this->nextX=-1;
            this->nextY=-1;
            CanMove=false;
        }else{
            mof<<this->Ship_name<<" currently can't move." << std::endl;;
            std::cout<<this->Ship_name<<" currently can't move." << std::endl;;
        }
}
void Amphibious::shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) {
    int x=0,y=0;
        int shots=2;
        int max_range = 5;
        int calXY;
        for(int i=0;i<shots;i++){
            x = (rand() % 11)-5;
            y = (rand() % 11)-5;
            calXY = abs(x) + abs(y);
            while(calXY>max_range || this->posX+x>9 || this->posX+x<0 || this->posY+y>9 || this->posY+y<0 || x==0 || y==0 || ships.findShipTeam(posX+x,posY+y)==this->Team_name){ //if not less than 5
            x = (rand() % 11)-5;
            y = (rand() % 11)-5;
            calXY = abs(x) + abs(y);
            }
            if(ships.findShipTeam(posX+x,posY+y)!=this->Team_name || field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1"){
                if(field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1" ){
                    mof << this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<std::endl;
                    std::cout<< this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<std::endl;
                }
                if(field.checkCell(posY+y,posX+x)==ships.findShipname(posX+x,posY+y)){
                    mof << this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<std::endl;
                    std::cout<< this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<std::endl;
                    if(ships.findShipPtr(posX+x,posY+y)->Ship_lives>1){
                    ships.findShipPtr(posX+x,posY+y)->Ship_lives--;
                    this->Ship_kill_count++;
                    mof<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<std::endl;;
                    std::cout<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<std::endl;;
                    if(ships.findShipPtr(posX+x,posY+y)->Ship_upgrade==false){
                        DESships.enqueue(ships.findShipPtr(posX+x,posY+y));
                    }
                    ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                    field.FieldBack(posY+y,posX+x);
                        if(this->Ship_kill_count==4){
                            mof << this->Ship_name << " upgrade to SuperShip!" << std::endl;
                            std::cout<< this->Ship_name << " upgrade to SuperShip!" << std::endl;
                            Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                            this->Ship_upgrade=true;
                            uS.push(ship);
                            break;                            }
                    }else if(ships.findShipPtr(posX+x,posY+y)->Ship_lives==1 && ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==false){
                        ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==true;
                        mof << this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<std::endl;
                        std::cout<< this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<std::endl;
                        ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                        field.FieldBack(posY+y,posX+x);
                            if(this->Ship_kill_count==4){
                            mof << this->Ship_name << " upgrade to SuperShip!" << std::endl;
                            std::cout<< this->Ship_name << " upgrade to SuperShip!" << std::endl;
                            Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                            this->Ship_upgrade=true;
                            uS.push(ship);
                            break;
                            }  
                    }
                }
            }  
        }
}
void Amphibious::actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
        mof<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< std::endl;
        std::cout<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< std::endl;
        look(field,ships);
        move(field,ships);
        shoot(field,ships,DESships,uS);
        mof<<std::endl;
        std::cout<<std::endl;
    }

//Amphibious--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SuperShip::SuperShip(char Team_name,std::string Ship_name,int posX,int posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
        this->Team_name = Team_name;
        this->Ship_name = Ship_name;
        this->Ship_lives=3;
        this->Ship_type = "SuperShip";
        this->posX = posX;
        this->posY = posY;
}

void SuperShip::updateF(Field& field){
    field.updateField(this,this->posY,this->posX);
}

void SuperShip::look(Field& field,LinkedList& ships) {
    int startingX=0,endingX=0,startingY=0,endingY=0;
        int NewP=0;
        if( this->posX-1<0 || this->posY-1<0 || this->posX+2>9 || this->posY+2>9){
            if(this->posX-1<0 && this->posY-1<0){ //top left
                startingX=this->posX;
                startingY=this->posY;
                endingX=this->posX+2;
                endingY=this->posY+2;
            }else if(this->posX+2>9 && this->posY-1<0){ //top right
                startingX=this->posX-1;
                startingY=this->posY;
                endingX=this->posX+1;
                endingY=this->posY+2; 
            }else if(this->posX-1<0 && this->posY+2>9){
                startingX=this->posX;
                startingY=this->posY-1;
                endingX=this->posX+2;
                endingY=this->posY+1;    
            }else if(this->posX+2>9 && posY+2>9){
                startingX=this->posX-1;
                startingY=this->posY-1;
                endingX=this->posX+1;
                endingY=this->posY+1;  
            }else if(this->posX-1<0){
                startingX=this->posX;
                startingY=this->posY-1;
                endingX=this->posX+2;
                endingY=this->posY+2;  
            }else if(this->posY-1<0){
                startingX=this->posX-1;
                startingY=this->posY;
                endingX=this->posX+2;
                endingY=this->posY+2;  
            }else if(this->posX+2>9){
                startingX=this->posX-1;
                startingY=this->posY-1;
                endingX=this->posX+1;
                endingY=this->posY+2;  
            }else if(this->posY+2>9){
                startingX=this->posX-1;
                startingY=this->posY-1;
                endingX=this->posX+1;
                endingY=this->posY+1;  
            }
        }else{
            startingX = (this->posX)-1;
            endingX = (this->posX)+2;
            startingY = (this->posY)-1;
            endingY = (this->posY+2);
        }

        for(int row=startingY;row<endingY;row++){
            for(int column=startingX;column<endingX;column++){
                if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)!=this->Team_name){
                    mof<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
                    std::cout<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
                    if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                    this->nextX=column;
                    this->nextY=row;
                    NewP=0;
                    break;
                    }
                }else if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)==this->Team_name){
                    mof<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
                    std::cout<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << std::endl;
                }
                if(field.checkCell(row,column)=="0" || (field.checkCell(row,column)!=this->Ship_name && ships.findShipTeam(column,row)==this->Team_name)){
                    if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                        ++NewP;
                    }
                }
            }
        }
        if(NewP!=0){  
            CanMove = true;
            int decide = (rand() % NewP)+1;
            int reaching=0;
            for(int row=startingY;row<endingY;row++){
                for(int column=startingX;column<endingX;column++){
                    if(field.checkCell(row,column)!="1"){
                        if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                            if(reaching!=decide){
                                reaching++;
                                if(reaching==decide){
                                    this->nextX=column;
                                    this->nextY=row;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }else if(NewP==0){
            CanMove=true;
        }
}

void SuperShip::step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
    if(CanMove){
            if(ships.findShipTeam(this->nextX,this->nextY)==this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
                mof<<this->Ship_name<<" step on fristd::endly ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< std::endl; 
                std::cout<<this->Ship_name<<" step on fristd::endly ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< std::endl; 
                if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                    ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                    mof<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<std::endl;
                    std::cout<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<std::endl;
                    if(ships.findShipPtr(this->nextX,this->nextY)->Ship_upgrade==false){
                        DESships.enqueue(ships.findShipPtr(this->nextX,this->nextY));
                    }
                    ships.deleteNode(ships.findShipPtr(this->nextX,this->nextY));
                    field.updateField(this,this->nextY,this->nextX);
                    field.FieldBack(this->posY,this->posX);
                    this->posX=this->nextX;
                    this->posY=this->nextY;
                    this->nextX=-1;
                    this->nextY=-1;
                    CanMove=false;
                }else if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives==1 && ships.findShipPtr(this->nextX,this->nextY)->Ship_die==false){
                    ships.findShipPtr(this->nextX,this->nextY)->Ship_die==true;
                    mof << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << std::endl;
                    std::cout<< this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << std::endl;
                    ships.deleteNode(ships.findShipPtr(this->nextX,this->nextY));
                    field.updateField(this,this->nextY,this->nextX);
                    field.FieldBack(this->posY,this->posX);
                    this->posX=this->nextX;
                    this->posY=this->nextY;
                    this->nextX=-1;
                    this->nextY=-1;
                    CanMove=false;
                }
            }else if(ships.findShipTeam(this->nextX,this->nextY)!=this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
                mof<<this->Ship_name<<" step on enemy ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< std::endl; 
                std::cout<<this->Ship_name<<" step on enemy ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< std::endl; 
                if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                    ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                    mof<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<std::endl;
                    std::cout<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<std::endl;
                    if(ships.findShipPtr(this->nextX,this->nextY)->Ship_upgrade==false){
                        DESships.enqueue(ships.findShipPtr(this->nextX,this->nextY));
                    }
                    ships.deleteNode(ships.findShipPtr(this->nextX,this->nextY));
                    field.updateField(this,this->nextY,this->nextX);
                    field.FieldBack(this->posY,this->posX);
                    this->posX=this->nextX;
                    this->posY=this->nextY;
                    this->nextX=-1;
                    this->nextY=-1;
                    CanMove=false;
                }else if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives==1 && ships.findShipPtr(this->nextX,this->nextY)->Ship_die==false){
                    ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                    mof << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << std::endl;
                    std::cout<< this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << std::endl;
                    ships.deleteNode(ships.findShipPtr(this->nextX,this->nextY));
                    field.updateField(this,this->nextY,this->nextX);
                    field.FieldBack(this->posY,this->posX);
                    this->posX=this->nextX;
                    this->posY=this->nextY;
                    this->nextX=-1;
                    this->nextY=-1;
                    CanMove=false;
                    this->Ship_kill_count++;
                }
            }else if(field.checkCell(this->nextY,this->nextX)=="0"){
                mof<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< std::endl; 
                std::cout<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< std::endl; 
                field.updateField(this,this->nextY,this->nextX);
                field.FieldBack(this->posY,this->posX);
                this->posX=this->nextX;
                this->posY=this->nextY;
                this->nextX=-1;
                this->nextY=-1;
                CanMove=false;
            }
        }else{
            mof<<this->Ship_type<<" is bugging" << std::endl;
            std::cout<<this->Ship_type<<" is bugging" << std::endl;
        }
}

void SuperShip::shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
    int x=0,y=0;
        int shots=3;
        int max_range = 5;
        int calXY;
        for(int i=0;i<shots;i++){
            x = (rand() % 11)-5;
            y = (rand() % 11)-5;
            calXY = abs(x) + abs(y);
            while(calXY>max_range || this->posX+x>9 || this->posX+x<0 || this->posY+y>9 || this->posY+y<0 || x==0 || y==0 || ships.findShipTeam(posX+x,posY+y)==this->Team_name){ //if not less than 5
            x = (rand() % 11)-5;
            y = (rand() % 11)-5;
            calXY = abs(x) + abs(y);
            }
            if(ships.findShipTeam(posX+x,posY+y)!=this->Team_name || field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1"){
                if(field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1" ){
                    mof << this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<std::endl;
                    std::cout<< this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<std::endl;
                }
                if(field.checkCell(posY+y,posX+x)==ships.findShipname(posX+x,posY+y)){
                    mof << this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<std::endl;
                    std::cout<< this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<std::endl;
                    if(ships.findShipPtr(posX+x,posY+y)->Ship_lives>1){
                        ships.findShipPtr(posX+x,posY+y)->Ship_lives--;
                        this->Ship_kill_count++;
                        mof<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<std::endl;;
                        std::cout<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<std::endl;;
                        if(ships.findShipPtr(posX+x,posY+y)->Ship_upgrade==false){
                            DESships.enqueue(ships.findShipPtr(posX+x,posY+y));
                        }
                        ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                        field.FieldBack(posY+y,posX+x);
                    }else if(ships.findShipPtr(posX+x,posY+y)->Ship_lives==1 && ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==false){
                        ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die=true;
                        mof << this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<std::endl;
                        std::cout<< this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<std::endl;
                        ships.deleteNode(ships.findShipPtr(posX+x,posY+y)); 
                        field.FieldBack(posY+y,posX+x);
                    }
                }
            }  
        }
}
void SuperShip::actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
        if(!this->ShootPosition){
            updateF(field);
            this->ShootPosition=true;
        }
        mof<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< std::endl;
        std::cout<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< std::endl;
        look(field,ships);
        step(field,ships,DESships,uS);
        if(this->Ship_upgrade){
            return;
        }
        shoot(field,ships,DESships,uS);
        mof<<std::endl;
        std::cout<<std::endl;
    }

//SuperShip--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//SniperShip--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SniperShip::SniperShip(char Team_name, std::string Ship_name,Field& field, LinkedList& ships, Queue& DESships,Stack& uS) {
    this->Team_name = Team_name;
    this->Ship_name = Ship_name;
    this->Ship_type = "SniperShip";
            while(true){
                this->posX = rand()%10;
                this->posY = rand()%10;
                if(field.checkCell(posY,posX)=="0"){
                    field.updateField(this,posY,posX);
                    break;
                }
            }
}

void SniperShip::look(Field& field, LinkedList& ships){
    //SniperShip look on the battlefield from top left to bottom right and select the first enemy as target.
    if (!targetLocked) {
        for (int row = 0; row < field.height; ++row) {
            for (int col = 0; col < field.width; ++col) {
                if (field.checkCell(row, col) != "0" && field.checkCell(row, col) != "1" && ships.findShipTeam(col, row) != this->Team_name) {
                    targetX = col;
                    targetY = row;
                    targetLocked = true;
                    mof << this->Ship_name << " locks onto target at (" << targetX << "," << targetY << ") and will shoot next turn!" << std::endl;
                    std::cout<< this->Ship_name << " locks onto target at (" << targetX << "," << targetY << ") and will shoot next turn!" << std::endl;
                    return;
                }
            }
        }
    }
}

void SniperShip::shoot(Field& field, LinkedList& ships, Queue& DESships,Stack& uS){
        if (targetLocked) {
            std::string targetName = ships.findShipname(targetX, targetY);
            if (targetName != "nothing" && ships.findShipTeam(targetX, targetY) != this->Team_name) {
                mof << this->Ship_name << " shoots at (" << targetX << "," << targetY << ") and hits " << targetName << "!" << std::endl;
                std::cout << this->Ship_name << " shoots at (" << targetX << "," << targetY << ") and hits " << targetName << "!" << std::endl;
                Ship* targetShip = ships.findShipPtr(targetX, targetY);
                if(targetShip->Ship_lives > 1){
                targetShip->Ship_lives--;
                mof<<targetName<<" remain " << targetShip->Ship_lives << " lives.";
                std::cout<<targetName<<" remain " << targetShip->Ship_lives << " lives.";
                if(targetShip->Ship_upgrade==false){
                    DESships.enqueue(targetShip);
                }
                ships.deleteNode(targetShip);
                field.FieldBack(targetY,targetX);
                }else if (targetShip->Ship_lives == 1 && targetShip->Ship_die==false) {
                    targetShip->Ship_die=true;
                    mof << targetName << " is destroyed!" << std::endl;
                    std::cout << targetName << " is destroyed!" << std::endl;
                    ships.deleteNode(targetShip);
                    field.FieldBack(targetY, targetX);
                }
            //If the target being destroyed , SniperShip will miss.
            } else {
                mof << this->Ship_name << " shoots at (" << targetX << "," << targetY << ") but the target disappear." << std::endl;
                std::cout<< this->Ship_name << " shoots at (" << targetX << "," << targetY << ") but the target disappear." << std::endl;
            }
            targetLocked = false; 
        }
}

void SniperShip::actions(Field& field, LinkedList& ships, Queue& DESships,Stack& uS) {
    if(this->record%2!=0 || this->record==0){
        mof << this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << std::endl;
        std::cout<< this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << std::endl;
        this->record++;
        look(field, ships);
    }else if(this->record%2==0 && this->record!=0){
        this->record++;
        mof << this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << std::endl;
        std::cout<< this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << std::endl;
        shoot(field, ships, DESships,uS);
        }else{
        mof<<"SniperShip Bugging lol." << std::endl;
        std::cout<<"SniperShip Bugging lol." << std::endl;
    }
        mof << std::endl;
        std::cout<< std::endl;
}

//SniperShip--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------