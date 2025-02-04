#include "Ship.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Field.h"
#include "Stack.h"
#include <fstream>
using namespace std;

Ship* Ship::createShip(const char& Team_name,const string& Ship_Type,const string& Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof){
            if(Ship_Type=="Battleship"){
                return new Battleship(Team_name,Ship_name,field,ships,DESships,uS, mof);
            }else if(Ship_Type=="Cruiser"){
                return new Cruiser(Team_name,Ship_name,field,ships,DESships,uS, mof);
            }else if(Ship_Type=="Frigate"){
                return new Frigate(Team_name,Ship_name,field,ships,DESships,uS, mof);
            }else if(Ship_Type=="Amphibious"){
                return new Amphibious(Team_name,Ship_name,field,ships,DESships,uS, mof);
            }else if(Ship_Type=="SniperShip"){
                return new SniperShip(Team_name,Ship_name,field,ships,DESships,uS, mof);
            }else{
                return nullptr;
            }
        }

Ship* Ship::updateShip(const char& Team_name,const string& Ship_Type,const string& Ship_name,const int& posX,const int& posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof){
            if(Ship_Type=="Destroyer"){
                return new Destroyer(Team_name,Ship_name,posX,posY,field,ships,DESships,uS, mof);
            }else if(Ship_Type=="Corvette"){
                return new Corvette(Team_name,Ship_name,posX,posY,field,ships,DESships,uS, mof);
            }else if(Ship_Type=="SuperShip"){
                return new SuperShip(Team_name,Ship_name,posX,posY,field,ships,DESships,uS, mof);
            }else{
                return nullptr;
            }
        }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Battleship::Battleship(char Team_name,string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof){
            //srand(time(0));
            this->Team_name = Team_name;
            this->Ship_name = Ship_name;
            this->Ship_type = "Battleship";
            while(true){
                this->posX = rand()%10;
                this->posY = rand()%10;
                if(field.checkCell(posY,posX)=="0"){
                    field.updateField(this,posY,posX);
                    break;
                }
            }
        }

void Battleship::look(Field& field,LinkedList& ships, ofstream& mof){
            int startingX=0,endingX=0,startingY=0,endingY=0;
            int NewP=0;
            //remember row , column left -> down! so y is row and x is column
            //for findShipname function,provide x first then y
            if( this->posX-1<0 || this->posY-1<0 || this->posX+2>9 || this->posY+2>9){
                if(this->posX-1<0 && this->posY-1<0){ //top left
                    //cout <<"Enter top left" << endl;
                    startingX=this->posX;
                    startingY=this->posY;
                    endingX=this->posX+2;
                    endingY=this->posY+2;
                }else if(this->posX+2>9 && this->posY-1<0){ //top right
                    //cout <<"Enter top right" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY;
                    endingX=this->posX+1;
                    endingY=this->posY+2; 
                }else if(this->posX-1<0 && this->posY+2>9){
                    //cout <<"Enter bottom left" << endl;
                    startingX=this->posX;
                    startingY=this->posY-1;
                    endingX=this->posX+2;
                    endingY=this->posY+1;    
                }else if(this->posX+2>9 && posY+2>9){
                    //cout <<"Enter bottom right" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY-1;
                    endingX=this->posX+1;
                    endingY=this->posY+1;  
                }else if(this->posX-1<0){
                    //cout <<"Enter left" << endl;
                    startingX=this->posX;
                    startingY=this->posY-1;
                    endingX=this->posX+2;
                    endingY=this->posY+2;  
                }else if(this->posY-1<0){
                    //cout <<"Enter top" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY;
                    endingX=this->posX+2;
                    endingY=this->posY+2;  
                }else if(this->posX+2>9){
                   //cout <<"Enter right" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY-1;
                    endingX=this->posX+1;
                    endingY=this->posY+2;  
                }else if(this->posY+2>9){
                    //cout <<"Enter down" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY-1;
                    endingX=this->posX+1;
                    endingY=this->posY+1;  
                }
            }else{
                //cout<<"Enter ram" << endl;
                startingX = (this->posX)-1;
                //cout << startingX << endl;
                endingX = (this->posX)+2;
                //cout << endingX << endl;
                startingY = (this->posY)-1;
                //cout << startingY << endl;
                endingY = (this->posY+2);
                //cout << endingY << endl;
            }

            for(int row=startingY;row<endingY;row++){
                for(int column=startingX;column<endingX;column++){
                    //cout <<column<<","<<row<<endl;
                    //cout<<ships.findShipname(column,row)<<endl;
                    if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)!=this->Team_name){
                        mof<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<")" << endl;
                    }else if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)==this->Team_name){
                        mof<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
                    }
                    if(field.checkCell(row,column)=="0"){
                        if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                            //cout<<this->Ship_name<<" can move to "<<column<<","<<row<<endl;
                            ++NewP;
                        }
                    }
                }
            }
            if(NewP!=0){  //laszy ass way to decide next move :)
                CanMove = true;
                int decide = (rand() % NewP)+1;
                //cout << decide << endl;
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
                                        //cout<<this->nextX<<" and "<<this->nextY;
                                        break;
                                    }
                                    //cout<<reaching<<endl;
                                }
                            }
                        }
                    }
                }
            }else if(NewP==0){
                CanMove=false;
            }
        }
