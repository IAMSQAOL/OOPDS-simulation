/**********|**********|**********|
Program: SHIP_TYPE.H
Course: Object Oriented Programming and Data Structures
Trimester: 2430
Name: YEE SI SHUN , GOH CHUN YONG , CHEAH CHUN YONG , LOKE KAR HEI
ID: 241UC24157 , 241UC24158 , 241UC2417G , 241UC24168
Lecture Section: TC1L
Tutorial Section: TT4L
Email: yee.si.shun@gstudent.mmu.edu.my , goh.chun.yong@student.mmu.edu.my , cheach.chun.yong@student.mmu.edu.my , loke.kar.hei@student.mmu.edu.my
Phone: 011-63303212 , 011-10758049 , 011-59252689 , 017-2900377
**********|**********|**********/

#ifndef SHIP_TYPE
#define SHIP_TYPE
#include "../include/SHIP.H"
#include <iostream>

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

class Battleship : public SeeingRobot,public MovingShip,public ShootingShip{
    public:
        Battleship(char Team_name,std::string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS);
        void look(Field& field,LinkedList& ships) override;
        void move(Field& field,LinkedList& ships) override;
        void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override;
        void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override;
};      

class Cruiser : public SeeingRobot,public RamShip{ //3 to Ds
    public:
        Cruiser(char Team_name,std::string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS);
        void look(Field& field,LinkedList& ships) override;
        void step(Field& field,LinkedList& ships,Queue& sDESships,Stack& uS) override;
        void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override;
        
};

class Destroyer : public SeeingRobot,public ShootingShip,public RamShip{ //3 to ss
    public:
        Destroyer(char Team_name,std::string Ship_name,int posX,int posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS);
        void updateF(Field& field);
        void look(Field& field,LinkedList& ships) override;
        void step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override;
        void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override;
        void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override;
};

class Frigate : public ShootingShip{ //cannot move,look,clockwise shoot,3 to corvette
    public:
        Frigate(char Team_name,std::string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS);

        void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override;
        void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override;
};

class Corvette : public ShootingShip{ //shoot surronding randomly
public:
    Corvette(char Team_name,std::string Ship_name,int posX,int posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS);

    void updateF(Field& field);

    void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override;
    void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override;
};

class Amphibious: public SeeingRobot,public MovingShip,public ShootingShip{ //move to sea or islands,like bs,4 to ss
public:
    Amphibious(char Team_name,std::string Ship_name,Field& field,LinkedList& ships,Queue& DESships,Stack& uS);
    void look(Field& field,LinkedList& ships) override;
    void move(Field& field,LinkedList& ships) override;
    void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override;
    void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override;
};

class SuperShip:public SeeingRobot,public RamShip,public ShootingShip{ //shoot 3
public:
    SuperShip(char Team_name,std::string Ship_name,int posX,int posY,Field& field,LinkedList& ships,Queue& DESships,Stack& uS);

    void updateF(Field& field);
    void look(Field& field,LinkedList& ships) override;
    void step(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override;
    void shoot(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override;
    void actions(Field& field,LinkedList& ships,Queue& DESships,Stack& uS) override;
};

class SniperShip : public SeeingRobot, public ShootingShip {
public:
    bool targetLocked;
    int targetX, targetY;

    SniperShip(char Team_name, std::string Ship_name,Field& field, LinkedList& ships, Queue& DESships,Stack& uS);

    void look(Field& field, LinkedList& ships) override;

    void shoot(Field& field, LinkedList& ships, Queue& DESships,Stack& uS) override;

    void actions(Field& field, LinkedList& ships, Queue& DESships,Stack& uS) override;
};

#endif