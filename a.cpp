#include <iostream>
#include <cstdlib>
#include<ctime>
#include <fstream>
using namespace std;


class Field;
class LinkedList;
class Queue;
class Stack;


//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Ship{
    public:
        bool CanMove;
        char Team_name;
        string Ship_name,Ship_type;
        int Ship_lives=3;
        int Ship_kill_count=0;
        int posX=-1,posY=-1,nextX=-1,nextY=-1;
        bool Ship_upgrade=false;
        bool ShootPosition=false;
        int record = 0;
        int targetX =-1;
        int targetY=-1;
        bool Ship_die = false;

        Ship(){}
        virtual ~Ship(){}
        virtual void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) = 0;
        static Ship* createShip(const char& Team_name,const string& Ship_Type,const string& Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS);
        static Ship* updateShip(const char& Team_name,const string& Ship_Type,const string& Ship_name,const int& posX,const int& posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS);
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Field{
    public:
        int width, height, rowCount, col;
        bool start_readFile;
        string ignore_line;
        string field[10][10];
        string backupfield[10][10];
        Field() : width(0), height(0), start_readFile(false), rowCount(0) {}

        void initialize(const string& filename) {
            ifstream file(filename);
            if (!file) {
                cout << "File not found" << endl;
                exit(1);
            }

            while (getline(file, ignore_line)) {
                if (!start_readFile) {
                    if (ignore_line[0] == '0') {
                        start_readFile = true;
                    } else {
                        continue;
                    }
                }

                if (start_readFile && rowCount < height) {
                    col = 0;
                    for (char c : ignore_line) {
                        if (c == '0' || c == '1') {
                            field[rowCount][col] = c;
                            backupfield[rowCount][col++] = c; //backup is ass so i put ++ here
                            if (col >= width) break;
                        }
                    }
                    rowCount++;
                }
            }
            file.close();
        }

        void printField() {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    cout << field[i][j];
                    if (field[i][j].length() == 1) {
                        cout << "  "; // Two spaces for single-character strings
                    } else {
                        cout << " "; // One space for multi-character strings
                    }
                }
                cout << endl;
            }
        }

        void printBackField() {
            for (int i = 0; i < height; ++i) {
                for (int j = 0; j < width; ++j) {
                    cout << backupfield[i][j];
                    if (backupfield[i][j].length() == 1) {
                        cout << "  "; // Two spaces for single-character strings
                    } else {
                        cout << " "; // One space for multi-character strings
                    }
                }
                cout << endl;
            }
        }

        void updateField(Ship* shipPtr, int y, int x) {
                field[y][x] = shipPtr->Ship_name;
        }

        void FieldBack(int y,int x){
            if(backupfield[y][x]=="0"){
                field[y][x] = '0';
            }else if(backupfield[y][x]=="1"){
                 field[y][x] = '1';
            }
        }
        string checkCell(int y, int x) {
            return field[y][x];
        }

};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class SeeingRobot : virtual public Ship{
    public:
        
        virtual void look(Field& field,LinkedList& ships)= 0;
};

class MovingShip : virtual public Ship{
    public:
        virtual void move(Field& field,LinkedList& ships)= 0;
};

class ShootingShip : virtual public Ship{
    public:
        virtual void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS)= 0;
};