void Battleship::move(Field& field,LinkedList& ships, ofstream& mof){
            if(CanMove){
                mof<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< endl; 
                field.updateField(this,this->nextY,this->nextX);
                field.FieldBack(this->posY,this->posX);
                this->posX=this->nextX;
                this->posY=this->nextY;
                this->nextX=-1;
                this->nextY=-1;
                CanMove=false;
            }else{
                mof<<this->Ship_name<<" currently can't move." <<endl;;
            }
        }
void Battleship::shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof){
            int x=0,y=0;
            int shots=2;
            int max_range = 5;
            int calXY;
            for(int i=0;i<shots;i++){
                x = (rand() % 11)-5;
                y = (rand() % 11)-5;
                calXY = abs(x) + abs(y); //initialize
                while(calXY>max_range || this->posX+x>9 || this->posX+x<0 || this->posY+y>9 || this->posY+y<0 || x==0 || y==0 || ships.findShipTeam(posX+x,posY+y)==this->Team_name){ //if not less than 5
                x = (rand() % 11)-5;
                y = (rand() % 11)-5;
                calXY = abs(x) + abs(y);
                }
                //cout <<x << " "<<y<<endl;
                if(ships.findShipTeam(posX+x,posY+y)!=this->Team_name || field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1"){
                    //cout <<x << " "<<y<<endl; //check not same team also check not itself hehe
                    if(field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1" ){
                        mof << this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<endl;
                    }
                    if(field.checkCell(posY+y,posX+x)==ships.findShipname(posX+x,posY+y)){
                        mof << this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<endl;
                        if(ships.findShipPtr(posX+x,posY+y)->Ship_lives>1){
                        ships.findShipPtr(posX+x,posY+y)->Ship_lives--;
                        this->Ship_kill_count++;
                        mof<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<endl;
                        if(ships.findShipPtr(posX+x,posY+y)->Ship_upgrade==false){
                        DESships.enqueue(ships.findShipPtr(posX+x,posY+y));
                        }
                        ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                        field.FieldBack(posY+y,posX+x);
                        //4 to Ds
                            if(this->Ship_kill_count==4){
                                mof << this->Ship_name << " upgrade to Destroyer!" << endl;
                                Ship* ship=updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                                this->Ship_upgrade=true;
                                uS.push(ship, mof);
                                break;
                                //(const char& Team_name,const string& Ship_Type,const string& Ship_name,const int& posX,const int& posY,Field& field,LinkedList& ships,Queue& DESships)
                            }
                        }else if(ships.findShipPtr(posX+x,posY+y)->Ship_lives==1 && ships.findShipPtr(posX+x,posY+y)->Ship_die==false){
                            ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die=true;
                            mof << this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<endl;
                            ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                            field.FieldBack(posY+y,posX+x);
                            if(this->Ship_kill_count==4){
                                mof << this->Ship_name << " upgrade to Destroyer!" << endl;
                                Ship* ship=updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                                this->Ship_upgrade=true;
                                uS.push(ship, mof);
                                break;
                            }  
                        }
                    }
                }  
            }
        }
void Battleship::actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof){
            mof<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< endl;
            look(field,ships, mof);
            move(field,ships, mof);  
            shoot(field,ships,DESships,uS, mof);
            mof<<endl;
        }


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Cruiser::Cruiser(char Team_name,string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof){
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
   
void Cruiser::look(Field& field,LinkedList& ships, ofstream& mof){
            int startingX=0,endingX=0,startingY=0,endingY=0;
            int NewP=0;
            //remember row , column left -> down! so y is row and x is column
            //for findShipname function,provide x first then y
            if( this->posX-1<0 || this->posY-1<0 || this->posX+2>9 || this->posY+2>9){
                if(this->posX-1<0 && this->posY-1<0){ //top left
                    //cout <<"Enter top left" << endl;
                    startingX=this->posX;
                    startingY=this->posY;
                    endingX=this->posX+2;
                    endingY=this->posY+2;
                }else if(this->posX+2>9 && this->posY-1<0){ //top right
                    //cout <<"Enter top right" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY;
                    endingX=this->posX+1;
                    endingY=this->posY+2; 
                }else if(this->posX-1<0 && this->posY+2>9){
                    //cout <<"Enter bottom left" << endl;
                    startingX=this->posX;
                    startingY=this->posY-1;
                    endingX=this->posX+2;
                    endingY=this->posY+1;    
                }else if(this->posX+2>9 && posY+2>9){
                    //cout <<"Enter bottom right" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY-1;
                    endingX=this->posX+1;
                    endingY=this->posY+1;  
                }else if(this->posX-1<0){
                    //cout <<"Enter left" << endl;
                    startingX=this->posX;
                    startingY=this->posY-1;
                    endingX=this->posX+2;
                    endingY=this->posY+2;  
                }else if(this->posY-1<0){
                    //cout <<"Enter top" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY;
                    endingX=this->posX+2;
                    endingY=this->posY+2;  
                }else if(this->posX+2>9){
                   //cout <<"Enter right" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY-1;
                    endingX=this->posX+1;
                    endingY=this->posY+2;  
                }else if(this->posY+2>9){
                    //cout <<"Enter down" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY-1;
                    endingX=this->posX+1;
                    endingY=this->posY+1;  
                }
            }else{
                //cout<<"Enter ram" << endl;
                startingX = (this->posX)-1;
                //cout << startingX << endl;
                endingX = (this->posX)+2;
                //cout << endingX << endl;
                startingY = (this->posY)-1;
                //cout << startingY << endl;
                endingY = (this->posY+2);
                //cout << endingY << endl;
            }

            for(int row=startingY;row<endingY;row++){
                for(int column=startingX;column<endingX;column++){
                    //cout <<column<<","<<row<<endl;
                    //cout<<ships.findShipname(column,row)<<endl;
                    if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)!=this->Team_name){
                        mof<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
                        if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                        this->nextX=column;
                        this->nextY=row;
                        NewP=0;
                        break;
                        }
                    }else if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)==this->Team_name){
                        mof<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
                    }
                    if(field.checkCell(row,column)=="0" || (field.checkCell(row,column)!=this->Ship_name && ships.findShipTeam(column,row)==this->Team_name)){
                        if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                            //cout<<this->Ship_name<<" can move to "<<column<<","<<row<<endl;
                            ++NewP;
                        }
                    }
                }
            }
            if(NewP!=0){  //laszy ass way to decide next move :)
                CanMove = true;
                int decide = (rand() % NewP)+1;
                //cout << decide << endl;
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
                                        //cout<<this->nextX<<" and "<<this->nextY;
                                        break;
                                    }
                                    //cout<<reaching<<endl;
                                }
                            }
                        }
                    }
                }
            }else if(NewP==0){
                CanMove=true;
            }
        }
