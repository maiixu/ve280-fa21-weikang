/*
 * @Author: your name
 * @Date: 2021-10-30 11:25:12
 * @LastEditTime: 2021-11-02 23:40:07
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
    world = new world_t;
    getSpecies(argv[1]);
    initWorld(argv[2]);
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
                if (optCode == opName[4] || optCode == opName[5] || optCode == opName[6] || optCode == opName[7] || optCode == opName[8]) {
                    unsigned int optCode2;
                    spStream >> optCode2;
                    result.program[size].address = optCode2;
                }
                else {
                    result.program[size].address = 1000;
                }
                size++;
                break;
            }
        }
        if (line.empty()) { break; }
        /*
        if (!line.empty()) {
            string optCode2;
            spStream >> optCode2;
            if (optCode2[0] >= 48 && optCode2[0] <= 57) {
                result.program[size].address = stoi(optCode2, 0, 10);
            }
            else {
                result.program[size].address = 1000; // A large enough number
            }
        } */
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
    speciesStream.open(speciesFile);
    int i = 0;
    string line;
    while (getline(speciesStream, line)) {
        speciesArray[i] = line;
        i++;
    }
    world->numSpecies = i - 1;
    for (int j = 0; j < world->numSpecies; j++) {
        world->species[j] = trans_sp(speciesArray[j + 1], speciesArray[0]);
    }
    speciesStream.close();
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
            if (creatureFile[i] == world->species[j].name) {
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
    worldStream.close();
}

void Simulation::printGrid() {
    for (int i = 0; i < world->grid.height; i++) {
        for (int j = 0; j < world->grid.width; j++) {
            if (world->grid.squares[i][j] != NULL)
                switch (world->grid.squares[i][j]->direction) {
                case EAST:
                    cout << world->grid.squares[i][j]->species->name.substr(0, 2) << "_"
                         << "e"
                         << " ";
                    break;
                case WEST:
                    cout << world->grid.squares[i][j]->species->name.substr(0, 2) << "_"
                         << "w"
                         << " ";
                    break;
                case NORTH:
                    cout << world->grid.squares[i][j]->species->name.substr(0, 2) << "_"
                         << "n"
                         << " ";
                    break;
                case SOUTH:
                    cout << world->grid.squares[i][j]->species->name.substr(0, 2) << "_"
                         << "s"
                         << " ";
                    break;
                }
            else
                cout << "____ ";
        }
        cout << endl;
    }
}

creature_t *Simulation::getCreature(point_t location) {
    return world->grid.squares[location.r][location.c];
}

bool Simulation::ifInside(point_t location) {
    return (location.r >= 0 && location.r < world->grid.width && location.c >= 0 && location.c < world->grid.height);
}

bool Simulation::ifSame(creature_t *a, point_t location) {
    cout << (a->species->name == getCreature(location)->species->name) << "Great you are right. Z" << endl;
    return a->species->name == getCreature(location)->species->name;
}

void Simulation::hop(creature_t *creature) {
    point_t target = adjacentPoint(creature->location, creature->direction);
    if ((getCreature(target) == NULL) && ifInside(target)) {
        world->grid.squares[creature->location.r][creature->location.c] = NULL;
        creature->location = target;
        world->grid.squares[creature->location.r][creature->location.c] = creature;
    }
}

void Simulation::left(creature_t *creature) {
    creature->direction = leftFrom(creature->direction);
}

void Simulation::right(creature_t *creature) {
    creature->direction = rightFrom(creature->direction);
}

void Simulation::infect(creature_t *creature) {
    point_t target = adjacentPoint(creature->location, creature->direction);
    if ((getCreature(target) != NULL) && ifInside(target)) {
        getCreature(target)->programID = 0;
        getCreature(target)->species = creature->species;
    }
}

void Simulation::ifEmpty(creature_t *creature, int n) {
    point_t target = adjacentPoint(creature->location, creature->direction);
    if (((getCreature(target) == NULL) && ifInside(target))) {
        creature->programID = n - 1;
        operation(creature, creature->species->program[creature->programID]); //FIXME: Might have some bug
    }
    else {
        creature->programID = creature->programID + 1;
        operation(creature, creature->species->program[creature->programID]);
    }
}

