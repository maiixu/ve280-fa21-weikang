/*
 * @Author: your name
 * @Date: 2021-10-30 11:25:04
 * @LastEditTime: 2021-11-08 02:30:45
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \p3\simulation.h
 */
#include "world_type.h"
#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

void check();
void checkArgument();
void checkRound();
void checkFileOpen();
void checkMaxSpecies();
void checkMaxProgram();
void checkInstruction();
void checkMaxCreatures();
void checkUnknownSpecies();
void checkUnknownDirection();
void checkGridHeight();
void checkInBound();
void checkOverlap();
class Simulation {
    //OVERVIEW: xxxxx
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

    void printGrid(); // Print a grid representation of the creature world.
    creature_t *getCreature(point_t location);
    // REQUIRES: location is inside the grid.
    //
    // EFFECTS: Returns a pointer to the creature at "location" in "grid".
    bool ifInside(point_t location);              // Judge whether the point is inside the grid.
    bool ifSame(creature_t *a, point_t location); // Judge whether the two species are the same

    void hop(creature_t *creature);                            // Apply opt_code hop
    void left(creature_t *creature);                           // Apply opt_code left
    void right(creature_t *creature);                          // Apply opt_code right
    void infect(creature_t *creature);                         // Apply opt_code infect
    void ifEmpty(creature_t *creature, int n);                 // Apply opt_code ifEmpty
    void ifWall(creature_t *creature, int n);                  // Apply opt_code ifWall
    void ifSame(creature_t *creature, int n);                  // Apply opt_code ifSame
    void ifEnemy(creature_t *creature, int n);                 // Apply opt_code ifEnemy
    void go(creature_t *creature, int n);                      // Apply opt_code go
    void operation(creature_t *creature, instruction_t instr); // Operate different opt_code according to their instruction
    void simulateCreature();
    // REQUIRES: creature is inside the grid.
    //
    // MODIFIES: creature, grid, cout.
    //
    // EFFECTS: Simulate one turn of "creature" and update the creature,
    //          the infected creature, and the grid if necessary.
    //          The creature programID is always updated. The function
    //          also prints to the stdout the procedure. If verbose is
    //          true, it prints more information.
};

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

// TODO:
// 1. 看看有没有能分出来的方程，debug输出ifenemy
// 2. 多加一些try catch throw，写error class
// 3. 过joj
// 4. 对拍
// 5. 写注释