void Cruiser::step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof){
            if(CanMove){
                if(ships.findShipTeam(this->nextX,this->nextY)==this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
                    mof<<this->Ship_name<<" step on friendly ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< endl; 
                    if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                        mof<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<endl;
                        //field.FieldBack(this->posY,this->posX);
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
                                mof << this->Ship_name << " upgrade to Destroyer!" << endl;
                                Ship* ship=updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                                this->Ship_upgrade=true;
                                uS.push(ship, mof);
                                return;
                            }
                    }else if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives==1 && ships.findShipPtr(this->nextX,this->nextY)->Ship_die==false){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                        mof << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << endl;
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
                            mof << this->Ship_name << " upgrade to Destroyer!" << endl;
                            Ship* ship=updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                            this->Ship_upgrade=true;
                            uS.push(ship, mof);
                            return;
                        }
                    }
                }else if(ships.findShipTeam(this->nextX,this->nextY)!=this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
                    mof<<this->Ship_name<<" step on enemy ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< endl; 
                    if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                        mof<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<endl;
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
                                mof << this->Ship_name << " upgrade to Destroyer!" << endl;
                                Ship* ship=updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                                this->Ship_upgrade=true;
                                uS.push(ship, mof);
                                return;
                            }
                    }else if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives==1 && ships.findShipPtr(this->nextX,this->nextY)->Ship_die==false){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                        mof << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << endl;
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
                            mof << this->Ship_name << " upgrade to Destroyer!" << endl;
                            Ship* ship = updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                            this->Ship_upgrade=true;
                            uS.push(ship, mof);
                            return;
                        }
                    }
                }else if(field.checkCell(this->nextY,this->nextX)=="0"){
                    mof<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< endl; 
                    field.updateField(this,this->nextY,this->nextX);
                    field.FieldBack(this->posY,this->posX);
                    this->posX=this->nextX;
                    this->posY=this->nextY;
                    this->nextX=-1;
                    this->nextY=-1;
                    CanMove=false;
                }
            }else{
                mof<<this->Ship_type<<" is bugging" << endl;
            }
        }
