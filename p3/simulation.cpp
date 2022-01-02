/*
 * @Author: Mai Xu
 * @Date: 2021-10-30 11:25:12
 * @LastEditTime: 2021-11-12 23:18:03
 * @Description: 2021 Fall VE280 Project 3
 * @FilePath: \p3\simulation.cpp
 */

#include "simulation.h"
#include <fstream>
#include <sstream>

void errorArgument() {
    cout << "Error: Missing arguments!" << endl;
    cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << endl;
}

void errorRound() {
    cout << "Error: Number of simulation rounds is negative!" << endl;
}

void errorFileOpen(string err) {
    cout << "Error: Cannot open file " << err << "!" << endl;
}

void errorMaxSpecies() {
    cout << "Error: Too many species!" << endl;
    cout << "Maximal number of species is " << MAXSPECIES << "." << endl;
}

void errorMaxProgram(string err) {
    cout << "Error: Too many instructions for species " << err << "!" << endl;
    cout << "Maximal number of instructions is " << MAXPROGRAM << "." << endl;
}

void errorInstruction(string m) {
    cout << "Error: Instruction " << m << " is not recognized!" << endl;
}

void errorMaxCreatures() {
    cout << "Error: Too many creatures!" << endl;
    cout << "Maximal number of creatures is " << MAXCREATURES << "." << endl;
}

void errorUnknownSpecies(string m) {
    cout << "Error: Species " << m << " not found!" << endl;
}

void errorUnknownDirection(string m) {
    cout << "Error: Direction " << m << " is not recognized!" << endl;
}

void errorGridHeight() {
    cout << "Error: The grid height is illegal!" << endl;
}

void errorGridWidth() {
    cout << "Error: The grid width is illegal!" << endl;
}

void errorInBound(string name, point_t location, int width, int height, string dir) {
    cout << "Error: Creature (" << name << " " << dir << " " << location.r << " " << location.c << ") is out of bound!" << endl;
    cout << "The grid size is " << height << "-by-" << width << "." << endl;
}

void errorOverlap(string name1, string name2, point_t location1, string dir1, point_t location2, string dir2) {
    cout << "Error: Creature (" << name1 << " " << dir1 << " " << location1.r << " " << location1.c << ") overlaps with creature (" << name2 << " " << dir2 << " " << location2.r << " " << location2.c << ")!" << endl;
}

Simulation::Simulation(int argc, char *argv[]) {
    // Initialize ifVerbose
    if (argc >= 5) {
        // Initialize info
        for (int i = 0; i < 5; ++i) {
            info[i] = argv[i];
        }
        if (info[4] == "v" || info[4] == "verbose") {
            ifVerbose = true;
        }
    }
    else if (argc == 4) {
        ifVerbose = false;
        // Initialize info
        for (int i = 0; i < 4; ++i) {
            info[i] = argv[i];
        }
    }
    // Argument Error Judge
    else {
        errorArgument();
        exit(0);
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
    string speciesPath = path + "/" + species;
    string line;
    int size = 0;
    opcode_t opt[9] = {HOP, LEFT, RIGHT, INFECT, IFEMPTY, IFENEMY, IFSAME, IFWALL, GO}; // For optcode check
    ifstream opStream(speciesPath);
    if (!opStream.is_open()) { // File Open Error Judge
        errorFileOpen(speciesPath);
        exit(0);
    }
    while (getline(opStream, line)) {
        istringstream spStream;
        spStream.str(line);
        string optCode;
        spStream >> optCode;
        bool judge = false;
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
                judge = true;
                break;
            }
        }
        if (line.empty()) {
            break;
        }
        if (judge == false) {
            errorInstruction(optCode);
            opStream.close();
            exit(0);
        } // Instruction Error Judge
    }
    opStream.close();
    result.programSize = size;
    judgeMaxProgram(result.programSize, result.name);
    return result;
}

void Simulation::judgeMaxProgram(int size, string name) {
    if ((unsigned int)size > MAXPROGRAM) {
        errorMaxProgram(name);
        exit(0);
    } // Max Program Error Judge
}

void Simulation::getRounds(int rounds) {
    round = rounds;
    if (round < 0) {
        errorRound();
        exit(0);
    } // Error Round Judge
}

void Simulation::getSpecies(string speciesFile) {
    string speciesArray[MAXSPECIES + 3];
    ifstream speciesStream(speciesFile);
    if (!speciesStream.is_open()) {
        errorFileOpen(speciesFile);
        exit(0);
    } // Error File Open
    int i = 0;
    string line;
    while (getline(speciesStream, line)) {
        if ((unsigned int)i > MAXSPECIES) {
            errorMaxSpecies();
            exit(0);
        } // Error Max Species
        speciesArray[i] = line;
        i++;
    }
    speciesStream.close();
    world->numSpecies = i - 1;
    for (int j = 0; j < (int)world->numSpecies; j++) {
        world->species[j] = trans_sp(speciesArray[j + 1], speciesArray[0]);
    } // translate to species
}

