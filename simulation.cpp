#include "Simulation.h"

Simulation::Simulation() {
    readGameFile("game.txt");
}

void Simulation::readGameFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error: Couldn't open " << filename << std::endl;
        return;
    }

    std::string line;
    file >> line >> field.iterations;
    file >> line >> field.width;
    file >> line >> field.height;

    file >> line >> team1.TeamName >> team1.Team_ships_count;
    for (int i = 0; i < team1.Team_ships_count; ++i) {
        std::string type, symbol;
        int count;
        file >> type >> symbol >> count;
        for (int j = 0; j < count; ++j) {
            Ship* ship = Ship::createShip(type);
            if (ship) {
                team1.ships.append(ship);
            }
        }
    }

    file >> line >> team2.TeamName >> team2.Team_ships_count;
    for (int i = 0; i < team2.Team_ships_count; ++i) {
        std::string type, symbol;
        int count;
        file >> type >> symbol >> count;
        for (int j = 0; j < count; ++j) {
            Ship* ship = Ship::createShip(type);
            if (ship) {
                team2.ships.append(ship);
            }
        }
    }

    field.sfield = false;
    field.rowCount = 0;
    while (getline(file, line)) {
        if (!field.sfield) {
            if (line[0] == '0') {
                field.sfield = true;
            } else {
                continue;
            }
        }
        if (field.sfield && field.rowCount < field.height) {
            int col = 0;
            for (char c : line) {
                if (c == '0' || c == '1') {
                    field.field[field.rowCount][col++] = c;
                    if (col >= field.width) break;
                }
            }
            field.rowCount++;
        }
    }

    file.close();
}