void Cruiser::actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof){
            mof<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< endl;
            look(field,ships, mof);
            step(field,ships,DESships,uS, mof);
            mof<<endl;
        }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Destroyer::Destroyer(char Team_name,string Ship_name,int posX,int posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof){
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

void Destroyer::look(Field& field,LinkedList& ships, ofstream& mof) {
            int startingX=0,endingX=0,startingY=0,endingY=0;
            int NewP=0;
            //remember row , column left -> down! so y is row and x is column
            //for findShipname function,provide x first then y
            if( this->posX-1<0 || this->posY-1<0 || this->posX+2>9 || this->posY+2>9){
                if(this->posX-1<0 && this->posY-1<0){ //top left
                    //cout <<"Enter top left" << endl;
                    startingX=this->posX;
                    startingY=this->posY;
                    endingX=this->posX+2;
                    endingY=this->posY+2;
                }else if(this->posX+2>9 && this->posY-1<0){ //top right
                    //cout <<"Enter top right" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY;
                    endingX=this->posX+1;
                    endingY=this->posY+2; 
                }else if(this->posX-1<0 && this->posY+2>9){
                    //cout <<"Enter bottom left" << endl;
                    startingX=this->posX;
                    startingY=this->posY-1;
                    endingX=this->posX+2;
                    endingY=this->posY+1;    
                }else if(this->posX+2>9 && posY+2>9){
                    //cout <<"Enter bottom right" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY-1;
                    endingX=this->posX+1;
                    endingY=this->posY+1;  
                }else if(this->posX-1<0){
                    //cout <<"Enter left" << endl;
                    startingX=this->posX;
                    startingY=this->posY-1;
                    endingX=this->posX+2;
                    endingY=this->posY+2;  
                }else if(this->posY-1<0){
                    //cout <<"Enter top" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY;
                    endingX=this->posX+2;
                    endingY=this->posY+2;  
                }else if(this->posX+2>9){
                   //cout <<"Enter right" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY-1;
                    endingX=this->posX+1;
                    endingY=this->posY+2;  
                }else if(this->posY+2>9){
                    //cout <<"Enter down" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY-1;
                    endingX=this->posX+1;
                    endingY=this->posY+1;  
                }
            }else{
                //cout<<"Enter ram" << endl;
                startingX = (this->posX)-1;
                //cout << startingX << endl;
                endingX = (this->posX)+2;
                //cout << endingX << endl;
                startingY = (this->posY)-1;
                //cout << startingY << endl;
                endingY = (this->posY+2);
                //cout << endingY << endl;
            }

            for(int row=startingY;row<endingY;row++){
                for(int column=startingX;column<endingX;column++){
                    //cout <<column<<","<<row<<endl;
                    //cout<<ships.findShipname(column,row)<<endl;
                    if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)!=this->Team_name){
                        mof<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
                        if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                        this->nextX=column;
                        this->nextY=row;
                        NewP=0;
                        break;
                        }
                    }else if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)==this->Team_name){
                        mof<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
                    }
                    if(field.checkCell(row,column)=="0" || (field.checkCell(row,column)!=this->Ship_name && ships.findShipTeam(column,row)==this->Team_name)){
                        if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                            //cout<<this->Ship_name<<" can move to "<<column<<","<<row<<endl;
                            ++NewP;
                        }
                    }
                }
            }
            if(NewP!=0){  //laszy ass way to decide next move :)
                CanMove = true;
                int decide = (rand() % NewP)+1;
                //cout << decide << endl;
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
                                        //cout<<this->nextX<<" and "<<this->nextY;
                                        break;
                                    }
                                    //cout<<reaching<<endl;
                                }
                            }
                        }
                    }
                }
            }else if(NewP==0){
                CanMove=true;
            }
        }
        void Destroyer::step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) {
            if(CanMove){
                if(ships.findShipTeam(this->nextX,this->nextY)==this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
                    mof<<this->Ship_name<<" step on friendly ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< endl; 
                    if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                        mof<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<endl;
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
                                mof << this->Ship_name << " upgrade to SuperShip!" << endl;
                                Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                                this->Ship_upgrade=true;
                                uS.push(ship, mof);
                                return;
                            }
                    }else if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives==1 && ships.findShipPtr(this->nextX,this->nextY)->Ship_die==false){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                        mof << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << endl;
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
                            mof << this->Ship_name << " upgrade to SuperShip!" << endl;
                            Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                            this->Ship_upgrade=true;
                            uS.push(ship, mof);
                            return;
                        }
                    }
                }else if(ships.findShipTeam(this->nextX,this->nextY)!=this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
                    mof<<this->Ship_name<<" step on enemy ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< endl; 
                    if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                        mof<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<endl;
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
                                mof << this->Ship_name << " upgrade to SuperShip!" << endl;
                                Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                                this->Ship_upgrade=true;
                                uS.push(ship, mof);
                                return;
                            }
                    }else if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives==1 && ships.findShipPtr(this->nextX,this->nextY)->Ship_die==false){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                        mof << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << endl;
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
                            mof << this->Ship_name << " upgrade to SuperShip!" << endl;
                            Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                            this->Ship_upgrade=true;
                            uS.push(ship, mof);
                            return;
                        }
                    }
                }else if(field.checkCell(this->nextY,this->nextX)=="0"){
                    mof<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< endl; 
                    field.updateField(this,this->nextY,this->nextX);
                    field.FieldBack(this->posY,this->posX);
                    this->posX=this->nextX;
                    this->posY=this->nextY;
                    this->nextX=-1;
                    this->nextY=-1;
                    CanMove=false;
                }
            }else{
                mof<<this->Ship_type<<" is bugging" << endl;
            }
        }
void Destroyer::shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) {
            int x=0,y=0;
            int shots=2;
            int max_range = 5;
            int calXY;
            for(int i=0;i<shots;i++){
                x = (rand() % 11)-5;
                y = (rand() % 11)-5;
                calXY = abs(x) + abs(y); //initialize
                while(calXY>max_range || this->posX+x>9 || this->posX+x<0 || this->posY+y>9 || this->posY+y<0 || x==0 || y==0 || ships.findShipTeam(posX+x,posY+y)==this->Team_name){ //if not less than 5
                x = (rand() % 11)-5;
                y = (rand() % 11)-5;
                calXY = abs(x) + abs(y);
                }
                //cout <<x << " "<<y<<endl;
                if(ships.findShipTeam(posX+x,posY+y)!=this->Team_name || field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1"){
                    //cout <<x << " "<<y<<endl; //check not same team also check not itself hehe
                    if(field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1" ){
                        mof << this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<endl;
                    }else if(field.checkCell(posY+y,posX+x)==ships.findShipname(posX+x,posY+y)){
                        mof << this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<endl;
                        if(ships.findShipPtr(posX+x,posY+y)->Ship_lives>1){
                            ships.findShipPtr(posX+x,posY+y)->Ship_lives--;
                            this->Ship_kill_count++;
                            mof<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<endl;;
                            if(ships.findShipPtr(posX+x,posY+y)->Ship_upgrade==false){
                            DESships.enqueue(ships.findShipPtr(posX+x,posY+y));
                            }
                            ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                            field.FieldBack(posY+y,posX+x);
                            if(this->Ship_kill_count==3){
                                mof << this->Ship_name << " upgrade to SuperShip!" << endl;
                                Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                                this->Ship_upgrade=true;
                                uS.push(ship, mof);
                                break;
                            }
                        }else if(ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives==1 && ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==false){
                            ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==true;
                            mof << this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<endl;
                            ships.deleteNode(ships.findShipPtr(this->posX+x,this->posY+y));
                            field.FieldBack(this->posY+y,this->posX+x);
                             if(this->Ship_kill_count==3){
                                mof << this->Ship_name << " upgrade to SuperShip!" << endl;
                                Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                                this->Ship_upgrade=true;
                                uS.push(ship, mof);
                                break;
                                }  
                        }
                    }
                }  
            }
        }

