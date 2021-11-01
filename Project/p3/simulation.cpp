/*
 * @Author: your name
 * @Date: 2021-10-30 11:25:12
 * @LastEditTime: 2021-11-01 23:45:52
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \p3\simulation.cpp
 */

#include "simulation.h"
#include <fstream>
#include <sstream>

// TODO: Put all argument in a check class operated at the beginning.
/* else {
        ifVerbose = false;
        cout << "Error: Missing arguments!" << endl;
        cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << endl;
    } */
// initWorld(world, argc[], argv);

Simulation::Simulation(int argc, char *argv[]) {
    // Initialize ifVerbose
    if (argc >= 5) {
        ifVerbose = true;
        // Initialize info
        for (int i = 0; i < 5; ++i) {
            info[i] = argv[i];
        }
    }
    else if (argc == 4) {
        ifVerbose = false;
        // Initialize info
        for (int i = 0; i < 4; ++i) {
            info[i] = argv[i];
        }
    }
    // Initialize round
    getRounds(atoi(argv[3]));
    // Initialize world
    getSpecies(argv[1]);
    cout << "Great You Are Right!3" << endl;
    initWorld(argv[2]);
    cout << "Great You Are Right!4" << endl;
}

species_t Simulation::trans_sp(string species, string path) {
    species_t result;
    result.name = species;
    ifstream opStream;
    opStream.open(path + "/" + species);
    string line;
    int size = 0;
    opcode_t opt[9] = {HOP, LEFT, RIGHT, INFECT, IFEMPTY, IFENEMY, IFSAME, IFWALL, GO};
    while (getline(opStream, line)) {
        istringstream spStream;
        spStream.str(line);
        string optCode;
        spStream >> optCode;
        for (int i = 0; i < 9; i++) {
            if (optCode == opName[i]) {
                result.program[size].op = opt[i];
                size++;
                break;
            }
        }
        if (!line.empty()) {
            string optCode2;
            spStream >> optCode2;
            if (optCode2[0] >= 48 && optCode2[0] <= 57) {
                result.program[size].address = stoi(optCode2, 0, 10);
            }
        }
    }
    result.programSize = size;
    opStream.close();
    return result;
}

void Simulation::getRounds(int rounds) {
    round = rounds;
}

void Simulation::getSpecies(string speciesFile) {
    string speciesArray[MAXSPECIES + 1];
    ifstream speciesStream;
    cout << "Great You Are Right! A" << endl;
    speciesStream.open(speciesFile);
    int i = 0;
    string line;
    cout << "Great You Are Right! B" << endl;
    while (getline(speciesStream, line)) {
        speciesArray[i] = line;
        i++;
    }
    cout << "Great You Are Right! C" << endl;
    world->numSpecies = i - 1;
    cout << "Great You Are Right! F" << endl;
    for (int j = 0; j < world->numSpecies; j++) {
        cout << "Great You Are Right! G" << endl;
        world->species[j] = trans_sp(speciesArray[j + 1], speciesArray[0]);
    }
    cout << "Great You Are Right! D" << endl;
    speciesStream.close();
    cout << "Great You Are Right! E" << endl;
}

void Simulation::initWorld(string worldFile) {
    string creatureFile[MAXCREATURES];
    direction_t list[4] = {EAST, SOUTH, WEST, NORTH};
    ifstream worldStream;
    worldStream.open(worldFile);
    string line;
    getline(worldStream, line);
    world->grid.height = stoi(line, 0, 10);
    getline(worldStream, line);
    world->grid.width = stoi(line, 0, 10);
    int i = 0;
    while (getline(worldStream, line)) {
        istringstream is(line);
        is >> creatureFile[i];
        for (int j = 0; j < world->numSpecies; j++) {
            if (creatureFile[j] == world->species[j].name) {
                species_t *p = &(world->species[j]);
                world->creatures[i].species = p;
            }
        }
        string temp;
        is >> temp;
        if (temp[0] == 'e') {
            world->creatures[i].direction = EAST;
        }
        else if (temp[0] == 'w') {
            world->creatures[i].direction = WEST;
        }
        else if (temp[0] == 'n') {
            world->creatures[i].direction = NORTH;
        }
        else {
            world->creatures[i].direction = SOUTH;
        }
        int r, c;
        is >> r;
        is >> c;
        world->creatures[i].location.r = r;
        world->creatures[i].location.c = c;
        world->creatures[i].programID = 0;
        creature_t *p = &(world->creatures[i]);
        world->grid.squares[r][c] = p;
        i++;
    }
    world->numCreatures = i;
    // TODO: 问问指针在类里面需不需要初始化
    worldStream.close();
}

void Simulation::printGrid(const grid_t &grid) {
    for (int i = 0; i < world->grid.height; i++) {
        for (int j = 0; j < world->grid.width; j++) {
            if (world->grid.squares[i][j] != NULL)
                cout << grid.squares[i][j]->species->name.substr(0, 2) << " ";
            else
                cout << "____ ";
        }
    }
}

void Simulation::simulate() {
    printGrid(world->grid);
}