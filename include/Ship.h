#ifndef SHIP_H
#define SHIP_H
#include <iostream>
using namespace std;
#include <fstream>

#include "LinkedList.h"
#include "Field.h"
#include "Queue.h"
#include "Stack.h"

class Field;
class LinkedList;
class Queue;
class Stack;
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
        virtual void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) = 0;
        static Ship* createShip(const char& Team_name,const string& Ship_Type,const string& Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof);
        static Ship* updateShip(const char& Team_name,const string& Ship_Type,const string& Ship_name,const int& posX,const int& posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof);
};

class SeeingRobot : virtual public Ship{
    public:
        virtual void look(Field& field,LinkedList& ships, ofstream& mof)= 0;
};

class MovingShip : virtual public Ship{
    public:
        virtual void move(Field& field,LinkedList& ships, ofstream& mof)= 0;
};

class ShootingShip : virtual public Ship{
    public:
        virtual void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof)= 0;
};

class RamShip : virtual public Ship{
    public:
        virtual void step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof)= 0;
};


class Battleship : public SeeingRobot,public MovingShip,public ShootingShip{
    public:
        Battleship(char Team_name,string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof);
        void look(Field& field,LinkedList& ships, ofstream& mof) override;
        void move(Field& field,LinkedList& ships, ofstream& mof) override;
        void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;
        void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;
    
};

class Cruiser : public SeeingRobot,public RamShip{
    public:
        Cruiser(char Team_name,string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof);
        void look(Field& field,LinkedList& ships, ofstream& mof) override;
        void step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;
        void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;
};

class Destroyer : public SeeingRobot,public ShootingShip,public RamShip{ //3 to ss
    public:
        Destroyer(char Team_name,string Ship_name,int posX,int posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof);
        void updateF(Field& field);
        void look(Field& field,LinkedList& ships, ofstream& mof) override;
        void step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;
        void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;
        void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;
};

class Frigate : public ShootingShip{
    public:
        Frigate(char Team_name,string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof);
        void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;
        void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;
};

class Corvette : public ShootingShip{ 
    public:
        Corvette(char Team_name,string Ship_name,int posX,int posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof);
        void updateF(Field& field);
        void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;
        void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;

};

class Amphibious: public SeeingRobot,public MovingShip,public ShootingShip{ //move to sea or islands,like bs,4 to ss
    public:
        Amphibious(char Team_name,string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof);
        void look(Field& field,LinkedList& ships, ofstream& mof) override;
        void move(Field& field,LinkedList& ships, ofstream& mof) override;
        void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;
        void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;
};

class SuperShip:public SeeingRobot,public RamShip,public ShootingShip{ //shoot 3
public:
    SuperShip(char Team_name,string Ship_name,int posX,int posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof);
    void updateF(Field& field);
    void look(Field& field,LinkedList& ships, ofstream& mof) override;
    void step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;
    void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;
    void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS, ofstream& mof) override;

};

class SniperShip : public SeeingRobot, public ShootingShip {
    protected:
        bool targetLocked;
        int targetX, targetY;
    public:
        SniperShip(char Team_name, string Ship_name,Field& field, LinkedList& ships, Queue& DESships,Stack& uS, ofstream& mof);
        void look(Field& field, LinkedList& ships, ofstream& mof) override;
        void shoot(Field& field, LinkedList& ships, Queue& DESships,Stack& uS, ofstream& mof) override;
        void actions(Field& field, LinkedList& ships, Queue& DESships,Stack& uS, ofstream& mof) override;
};

#endif