class RamShip : virtual public Ship{
    public:
        virtual void step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS)= 0;
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Node{ 
    Ship* shipPtr;
    Node* next;
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class LinkedList{
    public:
        Node* head;
        LinkedList() : head(nullptr){} 

        
        ~LinkedList(){
            clear();
        }

        LinkedList(const LinkedList& other) : head(nullptr) {
            Node* temp = other.head;
            while (temp != nullptr) {
                append(temp->shipPtr);
                temp = temp->next;
            }
        }

        LinkedList& operator=(const LinkedList& other) {
            if (this == &other) return *this;
            clear();
            Node* temp = other.head;
            while (temp != nullptr) {
                append(temp->shipPtr);
                temp = temp->next;
            }
            return *this;
        }

        LinkedList(LinkedList&& other) noexcept : head(other.head) {
            other.head = nullptr;
        }

        LinkedList& operator=(LinkedList&& other) noexcept {
            if (this == &other) return *this;
            clear();
            head = other.head;
            other.head = nullptr;
            return *this;
        }

        void append(Ship* shipPtr){
            Node * newNode = new Node();
            newNode -> shipPtr = shipPtr; 
            newNode -> next = nullptr;

            if(head == nullptr){
                head = newNode;
            }else{
                Node* temp = head;
                while(temp -> next != nullptr){
                    temp = temp -> next;
                }
                temp -> next = newNode;
            }
        }

        void deleteNode(Ship* shipPtr){
            Node* temp = head;
            Node* prev = nullptr;

            while(temp != nullptr && temp -> shipPtr != shipPtr){
                prev = temp;
                temp = temp -> next;
            }

            if(temp == nullptr){
                return;
            }

            if(prev == nullptr){
                head = temp -> next;
            }else{
                prev -> next = temp -> next;
            }

            delete temp;
        }


        void clear() {
            Node* temp;
            while(head!=nullptr){
                temp = head;
                head = head -> next;
                delete temp;
            }
        }

        void display(){
            Node* temp = head;
            while(temp != nullptr){
                cout << temp -> shipPtr ->Team_name << " , " << temp -> shipPtr -> Ship_name << " , " << temp -> shipPtr -> Ship_type << " , in (" << temp->shipPtr->posX <<","<<temp->shipPtr->posY<<")"<< endl;
                temp = temp -> next;
            }
            cout << endl;
        }

        string findShipname(int x, int y) {
            Node* findptr = head;
            while (findptr != nullptr) {
                if (findptr->shipPtr->posX == x && findptr->shipPtr->posY == y) {
                    return findptr->shipPtr->Ship_name;
                }
                findptr = findptr->next;
            }
            return "nothing"; 
        }

        char findShipTeam(int x, int y) {
            Node* findteam = head;
            while (findteam != nullptr) {
                if (findteam->shipPtr->posX == x && findteam->shipPtr->posY == y) {
                    return findteam->shipPtr->Team_name;
                }
                findteam = findteam->next;
            }
            return '-';
        }

        Ship* findShipPtr(int x,int y){
             Node* findShipptr = head;
            while (findShipptr != nullptr) {
                if (findShipptr->shipPtr->posX == x && findShipptr->shipPtr->posY == y) {
                    return findShipptr->shipPtr;
                }
                findShipptr = findShipptr->next;
                }
            return nullptr;
        }

        bool remainTeam(char TeamName){
            Node* ptr = head;
            while (ptr != nullptr) {
                if (ptr->shipPtr->Team_name == TeamName) {
                    return true;
                }
                ptr = ptr->next;
                }
            return false;
        }

};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Stack{ // we should really just stay using queue
    private:
        struct Node{
            Ship* shipPtr;
            Node * next;
        };
        Node* top;
    public:
        int size=0;
        const int maxSize=5;
        Stack() : top(nullptr),size(0){}

        bool isEmpty() const{
            return top == nullptr;
        }
        bool isFull() const{
            return size>= maxSize;
        }

        void push(Ship* shipPtr){
            if(isFull()){
                cout<<"No gonna happen" << endl;
                return;
            }
            Node* newNode = new Node();
            newNode->shipPtr =shipPtr;
            newNode->next = top;
            top = newNode;
            size++;
            //cout << "checking " << size  << endl;
            }

        Ship* pop(){
            if(isEmpty()){
                cout<<"Stack empty dumbass your code suck" << endl;
                return nullptr;
            }
            Node*temp = top;
            Ship* shipPtr = top ->shipPtr;
            top = top->next;
            delete temp;
            size--;
            //cout << "check2 " << size  << endl;
            return shipPtr;
        }

        ~Stack(){
            while(!isEmpty()){
                pop();
            }
        }
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Queue{
    private:
        Node* front;
        Node* rear;
    public:
        Queue() : front(nullptr), rear(nullptr){} //do nothing

        ~Queue(){
            clear();
        }

        Queue(const Queue& other) : front(nullptr), rear(nullptr) {
            Node* temp = other.front;
            while (temp != nullptr) {
                enqueue(temp->shipPtr);
                temp = temp->next;
            }
        }

        Queue& operator=(const Queue& other) {
            if (this == &other) return *this;
            clear();
            Node* temp = other.front;
            while (temp != nullptr) {
                enqueue(temp->shipPtr);
                temp = temp->next;
            }
            return *this;
        }

        Queue(Queue&& other) noexcept : front(other.front), rear(other.rear) {
            other.front = nullptr;
            other.rear = nullptr;
        }

        Queue& operator=(Queue&& other) noexcept {
            if (this == &other) return *this;
            clear();
            front = other.front;
            rear = other.rear;
            other.front = nullptr;
            other.rear = nullptr;
            return *this;
        }

        void enqueue(Ship* shipPtr){
            Node * newNode = new Node();
            newNode -> shipPtr = shipPtr; 
            newNode -> next = nullptr;

            if(front == nullptr){
                front = newNode;
                rear = newNode;
            }else{
                rear -> next = newNode;
                rear = newNode;
            }
        }

        void dequeue(Field& field,LinkedList& ships){
            if(front == nullptr){
                return;
            }
            Node* temp = front;
            int newX, newY;
            do {
                newX = rand() % 10;
                newY = rand() % 10;
            } while (field.checkCell(newY, newX) != "0");
            temp->shipPtr->posX = newX;
            temp->shipPtr->posY = newY;
            cout << temp->shipPtr->Ship_name <<" return to battlefield at ("<<newX <<","<<newY<<") !"<<endl;
            field.updateField(temp->shipPtr, newY, newX);
            ships.append(temp->shipPtr);
            front = front -> next;
            delete temp;
        }

        bool WaitTeam(char teamName){
            Node* temp = front;
            while (temp != nullptr) {
                if (temp->shipPtr->Team_name == teamName) {
                    return true; 
                }
                temp = temp->next;
            }
            return false;
        }

    private:
        void clear() {
            Node* temp;
            while(front!=nullptr){
                temp = front;
                front = front -> next;
                delete temp;
            }
            rear = nullptr;
        }
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Battleship : public SeeingRobot,public MovingShip,public ShootingShip{
    public:
        Battleship(char Team_name,string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
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

        void look(Field& field,LinkedList& ships) override{
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
                        cout<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<")" << endl;
                    }else if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)==this->Team_name){
                        cout<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
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
        void move(Field& field,LinkedList& ships) override{
            if(CanMove){
                cout<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< endl; 
                field.updateField(this,this->nextY,this->nextX);
                field.FieldBack(this->posY,this->posX);
                this->posX=this->nextX;
                this->posY=this->nextY;
                this->nextX=-1;
                this->nextY=-1;
                CanMove=false;
            }else{
                cout<<this->Ship_name<<" currently can't move." <<endl;;
            }
        }
        void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{
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
                        cout << this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<endl;
                    }
                    if(field.checkCell(posY+y,posX+x)==ships.findShipname(posX+x,posY+y)){
                        cout << this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<endl;
                        if(ships.findShipPtr(posX+x,posY+y)->Ship_lives>1){
                        ships.findShipPtr(posX+x,posY+y)->Ship_lives--;
                        this->Ship_kill_count++;
                        cout<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<endl;
                        if(ships.findShipPtr(posX+x,posY+y)->Ship_upgrade==false){
                        DESships.enqueue(ships.findShipPtr(posX+x,posY+y));
                        }
                        ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                        field.FieldBack(posY+y,posX+x);
                        //4 to Ds
                            if(this->Ship_kill_count==4){
                                cout << this->Ship_name << " upgrade to Destroyer!" << endl;
                                Ship* ship=updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                                this->Ship_upgrade=true;
                                uS.push(ship);
                                break;
                                //(const char& Team_name,const string& Ship_Type,const string& Ship_name,const int& posX,const int& posY,Field& field,LinkedList& ships,Queue& DESships)
                            }
                        }else if(ships.findShipPtr(posX+x,posY+y)->Ship_lives==1 && ships.findShipPtr(posX+x,posY+y)->Ship_die==false){
                            ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die=true;
                            cout << this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<endl;
                            ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                            field.FieldBack(posY+y,posX+x);
                            if(this->Ship_kill_count==4){
                                cout << this->Ship_name << " upgrade to Destroyer!" << endl;
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
        void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{
            cout<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< endl;
            look(field,ships);
            move(field,ships);  
            shoot(field,ships,DESships,uS);
            cout<<endl;
        }
};

class Cruiser : public SeeingRobot,public RamShip{ //3 to Ds
    public:
        Cruiser(char Team_name,string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
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
   
        void look(Field& field,LinkedList& ships) override{
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
                        cout<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
                        if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                        this->nextX=column;
                        this->nextY=row;
                        NewP=0;
                        break;
                        }
                    }else if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)==this->Team_name){
                        cout<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
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
        void step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{
            if(CanMove){
                if(ships.findShipTeam(this->nextX,this->nextY)==this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
                    cout<<this->Ship_name<<" step on friendly ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< endl; 
                    if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                        cout<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<endl;
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
                                cout << this->Ship_name << " upgrade to Destroyer!" << endl;
                                Ship* ship=updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                                this->Ship_upgrade=true;
                                uS.push(ship);
                                return;
                            }
                    }else if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives==1 && ships.findShipPtr(this->nextX,this->nextY)->Ship_die==false){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                        cout << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << endl;
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
                            cout << this->Ship_name << " upgrade to Destroyer!" << endl;
                            Ship* ship=updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                            this->Ship_upgrade=true;
                            uS.push(ship);
                            return;
                        }
                    }
                }else if(ships.findShipTeam(this->nextX,this->nextY)!=this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
                    cout<<this->Ship_name<<" step on enemy ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< endl; 
                    if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                        cout<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<endl;
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
                                cout << this->Ship_name << " upgrade to Destroyer!" << endl;
                                Ship* ship=updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                                this->Ship_upgrade=true;
                                uS.push(ship);
                                return;
                            }
                    }else if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives==1 && ships.findShipPtr(this->nextX,this->nextY)->Ship_die==false){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                        cout << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << endl;
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
                            cout << this->Ship_name << " upgrade to Destroyer!" << endl;
                            Ship* ship = updateShip(this->Team_name,"Destroyer",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                            this->Ship_upgrade=true;
                            uS.push(ship);
                            return;
                        }
                    }
                }else if(field.checkCell(this->nextY,this->nextX)=="0"){
                    cout<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< endl; 
                    field.updateField(this,this->nextY,this->nextX);
                    field.FieldBack(this->posY,this->posX);
                    this->posX=this->nextX;
                    this->posY=this->nextY;
                    this->nextX=-1;
                    this->nextY=-1;
                    CanMove=false;
                }
            }else{
                cout<<this->Ship_type<<" is bugging" << endl;
            }
        }
        void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{
            cout<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< endl;
            look(field,ships);
            step(field,ships,DESships,uS);
            cout<<endl;
        }
        
};