void Destroyer::actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) {
            if(!this->ShootPosition){
                updateF(field);
                this->ShootPosition=true;
            }
            mof<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< endl;
            look(field,ships, mof);
            step(field,ships,DESships,uS, mof);
            if(this->Ship_upgrade){
                return;
            }
            shoot(field,ships,DESships,uS, mof);
            mof<<endl;
        }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


Frigate::Frigate(char Team_name,string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof){
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

void Frigate::shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) { //sorry but i refuse
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
                        //cout<<i<< endl;
                        this->targetX = this->posX + directions[i][0];
                        this->targetY = this->posY + directions[i][1];
                        this->record = i;
                        this->ShootPosition=true;
                        break;
                    }
                }
            }

            if(this->ShootPosition){
                    string targetName = ships.findShipname(this->targetX, this->targetY);
                    if (targetName != "nothing" && ships.findShipTeam(this->targetX, this->targetY) != this->Team_name) {
                        mof << this->Ship_name << " shoots at (" << targetX << "," << targetY << ") and hits enemy ship: " << targetName << "!" << endl;
                        Ship* targetShip = ships.findShipPtr(targetX, targetY);
                        targetShip->Ship_lives--;
                        if(targetShip->Ship_lives>1){
                        mof<<targetShip->Ship_name<<" remain "<<targetShip->Ship_lives << " lives." << endl;
                        if(targetShip->Ship_upgrade==false){
                        DESships.enqueue(targetShip);
                        }
                        ships.deleteNode(targetShip);
                        field.FieldBack(this->targetY, this->targetX);
                        this->Ship_kill_count++;
                            if(this->Ship_kill_count==3){
                                mof << this->Ship_name << " upgrade to Corvette!" << endl;
                                Ship* ship=updateShip(this->Team_name,"Corvette",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                                this->Ship_upgrade=true;
                                uS.push(ship, mof);
                                return;
                            }
                        }else if (targetShip->Ship_lives == 1 && targetShip->Ship_die==false) {
                            targetShip->Ship_die=true;
                            mof << targetName << " is eliminated by "<<this->Ship_name<< "!" << endl;
                            ships.deleteNode(targetShip);
                            field.FieldBack(targetY, targetX);
                            this->Ship_kill_count++;
                            if(this->Ship_kill_count==3){
                                mof << this->Ship_name << " upgrade to Corvette!" << endl;
                                Ship* ship=updateShip(this->Team_name,"Corvette",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                                uS.push(ship, mof);
                                return;
                            }
                        }
                    }else {
                        mof << this->Ship_name << " shoots at (" << targetX << "," << targetY << ") and missed the shot.." << endl;
                    }
                    record++;
                    this->targetX = this->posX + directions[this->record][0];
                    this->targetY = this->posY + directions[this->record][1];
                    if(targetX<0||targetY<0||targetX>9||targetY>9){
                        this->ShootPosition=false;
                    }
                }
            }

void Frigate::actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) {
            mof << this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << endl;
            shoot(field, ships, DESships,uS, mof);
            mof<<endl;
        }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Corvette::Corvette(char Team_name,string Ship_name,int posX,int posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof){
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

void Corvette::shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof){
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
                        mof << this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<endl;
                    }
                    if(field.checkCell(this->posY+y,this->posX+x)==ships.findShipname(this->posX+x,this->posY+y)){
                        mof << this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<endl;
                        if(ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives>1){
                        ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives--;
                        this->Ship_kill_count++;
                        mof<<ships.findShipname(this->posX+x,this->posY+y)<<" remain "<<ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives <<" lives."<<endl;;
                        if(ships.findShipPtr(this->posX+x,this->posY+y)->Ship_upgrade==false){
                            DESships.enqueue(ships.findShipPtr(this->posX+x,this->posY+y));
                        }
                        ships.deleteNode(ships.findShipPtr(this->posX+x,this->posY+y));
                        field.FieldBack(this->posY+y,this->posX+x);
                        }else if(ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives==1 && ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==false){
                            ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                            mof << this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<endl;
                            ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                            field.FieldBack(posY+y,posX+x);
                        }
                    }
                }  
            }
    }