string Simulation::getDirection(creature_t a) {
    switch (a.direction) {
    case EAST:
        return "east";
        break;
    case WEST:
        return "west";
        break;
    case NORTH:
        return "north";
        break;
    case SOUTH:
        return "south";
        break;
    default:
        return "";
    }
}

void Simulation::judgeHeightWidth() {
    if (world->grid.height > MAXHEIGHT || world->grid.height <= 0) {
        errorGridHeight();
        throw false;
    }
    if (world->grid.width > MAXWIDTH || world->grid.width <= 0) {
        errorGridWidth();
        throw false;
    }
}

void Simulation::initDirection(string temp, int i) {
    if (temp == "east") {
        world->creatures[i].direction = EAST;
    }
    else if (temp == "west") {
        world->creatures[i].direction = WEST;
    }
    else if (temp == "north") {
        world->creatures[i].direction = NORTH;
    }
    else if (temp == "south") {
        world->creatures[i].direction = SOUTH;
    }
    else {
        errorUnknownDirection(temp);
        throw false;
    }
}

void Simulation::judgeOverlap() {
    for (int a = 0; a < (int)world->numCreatures; a++) {
        for (int j = 0; j < a; j++) {
            if ((world->creatures[a].location.r == world->creatures[j].location.r) && (world->creatures[a].location.c == world->creatures[j].location.c)) {
                errorOverlap(world->creatures[a].species->name, world->creatures[j].species->name, world->creatures[a].location, getDirection(world->creatures[a]), world->creatures[j].location, getDirection(world->creatures[j]));
                exit(0);
            }
        }
    }
}

void Simulation::initCreature(string *creatureFile, int &i, string line) {
    if ((unsigned int)i >= MAXCREATURES) {
        errorMaxCreatures();
        throw false;
    }
    istringstream is(line);
    is >> creatureFile[i];
    bool judge = false;
    for (int j = 0; j < (int)world->numSpecies; j++) {
        if (creatureFile[i] == world->species[j].name) {
            species_t *p = &(world->species[j]);
            world->creatures[i].species = p;
            judge = true;
        }
    }
    if (judge == false) {
        errorUnknownSpecies(creatureFile[i]);
        throw false;
    }
    is >> line;
    try {
        initDirection(line, i);
    } catch (bool exception) {
        throw false;
    }
    is >> world->creatures[i].location.r; // r is height
    is >> world->creatures[i].location.c; // c is width
    if (!ifInside(world->creatures[i].location)) {
        errorInBound(world->creatures[i].species->name, world->creatures[i].location, world->grid.height, world->grid.width, getDirection(world->creatures[i]));
        throw false;
    }
    world->creatures[i].programID = 0;
    creature_t *p = &(world->creatures[i]);
    world->grid.squares[world->creatures[i].location.r][world->creatures[i].location.c] = p;
    i++;
}

void Simulation::initWorld(string worldFile) {
    string creatureFile[MAXCREATURES];
    ifstream worldStream(worldFile);
    if (!worldStream.is_open()) {
        errorFileOpen(worldFile);
        exit(0);
    }
    string line;
    getline(worldStream, line);
    world->grid.height = stoi(line, 0, 10);
    getline(worldStream, line);
    world->grid.width = stoi(line, 0, 10);
    try {
        judgeHeightWidth();
    } catch (bool exception) {
        worldStream.close();
        exit(0);
    }
    int i = 0;
    while (getline(worldStream, line)) {
        try {
            initCreature(creatureFile, i, line);
        } catch (bool exception) {
            worldStream.close();
            exit(0);
        }
    }
    worldStream.close();
    world->numCreatures = i;
    judgeOverlap(); // Judge overlap error
}

