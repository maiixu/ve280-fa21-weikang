/*
 * @Author: your name
 * @Date: 2021-10-30 14:36:16
 * @LastEditTime: 2021-11-08 02:12:51
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \p3\p3.cpp
 */

#include <iostream>
#include "world_type.h"
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[]) {
    try {
        Simulation mySimulation(argc, argv);
        mySimulation.simulate();
    } catch (bool Exception) {
        return -1;
    }
    return 0;
}