void Simulation::ifWall(creature_t *creature, int n) {
    point_t target = adjacentPoint(creature->location, creature->direction);
    if (((getCreature(target) == NULL) && !ifInside(target))) {
        creature->programID = n - 1;
        operation(creature, creature->species->program[creature->programID]); //FIXME: Might have some bug
    }
    else {
        creature->programID = creature->programID + 1;
        operation(creature, creature->species->program[creature->programID]);
    }
}

void Simulation::ifSame(creature_t *creature, int n) {
    point_t target = adjacentPoint(creature->location, creature->direction);
    if (((getCreature(target) != NULL) && ifSame(creature, target))) {
        creature->programID = n - 1;
        operation(creature, creature->species->program[creature->programID]); //FIXME: Might have some bug
    }
    else {
        creature->programID = creature->programID + 1;
        operation(creature, creature->species->program[creature->programID]);
    }
}

void Simulation::ifEnemy(creature_t *creature, int n) {
    point_t target = adjacentPoint(creature->location, creature->direction);
    if (((getCreature(target) != NULL) && !ifSame(creature, target))) {
        creature->programID = n - 1;
        operation(creature, creature->species->program[creature->programID]); //FIXME: Might have some bug
    }
    else {
        creature->programID++;
        operation(creature, creature->species->program[creature->programID]);
    }
}

void Simulation::go(creature_t *creature, int n) {
    cout << creature->species->name << " in go1 applied " << n << opName[creature->species->program[creature->programID].op] << endl;
    creature->programID = n - 1;
    cout << creature->species->name << " in go2 applied " << opName[creature->species->program[creature->programID].op] << endl;
    operation(creature, creature->species->program[creature->programID]); //FIXME: Might have some bug
}

void Simulation::operation(creature_t *creature, instruction_t instr) {
    switch (instr.op) {
    case HOP:
        hop(creature);
        break;
    case LEFT:
        left(creature);
        break;
    case RIGHT:
        right(creature);
        break;
    case INFECT:
        infect(creature);
        break;
    case IFEMPTY:
        ifEmpty(creature, instr.address);
        break;
    case IFWALL:
        ifWall(creature, instr.address);
        break;
    case IFSAME:
        ifSame(creature, instr.address);
        break;
    case IFENEMY:
        ifEnemy(creature, instr.address);
        break;
    case GO:
        go(creature, instr.address);
        break;
    }
}

void Simulation::simulateCreature() {
    for (int i = 0; i < world->numCreatures; i++) {
        cout << world->creatures[i].species->name << " is going to apply " << opName[getInstruction(world->creatures[i]).op] << endl;
        operation(getCreature(world->creatures[i].location), getInstruction(world->creatures[i]));
        cout << world->creatures[i].species->name << " actually applied " << opName[getInstruction(world->creatures[i]).op] << endl;
        world->creatures[i].programID++;
    }
}

void Simulation::simulate() {
    cout << "Initial State:" << endl;
    printGrid();
    for (int i = 0; i < round; i++) {
        simulateCreature();
        cout << "Round " << i + 1 << ":" << endl;
        printGrid();
    }
}

direction_t leftFrom(direction_t dir) {
    switch (dir) {
    case EAST:
        return NORTH;
        break;
    case NORTH:
        return WEST;
        break;
    case WEST:
        return SOUTH;
        break;
    case SOUTH:
        return EAST;
        break;
    default:
        return dir;
        break;
    }
}

direction_t rightFrom(direction_t dir) {
    switch (dir) {
    case EAST:
        return SOUTH;
        break;
    case NORTH:
        return EAST;
        break;
    case WEST:
        return NORTH;
        break;
    case SOUTH:
        return WEST;
        break;
    default:
        return dir;
        break;
    }
}

point_t adjacentPoint(point_t pt, direction_t dir) {
    switch (dir) {
    case EAST:
        pt.c++;
        return pt;
        break;
    case NORTH:
        pt.r--;
        return pt;
        break;
    case WEST:
        pt.c--;
        return pt;
        break;
    case SOUTH:
        pt.r++;
        return pt;
        break;
    default:
        return pt;
        break;
    }
}

instruction_t getInstruction(const creature_t &creature) {
    return creature.species->program[creature.programID];
}