void Corvette::actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) {
        if(!this->ShootPosition){
                updateF(field);
                this->ShootPosition=true;
            }
        mof << this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << endl;
        shoot(field, ships, DESships,uS, mof);
    }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Amphibious::Amphibious(char Team_name,string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof){
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
void Amphibious::look(Field& field,LinkedList& ships, ofstream& mof){
        int startingX=0,endingX=0,startingY=0,endingY=0;
            int NewP=0;
            //remember row , column left -> down! so y is row and x is column
            //for findShipname function,provide x first then y
            if( this->posX-1<0 || this->posY-1<0 || this->posX+2>9 || this->posY+2>9){
                if(this->posX-1<0 && this->posY-1<0){ //top left
                    //cout <<"Enter top left" << endl;
                    startingX=this->posX;
                    startingY=this->posY;
                    endingX=this->posX+2;
                    endingY=this->posY+2;
                }else if(this->posX+2>9 && this->posY-1<0){ //top right
                    //cout <<"Enter top right" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY;
                    endingX=this->posX+1;
                    endingY=this->posY+2; 
                }else if(this->posX-1<0 && this->posY+2>9){
                    //cout <<"Enter bottom left" << endl;
                    startingX=this->posX;
                    startingY=this->posY-1;
                    endingX=this->posX+2;
                    endingY=this->posY+1;    
                }else if(this->posX+2>9 && posY+2>9){
                    //cout <<"Enter bottom right" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY-1;
                    endingX=this->posX+1;
                    endingY=this->posY+1;  
                }else if(this->posX-1<0){
                    //cout <<"Enter left" << endl;
                    startingX=this->posX;
                    startingY=this->posY-1;
                    endingX=this->posX+2;
                    endingY=this->posY+2;  
                }else if(this->posY-1<0){
                    //cout <<"Enter top" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY;
                    endingX=this->posX+2;
                    endingY=this->posY+2;  
                }else if(this->posX+2>9){
                   //cout <<"Enter right" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY-1;
                    endingX=this->posX+1;
                    endingY=this->posY+2;  
                }else if(this->posY+2>9){
                    //cout <<"Enter down" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY-1;
                    endingX=this->posX+1;
                    endingY=this->posY+1;  
                }
            }else{
                //cout<<"Enter ram" << endl;
                startingX = (this->posX)-1;
                //cout << startingX << endl;
                endingX = (this->posX)+2;
                //cout << endingX << endl;
                startingY = (this->posY)-1;
                //cout << startingY << endl;
                endingY = (this->posY+2);
                //cout << endingY << endl;
            }

            for(int row=startingY;row<endingY;row++){
                for(int column=startingX;column<endingX;column++){
                    //cout <<column<<","<<row<<endl;
                    //cout<<ships.findShipname(column,row)<<endl;
                    if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)!=this->Team_name){
                        mof<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<")" << endl;
                    }else if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)==this->Team_name){
                        mof<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
                    }
                    if(field.checkCell(row,column)=="0" ||field.checkCell(row,column)=="1"){
                        if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                            //cout<<this->Ship_name<<" can move to "<<column<<","<<row<<endl;
                            ++NewP;
                        }
                    }
                }
            }
            if(NewP!=0){  //laszy ass way to decide next move :)
                CanMove = true;
                int decide = (rand() % NewP)+1;
                //cout << decide << endl;
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
                                        //cout<<this->nextX<<" and "<<this->nextY;
                                        break;
                                    }
                                    //cout<<reaching<<endl;
                                }
                            }
                        }
                    }
                }
            }else if(NewP==0){
                CanMove=false;
            }
    }
void Amphibious::move(Field& field,LinkedList& ships, ofstream& mof){
        if(CanMove){
                mof<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< endl; 
                field.updateField(this,this->nextY,this->nextX);
                field.FieldBack(this->posY,this->posX);
                this->posX=this->nextX;
                this->posY=this->nextY;
                this->nextX=-1;
                this->nextY=-1;
                CanMove=false;
            }else{
                mof<<this->Ship_name<<" currently can't move." << endl;;
            }
    }

void Amphibious::shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) {
        int x=0,y=0;
            int shots=2;
            int max_range = 5;
            int calXY;
            for(int i=0;i<shots;i++){
                x = (rand() % 11)-5;
                y = (rand() % 11)-5;
                calXY = abs(x) + abs(y); //initialize
                while(calXY>max_range || this->posX+x>9 || this->posX+x<0 || this->posY+y>9 || this->posY+y<0 || x==0 || y==0 || ships.findShipTeam(posX+x,posY+y)==this->Team_name){ //if not less than 5
                x = (rand() % 11)-5;
                y = (rand() % 11)-5;
                calXY = abs(x) + abs(y);
                }
                //cout <<x << " "<<y<<endl;
                if(ships.findShipTeam(posX+x,posY+y)!=this->Team_name || field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1"){
                    //cout <<x << " "<<y<<endl; //check not same team also check not itself hehe
                    if(field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1" ){
                        mof << this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<endl;
                    }
                    if(field.checkCell(posY+y,posX+x)==ships.findShipname(posX+x,posY+y)){
                        mof << this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<endl;
                        if(ships.findShipPtr(posX+x,posY+y)->Ship_lives>1){
                        ships.findShipPtr(posX+x,posY+y)->Ship_lives--;
                        this->Ship_kill_count++;
                        mof<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<endl;;
                        if(ships.findShipPtr(posX+x,posY+y)->Ship_upgrade==false){
                            DESships.enqueue(ships.findShipPtr(posX+x,posY+y));
                        }
                        ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                        field.FieldBack(posY+y,posX+x);
                        //4 to Ds
                            if(this->Ship_kill_count==4){
                                mof << this->Ship_name << " upgrade to SuperShip!" << endl;
                                Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                                this->Ship_upgrade=true;
                                uS.push(ship, mof);
                                break;
                                //(const char& Team_name,const string& Ship_Type,const string& Ship_name,const int& posX,const int& posY,Field& field,LinkedList& ships,Queue& DESships)
                            }
                        }else if(ships.findShipPtr(posX+x,posY+y)->Ship_lives==1 && ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==false){
                            ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==true;
                            mof << this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<endl;
                            ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                            field.FieldBack(posY+y,posX+x);
                             if(this->Ship_kill_count==4){
                                mof << this->Ship_name << " upgrade to SuperShip!" << endl;
                                Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS, mof);
                                this->Ship_upgrade=true;
                                uS.push(ship, mof);
                                break;
                                }  
                        }
                    }
                }  
            }
    }

