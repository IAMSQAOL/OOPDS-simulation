#include "Ship.h"


Ship* Ship::createShip(const std::string& type, const std::string& name,Field& field) {
    if (type == "Cruiser") {
        return new Cruiser(name,field);
    } else if (type == "Destroyer") {
        return new Destroyer(name,field);
    } else if (type == "Frigate") {
        return new Frigate(name,field);
    } else if (type == "Battleship") {
        return new Battleship(name,field);
    } else if (type == "Amphibious") {
        return new Amphibious(name,field);
    } else if (type == "SuperShip") {
        return new SuperShip(name,field);
    } else if(type == "Corvette") {
        return new Corvette(name,field);
    }else {
        return nullptr;
    }
}

Ship::Ship(const std::string& name,Field& field) : name(name) , field(field),lives(lives),posX(posX),posY(posY) {
    while (true) {
        //srand(time(0));
        posX = rand() % field.getWidth();
        posY = rand() % field.getHeight();
        //int DposY = 9-posY; // for coordinate type 
        if (field.getCell(posY, posX) == "0") {
            field.setCell(posY, posX, name);
            break;
        }
    }
}    


Battleship::Battleship(const std::string& name,Field& field) : Ship(name,field) {}

void Battleship::see() {
    std::cout << "Battleship sees" << std::endl;
}

void Battleship::move() {
    std::cout << "Battleship moves" << std::endl;
}

void Battleship::shoot() {
    std::cout << "Battleship shoots" << std::endl;
}



// Define the Cruiser class functions
void Cruiser::see() {
    std::cout << "Cruiser sees" << std::endl;
}

void Cruiser::step() {
    std::cout << "Cruiser steps" << std::endl;
}


// Define the Destroyer class functions
void Destroyer::see() {
    std::cout << "Destroyer sees" << std::endl;
}

void Destroyer::shoot() {
    std::cout << "Destroyer shoots" << std::endl;
}

void Destroyer::step() {
    std::cout << "Destroyer steps" << std::endl;
}


// Define the Frigate class functions
void Frigate::shoot() {
    std::cout << "Frigate shoots" << std::endl;
}



// Define the Corvette class functions
void Corvette::shoot() {
    std::cout << "Corvette shoots" << std::endl;
}

void Corvette::display() {
    std::cout << name << std::endl;
}

// Define the Amphibious class functions
void Amphibious::see() {
    std::cout << "Amphibious sees" << std::endl;
}

void Amphibious::move() {
    std::cout << "Amphibious moves" << std::endl;
}

void Amphibious::shoot() {
    std::cout << "Amphibious shoots" << std::endl;
}



// Define the SuperShip class functions
void SuperShip::shoot() {
    std::cout << "SuperShip shoots" << std::endl;
}

void SuperShip::see() {
    std::cout << "SuperShip sees" << std::endl;
}

void SuperShip::step() {
    std::cout << "SuperShip steps" << std::endl;
}