void Simulation::printGrid() {
    for (int i = 0; i < (int)world->grid.height; i++) {
        for (int j = 0; j < (int)world->grid.width; j++) {
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
    if (!world->grid.squares[location.r][location.c]) {
        return NULL;
    }
    else {
        return world->grid.squares[location.r][location.c];
    }
}

bool Simulation::ifInside(point_t location) {
    if (world->grid.height == 0 || world->grid.width == 0) {
        return true;
    }
    return ((int)location.r >= 0 && (int)location.r < (int)world->grid.height && (int)location.c >= 0 && (int)location.c < (int)world->grid.width);
}

bool Simulation::isSame(creature_t *a, point_t location) {
    int res = a->species->name.compare(getCreature(location)->species->name);
    if (res == 0)
        return true;
    else
        return false;
}

void Simulation::hop(creature_t *creature) {
    point_t target = adjacentPoint(creature->location, creature->direction);
    if (ifInside(target)) {
        if (!getCreature(target)) {
            world->grid.squares[creature->location.r][creature->location.c] = NULL;
            creature->location = target;
            world->grid.squares[creature->location.r][creature->location.c] = creature;
        }
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
    if (ifInside(target)) {
        if (getCreature(target)) {
            getCreature(target)->programID = 0;
            getCreature(target)->species = creature->species;
        }
    }
}

void Simulation::ifEmpty(creature_t *creature, int n) {
    point_t target = adjacentPoint(creature->location, creature->direction);
    if (ifInside(target)) {
        if (!getCreature(target)) {
            creature->programID = n - 1;
            operation(creature, creature->species->program[creature->programID]);
        }
        else {
            creature->programID++;
            operation(creature, creature->species->program[creature->programID]);
        }
    }
    else {
        creature->programID++;
        operation(creature, creature->species->program[creature->programID]);
    }
}

void Simulation::ifWall(creature_t *creature, int n) {
    point_t target = adjacentPoint(creature->location, creature->direction);
    if (!ifInside(target)) {
        creature->programID = n - 1;
        operation(creature, creature->species->program[creature->programID]);
    }
    else {
        creature->programID++;
        operation(creature, creature->species->program[creature->programID]);
    }
}

void Simulation::ifSame(creature_t *creature, int n) {
    point_t target = adjacentPoint(creature->location, creature->direction);
    if (ifInside(target)) {
        if (getCreature(target) && isSame(creature, target)) {
            creature->programID = n - 1;
            operation(creature, creature->species->program[creature->programID]);
        }
        else {
            creature->programID++;
            operation(creature, creature->species->program[creature->programID]);
        }
    }
    else {
        creature->programID++;
        operation(creature, creature->species->program[creature->programID]);
    }
}

void Simulation::ifEnemy(creature_t *creature, int n) {
    point_t target = adjacentPoint(creature->location, creature->direction);
    if (ifInside(target)) {
        if (getCreature(target) && !isSame(creature, target)) {
            creature->programID = n - 1;
            operation(creature, creature->species->program[creature->programID]);
        }
        else {
            creature->programID++;
            operation(creature, creature->species->program[creature->programID]);
        }
    }
    else {
        creature->programID++;
        operation(creature, creature->species->program[creature->programID]);
    }
}

void Simulation::go(creature_t *creature, int n) {
    creature->programID = n - 1;
    operation(creature, creature->species->program[creature->programID]);
}

void Simulation::operation(creature_t *creature, instruction_t instr) {
    if (ifVerbose)
        cout << "Instruction " << (creature->programID + 1) << ": "; // Judge whether to print verbose instructions
    switch (instr.op) {
    case HOP:
        cout << "hop" << endl;
        hop(creature);
        break;
    case LEFT:
        cout << "left" << endl;
        left(creature);
        break;
    case RIGHT:
        cout << "right" << endl;
        right(creature);
        break;
    case INFECT:
        cout << "infect" << endl;
        infect(creature);
        break;
    case IFEMPTY:
        if (ifVerbose)
            cout << "ifempty " << instr.address << endl;
        ifEmpty(creature, instr.address);
        break;
    case IFWALL:
        if (ifVerbose)
            cout << "ifwall " << instr.address << endl;
        ifWall(creature, instr.address);
        break;
    case IFSAME:
        if (ifVerbose)
            cout << "ifsame " << instr.address << endl;
        ifSame(creature, instr.address);
        break;
    case IFENEMY:
        if (ifVerbose)
            cout << "ifenemy " << instr.address << endl;
        ifEnemy(creature, instr.address);
        break;
    case GO:
        if (ifVerbose)
            cout << "go " << instr.address << endl;
        go(creature, instr.address);
        break;
    }
}

void Simulation::simulateCreature() {
    for (int i = 0; i < (int)world->numCreatures; i++) {
        cout << "Creature (" << world->creatures[i].species->name << " " << getDirection(world->creatures[i]) << " " << world->creatures[i].location.r << " " << world->creatures[i].location.c << ") takes action:";
        if (ifVerbose)
            cout << endl;
        else
            cout << " ";
        operation(getCreature(world->creatures[i].location), getInstruction(world->creatures[i]));
        world->creatures[i].programID++;
        if (ifVerbose)
            printGrid();
    }
}

void Simulation::simulate() {
    cout << "Initial state" << endl;
    printGrid();
    for (int i = 0; i < round; i++) {
        cout << "Round " << i + 1 << endl;
        simulateCreature();
        if (!ifVerbose)
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
