#ifndef SHIP_H
#define SHIP_H

#include <string>
#include <iostream>
#include "Field.h"
#include <cstdlib>
#include <ctime>

class Ship {
public:
    int lives=3,posX=-1,posY=-1;
    std::string name;
    Field& field;
    Ship(const std::string& name,Field& field);
    virtual ~Ship() = 0; // Pure virtual destructor to make Ship an abstract class
    static Ship* createShip(const std::string& type, const std::string& name,Field& field); // Factory method to create ships
};

inline Ship::~Ship() {}

class MovingShip : virtual public Ship {
public: 
    MovingShip(){};
    MovingShip(const std::string& name,Field& field) : Ship(name,field) {}
    virtual void move() = 0; // Pure virtual function
};

class ShootingShip : virtual public Ship {
public:
    ShootingShip(){};
    ShootingShip(const std::string& name,Field& field) : Ship(name,field) {}
    virtual void shoot() = 0; // Pure virtual function
};

class SeeingRobot : virtual public Ship {
public:
    SeeingRobot(){};
    SeeingRobot(const std::string& name,Field& field) : Ship(name,field) {}
    virtual void see() = 0; // Pure virtual function
};

class RamShip : virtual public Ship {
public:
    RamShip(){};
    RamShip(const std::string& name,Field& field) : Ship(name,field){}
    virtual void step() = 0; // Pure virtual function
};

class Battleship : public SeeingRobot, public MovingShip, public ShootingShip {
public:
    Battleship(const std::string& name,Field& field);
    void see() override ;
    void move() override; 
    void shoot() override ;
   
};

class Cruiser : public SeeingRobot,public RamShip {
public:
    Cruiser(const std::string& name,Field& field) : Ship(name,field) {}
    void see() override ;
    void step() override ;
    
};

class Destroyer : public SeeingRobot, ShootingShip,public RamShip {
public:
    Destroyer(const std::string& name,Field& field) : Ship(name,field) {}
    void see() override ;
    void shoot() override ;
    void step() override ;

};

class Frigate : public ShootingShip{
public:
    Frigate(const std::string& name,Field& field) : Ship(name,field) {}
    void shoot() override ;
    

};

class Corvette : public ShootingShip {
public:
    Corvette(const std::string& name,Field& field) : Ship(name,field) {}
    void shoot() override ;

};

class Amphibious : public SeeingRobot,public MovingShip,public ShootingShip{
public:
    Amphibious(const std::string& name,Field& field) : Ship(name,field) {}
    void see() override ;
    void move() override ;
    void shoot() override ;

};

class SuperShip : public ShootingShip, public SeeingRobot, public RamShip {
public:
    SuperShip(const std::string& name,Field& field) : Ship(name,field) {}
    void shoot() override ;
    void see() override ;
    void step() override ;
};

#endif 