void Amphibious::actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) {
            mof<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< endl;
            look(field,ships, mof);
            move(field,ships, mof);
            shoot(field,ships,DESships,uS, mof);
            mof<<endl;
        }

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SuperShip::SuperShip(char Team_name,string Ship_name,int posX,int posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof){
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

void SuperShip::look(Field& field,LinkedList& ships, ofstream& mof){
        int startingX=0,endingX=0,startingY=0,endingY=0;
            int NewP=0;
            //remember row , column left -> down! so y is row and x is column
            //for findShipname function,provide x first then y
            if( this->posX-1<0 || this->posY-1<0 || this->posX+2>9 || this->posY+2>9){
                if(this->posX-1<0 && this->posY-1<0){ //top left
                    //cout <<"Enter top left" << endl;
                    startingX=this->posX;
                    startingY=this->posY;
                    endingX=this->posX+2;
                    endingY=this->posY+2;
                }else if(this->posX+2>9 && this->posY-1<0){ //top right
                    //cout <<"Enter top right" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY;
                    endingX=this->posX+1;
                    endingY=this->posY+2; 
                }else if(this->posX-1<0 && this->posY+2>9){
                    //cout <<"Enter bottom left" << endl;
                    startingX=this->posX;
                    startingY=this->posY-1;
                    endingX=this->posX+2;
                    endingY=this->posY+1;    
                }else if(this->posX+2>9 && posY+2>9){
                    //cout <<"Enter bottom right" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY-1;
                    endingX=this->posX+1;
                    endingY=this->posY+1;  
                }else if(this->posX-1<0){
                    //cout <<"Enter left" << endl;
                    startingX=this->posX;
                    startingY=this->posY-1;
                    endingX=this->posX+2;
                    endingY=this->posY+2;  
                }else if(this->posY-1<0){
                    //cout <<"Enter top" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY;
                    endingX=this->posX+2;
                    endingY=this->posY+2;  
                }else if(this->posX+2>9){
                   //cout <<"Enter right" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY-1;
                    endingX=this->posX+1;
                    endingY=this->posY+2;  
                }else if(this->posY+2>9){
                    //cout <<"Enter down" << endl;
                    startingX=this->posX-1;
                    startingY=this->posY-1;
                    endingX=this->posX+1;
                    endingY=this->posY+1;  
                }
            }else{
                //cout<<"Enter ram" << endl;
                startingX = (this->posX)-1;
                //cout << startingX << endl;
                endingX = (this->posX)+2;
                //cout << endingX << endl;
                startingY = (this->posY)-1;
                //cout << startingY << endl;
                endingY = (this->posY+2);
                //cout << endingY << endl;
            }

            for(int row=startingY;row<endingY;row++){
                for(int column=startingX;column<endingX;column++){
                    //cout <<column<<","<<row<<endl;
                    //cout<<ships.findShipname(column,row)<<endl;
                    if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)!=this->Team_name){
                        mof<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
                        if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                        this->nextX=column;
                        this->nextY=row;
                        NewP=0;
                        break;
                        }
                    }else if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)==this->Team_name){
                        mof<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
                    }
                    if(field.checkCell(row,column)=="0" || (field.checkCell(row,column)!=this->Ship_name && ships.findShipTeam(column,row)==this->Team_name)){
                        if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                            //cout<<this->Ship_name<<" can move to "<<column<<","<<row<<endl;
                            ++NewP;
                        }
                    }
                }
            }
            if(NewP!=0){  //laszy ass way to decide next move :)
                CanMove = true;
                int decide = (rand() % NewP)+1;
                //cout << decide << endl;
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
                                        //cout<<this->nextX<<" and "<<this->nextY;
                                        break;
                                    }
                                    //cout<<reaching<<endl;
                                }
                            }
                        }
                    }
                }
            }else if(NewP==0){
                CanMove=true;
            }
    }

void SuperShip::step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof){
        if(CanMove){
                if(ships.findShipTeam(this->nextX,this->nextY)==this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
                    mof<<this->Ship_name<<" step on friendly ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< endl; 
                    if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                        mof<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<endl;
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
                        mof << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << endl;
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
                    mof<<this->Ship_name<<" step on enemy ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< endl; 
                    if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                        mof<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<endl;
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
                        mof << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << endl;
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
                    mof<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< endl; 
                    field.updateField(this,this->nextY,this->nextX);
                    field.FieldBack(this->posY,this->posX);
                    this->posX=this->nextX;
                    this->posY=this->nextY;
                    this->nextX=-1;
                    this->nextY=-1;
                    CanMove=false;
                }
            }else{
                mof<<this->Ship_type<<" is bugging" << endl;
            }
    }
    
