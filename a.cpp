#include <iostream>
#include <cstdlib>
#include <fstream>
using namespace std;

class Field;
class LinkedList;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Ship{
    public:
        char Team_name;
        string Ship_name,Ship_type;
        int Ship_lives=3;
        int Ship_kill_count=0;
        int posX=-1,posY=-1;
        bool Ship_upgrade=false;
        bool go_Up = false;
        bool go_Down = false;
        bool go_Left = false;
        bool go_Right = false;

        Ship(){}
        virtual ~Ship(){}
        virtual void actions(Field& field,LinkedList& ships) = 0;
        static Ship* createShip(const char& Team_name,const string& Ship_Type,const string& Ship_name,Field& field,LinkedList& ships);
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
class Field{
    public:
        int width, height, rowCount, col;
        bool start_readFile;
        string ignore_line;
        string field[10][10];

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
                            field[rowCount][col++] = c;
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

        void updateField(Ship* shipPtr, int y, int x) {
            if (y < 0 || y >= height || x < 0 || x >= width) return;
                field[y][x] = shipPtr->Ship_name;
        }

        string checkCell(int y, int x) {
            if (y < 0 || y >= height || x < 0 || x >= width) return "";
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
        virtual void shoot(Field& field,LinkedList& ships)= 0;
};

class RamShip : virtual public Ship{
    public:
        virtual void step(Field& field,LinkedList& ships)= 0;
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
        LinkedList() : head(nullptr){} //do nothing

        
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

        string foundShip(int x, int y) {
            Node* findaddress = head;
            while (findaddress != nullptr) {
                if (findaddress->shipPtr->posX == x && findaddress->shipPtr->posY == y) {
                    return findaddress->shipPtr->Ship_name;
                }
                findaddress = findaddress->next;
            }
            return "nothing"; // Return an empty string if no ship is found at the given position
        }
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Battleship : public SeeingRobot,public MovingShip,public ShootingShip{
    public:
        Battleship(char Team_name,string Ship_name,Field& field,LinkedList& ships){
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
            int startingX,endingX,startingY,endingY;
            //remember row , column left -> down! so y is row and x is column
            //for foundShip function,provide x first then y
            if( this->posX-1<0 || this->posY-1<0 || this->posX+2>10 || this->posY+2>9){
    
            }else{
                int startingX = (this->posX)-1;
                cout << startingX << endl;
                int endingX = (this->posX)+2;
                cout << endingX << endl;
                int startingY = (this->posY)-1;
                cout << startingY << endl;
                int endingY = (this->posY+2);
                cout << endingX << endl;
            }
            for(int row=startingY;row<endingY;row++){
                for(int column=startingX;row<endingY;column++){
                    if(field.checkCell(row,column)==ships.foundShip(column,row)){
                        cout<<this->Ship_name<<" found "<<ships.foundShip(column,row)<<" at (" << column <<","<<row<<") " << endl;
                    }
                }
            }
        }
        void move(Field& field,LinkedList& ships) override{}
        void shoot(Field& field,LinkedList& ships) override{}
        void actions(Field& field,LinkedList& ships) override{
            look(field,ships);
        }
};

class Cruiser : public SeeingRobot,public RamShip{
    public:
        Cruiser(char Team_name,string Ship_name,Field& field,LinkedList& ships){
            this->Team_name = Team_name;
            this->Ship_name = Ship_name;
            this->Ship_type = "Cruiser";
            while(true){
                this->posX = rand()%10;
                this->posY = rand()%10;
                if(field.checkCell(posX,posY)=="0"){
                    field.updateField(this,posX,posY);
                    break;
                }
            }
        }
   
        void look(Field& field,LinkedList& ships) override{}
        void step(Field& field,LinkedList& ships) override{}
        void actions(Field& field,LinkedList& ships) override{}
        
};

class Destroyer : public SeeingRobot,public ShootingShip,public RamShip{
    public:
        Destroyer(char Team_name,string Ship_name,Field& field,LinkedList& ships){
            this->Team_name = Team_name;
            this->Ship_name = Ship_name;
            this->Ship_type = "Destroyer";
             while(true){
                this->posX = rand()%10;
                this->posY = rand()%10;
                if(field.checkCell(posX,posY)=="0"){
                    field.updateField(this,posX,posY);
                    break;
                }
            }
        }

        void look(Field& field,LinkedList& ships) override{}
        void shoot(Field& field,LinkedList& ships) override{}
        void step(Field& field,LinkedList& ships) override{}
        void actions(Field& field,LinkedList& ships) override{}
};

class Frigate : public ShootingShip{
    public:
        Frigate(char Team_name,string Ship_name,Field& field,LinkedList& ships){
            this->Team_name = Team_name;
            this->Ship_name = Ship_name;
            this->Ship_type = "Frigate";
            while(true){
                this->posX = rand()%10;
                this->posY = rand()%10;
                if(field.checkCell(posX,posY)=="0"){
                    field.updateField(this,posX,posY);
                    break;
                }
            }
        }

        void shoot(Field& field,LinkedList& ships) override{}
        void actions(Field& field,LinkedList& ships) override{
        }
};

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Ship* Ship::createShip(const char& Team_name,const string& Ship_Type,const string& Ship_name,Field& field,LinkedList& ships){
            if(Ship_Type=="Battleship"){
                return new Battleship(Team_name,Ship_name,field,ships);
            }else if(Ship_Type=="Cruiser"){
                return new Cruiser(Team_name,Ship_name,field,ships);
            }else if(Ship_Type=="Destroyer"){
                return new Destroyer(Team_name,Ship_name,field,ships);
            }else if(Ship_Type=="Frigate"){
                return new Frigate(Team_name,Ship_name,field,ships);
            }else{
                return nullptr;
            }
        }

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

        void dequeue(){
            if(front == nullptr){
                return;
            }

            Node* temp = front;
            front = front -> next;
            delete temp;
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



class Simulation{
    private:
        string ignore_line, Ship_Type, Ship_symbol, Ship_Name;
        char Team_Name;
        int ships_count_in_Team, ship_num;
    public:
        int iterations;
        Field field;
        LinkedList ships;
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
                        Ship* ship = Ship::createShip(Team_Name, Ship_Type, Ship_Name = Ship_symbol + to_string(j + 1),field,ships);
                        if (ship) {
                            ships.append(ship);
                        }
                    }
                }
            }
            file.close();
        }

        ~Simulation() {
            ships.clear();
        }
};



int main(){
    Simulation sim;
    //sim.ships.display();
    cout << "Initialize:" << endl;
    sim.field.printField();
    for(int x=1;x<sim.iterations;x++){
        cout << "Turn " << x << endl;
        Node* temp = sim.ships.head;
        while(temp != nullptr){
            temp -> shipPtr -> actions(sim.field,sim.ships);
            temp = temp -> next;
        }
        sim.field.printField();
    }
    return 0;
}