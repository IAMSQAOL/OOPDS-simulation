#ifndef TEAM_H
#define TEAM_H

#include "Ship.h"
#include "LinkedList.h"
#include <string>

struct Team {
    char TeamName;
    int Team_ships_count;
    LinkedList ships;

    ~Team() {
        Node* current = ships.head;
        while (current != nullptr) {
            delete current->data;
            current = current->next;
        }
    }

};

#endif