void SuperShip::shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) {
        int x=0,y=0;
            int shots=3;
            int max_range = 5;
            int calXY;
            for(int i=0;i<shots;i++){
                x = (rand() % 11)-5;
                y = (rand() % 11)-5;
                calXY = abs(x) + abs(y); //initialize
                while(calXY>max_range || this->posX+x>9 || this->posX+x<0 || this->posY+y>9 || this->posY+y<0 || x==0 || y==0 || ships.findShipTeam(posX+x,posY+y)==this->Team_name){ //if not less than 5
                x = (rand() % 11)-5;
                y = (rand() % 11)-5;
                calXY = abs(x) + abs(y);
                }
                //cout <<x << " "<<y<<endl;
                if(ships.findShipTeam(posX+x,posY+y)!=this->Team_name || field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1"){
                    if(field.checkCell(posY+y,posX+x)=="0" || field.checkCell(posY+y,posX+x)=="1" ){
                        mof << this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<endl;
                    }
                    if(field.checkCell(posY+y,posX+x)==ships.findShipname(posX+x,posY+y)){
                        mof << this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<endl;
                        if(ships.findShipPtr(posX+x,posY+y)->Ship_lives>1){
                            ships.findShipPtr(posX+x,posY+y)->Ship_lives--;
                            this->Ship_kill_count++;
                            mof<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<endl;;
                            if(ships.findShipPtr(posX+x,posY+y)->Ship_upgrade==false){
                                DESships.enqueue(ships.findShipPtr(posX+x,posY+y));
                            }
                            ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                            field.FieldBack(posY+y,posX+x);
                        }else if(ships.findShipPtr(posX+x,posY+y)->Ship_lives==1 && ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==false){
                            ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die=true;
                            mof << this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<endl;
                            ships.deleteNode(ships.findShipPtr(posX+x,posY+y)); 
                            field.FieldBack(posY+y,posX+x);
                        }
                    }
                }  
            }
    }

void SuperShip::actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) {
            if(!this->ShootPosition){
                updateF(field);
                this->ShootPosition=true;
            }
            mof<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< endl;
            look(field,ships, mof);
            step(field,ships,DESships,uS, mof);
            if(this->Ship_upgrade){
                return;
            }
            shoot(field,ships,DESships,uS, mof);
            mof<<endl;
        }


//--------------------------------------------------------------------------------------------------------------------------------------------

SniperShip::SniperShip(char Team_name, string Ship_name,Field& field, LinkedList& ships, Queue& DESships,Stack& uS, ofstream& mof) {
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

    void SniperShip::look(Field& field, LinkedList& ships, ofstream& mof) {
        if (!targetLocked) {
            for (int row = 0; row < field.height; ++row) {
                for (int col = 0; col < field.width; ++col) {
                    if (field.checkCell(row, col) != "0" && field.checkCell(row, col) != "1" && ships.findShipTeam(col, row) != this->Team_name) {
                        targetX = col;
                        targetY = row;
                        targetLocked = true;
                        mof << this->Ship_name << " locks onto target at (" << targetX << "," << targetY << ") and will shoot next turn!" << endl;
                        return;
                    }
                }
            }
        }
    }

    void SniperShip::shoot(Field& field, LinkedList& ships, Queue& DESships,Stack& uS, ofstream& mof) {
            if (targetLocked) {
                string targetName = ships.findShipname(targetX, targetY);
                if (targetName != "nothing" && ships.findShipTeam(targetX, targetY) != this->Team_name) {
                    mof << this->Ship_name << " shoots at (" << targetX << "," << targetY << ") and hits " << targetName << "!" << endl;
                    Ship* targetShip = ships.findShipPtr(targetX, targetY);
                    if(targetShip->Ship_lives > 1){
                    targetShip->Ship_lives--;
                    mof<<targetName<<" remain " << targetShip->Ship_lives << " lives.";
                    if(targetShip->Ship_upgrade==false){
                        DESships.enqueue(targetShip);
                    }
                    ships.deleteNode(targetShip);
                    field.FieldBack(targetY,targetX);
                    }else if (targetShip->Ship_lives == 1 && targetShip->Ship_die==false) {
                        targetShip->Ship_die=true;
                        mof << targetName << " is destroyed!" << endl;
                        ships.deleteNode(targetShip);
                        field.FieldBack(targetY, targetX);
                    }
                } else {
                    mof << this->Ship_name << " shoots at (" << targetX << "," << targetY << ") but the target disappear." << endl;
                }
                targetLocked = false; 
            }
    }

    void SniperShip::actions(Field& field, LinkedList& ships, Queue& DESships,Stack& uS, ofstream& mof)  {
        if(this->record%2!=0 || this->record==0){
            mof << this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << endl;
            this->record++;
            look(field, ships, mof);
        }else if(this->record%2==0 && this->record!=0){
            this->record++;
            mof << this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << endl;
            shoot(field, ships, DESships,uS, mof);
            }else{
            mof<<"SniperShip Bugging lol." << endl;
        }
            mof << endl;
    }