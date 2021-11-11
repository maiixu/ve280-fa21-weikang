/*
 * @Author: Mai Xu
 * @Date: 2021-10-30 11:25:04
 * @LastEditTime: 2021-11-11 13:25:39
 * @Description: 2021 Fall VE280 Project 3
 * @FilePath: \p3\simulation.h
 */

#include "world_type.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

void errorArgument();
// MODIFIES: cout
//
// EFFECTS: Output error message into stdcout stream

void errorRound();
// MODIFIES: cout
//
// EFFECTS: Output error message into stdcout stream

void errorFileOpen(string err);
// MODIFIES: cout
//
// EFFECTS: Output error message into stdcout stream

void errorMaxSpecies();
// MODIFIES: cout
//
// EFFECTS: Output error message into stdcout stream

void errorMaxProgram(string err);
// MODIFIES: cout
//
// EFFECTS: Output error message into stdcout stream

void errorInstruction(string err);
// MODIFIES: cout
//
// EFFECTS: Output error message into stdcout stream

void errorMaxCreatures();
// MODIFIES: cout
//
// EFFECTS: Output error message into stdcout stream

void errorUnknownSpecies(string err);
// MODIFIES: cout
//
// EFFECTS: Output error message into stdcout stream

void errorUnknownDirection(string err);
// MODIFIES: cout
//
// EFFECTS: Output error message into stdcout stream

void errorGridHeight();
// MODIFIES: cout
//
// EFFECTS: Output error message into stdcout stream

void errorGridWidth();
// MODIFIES: cout
//
// EFFECTS: Output error message into stdcout stream

void errorInBound(string name, point_t location);
// MODIFIES: cout
//
// EFFECTS: Output error message into stdcout stream

void errorOverlap(string name1, string name2);
// MODIFIES: cout
//
// EFFECTS: Output error message into stdcout stream

point_t adjacentPoint(point_t pt, direction_t dir);
// EFFECTS: Returns a point that results from moving one square
//          in the direction "dir" from the point "pt".

direction_t leftFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turning
//          left from the given direction "dir".

direction_t rightFrom(direction_t dir);
// EFFECTS: Returns the direction that results from turning
//          right from the given direction "dir".

instruction_t getInstruction(const creature_t &creature);
// EFFECTS: Returns the current instruction of "creature".

class Simulation {
    //OVERVIEW: The whole simulation of the simple world process
    //          with error check inside the construction function.

public:
    Simulation(int argc, char *argv[]);
    // MODIFIES: this class simulation.
    //
    // EFFECTS: Initialize the simulation class and its properties with
    //          input arguments from terminal commands.

    ~Simulation() {
        delete world;
    };
    // MODIFIES: this class simulation.
    //
    // EFFECTS: Delete the simulation class instance.

    void simulate();
    // MODIFIES: this class simulation and its properties, cout.
    //
    // EFFECTS: Simulate the whole world by rounds.

private:
    string info[5];
    // Store the argv in cpp string form

    int round;
    // Simulation rounds

    bool ifVerbose;
    // Whether to print out the simulation state detailedly

    world_t *world;
    // Store the current simulation state

    species_t trans_sp(string species, string path);
    // MODIFIES: create a species struct.
    //
    // EFFECTS: Translate a string representation into a species by opening a file with file path and targXet species file.

    void getRounds(int rounds);
    // MODIFIES: the <round> property in simulation class.
    //
    // EFFECTS: Initialize the <round> property in simulation class.

    void getSpecies(string speciesFile);
    // MODIFIES: the <species> and <numSpecies> properties in the world struct.
    //
    // EFFECTS: Get species path and string from a file and initialize the <species> and <numSpecies> properties in the world struct.

    string getDirection(creature_t a);

    void initWorld(string worldFile);
    // MODIFIES: the rest of the properties in the world struct.
    //
    // EFFECTS: Initialize the rest part of world struct.

    void printGrid();
    // EFFECTS: Print a grid representation of the creature world.

    creature_t *getCreature(point_t location);
    // REQUIRES: location is inside the grid.
    //
    // EFFECTS: Returns a pointer to the creature at "location" in "grid".

    bool ifInside(point_t location);
    // EFFECTS: Returns a bool that judges whether the point is inside the grid.
    //          Returns false if the point is outside the grid.

    bool isSame(creature_t *a, point_t location);
    // EFFECTS: Judge whether the two species are the same.
    //          Returns true if the two species are the same.

    void hop(creature_t *creature);
    // MODIFIES: The input creature.
    //
    // EFFECTS: Apply opt_code hop to the creature.

    void left(creature_t *creature);
    // MODIFIES: The input creature.
    //
    // EFFECTS: Apply opt_code left to the creature.

    void right(creature_t *creature);
    // MODIFIES: The input creature.
    //
    // EFFECTS: Apply opt_code right to the creature.

    void infect(creature_t *creature);
    // MODIFIES: The input creature.
    //
    // EFFECTS: Apply opt_code infect to the creature.

    void ifEmpty(creature_t *creature, int n);
    // MODIFIES: The input creature.
    //
    // EFFECTS: Apply opt_code ifEmpty to the creature.

    void ifWall(creature_t *creature, int n);
    // MODIFIES: The input creature.
    //
    // EFFECTS: Apply opt_code ifWall to the creature.

    void ifSame(creature_t *creature, int n);
    // MODIFIES: The input creature.
    //
    // EFFECTS:  Apply opt_code ifSame to the creature.

    void ifEnemy(creature_t *creature, int n);
    // MODIFIES: The input creature.
    //
    // EFFECTS: Apply opt_code ifEnemy to the creature.

    void go(creature_t *creature, int n);
    // MODIFIES: The input creature.
    //
    // EFFECTS: Apply opt_code go to the creature.

    void operation(creature_t *creature, instruction_t instr);
    // MODIFIES: The input creature.
    //
    // EFFECTS: Apply different opt_code to the creature according to their instruction.

    void simulateCreature();
    // REQUIRES: creature is inside the grid.
    //
    // MODIFIES: simulation class, creature, cout.
    //
    // EFFECTS: Simulate one turn of "creature" and update the creature,
    //          the infected creature, and the grid if necessary.
    //          The creature programID is always updated. The function
    //          also prints to the stdout the procedure. If verbose is
    //          true, it prints more information.
};

// TODO:
// 1. 看看有没有能分出来的方程，debug输出ifenemy
// 2. verbose 输出
// 2. 多加一些try catch throw，写error class
// 3. 过joj
// 4. 对拍