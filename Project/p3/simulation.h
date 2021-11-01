/*
 * @Author: your name
 * @Date: 2021-10-30 11:25:04
 * @LastEditTime: 2021-11-02 00:02:17
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \p3\simulation.h
 */
#include "world_type.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

class Simulation {
public:
    Simulation(int argc, char *argv[]);
    ~Simulation() {
        delete world;
    };
    void simulate(); // The whole process

private:
    string info[5]; // Store the argv in cpp string form
    int round;
    bool ifVerbose;
    world_t *world;
    species_t trans_sp(string species, string path); // Translate a string representation into a species
    void getRounds(int rounds);                      // Initialize round
    void getSpecies(string speciesFile);             // Get species path and string from a file and initialize species and numSpecies in world
    void initWorld(string worldFile);                // Initialize the rest part of world
    void printGrid(const grid_t &grid);              // Print a grid representation of the creature world.
};

void simulateCreature(creature_t &creature, grid_t &grid, bool verbose);
// REQUIRES: creature is inside the grid.
//
// MODIFIES: creature, grid, cout.
//
// EFFECTS: Simulate one turn of "creature" and update the creature,
//          the infected creature, and the grid if necessary.
//          The creature programID is always updated. The function
//          also prints to the stdout the procedure. If verbose is
//          true, it prints more information.

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

creature_t *getCreature(const grid_t &grid, point_t location);
// REQUIRES: location is inside the grid.
//
// EFFECTS: Returns a pointer to the creature at "location" in "grid".