class Destroyer : public SeeingRobot,public ShootingShip,public RamShip{ //3 to ss
    public:
        Destroyer(char Team_name,string Ship_name,int posX,int posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
            this->Ship_lives=3;
            this->Team_name = Team_name;
            this->Ship_name = Ship_name;
            this->Ship_type = "Destroyer";
            this->posX = posX;
            this->posY = posY;
        }
        void updateF(Field& field){
            field.updateField(this,this->posY,this->posX);
        }

        void look(Field& field,LinkedList& ships) override{
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
                        cout<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
                        if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                        this->nextX=column;
                        this->nextY=row;
                        NewP=0;
                        break;
                        }
                    }else if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)==this->Team_name){
                        cout<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
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
        void step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{
            if(CanMove){
                if(ships.findShipTeam(this->nextX,this->nextY)==this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
                    cout<<this->Ship_name<<" step on friendly ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< endl; 
                    if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                        cout<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<endl;
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
                                cout << this->Ship_name << " upgrade to SuperShip!" << endl;
                                Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                                this->Ship_upgrade=true;
                                uS.push(ship);
                                return;
                            }
                    }else if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives==1 && ships.findShipPtr(this->nextX,this->nextY)->Ship_die==false){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                        cout << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << endl;
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
                            cout << this->Ship_name << " upgrade to SuperShip!" << endl;
                            this->Ship_upgrade=true;
                            Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                            uS.push(ship);
                            return;
                        }
                    }
                }else if(ships.findShipTeam(this->nextX,this->nextY)!=this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
                    cout<<this->Ship_name<<" step on enemy ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< endl; 
                    if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                        cout<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<endl;
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
                                cout << this->Ship_name << " upgrade to SuperShip!" << endl;
                                Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                                this->Ship_upgrade=true;
                                uS.push(ship);
                                return;
                            }
                    }else if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives==1 && ships.findShipPtr(this->nextX,this->nextY)->Ship_die==false){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                        cout << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << endl;
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
                            cout << this->Ship_name << " upgrade to SuperShip!" << endl;
                            Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                            this->Ship_upgrade=true;
                            uS.push(ship);
                            return;
                        }
                    }
                }else if(field.checkCell(this->nextY,this->nextX)=="0"){
                    cout<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< endl; 
                    field.updateField(this,this->nextY,this->nextX);
                    field.FieldBack(this->posY,this->posX);
                    this->posX=this->nextX;
                    this->posY=this->nextY;
                    this->nextX=-1;
                    this->nextY=-1;
                    CanMove=false;
                }
            }else{
                cout<<this->Ship_type<<" is bugging" << endl;
            }
        }
        void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{
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
                        cout << this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<endl;
                    }else if(field.checkCell(posY+y,posX+x)==ships.findShipname(posX+x,posY+y)){
                        cout << this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<endl;
                        if(ships.findShipPtr(posX+x,posY+y)->Ship_lives>1){
                            ships.findShipPtr(posX+x,posY+y)->Ship_lives--;
                            this->Ship_kill_count++;
                            cout<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<endl;;
                            if(ships.findShipPtr(posX+x,posY+y)->Ship_upgrade==false){
                            DESships.enqueue(ships.findShipPtr(posX+x,posY+y));
                            }
                            ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                            field.FieldBack(posY+y,posX+x);
                            if(this->Ship_kill_count==3){
                                cout << this->Ship_name << " upgrade to SuperShip!" << endl;
                                Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                                this->Ship_upgrade=true;
                                uS.push(ship);
                                break;
                            }
                        }else if(ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives==1 && ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==false){
                            ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==true;
                            cout << this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<endl;
                            ships.deleteNode(ships.findShipPtr(this->posX+x,this->posY+y));
                            field.FieldBack(this->posY+y,this->posX+x);
                             if(this->Ship_kill_count==3){
                                cout << this->Ship_name << " upgrade to SuperShip!" << endl;
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
        void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{
            if(!this->ShootPosition){
                updateF(field);
                this->ShootPosition=true;
            }
            cout<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< endl;
            look(field,ships);
            step(field,ships,DESships,uS);
            if(this->Ship_upgrade){
                return;
            }
            shoot(field,ships,DESships,uS);
            cout<<endl;
        }
};

class Frigate : public ShootingShip{ //cannot move,look,clockwise shoot,3 to corvette
    public:
        Frigate(char Team_name,string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
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

        void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{ //sorry but i refuse
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
                        cout << this->Ship_name << " shoots at (" << targetX << "," << targetY << ") and hits enemy ship: " << targetName << "!" << endl;
                        Ship* targetShip = ships.findShipPtr(targetX, targetY);
                        targetShip->Ship_lives--;
                        if(targetShip->Ship_lives>1){
                        cout<<targetShip->Ship_name<<" remain "<<targetShip->Ship_lives << " lives." << endl;
                        if(targetShip->Ship_upgrade==false){
                        DESships.enqueue(targetShip);
                        }
                        ships.deleteNode(targetShip);
                        field.FieldBack(this->targetY, this->targetX);
                        this->Ship_kill_count++;
                            if(this->Ship_kill_count==3){
                                cout << this->Ship_name << " upgrade to Corvette!" << endl;
                                Ship* ship=updateShip(this->Team_name,"Corvette",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                                this->Ship_upgrade=true;
                                uS.push(ship);
                                return;
                            }
                        }else if (targetShip->Ship_lives == 1 && targetShip->Ship_die==false) {
                            targetShip->Ship_die=true;
                            cout << targetName << " is eliminated by "<<this->Ship_name<< "!" << endl;
                            ships.deleteNode(targetShip);
                            field.FieldBack(targetY, targetX);
                            this->Ship_kill_count++;
                            if(this->Ship_kill_count==3){
                                cout << this->Ship_name << " upgrade to Corvette!" << endl;
                                Ship* ship=updateShip(this->Team_name,"Corvette",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                                uS.push(ship);
                                return;
                            }
                        }
                    }else {
                        cout << this->Ship_name << " shoots at (" << targetX << "," << targetY << ") and missed the shot.." << endl;
                    }
                    record++;
                    this->targetX = this->posX + directions[this->record][0];
                    this->targetY = this->posY + directions[this->record][1];
                    if(targetX<0||targetY<0||targetX>9||targetY>9){
                        this->ShootPosition=false;
                    }
                }
            }

        void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{
            cout << this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << endl;
            shoot(field, ships, DESships,uS);
            cout<<endl;
        }
};

class Corvette : public ShootingShip{ //shoot surronding randomly
public:
    Corvette(char Team_name,string Ship_name,int posX,int posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
            this->Team_name = Team_name;
            this->Ship_name = Ship_name;
            this->Ship_type = "Corvette";
            this->Ship_lives=3;
            this->posX = posX;
            this->posY = posY;
    }

    void updateF(Field& field){
        field.updateField(this,this->posY,this->posX);
        }

    void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{
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
                        cout << this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<endl;
                    }
                    if(field.checkCell(this->posY+y,this->posX+x)==ships.findShipname(this->posX+x,this->posY+y)){
                        cout << this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<endl;
                        if(ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives>1){
                        ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives--;
                        this->Ship_kill_count++;
                        cout<<ships.findShipname(this->posX+x,this->posY+y)<<" remain "<<ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives <<" lives."<<endl;;
                        if(ships.findShipPtr(this->posX+x,this->posY+y)->Ship_upgrade==false){
                            DESships.enqueue(ships.findShipPtr(this->posX+x,this->posY+y));
                        }
                        ships.deleteNode(ships.findShipPtr(this->posX+x,this->posY+y));
                        field.FieldBack(this->posY+y,this->posX+x);
                        }else if(ships.findShipPtr(this->posX+x,this->posY+y)->Ship_lives==1 && ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==false){
                            ships.findShipPtr(this->nextX,this->nextY)->Ship_die=true;
                            cout << this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<endl;
                            ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                            field.FieldBack(posY+y,posX+x);
                        }
                    }
                }  
            }
    }
    void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{
        if(!this->ShootPosition){
                updateF(field);
                this->ShootPosition=true;
            }
        cout << this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << endl;
        shoot(field, ships, DESships,uS);
    }
};

