#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <string>

class Field;
class LinkedList;
class Queue;
class Stack;

class Ship {
public:
    bool CanMove;
    char Team_name;
    std::string Ship_name, Ship_type;
    int Ship_lives = 3;
    int Ship_kill_count = 0;
    int posX = -1, posY = -1, nextX = -1, nextY = -1;
    bool Ship_upgrade = false;
    bool ShootPosition = false;
    int record = 0;
    int targetX = -1;
    int targetY = -1;
    bool Ship_die = false;

    Ship();
    virtual ~Ship();

    virtual void actions(Field& field, LinkedList& ships, Queue& DESships, Stack& uS) = 0;
    static Ship* createShip(const char& Team_name, const std::string& Ship_Type, const std::string& Ship_name, Field& field, LinkedList& ships, Queue& DESships, Stack& uS);
    static Ship* updateShip(const char& Team_name, const std::string& Ship_Type, const std::string& Ship_name,const int& posX, const int& posY, Field& field, LinkedList& ships, Queue& DESships, Stack& uS);
};

#endif // SHIP_H