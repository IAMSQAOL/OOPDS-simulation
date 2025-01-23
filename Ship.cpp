#include "Ship.h"

Ship* Ship::createShip(const std::string& type) {
    if (type == "Cruiser") {
        return new Cruiser();
    } else if (type == "Destroyer") {
        return new Destroyer();
    } else if (type == "Frigate") {
        return new Frigate();
    } else if (type == "Battleship") {
        return new Battleship();
    } else if (type == "Amphibious") {
        return new Amphibious();
    } else if (type == "SuperShip") {
        return new SuperShip();
    } else {
        return nullptr;
    }
}