class Amphibious: public SeeingRobot,public MovingShip,public ShootingShip{ //move to sea or islands,like bs,4 to ss
public:
    Amphibious(char Team_name,string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
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
    void look(Field& field,LinkedList& ships) override{
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
                        cout<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<")" << endl;
                    }else if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)==this->Team_name){
                        cout<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
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
    void move(Field& field,LinkedList& ships) override{
        if(CanMove){
                cout<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< endl; 
                field.updateField(this,this->nextY,this->nextX);
                field.FieldBack(this->posY,this->posX);
                this->posX=this->nextX;
                this->posY=this->nextY;
                this->nextX=-1;
                this->nextY=-1;
                CanMove=false;
            }else{
                cout<<this->Ship_name<<" currently can't move." << endl;;
            }
    }
    void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{
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
                        cout << this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<endl;
                    }
                    if(field.checkCell(posY+y,posX+x)==ships.findShipname(posX+x,posY+y)){
                        cout << this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<endl;
                        if(ships.findShipPtr(posX+x,posY+y)->Ship_lives>1){
                        ships.findShipPtr(posX+x,posY+y)->Ship_lives--;
                        this->Ship_kill_count++;
                        cout<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<endl;;
                        if(ships.findShipPtr(posX+x,posY+y)->Ship_upgrade==false){
                            DESships.enqueue(ships.findShipPtr(posX+x,posY+y));
                        }
                        ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                        field.FieldBack(posY+y,posX+x);
                        //4 to Ds
                            if(this->Ship_kill_count==4){
                                cout << this->Ship_name << " upgrade to SuperShip!" << endl;
                                Ship* ship=updateShip(this->Team_name,"SuperShip",this->Ship_name,this->posX,this->posY,field,ships,DESships,uS);
                                this->Ship_upgrade=true;
                                uS.push(ship);
                                break;
                                //(const char& Team_name,const string& Ship_Type,const string& Ship_name,const int& posX,const int& posY,Field& field,LinkedList& ships,Queue& DESships)
                            }
                        }else if(ships.findShipPtr(posX+x,posY+y)->Ship_lives==1 && ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==false){
                            ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==true;
                            cout << this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<endl;
                            ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                            field.FieldBack(posY+y,posX+x);
                             if(this->Ship_kill_count==4){
                                cout << this->Ship_name << " upgrade to SuperShip!" << endl;
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
    void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{
            cout<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< endl;
            look(field,ships);
            move(field,ships);
            shoot(field,ships,DESships,uS);
            cout<<endl;
        }
};

class SuperShip:public SeeingRobot,public RamShip,public ShootingShip{ //shoot 3
public:
    SuperShip(char Team_name,string Ship_name,int posX,int posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
            this->Team_name = Team_name;
            this->Ship_name = Ship_name;
            this->Ship_lives=3;
            this->Ship_type = "SuperShip";
            this->posX = posX;
            this->posY = posY;
    }

    void updateF(Field& field){
        field.updateField(this,this->posY,this->posX);
    }
    void look(Field& field,LinkedList& ships) override{
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
                        cout<<this->Ship_name<<" found Enemy ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
                        if( row==this->posY-1 && column==this->posX || row==posY+1 && column==this->posX || column==posX+1 && row==this->posY || column==posX-1 && row==this->posY){
                        this->nextX=column;
                        this->nextY=row;
                        NewP=0;
                        break;
                        }
                    }else if(field.checkCell(row,column)==ships.findShipname(column,row)&&field.checkCell(row,column)!=this->Ship_name&&ships.findShipTeam(column,row)==this->Team_name){
                        cout<<this->Ship_name<<" found Freindly Ship: "<<ships.findShipname(column,row)<<" at (" << column <<","<<row<<") " << endl;
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
    void step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{
        if(CanMove){
                if(ships.findShipTeam(this->nextX,this->nextY)==this->Team_name && field.checkCell(this->nextY,this->nextX)!="0"){
                    cout<<this->Ship_name<<" step on friendly ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< endl; 
                    if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                        cout<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<endl;
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
                        cout << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << endl;
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
                    cout<<this->Ship_name<<" step on enemy ship: "<<ships.findShipname(this->nextX,this->nextY)<< "(" << this->nextX << "," << this->nextY <<")"<< endl; 
                    if(ships.findShipPtr(this->nextX,this->nextY)->Ship_lives>1){
                        ships.findShipPtr(this->nextX,this->nextY)->Ship_lives--;
                        cout<<ships.findShipname(this->nextX,this->nextY)<<" remain "<<ships.findShipPtr(this->nextX,this->nextY)->Ship_lives <<" lives."<<endl;
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
                        cout << this->Ship_name << " step on " << field.checkCell(this->nextY,this->nextX) << " and eliminated it!" << endl;
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
                    cout<<this->Ship_name<<" move to (" << this->nextX << "," << this->nextY <<")"<< endl; 
                    field.updateField(this,this->nextY,this->nextX);
                    field.FieldBack(this->posY,this->posX);
                    this->posX=this->nextX;
                    this->posY=this->nextY;
                    this->nextX=-1;
                    this->nextY=-1;
                    CanMove=false;
                }
            }else{
                cout<<this->Ship_type<<" is bugging" << endl;
            }
    }
    void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{
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
                        cout << this->Ship_name << " decide to shoot at "<<"(" <<this->posX+x<<","<<this->posY+y<<") and missed." <<endl;
                    }
                    if(field.checkCell(posY+y,posX+x)==ships.findShipname(posX+x,posY+y)){
                        cout << this->Ship_name << " decide to shoot at "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") and successful!" <<endl;
                        if(ships.findShipPtr(posX+x,posY+y)->Ship_lives>1){
                            ships.findShipPtr(posX+x,posY+y)->Ship_lives--;
                            this->Ship_kill_count++;
                            cout<<ships.findShipname(posX+x,posY+y)<<" remain "<<ships.findShipPtr(posX+x,posY+y)->Ship_lives <<" lives."<<endl;;
                            if(ships.findShipPtr(posX+x,posY+y)->Ship_upgrade==false){
                                DESships.enqueue(ships.findShipPtr(posX+x,posY+y));
                            }
                            ships.deleteNode(ships.findShipPtr(posX+x,posY+y));
                            field.FieldBack(posY+y,posX+x);
                        }else if(ships.findShipPtr(posX+x,posY+y)->Ship_lives==1 && ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die==false){
                            ships.findShipPtr(this->posX+x,this->posY+y)->Ship_die=true;
                            cout << this->Ship_name << " eliminated "<<field.checkCell(posY+y,posX+x)<<"(" <<this->posX+x<<","<<this->posY+y<<") !" <<endl;
                            ships.deleteNode(ships.findShipPtr(posX+x,posY+y)); 
                            field.FieldBack(posY+y,posX+x);
                        }
                    }
                }  
            }
    }
    void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override{
            if(!this->ShootPosition){
                updateF(field);
                this->ShootPosition=true;
            }
            cout<<this->Ship_type<<" "<<this->Ship_name<<" from Team " << this->Team_name <<" at (" << this->posX<<","<<this->posY<<") start actions:"<< endl;
            look(field,ships);
            step(field,ships,DESships,uS);
            if(this->Ship_upgrade){
                return;
            }
            shoot(field,ships,DESships,uS);
            cout<<endl;
        }
};

class SniperShip : public SeeingRobot, public ShootingShip {
public:
    bool targetLocked;
    int targetX, targetY;

    SniperShip(char Team_name, string Ship_name,Field& field, LinkedList& ships, Queue& DESships,Stack& uS) {
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

    void look(Field& field, LinkedList& ships) override {
        if (!targetLocked) {
            for (int row = 0; row < field.height; ++row) {
                for (int col = 0; col < field.width; ++col) {
                    if (field.checkCell(row, col) != "0" && field.checkCell(row, col) != "1" && ships.findShipTeam(col, row) != this->Team_name) {
                        targetX = col;
                        targetY = row;
                        targetLocked = true;
                        cout << this->Ship_name << " locks onto target at (" << targetX << "," << targetY << ") and will shoot next turn!" << endl;
                        return;
                    }
                }
            }
        }
    }

    void shoot(Field& field, LinkedList& ships, Queue& DESships,Stack& uS) override {
            if (targetLocked) {
                string targetName = ships.findShipname(targetX, targetY);
                if (targetName != "nothing" && ships.findShipTeam(targetX, targetY) != this->Team_name) {
                    cout << this->Ship_name << " shoots at (" << targetX << "," << targetY << ") and hits " << targetName << "!" << endl;
                    Ship* targetShip = ships.findShipPtr(targetX, targetY);
                    if(targetShip->Ship_lives > 1){
                    targetShip->Ship_lives--;
                    cout<<targetName<<" remain " << targetShip->Ship_lives << " lives.";
                    if(targetShip->Ship_upgrade==false){
                        DESships.enqueue(targetShip);
                    }
                    ships.deleteNode(targetShip);
                    field.FieldBack(targetY,targetX);
                    }else if (targetShip->Ship_lives == 1 && targetShip->Ship_die==false) {
                        targetShip->Ship_die=true;
                        cout << targetName << " is destroyed!" << endl;
                        ships.deleteNode(targetShip);
                        field.FieldBack(targetY, targetX);
                    }
                } else {
                    cout << this->Ship_name << " shoots at (" << targetX << "," << targetY << ") but the target disappear." << endl;
                }
                targetLocked = false; 
            }
    }

    void actions(Field& field, LinkedList& ships, Queue& DESships,Stack& uS) override {
        if(this->record%2!=0 || this->record==0){
            cout << this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << endl;
            this->record++;
            look(field, ships);
        }else if(this->record%2==0 && this->record!=0){
            this->record++;
            cout << this->Ship_type << " " << this->Ship_name << " from Team " << this->Team_name << " at (" << this->posX << "," << this->posY << ") start actions:" << endl;
            shoot(field, ships, DESships,uS);
            }else{
            cout<<"SniperShip Bugging lol." << endl;
        }
            cout << endl;
    }
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Ship* Ship::createShip(const char& Team_name,const string& Ship_Type,const string& Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
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

Ship* Ship::updateShip(const char& Team_name,const string& Ship_Type,const string& Ship_name,const int& posX,const int& posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS){
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

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Simulation{
    private:
        string ignore_line, Ship_Type, Ship_symbol, Ship_Name;
        char Team_Name;
        int ships_count_in_Team, ship_num;
    public:
        int iterations;
        Queue DESships;
        Field field;
        LinkedList ships;
        Stack uS,uS2;
        Simulation() {
            ifstream file("game.txt");
            if (!file) {
                cout << "File not found" << endl;
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
                        Ship* ship = Ship::createShip(Team_Name, Ship_Type, Ship_Name = Ship_symbol + to_string(j + 1),field,ships,DESships,uS);
                        if (ship) {
                            ships.append(ship);
                        }
                    }
                }
            }
            Ship* amphibious1 = Ship::createShip ('B', "Amphibious", ";1", field, ships, DESships,uS);
            Ship* amphibious2 =  Ship::createShip('B', "Amphibious", ";2",  field, ships, DESships,uS);
            Ship* Sniper =  Ship::createShip('A', "SniperShip", "~S",  field, ships, DESships,uS);
            ships.append(amphibious1);
            ships.append(amphibious2);
            ships.append(Sniper);
            file.close();
            StartGame();
        }

        void StartGame(){
                bool upgrade=false;
                cout << "Initialize:" << endl;
                field.printField();
                for(int x=1;x<=iterations;x++){
                    cout << "Turn " << x << endl;
                    for(int j=0;j<2;j++){
                        DESships.dequeue(field,ships); 
                    }
                    cout<<endl;
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
                            cout<<endl;
                            cout<<"Team B win as Team A annihilated!" << endl;
                        }else if(ships.remainTeam('B')==false){
                            cout<<endl;
                            cout<<"Team A win as Team B annihilated!" << endl;
                        }
                        break;
                    }
                    if(x==iterations){
                    cout<<"Simulation end with time up." << endl;
                    break;
                    }
                }
                cout<<endl;
        }

        ~Simulation() {
            ships.clear();
        }
};



int main(){
    srand(time(0));
    Simulation sim;
    return 0;
}