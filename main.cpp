#include "Simulation.h"
#include <iostream>

using namespace std;

int main() {
    Simulation simulation;

    cout << "Iterations: " << simulation.field.iterations << endl;
    cout << "Battlefield size: " << simulation.field.width << "x" << simulation.field.height << endl;

    cout << "Team A ships:" << endl;
    simulation.team1.ships.display();

    cout << "Team B ships:" << endl;
    simulation.team2.ships.display();

    cout << "Battlefield:" << endl;
    simulation.field.printField();

    return 0;
}